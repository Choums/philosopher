/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:04:31 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/22 16:30:33 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forkp(t_philo *tmp)
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
		return (pthread_mutex_unlock(&(*tmp->next_fork)));
	}
	usleep(tmp->lf->t_eat * 1000);
	pthread_mutex_lock(&(tmp->check));
	tmp->eating = 0;
	tmp->count++;
	pthread_mutex_unlock(&(tmp->check));
	pthread_mutex_unlock(&tmp->cur_fork);
	pthread_mutex_unlock(&(*tmp->next_fork));
	return (1);
}
