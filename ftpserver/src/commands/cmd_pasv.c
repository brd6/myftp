/*
** cmd_pasv.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:12:03 2017 bongol_b
** Last update Sun May 14 10:57:12 2017 bongol_b
*/

#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

static int	generate_port(int min, int max)
{
  srand(time(NULL));
  return (min + rand() % max);
}

int		try_create_server(unsigned int addr,
				  unsigned short *final_port,
				  int reuse_addr)
{
  int		try;
  int		sock_fd;

  try = MAX_TRY_CREATE_SERVER;
  sock_fd = -1;
  *final_port = generate_port(MIN_PASV_PORT, MAX_PASV_PORT);
  while (try > 0 &&
	 (sock_fd = server_create(addr, *final_port, reuse_addr)) < 0)
    {
      *final_port = generate_port(MIN_PASV_PORT, MAX_PASV_PORT);
      try--;
    }
  return (sock_fd);
}

static void	transform_ipaddr_dot_to_comma(struct in_addr sin_addr,
					      char *buff)
{
  int		addr[4];

  sscanf(inet_ntoa(sin_addr),
	 "%d.%d.%d.%d",
	 &addr[0],
	 &addr[1],
	 &addr[2],
	 &addr[3]);
  sprintf(buff, "%d,%d,%d,%d", addr[0], addr[1], addr[2], addr[3]);
}

int		cmd_pasv_execute(int sock_fd, const char **args)
{
  char		buff[BUFF_SIZE];
  char		buff_send[BUFF_SIZE];

  if (args[0] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (g_config.server.sock_data != -1)
    {
      close (g_config.server.sock_data);
      g_config.server.sock_data = -1;
    }
  g_config.server.sock_data = try_create_server(INADDR_ANY,
						&g_config.server.port_data,
						1);
  if (g_config.server.sock_data == -1)
    return (send_msg_response(sock_fd, "425", NULL), 0);
  transform_ipaddr_dot_to_comma(g_config.server.addr_in.sin_addr, buff);
  sprintf(&buff[strlen(buff)],
	  ",%d,%d",
	  g_config.server.port_data / 256,
	  g_config.server.port_data % 256);
  sprintf(buff_send, "Entering Passive Mode (%s)", buff);
  g_config.data_mode = PASSIVE;
  send_msg_response(sock_fd, "227", buff_send);
  return (1);
}
