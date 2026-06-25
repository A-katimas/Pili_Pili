#include "codexion.h"

int	is_valid_number(const char *str);
int is_all_valid_number(char **av);

t_used	parting(int ac, char **av)
{
	t_used	used_var;

	if (ac != 9)
		return (used_var.error = 1, used_var);
	if (!is_all_valid_number(av))
		return (used_var.error = 1, used_var);
	memset(&used_var, 0, sizeof(t_used));
	used_var.error = 0;
	used_var.number_of_coders = atoi(av[1]);
	used_var.time_to_burnout = atoi(av[2]);
	used_var.time_to_compile = atoi(av[3]);
	used_var.time_to_debug = atoi(av[4]);
	used_var.time_to_refactor = atoi(av[5]);
	used_var.number_of_compiles_required = atoi(av[6]);
	used_var.dongle_cooldown = atoi(av[7]);
	used_var.scheduler = av[8];
	if (!validate_args(used_var))
		return (used_var.error = 1, used_var);
	return (used_var);
}

int	validate_args(t_used used_var)
{
	if (used_var.number_of_coders <= 0)
		return (printf("Error: number_of_coders must be positive\n"), 0);
	if (used_var.time_to_burnout <= 0)
		return (printf("Error: time_to_burnout must be positive\n"), 0);
	if (used_var.time_to_compile <= 0)
		return (printf("Error: time_to_compile must be positive\n"), 0);
	if (used_var.time_to_debug <= 0)
		return (printf("Error: time_to_debug must be positive\n"), 0);
	if (used_var.time_to_refactor <= 0)
		return (printf("Error: time_to_refactor must be positive\n"), 0);
	if (used_var.number_of_compiles_required <= 0)
		return (printf("Error: number_of_compiles_required must be positive\n"), 0);
	if (used_var.dongle_cooldown < 0)
		return (printf("Error: dongle_cooldown cannot be negative\n"), 0);
	if (strcmp(used_var.scheduler, "fifo") != 0 &&
	    strcmp(used_var.scheduler, "edf") != 0)
		return (printf("Error: scheduler must be 'fifo' or 'edf'\n"), 0);
	return (1);
}

int is_all_valid_number(char **av)
{
	int i;

	i = 1;
	while (i < 8)
	{
		if (!is_valid_number(av[i]))
		{
			printf("Error: argument %d must be a positive number (got: %s)\n", i, av[i]);
			return (0);
		}
			i++;
	}
	return (1);
}

int	is_valid_number(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);

	i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}