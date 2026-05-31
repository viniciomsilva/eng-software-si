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
