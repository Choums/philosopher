/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/02 20:19:59 by root             ###   ########.fr       */
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

	i = 1;
	if (lf->num > 1)
		lf->philos = ft_lstnew(i, lf);
	while (++i <= lf->num)	
		ft_lstadd_back(&(lf->philos), ft_lstnew(i, lf));
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
*/
void	*routine(void *phil)
{
	t_philo	*tmp;

	tmp = (t_philo *)phil;
	while ()
	return (NULL);
}

int	all_alive(t_philo *tmp)
{
	while (tmp)
	{
		tmp = tmp->next;
	}
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
	init_threads(&lf);
	ft_lstclear(&(lf.philos), del);
	return (0);
}
