#include "builtins.h"

#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	char *args_1[] = { "echo", "hello", "world", NULL };
	run_echo(args_1);
	char *args_2[] = { "echo", "-n", NULL };
	run_echo(args_2);
	char *args_3[] = { "echo", NULL };
	run_echo(args_3);
	char *args_4[] = { "echo", "-n", "no", "newline", NULL };
	run_echo(args_4);
	char *args_5[] = { "echo", "test", NULL };
	run_echo(args_5);
	char *args_6[] = { "echo", NULL };
	run_echo(args_6);
	char *args_7[] = { "echo", "-n", "-n", NULL };
	run_echo(args_7);
	char *args_8[] = { "echo", "two", "", "spaces", NULL };
	run_echo(args_8);

	// run_pwd();
	// char	**envp_test = {"hello=world", "zest=test", "ZSH_PATH=~/.zshrc", "PATH=/home/test", "a=b", NULL};
	run_export(&envp, (char*[]){ "export", NULL });

	// run_export(&envp, (char*[]){ "export", "=hello", NULL});
	// run_export(&envp, (char*[]){ "export", "1abc=hello", NULL});

	return (0);
}