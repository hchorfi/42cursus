#ifndef MINISHELL_H
#define MINISHELL_H

#include "get_next_line.h"
#include "libft/libft.h"

# define POIN_VER 1

typedef struct		s_token
{
	char 			*command;
	char 			**arguments;
	int				limit;
}					t_token;
t_token				g_token;

#endif