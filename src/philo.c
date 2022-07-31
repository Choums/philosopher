/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/31 17:52:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


/*
 *	Init. les threads(philosophes) et debute la simu
 *	Soit boucle sur n_eat
 *	Soit boucle sur num
*/
int	init_threads(t_life *lf)
{
	int	i;

	i = 0;
	if (lf->num > 1)
		ft_lstnew();
	while (++i < lf->num)	
		ft_lstadd_back(&(lf->philos), ft_lstnew());
	return (1);
}


void	routine(void *arg)
{
	(void)arg;
	printf("created thread\n");
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
	return (0);
}
