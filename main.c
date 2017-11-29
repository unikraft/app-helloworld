#include <stdio.h>

/* Import user configuration: */
#include <uk/config.h>

int main(int argc, char *argv[])
{
	printf("Hello world!\n");

#if APPHELLOWORLD_PRINTARGS
	int i;

	printf("Arguments: ");
	for (i=0; i<argc; ++i)
		printf(" \"%s\"", argv[i]);
	printf("\n");
#endif
}
