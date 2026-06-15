/**
 * @file utils.c
 * @author Vinicio Monteiro (viniciomsilva@outlook.com.br)
 * @brief Implementation of the utils component.
 * @version 0.1
 *
 * @copyright Copyright (c) 2026 Vinicio Monteiro
 *
 */

#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def CLS_CMD
 * @brief Defines the console clear command based on the OS.
 * - Windows (_WIN32) uses "cls"
 * - Linux/macOS uses "clear"
 *
 */
#ifdef _WIN32
#define CLS_CMD "cls"
#else
#define CLS_CMD "clear"
#endif  // _WIN32

/**
 * @brief Clears remaining characters in the standard input buffer, consuming each
 * character until '\\n' and EOF is encountered.
 *
 */
void clean_buffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void clear(void) {
    system(CLS_CMD);
}

void read_str(char* buffer, int buffer_size) {
    // fgets reads from the standard input (stdin) up to the predefined size
    // (buffer_size). It will store in the buffer only the amount specified by
    // buffer_size, or until it encounters a '\n'.
    fgets(buffer, buffer_size, stdin);

    // strchr searches for '\n' in the buffer.
    // If not found, it means fgets left remaining characters in stdin.
    if (strchr(buffer, '\n') == NULL) {
        clean_buffer();
    } else {
        // Locate where "\n" is in the string and replace it with '\0'.
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

long read_long(int buffer_size, const char* err) {
    long value;
    char buffer[buffer_size];
    char* endptr;

    while (1) {
        read_str(buffer, sizeof(buffer));

        // If the input is empty, continues the loop to read again.
        if (!buffer) continue;

        buffer[strcspn(buffer, "\n")] = '\0';

        // Convert the input string value to a base-10 number.
        // strtol will traverse the buffer searching for a number.
        // It traverses until the end of the buffer or utils it finds '\0'.
        // The pointer to the final analyzed character is stored in endptr.
        value = strtol(buffer, &endptr, 10);

        // If the first character of the buffer is '\0' or
        // if the last evaluated character is not '\0',
        // it means there are non-numeric characters in the input.
        if (buffer[0] == '\0' || *endptr != '\0') {
            printf(err);
            continue;
        }

        break;
    }

    return value;
}

void transform_to_upper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int sum(const int* numbers, int size) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        result += numbers[i];
    }

    return result;
}
