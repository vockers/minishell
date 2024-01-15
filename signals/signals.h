#ifndef SIGNALS_H

# define SIGNALS_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/ioctl.h>

extern int gl_sig;

void	signal_handler();
void	signal_handler_child();
void	signal_handler_heredoc();
void	suppress_output(void);

#endif