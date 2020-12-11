#include "gnl.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int ret = 0;
    char *line = NULL;
    while ((ret = get_next_line(&line)) > 0)
    {
        printf("%s\n",line);
        free(line);
    }
    printf("%s",line);
    free(line);
    // system("leaks a.out");
}
