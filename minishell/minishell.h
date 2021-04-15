/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:53:07 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/15 13:17:27 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>

# define BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define NEW_LINE 10


typedef struct	s_command
{
	char		**tokens;
	int			n_tokens;
	int			input_file;
	int			output_file;
	int			pipe_pos;
	int			block;
}				t_command;

typedef struct	s_data
{
	t_list		*env_var;
	t_list		*history;
	t_list		*cmds;            //all commands
	t_list		*n_pipe_cmd;
	t_list		*fd_close;
	t_command	*command;         //one pipe lina or command
	int			ret;
	int			fd[2];
	int			fdd;
	int			num_pipes;
	int			n_fork;
	char		*line;
	int 		count;
	int     	his_count;
}				t_data;
t_data			g_data;

/*
** echo.c
*/

int				ft_echo(t_command *command);
int				is_quote(char c);

/*
** split.c
*/

char			**ft_split_pars(char *s, char c);
char			*get_other_variables(char *str);
char			*remove_all_quotes(char *str);
char			*ft_remove_slashes(char *str, int start, int end);


char	**csplit(const char *s, char c);


/*
** cd.c
*/

int				ft_cd(t_command *command);

/*
** pwd.c
*/

int				ft_pwd(void);

/*
** export.c
*/

int				ft_valid_export_var(t_command *command, char *export_var, char *token, char *str);
int				ft_exist_export_var(char *export_var, char *token);
char			*ft_get_export_var(char *exp_token);
int				ft_export(t_command *command);

/*
** env.c
*/

int				ft_env(t_command *command);

/*
** unset.c
*/

int				ft_unset();
int				ft_valid_unset_var(char *unset_var);
int				ft_chr_var(char *unset_var);
int				ft_del_list(t_list **head, int position);

/*
** bin.c
*/

int				ft_exec_bin(t_command *command);
void			ft_free_d_p(char **str);

/*
** main.c
*/

int				ft_exec(void);
void			ft_parse(char *line);
int				ft_prompt(int argc, char **argv);
void			ft_stock_envp(char **envp);

/*
** utils1.c
*/

int				ft_strchr_set(char *str, char *set, char *token);
void			ft_free_d_p(char **str);

/*
** exit.c
*/

/*
** redirections.c
*/

char    *ft_check_redirections(char *pipe_cmds);
char    *ft_check_in(char *pipe_cmds);


int				ft_exit(t_command *command);


int		get_line(void);
void    ft_parse(char *line);


#endif
