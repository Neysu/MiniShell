/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:11:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/09 19:17:34 by rureshet         ###   ########.fr       */
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
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\001\033[38;5;82m\002minishell >>\001\033[0m\002 "
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

/* ************************************************************************** */
/*                             STRUCTURES                                     */
/* ************************************************************************** */

typedef struct s_token
{
	char			*str;
	char			*str_backup;
	int				type;
	int				status;
	bool			join;
	bool			var_exists;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	char			*command;
	char			**cmd;
	char			*path;
	bool			pipe_output;
	int				*pipefd;
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
	int				exit_code;
	char			*working_dir;
	char			*old_working_dir;
	char			**env_list;
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
	ENV,			// 3 $ENV
	PIPE,			// 4 |
	REDIRECT_IN,	// 5 <
	REDIRECT_OUT,	// 6 >
	APPEND,			// 7 >>
	HEREDOC,		// 8 <<
	END,			// 9 '\0'
};

enum e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

/* ************************************************************************** */
/*                          SOURCES / BUILTINS                                */
/* ************************************************************************** */

/* builtins.c */
int		exec_buitlins(t_data *data, t_cmd *cmd);
/* cd.c+++ */
int		ft_cd(t_data *data, char **args);
/* echo.c++ */
int		ft_echo(t_data *data, char **args);
/* env.c */
int		print_env(t_data *data, char **args);
/* exit.c */
int		ft_exit(t_data *data, char **args);
/* export.c+ */
int		env_builtin(t_data *data, char **args);
int		ft_export(t_data *data, char **args);
/* pwd.c */
int		print_pwd(t_data *data, char **line);
/* unset.c */
int		ft_unset(t_data *data, char **args);

/* ************************************************************************** */
/*                          SOURCES / ENV                                     */
/* ************************************************************************** */

/* env_set.c+ */
bool	set_env_var(t_data *data, char *key, char *value);
bool	remove_env_var(t_data *data, int idx);
/* env_utils.c */
int		env_var_count(char **env);
int		get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);
bool	is_valid_env_var_key(char *var);

/* ************************************************************************** */
/*                          SOURCES / EXEC                                    */
/* ************************************************************************** */

/* exec_cmd.c++++ */
int		exec_cmd(t_data *data, t_cmd *cmd);
/* execute.c+++ */
bool	check_infile_outfile(t_cmd *cmd);
int		execute(t_data *data);
/* fd_utils.c */
int		ft_isspace(int c);
bool	input_is_space(char *input);
bool	create_pipes(t_data *data);
bool	set_pipe_fds(t_cmd *cmds, t_cmd *c);
/*   file_io.c   */
bool	restore_io(t_cmd *cmd);
bool	redirect_io(t_cmd *cmd);

/* ************************************************************************** */
/*                          SOURCES / LEXER                                   */
/* ************************************************************************** */

/*   envp_check.c+++   */
int		envp_check(t_token **token_list);
/* envp_handling.c */
int		var_exists(t_data *data, char *var);
int		find_env_var_index(char **env, char *var);
char	*fetch_env_var_value(char **env, char *var);
/*   envp_utils.c   */
int		var_len(char *str);
/*   lexer_utils.c   */
void	update_status(t_token **token, char c);
int		is_separator(char *str, int i);
int		check_quotes(int status, char *str, int i);
t_token	*lst_new_token(char *str, char *str_backup, int type, int status);
void	lst_addback_token(t_token **token_list, t_token *new_node);
/*   quotes_handler_utils.c++++   */
int		remove_quotes(t_token **token);
/*   quotes_handler.c+   */
int		quotes_handler(t_data *data);
/*   token_generator.c+++   */
int		token_generator(t_data *data, char *str);
/*   token_utils.c   */
bool	contains_space(char *str);
void	lstdelone_token(t_token *lst, void (*del)(void *));
void	lstclear_token(t_token **lst, void (*del)(void *));

/* ************************************************************************** */
/*                          SOURCES / PARSING                                 */
/* ************************************************************************** */

/*   args_handling.c   */
int		count_args(t_token *temp);
char	**copy_default_in_new_tab(int len, char **new_tab,
			t_cmd *last_cmd, t_token **tk_node);
void	remove_empty_var_args(t_token **tokens);
char	*join_vars(t_token **token_node);
char	**copy_in_new_tab(int len, char **new_tab,
			t_cmd *last_cmd, t_token *tmp);
/*   cmd_list_utils.c   */
void	init_cmd(t_cmd **cmd);
t_cmd	*lst_new_cmd(bool value);
void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node);
t_cmd	*lst_last_cmd(t_cmd *cmd);
/*   create_commands.c+   */
bool	remove_old_file_ref(t_cmd *cmd, bool infile);
void	create_commands(t_data *data, t_token *token);
/*   expand_variables.c   */
int		erase_var(t_token **token, char *str, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*erase_and_replace(t_token **token, char *str,
			char *var_value, int index);
/*   fill_args.c   */
int		fill_args(t_token **token_node, t_cmd *last_cmd);
/*   heredoc_utils.c   */
char	*get_new_token_str(char *oldstr, char *var_value,
			int newstr_size, int index);
int		replace_var(t_token **token_node, char *var_value, int index);
char	*replace_str_heredoc(char *str, char *var_value, int index);
bool	is_next_char_a_sep(char c);
bool	var_between_quotes(char *str, int i);
/*   heredoc_var_utils.c++   */
char	*recover_val(t_token *token, char *str, t_data *data);
/*   parse_append.c+   */
void	parse_append(t_cmd **last_cmd, t_token **token_lst);
/*   parse_heredoc.c++++   */
void	parse_heredoc(t_data *data, t_cmd **last_cmd, t_token **token_lst);
/*   parse_io.c++   */
void	set_outfile(t_token **token, t_cmd **last_cmd);
void	set_infile(t_cmd **last_cmd, t_token **token);
/*   parse_path.c++   */
char	*get_cmd_path(t_data *data, char *name);
/*   parse_pipe.c   */
void	parse_pipe(t_cmd **cmd, t_token **token_lst);
/*   parse_word.c+   */
void	parse_word(t_cmd **cmd, t_token **token_lst);
/*   parsing.c   */
bool	parser_user_input(t_data *data);
/*   signal.c   */
void	signal_reset_prompt(int signal);
void	signal_newline(int signal);
void	set_signal_interactive(void);
void	set_signal_noninteractive(void);
void	signal_ignore_sigquit(void);
/*   var_expander.c++   */
int		var_expander(t_data *data, t_token **token_lst);
char	*var_expander_heredoc(t_data *data, char *str);
bool	evaluate_heredoc_line(t_data *data, char **line, t_cmd *cmd, bool *ret);

/* ************************************************************************** */
/*                          SOURCES / UTILS                                   */
/* ************************************************************************** */

/*   cleanup.c+++   */
void	lst_clear_token(t_token **lst, void (*del)(void *));
void	lst_clear_cmd(t_cmd **lst, void (*del)(void *));
/*   errors.c+++   */
int		errmsg_cmd(char *command, char *detail,
			char *error_message, int error_nb);
void	error_message(char *text_error, char *detail, int quote);
/*   exit.c   */
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void	close_fds(t_cmd *cmds, bool close_backups);
void	exit_shell(t_data *data, int exit_code);
void	print_exit_shell(t_data *data, int exit_code);
/*   free.c   */
void	free_ptr(void *ptr);
void	free_str_tab(char **tab);
void	free_data(t_data *data, bool clear_history);
/*   init.c++   */
bool	init_data(t_data *data, char **envp);

/*   DELETE THIS   */
void	show_tokens(t_data *data);
void	show_lists(t_data *data);
/*   DELETE THIS   */

#endif
