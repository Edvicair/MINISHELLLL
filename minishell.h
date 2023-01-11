/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:43:04 by edvicair          #+#    #+#             */
/*   Updated: 2023/01/11 13:08:32 by edvicair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>

typedef struct s_env
{
	bool			egal;
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;


typedef struct s_loc
{
	void *garb; 
	struct s_loc	*next;
}				t_loc;

typedef enum	s_type
{
	NO_REDIR,
	RE_G,
	H_DOC,
	RE_D,
	RE_DD,
}			t_type;

typedef struct s_redir
{
	t_type	type;
	char	*feldup;
	struct s_redir	*next;
}				t_redir;

typedef struct s_token
{
	t_redir	*redir;
	char	**cmd;
	int	child;
	int in;
	int out;
	int	fd[2];
	struct s_token	*next;	
}				t_token;

typedef struct s_msh
{
	t_env	*env;
	char	*line;
	int	pip;
	int	in;
	int	out;
	t_token	*token;
}				t_msh;

						//PARSING//
int		is_quote(char *str);
char	**tokenizator(char *str, char c);
int	split_what(char *str, int i, char quote);
//void	freezer(t_token *token);
int	parser(t_msh *msh);
//int	tokenizator(char *str, t_token *token);
int	strlen_quote(char *str, int min, int max);
int	find_quote(char *str, int min , int max);
int	is_pipe(char *str);
int	find_pipe(char *str, int i);
char	*ft_substr2(const char *s, int min, int max);
int	split_quote(char *str, int i, char quote);
int		is_quote(char *str);
int	strlen_quote(char *str, int min, int max);
int	pipe_error(char *line);
char	*space_chips(char *line);
char	*ft_substr_pipe(const char *s, unsigned int start, unsigned int end);
int	redir_error(char *line);
t_redir	*redi_less(char *str);
void	ft_redir_add_back(t_redir **redir, t_redir *new);
t_redir	*ft_redir_last(t_redir *redir);
t_redir	*ft_redir_new(int R, char *word);
t_type  ft_choose_type(int R);
char	*ft_substr_redir(char *s);
int		ft_strlen_redir(char *str);

						// EXEC //
void	one_child(t_msh *msh);
void	exec(t_msh *msh, char **cmd, char **env);
						// LIB //
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(t_msh *msh, char const *s1, char const *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(t_msh *msh, const char *s);
bool	ft_strshr(const char *s, int c);
void    ft_free_double(char **s);

						// BUILT //
void	ft_export_pwd(t_msh *msh, char *pwd, char *path);
char	*ft_getenv(t_msh *msh, char *path);
void	ft_export(t_msh *msh);
void	ft_sort_export(t_msh *msh);
void	ft_unset(t_msh *msh);
void	ft_echo(t_msh *msh);
void	ft_exit(t_msh *msh);
void	ft_pwd(t_msh *msh);
void	ft_env(t_msh *msh);
void	ft_cd(t_msh *msh);

						// INIT //
void    free_one_env(t_env *env);
t_token	*ft_fill_token(t_msh *msh);
void	ft_init_struct(t_msh *msh, char **env);
void	ft_env_add_back(t_env **env, t_env *new);
t_env	*ft_env_new(t_msh *msh, char *name, char *value, bool egal);
void	ft_loc_add_back(t_loc **loc, t_loc *new);
t_loc	*ft_loc_last(t_loc *loc);
t_loc	*ft_loc_new(void *content);
char	**ft_split_space(char const *s);
void	ft_free_token(t_msh *msh);
t_redir	*redi_less(char *str);

#endif
