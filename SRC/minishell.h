/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:29:01 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/20 16:52:19 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_list
{
	struct s_list   *next;
	char *command;
	char type;
    int sep_type;
    char *buffer;
    int pipes[2];
} t_list;

typedef struct s_exec
{
    char **command;
    struct s_exec *next;
    int infile;
    int outfile;
    int flag;
}t_exec;

typedef struct s_env
{
    char **envir;
    char    *c;
    char    *v;
    int es;
    struct s_env *next;
}   t_env;


typedef struct s_var2
{
    int		i;
	int		len;
	int		s;
}   t_var2;

typedef struct s_var3
{
    char	*v2;
	char	*c;
	char	*v;
	char	*equal;
	int		i;
}   t_var3;
 void    print_nodes2(t_list *s);
 void    print_nodes(t_env *s, int data);
void    print_node_export(t_env *s , int data);

//parsing
void    ft_free_lst(t_list **list);
void    parsing(t_list **list, t_env **envp);
void    tokenizer(t_list **list, char *p, t_env **envp);

//check_input
int is_quote(t_list **list, char *cmd, int i);
int is_separ(t_list **list, char *cmd, int i);
int is_char(t_list **list, char *cmd, int i);

// liked list function
t_list	*ft_lstnew(char *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);

//erorr_hundle
void	specifie_type(t_list **list);
int     syntax_error(t_list **list);
int     cont_char(char *str);

//quotes_hundle
char    *q_remouve(char *str);
int quot_norm(char *cmd, int i, int j, char *c, char **p);


//free.c
int fun(char *str);
int only_alnum(char *str);

//env.c
t_env *fill_list(char **envp);
void    env_norm(t_env **new_env, char **envp, int *i, int *j);
void    env_norm2(t_env **head, t_env **current, t_env **new_env);
//util_func
int	ft_strcmp(char *s1, char *s2);
char *ft_strncpy(char *dst, char *src, int n);
void	ft_lstadd_back1(t_env **lst, t_env *new);
int	find_index(char *p,int i);
char *ft_strcpy(char *s1, char *s2);


//export.c
void update_or_add_env(t_env **envp, char **p);
t_env *find_node(t_env *head, char *command);
char *command_ret(char *str);
char *value_ret(char *str);

//unset.c
void    unset_norm(t_env **prev, t_env **current, t_env **envp);
void delete_from_env(t_env **envp, char **p);

//expand
void	expand(t_list **list,t_env **env);
void check_expand(t_list *tmp,t_env **env);
void	normal_expand(t_list *tmp,t_env **env);
char *check_env(char *p,t_env **env);
char *check_env_q(char *p,t_env **env);
void separ_expland(t_list *tmp,t_env **env);
char	*normal_expand_helper1(char *s,t_env **env);
char	*normal_expand_helper2(char *s,t_env **env);
char *special_expand(char *p,int *in);
int ft_check_ex(char *p);

//echo
void echo_command(char **command,int fd, t_env **env);
int check_echo_n(char *str);


//cd
void cd_command(char **command, t_env **env);
void cd_home(t_env **env);
void cd_back(t_env **env);
void cd_next(char *command,t_env **env);
char *ft_path(t_env **env);
int count_cdback(char *p);
void    cd_slash(t_env **env);
char *last_slash(char *p);
void cd_error(char *p, int f);
void cd_next_env(t_env *envp, t_env **env);
char *cd_back_free(char *p);


//pwd
void pwd_command(char *command, t_env **env, int fd);
int  pwd_lc(char *p);

void execution_part(t_list **list, t_env **envp);


//exection_part
void builting(t_exec **list, t_env **envp, int data);
void read_from_pipe(int pipes, t_env **env, t_list **list);
void open_pipe(t_list **list, t_env **envp);
char* concatenate_path_len(char *directory, size_t dir_length, char *command);
char** check_path_for_command(char *path_var, char *command);
void execute_command(char **executable_info);

//exec utils
int check_if_separ(t_list **list, char *separ);
// void exec_command(t_list **list, t_env **envp);
// char *delimiter(t_list **list);
// char *searching_path(char *command, t_env **envp);

//signals

void hundler(int signal);
void ignore_signals();
void catch_signals();
void default_signals();
//execution2.c
int redirection_in(char *file);
int redirection_out(char *file);
int	redirection_append(char *file);
int	here_doc(char *Delim);
int	list_size(t_exec *exec_val);
//execution3.c
char    *searching_path(char *command, t_env **envp);
int     builting_check(char *command);
void    simple_command(t_exec *exec_val, t_env **envp);
//execution4.c
int **make_fd(int n);
pid_t first_child(t_exec *exec_val, t_env **envp, int **fd);
pid_t middle_child(t_exec *exec_val, t_env **envp, int **fd, size_t i);
pid_t last_child(t_exec *exec_val , t_env **envp, int **fd, int n);
void free_double(int **fd);
//execution5.
void multiple_command(t_exec *exec_val , t_env **envp);
void free_list_exe(t_exec **list);
void    exec_func(t_exec *exec_val, t_env **envp);
char *command_slash(char *command);
void	free_doublep(char **command);
//exec_norm1.c
void	printf_error(char   *s);
void	for_here_doc(char   *Delim, int fd);
void	simple_cmd(t_exec *exec_val);
void	first(t_exec *exec_val, int **fd);
//exec_norm2.c
void    second(t_exec *exec_val, int **fd, size_t i);
void    last(t_exec *exec_val, int **fd, int n);
void    multi_cmd_fd(int **fd);
void    multi_cmd_fd_close(int **fd);
char    **executable_ret(char *path, int dir_length, char *command);
//exec_norm3.c
void b_norm(t_exec *tmp, t_env **envp, int data);
void b_norm2(t_exec *tmp, t_env **envp, int data);
void	exec_norm(t_list **head, t_exec **n);
void	exec_norm2(t_list	**head, t_exec **n);
void	exec_norm3(t_list  **list, t_exec **n);
//exec_norm4.c
void	exec_norm4(t_list **head, t_exec **n);
void    exec_norm5(t_list **head, t_exec **n);
void    exec_norm6(t_list **head, t_exec **n, t_exec **exec_val);
void    exec_norm7(t_exec **n);
int    exec_norm8(t_exec **n, t_list **list , int s);
//exec_norm5.c
void    initialination(t_exec **n, t_exec *exec_val);
void    initialination2(t_var2 *vars);
void    initialination3(t_list  **head, t_exec **n, t_exec **exec_val);
//export_norm.c
void    existing_norm(char **p, t_var3 **vars, t_env **existing);
void    not_exesting(char **p, t_env **new_env, t_var3 **vars);
void    not_exesting2(t_env **new_env, t_var3 **vars);
void    not_exesting_norm(t_env *new_env, t_var3 **vars, char **p, t_env **envp);
void    export_initialisation(char **p, t_var3 **vars, t_env **envp, t_env **existing);
//exit 
int check_exit(char *p);
void exit_command(char **command, int data);
int exit_status(int status);

////



#endif