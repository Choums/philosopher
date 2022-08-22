/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/22 17:56:13 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 *	Routine des philos: manger, dormir, penser
 *	La routine dure tant qu'un philo n'est pas mort ou si n_eat a été init
 *	-------------------------------------
 *	Le philo se met à manger s'il peut mutex sa fourchette et la suivante
 *	Chaque action doit se faire lock au préalable puis unlock pour
 *		éviter tout écrasement
 *	L'affichage doit aussi faire part d'un lock
 *	L'affichage vérifie si tout le monde est en vie avant d'afficher
 *	printf("pos %d\n", tmp->pos);
 *	printf("---------\n");
 *	printf("cur: %p\nnex: %p\n", &tmp->cur_fork, &(*tmp->next_fork));
 *	printf("---------\n");
*/
void	*routine(void *phil)
{
	t_philo	*tmp;

	tmp = (t_philo *)phil;
	pthread_mutex_lock(&(tmp->lf->starter));
	pthread_mutex_unlock(&(tmp->lf->starter));
	pthread_mutex_lock(&(tmp->check));
	tmp->start = get_time();
	pthread_mutex_unlock(&(tmp->check));
	while (check_end(tmp))
	{
		if (!take_fork(tmp))
			return (NULL);
		if (!eating(tmp))
			return (NULL);
		if (!display(tmp, "is sleeping"))
			return (NULL);
		usleep(tmp->lf->t_sleep * 1000);
		if (!display(tmp, "is thinking"))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	check_end(t_philo *tmp)
{
	pthread_mutex_lock(&(tmp->check));
	if (tmp->count == tmp->lf->n_eat)
	{
		pthread_mutex_unlock(&(tmp->check));
		return (0);
	}
	pthread_mutex_unlock(&(tmp->check));
	return (1);
}

int	display(t_philo *tmp, char *status)
{
	pthread_mutex_lock(&(tmp->check));
	pthread_mutex_lock(&(tmp->lf->dis));
	if (ft_strlen(status) != 4 && tmp->lf->died)
	{
		pthread_mutex_unlock(&(tmp->check));
		pthread_mutex_unlock(&(tmp->lf->dis));
		return (0);
	}
	printf("%d %d %s\n", get_time() - tmp->start, tmp->pos, status);
	pthread_mutex_unlock(&(tmp->lf->dis));
	pthread_mutex_unlock(&(tmp->check));
	return (1);
}

/*
	1->	number of philos.
	2->	time to die => (lim < gettime - start_count)
	3->	time to eat
	4->	time to sleep
	5->	number of times each philos. has to eat (optional)
	------------------------------------------------------
*/
int	main(int ac, char **av)
{
	t_life	lf;
	int		i;
	t_philo	*tmp;

	if (!check_arg(ac, av, &lf))
		return (ft_err("Invalid Arguments"));
	init_threads(&lf);
	tmp = lf.philos;
	i = 0;
	while (++i < lf.num)
	{
		pthread_join(tmp->philo, NULL);
		tmp = tmp->next;
	}
	pthread_join(tmp->philo, NULL);
	ft_lstclear(&(lf.philos), &lf, del);
	return (0);
}
