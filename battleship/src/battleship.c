/**
 * @file battleship.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Core match simulation engine loop logic implementations for
 * Battleship.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */
#include "battleship.h"

#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"

#define AIC 'A'  // Aircraft Carrier identification tag label.
#define BSH 'B'  // Battleship identification tag label.
#define SUB 'S'  // Submarine identification tag label.
#define DES 'D'  // Destroyer identification tag label.
#define PAB 'P'  // Patrol Boat identification tag label.

#define AIC_LENGTH 5  // Section length footprint of Aircraft Carriers.
#define BSH_LENGTH 4  // Section length footprint of Battleships.
#define SUB_LENGTH 3  // Section length footprint of Submarines.
#define DES_LENGTH 3  // Section length footprint of Destroyers.
#define PAB_LENGTH 2  // Section length footprint of Patrol Boats.

#define GNF 0  // Array index representing Gunfire payload types.
#define BMB 1  // Array index representing Bomb payload types.
#define TPD 2  // Array index representing Torpedo payload types.
#define SMN 3  // Array index representing Sea Mine payload types.

#define GNF_DAMAGE_SIZE 1  // Impact coverage area sizing for Gunfire payloads.
#define BMB_DAMAGE_SIZE 5  // Impact coverage area sizing for Bomb payloads.
#define TPD_DAMAGE_SIZE 7  // Impact coverage area sizing for Torpedo payloads.
#define SMN_DAMAGE_SIZE 9  // Impact coverage area sizing for Sea Mine payloads.

#define GNF_COUNT 20  // Initial ammunition quantity for Gunfire weapon reserves.
#define BMB_COUNT 3   // Initial ammunition quantity for Bomb weapon reserves.
#define TPD_COUNT 4   // Initial ammunition quantity for Torpedo weapon reserves.
#define SMN_COUNT 3   // Initial ammunition quantity for Sea Mine weapon reserves.

#define DIRECTIONS_SIZE 4                           // Orientation options map size (4 primary cardinal direction steps).
#define MAX_PLAYER_NAME_LEN (PLAYER_NAME_SIZE - 1)  // Sanitized text boundary length for name tracking strings.

/**
 * @brief Internal helper structure isolating collision state feedback
 * evaluations.
 *
 */
typedef struct Collision {
    bool collided; /**< Flag indicating if an impact with a physical entity occurred. */
    char who;      /**< Captured character signature specifying what asset type was struck. */
} Collision;

/**
 * @brief Internal layout packaging utility parsing coordinate vectors and
 * linear paths.
 *
 * Condenses multidimensional traversal parameters to keep function calls and
 * interface inputs brief.
 *
 */
typedef struct Path {
    Coord source;     /**< Anchor coordinate base where navigation calculations start. */
    Coord direction;  /**< Step direction offset rules dictating step increments. */
    int displacement; /**< Magnitude scale defining total units moved away from sources. */
} Path;

/**
 * @brief Factory template layout schema tracking raw ship configuration
 * details.
 *
 */
typedef struct ShipPattern {
    int length; /**< Structural length specifications. */
    char label; /**< Designated identifier character label. */
} ShipPattern;

/**
 * @brief Factory template layout schema tracking weapon projectile
 * specification models.
 *
 */
typedef struct ProjectilePattern {
    int count;         /**< Initial allocation volume quotas. */
    int damage_size;   /**< Area coverage boundary counts. */
    const char* label; /**< Text label tag identifier string. */
    Coord* damage;     /**< Pointer tracking relative blast impact zone layouts. */
} ProjectilePattern;

/**
 * @brief Evaluates if explicit coordinates exist cleanly inside legal board
 * boundaries.
 *
 * @param coord Coordinate configuration evaluating bounds matching.
 * @retval true If coordinates reside safely within grid rows and columns.
 * @retval false If coordinates spill past the layout dimensions.
 */
bool is_inside_board(Coord coord) {
    return coord.x >= 0 && coord.x < BOARD_SIZE && coord.y >= 0 && coord.y < BOARD_SIZE;
}

/**
 * @brief Verifies if grid spaces are currently occupied or reside
 * out-of-bounds.
 *
 * @param coord Target location parameters validating vacancy.
 * @retval true If coordinates sit outside the map boundaries or contain active
 * objects.
 * @retval false If coordinates are valid and clear of content (EMPTY).
 */
bool is_filledout(char (*board)[BOARD_SIZE], Coord coord) {
    return !is_inside_board(coord) || board[coord.y][coord.x] != EMPTY;
}

/**
 * @brief Decrements localized weapon allocations and total inventory combat
 * loads.
 *
 * @param projectile_count Pointer tracking remaining individual inventory
 * counts.
 * @param player_combat_load Pointer tracking system total inventory combat load
 * metrics.
 */
