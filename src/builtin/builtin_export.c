/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:07:49 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 16:07:49 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_print(t_shell *sh)
{
	t_env	*env_list;

	env_list = sh->env_list;
	while (env_list)
	{
		printf("declare -x %s", env_list->key);
		if (env_list->value)
			printf("=\"%s\"", env_list->value);
		printf("\n");
		env_list = env_list->next;
	}
}

void	builtin_export(char **cmd, t_shell *sh)
{
	char	*equal;
	char	*key;
	char	*value;

	if (!cmd[1])
		export_print(sh);
	else
	{
		equal = ft_strchr(cmd[1], '=');
		if (equal)
		{
			key = ft_substr(cmd[1], 0, equal - cmd[1]);
			value = ft_strdup(equal + 1);
			if (get_env_node(sh->env_list, key))
				update_env_var(sh->env_list, key, value);
			else
				add_env_var(&sh->env_list, key, value);
			free(key);
			free(value);
		}
		else
		{
			if (get_env_node(sh->env_list, cmd[1]))
				return ;
			else
				add_env_var(&sh->env_list, cmd[1], NULL);
		}
	}
}
