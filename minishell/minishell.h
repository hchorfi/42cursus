#ifndef MINISHELL_H
#define MINISHELL_H

#include "get_next_line.h"
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

# define POIN_VER 1

typedef	struct 	s_data
{
	t_list		*env_var;
}				t_data;
t_data			g_data;

typedef struct s_command
{
    char **tokens;
    char **input_files;
    char **output_files; 

}				t_command;
t_command		g_command;

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

int     ft_valid_export_var(char *export_var);
int     ft_exist_export_var(char *export_var);
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

int     ft_check_bin();

/*
** main.c
*/

int     ft_exec();
void    ft_parse(char *line);
int     ft_prompt();
void    ft_stock_envp(char **envp);

#endif