/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:29:01 by aamhal            #+#    #+#             */
/*   Updated: 2023/09/22 09:24:01 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	struct s_list   *next;
	char *command;
	char type;
} t_list;

typedef struct s_env
{
    char    *c;
    char    *v;
    struct s_env *next;
}   t_env;


 void    print_nodes2(t_list *s);
 void    print_nodes(t_env *s);


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
void    remove_quotes(t_list **list);

//free.c
void free_list(t_env *head);
int fun(char *str);
int only_alnum(char *str);

//env.c
t_env *fill_list(char **envp);

//util_func
int	ft_strcmp(char *s1, char *s2);
char *ft_strncpy(char *dst, char *src, int n);
void	ft_lstadd_back1(t_env **lst, t_env *new);
int	find_index(char *p,int i);


//export.c
void update_or_add_env(t_env **envp, char *p);
t_env *find_node(t_env *head, char *command);
char *command_ret(char *str);
char *value_ret(char *str);

//unset.c
void delete_from_env(t_env **envp, char *p);

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
void check_echo(t_list **list, int fd);
void echo_command(t_list *list, int fd);
int check_echo_n(char *str);

//exection_part
void builting(t_list **list, t_env **envp);
void read_from_pipe(int pipes, t_env **env, t_list **list);
void open_pipe(t_list **list, t_env **envp);
char* concatenate_path_len(char *directory, size_t dir_length, const char *command);
char** check_path_for_command(char *path_var, char *command);
void execute_command(const char *const *executable_info);
char* find_path(t_env *envp);
#endif