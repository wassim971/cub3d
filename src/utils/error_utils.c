/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:06:58 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/10 15:41:41 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_error(const char *msg)
{
	printf(RED"%s\n"RESET, msg);
	exit(1);
}

int	error_msg(char *msg)
{
	printf(RED"%s\n"RESET, msg);
	return (0);
}
