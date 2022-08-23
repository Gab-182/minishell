/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 06:52:23 by gabdoush          #+#    #+#             */
/*   Updated: 2022/08/19 22:16:43 by gabdoush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

/*--------  Colors --------*/
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define C "\033[0;36m"
# define P "\033[0;35m"
# define RESET "\033[0m"

/*--------------------------*/

/*--------------------------------  Structures -------------------------------*/
/**
 ** The environment structure
 ** env: 2D pointer to the program environment
 ** shlvl: to follow up the shell level
 */
typedef struct s_envp
{
	char			**env;
	size_t			shlvl;
}			t_envp;
/*=========================================*/
typedef struct s_dquote
{
	int		dquote;
	char	*parsed_cmd;
	int		pipes_nb;
}		t_dquote;

/*-----------------------------------------*/
/**
 ** s_cmd : 2D pointer to the parsed commands.
 ** path: the path for each command.
 ** operator:
 ** file_name:
 */
typedef struct s_data
{
	char		**operator;
	char		**file_name;
	char		**s_cmd;
	char		*path;
	int			fd[2];
	int			fd_temp;
	int			fd_rd;
	int			status;
	char		**env;
	char		*cmd;
	char		*full_cmd;
	char		**full_op;
	int			flag;
	t_dquote	all;
}			t_data;

/*-----------------------------------------*/
typedef struct s_gd
{
	t_envp		*envp;
	int			return_state;
	char		*printed_path;
	int			pipes_num;
	char		*args;
	int			fd_temp;
	int			i;
}		t_gd;

/*-----------------------------------------*/
t_gd	*g_data;

/*---------------------------------- parser.c --------------------------------*/
int		copy_only_cmd(t_data *data);
void	start_copy_cmd(t_data *data);
void	copy_op_and_file(t_data *data, int x);
void	allocate_op_and_file(t_data *data, int x);
int		copy_details(t_data *data);
int		copy_all_op(t_data *data);
int		count_op(t_data *data);
char	*check_dquote(char *cmd, t_dquote *data, t_data *info);
int		copy_op_line(t_data *data, int i, int x);
int		check_size_of_full_op(t_data *data, int i);
int		ft_isspace(char c);
int		check_full_op(t_data *data);
int		ft_strlen_n(const char *s);
int		wordscount_og(char const *s, char c);
char	*ft_getenv(char *name, char **env);
char	**ft_split_og(char const *s, char c);
char	*checkpath(char *str, char **env);
char	*check_expand(char *cmd, t_data *data);
char	*replace_sub_str_to_expand(char *cmd, int start, int len, char **env);
int		ft_strncomp(const char *s1, const char *s2, int n);
int		ft_exec(t_data *data);
int		data_init(t_data *data, t_dquote *for_all, char *cmd, t_envp *envp);
void	print_error(char *s);
int		checker(char *cmd);
t_data	*check_cmd(t_data *data);
char	*remove_dollar(char *cmd, int start);
void	skip_oop(t_data *data, int *i);
void	alloc_op(t_data *data, int nb_of_op);
int		incrementer55(t_data *data, int i);
int		incrementer_3(int x, t_data *data);
int		error_for_op(t_data *data, int i);
int		error_for_size_op(t_data *data, int i);
int		check_size_of_full_op(t_data *data, int i);
int		size_op_skip(t_data *data, int *i, int j);
int		increment_i(t_data *data, int i);
int		increment_j(t_data *data, int i, int j);
int		skip_j(t_data *data, int i, int j, char c);
int		incrementii(t_data *data, int i);
int		incrementjj(t_data *data, int i, int j);
int		ft_strlen_n(const char *s);
int		isenv_se(char c);
int		isenv(char c);
char	*check_expand_helper_2(char *final_expanded, int *i, t_data *data);
char	*ft_strndup(char *cmd, int length, int i);
char	*check_expand_1(int i, char *final_expanded, char **env);
char	*check_expand_helper_0(char *final_expanded, int *i, t_data *data);
int		check_expand_helper_01(char *final_expanded, int *i, t_data *data);
int		check_expand_helper_1(char *final_expanded, int *i);
int		check_flag(t_data *info, int i, char c);
int		increment_till_next_quote(t_dquote *data, char *cmd, int i, char c);
int		increment_till_next_op(t_data *data, int i);
void	print_error(char *s);
int		data_init(t_data *data, t_dquote *for_all, char
			*cmd_holder, t_envp *envp);
