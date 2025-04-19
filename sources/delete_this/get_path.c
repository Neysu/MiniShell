// char	*get_path()
// {
// 	char	**folders;
// 	char	*path;
// 	char	*pos;
// 	char	*tmp;
// 	int		len;

// 	path = ft_calloc(sizeof(char), PATH_MAX_LEN);
// 	getcwd(path, PATH_MAX_LEN);
// 	folders = ft_split(path, '/');
// 	len = ft_arrlen(folders);
// 	tmp = ft_strjoin(PROMPT1, folders[len - 1]);
// 	pos = ft_strjoin(tmp, PROMPT2);
// 	free(tmp);
// 	ft_free_arr(folders);
// 	free(path);
// 	return (pos);
// }
