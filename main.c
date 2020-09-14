#include <stdio.h>
#include <uk/essentials.h>

/* Import user configuration: */
#include <uk/config.h>

#if CONFIG_APPHELLOWORLD_SPINNER
#include <time.h>
#include <errno.h>

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

static void millisleep(unsigned int millisec)
{
	struct timespec ts;
	int ret;

	ts.tv_sec = millisec / 1000;
	ts.tv_nsec = (millisec % 1000) * 1000000;
	do
		ret = nanosleep(&ts, &ts);
	while (ret && errno == EINTR);
}
#endif /* CONFIG_APPHELLOWORLD_SPINNER */

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
#endif /* CONFIG_APPHELLOWORLD_PRINTARGS */

#if CONFIG_APPHELLOWORLD_SPINNER
	i = 0;
	printf("\n");
	while (1) {
		i %= ARRAY_SIZE(spinner);
		printf("\r%s", spinner[i++]);
		millisleep(1000);
	}
#endif /* CONFIG_APPHELLOWORLD_SPINNER */
}
