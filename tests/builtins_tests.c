#include "builtins/builtins.h"

#include <stdlib.h>

#include "libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;

	// char *args_1[] = { "echo", "hello", "world", NULL };
	// run_echo(args_1);
	// char *args_2[] = { "echo", "-n", NULL };
	// run_echo(args_2);
	// char *args_3[] = { "echo", NULL };
	// run_echo(args_3);
	// char *args_4[] = { "echo", "-n", "no", "newline", NULL };
	// run_echo(args_4);
	// char *args_5[] = { "echo", "test", NULL };
	// run_echo(args_5);
	// char *args_6[] = { "echo", NULL };
	// run_echo(args_6);
	// char *args_7[] = { "echo", "-n", "-n", NULL };
	// run_echo(args_7);
	// char *args_8[] = { "echo", "two", "", "spaces", NULL };
	// run_echo(args_8);

	// run_pwd();
	// char	**envp_test = {"hello=world", "zest=test", "ZSH_PATH=~/.zshrc", "PATH=/home/test", "a=b", NULL};
	env = env_init(envp);
	envp = env_to_strs(env);
	// run_export(&env, &envp, (char*[]){ "export", "hello=test", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "world=test", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "world=hoi", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "world", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "hello=", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "abczyx", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "hello world", NULL });
	// run_export(&env, &envp, (char*[]){ "export", "hello'world", NULL });
	// run_export(&env, &envp, (char*[]){ "export", NULL });

	// run_export(&envp, (char*[]){ "export", "=hello", NULL});
	// run_export(&envp, (char*[]){ "export", "1abc=hello", NULL});

	/* cd */
	printf("%d\n", run_cd((char*[]){ "cd", NULL }, &env, &envp));
	printf("%d\n", run_cd((char*[]){ "cd", "-", NULL }, &env, &envp));
	printf("%d\n", run_cd((char*[]){ "cd", "asdhasd", NULL }, &env, &envp));
	printf("%d\n", run_cd((char*[]){ "cd", "test", "asdasd", NULL }, &env, &envp));
	printf("%d\n", run_cd((char*[]){ "cd", "tests", NULL }, &env, &envp));
	printf("%d\n", run_cd((char*[]){ "cd", "/tmp", NULL }, &env, &envp));

	env_free(env);
	free(envp);

	return (0);
}