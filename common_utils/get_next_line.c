/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:30:27 by hyunahn           #+#    #+#             */
/*   Updated: 2024/04/14 16:23:13 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

char	*read_for_save(int fd, char *backup)
{
	char	*buf;
	int		err_check;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	err_check = 1;
	while (err_check && !ft_strchr(backup, '\n'))
	{
		err_check = read(fd, buf, BUFFER_SIZE);
		if (err_check == -1)
		{
			free(buf);
			buf = 0;
			return (0);
		}
		buf[err_check] = 0;
		backup = ft_strjoin(backup, buf);
	}
	free(buf);
	return (backup);
}

char	*push_arr(char *backup)
{
	int		i;
	char	*arr;

	i = 0;
	if (!backup[i])
		return (0);
	while (backup[i] && backup[i] != '\n')
		i++;
	arr = (char *)malloc((i + 2) * sizeof(char));
	if (!arr)
		return (0);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		arr[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		arr[i] = backup[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*make_new_backup(char *backup)
{
	char	*arr;
	int		i;
	int		j;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		backup = 0;
		return (0);
	}
	arr = (char *)malloc((ft_strlen(backup) - i + 1) * sizeof(char));
	if (!arr)
		return (0);
	i++;
	j = 0;
	while (backup[i])
		arr[j++] = backup[i++];
	arr[j] = '\0';
	free(backup);
	return (arr);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*arr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	backup = read_for_save(fd, backup);
	if (!backup)
		return (0);
	arr = push_arr(backup);
	backup = make_new_backup(backup);
	return (arr);
}

/*
char *lst_to_str(t_list *lst)
{
    t_list  *tmp;
    size_t  len = 0;
    char    *str;

    tmp = lst;
    while (tmp)
    {
        len += strlen(tmp->content);
        tmp = tmp->next;
    }
    str = (char *)malloc((len + 1) * sizeof(char));
    if (!str)
        return (NULL);
    str[0] = '\0';
    tmp = lst;
    while (tmp)
    {
        ft_strlcat(str, tmp->content, len + 1);
        tmp = tmp->next;
    }
    return (str);
}

char *read_for_save(int fd, t_list **backup)
{
    char    *buf;
    int     err_check;
    t_list  *node;

    buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buf)
        return (NULL);
    err_check = 1;
    while (err_check && (!*backup || !ft_strchr(lst_to_str(*backup), '\n')))
    {
        err_check = read(fd, buf, BUFFER_SIZE);
        if (err_check == -1)
        {
            free(buf);
            return (NULL);
        }
        buf[err_check] = '\0';
        node = ft_lstnew(strdup(buf));
        ft_lstadd_back(backup, node);
    }
    free(buf);
    return (lst_to_str(*backup));
}

char *push_arr(t_list *backup)
{
    char    *str;
    size_t  i = 0;

    str = lst_to_str(backup);
    if (!str || !str[0])
        return (NULL);
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        str[i + 1] = '\0';
    return (str);
}

void make_new_backup(t_list **backup)
{
    char    *str;
    size_t  i = 0;
    t_list  *node;
    t_list  *new_backup = NULL;

    str = lst_to_str(*backup);
    while (str[i] && str[i] != '\n')
        i++;
    if (!str[i])
    {
        ft_lstclear(backup, free);
        return ;
    }
    i++;
    node = ft_lstnew(strdup(&str[i]));
    ft_lstadd_back(&new_backup, node);
    ft_lstclear(backup, free);
    *backup = new_backup;
}

char *get_next_line(int fd)
{
    static t_list *backup = NULL;
    char          *arr;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!read_for_save(fd, &backup))
        return (NULL);
    arr = push_arr(backup);
    make_new_backup(&backup);
    return (arr);
}

char *get_next_line(int fd);

int	main()
{
	int	fd;
	char	*arr;
	
	fd = open("42.fdf", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((arr = get_next_line(fd)) != NULL)
	{
		printf("%s", arr); // printf("%s", arr) already includes the newline
		free(arr);
	}
	close(fd);
	return (0);
}
*/
