#include "minishell.h"

void	ft_putstrs_fd(char *s1, char *s2, char *s3, char *s4, char *s5)
{
	if (s1 != NULL)
		ft_putstr_fd(s1, 2);
	if (s2 != NULL)
		ft_putstr_fd(s2, 2);
	if (s3 != NULL)
		ft_putstr_fd(s3, 2);
	if (s4 != NULL)
		ft_putstr_fd(s4, 2);
	if (s5 != NULL)
		ft_putstr_fd(s5, 2);
}