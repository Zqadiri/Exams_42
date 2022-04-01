/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:36:55 by zqadiri           #+#    #+#             */
/*   Updated: 2021/11/23 12:05:43 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
 
int	main(int argc, char *argv[], char **envp)
{
	if (argc > 1)
	{
		int 	i = 1;
		int		pids[1000];
		int		in = 0;
		int		pipe_in = 0;
		int		out = 1;
		int		pipe_fd[2];
		int		pid_index = 0;
		while (i < argc)
		{
			//!----- Parse cmd to the "|" or semi ";" -----!//
			char 	*cmds[1000];
			int		arg_nb = 0;
			while(i < argc && strncmp(argv[i], "|", 2) && strncmp(argv[i], ";", 2))
			{
				cmds[arg_nb] = argv[i];
				i++;
				arg_nb++;
			}
			cmds[arg_nb] = 0;
			//!---- Check for empty cmd ";" ";"	----!//
			if (arg_nb == 0){
				i++;
				continue;
			}
			//!---- if the cmd is a pipeline -----!//
			if (i < argc && !strncmp(argv[i], "|", 2))
			{
				pipe(pipe_fd);
				pipe_in = pipe_fd[0];
				out = pipe_fd[1];
				i++;
			}
			else
			{
				// printf ("in : %d pipe_in : %d out : %d cmd : %s\n", in, pipe_in,out, cmds[0]);
				pids[pid_index] = fork();
				if (pids[pid_index] == 0)
				{
					dup2(in, 0);
					dup2(out, 1);
					if (pipe_in != 0)
						close(pipe_in);
					if (in != 0)
						close(in);
					if (out != 1)
						close(out);
					if (!strncmp(cmds[0], "cd", 3))
					{
						if (arg_nb != 2){
							write (2, "error: cd: bad arguments\n", 25);
							// return 1;
						}
						if (chdir(cmds[1])){
							write (2, "error: cd: cannot change directory to\n", 38);
							// return 1;
						}
					}
					else if (execve(cmds[0], cmds, envp))
						exit(126);
				}
				else
				{
					if (out != 1)
						close(out);
					if (in != 0)
						close(in);
					in = pipe_in;
					pid_index++;
				}
				int status;
				if (i >= argc || (i < argc && (!strcmp(argv[i], ";"))))
				{
					// while(waitpid(-1, &status, 0) > 0)
					// 	;
					waitpid(pids[pid_index], NULL, 0);
					in = 0;
					pipe_in = 0;
					out = 1;
					i++;
				}
			}
		}
	}
}

int main (int ac, char **av, char **env)
{
	int i = 1, j,k,l;
	int p[2];
	int fd_in;
	pid_t pid;
	while (i < ac)
	{
		j = i, k = i, l = i;
		fd_in = 0;
		while (j < ac && strncmp(av[j], ";", 2))
			j++;
		while (k < j)
		{
			l = k;
			while (l < j && strncmp(av[l], "|", 2))
				l++;
			char *argv[l - k + 1];
			sub();
			pipe(p);
			if ((pid = fork()) == -1)
				return -1;
			else if (pid == 0)
			{
				dup2(fd_in, 0);
				if (l < j)
					dup2(p[1], 1);
				close (p[0]);
				if (!strncmp(argv[0], "cd", 3))
					cd(argv, l - k);
				else if (execve(argv[0], argv, env))
				{
					close (p[1]);
					close (fd_in);
					return -1;
				}
				close (p[1]);
				close (fd_in);
				return 0;
			}
			else
			{

				waitpid(pid, NULL, 0);
				close (p[1]);
				if (fd_in)
					close(fd_in);
				fd_in = p[0];
			}
			k = l + 1;
		}
		i = j +1;
		close (fd_in);
	}
	return 0;
}