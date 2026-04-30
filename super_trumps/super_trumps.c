#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SZ 101
#define CITY_NAME_SZ 51
#define CODE_SZ 5
#define LINE "--------------------------------------------------\n"

int main(void) {
    char state = '\0';
    char buffer[BUFFER_SZ] = "";
    char code[CODE_SZ] = "";
    char city_name[CITY_NAME_SZ] = "";
    float area = .0f;
    float pib = .0f;
    int population = 0;
    int tourist_attractions = 0;

    for (int i = 1; i <= 2; i++) {
        printf("\nCADASTRO DA CIDADE #%d\n", i);
        printf(LINE);

        printf("ESTADO...............: ");
        fgets(buffer, sizeof(buffer), stdin);
        state = buffer[0];

        printf("CÓDIGO...............: ");
        fgets(code, sizeof(code), stdin);
        code[strcspn(code, "\n")] = '\0';

        printf("NOME.................: ");
        fgets(city_name, sizeof(city_name), stdin);
        city_name[strcspn(city_name, "\n")] = '\0';

        printf("POPULAÇÃO............: ");
        fgets(buffer, sizeof(buffer), stdin);
        population = atoi(buffer);

        printf("ÁREA.................: ");
        fgets(buffer, sizeof(buffer), stdin);
        area = atof(buffer);

        printf("PIB..................: ");
        fgets(buffer, sizeof(buffer), stdin);
        pib = atof(buffer);

        printf("N0. PONTOS TURÍSTICOS: ");
        fgets(buffer, sizeof(buffer), stdin);
        tourist_attractions = atoi(buffer);

        // display informations
        printf("\nCIDADE #%d CADASTRADA COM SUCESSO\n", i);
        printf(LINE);
        printf("ESTADO...............: %c \n", state);
        printf("CÓDIGO...............: %s \n", code);
        printf("NOME.................: %s \n", city_name);
        printf("POPULAÇÃO............: %d HABITANTES\n", population);
        printf("ÁREA.................: %.2fKM²\n", area);
        printf("PIB..................: R$%.2fBI\n", pib);
        printf("N0. PONTOS TURÍSTICOS: %d \n", tourist_attractions);

        getchar();
    }

    return 0;
}
