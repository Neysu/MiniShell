/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:11:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/10 23:41:40 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

//# define PROMPT "\033[0;36mminishell>\033[0m "
//# define PROMPT "\033[1;38;5;207m \033[1;35mminishell\033[1;38;5;207m ❯\033[0m "
# define PROMPT1 "\033[1;32m┌──(\033[1;34mminishell\033[1;32m)-[\033[0m\033[1;37m"
# define PROMPT2 "\033[1;32m]\n└─\033[1;31m$\033[0m "
# define ERRORCMD "minishell : %s: unknown command\n"
# define UNSETARGS "unset: not enough args"
# define PATH_MAX_LEN 4096

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SUCCESS 0
# define FAILURE 1

typedef struct		s_envp
{
	char			*var;
	int				index;
	struct s_envp	*next;
}					t_envp;

typedef struct		s_token
{
	char			*str;
	int				type;
	int				status;
	bool			join;
	bool			var_exist;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_cmd
{
	char 			**cmd;
	char 			*cmd_name;
	int				fd;
	int				type;
	int				pipefd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_data
{
	char			*user_input;
	bool			work;
	int				exit_code;
	t_envp			*envp;
	t_token			*token;
	t_cmd			*cmd;
}					t_data;

typedef struct		s_sig
{
	int				sigint;
	int				sigquit;
	int 			exit_status;
	pid_t 			pid;
}					t_sig;

enum				e_token_type{
	SPACES = 1,
	WORD,			// 2 word
	ENV,			// 3 $
	PIPE,			// 4 |
	REDIRECT_IN,	// 5 <
	REDIRECT_OUT,	// 6 >
	APPEND,			// 7 >>
	HEREDOC,		// 8 <<
	END,			// 9 '\0'
	COMMAND = 10	// 10 COMMAND
};

enum				e_quoting_status{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

t_envp	*get_env(char **envp);
t_envp	*ft_lstnsave_word_or_sepew_env(char *envp);

size_t	ft_envsize(t_envp *env);
int		ft_exit(char *line, t_data *data);
int		ft_export(char *line, t_envp *envp_data);
int		ft_echo(char *line, t_data *data);
int		print_pwd(char *line);
int		print_env(t_envp *envp);
int		change_dirs(t_envp *envp, t_cmd	*cmd_data);
int		ft_unset(char *line, t_envp *envp_data);


int		exec_cmd(t_cmd *cmd_data, t_envp *envp);
int		exec_buitlins(char *line, t_data *data);

int		exec(t_data *data);

int		get_redirect(t_cmd *cmd_data);
int		open_files(t_cmd *cmd_data, t_data *data);
int		redirect(t_cmd *cmd_data, t_data *data);

void	ft_puterror(char *cmd);
void	ft_closefds(t_cmd *cmd_data);
char	*findcmd(t_cmd *cmd_data, t_envp *envp);

char	**env_to_str(t_envp *envp);

void	closepipe(t_cmd *cmd_data);

void	ft_lstadd_back(t_envp **lst, char *envp);

/*   utils/errors.c   */
void	error_message(char *text_error, char *detail, int quote);

/*   utils/errors.c   */
void	free_ptr(void *ptr);

/*   utils/free.c   */
void	lst_clear_cmd(t_cmd **lst, void (*del)(void *));
void	free_data(t_data *data, bool clear_history);
void	free_ptr(void *ptr);
void	lst_clear_token(t_token **lst, void (*del)(void *));
void	lst_delone_token(t_token *lst, void (*del)(void *));
void	free_str_tab(char **tab);
void	exit_shell(t_data *data, int exit_code);

/*   parsing/lexer.c   */
int		token_generator(t_data *data, char *str);
t_token	*lst_new_token(char *str, int type, int status);
void	lst_addback_token(t_token **token_list, t_token *new_node);
int		save_word(t_token **token_list, char *str, int index, int start);
int		save_separator(t_token **token_list, char *str, int index, int type);

/*   parsing/expand_variables.c   */
int		expand_variables(t_data *data, t_token **tokens);

/*   parsing/parsing.c   */
int		is_builtin(t_cmd *cmd_data);
t_cmd	*create_cmd(int type, char *cmd);
void	parsing(t_data *data);
bool	parser_user_input(t_data *data);

/*   envp_check.c   */
int	envp_check(t_token **token_list);

/*   parsing/signal.c   */
void	signal_reset_prompt(int signal);
void	signal_newline(int signal);
void	signal_ignore_sigquit(void);
void	set_signal_interactive(void);
void	set_signal_noninteractive(void);

/*   parsing/quotes_handler.c   */
int		quotes_handler(t_data *data);

/*   parsing/create_commands.c   */
void create_commands(t_data *data, t_token *token);

/*   DELETE THIS   */
void	show_tokens(t_data *data);
void	show_lists(t_data *data);

t_cmd	*lst_last_cmd(t_cmd *cmd);

#endif