void decrement_ammunition(int* projectile_count, int* player_combat_load) {
    *projectile_count -= 1;
    *player_combat_load -= 1;
}

/**
 * @brief Calculates linear position transformations by accumulating path steps
 * onto anchor coordinates.
 *
 * @param path Mapping context parameters calculating updates.
 * @return Coord Transformed coordinate destination location output.
 */
Coord increment_coord(Path path) {
    path.source.x += path.direction.x * path.displacement;
    path.source.y += path.direction.y * path.displacement;
    return path.source;
}

/**
 * @brief Generates valid random start positions ensuring entire ship lengths
 * fit onto grids.
 *
 * Validates orientation models and length metrics packed inside path instances.
 * Runs placement checks until it confirms the tail end of the vessel footprint
 * also rests within board borders.
 *
 * @param path Vector mapping contexts driving calculations.
 * @param length Total segment count metric for target deployment objects.
 * @return Coord Verified, completely valid starting location coordinates.
 */
Coord gen_start_coord(Path path, int length) {
    path.displacement = --length;

    while (true) {
        path.source.x = draw_random(BOARD_SIZE);
        path.source.y = draw_random(BOARD_SIZE);

        Coord last_coord = increment_coord(path);

        if (is_inside_board(last_coord)) break;
    }

    return path.source;
}

/**
 * @brief Scans continuous trajectory paths to verify if any blocking obstacles
 * exist.
 *
 * @param board Target map instance being evaluated.
 * @param path Direction and start tracking rules driving spatial navigation.
 * @param length Continuous segment check boundary length thresholds.
 * @retval true If any coordinate checkpoint along the trace trajectory is
 * already occupied.
 * @retval false If the path is perfectly clear and vacant throughout.
 */
bool is_anything(char (*board)[BOARD_SIZE], Path path, int length) {
    path.displacement = 1;

    while (length > 0) {
        if (is_filledout(board, path.source)) return true;

        path.source = increment_coord(path);
        length--;
    }

    return false;
}

/**
 * @brief Baks ship identification character signatures into continuous grid
 * blocks.
 *
 * Renders spatial footprints on matrices by setting values across path
 * configurations step-by-step up to overall vessel lengths.
 *
 * @param board Target deployment board matrix instances.
 * @param ship Fleet unit model being tracked onto environments.
 * @param path Vector tracking paths controlling layout deployment steps.
 */
void place_on_board(char (*board)[BOARD_SIZE], Ship* ship, Path path) {
    path.displacement = 1;

    for (int i = 0; i < ship->length; i++) {
        board[path.source.y][path.source.x] = ship->label;
        path.source = increment_coord(path);
    }
}

/**
 * @brief Initializes ship structures and commits deployment parameters onto
 * hidden answer maps.
 *
 * Assigns profile constants from patterns, sources valid spawn vectors via
 * random loops, and passes structural parameters over to map printing engines
 * once footprints clear verification checks.
 *
 * @param board Hidden answer tracker matrix layout configurations.
 * @param directions Reference list containing permissible deployment layout
 * offsets.
 * @param ship Target model tracking container instance receiving
 * configurations.
 * @param pattern Config template source structure mapping length parameters.
 */
void create_ship(char (*board)[BOARD_SIZE], Coord* directions, Ship* ship, ShipPattern pattern) {
    Path path = { 0 };

    ship->label = pattern.label;
    ship->length = pattern.length;
    ship->is_sunk = false;
    ship->has_been_recorded = false;

    while (true) {
        path.direction = directions[draw_random(DIRECTIONS_SIZE)];
        path.source = gen_start_coord(path, pattern.length);

        if (is_anything(board, path, pattern.length)) continue;

        break;
    }

    place_on_board(board, ship, path);
}

/**
 * @brief Configures weapon projectile objects using defined pattern blueprints.
 *
 * @param projectile Weapon model instance tracking ammunition data.
 * @param pattern Blueprint template configuration schema source.
 */
void create_projectile(Projectile* projectile, ProjectilePattern pattern) {
    int mem_size_damage = DAMAGE_MAX_SIZE * sizeof(Coord);

    projectile->count = pattern.count;
    projectile->damage_size = pattern.damage_size;
    strncpy(projectile->label, pattern.label, PROJECTILE_LABEL_SIZE);
    memcpy(projectile->damage, pattern.damage, mem_size_damage);
}

