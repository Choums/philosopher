/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:33:30 by chaidel           #+#    #+#             */
/*   Updated: 2022/04/13 22:01:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		philos;
	pthread_mutex_t	fork;
	long int		lim;
	long int		start_count;
	int				is_alive; //1 alive 0 dead
}	t_philo;

typedef struct s_life
{
	int	num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	t_philo	*philos;
}	t_life;


int		ft_check_arg(int ac, char **av, t_life *lf);
int		ft_gettime(void);

int		ft_atoi(const char *str);
void	ft_err(char *msg);
#endif