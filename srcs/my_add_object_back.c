#include "../includes/rtmini.h"

int	my_add_back(t_list **list, t_list *new)
{
	t_list	*tmp;

	if (!list || !new)
		return (1);
	if (*list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*list = new;
	return (0);
}
