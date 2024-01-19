#include "signals.h"

void	suppress_output(void)
{
	struct termios	new_settings;

	if (tcgetattr(0, &new_settings))
		perror("tcsetattr");
	new_settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &new_settings))
		perror("tcsetattr");
}

void	signal_handler_init(void (*f)(int), int sig_type)
{
	struct sigaction	sa;

	sa.sa_handler = f;
	sa.sa_flags = SA_RESTART;
	if (sigaction(sig_type, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	ft_empty(int signum)
{
}
