Simulador de Semáforo com Raspberry Pi Pico

Este projeto simula o funcionamento de um semáforo utilizando um Raspberry Pi Pico e LEDs. O semáforo é ativado ao pressionar um botão e segue a sequência: vermelho → amarelo → verde.

Requisitos

Placa: Raspberry Pi Pico

Componentes:

3 LEDs (Vermelho, Amarelo, Verde)

3 resistores (330Ω)

1 Botão

Jumpers e protoboard

Software:

Raspberry Pi Pico SDK

Compilador C para ARM (como GCC ARM)

Visual Studio Code (opcional)

Wokwi para simulação (opcional)

Esquema de Conexão

Componente

Pino no Pico

LED Vermelho

GP13

LED Amarelo

GP12

LED Verde

GP11

Botão

GP5

Instalação e Uso

1. Configurar o Ambiente

Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no seu ambiente de desenvolvimento.

2. Compilar o Código

Para compilar o programa, use os seguintes comandos no terminal:

mkdir build
cd build
cmake ..
make

Isso gerará um arquivo .uf2, que pode ser carregado no Raspberry Pi Pico.

3. Executar no Pico

Conecte o Raspberry Pi Pico ao PC segurando o botão BOOTSEL.

Arraste o arquivo programa.uf2 para a unidade que aparecerá no seu explorador de arquivos.

O código será executado automaticamente.

4. Funcionamento

O semáforo inicia desligado.

Ao pressionar o botão, ele segue a sequência:

Vermelho - "Pare!"

Amarelo - "Atenção!"

Verde - "Pode passar!"

O ciclo reinicia após a conclusão.

Simulação no Wokwi

Se quiser testar no Wokwi:

Acesse Wokwi

Escolha Raspberry Pi Pico

Copie e cole o código no editor

Conecte os LEDs e botão conforme o esquema

Clique em "Play" para rodar a simulação