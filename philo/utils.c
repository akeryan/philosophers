/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeryan <akeryan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:48:30 by akeryan           #+#    #+#             */
/*   Updated: 2024/03/08 19:51:21 by akeryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
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