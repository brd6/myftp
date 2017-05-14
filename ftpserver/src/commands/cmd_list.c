/*
** cmd_list.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:23:26 2017 bongol_b
** Last update Sun May 14 22:16:19 2017 bongol_b
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_list_execute(int sock_fd, const char **args)
{
  char		*cmd_result;
  char		*tmp;
  char		cmd[BUFF_SIZE];

  PRINT_DEBUG("cmd_list_execute");
  if (args[0] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (setup_data_mode(sock_fd) == 0)
    return (0);
  sprintf(cmd, "ls -l %s", args[1] != NULL ? args[1] : "");
  if ((cmd_result = execute_system_command(cmd)) == NULL)
    return (send_msg_response(sock_fd, "552", NULL), 0);
  tmp = cmd_result;
  cmd_result = my_str_replace("\n", "\r\n", tmp, -1);
  free(tmp);
  packet_send(g_config.client.sock_data, cmd_result);
  free(cmd_result);
  send_msg_response(sock_fd, "226", NULL);
  close_data_mode();
  return (1);
}
