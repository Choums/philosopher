/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:05:57 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/22 16:30:56 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_stop(t_life *lf, t_philo *tmp)
{
	if (tmp->count == tmp->lf->n_eat)
	{
		lf->stop--;
		if (lf->stop == 0)
		{
			pthread_mutex_unlock(&(tmp->check));
			return (0);
		}
		if (!tmp->next)
		{
			lf->stop = lf->num;
			pthread_mutex_unlock(&(tmp->check));
			tmp = lf->philos;
		}
		else
		{
			pthread_mutex_unlock(&(tmp->check));
			tmp = tmp->next;
		}
	}
	else
		next_tmp(lf, tmp);
	return (1);
}

void	next_tmp(t_life *lf, t_philo *tmp)
{
	if (!tmp->next)
	{
		lf->stop = lf->num;
		pthread_mutex_unlock(&(tmp->check));
		tmp = lf->philos;
	}
	else
	{
		pthread_mutex_unlock(&(tmp->check));
		tmp = tmp->next;
	}
}
