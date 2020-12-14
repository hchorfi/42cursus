#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
ssize_t ft_read(int fildes, void *buf, size_t nbyte);

int     main()
{
    //char *str1= "abc";
    //char *str2= "abd";
    char *dst = malloc(10 * sizeof (char));
    //printf("*%d*\n", strcmp("124","120"));
    //printf("*%d*\n", ft_strcmp("124","120"));
    //printf("*%s*\n", strcpy(dst,"13313213132132132313"));
    //printf("*%s*\n", strcpy(dst,"1"));
    //ssize_t l = ft_write(1, "hamza", 5);
    char *s = "12345";
    ft_write(1, s, 10);
    //ssize_t l = ft_read(0, dst, 10);
    //printf("*%zd*", l);
    return 0;
}