#include <stdio.h>

#ifdef DEBUG
#define mlog(...)	printf("%-30s (%04d) : ", __func__ , __LINE__);	\
			printf(__VA_ARGS__);	\
			printf("\r\n");
#else
#define mlog(...)
#endif
