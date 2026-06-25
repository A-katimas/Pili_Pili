/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtardieu <jtardieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 22:31:15 by jtardieu          #+#    #+#             */
/*   Updated: 2026/06/25 22:35:47 by jtardieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


#include <time.h>

long long get_current_time_ms(void)
{
	return (time(NULL) * 1000);
}