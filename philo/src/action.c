/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:04:31 by chaidel           #+#    #+#             */
/*   Updated: 2022/09/13 13:52:26 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_fork(t_philo *tmp)
{
	if (tmp->pos % 2)
	{
		if (&(*tmp->next_fork))
		{
			pthread_mutex_lock(&(*tmp->next_fork));
			if (!display(tmp, "has taken a fork"))
			{
				pthread_mutex_unlock(&(*tmp->next_fork));
				return (0);
			}
		}
		else
			return (0);
		pthread_mutex_lock(&tmp->cur_fork);
		if (!display(tmp, "has taken a fork"))
		{
			pthread_mutex_unlock(&tmp->cur_fork);
			pthread_mutex_unlock(&(*tmp->next_fork));
			return (0);
		}
	}
	else
		return (take_forkup(tmp));
	return (1);
}

int	take_forkup(t_philo *tmp)
{
	pthread_mutex_lock(&tmp->cur_fork);
	if (!display(tmp, "has taken a fork"))
	{
		pthread_mutex_unlock(&tmp->cur_fork);
		return (0);
	}
	if (&(*tmp->next_fork))
	{
		pthread_mutex_lock(&(*tmp->next_fork));
		if (!display(tmp, "has taken a fork"))
		{
			pthread_mutex_unlock(&tmp->cur_fork);
			return (0);
		}
	}
	else
	{
		pthread_mutex_unlock(&tmp->cur_fork);
		return (0);
	}
	return (1);
}

int	eating(t_philo *tmp)
{
	pthread_mutex_lock(&(tmp->check));
	tmp->eating = 1;
	tmp->ate = get_time();
	pthread_mutex_unlock(&(tmp->check));
	if (!display(tmp, "is eating"))
	{
		pthread_mutex_unlock(&tmp->cur_fork);
		pthread_mutex_unlock(&(*tmp->next_fork));
		return (0);
	}
	sleeper(tmp, tmp->lf->t_eat);
	pthread_mutex_lock(&(tmp->check));
	tmp->eating = 0;
	tmp->count++;
	pthread_mutex_unlock(&(tmp->check));
	pthread_mutex_unlock(&tmp->cur_fork);
	pthread_mutex_unlock(&(*tmp->next_fork));
	return (1);
}

/*
 *	Fait dormir ou manger le philo pendant le temps donné
 *	Le prog doit pouvoir couper pendant l'action d'un philo
*/
void	sleeper(t_philo *tmp, int time)
{
	int	start;

	start = get_time();
	pthread_mutex_lock(&(tmp->lf->dis));
	while (tmp->lf->died == 0)
	{
		pthread_mutex_unlock(&(tmp->lf->dis));
		if (get_time() - start >= time)
			return ;
		usleep(100);
		pthread_mutex_lock(&(tmp->lf->dis));
	}
	if (tmp->lf->died == 1)
		pthread_mutex_unlock(&(tmp->lf->dis));
}
