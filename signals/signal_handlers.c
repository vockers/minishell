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

static void	signal_handler_init(void (*f)(int), int sig_type)
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

/// PARENT HANDLERS ///

static void	sigint_handler(int signum)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_handler(int signum)
{
}

void	signal_handler(void)
{
	signal_handler_init(&sigint_handler, SIGINT);
	signal_handler_init(&sigquit_handler, SIGQUIT);
}

/// CHILD HANDLERS ///

static void	sigint_handler_child(int signum)
{
}

static void	sigquit_handler_child(int signum)
{
}

void	signal_handler_child(void)
{
	signal_handler_init(&sigint_handler_child, SIGINT);
	signal_handler_init(&sigquit_handler_child, SIGQUIT);
}

/// HEREDOC SIGNAL HANDLERS ///

static void	sigint_heredoc(int signum)
{
	gl_sig = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static void	sigquit_heredoc(int signum)
{
}

void	signal_handler_heredoc(void)
{
	signal_handler_init(&sigint_heredoc, SIGINT);
	signal_handler_init(&sigquit_heredoc, SIGQUIT);
}
