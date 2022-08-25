/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:33:30 by chaidel           #+#    #+#             */
/*   Updated: 2022/08/25 10:26:53 by chaidel          ###   ########.fr       */
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

/*
	philo		->	thread
	cur_fork	->	philo's fork
	next_fork	->	seatmate's fork (last point to first)
	check		->	allow the watcher to verify philo's condition without data race
	----------
	count		->	position around the table
	pos			->	number of time philo ate
	ate			->	last time the philo ate
	eating		->	to warn the checking thread that the philo is currently eating
	start		->	time at the beginning of the thread simulation
	----------
	lf			->	philo can access to simulation info
	next		->	point to next philo
	previous	->	point to previous philo
*/
typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	cur_fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	check;

	int				count;
	int				pos;
	int				ate;
	int				eating;
	int				start;

	struct s_life	*lf;
	struct s_philo	*next;
	struct s_philo	*previous;
}	t_philo;

/*
	num			->	number of philo
	t_die		->	time before dying
	t_eat		->	time to eating
	t_sleep		->	time of sleep
	n_eat		->	number of time the philo eats
	died		->	bool to check if a philo died
	stop		->	make the watcher stop when all threads have eaten enough
	----------
	starter		->	wait that all threads are created to launch the simulation
	dis			->	one thread can display at a time
	philos		->	list of philosophes
*/
typedef struct s_life
{
	int				num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				died;
	int				stop;

	pthread_mutex_t	death;
	pthread_mutex_t	starter;
	pthread_mutex_t	dis;
	t_philo			*philos;
}	t_life;

/*	Checker */
int		check_arg(int ac, char **av, t_life *lf);
int		strs_are_num(char **av);
int		get_time(void);

/*	Thread */
int		init_threads(t_life *lf);
void	create_list(t_life *lf);
void	*routine(void *phil);
int		check_end(t_philo *tmp);
int		take_fork(t_philo *tmp);
int		take_forkup(t_philo *tmp);
int		eating(t_philo *tmp);
int		display(t_philo *tmp, char *status);
void	init_forks(t_life *lf);
int		watcher(t_life *lf);
t_philo	*check_stop(t_life *lf, t_philo *tmp);
t_philo	*next_tmp(t_life *lf, t_philo *tmp);
void	sleeper(t_philo *tmp, int time);

/*	list */
t_philo	*ft_lstnew(int pos, t_life *lf);
void	ft_lstclear(t_philo **lst, t_life *lf, void (*del)(pthread_mutex_t,
				pthread_mutex_t));
void	ft_lstadd_back(t_philo **alst, t_philo *new);
void	ft_lstdelone(t_philo *lst, void (*del)(pthread_mutex_t,
				pthread_mutex_t));
t_philo	*ft_lstlast(t_philo *lst);
void	del(pthread_mutex_t cur_fork, pthread_mutex_t check);

/*	Utils */
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		ft_err(char *msg);
#endif
