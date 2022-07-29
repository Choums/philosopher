/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/29 14:58:31 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


/*
 *	Init. les threads(philosophes) debute la simu
 *	Soit boucle sur n_eat
 *	Soit boucle sur num
*/
int	init_threads(t_life *lf)
{
	pthread_t	thread;
	int			i;

	while (lf->n_eat)
	{
		lf->n_eat--;
	}
	i = 0;
	while (i <= lf->num)
	{
		pthread_create(&thread, ));
		i++;
	}
	return (1);
}


void	routine(void)
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

	// if (!ft_check_arg(ac, av, &lf))
	// 	ft_err("Invalid Arguments");
	int i = get_time();
	sleep(5);
	int j = get_time();
	printf("%dms\n", j - i);
	return (0);
}
