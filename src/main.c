#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ===== ULTRASSOM =====
#define TRIG_PIN 23
#define ECHO_PIN 22

// ===== MOTORES =====
#define IN1 18
#define IN2 19
#define IN3 16
#define IN4 17

// ===== SENSOR DE BORDA =====
#define LINE_SENSOR 34   // TCRT5000 DO

// ===== CONFIG =====
#define DIST_TARGET 38     // perseguir
#define DIST_ATTACK 12     // colado
#define READ_DELAY_MS 90   // tempo entre leituras
#define SCAN_MS 260

//---------------------------------------------
// FUNÇÃO ULTRASSOM ESTÁVEL
//---------------------------------------------
float read_distance(){
    gpio_set_level(TRIG_PIN,0);
    esp_rom_delay_us(4);
    gpio_set_level(TRIG_PIN,1);
    esp_rom_delay_us(12);
    gpio_set_level(TRIG_PIN,0);

    uint64_t timeout = esp_timer_get_time()+35000;

    while(gpio_get_level(ECHO_PIN)==0){
        if(esp_timer_get_time()>timeout) return -1;
    }

    uint64_t start = esp_timer_get_time();
    while(gpio_get_level(ECHO_PIN)==1){
        if(esp_timer_get_time()>timeout) return -1;
    }

    float t = esp_timer_get_time()-start;
    float dist = (t*0.0343f)/2.0f;

    if(dist<1 || dist>300) return -1;
    return dist;
}

// ===== MOTOR =====
void stop(){
    gpio_set_level(IN1,0); gpio_set_level(IN2,0);
    gpio_set_level(IN3,0); gpio_set_level(IN4,0);
}

void front(){
    gpio_set_level(IN1,1); gpio_set_level(IN2,0);
    gpio_set_level(IN3,1); gpio_set_level(IN4,0);
}

void back(){
    gpio_set_level(IN1,0); gpio_set_level(IN2,1);
    gpio_set_level(IN3,0); gpio_set_level(IN4,1);
}

void turn_right(){
    gpio_set_level(IN1,1); gpio_set_level(IN2,0);
    gpio_set_level(IN3,0); gpio_set_level(IN4,1);
}

void turn_left(){
    gpio_set_level(IN1,0); gpio_set_level(IN2,1);
    gpio_set_level(IN3,1); gpio_set_level(IN4,0);
}

// ===== INIT =====
void init_gpio(){
    gpio_set_direction(TRIG_PIN,GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN,GPIO_MODE_INPUT);

    gpio_set_direction(IN1,GPIO_MODE_OUTPUT);
    gpio_set_direction(IN2,GPIO_MODE_OUTPUT);
    gpio_set_direction(IN3,GPIO_MODE_OUTPUT);
    gpio_set_direction(IN4,GPIO_MODE_OUTPUT);

    gpio_set_direction(LINE_SENSOR, GPIO_MODE_INPUT);

    stop();
}

// ===== MAIN =====
void app_main(){
    init_gpio();
    printf("🔥 Bota a mão na cabeça que vai começar 🔥\n");

    vTaskDelay(pdMS_TO_TICKS(5000));

    float d = -1;

    while(1){

        // ❗ PRIMEIRO SEMPRE CHECA BORDA
        if(gpio_get_level(LINE_SENSOR) == 1){
            // encontrou branco
            printf("⚠️ BORDA DETECTADA! ⚠️\n");
            back();
            vTaskDelay(pdMS_TO_TICKS(180));
            turn_left();
            vTaskDelay(pdMS_TO_TICKS(260));
            continue;
        }

        // ===== ULTRASSOM =====
        d = read_distance();
        vTaskDelay(pdMS_TO_TICKS(READ_DELAY_MS));

        if(d < 0){
            turn_right();
            vTaskDelay(pdMS_TO_TICKS(SCAN_MS));
            continue;
        }

        // ===== ATAQUE =====
        if(d <= DIST_ATTACK){
            front();
            while(1){
                if(gpio_get_level(LINE_SENSOR)==1) break;
                float da = read_distance();
                if(da < 0 || da > DIST_TARGET) break;
                vTaskDelay(pdMS_TO_TICKS(40));
            }
            continue;
        }

        // ===== PERSEGUIR =====
        if(d <= DIST_TARGET){
            front();
            continue;
        }

        // ===== SCAN =====
        turn_right();
        vTaskDelay(pdMS_TO_TICKS(SCAN_MS));
    }
}
