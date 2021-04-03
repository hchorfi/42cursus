#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "libft/libft.h"

#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108

static struct termios term, oterm;

static int getch(void);
static int kbhit(void);
static int kbesc(void);
static int kbget(void);

static int getch(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

static int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

static int kbesc(void)
{
    int c;

    if (!kbhit()) return KEY_ESCAPE;
    c = getch();
    if (c == '[') {
        switch (getch()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_LEFT;
                break;
            case 'D':
                c = KEY_RIGHT;
                break;
            default:
                c = 0;
                break;
        }
    } else {
        c = 0;
    }
    if (c == 0) while (kbhit()) getch();
    return c;
}

static int kbget(void)
{
    int c;

    c = getch();
    return (c == KEY_ESCAPE) ? kbesc() : c;
}

int main(void)
{
    int c;
    char *line;
    char *charater;
    char *tmp_free;
    t_list  *history;
    int     his_count;
    his_count = 0;
    int up_count;
    int dn_count;
    dn_count = 0;
    up_count = 0;

    line = ft_strdup("");
    history = NULL;
    while (1) {
        c = kbget();
        if (c == KEY_ESCAPE) {
            break;
        } else if (c == KEY_ENTER){
            printf("\r%s\n", line);
            if(history == NULL)
                history = ft_lstnew(ft_strdup(line));
            else
                ft_lstadd_back(&history, ft_lstnew(ft_strdup(line)));
            free(line);
            line = ft_strdup("");
            his_count++;
            up_count = his_count;
            // dn_count = 0;

            //free(line);
            //break;
        }
        else if (c == KEY_UP){
            if (up_count != 0)
            {
                up_count--;
                // if (up_count == 0)
                //     up_count = his_count;
                printf("\r%d\n", up_count);
            }
        }
        else if (c == KEY_DOWN){
            
            if (up_count < his_count)
            {
                up_count++;
                // if (dn_count == his_count)
                //     dn_count == 0;
                printf("\r%d\n", up_count);
            }
        }
        else if (c == KEY_RIGHT) {
            cursorbackward(1);
        } else if (c == KEY_LEFT) {
            cursorforward(1);
        } else {
            putchar(c);
            charater = malloc(sizeof(char) * 2);
            charater[0] = (char)c;
            charater[1] = '\0';
            tmp_free = line;
            line = ft_strjoin(line, charater);
            free(tmp_free);
            free(charater);
        }
    }
    printf("\n");
    return 0;
}