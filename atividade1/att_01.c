#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define VERMELHO 13
#define AMARELO 12
#define VERDE 11

int cor_atual = 0; // Estado atual do semáforo

// Configura os pinos dos LEDs
void configurar_leds() {
    int pinos[] = {VERMELHO, AMARELO, VERDE};
    for (int i = 0; i < 3; i++) {
        gpio_init(pinos[i]);
        gpio_set_dir(pinos[i], GPIO_OUT);
        gpio_put(pinos[i], false);
    }
    gpio_put(VERMELHO, true); // Começa no vermelho
}

// Função para alternar o semáforo
bool alternar_semaforo(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de ativar o próximo
    gpio_put(VERMELHO, false);
    gpio_put(AMARELO, false);
    gpio_put(VERDE, false);

    // Alterna a cor do semáforo
    switch (cor_atual) {
        case 0:
            gpio_put(AMARELO, true);
            printf("Cuidado! Sinal amarelo.\n");
            break;
        case 1:
            gpio_put(VERDE, true);
            printf("Sinal verde! Pode seguir.\n");
            break;
        case 2:
            gpio_put(VERMELHO, true);
            printf("Pare! Sinal vermelho.\n");
            break;
    }

    // Passa para a próxima cor
    cor_atual = (cor_atual + 1) % 3;
    return true;
}

int main() {
    stdio_init_all();
    configurar_leds();

    // Inicia o temporizador para trocar o sinal a cada 3 segundos
    struct repeating_timer temporizador;
    add_repeating_timer_ms(3000, alternar_semaforo, NULL, &temporizador);

    // Loop principal exibindo mensagens a cada segundo
    while (true) {
        printf("Tempo passando...\n");
        sleep_ms(1000);
    }

    return 0;
}
