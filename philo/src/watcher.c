/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:05:57 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/25 11:20:01 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*check_stop(t_life *lf, t_philo *tmp)
{
	if (tmp->count == tmp->lf->n_eat)
	{
		lf->stop--;
		if (lf->stop == 0)
		{
			pthread_mutex_unlock(&(tmp->check));
			return (NULL);
		}
		if (!tmp->next)
		{
			lf->stop = lf->num;
			pthread_mutex_unlock(&(tmp->check));
			return (lf->philos);
		}
		else
		{
			pthread_mutex_unlock(&(tmp->check));
			return (tmp->next);
		}
	}
	else
		return (next_tmp(lf, tmp));
}

t_philo	*next_tmp(t_life *lf, t_philo *tmp)
{
	if (!tmp->next)
	{
		lf->stop = lf->num;
		pthread_mutex_unlock(&(tmp->check));
		return (lf->philos);
	}
	else
	{
		pthread_mutex_unlock(&(tmp->check));
		return (tmp->next);
	}
}
