#pragma once



float atof(char *);
double strtod(const char *string, char **endptr);
long int strtol(const char *str, char **endptr, int base);
void *malloc(size_t);
//void memcpy(void *, void *, unsigned int);
void free(void *);
#define RAND_MAX 0x7fffffff


#define __disable_irq()
#define __set_MSP(x)
#define __enable_irq()
