/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:35:39 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/06 19:39:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

void	*ft_sum(void *arg)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&mutex);
	printf("incrementing\n");
    for (int i = 0; i < 10000; ++i) {
        sum++;
    }
	pthread_mutex_unlock(&mutex);
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

	if (ac < 5 && ft_check_arg())
	{
		ft_endless();
	}
	else
		ft_
	// gettimeofday(&ms, NULL);
	// printf("%ld\n", ms.tv_sec);
	// printf("%d\n", ms.tv_usec);
	printf("%d\n", sum);
	return (0);
}