char	*copy_parsed_cmd(char *cmd, char *new);
char	*allocate_parsed_cmd(char *cmd);
int		check_dquote_only(char *cmd, t_dquote *data);
int		size_op_from_full(t_data *data, int i, int j);
int		skip_op(t_data *data, int i);
char	*check_expand_helper_final(char *final_expanded, int *i, t_data *data);
int		check_error_status(int pipe_num, char *cmd_line, t_dquote *for_all);
int		check_full_op(t_data *data);
int		incrementer(const char *s, int i);
int		count_pipes(char *cmd_line, int j);
int		redirect_all_commands(t_data *data, t_dquote *for_all);
char	*no_expand_found(char **cmd, int start, int length);
char	*edit_expanded(char *expanded, char *cmd, int length, int start);

/*---------------------------------  Signals ---------------------------------*/
void	handle_signals(void);

/*--------------------------  Built_in_commands ------------------------------*/
int		ft_echo(t_data *data, int cmd_num);
int		ft_cd(t_data *data, t_envp *envp, int cmd_num);
int		ft_pwd(t_data *data, int cmd_num);
int		ft_exit(t_data *data, int cmd_num);
int		ft_unset(t_data *data, t_envp *envp, int cmd_num);
int		ft_env(t_data *data, t_envp *envp, int cmd_num);
int		ft_export(t_data *data, t_envp *envp, int cmd_num);

/*--------------------------  Built_in commands handlers ---------------------*/
int		builtin(t_data *data, int cmd_num);
int		builtin_checker(t_data *data, int cmd_num);
int		piped_built_in(t_data *data, int cmd_num);

/*----------------------------# Environment_utils #---------------------------*/
int		sizeof_2d_array(char **array);
void	add_to_env(t_envp *envp, char *to_add);
void	del_from_env(t_envp *envp, char *to_delete);
char	**dup_2darray(char **array);
size_t	env_element_name(char **env, int index);
void	shlvl_edge_cases(t_envp *envp);
void	add_to_shlvl(void);
int		is_excited(t_envp *envp, char *to_compare);

/*-----------------------------# Cleaning_utils #-----------------------------*/
void	free_struct_s_cmd(t_data *data, int cmd_num);
void	free_struct_file_name(t_data *data, int cmd_num);
void	free_struct_operator(t_data *data, int cmd_num);
void	fd_closer(t_data *data);
void	free_cmds(t_data *data);
void	free_global_data(void);

/*-----------------------------# Export_utils #-------------------------------*/
int		export_error(char *err_cmd);
int		already_exist(char *to_add, t_envp *envp);
int		valid_toadd(t_data *data, int index);
void	add_to_env_value(t_envp *envp, char *new_cmd);
char	*env_value(t_envp *envp, char *element_name);
void	export_print(t_envp *envp);
char	*delchar(char *cmd);
void	export_print_2(t_envp *envp, int *i, int *j);
void	sorting_environment(t_envp *envp);

/*--------------------------# redirection_utils #-----------------------------*/
int		check_redirection(t_data *data, int cmd_num);
void	check_rp_redirection(t_data *data, int cmd_num, int i);
void	check_ap_redirection(t_data *data, int cmd_num, int i);
int		ft_open_rp(char *str);
int		ft_open_ap(char *str);
int		ft_open(char *str);
int		ft_here_doc_2(char *str);
int		ft_strncoomp(const char *s1, const char *s2, int n);
int		heredoc_exec(t_data *data, char *str, int cmd_num);

/*--------------------------------- execution --------------------------------*/
int		execute(t_data *data);
void	ft_dup2(t_data *data, int cmd_num);
void	free_2d_array(char **array);
void	free_env(t_envp *envp);
void	fork_child(t_data *data, int cmd_num);
char	*get_path(char *path, t_data *data, char *args);
char	*print_path(void);
void	fd_temp_closer(void);
void	fd_rd_closer(t_data *data, int cmd_num);
void	ft_wait_all(void);

/*============================================================================*/
#endif
