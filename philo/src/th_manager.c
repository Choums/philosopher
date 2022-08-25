/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:55:38 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/25 09:29:45 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_list(t_life *lf)
{
	int	i;

	i = 1;
	if (lf->num > 0)
		lf->philos = ft_lstnew(i++, lf);
	while (i <= lf->num)
		ft_lstadd_back(&(lf->philos), ft_lstnew(i++, lf));
}

/*
 *	Init. les threads(philosophes) et debute la simu
 *  Créer la list de philo
 *  Initialise la fourchette de chaque philo
 *  
*/
int	init_threads(t_life *lf)
{
	t_philo	*tmp;

	create_list(lf);
	init_forks(lf);
	tmp = lf->philos;
	pthread_mutex_lock(&(lf->starter));
	while (tmp)
	{
		if ((tmp->pos % 2))
			pthread_create(&(tmp->philo), NULL, &routine, tmp);
		tmp = tmp->next;
	}
	tmp = lf->philos;
	while (tmp)
	{
		if (!(tmp->pos % 2))
			pthread_create(&(tmp->philo), NULL, &routine, tmp);
		tmp = tmp->next;
	}
	pthread_mutex_unlock(&(lf->starter));
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
		if (!tmp->eating && get_time() - tmp->ate >= lf->t_die)
		{
			pthread_mutex_lock(&(tmp->lf->death));
			lf->died = 1;
			pthread_mutex_unlock(&(tmp->lf->death));
			pthread_mutex_unlock(&(tmp->check));
			display(tmp, "died");
			return (0);
		}
		tmp = check_stop(lf, tmp);
		if (tmp == NULL)
			return (0);
	}
	return (1);
}

/*
 *	free la fourchette et le philo
*/
void	del(pthread_mutex_t cur_fork, pthread_mutex_t check)
{
	pthread_mutex_destroy(&cur_fork);
	pthread_mutex_destroy(&check);
}
