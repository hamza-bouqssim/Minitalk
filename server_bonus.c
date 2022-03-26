/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:55:14 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/02/06 17:55:16 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid = 0;

void	reset(char *b, int *sh, int pid)
{
	*b = 0b11111111;
	*sh = 0;
	g_pid = pid;
}

void	handler(int signum, siginfo_t *siginfo, void *oact)
{
	static char	printed = 0b11111111;
	static int	shifter;

	(void)oact;
	if (g_pid != siginfo->si_pid)
		reset(&printed, &shifter, siginfo->si_pid);
	if (signum == SIGUSR1)
		printed = printed | 128 >> shifter;
	else
		printed = printed ^ 128 >> shifter;
	shifter++;
	if (shifter == 8)
	{
		if (printed == 0)
			kill (siginfo->si_pid, SIGUSR1);
		else
			write (1, &printed, 1);
		shifter = 0;
		printed = 0b11111111;
	}
}

int	main(void)
{
	struct sigaction	sa;

	write(1, YELLOW "PID : ", 14);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
