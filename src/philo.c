/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/05 19:29:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

int	sum = 0;

void	*ft_sum(void *arg)
{
	
	while (sum < 50000)
	{
		sum++;
	}
	printf("%d\n", sum);
	return (0);
}
/*
	1->	number of philos.
	2->	time to die
	3->	time to eat
	4->	time to sleep
	5->	number of times each philos. has to eat (optional)
	------------------------------------------------------
	
*/
int	main(int ac, char **av)
{
	struct timeval	ms;
	pthread_t		philo[atoi(av[1])];
	
	// gettimeofday(&ms, NULL);
	// printf("%ld\n", ms.tv_sec);
	// printf("%d\n", ms.tv_usec);
	pthread_create(&philo[0], NULL, ft_sum, NULL);
	pthread_create(&philo[1], NULL, ft_sum, NULL);
	pthread_join(philo[0], NULL);
	pthread_join(philo[1], NULL);
	return (0);
}
