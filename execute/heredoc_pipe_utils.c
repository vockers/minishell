#include "execute.h"

t_list	**add_fd(t_list **fds, char *file_name)
{
	t_list	*new;

	if (!file_name)
		return (NULL);
	new = ft_lstnew(file_name);
	if (!new)
	{
		unlink(file_name);
		free(file_name);
		ft_lstclear(fds, free);
		return (NULL);
	}
	ft_lstadd_back(fds, new);
	return (fds);
}

char	*create_file_name(int i)
{
	char	*name;
	char	*file_num;

	name = (char *)malloc(sizeof(char) * 14);
	if (!name)
		return (NULL);
	ft_strlcpy(name, "tmp_file_", 14);
	file_num = ft_itoa(i);
	if (!file_num)
	{
		free(name);
		return (NULL);
	}
	ft_strlcat(name, file_num, 14);
	free(file_num);
	return (name);
}

void	delete_files(t_list **hdoc_fd)
{
	t_list	*temp;

	temp = *hdoc_fd;
	while (temp)
	{
		unlink((char *)temp->content);
		temp = temp->next;
	}
}
