#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 104
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
    char name[CITY_NAME_SZ];
    char code[CODE_SZ];
    char state;
} Card;

typedef struct Attribute {
    short used;
    short lower;
    short winner;
    char label[30];
} Attribute;

void line(void) { printf("\n---\n\n"); }

void clean_terminal(void) { system(CMD_CLS); }

void pause(void) {
    printf("\nPressione qualquer tecla para continuar... ");
    getchar();
}

void register_cards(Card* cds, int size) {
    char buffer[BUFFER_SIZE];

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
        fgets(cds[i].name, sizeof(cds[i].name), stdin);
        cds[i].name[strcspn(cds[i].name, "\n")] = '\0';

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
    clean_terminal();

    for (int i = 0; i < size; i++) {
        if (i != 0) line();

        printf("Carta #%d ", i + 1);
        printf("| Est: %c ", cds[i].state);
        printf("| Cod: %s ", cds[i].code);
        printf("| SUPER POWER: " FMT_DEC " \n", cds[i].super_power);
        printf("Nome da cidade: %s \n", cds[i].name);
        printf("Populacao: %u hab. \n", cds[i].population);
        printf("Area: " FMT_DEC " km2 \n", cds[i].area);
        printf("PIB: R$ " FMT_DEC " bi \n", cds[i].gdp);
        printf("Pontos turisticos: %u \n", cds[i].attractions);
        printf("Densidade populacional: " FMT_DEC " hab/km2 \n", cds[i].ppt_dsty);
        printf("PIB per capita: R$ " FMT_DEC " \n", cds[i].gdp_pc);
    }
}

short compare(double val1, double val2, short lower) {
    if (val1 == val2) return -1;

    return (lower && val1 > val2) || val1 < val2;
}

void display_res(char* attr, char* winner, double v_winner, char* loser, double v_loser, short draw) {
    printf("\nResultado: %-18s | ", attr);
    if (!draw) {
        printf("Ganhador: %s [ ", winner);
        printf(FMT_DEC " ] | ", v_winner);
        printf("Perdedor: %s [ ", loser);
        printf(FMT_DEC " ] \n", v_loser);
    } else {
        printf("%s | ", winner);
        printf("%s | ", loser);
        printf("EMPATE [ " FMT_DEC " ] \n", v_winner);
    }
}

