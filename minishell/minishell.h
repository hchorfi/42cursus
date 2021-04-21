/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:53:07 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/21 17:00:16 by hchorfi          ###   ########.fr       */
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
	int			append;
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
** export_utils.c
*/

void	ft_print_export2(char *content, char *str_chr, char *var);
int		ft_valid_export_var(t_command *command, char *export_var, char *token, char *str);
char	*ft_get_export_var(char *exp_token);
int		ft_sort_exp_cmp(char *i_content, char *j_content);
void	ft_sort_export(void);

/*
** export_utils2.c
*/

void	ft_change(int j, char *token, char *old_var, t_list *newlist);
int		can_change(char *content, char *token, char *old_var, char *export_var);
char	*ft_get_oldvar(char *content);
void	ft_free_exist(char *str_free, char *str, char c);

/*
** env.c
*/

int				ft_env(t_command *command);
void			ft_stock_envp(char **envp);
char			**ft_get_envp();
void			ft_stock_ret(void);


/*
** unset.c
*/

int				ft_unset(t_command *command);
int				ft_chr_var(char *unset_var);
int    			ft_del_list(t_list **head, int position, t_list *curr, t_list *prev);

/*
** bin.c
*/

int				ft_exec_bin(t_command *command);
void			ft_free_d_p(char **str);
void			ft_bin(t_command *command);


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
void			ft_free_list();
void			ft_close_fd();
int				ft_strcmp(const char *s1, const char *s2);

/*
** utils2.c
*/

void	ft_putstrs_fd(char *s1, char *s2, char *s3, char *s4, char *s5);

/*
** exit.c
*/

int				ft_exit(t_command *command);

/*
** redirections.c
*/

char	*ft_check_redirections(char *pipe_cmds, int i, char *new_pipe);
void	ft_check_redirections2(char **new_pipe, int *i, char *str);
void	ft_in_red_file(char **new_pipe, char **tmp_in, int j);
char    *ft_check_in(char *pipe_cmds, char *new_pipe, char *tmp_free, int i);
void	ft_out_red_file(char *tmp_out, char **new_pipe);

/*
** redirections_utils.c
*/

int	ft_check_in2(char *tmp_in);
int	ft_check_out(char **tmp_out);
void	ft_out_red_file2(char *file, char *tmp_free, int out, int priority);

/*
** builtin_utils.c
*/

int     ft_check_builtin(t_command *command);
int     ft_exec_builtin(t_command *command);
void    ft_builtin(t_command *command);

/*
** tockens.c
*/

void    ft_prepare_tokens(t_command *command);
void    ft_new_tokens(t_command *command,int len);

int		get_line(void);
void    ft_parse(char *line);


#endif
