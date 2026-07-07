/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnsecu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 15:31:33 by jtardieu          #+#    #+#             */
/*   Updated: 2026/07/07 15:32:30 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_burn(t_sim *sim, t_coder *coder)
{
	const int	res = has_burned_out(sim, coder);

	if (res == 1)
		return (1);
	else if (res == 2)
		return (1);
	return (0);
}
