#include "minishell.h"

int	len;

int	nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows, int a, int i)
{
	char	buf[255];
	int		ret;
	int		temp;

	write(1, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int	putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	ft_add_line_to_his(void)
{
	t_list	*prev;
	t_list	*tail;
	t_list	*newlist;

	if (ft_lstsize(g_data.history) == 1)
	{
		ft_lstadd_front(&g_data.history, ft_lstnew(ft_strdup(g_data.line)));
		g_data.history->prev = NULL;
		ft_lstlast(g_data.history)->prev = g_data.history;
	}
	else if (ft_lstsize(g_data.history) > 1)
	{
		tail = ft_lstlast(g_data.history);
		prev = ft_lstlast(g_data.history)->prev;
		newlist = ft_lstnew(ft_strdup(g_data.line));
		newlist->next = prev->next;
		prev->next = newlist;
		newlist->prev = prev;
		newlist->next->prev = newlist;
	}
}

void	delete_end(int *col, int *row)
{
	char	*tmp_free;
	//ft_putstr(g_data.line);
	// if (*row == g_data.init_row)
	// 	len = 17;
	// if ((*col > len && *row > g_data.init_row) || *col > len)
	// {
	// 	--(*col);
	// 	write(1, tgetstr("le", NULL), ft_strlen(tgetstr("le", NULL)));
	// 	tputs(tgetstr("ce", NULL), 1, putchar_tc);
	// }
	// else if (*row > g_data.init_row)
	// {
	// 	(*row)--;
	// 	write(1, tgetstr("up", NULL), ft_strlen(tgetstr("up", NULL)));
	// 	*col = 0;
	// 	while (*col < tgetnum("co"))
	// 	{
	// 		write(1, tgetstr("nd", NULL), ft_strlen(tgetstr("nd", NULL)));
	// 		(*col)++;
	// 	}
	// }

	if (ft_strlen(g_data.line) > 0)
	{
		if (*col > tgetnum("co"))
			*col = *col % tgetnum("co");
		if (*col > 0)
			(*col)--;
		if (*col == 0)
		{
			write(1, tgetstr("le", NULL), ft_strlen(tgetstr("le", NULL)));
			tputs(tgetstr("ce", NULL), 1, putchar_tc);
			write(1, tgetstr("up", NULL), ft_strlen(tgetstr("up", NULL)));
			while (*col < tgetnum("co"))
			{
				write(1, tgetstr("nd", NULL), ft_strlen(tgetstr("nd", NULL)));
				(*col)++;
			}
		}
		else
		{
			write(1, tgetstr("le", NULL), ft_strlen(tgetstr("le", NULL)));
			tputs(tgetstr("ce", NULL), 1, putchar_tc);
		}
		g_data.line[ft_strlen(g_data.line) - 1] = '\0';
	}
}

void	ft_print_list()
{
	t_list *list = g_data.history;

	while(list)
	{
		ft_printf("----\nprev : %p\nnode : |%s| - %p\nnext : %p\n----\n", list->prev, list->content, list, list->next);
		list = list->next;
	}
}


void	ft_init_term(void)
{
	tcgetattr(STDIN_FILENO, &g_data.orig_term);
	g_data.term = g_data.orig_term;
	g_data.term.c_lflag &= ~ICANON;
	g_data.term.c_lflag &= ~ECHO;
	g_data.term.c_cc[VMIN] = 1;
	g_data.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data.term);
	tgetent(NULL, "xterm");
}

void	down_key()
{
	char	*tmp_free;

	if (g_data.term_list && g_data.term_list->next)
	{
		write(1, "\r", 1);
		if (g_data.ret == 0)
		{
			ft_printf("\033[0;32m");
			ft_printf("minishell 👽 > ");
			ft_printf("\033[0m");
		}
		else
		{
			ft_printf("\033[0;31m");
			ft_printf("minishell 👽 > ");
			ft_printf("\033[0m");
		}
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		g_data.term_list = g_data.term_list->next;
		tmp_free = g_data.line;
		g_data.line = ft_strdup(g_data.term_list->content);
		free(tmp_free);
		ft_putstr_fd(g_data.line, 1);
	}
}

void	up_key()
{
	char *tmp_free;
	if (!g_data.press)
	{
		g_data.press = 1;
		tmp_free = ft_lstlast(g_data.history)->content;
		ft_lstlast(g_data.history)->content = ft_strdup(g_data.line);
		free(tmp_free);
	}
	if (g_data.term_list && g_data.term_list->prev)
	{
		write(1, "\r", 1);
		if (g_data.ret == 0)
		{
			ft_printf("\033[0;32m");
			ft_printf("minishell 👽 > ");
			ft_printf("\033[0m");
		}
		else
		{
			ft_printf("\033[0;31m");
			ft_printf("minishell 👽 > ");
			ft_printf("\033[0m");
		}
		write(1, tgetstr("ce", NULL), strlen(tgetstr("ce", NULL)));
		g_data.term_list = g_data.term_list->prev;
		tmp_free = g_data.line;
		g_data.line = ft_strdup(g_data.term_list->content);
		free(tmp_free);
		ft_putstr_fd(g_data.line, 1);
	}	
}

int		get_line(void)
{
	len = 17;
	ft_init_term();
	int c = 0;
	int row;
	int col;
	g_data.line = ft_strdup("");
	char *charater;
	char  *strtmp;
    char *tmp_free;
	char *tmp_line;
	g_data.term_list = ft_lstlast(g_data.history);
	g_data.press = 0;
	if (!ft_lstsize(g_data.history))
	{
		g_data.history = ft_lstnew(ft_strdup(""));
		g_data.history->prev = NULL;
	}
	//get_cursor_position(&col, &row, 0, 1);
	g_data.init_row = row;
	col = 16;
	while (read(0, &c, sizeof(c)) > 0)
	{
		//get_cursor_position(&col, &row, 0, 1);	
		if (c == DOWN_ARROW)
		{
			down_key();
			if (ft_strlen(g_data.line))
				col = ft_strlen(g_data.line) + 16;
			else
				col = 16;
		}
		else if (c == UP_ARROW)
		{
			up_key();
			if (ft_strlen(g_data.line))
				col = ft_strlen(g_data.line) + 16;
			else
				col = 16;
		}
		else if (c == BACKSPACE)
		{
			g_data.press = 0;
			delete_end(&col, &row);
		}
		else if (c == CTRLD)
		{
			if (g_data.line && ft_strlen(g_data.line) == 0)
			{
				ft_putstr_fd("exit\n", 2);
				exit(0);
			}
		}
		else if (c == NEW_LINE)
		{
			write(1, "\n", 1);
			g_data.press = 0;
			if (*(g_data.line) != 0)
			{
				ft_add_line_to_his();
				g_data.term_list = ft_lstlast(g_data.history);
			}
			if (*(g_data.line) != 0)
			{
				if (!ft_check_syntax(g_data.line))
					ft_parse(g_data.line, 0, 0);	
			}
			// ft_print_list();
			//ft_putnbr_fd(col, 2);
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_data.orig_term);
			break;
		}
		else
		{
			g_data.press = 0;
			if (c != '\n' && ft_isprint(c))
			{
				//if (col == 0 && row == tgetnum("li"))
					//g_data.init_row--;
				write(0, &c, 1);
				if (col == tgetnum("co"))
				{	
					//row++;
					write(1, tgetstr("do", NULL), ft_strlen(tgetstr("do", NULL)));
					col = 1;
					//len = 0;
				}
				else
					col++;
				charater = malloc(sizeof(char) * 2);
				charater[0] = (char)c;
				charater[1] = '\0';
				tmp_free = g_data.line;
				g_data.line = ft_strjoin(g_data.line, charater);
				tmp_line = g_data.line;
				free(tmp_free);
				free(charater);
			}
		}
		c = 0;
	}
	return 0;
}