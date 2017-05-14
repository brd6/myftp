/*
** cmd_port.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:14:41 2017 bongol_b
** Last update Sun May 14 22:08:53 2017 bongol_b
*/

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

static int	is_valid_ipaddr(const char *addr)
{
  t_sockaddr_in	sa;

  return (inet_pton(AF_INET, addr, &(sa.sin_addr)) != 0);
}

static int	is_valid_addr_and_port_buff(const char *buff)
{
  int		i;
  int		dig_cpt;
  int		comma_cpt;

  i = 0;
  dig_cpt = 0;
  comma_cpt = 0;
  while (buff && buff[i])
    {
      if ((!isdigit(buff[i]) && buff[i] != ',') ||
	  (dig_cpt > 3 && comma_cpt < 5))
	return (0);
      if (buff[i] == ',')
	{
	  dig_cpt = 0;
	  comma_cpt++;
	}
      else
	dig_cpt++;
      i++;
    }
  return (1);
}

static int	parse_address_and_port(const char **args,
				       char *addr,
				       uint16_t *port)
{
  int		addr_cmp[4];
  int		port_cmp[2];

  if (!is_valid_addr_and_port_buff(args[1]))
    return (0);
  sscanf(args[1],
	 "%d,%d,%d,%d,%d,%d",
	 &addr_cmp[0],
	 &addr_cmp[1],
	 &addr_cmp[2],
	 &addr_cmp[3],
	 &port_cmp[0],
	 &port_cmp[1]);
  sprintf(addr, "%d.%d.%d.%d",
	  addr_cmp[0],
	  addr_cmp[1],
	  addr_cmp[2],
	  addr_cmp[3]);
  *port = (port_cmp[0] * 256 + port_cmp[1]);
  return (is_valid_ipaddr(addr));
}

int		cmd_port_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (g_config.client.sock_data != -1)
    {
      close (g_config.client.sock_data);
      g_config.client.sock_data = -1;
    }
  if (parse_address_and_port(args, g_config.client.ipaddr,
			     &g_config.client.port_data) == 0)
    return (send_msg_response(sock_fd, "501", NULL), 0);
  PRINT_DEBUG("cmd_port_execute: addr=%s,port=%u",
	      g_config.client.ipaddr,
	      g_config.client.port_data);
  g_config.data_mode = ACTIVE;
  send_msg_response(sock_fd, "200", NULL);
  PRINT_WARNING("data mode : ACTIVE");
  return (1);
}
