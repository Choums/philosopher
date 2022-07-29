/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:33:30 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/29 14:58:42 by chaidel          ###   ########.fr       */
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
	pthread_t		philo;		// thread
	pthread_mutex_t	cur_fork;	// philo's fork
	pthread_mutex_t	next_fork;	// seatmate's fork

	int				count;		// time of the philo's action
	int				is_alive;	// bool

	t_philo			next;		// point to next philo (last point to last)
	t_philo			previous;	// point to previous philo (first point to last)
}	t_philo;

typedef struct s_life
{
	int		num;		// number of philo
	int		t_die;		// time before dying
	int		t_eat;		// time to eating
	int		t_sleep;	// time of sleep
	int		n_eat;		// number of time the philo eats
	t_philo	*philos;
}	t_life;


int		ft_check_arg(int ac, char **av, t_life *lf);
int		get_time(void);
int		init_threads(t_life *lf);
void	routine(void);

/*	Utils */
int		ft_atoi(const char *str);
void	ft_err(char *msg);
#endif