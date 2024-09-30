# README

## Visão Geral
Este código em C para um microcontrolador AVR implementa um sistema de aquisição de dados que lê valores de dois canais do conversor analógico-digital (ADC). Ele calcula a média das leituras, exibe os resultados em formato hexadecimal e decimal via UART (Universal Asynchronous Receiver/Transmitter), e acende um LED durante a transmissão de dados.

## Requisitos de Hardware
- Microcontrolador AVR (ex: ATmega328P)
- Sensores ou dispositivos que forneçam saídas analógicas para o ADC
- Conexões UART para transmissão de dados (ex: módulo Bluetooth ou cabo serial)
- Um LED para indicação visual
- Ambiente de desenvolvimento AVR para compilação (ex: Atmel Studio)
- Um clock externo rodando a 16 MHz

## Funcionalidades
- **Leitura do ADC**: O código realiza leituras do ADC em dois canais e calcula a média das leituras.
- **Transmissão Serial**: Os resultados são enviados via UART, permitindo a visualização em um monitor serial.
- **Indicação com LED**: Um LED é acionado durante a transmissão de dados, fornecendo feedback visual.
- **Formatação dos Resultados**: Os valores lidos são formatados em hexadecimal e decimal, além de serem convertidos em unidades de tensão, porcentagem e temperatura.

## Estrutura do Código

### Definições e Inicializações
- **`#define F_CPU`**: Define a frequência do clock do microcontrolador.
- **`volatile`**: Declara variáveis utilizadas em interrupções e que podem ser alteradas fora do controle do código.

### Inicialização da UART (`init_serial`)
- Configura os registradores da UART para habilitar a comunicação serial, definindo a taxa de transmissão.

### Inicialização do ADC (`init_adc`)
- Configura os registradores `ADCSRA` e `ADMUX` para habilitar o ADC e selecionar o canal.

### Inicialização de Entradas e Saídas (`init_io`)
- Configura o pino do LED como saída.

### Leitura do ADC (`read_adc`)
- Realiza a leitura do ADC para um canal específico e retorna o valor lido.

### Funções de Transmissão e Formatação
- **`uart_tx`**: Envia um byte via UART.
- **`uart_string`**: Envia uma string via UART.
- **`print_hexa`, `print_dec`, `print_volt`, `print_TEMP`, `print_POT`**: Formatam e preparam os dados para a transmissão em diferentes formatos.

### Loop Principal (`main`)
- O loop realiza as seguintes tarefas:
  1. Realiza leituras de ADC em dois canais, somando os resultados.
  2. Calcula a média das leituras.
  3. Formata os dados e os envia via UART.
  4. Aciona o LED durante a transmissão de dados.
  5. Repete o processo a cada 300 ms.

## Como Funciona
1. **Inicialização**: O microcontrolador é inicializado, configurando a UART e o ADC, além de definir o pino do LED.
2. **Coleta de Dados**: O loop realiza leituras do ADC em dois canais, somando e calculando a média das leituras.
3. **Transmissão dos Resultados**: Os resultados são formatados em hexadecimal, decimal, e convertidos em unidades de tensão, porcentagem e temperatura, enviados pela UART.
4. **Indicação Visual**: Um LED é acionado durante a transmissão de dados, proporcionando um feedback visual.

## Compilação e Uso
- Para compilar e carregar o código, utilize um conjunto de ferramentas compatível com AVR, como AVR-GCC, e um programador (ex: USBasp).
- Conecte o microcontrolador aos sensores analógicos e ao dispositivo de comunicação UART.
- Após programar o microcontrolador, os dados começarão a ser coletados e transmitidos automaticamente, podendo ser visualizados em um monitor serial.

## Notas
- Certifique-se de que a configuração do clock do microcontrolador esteja correta para a taxa de transmissão da UART.
- O código assume que os dados recebidos do ADC estão dentro dos limites esperados; ajustes podem ser necessários dependendo do sensor utilizado.
- O LED deve estar corretamente conectado ao pino definido para indicar a transmissão de dados.
