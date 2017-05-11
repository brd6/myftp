/*
** myftp_server.h for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:36:13 2017 Berdrigue Bongolo-Beto
** Last update Thu May 11 15:25:08 2017 bongol_b
*/

#ifndef MYFTP_SERVER_H_
# define MYFTP_SERVER_H_

# define SERVER_LISTEN_BACKLOG	5
# define RESPONSE_DIGIT_SIZE	4
# define PACKET_MSG_SIZE	1024
# define RAW_DATA_SIZE		(PACKET_MSG_SIZE - RESPONSE_DIGIT_SIZE)
# define UNKNOW_MSG_TYPE_IDX	-1

typedef struct	s_user
{
  char		*name;
  char		*password;
  char		*home_dir;
}		t_user;

typedef struct	s_config
{
  int		sock_fd;
  int		port;
}		t_config;

typedef struct	s_command
{

}		t_command;

typedef struct	s_msg
{
  char		*code;
  char		*text;
}		t_msg;

extern int		g_stop;

int		server_create(int *sock_fd, int port);
int		server_run(t_config const *config, t_user const *user);

void		debug_socket_address(int sock_fd);
void		debug_socket_distance_address(int sock_fd);

int		user_create(t_user *user,
			    char const *name,
			    char const *passwd,
			    char const *path);

void		service_handler(t_config const *config, int client_sock_fd);

t_msg		msg_create(const char *code, const char *text);
int		packet_msg_send(int socket_fd, t_msg const *msg);
int		packet_send(int socket_fd, char *buff);
int		packet_receive(int socket_fd, char *buff);

int		send_msg_response(int socket_fd,
				  const char *code,
				  const char *text);

#endif /* !MYFTP_SERVER_H_ */
