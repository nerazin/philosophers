/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajothos <ajothos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:09:14 by ajothos           #+#    #+#             */
/*   Updated: 2021/12/13 13:02:21 by ajothos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

# define OVER	"\033[0m\x1b[30m\x1b[47m"
# define GREEN	"\x1b[32m"
# define RED	"\x1b[31m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define BOLD	"\033[1m"
# define NORMAL	"\033[0m"

# define TAKE_FORK	" has taken a fork.\n"
# define EATING		" is eating.\n"
# define SLEEPING	" is sleepingn\n"
# define THINKING	" is thinking.\n"
# define DIED		" is dead.\n"
# define SIM_OVER	"SIMULATION IS OVER!\n"

# define MALLOC_E	"Error: failed to allocate memory.\n"
# define MUTEX_E	"Error: failed to init mutex.\n"
# define THREAD_E	"Error: failed to create thread.\n"
# define DETACH_E	"Error: failed to detach thread.\n"
# define ARG_E		"Error: invalid number of parametrs.\n"
# define SET_E		"Error: invalid parametrs have been passed.\n"

# define FAIL 1
# define SUCCESS 0

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef enum e_bool
{
	false = 0,
	true = 1,
}	t_bool;

typedef enum e_p_state
{
	created,
	frustrating,
	eating,
	sleeping,
	thinking,
	died,
	done
}	t_p_state;

typedef struct s_settings
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	t_bool	is_start;
}	t_settings;

typedef struct s_philosopher
{
	t_mutex		*left;
	t_mutex		*right;
	t_mutex		*printer;
	t_settings	*settings;
	t_thread	thread;
	t_p_state	state;
	size_t		start_hungry;
	size_t		begin_time;
	int			id;
	int			eat_count;
}	t_philosopher;

typedef struct s_table
{
	t_philosopher	*philos;
	t_mutex			*forks;
	t_mutex			printer;
}	t_table;

//errors.c
t_bool	ft_errors(char *s);
//ft_atoi.c
int		ft_atoi(const char *str);
//set_setting.c
t_bool	set_settings(t_settings *settings, int argc, char **argv);
//inits.c
t_bool	init_table(t_table *table, int num_philos);
t_bool	init_philos(t_table *table, t_settings *settings);
//philo_action.c
void	*philo_action(void *arg);
//utils.c
size_t	time_ms(void);
void	ms_sleep(int ms);

#endif