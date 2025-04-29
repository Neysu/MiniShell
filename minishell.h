/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:11:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/29 14:51:19 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
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

typedef struct s_envp
{
	char			*var;
	struct s_envp	*next;
}					t_envp;

typedef struct s_token
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

typedef struct s_cmd
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

typedef struct s_data
{
	char			*user_input;
	bool			work;
	int				exit_code;
	char			*working_dir;
	char			*old_working_dir;
	char			**env_list;
	t_envp			*envp;
	t_token			*token;
	t_cmd			*cmd;
	pid_t			pid;
}					t_data;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
}					t_sig;

enum e_token_type
{
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

enum e_quoting_status
{
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
int		errmsg_cmd(char *command, char *detail,
			char *error_message, int error_nb);
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

/*       PARSING       */
/*   args_handling.c   */

int		create_args_default_mode(t_token **token_node, t_cmd *last_cmd);
char	**copy_default_in_new_tab(int len, char **new_tab,
			t_cmd *last_cmd, t_token **tk_node);
int		add_args_default_mode(t_token **token_node, t_cmd *last_cmd);
int		fill_args(t_token **token_node, t_cmd *last_cmd);

/*   cmd_list_utils.c   */

void	init_cmd(t_cmd **cmd);
t_cmd	*lst_new_cmd(bool value);
t_cmd	*lst_add_new_cmd(void);
void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node);
t_cmd	*lst_last_cmd(t_cmd *cmd);

/*   create_commands.c   */

void	prep_no_arg_commands(t_data *data);
bool	remove_old_file_ref(t_cmd *cmd, bool infile);
void	create_commands(t_data *data, t_token *token);

/*   env_var_handling.c   */

int		var_exist(t_data *data, char *var);
char	*extract_env_value(t_data *data, char *var);
char	*resolve_env_variable(t_token *token, char *str, t_data *data);
int		find_env_var_index(char **env, char *var);
char	*fetch_env_var_value(char **env, char *var);

/*   env_var_utils.c   */

void	update_status(t_token **token, char c);

/*   envp_check.c   */

int		exchange_var(t_token **token, char *var_value, int index);
void	envp_check_tool(t_token **token);
bool	is_consecutive(t_token *token);
int		check_syntax_operators(t_token **token_list);
int		envp_check(t_token **token_list);

/*   expand_variables.c   */

int		erase_var(t_token **token, char *str, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*get_new_token_str(char *str, char *var_value,
			int new_str_size, int index);
char	*erase_and_replace(t_token **token, char *str,
			char *var_value, int index);
int		expand_variables(t_data *data, t_token **tokens);

/*   file_io.c   */

bool	restore_io(t_cmd *cmd);
bool	redirect_io(t_cmd *cmd);

/*   lexer_utils.c   */

int		is_separator(char *str, int i);
int		check_quotes(int status, char *str, int i);
t_token	*lst_new_token(char *str, char *str_backup, int type, int status);
void	lst_addback_token(t_token **token_list, t_token *new_node);

/*   token_generator.c   */

int		save_word(t_token **token_list, char *str, int index, int start);
int		save_separator(t_token **token_list, char *str, int index, int type);
int		save_word_or_sep(int *i, char *str, int start, t_data *data);
int		token_generator(t_data *data, char *str);

/*   parse_append.c   */

void	parse_append(t_cmd **last_cmd, t_token **token_lst);

/*   heredoc_var_utils.c   */

int		var_exists(t_data *data, char *var);
char	*search_env_var(t_data *data, char *var);
char	*identify_var(char *str);
char	*recover_val(t_token *token, char *str, t_data *data);
bool	is_var_compliant(char c);

/*   heredoc_utils.c   */

char	*get_new_token_string(char *oldstr, char *var_value,
			int newstr_size, int index);
int		replace_var(t_token **token_node, char *var_value, int index);
char	*replace_str_heredoc(char *str, char *var_value, int index);
bool	is_next_char_a_sep(char c);
bool	var_between_quotes(char *str, int i);

/*   parse_heredoc_utils.c   */

int		var_expander(t_data *data, t_token **token_lst);
char	*var_expander_heredoc(t_data *data, char *str);
char	*make_str_from_tab(char **tab);
char	*get_expanded_var_line(t_data *data, char *line);
bool	evaluate_heredoc_line(t_data *data, char **line, t_cmd *cmd, bool *ret);

/*   parse_heredoc.c   */

bool	fill_heredoc(t_data *data, t_cmd *cmd, int fd);
bool	get_heredoc(t_data *data);
char	*get_heredoc_name(void);
char	*get_delim(char *delim, bool *quotes);
void	parse_heredoc(t_data *data, t_cmd **last_cmd, t_token **token_lst);

/*   parse_io.c 4f  */

void	set_outfile(t_token **token, t_cmd **last_cmd);
void	set_infile(t_token **token, t_cmd **last_cmd);

/*   parse_path.c   */

char	*get_cmd_path(t_data *data, char *name);

/*   parse_pipe.c   */

void	parse_pipe(t_cmd **cmd, t_token **token_lst);

/*   parse_pipe.c 3f  */
void	parse_word(t_cmd **cmd, t_token **token);

/*   fd_utils.c   */

int		ft_isspace(int c);
bool	input_is_space(char *input);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
bool	create_pipes(t_data *data);
void	close_fds(t_cmd *cmds, bool close_backups);

/*   execute.c   */

int		get_children(t_data *data);
int		create_children(t_data *data);
bool	check_infile_outfile(t_cmd *cmd);
int		prep_for_exec(t_data *data);
int		execute(t_data *data);

/*   parsing.c   */

int		is_builtin(t_cmd *cmd_data);
void	parsing(t_data *data);
bool	parser_user_input(t_data *data);

/*   quotes_handler_utils.c   */

int		count_len(char *str, int count, int i);
bool	quote_and_status_default(t_token **token, int i);
void	change_status_quote(t_token **token, int *i);
bool	back_status_to_default(t_token **token, int *i);
int		remove_quotes(t_token **token);

/*   quotes_handler.c   */

bool	quotes_in_str(char *str);
int		quotes_handler(t_data *data);

/*   signal.c   */

void	signal_reset_prompt(int signal);
void	signal_newline(int signal);
void	set_signal_interactive(void);
void	set_signal_noninteractive(void);
void	signal_ignore_sigquit(void);

/*   token_utils.c   */

bool	contains_space(char *str);
void	lstdelone_token(t_token *lst, void (*del)(void *));
void	lstclear_token(t_token **lst, void (*del)(void *));

/*   var_validation.c   */

bool	char_is_sep(char c);
bool	between_quotes(char *str, int i);
bool	is_var_valid(char c);
int		var_len(char *str);
char	*search_name_var(char *str);

/*   DELETE THIS   */
void	show_tokens(t_data *data);
void	show_lists(t_data *data);
/*   DELETE THIS   */

t_cmd	*lst_last_cmd(t_cmd *cmd);

#endif
