/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:46:33 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 02:40:43 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	home_cd(t_pipe *pipe, t_info *info)
{
	char	**str;

	if (pipe->exe_in_par == TRUE)
	{
		str = ft_split(get_env_val("HOME=", info), '=');
		if (chdir(str[1]) == FAILURE)
		{
			free(str[0]);
			free(str[1]);
			free(str);
			return (ft_perror(SUCCESS));
		}
		free(str[0]);
		free(str[1]);
		free(str);
		return (SUCCESS);
	}
	else
		exit(EXIT_SUCCESS);
}

int	exe_cd(t_pipe *pipe, t_info *info)
{
	char	*path;

	path = pipe->cmd[1];
	if (path == NULL)
		return (home_cd(pipe, info));
	if (chdir(path) == FAILURE)
	{
		g_exit_code = 1;
		if (pipe->exe_in_par == TRUE)
		{
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
			return (ft_perror(SUCCESS));
		}
		else
			exit(EXIT_SUCCESS);
	}
	if (pipe->exe_in_par == TRUE)
		return (SUCCESS);
	else
		exit(EXIT_SUCCESS);
}
