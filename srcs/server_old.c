/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:58:26 by vsinagl           #+#    #+#             */
/*   Updated: 2024/05/07 18:15:21 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"
#include <unistd.h>

char	*text_buffer_handler(char *str, char c)
{
	char	*tmp;
	char	*charstr;
	char	*newstr;
	int		boolean;

	boolean = 0;
	if (str == NULL)
	{
		str = "";
		boolean = 1;
	}
	tmp = str;
	charstr = (char *)malloc(sizeof(char) * 2);
	charstr[0] = c;
	charstr[1] = '\0';
	newstr = ft_strjoin(str, charstr);
	free(charstr);
	if (boolean == 0)
		free(tmp);
	return (newstr);
}

void	reciever(int signum)
{
	static int		bits_recieved;
	static int		bit_value;

	if (signum == SIGUSR1)
		bit_value |= (0x01 << bits_recieved);
	bits_recieved++;
	if (bits_recieved == 8)
	{
		ft_putchar_fd((char)bit_value, STDOUT_FILENO);
		bits_recieved = 0;
		bit_value = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_putstr_fd("Server started\nServer PID: ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd("\n\nPRINTING AREA >>>>>>>>>>>>>>\n", STDOUT_FILENO);
	sa.sa_handler = &reciever;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
