/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/04 10:35:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 *	Init. les threads(philosophes) et debute la simu
*/
int	init_threads(t_life *lf)
{
	int		i;
	t_philo	*tmp;
	t_philo	*fst;

	i = 1;
	if (lf->num > 1)
		lf->philos = ft_lstnew(i, lf);
	while (++i <= lf->num)
		ft_lstadd_back(&(lf->philos), ft_lstnew(i, lf));
	tmp = lf->philos;
	fst = lf->philos;
	while (tmp->pos < tmp->lf->num)
	{
		tmp->next_fork = &tmp->next->cur_fork;
		tmp = tmp->next;
	}
	tmp->next_fork = &fst->cur_fork;
	tmp = lf->philos;
	while (tmp)
	{
		pthread_create(&(tmp->philo), NULL, &routine, tmp);
		tmp = tmp->next;
	}
	return (1);
}


/*
 *	Routine des philos: manger, dormir, penser
 *	La routine dure tant qu'un philo n'est pas mort ou si n_eat a été init
 *	-------------------------------------
 *	Fork
 *	Le philo se met à manger s'il peut mutex sa fourchette et la suivante
 *	Attention => les threads ce lancent quasi en meme temps, le 2nd lock son cur
 *					avant que le 1er ne puisse lock le next ==> Error
*/
void	*routine(void *phil)
{
	t_philo	*tmp;
	int		time;

	tmp = (t_philo *)phil;
	// printf("pos %d\n", tmp->pos);
	// printf("---------\n");
	// printf("cur: %p\nnex: %p\n", &tmp->cur_fork, &(*tmp->next_fork));
	// printf("---------\n");
	time = get_time();
	while (tmp->count < tmp->lf->n_eat)
	{
		pthread_mutex_lock(&tmp->cur_fork);
		pthread_mutex_lock(&(*tmp->next_fork));
		printf("phil %d has taken a fork\n", tmp->pos);
		pthread_mutex_lock(&tmp->lf->mem);
		printf("phil %d is eating\n", tmp->pos);
		usleep(tmp->lf->t_eat * (int)1e3);
		time = get_time();
		pthread_mutex_unlock(&tmp->lf->mem);
		pthread_mutex_unlock(&tmp->cur_fork);
		pthread_mutex_unlock(&(*tmp->next_fork));
		printf("%d phil %d is sleeping\n", get_time() - time, tmp->pos);
		usleep(tmp->lf->t_sleep * (int)1e3);
		printf("phil %d is thinking\n", tmp->pos);
		tmp->count++;
	}
	return (NULL);
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

	if (!ft_check_arg(ac, av, &lf))
		ft_err("Invalid Arguments");
	// int time = get_time();
	// printf("time: %d\n", time);
	// printf("t: %d | %d\n", get_time(), get_time() - time);
	// usleep(2000 * (int)1e3);
	// printf("%d\n", get_time() - time);
	init_threads(&lf);
	ft_lstclear(&(lf.philos), del);
	return (0);
}
