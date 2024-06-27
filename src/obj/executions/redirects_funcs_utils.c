/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:56 by aprado            #+#    #+#             */
/*   Updated: 2024/06/27 17:46:50 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//node->fd_in
//node->fd_out
// ------------- IMPORTANTE --------------
// Essas funcoes vao apenas abrir/criar os FDs necessarios, quando ncessario.
// Elas nao vao dar dup2() em NADA agora. 
// O dup2() tem que ser feito dentro do fork()

int	heredoc_func(t_token *node, t_main *bag, int i)
{
	int		hd_fd[2];
	char	*eof;
	char	*buff;

	(void)bag;
	eof = ft_strdup(node->arr[i + 1]);
	buff = NULL;
	if (pipe(hd_fd) == -1)
		return (-1);
	while (42)
	{
		buff = readline("> ");
		if (!buff || !ft_strncmp(eof, buff, ft_strlen(buff) + 1))
			break ;
		else if (buff)
		{
			ft_putstr_fd(buff, hd_fd[1]);
			ft_putchar_fd('\n', hd_fd[1]);
			free(buff);
		}
	}
	if (buff)
		free(buff);
	close(hd_fd[1]);
	return (hd_fd[0]);
}

int	append_func(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return (-1);
	}
	fd = open(node->arr[i + 1], O_CREAT | O_RDWR | O_APPEND, 00700);
	if (fd < 0)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("No such file or directory\n", 2), -1);
	}
	return (fd);
}

int	redirect_in(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return (-1);
	}
	fd = open(node->arr[i + 1], O_RDONLY);
	if (fd < 0)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("No such file or directory\n", 2), -1);
	}
	return (fd);
	/*
	if (dup2(node->fd_in, 0) == -1)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("2- No such file or directory\n", 2));
	}
	//close(STDOUT_FILENO);
	*/
}

int	redirect_out(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return (-1);
	}
	fd = open(node->arr[i + 1], O_CREAT | O_RDWR | O_TRUNC, 00700);
	if (fd < 0)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("No such file or directory\n", 2), -1);
	}
	return (fd);
	/*
	if (dup2(node->fd_out, 1) == -1)
	{
		//FREE NAS PARADA TODA
		return (ft_putstr_fd("No such file or directory", 2));
	}
	ft_printf("END REDIR OUT\n");
	*/
}
