/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/01 18:00:12 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0 , sizeof(t_cmd));
	new_node->cmd = NULL;
	//new_node->args = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_cmd	*lst_add_new_cmd(char *str)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0 , sizeof(t_cmd));
	new_node->cmd = str;
	//new_node->args = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd *start;

	start = *cmd_list;
	if(start == NULL)
	{
		*cmd_list = new_node;
		return ;
	}
	if (cmd_list && *cmd_list && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_cmd	*lst_last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void parse_word(t_data *data, t_token **token)
{
	t_token	*temp;
	t_cmd	*new_cmd;
	char	*space;
	char	*tmp_str;

	temp = *token;
	new_cmd = lst_new_cmd(); // Создаем новую команду

	while (temp && temp->type != END)
	{
		if (temp->type == WORD || temp->type == ENV)
		{
			if (new_cmd->cmd == NULL)
				new_cmd->cmd = ft_strdup(temp->str);
			else
			{
				space = " ";
				tmp_str = new_cmd->cmd;
				new_cmd->cmd = ft_strjoin(tmp_str, space);
				free(tmp_str);
				tmp_str = new_cmd->cmd;
				new_cmd->cmd = ft_strjoin(tmp_str, temp->str);
				free(tmp_str);
			}
			temp = temp->next;
		}
		else if (temp->type & (PIPE | REDIRECT_IN | REDIRECT_OUT | APPEND | HEREDOC))
		{
			new_cmd->type = temp->type;
			temp = temp->next;
			break ;
		}
		else
		{
			break ;
		}
	}
	if (new_cmd->cmd != NULL)
		lst_addback_cmd(&data->cmd, new_cmd);
	else
		free(new_cmd);
	*token = temp;
}

void create_commands(t_data *data, t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp && temp->type != END)
	{
		parse_word(data, &temp);
	}
}

/*void parse_word(t_cmd **cmd, t_token **token)
{
	t_token	*temp;
	t_cmd	*last_cmd;

	temp = *token;
	printf("temp->str: %s", temp->str);
	while(temp)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE) || last_cmd->cmd == NULL)
		{
			last_cmd->cmd = ft_strdup(temp->str);
			temp = temp->next;
		}
		temp = temp->next;
	}
	*token = temp;
}

void create_commands(t_data *data, t_token *token)
{
	t_token *temp;
	t_cmd *new_cmd = NULL;

	temp = token;
	printf("<cc>\n");
	if (temp->type == END)
		return ;
	if (temp)
    {
        new_cmd = lst_new_cmd(); // Создаем пустую команду
        lst_addback_cmd(&data->cmd, new_cmd);
    }

    while (temp)
    {
        printf("temp->str: %s\n", temp->str);

        // Получаем последнюю команду
        t_cmd *last_cmd = lst_last_cmd(data->cmd);

        // Если это первая команда и она пустая, заполняем ее
        if (last_cmd->cmd == NULL)
        {
            last_cmd->cmd = ft_strdup(temp->str);
        }
        // Иначе создаем новую команду для нового токена
        else if (temp->type == WORD || temp->type == ENV)
        {
            new_cmd = lst_new_cmd();
            new_cmd->cmd = ft_strdup(temp->str);
            lst_addback_cmd(&data->cmd, new_cmd);
        }

        printf("data->cmd->cmd: %s\n", data->cmd->cmd);
        temp = temp->next;
    }

}*/
