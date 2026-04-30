#include <stdio.h>
#include <string.h>

#define STR_MAX_LEN 50

void clean_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    int age = 0;
    float height = .0f;
    char name[STR_MAX_LEN] = "";

    printf("Digite seu nome: ");
    if (fgets(name, sizeof(name), stdin) != NULL) {
        name[strcspn(name, "\n")] = '\0';
    }

    printf("Digite sua idade: ");
    if (scanf("%d", &age) <= 0) {
        printf("Valor para idade deve ser numérico.\n");
        age = 1;
    }

    clean_buffer();

    printf("Digite sua altura: ");
    if (scanf("%f", &height) <= 0) {
        printf("Valor para altura deve ser numérico.\n");
        height = 1;
    }

    printf("\n----\n");
    printf("Prazer, %s!\n", name);
    printf("Já vi que você tem %d anos e mede %.2fm.\n", age, height);
    printf("Seja bem-vindo(a) à Linguagem C!\n\n");

    return 0;
}
