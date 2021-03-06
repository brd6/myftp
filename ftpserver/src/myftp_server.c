/*
** myftp_server.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 08:25:08 2017 bongol_b
** Last update Sun May 21 23:36:48 2017 Berdrigue Bongolo-Beto
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "myftp_server.h"
#include "errors.h"

static int		wait_client_sock_connection(int *client_sock_fd,
						    struct sockaddr_in *addr,
						    socklen_t *sock_len)
{
  *client_sock_fd = accept(g_config.sock_fd,
			   (struct sockaddr *)addr,
			   sock_len);
  if (*client_sock_fd == -1)
    return (dprintf(2, ERR_SOCKET_ACCEPT, strerror(errno)), 0);
  g_config.client_sock_fd = *client_sock_fd;
  return (1);
}

static int		handler_new_client(int client_sock_fd)
{
  int			child_pid;

  if ((child_pid = fork()) == 0)
    {
      close(g_config.sock_fd);
      service_handler(client_sock_fd);
      close(client_sock_fd);
      exit(EXIT_SUCCESS);
    }
  close(client_sock_fd);
  return (1);
}

static void		reset_current_user()
{
  memset(g_config.current_user.name, 0, BUFF_SIZE);
  memset(g_config.current_user.pass, 0, BUFF_SIZE);
  memset(g_config.current_user.home_dir, 0, BUFF_SIZE);
  g_config.current_user.is_auth = 0;
}

int			server_run()
{
  int			client_sock_fd;
  struct sockaddr_in	client_addr;
  socklen_t		sock_len;

  reset_current_user();
  memset(g_config.current_path, 0, PATH_MAX);
  memset(&sock_len, 0, sizeof(sock_len));
  g_config.data_mode = _NONE;
  g_config.server.sock_data = -1;
  g_config.data_type = BINARY;
  while (!g_config.should_stop)
    {
      if (wait_client_sock_connection(&client_sock_fd,
				      &client_addr,
				      &sock_len) == 1)
	handler_new_client(client_sock_fd);
    }
  return (1);
}
