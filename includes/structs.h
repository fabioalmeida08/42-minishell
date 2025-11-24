#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;	
}	t_env;

typedef struct s_shell
{
    char       **envp;
    t_env       *env_list;
}   t_shell;

#endif