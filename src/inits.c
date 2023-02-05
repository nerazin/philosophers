/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajothos <ajothos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:06:06 by ajothos           #+#    #+#             */
/*   Updated: 2021/12/08 16:20:49 by ajothos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	init_table(t_table *table, int num_philos)
{
	table->philos = malloc(sizeof(t_philosopher) * num_philos);
	table->forks = malloc(sizeof(t_mutex) * num_philos);
	if (!table->philos || !table->forks)
		return (ft_errors(MALLOC_E));
	return (true);
}

void	set_values(t_philosopher *philo, t_settings *settings,
	int i, t_table *table)
{
	philo->id = i;
	philo->state = created;
	philo->settings = settings;
	philo->eat_count = 0;
	philo->printer = &table->printer;
	if (i == 0)
	{
		table->philos[i].right = &table->forks[i];
		table->philos[i].left = &table->forks[settings->num_philos - 1];
	}
	else
	{
		table->philos[i].left = &table->forks[i - 1];
		table->philos[i].right = &table->forks[i];
	}
}

t_bool	init_philos(t_table *table, t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_action, &table->philos[i]) != 0)
			return (ft_errors(THREAD_E));
		if (pthread_mutex_init(&table->forks[i], NULL) != 0
			|| pthread_mutex_init(&table->printer, NULL) != 0)
			return (ft_errors(MUTEX_E));
		set_values(&table->philos[i], settings, i, table);
		i++;
	}
	return (true);
}
