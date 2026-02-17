/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc < eakkoc@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:25:57 by eakkoc            #+#    #+#             */
/*   Updated: 2024/10/29 00:40:59 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	check_sign(char c, int *i)
{
	int	sign;

	sign = 1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long long	ft_atoi(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = check_sign(str[i], &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 922337203685477580 || (result == 922337203685477580
				&& str[i] >= '7'))
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
