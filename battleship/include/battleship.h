/**
 * @file battleship.h
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Core engine structure definitions and business rule validation
 * functions for Battleship.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdbool.h>

#define EMPTY '\0'       // Empty cell placeholder.
#define WATER_LABEL '~'  // Character representing water misses.

#define SHIPS_QTY 5  // Total number of deployable ships.

#define ARSENAL_SIZE 4           // Dimensions of the arsenal array (number of projectile types).
#define PROJECTILE_LABEL_SIZE 4  // Maximum length of the projectile label string.
#define DAMAGE_MAX_SIZE 9        // Maximum size of the structural damage spread footprint.
#define BOARD_SIZE 10            // Size of the square board matrix grid.
#define PLAYER_NAME_SIZE 11      // Maximum length of the player name string.

/**
 * @brief Cartesian coordinate system structure (x, y) mapping 2D matrix
 * indices. x defines the horizontal axis (column index) and y defines the vertical axis
 * (row index).
 *
 */
typedef struct Coord {
    int x; /**< Column index within the matrix grid. */
    int y; /**< Row index within the matrix grid. */
} Coord;

/**
 * @brief Data structure representing an individual naval ship vessel.
 *
 */
typedef struct Ship {
    int length;             /**< Total length / remaining hit-points of the ship. */
    bool is_sunk;           /**< Flag identifying if the vessel has been completely destroyed. */
    bool has_been_recorded; /**< Flag ensuring the score increment for this ship was processed. */
    char label;             /**< Visual character designation representing the ship type. */
} Ship;

/**
 * @brief Data structure representing an offensive attack weapon projectile.
 *
 */
typedef struct Projectile {
    int count;                         /**< Current remaining ammunition for this weapon type. */
    int damage_size;                   /**< Total size of the impacted grid area. */
    char label[PROJECTILE_LABEL_SIZE]; /**< String label identifier for the weapon. */
    Coord damage[DAMAGE_MAX_SIZE];     /**< Relative offset coordinates defining the blast spread pattern. */
} Projectile;

/**
 * @brief Data structure storing profile data and loadouts for the active
 * player.
 *
 */
typedef struct Player {
    int combat_load;                  /**< Cumulative count of all available ammo remaining across the arsenal. */
    int score;                        /**< Total count of successfully destroyed enemy ships. */
    bool wins;                        /**< Victory evaluation status flag. */
    char name[PLAYER_NAME_SIZE];      /**< Player name character array. */
    Projectile arsenal[ARSENAL_SIZE]; /**< Available projectile weapon selection array. */
} Player;

/**
 * @brief Master tracking state structure capturing the active game context.
 *
 */
typedef struct GameState {
    bool running;                               /**< Flag indicating if the match cycle is active. */
    char control_board[BOARD_SIZE][BOARD_SIZE]; /**< Background control matrix storing hidden solution states. */
    char draw_board[BOARD_SIZE][BOARD_SIZE];    /**< Foreground matrix rendering visible data to the screen. */
    Ship ships[SHIPS_QTY];                      /**< Collection tracking the deployed fleet units. */
    Player player;                              /**< Embedded active player instance data. */
} GameState;

/**
 * @brief Validates whether a given target coordinate falls within legitimate
 * grid boundaries.
 *
 * Guards against unsafe out-of-bounds matrix lookups that lead to application
 * segmentation faults.
 *
 * @param coord Coord structure enclosing target x and y positions.
 * @retval true If the coordinate safely rests inside grid boundaries.
 * @retval false If the coordinate drops outside grid boundaries.
 */
bool validate_coord(Coord coord);

/**
 * @brief Validates if the selected projectile index exists and contains
 * remaining ammunition.
 *
 * Prevents index-out-of-bounds errors on arsenal arrays and stops fires on dry
 * ammunition supplies.
 *
 * @param arsenal Pointer to the player's weapon projectile collection.
 * @param i Index position of the requested ammunition type.
 * @retval true If the selection index is valid and ammunition count is above
 * zero.
 * @retval false If the selection index is invalid or ammunition supplies are
 * depleted.
 */
bool validate_projectile(Projectile* arsenal, int i);

/**
 * @brief Evaluates if the player has successfully sunk all enemy vessels.
 *
 * Each fully destroyed ship yields one point. Victory triggers when total
 * points match total fleet size.
 *
 * @param player Pointer to the active player tracking state.
 * @retval true If the player's score matches total fleet count
 * (victory achieved).
 * @retval false If outstanding enemy ships remain active.
 */
bool did_sink_all_ships(Player* player);

/**
 * @brief Evaluates if all ammunition reserves in the user's arsenal are fully
 * spent.
 *
 * Firing weapons decrements localized asset counters. Depleting the total
 * combat pool without achieving victory triggers defeat.
 *
 * @param player Pointer to the active player tracking state.
 * @retval true If total weapon reserves across the entire arsenal hit zero.
 * @retval false If operational ammunition remains available for use.
 */
bool did_run_out_ammunition(Player* player);

/**
 * @brief Shuts down the match cycle by flipping the running state flag from
 * true to false.
 *
 * @param state Pointer to the active game state container.
 */
void finish_game(GameState* state);

/**
 * @brief Orchestrates initial application start, flagging execution states and
 * populating game objects.
 *
 * Sets up primary game board configurations, seeds the tactical fleet
 * positions, and establishes the player loadouts.
 *
 * @param state Pointer to the allocated game state object.
 * @param player_name Source string containing the designated player name.
 */
void init_game_state(GameState* state, const char* player_name);

/**
 * @brief Re-evaluates fleet destruction statuses to safely update player
 * scoring.
 *
 * Scans ship status arrays to isolate recently sunk entries, updating user
 * metrics while guarding against double-counting.
 *
 * @param player Pointer to the player instance receiving score adjustments.
 * @param ships Pointer to the tracking array containing current fleet health
 * conditions.
 */
void update_player_score(Player* player, Ship* ships);

/**
 * @brief Unveils the tactical positions of all active and hidden naval assets.
 *
 * Maps hidden structural targets from control grids directly into display
 * matrices to conclude matches.
 *
 * @param state Pointer to the active game state tracking object.
 */
void open_all_draw_board(GameState* state);

/**
 * @brief Commits a win condition status update to the player instance profile.
 *
 * @param player Pointer to the target player entity.
 */
void set_player_wins(Player* player);

/**
 * @brief Applies the spatial pattern payload of an explosive projectile onto
 * target environments.
 *
 * Unrolls offset attack configurations across coordinates centered at target
 * points. Checks blast steps against underlying control layouts to damage
 * ships, process misses, and deduct weapon counts.
 *
 * @param state Pointer to the active game state container.
 * @param projectile_i Selection layout index mapping weapon payloads.
 * @param coord Absolute central grid target coordinate selected for deployment.
 * @retval true If the attack successfully compromises at least one target ship
 * position.
 * @retval false If the entire payload misses target ship placements (splash in
 * water).
 */
bool fire(GameState* state, int projectile_i, Coord coord);

#endif  // BATTLESHIP_H
