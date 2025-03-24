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
	printf("Tokens:\n");
	while (data->token)
	{
		printf("  Token: %s, Type: %d, Status: %d\n", data->token->str, data->token->type, data->token->status);
		data->token = data->token->next;
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
