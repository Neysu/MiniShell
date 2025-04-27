/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:11:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/27 17:21:13 by rureshet         ###   ########.fr       */
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
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\033[1;37mminishell >>\033[0m "
//# define PROMPT "\033[1;38;5;207m \033[1;35mminishell\033[1;38;5;207m ❯\033[0m "
// # define PROMPT1 "\033[1;32m┌──(\033[1;34mminishell\033[1;32m)-[\033[0m\033[1;37m"
// # define PROMPT2 "\033[1;32m]\n└─\033[1;31m$\033[0m "
# define ERRORCMD "minishell : %s: unknown command\n"
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"
# define UNSETARGS "unset: not enough args"

# ifndef PATH_MAX_LEN
#  define PATH_MAX_LEN 4096
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SUCCESS 0
# define FAILURE 1

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

typedef struct		s_envp
{
	char			*var;
	struct s_envp	*next;
}					t_envp;

typedef struct		s_token
{
	char			*str;
	char			*str_backup;
	int				type;
	int				status;
	bool			join;
	bool			var_exist;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_cmd
{
	char			**cmd;
	char			*path;
	bool			pipe_output;
	int				*pipefd;
	int				type;
	int				fd;
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	int				stdin_backup;
	int				stdout_backup;
	char			*heredoc_delimiter;
	bool			heredoc_quotes;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_data
{
	char			*user_input;
	bool			work;
	int				exit_code;
	char			*working_dir;
	char			*old_working_dir;
	char 			**env_list;
	t_envp			*envp;
	t_token			*token;
	t_cmd			*cmd;
	pid_t 			pid;
}					t_data;

typedef struct		s_sig
{
	int				sigint;
	int				sigquit;
	int 			exit_status;
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

/* env related*/
t_envp	*get_env(char **envp);
t_envp	*ft_lstnsave_word_or_sepew_env(char *envp);
void	ft_lstadd_back(t_envp **lst, char *envp);
char	**env_to_str(t_envp *envp);

/* builtins */
size_t	ft_envsize(t_envp *env);
int		ft_exit(char *line, t_data *data);
int		ft_export(char *line, t_envp *envp_data);
int		ft_echo(char *line, t_data *data);
int		print_pwd(char *line);
int		print_env(t_envp *envp);
int		change_dirs(t_envp *envp, t_cmd	*cmd_data);
int		ft_unset(char *line, t_envp *envp_data);

int		print_env2(char **envp);

/* executions */
int		exec_cmd(t_data *data, t_cmd *cmd);
char	*findcmd(t_cmd *cmd_data, t_envp *envp);
int		exec_buitlins(t_data *data, t_cmd *cmd);
int		exec(t_data *data);

/* redirections*/
void	closepipe(t_cmd *cmd_data);
void	ft_closefds(t_cmd *cmd_data);
int		get_redirect(t_cmd *cmd_data);
int		is_redirect(t_cmd	*cmd_data);
int		open_files(t_cmd *cmd_data, t_data *data);
int		redirect(t_cmd *cmd_data, t_data *data);

/*   utils/errors.c   */
void	ft_puterror(char *cmd);
int		errmsg_cmd(char *command, char *detail, char *error_message, int error_nb);
void	error_message(char *text_error, char *detail, int quote);

/*   utils/free.c   */
void	free_ptr(void *ptr);
void	free_tokens(t_token *head);

/*   utils/free.c   */
void	lst_clear_cmd(t_cmd **lst, void (*del)(void *));
void	free_data(t_data *data, bool clear_history);
void	free_ptr(void *ptr);
void	lst_clear_token(t_token **lst, void (*del)(void *));
void	lst_delone_token(t_token *lst, void (*del)(void *));
void	free_str_tab(char **tab);
void	exit_shell(t_data *data, int exit_code);
void	print_exit_shell(t_data *data, int exit_code);
void	free_env_array(char **env_array);

/*   parsing/lexer.c   */

int		token_generator(t_data *data, char *str);
t_token	*lst_new_token(char *str, char *str_backup, int type, int status);
void	lst_addback_token(t_token **token_list, t_token *new_node);
int		save_word(t_token **token_list, char *str, int index, int start);
int		save_separator(t_token **token_list, char *str, int index, int type);

/*   parsing/cmd_list_utils.c   */
t_cmd	*lst_new_cmd(bool value);
t_cmd	*lst_add_new_cmd(void);
void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node);
t_cmd	*lst_last_cmd(t_cmd *cmd);

/*   parsing/token_utils.c   */
bool	contains_space(char *str);
void	lstdelone_token(t_token *lst, void (*del)(void *));
void	lstclear_token(t_token **lst, void (*del)(void *));

/*   parsing/args_handling.c   */
int		args_count(t_token *token);
int		create_args_default_mode(t_token **token_node, t_cmd *last_cmd);
char	**copy_default_in_new_tab(int len, char **new_tab, t_cmd *last_cmd, t_token **tk_node);
int		add_args_default_mode(t_token **token_node, t_cmd *last_cmd);

/*   parsing/create_commands.c   */
int		fill_cmd(t_token **token_node, t_cmd *last_cmd, char *str);
int		fill_args(t_token **token_node, t_cmd *last_cmd);
void	split_var_cmd_token(t_cmd *last_cmd, char *cmd_str);
void	parse_word(t_cmd **cmd, t_token **token);
void	set_cmd_type(t_data *data, t_token **token, int type);
void	create_commands(t_data *data, t_token *token);
bool	remove_old_file_ref(t_cmd *cmd, bool infile);

/*   parsing/var_validation.c   */
bool	char_is_sep(char c);
bool	between_quotes(char *str, int i);
bool	is_var_valid(char c);
int		var_len(char *str);
char	*search_name_var(char *str);

/*   parsing/env_var_handling.c   */
void	update_status(t_token **token, char c);
int		var_exist(t_data *data, char *var);
char	*get_env_value(t_data *data, char *var);
char	*get_var_value(t_token *token, char *str, t_data *data);
int		exchange_var(t_token **token, char *var_value, int index);
int		get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);

/*   parsing/expand_variables.c   */

int		erase_var(t_token **token, char *str, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*get_new_token_str(char *str, char *var_value, int new_str_size, int index);
char	*erase_and_replace(t_token **token, char *str, char *var_value, int index);
int		expand_variables(t_data *data, t_token **tokens);


/*   parsing/file_io.c   */
void	init_io(t_cmd *cmd);
bool	restore_io(t_cmd *cmd);
bool	redirect_io(t_cmd *cmd);

/*   parsing/parse_path.c   */
char	*get_cmd_path(t_data *data, char *name);

/*   parsing/parse_pipe.c   */
void	parse_pipe(t_cmd **cmd, t_token **token_lst);

/*   parsing/parse_append.c   */
void	parse_append(t_cmd **last_cmd, t_token **token_lst);

/*   parsing/parse_append.c   */
void	parse_heredoc(t_data *data, t_cmd **last_cmd, t_token **token_lst);

/*   parsing/parsing.c   */
int		is_builtin(t_cmd *cmd_data);
t_cmd	*create_cmd(int type, char *cmd);
void	parsing(t_data *data);
bool	parser_user_input(t_data *data);
bool	check_infile_outfile(t_cmd *cmd);
void	close_fds(t_cmd *cmds, bool close_backups);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
bool	create_pipes(t_data *data);

/*   envp_check.c   */
int		envp_check(t_token **token_list);

/*   parsing/signal.c   */
void	signal_reset_prompt(int signal);
void	signal_newline(int signal);
void	signal_ignore_sigquit(void);
void	set_signal_interactive(void);
void	set_signal_noninteractive(void);

/*   parsing/quotes_handler.c   */
int		quotes_handler(t_data *data);

/*   parsing/quotes_handler.c   */
int	create_args_echo_mode(t_token **token_node, t_cmd *last_cmd);
int	add_args_echo_mode(t_token **token_node, t_cmd *last_cmd);

/*   DELETE THIS   */
void	show_tokens(t_data *data);
void	show_lists(t_data *data);
/*   DELETE THIS   */

t_cmd	*lst_last_cmd(t_cmd *cmd);

#endif
