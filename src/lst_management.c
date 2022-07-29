/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:49:55 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/29 14:56:42 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*ft_lstnew(char *content)
{
	t_philo *another;

	another = malloc(sizeof(*another));
	if (!another)
		return (NULL);
    pthread_create(&another->philo, NULL, routine, arg);
    another->count = 0;
    another->is_alive = 1;
	return (another);
}

void	ft_lstclear(t_philo **lst, void (*del)(char *))
{
	t_philo	*tmp;

	if (*lst && del)
	{
		while ((*lst)->next)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(tmp, del);
		}
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
}

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*tmp;

	if (alst)
	{
		if (*alst)
		{
			tmp = ft_lstlast(*alst);
			tmp->next = new;
			new->previous = tmp;
		}
		else
			(*alst) = new;
	}
}