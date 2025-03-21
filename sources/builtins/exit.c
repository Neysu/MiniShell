#include "../../minishell.h"

int		ft_exit(char *line)
{
	char	**args;
	int		ret;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) > 2)
	{
		ft_putendl_fd("minishell: exit: too many args", 2);
		return (1);
	}
	else if (ft_arrlen(args) == 2)
	{
		ft_putendl_fd("exit", 1);
		ret = ft_atol(args[1]);
		if (ret < 1 || ret > 255)
			exit(0);
		else
			exit(ret);
	}
	else
		exit(0);
	return (0);
}
