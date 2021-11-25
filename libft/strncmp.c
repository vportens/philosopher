/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:46:04 by viporten          #+#    #+#             */
/*   Updated: 2021/08/26 16:09:11 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *str, char *to, int n)
{
	int	i;

	i = 0;
	if (str == NULL || to == NULL)
		return (-1);
	if ((int)ft_strlen(str) < n || (int)ft_strlen(to) < n)
		return (-1);
	while (i < n)
	{
		if (str[i] != to[i])
			return (-1);
		i++;
	}
	return (n);
}
