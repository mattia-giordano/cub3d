/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:52:39 by mgiordan          #+#    #+#             */
/*   Updated: 2021/03/17 12:52:42 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

short	ft_strcmp(char *str1, char *str2);
short	ft_check_ext(char *file_path, char *ext);
char	*ft_strjoin(char *str1, char *str2);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_gnl(int fd, char **line);
short	ft_is_in_string(char c, char *str);
int		ft_atoi(char *num, int *i);
char	*ft_itoa(int n);

#endif
