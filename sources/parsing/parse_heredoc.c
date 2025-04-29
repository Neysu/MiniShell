/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:52:42 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/29 12:41:37 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	fill_heredoc(t_data *data, t_cmd *cmd, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		set_signal_interactive();
		line = readline(">");
		set_signal_noninteractive();
		if (!evaluate_heredoc_line(data, &line, cmd, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (ret);
}

bool	get_heredoc(t_data *data)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(data->cmd->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, data->cmd, tmp_fd);
	close(tmp_fd);
	return (ret);
}

char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

void	parse_heredoc(t_data *data, t_cmd **last_cmd, t_token **token_lst)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	if (!remove_old_file_ref(cmd, true))
		return ;
	cmd->infile = get_heredoc_name();
	cmd->heredoc_delimiter = get_delim(temp->next->str, &(cmd->heredoc_quotes));
	if (get_heredoc(data))
		cmd->fd_in = open(cmd->infile, O_RDONLY);
	else
		cmd->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
