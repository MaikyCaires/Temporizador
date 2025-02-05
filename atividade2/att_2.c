#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos
const uint LED_VERMELHO = 13;
const uint LED_AMARELO = 12;
const uint LED_VERDE = 11;
const uint BOTAO = 5;

// Controle do estado do semáforo
int etapa = 0;
bool ciclo_ativo = false; // Evita múltiplas ativações pelo botão

// Configura os LEDs e o botão
void configurar_hardware() {
    int leds[] = {LED_VERMELHO, LED_AMARELO, LED_VERDE};
    for (int i = 0; i < 3; i++) {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
        gpio_put(leds[i], false);
    }
    
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO); // Pull-up interno ativado
}

// Alterna os LEDs a cada 3 segundos
int64_t alternar_leds(alarm_id_t id, void *user_data) {
    // Desliga todos os LEDs antes de ativar o próximo
    gpio_put(LED_VERMELHO, false);
    gpio_put(LED_AMARELO, false);
    gpio_put(LED_VERDE, false);

    // Controla o ciclo do semáforo
    switch (etapa) {
        case 0:
            gpio_put(LED_AMARELO, true);
            printf("Atenção! Sinal amarelo.\n");
            break;
        case 1:
            gpio_put(LED_VERDE, true);
            printf("Sinal verde! Pode passar.\n");
            break;
        case 2:
            printf("Ciclo encerrado. Aguarde novo acionamento.\n");
            ciclo_ativo = false; // Permite um novo acionamento do botão
            return 0; // Termina o ciclo
    }

    etapa++; // Passa para o próximo estágio
    return 3000000; // 3 segundos em microssegundos
}

int main() {
    stdio_init_all();
    configurar_hardware();

    while (true) {
        // Verifica se o botão foi pressionado e se o semáforo está inativo
        if (gpio_get(BOTAO) == 0 && !ciclo_ativo) {
            sleep_ms(50); // Debounce para evitar leituras erradas

            if (gpio_get(BOTAO) == 0) { // Confirma a pressão do botão
                gpio_put(LED_VERMELHO, true);
                printf("Pare! Sinal vermelho.\n");

                ciclo_ativo = true;
                etapa = 0; // Reinicia o ciclo

                add_alarm_in_ms(3000, alternar_leds, NULL, false);
            }
        }

        sleep_ms(10); // Reduz o uso da CPU
    }
    return 0;
}
