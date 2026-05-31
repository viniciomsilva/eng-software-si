#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
#define CLS_CMD "cls"
#else
#define CLS_CMD "clear"
#endif  // _WIN32

void clear(void);
void clean_buffer(void);
void read_str(char* buffer, int buffer_size);
void transform_to_upper(char* str);

#endif  // UTILS_H