/**
 * @brief Seeds geometric splash damage layouts mapping coordinates relative to
 * centers.
 *
 * Populates coordinate vectors with coordinate offset structures mapping
 * geometric area footprints. First positions act as zero-point indicators
 * tracking initial direct impacts.
 *
 * - Gunfire: Precise point target payload damage tracking (1 cell impacted).
 *
 * - Bomb: Standard cross layout splash damage tracking footprints (5 cells
 * impacted).
 *
 * - Torpedo: Elongated horizontal winged cross damage tracking configurations
 * (7 cells impacted).
 *
 * - Sea Mine: Dense structural triangular footprint distribution tracking
 * matrix blocks (9 cells impacted).
 *
 * @param dest Output coordinates collection destination array container.
 * @param projectile_i Key selector index isolating weapon layout styles.
 */
void gen_damage(Coord* dest, int projectile_i) {
    switch (projectile_i) {
        case GNF: {
            Coord src[GNF_DAMAGE_SIZE] = {
                { .x = 0, .y = 0 },  // Central impact point.
            };

            memcpy(dest, src, sizeof(src));
            break;
        }

        case BMB: {
            Coord src[BMB_DAMAGE_SIZE] = {
                { .x = 0, .y = 0 },   // Central impact point.
                { .x = -1, .y = 0 },  // Left offset.
                { .x = 1, .y = 0 },   // Right offset.
                { .x = 0, .y = -1 },  // Top offset.
                { .x = 0, .y = 1 },   // Bottom offset.
            };

            memcpy(dest, src, sizeof(src));
            break;
        }

        case TPD: {
            Coord src[TPD_DAMAGE_SIZE] = {
                { .x = 0, .y = 0 },   // Central impact point.
                { .x = -1, .y = 0 },  // Left step 1.
                { .x = -2, .y = 0 },  // Left step 2.
                { .x = 1, .y = 0 },   // Right step 1.
                { .x = 2, .y = 0 },   // Right step 2.
                { .x = 0, .y = -1 },  // Top offset.
                { .x = 0, .y = 1 },   // Bottom offset.
            };

            memcpy(dest, src, sizeof(src));
            break;
        }

        case SMN: {
            Coord src[SMN_DAMAGE_SIZE] = {
                { .x = 0, .y = 0 },   // Central impact point.
                { .x = -1, .y = 0 },  // Middle layer left.
                { .x = 1, .y = 0 },   // Middle layer right.
                { .x = 0, .y = -1 },  // Apex top layer cell.
                { .x = -2, .y = 1 },  // Base layer far-left.
                { .x = -1, .y = 1 },  // Base layer mid-left.
                { .x = 0, .y = 1 },   // Base layer center.
                { .x = 1, .y = 1 },   // Base layer mid-right.
                { .x = 2, .y = 1 },   // Base layer far-right.
            };

            memcpy(dest, src, sizeof(src));
            break;
        }
    }
}

/**
 * @brief Assesses whether collisions with game entities occur at specific grid
 * checkpoints.
 *
 * @param board Reference tracking matrix verified for impacts.
 * @param target Targeted matrix grid checkpoint being evaluated.
 * @return Collision Populated helper results payload summary.
 */
Collision was_there_collision(char (*board)[BOARD_SIZE], Coord target) {
    char content = board[target.y][target.x];
    Collision result = {
        .collided = false,
        .who = WATER_LABEL,
    };

    if (content == EMPTY) return result;

    result.collided = true;
    result.who = content;
    return result;
}

/**
 * @brief Deducts operational hit-points from targeted fleet units when
 * successfully struck.
 *
 * Decrements length/health metrics matching ship types. If operational capacity
 * hits 0, flips the sunk flag status to track total destruction events.
 *
 * @param ships Active collection monitoring total fleet status records.
 * @param target_label Unique identifying signature tracking impacted entities.
 */
void update_ships_state(Ship* ships, char target_label) {
    for (int i = 0; i < SHIPS_QTY; i++) {
        if (target_label == ships[i].label) {
            ships[i].length--;

            if (!ships[i].length) {
                ships[i].is_sunk = true;
            }

            break;
        }
    }
}

/**
 * @brief Writes a specific character into a designated cell on the board
 * matrix.
 *
 * Directly updates the grid element at the specified coordinate intersection.
 *
 * @param board Pointer to the 2D array board grid matrix.
 * @param coord Coord structure specifying the target row (y) and column (x)
 * indices.
 * @param content Character value to be assigned to the target board cell.
 */
void fill_in(char (*board)[BOARD_SIZE], Coord coord, char content) {
    board[coord.y][coord.x] = content;
}

/**
 * @brief Builds the default status configuration loadouts mapping onto profile
 * containers.
 *
 * @param player Target data instance container initialized.
 * @param name Source string text assigning name fields.
 */
