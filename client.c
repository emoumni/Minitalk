/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoumni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:11:30 by emoumni           #+#    #+#             */
/*   Updated: 2023/04/20 17:11:32 by emoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	err_main(int ac, char **av)
{
	int	i;

	i = -1;
	if (ac != 3)
	{
		ft_putstr_fd("wrong number of args", 1);
		return (1);
	}
	while (av[1][++i])
	{
		if (!ft_strchr("0123456789", av[1][i]))
		{	
			ft_putstr_fd("error consurning pid", 1);
			return (1);
		}
	}
	return (0);
}

static void	send_len_bit_bit(int pid, int len)
{
	int	i;

	i = -1;
	while (++i < 32)
	{
		if (len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		usleep(200);
	}
}

static void	send_str(int pid, unsigned char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;
	int		len;
	char	*str;

	if (err_main(ac, av))
		return (-1);
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("error consurning pid", 1);
		return (-1);
	}
	str = av[2];
	len = ft_strlen(str);
	send_len_bit_bit(pid, len);
	i = -1;
	while (str[++i])
		send_str(pid, str[i]);
	send_str(pid, str[i]);
	return (0);
}
