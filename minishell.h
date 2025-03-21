/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:11:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/21 16:27:50 by rureshet         ###   ########.fr       */
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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERRORCMD "minishell : %s: unknown command\n"
# define UNSETARGS "unset: not enough args"
# define PATH_MAX_LEN 4096

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
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_cmd
{
	char			**cmd;
	int				pipefd[2];
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_data
{
	char			*user_input;
	bool			work;
	t_envp			*envp;
	t_token			*token;
	t_cmd			*cmd;
}					t_data;


enum				e_token_type{
	SPACES = 1,
	WORD,			// command or argument
	ENV,			// env $
	PIPE,			// pipe (|)
	REDIRECT_IN,	// <
	REDIRECT_OUT,	// >
	APPEND,			// <<
	HEREDOC,		// >>
	END
};

enum				e_quoting_status{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

t_envp	*get_env(char **envp);
t_envp	*ft_lstnsave_word_or_sepew_env(char *envp);

size_t	ft_envsize(t_envp *env);

int		ft_echo(char *line);

int		print_pwd(char *line);
int		print_env(t_envp *envp);
int		change_dirs(t_envp *envp, char *line);
int		ft_unset(char *line, t_envp *envp_data);
int		exec_cmd(t_cmd *cmd_data, t_envp *envp);
int		exec_buitlins(char *line, t_envp *env_data);

char	*findcmd(t_cmd *cmd_data, t_envp *envp);

char	**env_to_str(t_envp *envp);

void	ft_lstadd_back(t_envp **lst, char *envp);

/*   utils/errors.c   */
void	error_message(char *text_error);

/*   parsing/lexer.c   */
int		token_generator(t_data *data, char *str);

/*   parsing/parsing.c   */
int		is_builtin(char *line);
t_cmd	*create_cmd(int type, char *cmd);
t_cmd	*parsing(char *line);
bool	parser_user_input(t_data *data);

#endif
