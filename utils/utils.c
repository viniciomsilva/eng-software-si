#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear(void) {
    system(CLS_CMD);
}

void clean_buffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

long read_long(int buffer_size, const char* err) {
    long value;
    char buffer[buffer_size];
    char* endptr;

    while (1) {
        read_str(buffer, sizeof(buffer));

        if (!buffer) continue;

        buffer[strcspn(buffer, "\n")] = '\0';
        value = strtol(buffer, &endptr, 10);

        if (buffer[0] == '\0' || *endptr != '\0') {
            printf(err);
            continue;
        }

        break;
    }

    return value;
}

void read_str(char* buffer, int buffer_size) {
    fgets(buffer, buffer_size, stdin);

    if (strchr(buffer, '\n') == NULL) {
        clean_buffer();
    } else {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void transform_to_upper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int sum(const int *numbers, int size) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        result += numbers[i];
    }

    return result;
}
