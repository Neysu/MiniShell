/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:11:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/24 23:31:16 by egibeaux         ###   ########.fr       */
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

typedef struct		s_cmd
{
	char			**cmd;
	char			*file;
	int				pipefd[2];
	int				outfile;
	int				infile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

enum				e_token_type
{
	SPACES = 1, 
	WORD,			// 2 WORD
	ENV,			// 3 $
	PIPE,			// 4 |
	REDIRECT_IN,	// 5 <
	REDIRECT_OUT,	// 6 >
	APPEND,			// 7 <<
	HEREDOC,		// 8 >>
	END				// 9 '\0'
};

enum				e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

typedef struct		s_data
{
	char			*user_input;
	bool			work;
	int				ret;
	t_envp			*env_data;
	t_cmd			*cmd_data;
}					t_data;

t_cmd	*parse_cmd(char *line);

t_envp	*get_env(char **envp);
t_envp	*ft_lstnew_env(char *envp);

size_t	ft_envsize(t_envp *env);


int		is_builtin(char *line);
int		exec_buitlins(char *line, t_data *data);

int		print_pwd(char *line);
int		print_env(t_envp *envp);
int		ft_echo(char *line, t_data *data);
int		ft_exit(char *line, t_data *data);
int		change_dirs(t_envp *envp, char *line);
int		ft_unset(char *line, t_envp *envp_data);
int		ft_export(char *line, t_envp *envp_data);

int		exec_cmd(t_cmd *cmd_data, t_envp *envp);

int		redirect_out(t_cmd *cmd_data);
int		redirect_inf(t_cmd *cmd_data);
int		open_out(char *file, t_cmd *cmd_data);
int		open_inf(char *file, t_cmd *cmd_data);


char	*findcmd(t_cmd *cmd_data, t_envp *envp);

char	**env_to_str(t_envp *envp);

void	error_path(char *s);
void	ft_free_env(t_envp *envp);
void	ft_lstadd_back_env(t_envp **lst, char *envp);

#endif