void init_player_state(Player* player, const char* name) {
    const int counts[ARSENAL_SIZE] = {
        GNF_COUNT,
        BMB_COUNT,
        TPD_COUNT,
        SMN_COUNT,
    };
    const int damage_sizes[ARSENAL_SIZE] = {
        GNF_DAMAGE_SIZE,
        BMB_DAMAGE_SIZE,
        TPD_DAMAGE_SIZE,
        SMN_DAMAGE_SIZE,
    };
    const char* labels[ARSENAL_SIZE] = {
        "GNF",
        "BMB",
        "TPD",
        "SMN",
    };

    strncpy(player->name, name, MAX_PLAYER_NAME_LEN);
    player->name[MAX_PLAYER_NAME_LEN] = EMPTY;
    player->score = 0;
    player->wins = false;
    player->combat_load = sum(counts, ARSENAL_SIZE);

    for (int i = 0; i < ARSENAL_SIZE; i++) {
        Coord damage[DAMAGE_MAX_SIZE] = { 0 };
        gen_damage(damage, i);

        ProjectilePattern pattern = {
            .count = counts[i],
            .label = labels[i],
            .damage = damage,
            .damage_size = damage_sizes[i],
        };
        create_projectile(&player->arsenal[i], pattern);
    }
}

/**
 * @brief Clears active boards by initializing all cells to clean EMPTY
 * defaults.
 *
 * @param state Master engine status context tracked.
 */
void init_boards(GameState* state) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Coord coord = {
                .x = x,
                .y = y,
            };

            fill_in(state->control_board, coord, EMPTY);
            fill_in(state->draw_board, coord, EMPTY);
        }
    }
}

/**
 * @brief Spawns the match fleet using configured blueprints onto background
 * control sheets.
 *
 * @param state Master engine status context tracked.
 */
void init_ships(GameState* state) {
    Coord directions[DIRECTIONS_SIZE] = {
        { .x = 0, .y = 1 },
        { .x = 1, .y = 0 },
        { .x = 1, .y = 1 },
        { .x = -1, .y = 1 },
    };
    const int lengths[SHIPS_QTY] = {
        AIC_LENGTH, BSH_LENGTH, SUB_LENGTH, DES_LENGTH, PAB_LENGTH,
    };
    const char labels[SHIPS_QTY] = {
        AIC, BSH, SUB, DES, PAB,
    };

    for (int i = 0; i < SHIPS_QTY; i++) {
        ShipPattern pattern = {
            .label = labels[i],
            .length = lengths[i],
        };

        create_ship(state->control_board, directions, &state->ships[i], pattern);
    }
}

bool validate_projectile(Projectile* arsenal, int i) {
    return i >= 0 && i < ARSENAL_SIZE && arsenal[i].count;
}

bool validate_coord(Coord coord) {
    return is_inside_board(coord);
}

bool did_sink_all_ships(Player* player) {
    return player->score == SHIPS_QTY;
}

bool did_run_out_ammunition(Player* player) {
    return !player->combat_load;
}

void finish_game(GameState* state) {
    state->running = false;
}

void init_game_state(GameState* state, const char* player_name) {
    state->running = true;
    set_random_seed_based_time();
    init_boards(state);
    init_ships(state);
    init_player_state(&state->player, player_name);
}

void update_player_score(Player* player, Ship* ships) {
    for (int i = 0; i < SHIPS_QTY; i++) {
        if (!ships[i].has_been_recorded && ships[i].is_sunk) {
            ships[i].has_been_recorded = true;
            player->score++;
        }
    }
}

void open_all_draw_board(GameState* state) {
    char (*control_board)[BOARD_SIZE] = state->control_board;
    char (*draw_board)[BOARD_SIZE] = state->draw_board;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Coord coord = {
                .x = x,
                .y = y,
            };

            if (is_filledout(draw_board, coord)) continue;
            if (control_board[y][x] == EMPTY) continue;

            fill_in(draw_board, coord, control_board[y][x]);
        }
    }
}

void set_player_wins(Player* player) {
    player->wins = true;
}

bool fire(GameState* state, int projectile_i, Coord coord) {
    bool success = false;
    Projectile* projectile = &state->player.arsenal[projectile_i];
    Path path = {
        .source = coord,
        .displacement = 1,
    };

    for (int i = 0; i < projectile->damage_size; i++) {
        path.direction = projectile->damage[i];
        Coord target = increment_coord(path);

        if (is_filledout(state->draw_board, target)) continue;

        Collision result = was_there_collision(state->control_board, target);

        if (result.collided) {
            update_ships_state(state->ships, result.who);
            success = true;
        }

        fill_in(state->draw_board, target, result.who);
    }

    decrement_ammunition(&projectile->count, &state->player.combat_load);
    return success;
}
