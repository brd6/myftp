/*
** myftp_server.h for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:36:13 2017 Berdrigue Bongolo-Beto
** Last update Mon May 15 23:30:20 2017 bongol_b
*/

#ifndef MYFTP_SERVER_H_
# define MYFTP_SERVER_H_

# include <linux/limits.h>
# include <stdint.h>
# include <arpa/inet.h>

# define SERVER_LISTEN_BACKLOG	5
# define RESPONSE_DIGIT_SIZE	4
# define PACKET_BUFF_SIZE	1024
# define RAW_DATA_SIZE		(PACKET_MSG_SIZE - RESPONSE_DIGIT_SIZE)
# define UNKNOW_MSG_TYPE_IDX	-1
# define UNKNOW_USER_IDX	-1
# define UNKNOW_CMD_IDX		-1
# define BUFF_SIZE		(PACKET_BUFF_SIZE >> 1)
# define WORD_SEPS		" \t"
# define MAX_TRY_CREATE_SERVER	100
# define MIN_PASV_PORT		1024
# define MAX_PASV_PORT		65535

typedef enum	e_auth_state
  {
    NONE = -1,
    NAME_STEP,
    PASS_STEP,
    SUCCESS
  }		t_auth_state;

typedef enum	e_data_mode
  {
    _NONE = -1,
    PASSIVE,
    ACTIVE
  }		t_data_mode;

typedef enum	e_data_type
  {
    ASCII,
    BINARY
  }		t_data_type;

typedef struct	s_user
{
  char		name[BUFF_SIZE];
  char		pass[BUFF_SIZE];
  char		home_dir[PATH_MAX];
  int		is_auth;
}		t_user;

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;

typedef struct	s_socket
{
  int		sock_cmd;
  uint16_t	port_cmd;
  int		sock_data;
  uint16_t	port_data;
  t_sockaddr_in	addr_in;
  char		ipaddr[BUFF_SIZE];
}		t_socket;

typedef struct	s_config
{
  t_socket	server;
  t_socket	client;
  t_data_mode	data_mode;
  t_data_type	data_type;

  int		sock_fd;
  int		client_sock_fd;
  int		port;

  int		parent_pid;
  char		current_path[PATH_MAX];
  int		should_stop;
  t_user	current_user;
}		t_config;

typedef struct	s_cmd
{
  char		*command;
  int		(*execute)(int sock_fd, const char **args);
}		t_cmd;

typedef struct	s_msg
{
  char		code[BUFF_SIZE];
  char		text[BUFF_SIZE];
}		t_msg;

extern t_config	g_config;

int		server_create(unsigned int addr,
			      unsigned short port,
			      int reuse_addr);
int		server_run();

int		client_create(const char *addr, uint16_t port);

void		debug_socket_address(int sock_fd);
void		debug_socket_distance_address(int sock_fd);

int		init_sock_addr(int sock_fd, struct sockaddr_in *sock_addr);

int		user_get(const char *name, t_user *user);
int		user_change_home(const char *user_name, const char *home_dir);
int		user_try_auth(const char *user_name, const char *pass);

int		service_authentification(int sock_fd);
int		service_handler(int sock_fd);

int		msg_create(const char *code, const char *text, t_msg *msg);
int		packet_msg_send(int socket_fd, t_msg const *msg);
int		packet_send(int socket_fd, char *buff);
int		packet_send_raw(int socket_fd, char *buff, int size);
int		packet_receive(int socket_fd, char *buff);

int		send_msg_response(int socket_fd,
				  const char *code,
				  const char *text);

int		get_cmd(const char *buff, t_cmd *cmd);
int		is_auth_cmd_allowed(const char *cmd);
void		get_debug_available_cmds(char *buff);

int		cmd_user_execute(int sock_fd, const char **args);
int		cmd_pass_execute(int sock_fd, const char **args);
int		cmd_quit_execute(int sock_fd, const char **args);
int		cmd_pwd_execute(int sock_fd, const char **args);
int		cmd_cwd_execute(int sock_fd, const char **args);
int		cmd_cdup_execute(int sock_fd, const char **args);
int		cmd_dele_execute(int sock_fd, const char **args);
int		cmd_pasv_execute(int sock_fd, const char **args);
int		cmd_port_execute(int sock_fd, const char **args);
int		cmd_help_execute(int sock_fd, const char **args);
int		cmd_noop_execute(int sock_fd, const char **args);
int		cmd_retr_execute(int sock_fd, const char **args);
int		cmd_stor_execute(int sock_fd, const char **args);
int		cmd_list_execute(int sock_fd, const char **args);
int		cmd_syst_execute(int sock_fd, const char **args);
int		cmd_type_execute(int sock_fd, const char **args);
int		cmd_size_execute(int sock_fd, const char **args);

int		skip_space(const char *str);
int		get_file_size(const char *file_name);

int		my_get_char_pos(const char *str, char c);
char		**my_str_split(const char *str, const char *sp);
int		my_wordtab_count(const char **tab);
void		my_free_wordtab(char **tab);
char		*my_str_replace(char *search,
				char *replace,
				char *subject,
				int n);
char		*my_wordtab_to_str(const char **args, char sp);

char		*execute_system_command(const char *cmd);

int		setup_data_mode(int sock_fd);
int		setup_passive_mode();
int		setup_active_mode();
void		close_data_mode();

char		**parse_packet_args(int sock_fd);

#endif /* !MYFTP_SERVER_H_ */
