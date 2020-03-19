#include <stdio.h>
#include <unistd.h>
#include <uk/essentials.h>

/* Import user configuration: */
#include <uk/config.h>

#if CONFIG_APPHELLOWORLD_SPINNER
static const char *spinner[] = {
	">))'>        ",
	" >))'>       ",
	"  >))'>      ",
	"   >))'>     ",
	"    >))'o    ",
	"     >))'>°  ",
	"     <'((< ° ",
	"    <'((<   '",
	"   <'((<     ",
	"  <'((<      ",
	" <'((<       ",
	"<'((<        ",
};
#endif

int main(int argc, char *argv[])
{
#if CONFIG_APPHELLOWORLD_PRINTARGS || CONFIG_APPHELLOWORLD_SPINNER
	int i;
#endif
	printf("Hello world!\n");

#if CONFIG_APPHELLOWORLD_PRINTARGS
	printf("Arguments: ");
	for (i=0; i<argc; ++i)
		printf(" \"%s\"", argv[i]);
	printf("\n");
#endif

#if CONFIG_APPHELLOWORLD_SPINNER
	i = 0;
	printf("\n");
	while (1) {
		i %= ARRAY_SIZE(spinner);
		printf("\r%s", spinner[i++]);
		sleep(1);
	}
#endif
}
