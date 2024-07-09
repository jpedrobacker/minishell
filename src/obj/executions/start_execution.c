/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 15:50:55 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	change_status_var(t_varenv *env, char *new_var)
{
	t_varenv	*aux_env;

	aux_env = env;
	while (aux_env)
	{
		if (ft_strcmp(aux_env->key, "?") == 0)
		{
			aux_env->var = new_var;
			return (0);
		}
		aux_env = aux_env->next;
	}
	return (1);
}

void	update_gstatus(t_varenv *env)
{
	char		*g_status_char;
	char		*status;
	t_varenv	*aux_env;
	t_varenv	*temp;

	aux_env = env;
	temp = env;
	while (temp)
	{
		if (ft_strcmp("?", temp->key) == 0)
			free(temp->var);
		temp = temp->next;
	}
	g_status_char = ft_itoa(g_status);
	status = ft_strdup(g_status_char);
	free(g_status_char);
	change_status_var(aux_env, status);
	free(status);
}

void	main_exec(t_main *main)
{
	t_token		*token;
	int			have_pipe;

	token = main->cmds;
	have_pipe = if_pipe(main);
	while (token)
	{
		if (pre_execute(token))
		{
			if (have_pipe == 1)
				exec_cmds_pipe(main, token);
			else
				call_cmd(main, token);
		}
		close_all(token);
		token = token->next;
	}
	//close_fds(main->cmds);
	//token = main->cmds;
}

void	wait_all(t_token *token)
{
	t_token	*aux;
	int		status;

	status = 0;
	if (!token)
		return ;
	aux = token;
	while (token)
	{
		if (token->pid != 0 && !our_builtins(token->cmd))
			waitpid(token->pid, &status, 0);
		token = token->next;
	}
	token = aux;
	while (token)
	{
		if (status >= 0 && !our_builtins(token->cmd))
			g_status = WEXITSTATUS(status);
		token = token->next;
	}
	return ;
}

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main);
	if (!make_pipe(main))
		ft_putstr_fd("Pipe Error.\n", 2);
	ordering_fds(main);
	//if (!ordering_fds(main))
	//	ft_putstr_fd("Use an existing file.\n", 2);
	main_exec(main);
	wait_all(main->cmds);
	//---------------------------------------------------------
	//------- PRECISAMOS JOGAR AS FUNCS DE FREE() AQUI --------
	//------------- MENOS A DE FREE_ENVP() --------------------
	//---------------------------------------------------------
	//free_all(main); O problema do unset PATH está nesta função :)
	token_free(&main->cmds);
	//so damos free na linked list envp apenas quando encerramos o programa!
	//envs_free(&bag->envs);
}
//-------------------------------------------------------------------
//---------------- feat_execution ----------------------------------
/*
int	execution(t_main *main)
{
//	t_token	*token;
	//int		have_pipe;
	///int		have_redir;

//	token = main->cmds;
	//função para prepara o pipe
	//have_pipe = 0;

	if (!check_builtins(main))
		call_cmd(main);
	else
		return (-1);
		//função para fechar fds abrangendo o pipe
		//função para chamar o proximo pipe
	return (0);
}

void	test_execution(t_main *bag)
{
	(void)bag;
	pid_t	pid;
	char	*s[] = {"cat", NULL};

	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork Error\n", 2);
	if (pid == 0)
	{
		ft_printf("processo forkado\n");
		bag->cmds->fd_in = open(bag->cmds->arr[1], O_RDONLY);
		bag->cmds->fd_out = open(bag->cmds->arr[4], O_CREAT | O_RDWR | O_TRUNC, 00700);
		if (dup2(bag->cmds->fd_in, 0) == -1)
			ft_putstr_fd("TESTE\n", 2);
		if (dup2(bag->cmds->fd_out, 1) == -1)
			ft_putstr_fd("TESTE\n", 2);
		execve("/usr/bin/cat", s, NULL);
	}
	else
		waitpid(pid, NULL, 0);
	close(bag->cmds->fd_in);
	close(bag->cmds->fd_out);
}

void	begin_exec(t_main *bag)
{
	t_token	*aux;
	pid_t		pid;
	int			fd[2];
	int			node;

	aux = bag->cmds;
	node = 0;
	while (aux)
	{
		if (!aux->next && node == 0)
		{
			pid = fork();
			if (pid < 0)
				break ; // ERROR, preciso dar free em tudo
			if (pid == 0)
			{
				if (aux->fd_in != 0)
					if (dup2(aux->fd_in, READ_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				if (aux->fd_out != 0)
					if (dup2(aux->fd_out, WRITE_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				//if (for nossos builtins) = manda pra eles
				//else = manda pro execve
				execve(aux->real_path, aux->args, NULL);
			}
			else
				waitpid(pid, NULL, 0);
		}
		else
		{
			if (pipe(fd) == -1)
				break ; // ERROR, PRECISO DAR FREE EM TUDO
			if ((pid = fork()) < 0)
				break ; // ERROR, PRECISO DAR FREE EM TUDO
			if (pid == 0) //CHILD PROCESS
			{
				if (aux->fd_in != 0)
				{
					if (dup2(aux->fd_in, READ_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				}
				else if (node != 0)
					if (dup2(fd[0], READ_END) == -1)
						ft_putstr_fd("Error\n", 2);
				if (aux->fd_out != 0)
				{
					if (dup2(aux->fd_out, WRITE_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				}
				else if (node != 0)
					if (dup2(fd[1], WRITE_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				//if (for nossos builtins) = manda pra eles
				//else = manda pro execve
				execve(aux->real_path, aux->args, NULL);
			}
			else
			{
				waitpid(pid, NULL, 0);
				//close(fd[1]);
			}
			//CLOSE FDS NECESSARIOS
		}
		node++;
		aux = aux->next;
	}
}

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main); // Todas as estruturas estao organizadas aqui...
	ordering_fds(main); // Agora, faremos a mudanca dos fds...
	begin_exec(main); // Agora, faremos o inicio da execucao...

	//testing redirecting FDs
	//test_execution(main);

	//execution(main);
	//waitpid dos comandos
	//free do token
}
*/
