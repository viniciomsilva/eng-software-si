#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SZ 104
#define CITY_NAME_SZ 52
#define CODE_SZ 6
#define CARDS_SZ 2

#ifdef _WIN32
#define CMD_CLS "cls"
#else
#define CMD_CLS "clear"
#endif

typedef struct {
    double gdp;
    double gdp_pc;  // gdp per capita
    double super_power;
    float area;
    float ppt_dsty;  // population density
    unsigned int population;
    unsigned int tourist_attractions;
    char city_name[CITY_NAME_SZ];
    char code[CODE_SZ];
    char state;
} Card;

void clean(void) { system(CMD_CLS); }

void line(void) { printf("\n---\n\n"); }

void pause(void) {
    printf("\nPressione qualquer tecla para continuar... ");
    getchar();
}

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
        unsigned int population = (unsigned int)strtoul(buffer, NULL, 10);
        cds[i].population = population;

        printf("Area (km2): ");
        fgets(buffer, sizeof(buffer), stdin);
        float area = atof(buffer);
        cds[i].area = area;

        printf("PIB (bilhoes): R$ ");
        fgets(buffer, sizeof(buffer), stdin);
        float gdp = atof(buffer);
        cds[i].gdp = gdp;

        printf("No. de pontos turisticos: ");
        fgets(buffer, sizeof(buffer), stdin);
        cds[i].tourist_attractions = (unsigned int)strtoul(buffer, NULL, 10);

        float ppt_dsty = (area > .0f) ? (float)population / area : population;
        float ppt_dsty_inverse = (ppt_dsty > .0f) ? 1.0f / ppt_dsty : .0f;
        double gdp_pc = (population > 0) ? gdp * 1e9 / population : gdp;

        cds[i].ppt_dsty = ppt_dsty;
        cds[i].gdp_pc = gdp_pc;
        cds[i].super_power = (cds[i].gdp + cds[i].gdp_pc + cds[i].area + ppt_dsty_inverse +
                              (double)cds[i].population + (double)cds[i].tourist_attractions);

        printf("\nCidade cadastrada com sucesso");
        pause();
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
        printf("PIB: R$ %.2fbi \n", cds[i].gdp);
        printf("Pontos turisticos: %u \n", cds[i].tourist_attractions);
        printf("Densidade populacional: %.2f hab/km2 \n", cds[i].ppt_dsty);
        printf("PIB per capita: R$ %.2f \n", cds[i].gdp_pc);
        printf("SUPER POWER: %.2f \n", cds[i].super_power);
    }

    printf("\nPronto para comecar o duelo?");
    pause();

    // card duel
    short i = 0;
    short j = 1;
    short w = -1;

    clean();

    // population comparison
    if (cds[i].population > cds[j].population) {
        w = i;
    } else if (cds[j].population > cds[i].population) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Em populacao: houve empate! \n");
    } else {
        printf("Ganhadora em populacao: %s ", cds[w].city_name);
        printf("com %u hab. \n", cds[w].population);
    }

    line();

    // area comparison
    if (cds[i].area > cds[j].area) {
        w = i;
    } else if (cds[j].area > cds[i].area) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Em area: houve empate! \n");
    } else {
        printf("Ganhadora em area: %s ", cds[w].city_name);
        printf("com %.2fkm2. \n", cds[w].area);
    }

    line();

    // population density comparison
    if (cds[i].ppt_dsty < cds[j].ppt_dsty) {
        w = i;
    } else if (cds[j].ppt_dsty < cds[i].ppt_dsty) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Em densidade populacional: houve empate! \n");
    } else {
        printf("Ganhadora em densidade populacional: %s ", cds[w].city_name);
        printf("com %.2f hab/km2. \n", cds[w].ppt_dsty);
    }

    line();

    // gdp comparison
    if (cds[i].gdp > cds[j].gdp) {
        w = i;
    } else if (cds[j].gdp > cds[i].gdp) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Em PIB: houve empate! \n");
    } else {
        printf("Ganhadora em PIB: %s ", cds[w].city_name);
        printf("com R$ %.2fbi. \n", cds[w].gdp);
    }

    line();

    // gdp per capital comparison
    if (cds[i].gdp_pc > cds[j].gdp_pc) {
        w = i;
    } else if (cds[j].gdp_pc > cds[i].gdp_pc) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Em PIB per capita: houve empate! \n");
    } else {
        printf("Ganhadora em PIB per capita: %s ", cds[w].city_name);
        printf("com R$ %.2f /hab. \n", cds[w].gdp_pc);
    }

    line();

    // gdp per capital comparison
    if (cds[i].tourist_attractions > cds[j].tourist_attractions) {
        w = i;
    } else if (cds[j].tourist_attractions > cds[i].tourist_attractions) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Em pontos turisticos: houve empate! \n");
    } else {
        printf("Ganhadora em pontos turisticos: %s ", cds[w].city_name);
        printf("com %u atracoes. \n", cds[w].tourist_attractions);
    }

    line();

    // super power comparison
    if (cds[i].super_power > cds[j].super_power) {
        w = i;
    } else if (cds[j].super_power > cds[i].super_power) {
        w = j;
    } else {
        w = -1;
    }

    if (w < 0) {
        printf("Resultado final: empate de SUPER POWERS! \n");
    } else {
        printf("Ganhadora: %s ", cds[w].city_name);
        printf("com %.2f de SUPER POWER!!! \n", cds[w].super_power);
    }

    return 0;
}
