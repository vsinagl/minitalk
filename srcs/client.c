/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:58:26 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/07 18:15:21 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	example(void)
{
	ft_putstr_fd("\n\tPlease, run client binary like this: ",
		STDOUT_FILENO);
	ft_putstr_fd("./client <PID> \"your message\"\n", STDOUT_FILENO);
}

int	handle_inputs(int argc, char **argv)
{
	int	i;

	if (argc != 3)
	{
		ft_putstr_fd("\nError, more or less than 2 parameters!\n",
			STDOUT_FILENO);
		example();
		return (1);
	}
	i = 0;
	while (argv[1][i] != '\0')
	{
		if (ft_isdigit(argv[1][i]) == 0)
		{
			ft_putstr_fd("\nError, invalid PID number\n", STDOUT_FILENO);
			example();
			return (1);
		}
		i++;
	}
	return (0);
}

//sigusr1 = for 1
//sugusr2 = for 0
int	send_message(int pid, char *message)
{
	int		bitcomp;
	int		bits_send;

	bitcomp = 0x01;
	while (*message != '\0')
	{
		bits_send = 0;
		while (bits_send < 8)
		{
			if ((*message >> bits_send & (bitcomp)) == 1)
			{
				kill(pid, SIGUSR1);
			}
			else
			{
				kill(pid, SIGUSR2);
			}
			bits_send++;
			usleep(500);
		}
		message++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		pid;

	if (handle_inputs(argc, argv) == 1)
		return (1);
	pid = ft_atoi(argv[1]);
	printf("sending message: %s\n", argv[2]);
	send_message (pid, argv[2]);
	send_message (pid, "\n");
	return (0);
}
