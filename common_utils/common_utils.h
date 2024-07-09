/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:45:02 by hyunahn           #+#    #+#             */
/*   Updated: 2024/07/09 15:45:07 by hyunahn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_UTILS_H
# define COMMON_UTILS_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char						*make_new_backup(char *backup);
char						*get_next_line(int fd);
char						*read_for_save(int fd, char *backup);
char						*push_arr(char *backup);
size_t						ft_strlen(const char *s);
char						*ft_strjoin(char *s1, char *s2);
void						ft_bzero(void *s, size_t n);
int							ft_atoi(const char *nptr);
void						*ft_calloc(size_t nmemb, size_t size);
char						*ft_strchr(const char *s, int c);
int							ft_strrstr(const char *s1, const char *s2, int len);
char						*ft_strrchr(const char *s, int n);
char						**ft_split(char const *s, char c);
void						ft_putendl_fd(char *s, int fd);

#endif
