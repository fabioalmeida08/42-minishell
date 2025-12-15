/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:09:12 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 16:09:12 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_builtin(t_shell *sh)
{
	int	n;
	t_builtin	builtins[] = {
		{"pwd", builtin_pwd},
		{"env", builtin_env},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{NULL, NULL}
	};

	n = 0;
	while (builtins[n].name)
		n++;
	sh->g_builtins = malloc(sizeof(t_builtin) * (n + 1));
	if (!sh->g_builtins)
		perror("g_builtins MALLOC FAILED");
	n = 0;
	while (builtins[n].name)
	{
		sh->g_builtins[n] = builtins[n];
		n++;
	}
	sh->g_builtins[n].name = NULL;
	sh->g_builtins[n].func = NULL;
}

int	is_builtin(char **cmd, t_shell *sh)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (sh->g_builtins[i].name)
	{
		if (ft_strcmp(cmd[0], sh->g_builtins[i].name))
		{
			res = 1;
			break ;
		}
		i++;
	}
	return (res);
}

void	exec_builtin(char **cmd, t_shell *sh)
{
	int	i;

	i = 0;
	printf("BUILTIN !!! \n");
	while (sh->g_builtins[i].name)
	{
		if (ft_strcmp(cmd[0], sh->g_builtins[i].name))
		{
			sh->g_builtins[i].func(cmd, sh);
			break ;
		}
		i++;
	}
}
