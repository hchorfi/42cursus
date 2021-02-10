#ifndef MINISHELL_H
#define MINISHELL_H

#include "get_next_line.h"
#include "libft/libft.h"
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


#endif