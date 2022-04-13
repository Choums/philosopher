/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/13 22:02:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

/*
 *	Init. les threads(philosophes) debute la simu
 *	Soit boucle sur n_eat
 *	Soit boucle sur num
*/
int	ft_init_threads(t_life *lf)
{
	pthread_t	ph;
	int			i;
	
	while (lf->n_eat)
	{
		lf->n_eat--;
	}
	i = 0;
	while (i <= lf->num)
	{
		pthread_create(&ph, ));
		i++;
	}
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
	
	// if (!ft_check_arg(ac, av, &lf))
	// 	ft_err("Invalid Arguments");
	printf("time = %d\n", ft_gettime());
	return (0);
}
