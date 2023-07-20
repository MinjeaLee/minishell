/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:28:54 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/06 14:30:37 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	(void)signo;
	g_exit_code = 1;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_sig(t_info *info)
{
	info->term = info->term_back;
	info->term.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &info->term);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc_child(int signo)
{
	(void)signo;
	exit(1);
}

void	sig_heredoc_parent(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
}

void	sig_parent(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_code = 1;
	}
	else if (signo == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		g_exit_code = 131;
	}
}
