#include "minishell.h"

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(1, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
        //printf("buf : %c\n", buf[i]);
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
    //printf("row : %d, col : %d\n", *rows, *col);
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	ft_add_line_to_his()
{
	t_list *nlist;
	nlist = g_data.history;
	if(g_data.history == NULL)
		g_data.history = ft_lstnew(ft_strdup(g_data.line));
	else
	{
		ft_lstadd_back(&g_data.history, ft_lstnew(ft_strdup(g_data.line)));
	}
}

char    *ft_print_his(int i, t_list *newlist, int work)
{
   int j = 0;

   while (newlist)
   {
       if (j == i)
       {
           return (newlist->content);
       }
       newlist = newlist->next;
       j++;
   }
	return (NULL);
}

void	up(int *count)
{
	//printf("up\n");
	//if (*line != 0)
		//ft_add_line_to_his(line);
	//printf("%d", *count);
	//printf("count : %d\n", *count);
	if (*count != 0)
	{
		(*count)--;
		// if (count == 0)
		//     count = his_count;
		g_data.line = ft_print_his(*count, g_data.history, 0);
	}
	
}

void	down(int *count, int *his_count)
{
	//printf("down\n");
	//if (*line != 0)
		//ft_add_line_to_his(line);
	//printf("count : %d\n", *count);
	if (*count < *his_count - 1)
	{
		(*count)++;
		// if (dn_count == his_count)
		//     dn_count == 0;
		g_data.line = ft_print_his(*count, g_data.history, 0);
	}
}

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
	//free(*line);
	g_data.line = ft_substr(g_data.line, 0, ft_strlen(g_data.line) - 1);
}

int		get_line(void)
{
	/* change term settings */
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	/* init termcap */
	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL); //cursor motion
	char *ce = tgetstr("ce", NULL); //clear line from cursor
	
	int c = 0;
	int row;
	int col;
	g_data.line = ft_strdup("");
	char *charater;
	char  *strtmp;
    char *tmp_free;

	while (read(0, &c, sizeof(c)) > 0)
	{
		//printf("%d\n", c);
		get_cursor_position(&col, &row);
		//col = ft_strlen(line);
		if (c == DOWN_ARROW)
		{
			down(&g_data.count, &g_data.his_count);
			strtmp = tgetstr("ce", NULL);
			write(1, "\r", 1);
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
			write(1, strtmp, strlen(strtmp));
			ft_putstr_fd(g_data.line, 1);
			//free(line);
			//line = ft_strdup("");
		}
		else if (c == UP_ARROW)
		{
			up(&g_data.count);
			//write(1, "up\n", 3);
			ft_putstr_fd(g_data.line, 1);
			//printf("%d\n",count);
			strtmp = tgetstr("ce", NULL);
			write(1, "\r", 1);
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
			write(1, strtmp, strlen(strtmp));
			ft_putstr_fd(g_data.line, 1);
			//free(line);
			//line = ft_strdup("");
		}
		else if (c == BACKSPACE)
			delete_end(&col, &row, cm, ce);
		else if (c == NEW_LINE)
		{
			write(1, "\n", 1);
			if (*(g_data.line) != 0)
			{
				ft_add_line_to_his();
				g_data.his_count++;
				g_data.count = g_data.his_count;
				//press = 0;
			}
			//free(line);
			ft_parse(g_data.line);
			//g_data.line = ft_strdup("");
			break;
		}
		else
		{
			col++;
			write(0, &c, 1);
			if (c != '\n' && ft_isprint(c))
			{
				charater = malloc(sizeof(char) * 2);
				charater[0] = (char)c;
				charater[1] = '\0';
				tmp_free = g_data.line;
				g_data.line = ft_strjoin(g_data.line, charater);
				free(tmp_free);
				free(charater);
			}
		}
		c = 0; //flush buffer
	}
	return 0;
}