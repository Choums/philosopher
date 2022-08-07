/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/07 12:28:35 by root             ###   ########.fr       */
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
	if (lf->num > 0)
		lf->philos = ft_lstnew(i++, lf);
	while (i <= lf->num)
		ft_lstadd_back(&(lf->philos), ft_lstnew(i++, lf));
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
	tmp = lf->philos;
	while (1)
	{
		if (tmp->count == tmp->lf->n_eat)
			return (1);
		if (!tmp->ate && !tmp->eating && get_time() - lf->start >= lf->t_die)
		{
			// printf("killed 1\n");
			lf->died = 1;
			display(tmp, get_time() - tmp->lf->start, "died");
			exit(1);
		}
		else if (tmp->ate && !tmp->eating && get_time() - tmp->ate >= lf->t_die)
		{
			// printf("killed 2\n");
			lf->died = 1;
			display(tmp, get_time() - tmp->lf->start, "died");
			exit(1);
		}
		if (!tmp->next)
			tmp = lf->philos;
		else
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
 *	---
 *	Chaque action doit se faire lock au préalable puis unlock pour éviter tout écrasement
 *	L'affichage doit aussi faire part d'un lock
*/
void	*routine(void *phil)
{
	t_philo	*tmp;

	tmp = (t_philo *)phil;
	// printf("pos %d\n", tmp->pos);
	// printf("---------\n");
	// printf("cur: %p\nnex: %p\n", &tmp->cur_fork, &(*tmp->next_fork));
	// printf("---------\n");
	tmp->lf->start = get_time();
	while (!tmp->lf->died && (tmp->count != tmp->lf->n_eat))
	{
		pthread_mutex_lock(&tmp->cur_fork);
		pthread_mutex_lock(&(*tmp->next_fork));
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
		// if ((get_time() - tmp->ate) > tmp->lf->t_die)
		// {
		// 	tmp->lf->died = 1;
		// 	display(tmp, get_time() - tmp->lf->start, "died");
		// 	break ;
		// }
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
	printf("%d phil %d %s\n", timer, tmp->pos, status);
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
		ft_err("Invalid Arguments");
	init_threads(&lf);
	ft_lstclear(&(lf.philos), del);
	return (0);
}
