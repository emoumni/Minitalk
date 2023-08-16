/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emoumni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:11:43 by emoumni           #+#    #+#             */
/*   Updated: 2023/04/20 17:11:45 by emoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_restart_variables(int *len_received, char **str, int *i)
{
	*len_received = 0;
	if (str)
	{
		ft_putendl_fd(*str, 1);
		free(*str);
		*str = 0;
	}
	*i = 0;
}

static void	ft_receive_strlen(int *curr_bit, char **str, int *delivrd, int s)
{
	static int	len_val = 0;

	if (s == SIGUSR2)
		len_val += ft_power(2, *curr_bit);
	if (*curr_bit == 31)
	{
		*delivrd = 1;
		*str = ft_calloc_e((len_val + 1) * 2, sizeof(char));
		*curr_bit = 0;
		len_val = 0;
		return ;
	}
	(*curr_bit)++;
}

static void	ft_receive_info_from_client(int signal)
{
	static int	cur_bit = 0;
	static int	i = 0;
	static int	char_value = 0;
	static char	*final_str = 0;
	static int	len_deleivred = 0;

	if (!len_deleivred)
		ft_receive_strlen(&cur_bit, &final_str, &len_deleivred, signal);
	else
	{
		if (signal == SIGUSR2)
			char_value += ft_power(2, cur_bit);
		if (cur_bit == 7)
		{
			final_str[i++] = char_value;
			cur_bit = 0;
			if (char_value == 0)
				return (ft_restart_variables(&len_deleivred, &final_str, &i));
			char_value = 0;
			return ;
		}
		cur_bit++;
	}
}

int	main(void)
{
	int	id;

	id = (int)(getpid());
	ft_putnbr_fd(id, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, ft_receive_info_from_client);
	signal(SIGUSR2, ft_receive_info_from_client);
	while (1)
		usleep(200);
}
