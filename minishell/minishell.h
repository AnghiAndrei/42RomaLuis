/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:57:21 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/05 12:19:58 by aanghi           ###   ########.fr       */
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

# define STRERROR "02: What command did you give me, darling?\n"

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
	char		*temp;
	char		*temp2;
	int			i2;
	char		*env_var;
	char		*env_name;
	int			pipe;
	int			pipe_1;
	int			or_1;
	int			or;
	int			i;
	int			quote;
	int			dquote;
}				t_data;

typedef struct s_data2
{
	char		**arg;
	char		*t1;
	char		*t2;
	int			i;
}				t_data2;

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

void	check_pipe_fork(t_master *master, t_cmd *cur, int *fd, pid_t *pid);
int		bt_cd(t_master *master, t_cmd *cur, char *home, char **arg);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		bt_unset(t_master *master, t_cmd *cur, int i2, char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		bt_echo(t_master *master, t_cmd *cur, int i, int n);
void	bt4s_export(t_master *mast, t_cmd *cur, t_data2 *d);
int		bt_exit(t_master *master, char *cmd, int i, int i2);
int		bt_export(t_master *master, t_cmd *cur, t_data2 d);
char	*expander(t_master *master, t_cmd *cmd, t_data d);
char	**get_args(char *s, t_master *master, t_cmd *cmd);
int		controll_builtins(t_master *master, t_cmd *cur);
void	trim_cmd(t_master *master, t_cmd *cmd, int i);
void	executor(t_master *master, char *str, int i);
char	*ft_strjoin(char const *s1, char const *s2);
char	**order(char **mt, int i, int i2, int len);
int		init_start(t_master *master, char **env);
void	gu1(int *word, char *s, int *i, char ch);
char	*program_name(char *command, char *path);
int		search_env(t_master *master, char *rule);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
int		controll_file(char *file, int command);
void	child_op(t_master *master, t_cmd *cur);
void	gu4(int *i, char *s, int *w, char **m);
void	spik_duote(int *i, char *str, char c);
char	*get_env(t_master *master, char *env);
int		bt_env(t_master *master, t_cmd *cur);
char	*get_command_f_histori(char *input);
int		free_all_steoridi(t_master *master);
char	*extr_m(t_cmd *cur, int i, int i2);
char	*ft_strjoin12f(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin2f(char *s1, char *s2);
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
int		free_matrix(char **m);
char	*gu3(int *i, char *s);
void	here_doc(char *rule);
int		skip(int i, char *s);
char	**redirect(char **m);
char	**copy_m(char **m);
bool	free_n(char *str);
void	sigbs(int signum);
int		ft_mlen(char **m);
int		ceck_fork(void);
char	*get_path(void);
int		cmmal(char **m);
char	*ft_itoa(int n);
int		bt_pwd(void);
#endif