void duel(Card* cds) {
    Attribute attrs[7] = {
        {.label = "Populacao", .used = 0, .winner = 0, .lower = 0},
        {.label = "Area", .used = 0, .winner = 0, .lower = 0},
        {.label = "Densidade", .used = 0, .winner = 0, .lower = 1},
        {.label = "PIB", .used = 0, .winner = 0, .lower = 0},
        {.label = "PIB Per Capita", .used = 0, .winner = 0, .lower = 0},
        {.label = "Ponto Turisticos", .used = 0, .winner = 0, .lower = 0},
        {.label = "SUPER POWER", .used = 0, .winner = 0, .lower = 0},
    };
    short o = 0;
    double score_player_1 = .0;
    double score_player_2 = .0;
    char buffer[8];

    do {
        clean_terminal();

        for (short i = 0; i < 7; i++) {
            if (!attrs[i].used) printf("[ %d ] %s \n", (i + 1), attrs[i].label);
        }

        printf("[ 0 ] Resultado Final \n\n");
        printf("Escolha > ");
        fgets(buffer, sizeof(buffer), stdin);
        o = (short)strtol(buffer, NULL, 10) - 1;

        switch (o) {
            case -1:
                if (score_player_1 > score_player_2)
                    display_res("Final", cds[0].name, score_player_1, cds[1].name, score_player_2, 0);
                else if (score_player_2 > score_player_1)
                    display_res("Final", cds[1].name, score_player_2, cds[0].name, score_player_1, 0);
                else
                    display_res("Final", cds[0].name, score_player_1, NULL, 0.0, 1);
                break;

            case 0:  // population duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare((double)cds[0].population, (double)cds[1].population, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += (double)cds[0].population;
                    else if (attrs[o].winner)
                        score_player_2 += (double)cds[1].population;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].population, cds[1].name,
                                (double)cds[1].population, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, (double)cds[1].population, cds[0].name,
                                (double)cds[0].population, 0);
                else
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].population, NULL, 0.0, 1);
                break;

            case 1:  // area duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare((double)cds[0].area, (double)cds[1].area, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += (double)cds[0].area;
                    else if (attrs[o].winner)
                        score_player_2 += (double)cds[1].area;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].area, cds[1].name, (double)cds[1].area, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, (double)cds[1].area, cds[0].name, (double)cds[0].area, 0);
                else
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].area, NULL, 0.0, 1);
                break;

            case 2:  // density duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare((double)cds[0].ppt_dsty, (double)cds[1].ppt_dsty, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += 1 / (double)cds[0].ppt_dsty;
                    else if (attrs[o].winner)
                        score_player_2 += 1 / (double)cds[1].ppt_dsty;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].ppt_dsty, cds[1].name,
                                (double)cds[1].ppt_dsty, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, (double)cds[1].ppt_dsty, cds[0].name,
                                (double)cds[0].ppt_dsty, 0);
                else
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].ppt_dsty, NULL, 0.0, 1);
                break;

            case 3:  // gdp duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare(cds[0].gdp, cds[1].gdp, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += cds[0].gdp;
                    else if (attrs[o].winner)
                        score_player_2 += cds[1].gdp;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, cds[0].gdp, cds[1].name, cds[1].gdp, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, cds[1].gdp, cds[0].name, cds[0].gdp, 0);
                else
                    display_res(attrs[o].label, cds[0].name, cds[0].gdp, NULL, 0.0, 1);
                break;

            case 4:  // gdp per capita duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare(cds[0].gdp_pc, cds[1].gdp_pc, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += cds[0].gdp_pc;
                    else if (attrs[o].winner)
                        score_player_2 += cds[1].gdp_pc;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, cds[0].gdp_pc, cds[1].name, cds[1].gdp_pc, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, cds[1].gdp_pc, cds[0].name, cds[0].gdp_pc, 0);
                else
                    display_res(attrs[o].label, cds[0].name, cds[0].gdp_pc, NULL, 0.0, 1);
                break;

            case 5:  // attractions duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare((double)cds[0].attractions, (double)cds[1].attractions, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += (double)cds[0].attractions;
                    else if (attrs[o].winner)
                        score_player_2 += (double)cds[1].attractions;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].attractions, cds[1].name,
                                (double)cds[1].attractions, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, (double)cds[1].attractions, cds[0].name,
                                (double)cds[0].attractions, 0);
                else
                    display_res(attrs[o].label, cds[0].name, (double)cds[0].attractions, NULL, 0.0, 1);
                break;

            case 6:  // super_power duel
                if (!attrs[o].used) {
                    attrs[o].used = 1;
                    attrs[o].winner = compare(cds[0].super_power, cds[1].super_power, attrs[o].lower);

                    if (!attrs[o].winner)
                        score_player_1 += cds[0].super_power;
                    else if (attrs[o].winner)
                        score_player_2 += cds[1].super_power;
                }

                if (!attrs[o].winner)
                    display_res(attrs[o].label, cds[0].name, cds[0].super_power, cds[1].name, cds[1].super_power, 0);
                else if (attrs[o].winner)
                    display_res(attrs[o].label, cds[1].name, cds[1].super_power, cds[0].name, cds[0].super_power, 0);
                else
                    display_res(attrs[o].label, cds[0].name, cds[0].super_power, NULL, 0.0, 1);
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

        pause();
    } while (o >= 0);
}

void main_menu(void) {
    clean_terminal();
    printf("===== SUPER TRUNFO ===== \n\n");
    printf("[ 1 ] Cadastrar Cartas \n");
    printf("[ 2 ] Exibir Cartas \n");
    printf("[ 3 ] Duelar \n");
    printf("[ 0 ] Sair \n\n");
}

int main(void) {
    Card cds[CARDS_SZ];
    char buffer[BUFFER_SIZE];
    short opt = 0;

    main_menu();

    do {
        printf("Escolha > ");
        fgets(buffer, sizeof(buffer), stdin);
        opt = (short)strtoul(buffer, NULL, 10);

        switch (opt) {
            case 1:
                register_cards(cds, CARDS_SZ);

            case 2:
                display_cards(cds, CARDS_SZ);
                pause();
                main_menu();
                break;

            case 3:
                duel(cds);
                main_menu();
                break;

            case 0:
                printf("Saindo...");
                break;

            default:
                main_menu();
                printf("Opcao invalida! ");
                break;
        }

    } while (opt != 0);

    return 0;
}
