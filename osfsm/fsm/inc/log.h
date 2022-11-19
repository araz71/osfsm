#include <stdio.h>

#define mlog(...)	printf("%-20s:%04d : ", "FILE" , __LINE__);	\
			printf(__VA_ARGS__);	\
			printf("\r\n");
