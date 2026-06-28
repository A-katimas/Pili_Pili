/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:21:02 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/28 23:46:32 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <ctype.h>
# include <unistd.h>
# include <sys/time.h>

/* ==================== STRUCTURES ==================== */
typedef struct s_request
{
	int			coder_id;
	long long	arrival_time;
	long long	deadline;
}	t_request;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_request		*queue;
	int				available;
	long long		cooldown_end_time;
	int				queue_size;
	int				queue_capacity;
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

typedef struct safe_couter
{
	int				*counter;
	pthread_mutex_t	*lock;
}	t_safe;

typedef struct s_sim
{
	t_used			params;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_t		monitor_thread;
	long long		start_time;
	int				simulation_active;
}	t_sim;

typedef struct s_thread_args
{
	t_sim	*sim;
	t_coder	*coder;
}	t_thread_args;

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
void		log_taken_dongle(t_sim *sim, int coder_id);
void		log_is_compiling(t_sim *sim, int coder_id);
void		log_is_debugging(t_sim *sim, int coder_id);
void		log_is_refactoring(t_sim *sim, int coder_id);
void		log_burned_out(t_sim *sim, int coder_id);

//coder.c
void		*coder_routine(void *arg);

// thread.c
int			create_coder_threads(t_sim *sim);
void		wait_all_threads(t_sim *sim);
void		wait_monitor_thread(t_sim *sim);

// monitor.c
void		*monitor_routine(void *arg);

// dongle.c
void		release_dongle(t_sim *sim, t_dongle *dongle);
int			take_dongle(t_sim *sim, t_dongle *dongle, int coder_id);
t_dongle	*get_right_dongle(t_sim *sim, int coder_id);
t_dongle	*get_left_dongle(t_sim *sim, int coder_id);

// scheduler.c
void		add_to_queue(t_dongle *dongle, int coder_id,
				long long arrival_time, long long deadline);
int			get_next_coder_fifo(t_dongle *dongle);
int			get_next_coder_edf(t_dongle *dongle);
int			get_next_coder(t_dongle *dongle, const char *scheduler);

// debug.C
void		print_queue_status(t_sim *sim, t_dongle *dongle, int coder_id);
void		print_scheduler_choice(t_sim *sim, int dongle_id, int coder_chosen);

#endif