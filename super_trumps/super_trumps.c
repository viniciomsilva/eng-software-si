#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SZ 104
#define CITY_NAME_SZ 52
#define CODE_SZ 6
#define CARDS_SZ 2
#define FMT_DEC "%.2f"

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

void line(void) { printf("\n---\n\n"); }

void clean_terminal(void) { system(CMD_CLS); }

void pause(void) {
    printf("\nPressione qualquer tecla para continuar... ");
    getchar();
}

void register_cards(Card* cds, int size) {
    char buffer[BUFFER_SZ];

    for (int i = 0; i < size; i++) {
        clean_terminal();
        printf("Cadastrar cidade #%d \n", i + 1);

        do {
            printf("Estado (A-H): ");
            fgets(buffer, sizeof(buffer), stdin);
            cds[i].state = toupper(buffer[0]);
        } while (cds[i].state < 'A' || cds[i].state > 'H');

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

        float ppt_dsty = (area > .0f) ? (float)population / area : (float)population;
        float ppt_dsty_inverse = (ppt_dsty > .0f) ? 1.0f / ppt_dsty : .0f;
        double gdp_pc = (population > 0) ? gdp * 1e9 / (double)population : gdp;

        cds[i].ppt_dsty = ppt_dsty;
        cds[i].gdp_pc = gdp_pc;
        cds[i].super_power = (           // super power =
            cds[i].gdp +                 // gdp +
            cds[i].gdp_pc +              // dgp per capita +
            cds[i].area +                // area +
            ppt_dsty_inverse +           // population density inverse +
            (double)cds[i].population +  // population
            (double)cds[i].attractions   // tourist attractions
        );

        printf("\nCidade cadastrada com sucesso");
        pause();
    }
}

void display_cards(Card* cds, int size) {
    for (int i = 0; i < size; i++) {
        if (i != 0) line();

        printf("Carta #%d ", i + 1);
        printf("| Est: %c ", cds[i].state);
        printf("| Cod: %s ", cds[i].code);
        printf("| SUPER POWER: " FMT_DEC " \n", cds[i].super_power);
        printf("Nome da cidade: %s \n", cds[i].city_name);
        printf("Populacao: %u hab. \n", cds[i].population);
        printf("Area: " FMT_DEC " km2 \n", cds[i].area);
        printf("PIB: R$ " FMT_DEC " bi \n", cds[i].gdp);
        printf("Pontos turisticos: %u \n", cds[i].attractions);
        printf("Densidade populacional: " FMT_DEC " hab/km2 \n", cds[i].ppt_dsty);
        printf("PIB per capita: R$ " FMT_DEC " \n", cds[i].gdp_pc);
    }
}

void duel(const char* attr, char* name1, double val1, char* name2, double val2, short lower) {
    printf(">>> Atributo: %-24s ", attr);

    if (val1 == val2) {
        printf("| EMPATE | Valor " FMT_DEC "\n", val1);
        return;
    }

    short winner = (lower && val1 > val2) || val1 < val2;

    printf("| Vencedor: %-24s ", (!winner) ? name1 : name2);  // !0 == gamer #1 wins
    printf("| Valor: " FMT_DEC "\n", (!winner) ? val1 : val2);
}

int main(void) {
    Card cds[CARDS_SZ];

    // register cards
    register_cards(cds, CARDS_SZ);

    // display cards
    clean_terminal();
    display_cards(cds, CARDS_SZ);

    // card duel
    printf("\nPronto para comecar o duelo?");
    pause();
    clean_terminal();

    short i = 0;
    short j = 1;

    // population duel
    duel("Populacao", cds[i].city_name, (double)cds[i].population, cds[j].city_name, (double)cds[j].population, 0);
    // area duel
    duel("Area", cds[i].city_name, cds[i].area, cds[j].city_name, cds[j].area, 0);
    // population density duel
    duel("Densidade Populacional", cds[i].city_name, cds[i].ppt_dsty, cds[j].city_name, cds[j].ppt_dsty, 1);
    // gdp duel
    duel("PIB", cds[i].city_name, cds[i].gdp, cds[j].city_name, cds[j].gdp, 0);
    // gpd per capita duel
    duel("PIB Per Capita", cds[i].city_name, cds[i].gdp_pc, cds[j].city_name, cds[j].gdp_pc, 0);
    // tourist attractions duel
    duel("Pontos Turisticos", cds[i].city_name, (double)cds[i].attractions, cds[j].city_name,
         (double)cds[j].attractions, 0);
    // super power duel
    duel("SUPER POWER", cds[i].city_name, cds[i].super_power, cds[j].city_name, cds[j].super_power, 0);

    return 0;
}
