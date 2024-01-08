#include "signals.h"

void    suppress_output(void)
{
    struct termios    new_settings;

    if (tcgetattr(0, &new_settings))
        perror("tcsetattr");
    new_settings.c_lflag &= ~ECHOCTL;
    if (tcsetattr(0, 0, &new_settings))
        perror("tcsetattr");
}

void	ctrl_c_handler(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_init()
{
	struct sigaction	sa;

	suppress_output();
	sa.sa_handler = &ctrl_c_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
