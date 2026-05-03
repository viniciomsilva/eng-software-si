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

typedef struct Card {
    double gdp;
    double gdp_pc;  // gdp per capita
    double super_power;
    float area;
    float ppt_dsty;  // population density
    unsigned int population;
    unsigned int attractions;  // tourist attractions
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

void duel(const char* attr, char* name1, double val1, char* name2, double val2, short lower) {
    short winner;

    if (val1 == val2) {
        printf("Em %s: houve empate! \n", attr);
        return;
    }

    if (!lower)
        winner = (val1 > val2) ? 0 : 1;
    else
        winner = (val1 < val2) ? 0 : 1;

    printf("Ganhadora em %s, %s ", attr, (!winner) ? name1 : name2);  // !0 == gamer #1 wins
    printf("com %.2f. \n", (!winner) ? val1 : val2);
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
        cds[i].attractions = (unsigned int)strtoul(buffer, NULL, 10);

        float ppt_dsty = (area > .0f) ? (float)population / area : population;
        float ppt_dsty_inverse = (ppt_dsty > .0f) ? 1.0f / ppt_dsty : .0f;
        double gdp_pc = (population > 0) ? gdp * 1e9 / population : gdp;

        cds[i].ppt_dsty = ppt_dsty;
        cds[i].gdp_pc = gdp_pc;
        cds[i].super_power = (   // super power =
            cds[i].gdp +         // gdp +
            cds[i].gdp_pc +      // dgp per capita +
            cds[i].area +        // area +
            ppt_dsty_inverse +   // population density inverse +
            cds[i].population +  // population
            cds[i].attractions   // tourist attractions
        );

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
        printf("Pontos turisticos: %u \n", cds[i].attractions);
        printf("Densidade populacional: %.2f hab/km2 \n", cds[i].ppt_dsty);
        printf("PIB per capita: R$ %.2f \n", cds[i].gdp_pc);
        printf("SUPER POWER: %.2f \n", cds[i].super_power);
    }

    printf("\nPronto para comecar o duelo?");
    pause();

    // card duel
    short i = 0;
    short j = 1;

    clean();
    // population duel
    duel("Populacao", cds[i].city_name, cds[i].population, cds[j].city_name, cds[j].population, 0);
    // area duel
    duel("Area", cds[i].city_name, cds[i].area, cds[j].city_name, cds[j].area, 0);
    // population density duel
    duel("Densidade Populacional", cds[i].city_name, cds[i].ppt_dsty, cds[j].city_name, cds[j].ppt_dsty, 1);
    // gdp duel
    duel("PIB", cds[i].city_name, cds[i].gdp, cds[j].city_name, cds[j].gdp, 0);
    // gpd per capita duel
    duel("PIB Per Capita", cds[i].city_name, cds[i].gdp_pc, cds[j].city_name, cds[j].gdp_pc, 0);
    // tourist attractions duel
    duel("Pontos Turisticos", cds[i].city_name, cds[i].attractions, cds[j].city_name, cds[j].attractions, 0);
    // super power duel
    duel("SUPER POWER", cds[i].city_name, cds[i].super_power, cds[j].city_name, cds[j].super_power, 0);

    return 0;
}
