/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:03:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/16 21:34:47 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*get_node_var(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env_node;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	pwd_update(t_data *data, char *path)
{
	t_env	*node_pwd;
	t_env	*node_old_pwd;
	char	*old_pwd;

	node_pwd = get_node_var(data, "PWD");
	if (!node_pwd)
		return (1);
	old_pwd = node_pwd->value;
	if (chdir(path) != 0)
		return (1);
	node_pwd->value = getcwd(NULL, 0);
	node_old_pwd = get_node_var(data, "OLDPWD");
	if (!node_old_pwd)
	{
		free(old_pwd);
		return (1);
	}
	if (node_old_pwd->value)
		free(node_old_pwd->value);
	node_old_pwd->value = old_pwd;
	freearray(data->env);
	data->env = NULL;
	ft_set_env(data);
	data->exit_code = 0;
	return (0);
}

void	ft_cd(t_data *data)
{
	t_env	*go_home;

	data->exit_code = 1;
	if (data->cmd->cmd && data->cmd->cmd[0]
		&& data->cmd->cmd[1] && data->cmd->cmd[2])
		ft_putendl_fd(" too many arguments", 2);
	else if (data->cmd->cmd[1] == NULL)
	{
		go_home = get_node_var(data, "HOME");
		if (go_home != NULL)
		{
			if (pwd_update(data, go_home->value))
				ft_putendl_fd("cd", 2);
		}
		else
			ft_putendl_fd("cd: could not determine home directory", 2);
	}
	else if (data->cmd->cmd[1] != NULL && pwd_update(data, data->cmd->cmd[1]))
		ft_putendl_fd(" No such file or directory", 2);
}
