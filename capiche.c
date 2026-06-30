/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 16:29:53 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/30 13:50:17 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void	*foo(void *count)
{
	int		i;
	t_safe	info;

	info = *(t_safe *)count;
	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(info.lock);
		*info.counter += 1;
		pthread_mutex_unlock(info.lock);
		i++;
	}
	return ((void *)info.counter);
}

int	main(int ac, char **av)
{
	pthread_t		*comme_tu_veux;
	int				i;
	pthread_mutex_t	a;
	void			*ret;
	int				counter;

	pthread_mutex_init(&a, NULL);
	(void) ac;
	comme_tu_veux = calloc(sizeof(pthread_t), 5);
	printf("hello %s", av[1]);
	i = 0;
	counter = 0;
	while (i < 5)
		pthread_create(&comme_tu_veux[i++], NULL, foo, &(t_safe){&counter, &a});
	i = 0;
	while (i < 5)
	{
		pthread_join(comme_tu_veux[i], &ret);
		printf("thread %d : %d\n", i, *(int *)ret);
		i++;
	}
	printf("counter : %d\n", counter);
	free(comme_tu_veux);
	return (0);
}
