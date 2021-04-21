#include "minishell.h"

int	ft_check_in2(char *tmp_in)
{
	int		j;
	int		cot;

	j = 0;
	if (tmp_in[j] == '\"' || tmp_in[j] == '\'')
	{
		cot = j++;
		while (tmp_in[j] != tmp_in[cot] && tmp_in[j] != '\0')
			j++;
	}
	else
	{
		while (tmp_in[j] != ' ' && tmp_in[j] != '\0')
			j++;
	}
	return (j);
}

int	ft_check_out(char **tmp_out)
{
	int		j;
	int		cot;

	j = 0;
	if ((*tmp_out)[0] == '>')
	{
		(*tmp_out)++;
		while ((*tmp_out)[j] == ' ' && (*tmp_out)[j] != '\0')
			j++;
		g_data.append = 1;
	}
	if (((*tmp_out)[j] == '\"' || (*tmp_out)[j] == '\''))
	{
		cot = j++;
		while ((*tmp_out)[j] != (*tmp_out)[cot] && (*tmp_out)[j] != '\0')
		{
			j++;
		}
	}
	else
	{
		while ((*tmp_out)[j] != ' ' && (*tmp_out)[j] != '\0')
			j++;
	}
	return (j);
}

void	ft_out_red_file2(char *file, char *tmp_free, int out, int priority)
{
	struct stat	path_stat;

	tmp_free = file;
	file = get_other_variables(file);
	free(tmp_free);
	tmp_free = file;
	file = remove_all_quotes(file);
	free(tmp_free);
	if (g_data.append == 0)
	{
		priority = 1;
		out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		free(file);
	}
	else
	{
		if (priority == 0 || stat(file, &path_stat))
			out = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
		free(file);
	}
	if (g_data.command->output_file > 1)
		close(g_data.command->output_file);
	g_data.command->output_file = out;
}
