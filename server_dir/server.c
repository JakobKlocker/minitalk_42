/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jklocker <jklocker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:53:52 by jklocker          #+#    #+#             */
/*   Updated: 2022/11/16 13:30:22 by jklocker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

unsigned int	g_bit_count;

void	handle_signal(int signum, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	if (signum == SIGUSR1)
		print_char(0);
	if (signum == SIGUSR2)
		print_char(1);
	usleep(20);
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
		exit(-1);
}

void	print_char(unsigned char bit)
{
	static unsigned char	prnt;

	if (g_bit_count == 0)
		prnt = 0;
	if (bit == 0)
		prnt = prnt << 1;
	else if (bit == 1)
		prnt = (prnt << 1) + 1;
	g_bit_count++;
	if ((g_bit_count % 16) == 0 && g_bit_count != 0)
	{
		ft_printf("%c", prnt);
		prnt = 0;
		g_bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Pid: %u\n", getpid());
	g_bit_count = 0;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_signal;
	if (sigaction(SIGUSR1, &act, 0) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &act, 0))
		return (-1);
	while (1)
		pause();
	return (0);
}
