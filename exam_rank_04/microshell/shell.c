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
			while(i < argc && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			{
				cmds[arg_nb] = argv[i];
				i++;
				arg_nb++;
			}
			cmds[arg_nb] = 0;
			//!---- Check for empty cmd ";" ";"	----!//
			if (arg_nb == 0)
			{
				i++;
				continue;
			}
			//!---- if the cmd is a pipeline -----!//
			if (i < argc && !strcmp(argv[i], "|"))
			{
				pipe(pipe_fd);
				pipe_in = pipe_fd[0];
				out = pipe_fd[1];
				i++;
			}
			if (!strcmp(cmds[0], "cd"))
				puts("cd");
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
					if (execve(cmds[0], cmds, envp))
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
					while(waitpid(-1, &status, 0) > 0)
					{
						// waitpid(pids[pid_index], 0, 0);
						// pid_index--;
					}
					in = 0;
					pipe_in = 0;
					out = 1;
					i++;
				}
			}
		}
	}
}
