#include "signals.h"

static void	sigint_handler(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(void)
{
	signal_handler_init(&sigint_handler, SIGINT);
	signal_handler_init(&ft_empty, SIGQUIT);
}

void	signal_handler_child(void)
{
	signal_handler_init(&ft_empty, SIGINT);
	signal_handler_init(&ft_empty, SIGQUIT);
}

static void	sigint_heredoc(int signum)
{
	gl_sig = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	signal_handler_heredoc(void)
{
	signal_handler_init(&sigint_heredoc, SIGINT);
	signal_handler_init(&ft_empty, SIGQUIT);
}
