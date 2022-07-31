/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:49:55 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/31 17:47:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*ft_lstnew(void)
{
	t_philo *another;

	another = malloc(sizeof(*another));
	if (!another)
		return (NULL);
    pthread_create(&another->philo, NULL, &routine, NULL);
    another->count = 0;
    another->is_alive = 1;
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
	
}