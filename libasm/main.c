/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:31:42 by hchorfi           #+#    #+#             */
/*   Updated: 2020/12/23 11:31:45 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

void	test_strcmp(void)
{
	printf("\033[0;32mft_strcmp TEST\033[0m\n");
	char *s1 = ""; char *s2 = "";
	printf("strcmp : %d\n", strcmp(s1, s2));
	printf("ft_strcmp : %d\n", ft_strcmp(s1, s2));
	printf("strcmp : %d\n", strcmp("", ""));
	printf("ft_strcmp : %d\n", ft_strcmp("", ""));
	printf("strcmp : %d\n", strcmp("123", "123"));
	printf("ft_strcmp : %d\n", ft_strcmp("123", "123"));
	printf("ft_strcmp : %d\n", ft_strcmp("testt", "test"));
	printf("strcmp : %d\n", strcmp("testt", "test"));
	printf("ft_strcmp : %d\n", ft_strcmp("TestT", "test"));
	printf("strcmp : %d\n", strcmp("TestT", "test"));
	printf("ft_strcmp : %d\n", ft_strcmp("Te\0stT", "test"));
	printf("strcmp : %d\n", strcmp("Te\0stT", "test"));
	printf("ft_strcmp : %d\n", ft_strcmp("\200", "\0"));
	printf("strcmp : %d\n\n", strcmp("\200", "\0"));
}

void	test_write(void)
{
	printf("\033[0;32mft_write TEST\033[0m\n");
	int fd = open("file", O_RDWR | O_CREAT);
	write(1, "write : hello\n", 14);
	ft_write(1, "ft_write : hello\n\n", 18);
	write(0, "write : hello\n", 14);
	ft_write(0, "ft_write : hello\n\n", 18);
	write(fd, "write : hello\n", 14);
	ft_write(fd, "ft_write : hello\n\n", 18);
	if ((write(-4, "buf", 6) == -1))
		printf("write error : \033[1;31mERROR: %s\033[0m\n", strerror(errno));
	if ((ft_write(-4, "buf", 6) == -1))
		printf("ft_write error : \033[1;31mERROR: %s\033[0m\n\n", strerror(errno));
	if ((write(0, NULL, 6) == -1))
		printf("write error : \033[1;31mERROR: %s\033[0m\n", strerror(errno));
	if ((ft_write(0, NULL, 6) == -1))
		printf("ft_write error : \033[1;31mERROR: %s\033[0m\n\n", strerror(errno));
}

void	test_copy(void)
{
	char dst1[1000];
	char dst2[1000];
	printf("\033[0;31mMandatory TEST\033[0m\n");
	printf("\033[0;32mft_strcpy TEST\033[0m\n");
	printf("strcpy : %s \n", strcpy(dst1, ""));
	printf("ft_strcpy : %s \n\n", ft_strcpy(dst2, ""));
	printf("strcpy : %s \n", strcpy(dst1, "Lorem Ipsum is simply"));
	printf("ft_strcpy : %s \n\n", ft_strcpy(dst2, "Lorem Ipsum is simply"));
}

void	test_read(void)
{
	printf("\033[0;32mft_read TEST\033[0m\n");
	char buf[20];
	bzero(buf, 20);
	char buf2[20];
	bzero(buf2, 20);
	printf("read : %zd \n", read(0, buf, 20));
	printf("ft_read : %zd \n\n", ft_read(0, buf2, 20));
	if ((read(-4, buf, 6) == -1))
		printf("read error : \033[1;31mERROR: %s\033[0m\n", strerror(errno));
	if ((ft_read(-4, buf2, 6) == -1))
		printf("ft_read error : \033[1;31mERROR: %s\033[0m\n", strerror(errno));
}

void	test_dup(void)
{
	printf("\033[0;32mft_strdup TEST\033[0m\n\n");
	char *sdup = "There are many variations of passages of Lorem Ipsum available";
	printf("strdup : %s \n", strdup(sdup));
	printf("ft_strdup : %s \n\n", ft_strdup(sdup));
	printf("strdup : %s \n", strdup(""));
	printf("ft_strdup : %s \n\n", ft_strdup(""));
	printf("strdup : %s \n", strdup("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."));
	printf("ft_strdup : %s \n\n", ft_strdup("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."));
}

void	test_len(void)
{
	printf("\033[0;32mft_strlen TEST\033[0m\n");
	printf("ft_strlen : %lu\n", ft_strlen("hamza"));
	printf("strlen : %lu\n\n", strlen("hamza"));
	printf("ft_strlen : %lu\n", ft_strlen(""));
	printf("strlen : %lu\n\n", strlen(""));
}

int     main()
{
	test_copy();
	test_write();
	test_read();
	test_dup();
	test_strcmp();
	test_len();
	return 0;
}
