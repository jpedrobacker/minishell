/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:22:56 by aprado            #+#    #+#             */
/*   Updated: 2024/07/07 16:39:18 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//node->fd_in
//node->fd_out
// ------------- IMPORTANTE --------------
// Essas funcoes vao apenas abrir/criar os FDs necessarios, quando ncessario.
// Elas nao vao dar dup2() em NADA agora.
// O dup2() tem que ser feito dentro do fork()

void	sig_int_heredoc_handle(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_DFL);
		exit(EXIT_SUCCESS);
	}
	else
	{
		write(1, "> ", 2);
		ioctl(1, TIOCSTI, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

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
	signal(SIGINT, &sig_int_heredoc_handle);
	while (42)
	{
		buff = readline("> ");
		if (!buff || !ft_strncmp(eof, buff, ft_strlen(buff) + 1))
			break ;
		else if (buff)
		{
			ft_putendl_fd(buff, hd_fd[1]);
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
	fd = 0;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return (-1);
	}
	fd = open(node->arr[i + 1], O_CREAT | O_RDWR | O_APPEND, 00777);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		write(2, node->arr[i + 1], ft_strlen(node->arr[i + 1]));
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}

int	redirect_in(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	fd = 0;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return (-1);
	}
	if (!access(node->arr[i + 1], F_OK | R_OK))
		fd = open(node->arr[i + 1], O_RDONLY);
	else
		fd = -1;
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		write(2, node->arr[i + 1], ft_strlen(node->arr[i + 1]));
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}

int	redirect_out(t_token *node, t_main *bag, int i)
{
	int	fd;

	(void)bag;
	fd = 0;
	if (!node->arr[i + 1])
	{
		//FREE NAS PARADA TODA
		return (-1);
	}
	fd = open(node->arr[i + 1], O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		write(2, node->arr[i + 1], ft_strlen(node->arr[i + 1]));
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}
