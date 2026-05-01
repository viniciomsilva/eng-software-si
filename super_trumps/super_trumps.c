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
    float area = .0;
    float pib = .0;
    float pib_per_capita = .0;
    float population_density = .0;
    int population = 0;
    int tourist_attractions = 0;

    for (int i = 1; i <= 2; i++) {
        printf("\nCADASTRO DA CIDADE #%d\n", i);
        printf(LINE);

        printf("ESTADO...............: ");
        fgets(buffer, sizeof(buffer), stdin);
        state = buffer[0];

        printf("CODIGO...............: ");
        fgets(code, sizeof(code), stdin);
        code[strcspn(code, "\n")] = '\0';

        printf("NOME.................: ");
        fgets(city_name, sizeof(city_name), stdin);
        city_name[strcspn(city_name, "\n")] = '\0';

        printf("POPULACAO............: ");
        fgets(buffer, sizeof(buffer), stdin);
        population = atoi(buffer);

        printf("AREA.................: ");
        fgets(buffer, sizeof(buffer), stdin);
        area = atof(buffer);

        printf("PIB..................: ");
        fgets(buffer, sizeof(buffer), stdin);
        pib = atof(buffer);

        printf("N0. PONTOS TURISTICOS: ");
        fgets(buffer, sizeof(buffer), stdin);
        tourist_attractions = atoi(buffer);

        population_density = (float)population / area;
        pib_per_capita = (float)pib * 1e9f / population;

        printf("\nCIDADE #%d CADASTRADA COM SUCESSO\n", i);
        printf(LINE);
        printf("ESTADO................: %c \n", state);
        printf("CODIGO................: %s \n", code);
        printf("NOME..................: %s \n", city_name);
        printf("POPULACAO.............: %d hab\n", population);
        printf("AREA..................: %.2fkm2\n", area);
        printf("PIB...................: R$ %.2f Bi\n", pib);
        printf("N0. PONTOS TURISTICOS.: %d \n", tourist_attractions);
        printf("DENSIDADE POPULACIONAL: %.2f hab/km2\n", population_density);
        printf("PIB PER CAPITA........: R$ %.2f", pib_per_capita);

        printf("PRESSIONE ENTER PARA CONTINUAR...");
        getchar();
    }

    return 0;
}
