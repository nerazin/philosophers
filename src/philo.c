/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajothos <ajothos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:06:15 by ajothos           #+#    #+#             */
/*   Updated: 2021/12/08 18:26:11 by ajothos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_creation(t_table *table)
{
	int		i;
	int		num_philos;
	t_bool	wait;

	wait = true;
	num_philos = table->philos[0].settings->num_philos;
	while (wait)
	{
		i = 0;
		wait = false;
		while (i < num_philos)
		{
			if (table->philos[i].state == created)
				wait = true;
			i++;
		}
		usleep(50);
	}
}

t_bool	death_philo(t_philosopher *philo, size_t current_time)
{
	if (philo->state != frustrating
		&& philo->state != done
		&& current_time > philo->start_hungry + philo->settings->time_to_die)
	{
		philo->state = died;
		pthread_mutex_lock(philo->printer);
		current_time = current_time - philo->begin_time;
		printf("%zu\t %d died.\n", current_time, philo->id);
		return (true);
	}
	return (false);
}

t_bool	monitor(t_table *table)
{
	int		i;
	int		num_philos;
	t_bool	all_done;
	size_t	current_time;

	num_philos = table->philos[0].settings->num_philos;
	all_done = false;
	while (!all_done)
	{
		i = 0;
		all_done = true;
		current_time = time_ms();
		while (i < num_philos)
		{
			if (table->philos[i].state == died
				|| death_philo(&table->philos[i], current_time))
				return (false);
			if (table->philos[i].state != done)
				all_done = false;
			i++;
		}
		usleep(50);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_settings	settings;
	t_table		table;

	if (!set_settings(&settings, argc, argv))
		return (FAIL);
	if (!init_table(&table, settings.num_philos))
		return (FAIL);
	if (!init_philos(&table, &settings))
		return (FAIL);
	wait_creation(&table);
	settings.is_start = true;
	if (monitor(&table))
	{
		printf(OVER"SIMULATION IS OVER!\n"NORMAL);
		return (FAIL);
	}
	printf(OVER"SIMULATION IS OVER!\n"NORMAL);
	return (SUCCESS);
}
