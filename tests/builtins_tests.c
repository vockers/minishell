#include "builtins.h"

#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char *args_1[] = { "hello", "world", NULL };
	builtin_echo(args_1);
	char *args_2[] = { "-n", NULL };
	builtin_echo(args_2);
	char *args_3[] = { NULL };
	builtin_echo(args_3);
	char *args_4[] = { "-n", "hello", "world", NULL };
	builtin_echo(args_4);
	char *args_5[] = { "test", NULL };
	builtin_echo(args_5);
	char *args_6[] = { NULL };
	builtin_echo(args_6);
	char *args_7[] = { "-n", "-n", NULL };
	builtin_echo(args_7);

	return (0);
}