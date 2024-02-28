#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define BUFFER_SIZE_TOK 128
#define DELIM_TK " \t\r\n\a"

extern char **environ;

typedef struct s_data
{
	char **arg_v;
	char *input;
	char **args;
	int status;
	int i;
	char **env_var;
	char *pid;
} sh_data;


typedef struct s_list
{
	char sep;
	struct s_list *next;
} t_sep_list;


typedef struct s_list_line
{
	char *line;
	struct s_list_line *next;
} t_list_line;


typedef struct s_list_vars
{
	int len;
	char *val;
	int val_len;
	struct s_list_vars *next;
} t_list_vars;

typedef struct s_builtin
{
	char *name;
	int (*f)(sh_data *datas);
} t_builtin;


t_sep_list *add_separator_at_end(t_sep_list **head, char seep);
void free_separator_list(t_sep_list **head);
t_list_line *add_line_at_end(t_list_line **head, char *line);
void free_line(t_list_line **head);

t_list_vars *add_var_end(t_list_vars **head, int l_var, char *var, int l_val);
void free_var(t_list_vars **head);

char *ft_strcat(char *dest, const char *src);
char *ft_strcpy(char *dest, char *src);
int ft_strcmp(char *str1, char *str2);
int ft_strspn(char *s, char *charset);
int ft_atoi(char *s);

char *ft_strdup(const char *s);
int ft_strlen(const char *s);
char *ft_strtok(char str[], const char *delim);
int ft_isdigit(const char *s);

void ft_rev_str(char *s);
int ft_chars_comp(char s[], const char *dlim);
char *ft_strchr(char *s, char c);
int get_length(int len);
char *ft_itoa(int n);

void ft_memcpy(void *restrict_dst, const void *restrict_src, unsigned int n);
void *ft_realloc(void *ptr, unsigned int old_n, unsigned int new_n);
char **ft_reallocdp(char **ptr, unsigned int old_n, unsigned int new_n);

int count_repeated_char(char *input, int i);
int sep_error(char *input, int i, char last);
int char_first_index(char *s, int *i);
void syntax_error_display(sh_data *datas, char *input, int i, int bool);
int syntax_errors(sh_data *datas, char *s);

char *remove_comment(char *input);
void loop_shell(sh_data *datas);

char *ft_read_line(int *end_file);

char *ft_swap(char *input, int bool);
void add_sep_cmd_line(t_sep_list **head_s, t_list_line **head_l, char *input);
void next_cmd(t_sep_list **list_s, t_list_line **list_l, sh_data *datash);
int cmd_split(sh_data *datash, char *input);
char **line_splitting(char *str);

void valid_env(t_list_vars **h, char *in, sh_data *data);
int valid_vars(t_list_vars **h, char *in, char *st, sh_data *data);
char *rep_inputs(t_list_vars **head, char *input, char *new_input, int nlen);
char *replace_str_var(char *input, sh_data *datash);

void assign_line(char **line, size_t *n, char *buf, size_t l);
ssize_t ft_get_line(char **line, size_t *n, FILE *stream);

int execute_line(sh_data *data);
int exec_command(sh_data *data);
int check_is_executable(sh_data *data);

int check_is_curr_dir(char *path, int *i);
char *which_cmd(char *cmd, char **envi);
int cmd_check_error(char *dir, sh_data *datash);

char *ft_getenv(const char *name, char **envi);
int ft_env(sh_data *data);
char *infos(char *name, char *value);

void set_env(char *var_name, char *var_value, sh_data *data);
int ft_setenv(sh_data *data);
int ft_unsetenv(sh_data *data);

void ft_cd_to(sh_data *data);
void ft_cd_previous(sh_data *data);
void ft_cd_to_home(sh_data *data);

void ft_cd_dot(sh_data *data);
int ft_cd_dir(sh_data *data);
int ft_exit_sh(sh_data *data);

int (*ft_get_builtin(char *cmd))(sh_data *data);

char *ft_strcat_cd(sh_data *data, char *msg, char *error, char *ver_str);
char *ft_get_cd_error(sh_data *data);
char *ft_not_found_error(sh_data *data);
char *ft_exit_shell_error(sh_data *data);

char *ft_env_error(sh_data *data);
char *ft_path_error(sh_data *data);
int ft_get_error(sh_data *data, int eval);

void ft_sigint_handler(int sig);

void ft_env_help(void);
void ft_setenv_help(void);
void ft_unsetenv_help(void);
void ft_gen_help(void);
void ft_exit_help(void);

void ft_help(void);
void ft_alias_help(void);
void ft_cd_help(void);
int ft_get_help(sh_data *data);

#endif
