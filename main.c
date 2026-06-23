/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:26:47 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/23 18:18:06 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "string.h"
#include "codexion.h"

t_used	parting(int ac, char **av);


int	main(int ac, char **av)
{
	t_used	used_var;

	used_var = parting(ac, av);
	if (used_var.error == 1)
	{
		printf("error no good argument");
		return (1);
	}
	printf("%d", used_var.time_to_burnout);
	return (0);
}

t_used	parting(int ac, char **av)
{
	t_used	used_var;
	int		i;

	if (ac != 9)
		return (used_var.error = 1, used_var);
	i = 1;
	used_var.error = 0;
	used_var.number_of_coders = atoi(av[1]);
	used_var.time_to_burnout = atoi(av[2]);
	used_var.time_to_compile = atoi(av[3]);
	used_var.time_to_debug = atoi(av[4]);
	used_var.time_to_refactor = atoi(av[5]);
	used_var.number_of_compiles_required = atoi(av[6]);
	used_var.dongle_cooldown = atoi(av[7]);
	used_var.scheduler = av[8];
	return (used_var);
}
