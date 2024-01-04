#include "execute.h"
#include "../libft/libft.h"

t_list	*here_doc_handler(char *delimiter)
{
	char	*line;
	t_list	*here_doc_input;
	t_list	*new;

	if (!delimiter)
	{
		printf("minishell: parse error near `\\n'\n");
		return (NULL);
	}
	here_doc_input = NULL;
	line = readline("heredoc> ");
	while (ft_strcmp(line, delimiter))
	{
		new = ft_lstnew(line);
		if (!new)
		{
			ft_lstclear(&here_doc_input, free);
			return (NULL);
		}
		ft_lstadd_back(&here_doc_input, ft_lstnew(line));
		line = readline("heredoc> ");
	}
	return (here_doc_input);
}
