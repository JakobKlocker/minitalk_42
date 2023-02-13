/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jklocker <jklocker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:39:05 by jklocker          #+#    #+#             */
/*   Updated: 2022/11/16 13:30:26 by jklocker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		g_sig_recv;

void	received(int i, siginfo_t *siginfo, void *unused)
{
	(void)i;
	(void)siginfo;
	(void)unused;
	ft_printf("Signal from Server Received\n");
	g_sig_recv = 1;
}

void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 15;
	while (i >= 0)
	{
		if (g_sig_recv == 1)
		{
			if (((c >> i) & 1) == 0)
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(error_msg());
			}
			else if (((c >> i) & 1) == 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(error_msg());
			}
			g_sig_recv = 0;
			i--;
		}
	}
}

int	error_msg(void)
{
	ft_printf("Error occured.\n");
	return (-1);
}

int	send_signal(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_char(pid, str[i]);
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	g_sig_recv = 1;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &received;
	sigaction(SIGUSR1, &act, 0);
	if (argc != 3 || ft_atoi(argv[1]) < 0)
		return (error_msg());
	send_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
