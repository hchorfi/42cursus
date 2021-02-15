#ifndef MINISHELL_H
#define MINISHELL_H

#include "get_next_line.h"
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/wait.h>

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

int ft_unset();

/*
** main.c
*/

int     ft_exec();
void    ft_parse(char *line);
int     ft_prompt();
void    ft_stock_envp(char **envp);

#endif