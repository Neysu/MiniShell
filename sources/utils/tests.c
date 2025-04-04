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
	if (!data->cmd)
	{
		printf("Command list is empty.\n");
		return;
	}
	printf("\033[1;32mTokens:\033[0m\n");
	while (data->token)
	{
		printf("   Token:\033[30;32m %s \033[0m, Type: %d, Status: %d\n", data->token->str, data->token->type, data->token->status);
		data->token = data->token->next;
	}
	printf("\033[1;34mCommands:\033[0m\n");
	while (data->cmd)
	{
		printf("   Command:\033[30;34m %s \033[0m, Type: %d\n", data->cmd->cmd, data->cmd->type);
		data->cmd = data->cmd->next;
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
}
