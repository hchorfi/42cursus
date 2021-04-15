#include "minishell.h"

void	ft_free_d_p(char **str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	while (len >= 0)
	{
		free(str[len]);
		len--;
	}
	free(str);
}

int     ft_strchr_set(char *str, char *set, char *token)
{
    int     i;
    int     j;

    i = 0;
    while (str[i] != '\0')
    {
        j = 0;
        while (set[j] != '\0')
        {
            if (str[i] == set[j])
            {
                if (str[i] == '+' && token[i + 1] !='\0' && token[i + 1] == '=')
                {
                    j++;
                    continue;
                }
                else
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

