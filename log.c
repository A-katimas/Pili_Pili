/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 17:04:36 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/30 13:48:37 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_taken_dongle(t_sim *sim, int coder_id)
{
	log_message(sim, coder_id, "has taken a dongle");
}

void	log_is_compiling(t_sim *sim, int coder_id)
{
	log_message(sim, coder_id, "is compiling");
}

void	log_is_debugging(t_sim *sim, int coder_id)
{
	log_message(sim, coder_id, "is debugging");
}

void	log_is_refactoring(t_sim *sim, int coder_id)
{
	log_message(sim, coder_id, "is refactoring");
}

void	log_burned_out(t_sim *sim, int coder_id)
{
	log_message(sim, coder_id, "burned out");
}
