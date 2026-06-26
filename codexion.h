/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:21:02 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/26 17:39:06 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/time.h>

/* ==================== STRUCTURES ==================== */

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	int				available;
	long long		cooldown_end_time;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	long long		last_compile_start;
	int				compile_count;
	int				burned_out;
}	t_coder;

typedef struct s_used
{
	int		error;
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}	t_used;

typedef struct s_sim
{
	t_used			params;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	long long		start_time;
	int				simulation_active;
}	t_sim;

/* ==================== FUNCTIONS ==================== */

// Parsing
t_used		parting(int ac, char **av);
int			validate_args(t_used used_var);

// Utils
long long	get_current_time_ms(void);
void		cleanup_simulation(t_sim *sim);
void		log_message(t_sim *sim, int coder_id, const char *action);

// init.c
int			init_simulation(t_sim *sim, t_used params);

// log.c
void	log_taken_dongle(t_sim *sim, int coder_id);
void	log_is_compiling(t_sim *sim, int coder_id);
void	log_is_debugging(t_sim *sim, int coder_id);
void	log_is_refactoring(t_sim *sim, int coder_id);
void	log_burned_out(t_sim *sim, int coder_id);

#endif