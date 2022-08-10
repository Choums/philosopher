/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:55:38 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/10 20:26:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 *	Init. les threads(philosophes) et debute la simu
 *  Créer la list de philo
 *  Initialise la fourchette de chaque philo
 *  
*/
int	init_threads(t_life *lf)
{
	int		i;
	t_philo	*tmp;

	i = 1;
	if (lf->num > 0)
		lf->philos = ft_lstnew(i++, lf);
	while (i <= lf->num)
		ft_lstadd_back(&(lf->philos), ft_lstnew(i++, lf));
	init_forks(lf);
	tmp = lf->philos;
	while (tmp)
	{
		pthread_create(&(tmp->philo), NULL, &routine, tmp);
		tmp = tmp->next;
	}
	return (watcher(lf));
}

void	init_forks(t_life *lf)
{
	t_philo	*tmp;
	t_philo	*fst;

	tmp = lf->philos;
	fst = lf->philos;
	while (tmp->pos < tmp->lf->num)
	{
		tmp->next_fork = &tmp->next->cur_fork;
		tmp = tmp->next;
	}
	if (&tmp->cur_fork != &(fst->cur_fork))
		tmp->next_fork = &fst->cur_fork;
	else
		tmp->next_fork = NULL;
}

int	watcher(t_life *lf)
{
	t_philo	*tmp;

	tmp = lf->philos;
	while (1)
	{
		pthread_mutex_lock(&(tmp->check));
		// if (tmp->count == tmp->lf->n_eat)
		// 	return (pthread_mutex_unlock(&(tmp->check)));
		if (!tmp->ate && !tmp->eating && get_time() - tmp->start >= lf->t_die)
		{
			lf->died = 1;
			display(tmp, get_time() - tmp->start, "died");
			pthread_mutex_unlock(&(tmp->check));
			return (0);
		}
		else if (tmp->ate && !tmp->eating && get_time() - tmp->ate >= lf->t_die)
		{
			lf->died = 1;
			display(tmp, get_time() - tmp->start, "died");
			pthread_mutex_unlock(&(tmp->check));
			return (0);
		}
		pthread_mutex_unlock(&(tmp->check));
		if (!tmp->next)
			tmp = lf->philos;
		else
			tmp = tmp->next;
	}
	return (1);
}

/*
 *	free la fourchette et le philo
*/
void	del(pthread_t phil, pthread_mutex_t cur_fork, pthread_mutex_t check)
{
	pthread_join(phil, NULL);
	pthread_mutex_destroy(&cur_fork);
	pthread_mutex_destroy(&check);
}