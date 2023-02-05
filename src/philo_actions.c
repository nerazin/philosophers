/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajothos <ajothos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:05:35 by ajothos           #+#    #+#             */
/*   Updated: 2021/12/08 16:20:44 by ajothos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	try_get_fork(t_mutex *fork, t_philosopher *philo)
{
	size_t	current_time;

	pthread_mutex_lock(fork);
	current_time = time_ms() - philo->begin_time;
	pthread_mutex_lock(philo->printer);
	printf(YELLOW"%zu\t %d has taken a fork\n", current_time, philo->id);
	pthread_mutex_unlock(philo->printer);
}

void	try_eat(t_philosopher *philo)
{
	size_t	current_time;

	philo->start_hungry = time_ms();
	philo->state = eating;
	philo->eat_count++;
	pthread_mutex_lock(philo->printer);
	current_time = time_ms() - philo->begin_time;
	printf(GREEN"%zu\t %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(philo->printer);
	ms_sleep(philo->settings->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

t_bool	try_sleep(t_philosopher *philo)
{
	size_t	current_time;

	philo->state = sleeping;
	pthread_mutex_lock(philo->printer);
	current_time = time_ms() - philo->begin_time;
	printf(RED"%zu\t %d is sleeping\n", current_time, philo->id);
	pthread_mutex_unlock(philo->printer);
	ms_sleep(philo->settings->time_to_sleep);
	philo->state = thinking;
	pthread_mutex_lock(philo->printer);
	current_time = time_ms() - philo->begin_time;
	printf(BLUE"%zu\t %d is thinking\n", current_time, philo->id);
	pthread_mutex_unlock(philo->printer);
	if (philo->settings->must_eat != -1
		&& philo->eat_count == philo->settings->must_eat)
	{
		philo->state = done;
		return (false);
	}
	return (true);
}

void	ft_skip(t_bool *skip, int time_to_eat)
{
	if (*skip)
		ms_sleep(time_to_eat);
	*skip = false;
}

void	*philo_action(void *arg)
{
	t_philosopher	*philo;
	t_bool			skip;

	philo = (t_philosopher *)arg;
	philo->state = frustrating;
	while (!philo->settings->is_start)
		usleep(50);
	skip = false;
	if (philo->id % 2 == 1)
		skip = true;
	philo->begin_time = time_ms();
	philo->start_hungry = philo->begin_time;
	while (true)
	{
		philo->state = thinking;
		ft_skip(&skip, philo->settings->time_to_eat);
		try_get_fork(philo->left, philo);
		try_get_fork(philo->right, philo);
		try_eat(philo);
		if (!try_sleep(philo))
			return (NULL);
	}
}
