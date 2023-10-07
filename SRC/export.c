/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:18:19 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/07 20:25:44 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *find_node(t_env *head, char *command)
{
    t_env *current;

    current = head;
    while (current != NULL)
    {
        if (!ft_strcmp(current->c, command))
                return (current);
        current = current->next;
    }
    return (0);
}

char *command_ret(char *str)
{
    char *s;
    int i;
    int j;

    i = 0;
    while(str[i] && str[i] != '=' && str[i] != '+')
        i++;
    s = malloc(i + 1);
    if (!s)
        return (0);
    j = 0;
    while(str[j] && j < i)
    {
        s[j] = str[j];
        j++;
    }
    s[i] = '\0';
    return (s);
}

char *value_ret(char *str)
{
    char *s;
    int i;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    if (str[i] == '\0')
        return (0);
    i++;
    s = ft_substr(str, i, ft_strlen(str) - i);
    return (s);
}

int cheking_only(char *c)
{
    int is_valid_command = 1;
    int i;

    i = 0;
    while (c[i])
    {
        if (ft_isalnum(c[i] == 0))
        {
            is_valid_command = 0;
            return (0);
        }
        i++;
    }
    return (1);
}

void update_or_add_env(t_env **envp, char **p)
{
    t_env *existing;
    t_env *new_env;
    char *v2;
    char *c;
    char *v;
    char *equal;
    int i;
    p++;
    while (*p)
    {
        if (only_alnum(*p) == 1)
        {
            c = command_ret(*p);
            v = value_ret(*p);
            existing = find_node(*envp, c);
            if (cheking_only(*p) == 1)
            {
                if (existing)
                {
                    if (!ft_strcmp(c, "_"))
                            i = 0;              
                    else if(fun(*p) == 1)
                    {
                        if (existing->v && v)
                        {
                            v2 = ft_strjoin(existing->v , v);
                        existing->v = ft_strdup(v2);
                            
                        }
                    }
                    else
                    {
                        if (!v)
                            return ;
                        free(existing->v);
                        existing->v = ft_strdup(v);
                    }
                }
                else
                {
                    new_env = malloc(sizeof(t_env));
                    if (!new_env)
                        return;
                    equal = ft_strchrr(*p, '=');
                    if (!equal)
                    {
                        c = command_ret(*p);
                        new_env->c = ft_strdup(c);
                        if (ft_isdigit(new_env->c[0]) == 1)
                        {
                            printf("not a valid identifier\n");
                            exit(1);
                        }
                        v = value_ret(*p);
                        new_env->v = v;
                    }
                    else
                    {
                        new_env->c = ft_strdup(c);
                        if (ft_isdigit(new_env->c[0]) == 1)
                        {
                            printf("not a valid identifier\n");
                            exit(1);
                        }
                        if (!v)
                            new_env->v = ft_strdup("");
                        else
                            new_env->v = ft_strdup(v);
                    }
                    new_env->next =  NULL;
                    free(c);
                    free(v);
                    ft_lstadd_back1(envp, new_env);
                }
            }
            else
                return ;
        }
        else
            return ;
            p++;
        }
        
}
