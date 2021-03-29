
# include "get_next_line.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
int main()
{
	int out = open("file", O_RDWR|O_CREAT);
	dup(out);
	write(1, "a", 1);
	while (1)
	{
		printf("ok");
	}
}