#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
#define CLS_CMD "cls"
#else
#define CLS_CMD "clear"
#endif  // _WIN32

void clear(void);
void clean_buffer(void);
long read_long(int buffer_size, const char* err);
void read_str(char* buffer, int buffer_size);
void transform_to_upper(char* str);

int sum(const int *numbers, int size);

#endif  // UTILS_H
