#include "builtins.h"

#include <stdlib.h>

int	main(int argc, char *argv[])
{
	char *args_1[] = { "echo", "hello", "world", NULL };
	builtin_echo(args_1);
	char *args_2[] = { "echo", "-n", NULL };
	builtin_echo(args_2);
	char *args_3[] = { "echo", NULL };
	builtin_echo(args_3);
	char *args_4[] = { "echo", "-n", "no", "newline", NULL };
	builtin_echo(args_4);
	char *args_5[] = { "echo", "test", NULL };
	builtin_echo(args_5);
	char *args_6[] = { "echo", NULL };
	builtin_echo(args_6);
	char *args_7[] = { "echo", "-n", "-n", NULL };
	builtin_echo(args_7);
	char *args_8[] = { "echo", "two", "", "spaces", NULL };
	builtin_echo(args_8);

	return (0);
}