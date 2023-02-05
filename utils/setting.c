/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajothos <ajothos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:06:21 by ajothos           #+#    #+#             */
/*   Updated: 2021/12/08 16:20:31 by ajothos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	set_settings(t_settings *settings, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_errors(ARG_E));
	settings->num_philos = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	settings->is_start = false;
	settings->must_eat = -1;
	if (argc == 6)
		settings->must_eat = ft_atoi(argv[5]);
	if (settings->num_philos < 1
		|| settings->num_philos > 200 || settings->time_to_die < 60
		|| settings->time_to_eat < 60 || settings->time_to_sleep < 60
		|| (argc == 6 && settings->must_eat <= 0))
		return (ft_errors(SET_E));
	return (true);
}
