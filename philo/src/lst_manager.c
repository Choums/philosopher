/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:49:55 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/22 16:44:29 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*ft_lstnew(int pos, t_life *lf)
{
	t_philo	*another;

	another = malloc(sizeof(*another));
	if (!another)
		return (NULL);
	another->count = 0;
	another->pos = pos;
	another->ate = 0;
	another->eating = 0;
	another->start = 0;
	pthread_mutex_init(&(another->cur_fork), NULL);
	pthread_mutex_init(&(another->check), NULL);
	another->lf = lf;
	another->next = NULL;
	another->previous = NULL;
	return (another);
}

void	ft_lstclear(t_philo **lst, t_life *lf,
				void (*del)(pthread_mutex_t, pthread_mutex_t))
{
	t_philo	*tmp;
	t_philo	*fst;

	if (*lst && del)
	{
		fst = *lst;
		if (lf->num > 1)
		{
			*lst = (*lst)->next;
			while (((*lst)->pos < (*lst)->lf->num))
			{
				tmp = *lst;
				*lst = (*lst)->next;
				ft_lstdelone(tmp, del);
			}
			ft_lstdelone(*lst, del);
			*lst = NULL;
		}
		ft_lstdelone(fst, del);
		pthread_mutex_destroy(&(lf->dis));
		pthread_mutex_destroy(&(lf->starter));
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

void	ft_lstdelone(t_philo *lst,
			void (*del)(pthread_mutex_t, pthread_mutex_t))
{
	if (lst && del)
	{
		(*del)(lst->cur_fork, lst->check);
		free(lst);
	}
}
