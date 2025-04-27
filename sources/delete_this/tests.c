/*
		DELETE THIS
*/
#include "../../minishell.h"

void show_tokens(t_data *data)
{
	if (!data->token)
	{
		printf("No tokens to display.\n");
		return;
	}

	printf("\033[1;32mTokens:\033[0m\n");
	while (data->token)
	{
		printf("   Token:\033[30;32m %s \033[0m, Type: %d\n", data->token->str, data->token->type);
		data->token = data->token->next;
	}

}

void show_commands(t_data *data)
{
	if (!data || !data->cmd)
	{
		printf("Command list is empty.\n");
		return;
	}

	printf("\033[1;34mCommands:\033[0m\n");
	t_cmd *current = data->cmd;
	int cmd_num = 0;

	while (current)
	{
		printf("   Command #%d (Type: %d):\n", cmd_num, current->type);

		if (current->cmd)
		{
			int i = 0;
			while (current->cmd[i])
			{
				printf("      cmd[%d] : \033[30;34m%s\033[0m\n", i, current->cmd[i] ? current->cmd[i] : "(null)");
				i++;
				if (current->infile)
				{
						printf("      infile : \033[30;34m%s\033[0m\n", current->infile ? current->infile : "(null)");
				}
				if (current->fd_in != -1)
				{
						printf("      fd_in : \033[30;34m%d\033[0m\n", current->fd_in ? current->fd_in : 0);
				}
				if (current->outfile)
				{
						printf("      outfile : \033[30;34m%s\033[0m\n", current->outfile ? current->outfile : "(null)");
				}
				if (current->fd_out != -1)
				{
						printf("      fd_out : \033[30;34m%d\033[0m\n", current->fd_out ? current->fd_out : 0);
				}
				if (current->pipefd)
				{
					int i = 0;
					while (current->pipefd[i])
					{
						printf("      pipefd[%d] : \033[30;34m%d\033[0m\n", i, current->pipefd[i]);
						i++;
					}
				}
				if(current->heredoc_delimiter)
				{
					printf("      Heredoc delimiter : \033[30;34m%s\033[0m\n", current->heredoc_delimiter ? current->heredoc_delimiter : 0);
				}
			}
		}
		current = current->next;
		cmd_num++;
	}
}

void show_lists(t_data *data)
{
	if (!data)
	{
		printf("Data is NULL.\n");
		return;
	}
	printf("User Input: %s\n", data->user_input ? data->user_input : "NULL");
	printf("Work: %s\n", data->work ? "true" : "false");
	show_tokens(data);
	show_commands(data);
}
