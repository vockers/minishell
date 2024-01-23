#include "builtins/builtins.h"

#include <stdlib.h>

#include "libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;

	env_init(&env, envp);

	/* echo */
	// run_echo((char *[]){ "echo", "hello", "world", NULL });
	// run_echo((char *[]){ "echo", "-n", NULL });
	// run_echo((char *[]){ "echo", NULL });
	// run_echo((char *[]){ "echo", "-n", "no", "newline", NULL });
	// run_echo((char *[]){ "echo", "test", NULL });
	// run_echo((char *[]){ "echo", NULL });
	// run_echo((char *[]){ "echo", "-n", "-n", NULL });
	// run_echo((char *[]){ "echo", "two", "", "spaces", NULL });

	/* export */
	// char	**envp_test = {"hello=world", "zest=test", "ZSH_PATH=~/.zshrc", "PATH=/home/test", "a=b", NULL};
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
	run_cd((char*[]){ "cd", NULL }, &env);
	run_pwd();
	run_cd((char*[]){ "cd", "-", NULL }, &env);
	run_pwd();
	run_cd((char*[]){ "cd", "asdhasd", NULL }, &env);
	run_cd((char*[]){ "cd", "test", "asdasd", NULL }, &env);
	run_cd((char*[]){ "cd", "tests", NULL }, &env);
	run_pwd();
	run_cd((char*[]){ "cd", "..", NULL }, &env);
	run_pwd();
	run_cd((char*[]){ "cd", "../../..", NULL }, &env);
	run_pwd();
	run_cd((char*[]){ "cd", "/tmp", NULL }, &env);
	run_pwd();
	run_unset((char*[]){ "unset", "HOME" }, &env);
	run_cd((char*[]){ "cd", NULL }, &env);
	run_pwd();

	env_free(env.head);
	free(env.strs);

	return (0);
}