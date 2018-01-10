#include <lib/string.h>

char *itoa(int num, int base)
{
	static char buf[32] = {0};
	int i = 30;

	for(; num && i; i--, num /= base)
		buf[i] = "0123456789ABCDEF"[num % base];
	
	return &buf[i+1];
}

char *uitoa(unsigned int num, int base)
{
	static char buf[32] = {0};
        unsigned int i = 30;

        for(; num && i; i--, num /= base)
                buf[i] = "0123456789ABCDEF"[num % base];

        return &buf[i+1];
}

void *memset(void *dst, char val, int num)
{
	char *tmp = dst;
	for (;num != 0; num--)
		*tmp++ = val;
	return dst;
}

void *memcpy(void *dst, void *src, unsigned int n)
{
	char *csrc = src, *cdst = dst;
	unsigned int i;

	for (i = 0; i < n; i++)
		cdst[i] = csrc[i];

	return cdst;
}
