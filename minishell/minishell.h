/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:57:21 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/02 14:54:44 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int		g_code_exit;

typedef struct s_cmd
{
	int				or;
	int				pipe;
	char			*cmd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	char		*env_var;
	char		*env_name;
	char		*temp;
	int			pipe;
	int			pipe_1;
	int			or_1;
	int			or;
	int			i2;
	int			i;
	int			quote;
	int			dquote;
}				t_data;

typedef struct s_master
{
	t_cmd	*lcmd;
	char	*input;
	char	**env;
	int		print;
	int		npipe;
	int		ncmd;
	int		in;
	int		out;
}				t_master;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*trim_cmd(char *str, t_master *master, t_cmd *cmd, int i);
int		bt_unset(t_master *master, t_cmd *cur, int i2, char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		bt_echo(t_master *master, t_cmd *cur, int i, int n);
int		bt_exit(t_master *master, char *cmd, int i, int i2);
char	*expander(t_master *master, t_cmd *cmd, t_data d);
char	**get_args(char *s, t_master *master, t_cmd *cmd);
int		bt_export(t_master *master, t_cmd *cur, int i2);
int		controll_builtins(t_master *master, t_cmd *cur);
void	executor(t_master *master, char *str, int i);
char	*ft_strjoin(char const *s1, char const *s2);
char	**order(char **mt, int i, int i2, int len);
int		init_start(t_master *master, char **env);
void	gu1(int *word, char *s, int *i, char ch);
char	*program_name(char *command, char *path);
int		search_env(t_master *master, char *rule);
char	*extract_mane(t_cmd *cur, int i, int i2);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
int		controll_file(char *file, int command);
void	gu4(int *i, char *s, int *w, char **m);
void	spik_duote(int *i, char *str, char c);
char	*get_env(t_master *master, char *env);
int		bt_env(t_master *master, t_cmd *cur);
char	*get_command_f_histori(char *input);
int		bt_cd(t_master *master, t_cmd *cur);
void	ceck_pipe_fork(int *fd, pid_t *pid);
void	free_all_steoridi(t_master *master);
char	*ft_strjoin12f(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin1f(char *s1, char *s2);
char	*gu2(int *i, char *s, char ch);
int		count_pipe(char *str, char c);
int		ft_strlen(const char *string);
char	**ft_splitf(char *s, char c);
void	split_cmd(t_master *master);
int		ft_atoi(const char *string);
void	free_all(t_master *master);
int		ft_isdigit(int char_test);
int		get_a(int i, char *cmd);
char	*clear_space(char *str);
char	*get_next_line(int fd);
char	*get_command_f_0(void);
void	free_matrix(char **m);
char	*gu3(int *i, char *s);
void	here_doc(char *rule);
int		skip(int i, char *s);
char	**redirect(char **m);
bool	free_norm(char *str);
char	**copy_m(char **m);
int		ft_mlen(char **m);
int		cmmal(char **m);
char	*ft_itoa(int n);
int		bt_pwd(void);
#endif