#include <stdio.h>
#include <term.h>
#include <unistd.h>
#include <termcap.h>
#include <stdlib.h>
#include <signal.h>

int init_term()
{
    int ret;
    char *term_type = getenv("TERM");

    if (term_type == NULL)
    {
        fprintf(stderr, "TERM must be set (see 'env').\n");
        return -1;
    }

    ret = tgetent(NULL, term_type);

    if (ret == -1)
    {
        fprintf(stderr, "Could not access to the termcap database..\n");
        return -1;
    }
    else if (ret == 0)
    {
        fprintf(stderr, "Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int ret = init_term();

    /* On évite les warnings pour variables non utilisées. */
    (void)argc;
    (void)argv;

    if (ret == 0)
    {
        /* Le déroulement de notre programme se fera ici. */
    }

    return ret;
}