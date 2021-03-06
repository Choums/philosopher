/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:49:55 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/02 17:45:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*ft_lstnew(int pos, t_life *lf)
{
	t_philo *another;

	another = malloc(sizeof(*another));
	if (!another)
		return (NULL);
    another->count = 0;
    another->is_alive = 1;
	another->pos = pos;
	pthread_mutex_init(&(another->cur_fork), NULL);
	another->lf = lf;
	another->next = NULL;
	another->previous = NULL;
	return (another);
}

void	ft_lstclear(t_philo **lst, void (*del)(pthread_t, pthread_mutex_t))
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

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone(t_philo *lst, void (*del)(pthread_t, pthread_mutex_t))
{
	if (lst && del)
	{
		(*del)(lst->philo, lst->cur_fork);
		free(lst);
	}
}

/*
 *	free la fourchette et le philo
*/
void	del(pthread_t phil, pthread_mutex_t cur_fork)
{
	pthread_join(phil, NULL);
	pthread_mutex_destroy(&cur_fork);
}