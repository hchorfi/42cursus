#ifndef MINISHELL_H
#define MINISHELL_H

#include "get_next_line.h"
#include "libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <signal.h> 


# define POIN_VER 1

typedef	struct 	s_data
{
	t_list		*env_var;
    t_list      *cmds;
    t_list      *n_pipe_cmd;
    int         ret;
}				t_data;
t_data			g_data;

typedef struct s_command
{
    char        **tokens;
    int         n_tokens;
    int         input_file;
    int         output_file;
    int         pipe_pos;
    int         block; 
}				t_command;
t_command		*g_command;


/*
** echo.c
*/

int				ft_echo();

/*
** split.c
*/

char		**ft_split_pars(char *s, char c);
char		*get_other_variables(char *str);
char		*remove_all_quotes(char *str);

/*
** cd.c
*/

int     ft_cd();

/*
** pwd.c
*/

int     ft_pwd();

/*
** export.c
*/

int     ft_valid_export_var(char *export_var, char *token, char *str);
int     ft_exist_export_var(char *export_var, char *token);
char    *ft_get_export_var(char *exp_token);
int     ft_export();

/*
** env.c
*/

int     ft_env();

/*
** unset.c
*/

int     ft_unset();
int     ft_valid_unset_var(char *unset_var);
int		ft_chr_var(char *unset_var);
int     ft_del_list(t_list **head, int position);

/*
** bin.c
*/

int		ft_exec_bin(void *cmd);

/*
** echo.c
*/

int		is_quote(char c);

/*
** main.c
*/

int     ft_exec();
void    ft_parse(char *line);
int     ft_prompt();
void    ft_stock_envp(char **envp);

/*
** exit.c
*/

int     ft_exit();

#endif