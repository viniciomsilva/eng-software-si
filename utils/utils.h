/**
 * @file utils.h
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Definitions of utility functions not related to business rules.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Clears the system console.
 *
 */
void clear(void);

/**
 * @brief Draws a random pseudo-random integer index cleanly below designated
 * target bounds.
 *
 * @param limit Non-inclusive top bounds index cutoff limit.
 * @return int Sourced random index spanning from 0 to (limit - 1).
 */
int draw_random(int limit);

/**
 * @brief Set the random seed based time object.
 *
 */
void set_random_seed_based_time();

/**
 * @brief Reads standard input while preventing buffer overflow.
 *
 * @param buffer Pointer to where the value will be stored.
 * @param buffer_size Size of the buffer.
 *
 * @note Safer than scanf. It handles remaining characters and properly stores
 * inputs with spaces.
 *
 */
void read_str(char* buffer, int buffer_size);

/**
 * @brief Reads only numbers.
 *
 * @param buffer_size Size of the buffer.
 * @param err Custom error message for non-numeric inputs.
 * @return long A valid long integer entered by the user.
 */
long read_long(int buffer_size, const char* err);

/**
 * @brief Converts a string to uppercase.
 *
 * @param str Pointer to where the string will be stored.
 */
void transform_to_upper(char* str);

/**
 * @brief Sums all elements of an integer array.
 *
 * @param numbers Pointer to the integer array.
 * @param size Array size (number of elements).
 * @return int The sum of all elements.
 */
int sum(const int* numbers, int size);

#endif  // UTILS_H
