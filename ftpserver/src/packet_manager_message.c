/*
** packet_manager_message.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 11:43:46 2017 bongol_b
** Last update Thu May 11 17:19:18 2017 bongol_b
*/

#include <string.h>
#include "myftp_server.h"

static void	pack_msg(t_msg const *msg, char *buff)
{
  strcpy(buff, msg->code);
  strcpy(&buff[strlen(buff)], " ");
  strcpy(&buff[strlen(buff)], msg->text);
  strcpy(&buff[strlen(buff)], "\n");
}

t_msg		msg_create(const char *code, const char *text)
{
  t_msg		msg;

  strcpy(msg.code, code);
  strcpy(msg.text, text);
  return (msg);
}

int		packet_msg_send(int socket_fd, t_msg const *msg)
{
  char		buff[PACKET_BUFF_SIZE];

  pack_msg(msg, buff);
  return (packet_send(socket_fd, buff));
}
