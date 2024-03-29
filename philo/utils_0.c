/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:48:30 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/10 20:21:20 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	char	*p;
	int		num;
	int		sign;

	p = (char *)str;
	num = 0;
	sign = 1;
	while (*p == 32 || (*p >= 9 && *p <= 13))
		p++;
	if (*p == '+' || *p == '-')
	{
		if (*p == '-')
			sign *= -1;
		p++;
	}
	while (ft_isdigit(*p))
	{
		num *= 10;
		num += (*p - '0');
		p++;
	}
	return (num * sign);
}	

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}