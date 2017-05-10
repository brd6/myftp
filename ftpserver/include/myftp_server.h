/*
** myftp_server.h for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:36:13 2017 Berdrigue Bongolo-Beto
** Last update Thu May 11 00:54:47 2017 bongol_b
*/

#ifndef MYFTP_SERVER_H_
# define MYFTP_SERVER_H_

# define SERVER_LISTEN_BACKLOG	5

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

extern int	g_stop;

int		server_create(int *sock_fd, int port);
int		server_run(t_config const *config, t_user const *user);

void		debug_socket_address(int sock_fd);
void		debug_socket_distance_address(int sock_fd);

int		user_create(t_user *user,
			    char const *name,
			    char const *passwd,
			    char const *path);

void		service_handler(t_config const *config, int client_sock_fd);

#endif /* !MYFTP_SERVER_H_ */
