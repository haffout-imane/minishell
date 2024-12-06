/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihajouji <ihajouji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:31:08 by ihaffout          #+#    #+#             */
/*   Updated: 2024/09/14 10:31:40 by ihajouji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>

extern int		g_es;
# define INITIAL_BUFFER_SIZE 1024

typedef struct s_minishell
{
	char			**command;
	char			**words;
	char			**tokens;
	char			**files;
	char			**limiter;
	int				*fd;
	int				*heredoc_fd;
	char			**not_expanded;
	int				g_es;
}					t_minishell;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct s_exc
{
	pid_t			pid;
	pid_t			*pids;
	char			**env;
	t_env			**my_env;
	int				len;
	int				input_fd;
}					t_exc;

typedef struct s_var
{
	int				c_index;
	int				t_index;
	int				w_index;
	int				f_index;
	int				l_index;
}					t_var;

/* ------------------------------- SIGNALS ------------------------------ */
void				handle_sigint(int sig);
void				heredoc_sigint(int sig);
void				handle_signals(int flag);

/* ------------------------------- EXECUTION ------------------------------ */
// EXECUTE //
int					execution(t_minishell *line, char **cmnds, t_env **my_env);
void				cleanup_resources2(t_exc *exc, t_minishell *line);
void				check_files(t_minishell *line, int len, int *error);
void				cleanup_resources(t_exc *exc, t_minishell *line);
int					process_commands(t_exc *exc, t_minishell *line, int *fd);
int					handle_parent_process(t_exc *exc, int i, int *fd,
						t_minishell *line);
int					handle_child_process(t_exc *exc, t_minishell *line, int i,
						int *fd);

// EXECUTION UTILS //
void				ft_free(char **str, int i);
void				perror_exit(char *str, int nbr);
void				execute_command(t_minishell *line, t_env **my_env,
						char **env);
int					execution_init(t_exc *exc, char **cmnds, t_env **my_env);

// HEREDOC //
int					handle_heredoc(char *limiter, char **env);
int					preprocess_heredocs(t_minishell *lines, int len,
						char **env);
int					have_heredoc(t_minishell *line);

// REDIRECTIONS //
int					check_tokens(t_minishell *line);
int					handle_redirections(int i,
						int *j, int *d, t_minishell *line);
int					append_output_redirection(char *files, int *fd, int *j);
int					nbr_tokens(char **tokens);
int					nbr_files(char **files);
int					output_redirection(char *files, int *fd, int *j);
int					input_redirection(char *files, int *fd, int *j);

// PATH //
char				*get_path(char *command, char **env);
char				*join_and_check_path(char *dir, char *command);
char				**get_path_variable(char **env);
char				*check_absolute_path(char *command);

/* ---------------------- INIT_UTILS ---------------------- */
t_minishell			*init_scanner(t_minishell *scanner, int i, char *cmnd);
int					is_redirection_(char *str);
int					is_heredoc(char *str);
int					fill_words(t_minishell *scanner, t_var *var);
char				*join_wildcards(char **res);
void				sort_wildcards(char **res);
int					handle_redirection_heredoc(t_minishell *scanner,
						t_var *var);

/* ---------------------- free ---------------------- */
void				free_element(char **array);
char				**clear_arr(char **result, int j);
void				ft_clean(char **new_env, t_env *my_env);
int					_clean2(char **new_env, t_env *my_env, char **cmnds);

/* ---------------------- LINKED LIST ---------------------- */
int					ft_lstsize(t_env *lst);
void				ft_lstdelone(t_env *lst, void (*del)(void *));
void				ft_lstclear(t_env **lst, void (*del)(void *));
t_env				*ft_lstlast(t_env *lst);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				ft_lstadd_front(t_env **lst, t_env *new);
t_env				*ft_lstnew(void *var);
void				init_env(t_env **my_env, char **env);

/*----------- WILDCARDS UTILS -------------------*/
char				*ft_strstr(char *haystack, char *needle);
char				*ft_strcat(char *dest, char *src);
int					contains_wildcard(char *str);
int					check_dote(char *str);
int					is_quoted(char *token);
char				*ft_strtok(char *str, const char *delim);

/*----------- WILDCARDS -------------------*/
char				*ft_realloc(char *results, int size, DIR *dir);
char				*handle_wildcards(char *command);
char				*handle_star_middle_wildcard(char *token);
int					have_pattern(char *name, char *prefix, char *suffix);
char				*finalize_results(char *results, size_t results_len);
DIR					*open_directory_and_init_results(char **results,
						size_t *results_len);
char				*append_to_results2(char *results, size_t *results_len,
						char *entry_name, DIR *dir);
int					handle_position(int position, char *pattern,
						char *entry_name);

/* -------- ENVIRONMENT UTILS ------------ */
char				*append_space(char *command, int start);
int					ft_isalnum(int c);
char				*ft_strndup(char *s, int n);
char				*get_variable(char *word, char **env);
char				*ft_substr(char *s, unsigned int start, size_t len);
int					handle_quote_expand(char *command, int i);
char				*append_non_var_part(char *result, char *command, int start,
						int i);
char				*handle_not_dollar(char *command, int *i, char *result);
char				*handle_star_leading_wildcard(char *token);
char				*handle_star_trailing_wildcard(char *token);
char				*handle_star_leading_trailing_wildcard(char *token);
char				*handle_only_star_wildcard(void);
char				*handle_wildcards(char *command);
void				process_token(char *expanded_command, char *token);
char				*init_expanded_command(void);
char				*expand_wildcards(char *token);
char				*collect_files(DIR *dir, char *results, int *results_len);
char				*match_pattern(char *pattern, int position);

/* ----------------- UTILS ----------------  */
int					ft_isalnum(int c);
void				ft_error(char *msg, char *cmd);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcpy(char *dest, const char *src);
int					only_spaces(char *str);
int					check_valid_cmd(char **cmnds, char *input, char **new_env);

/* ----------------- FT_SPLIT UTILS ----------------  */
int					skip_leading_delimiters(char *s, int i, char c);
int					is_double_redirection(char *str, int i);
int					is_redirection(char c);
int					handle_quote(char *s, int i, char quote);
int					ft_skip(char *str, int i, char c);
char				*fill(char *str, int start, int end);

/* ----------------- SPLIT_COMMANDS UTILS ----------------  */
int					_handle_quote(const char *s, int i, char quote);
int					skip_between_quotes(const char *s, char c, int i);

/* ----------------- BUILTINS ----------------  */
int					ft_echo(char **args);
int					ft_pwd(t_env **env);
int					ft_env(t_env **env);
int					ft_cd(char **words, t_env **env);
int					ft_export(char **args, t_env **my_env);
int					check_var_name(char	**args, int i, char *name);
int					ft_unset(char **words, t_env **my_env);
int					ft_exit(char **args, t_minishell *line);
int					is_builtin(char **words, t_env **my_env, t_minishell *line);
int					check_builtin(char *str);

int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**replace_new_env(t_env *my_env);
size_t				ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				**ft_split(char *s, char c);
char				**split_commands(const char *s, char c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_itoa(int n);
char				*ft_strdup(char *s1);
char				*read_input(char **env);
int					count_commands(char **cmnds);
t_minishell			*init_structs(char **cmnds, char **env);
int					token_count(char **str);
int					word_count(char **str);
int					heredoc_count(char **str);
void				free_minishell(t_minishell *scanner, char **new_env,
						char **cmnds);
char				*handle_invalid_var(char *result, char *var_name);
char				*extract_var_name(char *command, int *i);
char				*replace_env_vars_in_command(char *command, char **env);
#endif
