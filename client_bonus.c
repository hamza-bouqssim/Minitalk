/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouqssi <hbouqssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:55:24 by hbouqssi          #+#    #+#             */
/*   Updated: 2022/03/26 20:00:26 by hbouqssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
// int check_pid(int pid, char *str)
// {
// 	if (pid == -1 || pid == 0 || strlen(str) < 5)
// 		return 0;
// 	else
// 		return 1;
// }
void	send_message(int pid, const char *str)
{
	int	i;
	int	j;

	i = 0;
	while (1)
	{
		j = 0;
		while (j < 8)
		{
			if ((str[i] & 128 >> j) != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(800);
			j++;
		}
		if (str[i] == 0)
			break ;
		i++;
	}
}

void	handler(int signum)
{
	(void)signum;
	write (1, GREEN "YOUR MESSAGE HAS BEEN SENT", 34);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(1, "Client:" RED "INVALID ARGUMENT !\n", 34);
		exit(EXIT_FAILURE);
	}
	if (pid <= 1)
	{
		write(1, "INVALID ARGUMENT !\n", 34);
		exit(1);
	}
	signal (SIGUSR1, handler);
	pid = ft_atoi(argv[1]);
	send_message(pid, argv[2]);
	return (0);
}
