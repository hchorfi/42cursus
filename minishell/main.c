/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:39:14 by devza             #+#    #+#             */
/*   Updated: 2021/04/27 12:31:35 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse2(int i, int j, char *pipe_cmd)
{
	char	*new_pipe;
	char	*tmp_free;
	int		k;

	g_data.command = malloc(sizeof * g_data.command);
	g_data.command->block = i;
	g_data.command->pipe_pos = j;
	new_pipe = ft_check_redirections(pipe_cmd, 0, ft_strdup(""));
	g_data.command->tokens = ft_split_pars(new_pipe, ' ');
	free(new_pipe);
	k = 0;
	while (g_data.command->tokens[k])
	{
		tmp_free = g_data.command->tokens[k];
		g_data.command->tokens[k] = ft_strtrim(g_data.command->tokens[k], " ");
		free(tmp_free);
		k++;
	}
	g_data.command->n_tokens = k;
	if (g_data.cmds == NULL)
		g_data.cmds = ft_lstnew(g_data.command);
	else
		ft_lstadd_back(&g_data.cmds, ft_lstnew(g_data.command));
}

void	ft_parse(char *line, int j, int i)
{
	char	**cmds;
	char	**pipe_cmds;
	int		*npipe;

	cmds = ft_split_pars(line, ';');
	while (cmds[i])
	{
		pipe_cmds = ft_split_pars(cmds[i], '|');
		j = 0;
		while (pipe_cmds[j])
		{
			ft_parse2(i, j, pipe_cmds[j]);
			j++;
		}
		ft_free_d_p(pipe_cmds);
		npipe = malloc(sizeof(int));
		*npipe = j - 1;
		if (g_data.n_pipe_cmd == NULL)
			g_data.n_pipe_cmd = ft_lstnew(npipe);
		else
			ft_lstadd_back(&g_data.n_pipe_cmd, ft_lstnew(npipe));
		i++;
	}
	ft_free_d_p(cmds);
}

int	ft_check_syntax(char *line)
{
	if (*line == '|' || *line == ';')
	{
		ft_printf("syn err\n");
		return (1);
	}
	return (0);
}

int	ft_prompt(int argc, char **argv)
{
	if (argc >= 2)
	{
		g_data.line = argv[2];
		ft_parse(g_data.line, 0, 0);
	}
	else
	{
		if (g_data.ret == 0)
		{
			ft_printf("\033[0;32m");
			ft_printf("minishell 👽 %d > ", g_data.ret);
			ft_printf("\033[0m");
		}
		else
		{
			ft_printf("\033[0;31m");
			ft_printf("minishell 👽 %d > ", g_data.ret);
			ft_printf("\033[0m");
		}
		get_line();
		//get_next_line(1, &g_data.line);
	}
	//if (!ft_check_syntax(g_data.line))
		//ft_parse(g_data.line, 0, 0);
	//if (argc < 2)
		//free(g_data.line);
	return (0);
}

void	sighandler(int dummy)
{
	if (g_data.n_fork == 0)
	{
		//ft_printf("%d\n", g_data.ret);
		ft_printf("\n");
		ft_printf("\033[0;32m");
		// if (g_data.ret == 130)
		//     g_data.ret = 130;
		// else
		//     g_data.ret = 1;
		ft_printf("minishell 👽 %d > ", g_data.ret = 1);
		ft_printf("\033[0m");
	}
	else
	{
		ft_printf("\n");
		g_data.ret = 130;
	}
}

int	check_input(t_list *newlist, int j)
{
	while (newlist && (((t_command *)newlist->content)->block == j))
	{
		if (((t_command *)newlist->content)->input_file == -1)
		{
			g_data.ret = 1;
			return (-1);
		}
		newlist = newlist->next;
	}
	return (j);
}

void	ft_exec(t_command *command)
{
	int	*tmp;

	ft_prepare_tokens(command, 0, 0);
	if (command->pipe_pos != g_data.num_pipes && g_data.num_pipes > 0)
		pipe(g_data.fd);
	if (ft_check_builtin(command))
		ft_builtin(command);
	else if (command->tokens[0] != NULL && command->tokens[0][0] != '\0')
		ft_bin(command);
	if (g_data.num_pipes > 0)
	{
		close(g_data.fd[1]);
		g_data.fdd = g_data.fd[0];
		tmp = malloc(sizeof(int));
		*tmp = g_data.fdd;
		ft_lstadd_back(&g_data.fd_close, ft_lstnew(tmp));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*newlist;
	t_list		*pipe_list;
	t_command	*command;
	int			j;

	ft_stock_envp(envp);
	g_data.ret = 0;
	g_data.count = 0;
	g_data.his_count = 0;
	//signal(SIGQUIT, intHandler);
	while (1)
	{
		signal(SIGINT, sighandler);
		j = ft_prompt(argc, argv);
		newlist = g_data.cmds;
		pipe_list = g_data.n_pipe_cmd;
		while (pipe_list)
		{
			ft_stock_ret();
			g_data.num_pipes = *(int *)pipe_list->content;
			g_data.fdd = 0;
			g_data.n_fork = 0;
			g_data.fd[0] = 0;
			g_data.fd[1] = 1;
			while (newlist && (((t_command *)newlist->content)->block == j))
			{
				command = (t_command *)newlist->content;
				if (check_input(g_data.cmds, j) != -1)
					ft_exec(command);
				newlist = newlist->next;
			}
			ft_close_fd();
			while (g_data.n_fork > 0)
			{
				wait(&g_data.ret);
				g_data.ret /= 256;
				g_data.n_fork--;
			}
			pipe_list = pipe_list->next;
			j++;
		}
		if (argc >= 2)
		{
			argc = 0;
			return (g_data.ret);
		}
		ft_free_list();
	}
	return (0);
}
