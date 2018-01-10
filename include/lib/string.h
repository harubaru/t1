#ifndef LIB_STRING_H
#define LIB_STRING_H

char *itoa(int num, int base);
char *uitoa(unsigned int num, int base);
void *memset(void *dst, char val, int num);
void *memcpy(void *dst, void *src, unsigned int n);

#endif

