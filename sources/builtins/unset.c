/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:14:33 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/01 19:19:29 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_data *data, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = get_env_var_index(data->env_list, args[i]);
			if (idx != -1)
				remove_env_var(data, idx);
		}
		i++;
	}
	return (ret);
}
