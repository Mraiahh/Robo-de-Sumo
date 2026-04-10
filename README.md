# Robô de Sumô Autônomo

Projeto de robótica embarcada desenvolvido com foco em competições de sumô, envolvendo integração entre hardware e software para tomada de decisão em tempo real.

O robô é capaz de detectar adversários e limites da arena de forma autônoma, utilizando sensores e lógica embarcada para executar estratégias de ataque e evasão.

---

## Objetivo

Desenvolver um robô autônomo capaz de competir em arenas de sumô, tomando decisões em tempo real para:

- Identificar e localizar o adversário
- Evitar sair da arena
- Executar movimentos estratégicos de ataque

---

## Funcionalidades

- Detecção de adversário por sensores de distância  
- Identificação da borda da arena com sensores de linha  
- Tomada de decisão em tempo real  
- Movimentação autônoma baseada em estratégia  
- Controle de motores DC via ponte H  

---

## Lógica de Funcionamento

O comportamento do robô é baseado em decisões reativas:

1. Se detectar a borda → recua imediatamente  
2. Se detectar adversário → avança para ataque  
3. Se não detectar nada → executa busca ativa  

Essa abordagem permite operação totalmente autônoma durante a luta.

---

## Tecnologias Utilizadas

- **ESP32**
- **Linguagem C**
- Sensores de linha (IR)
- Sensores de distância (ultrassônico ou similar)
- Ponte H (controle de motores)
- Motores DC

---

## Arquitetura do Sistema

O sistema é composto por três principais módulos:

- **Percepção:** leitura dos sensores  
- **Processamento:** lógica de decisão embarcada  
- **Ação:** controle dos motores  

---

## Como Executar

1. Conectar o ESP32 ao computador
2. Compilar e enviar o código para a placa
3. Posicionar o robô na arena
4. Ligar o sistema

---

## Demonstração

https://youtube.com/shorts/otXRvUk7AIg?si=HNHDcXg92-bsDvUM

---

## Desafios e Aprendizados

Durante o desenvolvimento e testes do robô, foram identificados alguns desafios relevantes:

- O robô utiliza uma estratégia de busca baseada em rotação rápida, o que coincidiu com o nome "Robolation". Essa abordagem permitia uma varredura dinâmica do ambiente, favorecendo a rápida identificação de adversários durante a competição.
- A distribuição de peso e estrutura física do hardware afetaram a estabilidade, resultando em tendência de inclinação para trás durante movimentos mais agressivos.

Apesar dessas limitações, o robô conseguiu operar de forma funcional e competitiva, alcançando o **3º lugar na competição**.

Esses desafios contribuíram para aprendizados importantes, como:
- Importância do balanceamento mecânico em sistemas embarcados móveis
- Impacto do design físico no desempenho do sistema
- Necessidade de integração eficiente entre hardware e lógica de controle

---

## Autores

Mariah Cesar: @Mraiahh

Rômulo Lopes: @romulolpaula
