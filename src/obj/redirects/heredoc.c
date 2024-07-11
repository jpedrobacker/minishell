/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:57:36 by aprado            #+#    #+#             */
/*   Updated: 2024/07/11 14:11:56 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_int_heredoc_handle(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		g_status = 130;
		exit(g_status);
	}
	else
	{
		write(1, "> ", 2);
		ioctl(1, TIOCSTI, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	core_heredoc(int fd_in, char *limiter)
{
	char	*buff;
	char	*eof;

	buff = NULL;
	eof = ft_strdup(limiter);
	while (42)
	{
		buff = readline("> ");
		if (!buff || !ft_strncmp(eof, buff, ft_strlen(buff) + 1))
			break ;
		else if (buff)
		{
			ft_putendl_fd(buff, fd_in);
			free(buff);
		}
	}
	if (buff)
		free(buff);
}

int	heredoc_func(t_token *node, t_main *bag, int i)
{
	pid_t	hd_pid;
	int		hd_fd[2];
	int		status;

	if (pipe(hd_fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	hd_pid = fork();
	(void)bag;
	if (hd_pid == 0)
	{
		close(hd_fd[0]);
		signal(SIGINT, &sig_int_heredoc_handle);
		core_heredoc(hd_fd[1], node->arr[i + 1]);
		close(hd_fd[1]);
		exit(1);
	}
	waitpid(hd_pid, &status, 0);
	close(hd_fd[1]);
	g_status = WEXITSTATUS(status);
	if (g_status == 130)
		return (-1);
	return (hd_fd[0]);
}

/*
int	heredoc_func(t_token *node, t_main *bag, int i)
{
	pid_t	hd_pid;
	int		hd_fd[2];
	char	*eof;
	char	*buff;
	int		status;

	if (pipe(hd_fd) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	hd_pid = fork();
	(void)bag;
	if (hd_pid == 0)
	{
		close(hd_fd[0]);
		eof = ft_strdup(node->arr[i + 1]);
		buff = NULL;
		signal(SIGINT, &sig_int_heredoc_handle);
		core_heredoc(hd_fd[1], node->arr[i + 1]);
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
		exit(1);
	}
	waitpid(hd_pid, &status, 0);
	close(hd_fd[1]);
	g_status = WEXITSTATUS(status);
	if (g_status == 130)
		return (-1);
	return (hd_fd[0]);
}
*/
