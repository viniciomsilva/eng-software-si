#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SZ 104
#define CITY_NAME_SZ 52
#define CODE_SZ 6
#define CARDS_SZ 2

typedef struct {
    double gpd;
    double gpd_pc;  // pib per capita
    float area;
    float ppt_dsty;  // population density
    unsigned int population;
    unsigned int tourist_attractions;
    char city_name[CITY_NAME_SZ];
    char code[CODE_SZ];
    char state;
} Card;

void clean(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void line(void) { printf("\n---\n\n"); }

int main(void) {
    Card cds[CARDS_SZ];
    char buffer[BUFFER_SZ];

    // input cards
    for (int i = 0; i < CARDS_SZ; i++) {
        clean();
        printf("Cadastrar cidade #%d \n", i + 1);

        printf("Estado (A-H): ");  // TODO: validate input
        fgets(buffer, sizeof(buffer), stdin);
        cds[i].state = buffer[0];

        printf("Codigo (Ex.: A01): ");
        fgets(cds[i].code, sizeof(cds[i].code), stdin);
        cds[i].code[strcspn(cds[i].code, "\n")] = '\0';  // remove '\n'

        printf("Nome da cidade: ");
        fgets(cds[i].city_name, sizeof(cds[i].city_name), stdin);
        cds[i].city_name[strcspn(cds[i].city_name, "\n")] = '\0';

        printf("Populacao: ");
        fgets(buffer, sizeof(buffer), stdin);
        cds[i].population = (unsigned int)strtoul(buffer, NULL, 10);

        printf("Area (km2): ");
        fgets(buffer, sizeof(buffer), stdin);
        cds[i].area = atof(buffer);

        printf("PIB (bilhoes): R$ ");
        fgets(buffer, sizeof(buffer), stdin);
        cds[i].gpd = atof(buffer);

        printf("No. de pontos turisticos: ");
        fgets(buffer, sizeof(buffer), stdin);
        cds[i].tourist_attractions = (unsigned int)strtoul(buffer, NULL, 10);

        cds[i].ppt_dsty = (float)cds[i].population / cds[i].area;
        cds[i].gpd_pc = cds[i].gpd * 1e9 / (double)cds[i].population;

        printf("\nCidade cadastrada com sucesso \n");
        printf("Pressione qualquer tecla para continuar...");
        getchar();
    }

    // display cards
    clean();

    for (int i = 0; i < CARDS_SZ; i++) {
        if (i != 0) line();

        printf("Carta #%d ", i + 1);
        printf("| Est: %c ", cds[i].state);
        printf("| Cod: %s \n", cds[i].code);
        printf("Nome da cidade: %s \n", cds[i].city_name);
        printf("Populacao: %u hab. \n", cds[i].population);
        printf("Area: %.2fkm2 \n", cds[i].area);
        printf("PIB: R$ %.2fbi \n", cds[i].gpd);
        printf("Pontos turisticos: %u \n", cds[i].tourist_attractions);
        printf("Densidade populacional: %.2f hab/km2 \n", cds[i].ppt_dsty);
        printf("PIB per capita: R$ %.2f \n", cds[i].gpd_pc);
    }

    return 0;
}
