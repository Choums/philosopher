/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/09 19:23:23 by chaidel          ###   ########.fr       */
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
*/
void	*routine(void *phil)
{
	t_philo	*tmp;

	tmp = (t_philo *)phil;
	// printf("pos %d\n", tmp->pos);
	// printf("---------\n");
	// printf("cur: %p\nnex: %p\n", &tmp->cur_fork, &(*tmp->next_fork));
	// printf("---------\n");
	// tmp->lf->start = get_time();
	while (!tmp->lf->died && (tmp->count != tmp->lf->n_eat))
	{
		pthread_mutex_lock(&tmp->cur_fork);
		if (&(*tmp->next_fork))
			pthread_mutex_lock(&(*tmp->next_fork));
		else
			return (NULL);
		if (!display(tmp, get_time() - tmp->lf->start, "has taken a fork"))
			return (NULL);
		pthread_mutex_lock(&tmp->lf->mem);
		if (!display(tmp, get_time() - tmp->lf->start, "is eating"))
			return (NULL);
		tmp->eating = 1;
		usleep(tmp->lf->t_eat * 1000);
		tmp->ate = get_time();
		tmp->eating = 0;
		pthread_mutex_unlock(&tmp->lf->mem);
		pthread_mutex_unlock(&tmp->cur_fork);
		pthread_mutex_unlock(&(*tmp->next_fork));
		if (!display(tmp, get_time() - tmp->lf->start, "is sleeping"))
			return (NULL);
		usleep(tmp->lf->t_sleep * 1000);
		if (!display(tmp, get_time() - tmp->lf->start, "is thinking"))
			return (NULL);
		tmp->count++;
	}
	return (NULL);
}

int	display(t_philo *tmp, int timer, char *status)
{
	pthread_mutex_lock(&(tmp->lf->dis));
	if (ft_strlen(status) != 4 && tmp->lf->died)
		return (0);
	printf("%d %d %s\n", timer, tmp->pos, status);
	pthread_mutex_unlock(&(tmp->lf->dis));
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
	t_life			lf;

	if (!check_arg(ac, av, &lf))
		return (ft_err("Invalid Arguments"));
	init_threads(&lf);
	ft_lstclear(&(lf.philos), del);
	return (0);
}
