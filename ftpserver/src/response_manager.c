/*
** response_manager.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 15:02:57 2017 bongol_b
** Last update Thu May 11 15:25:23 2017 bongol_b
*/

#include <stdlib.h>
#include <string.h>
#include "myftp_server.h"

static t_msg	g_msg_types[] = {
  {"120", "Service ready in %d minutes."},
  {"125", "Data connection already open; transfer starting."},
  {"150", "File status okay; about to open data connection."},
  {"200", "Command okay."},
  {"214", "Help message."},
  {"220", "Service ready for new user."},
  {"221", "Service closing control connection."},
  {"226", "Closing data connection."},
  {"227", "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
  {"230", "User logged in, proceed."},
  {"250", "Requested file action okay, completed."},
  {"257", "\"%s\" created."},
  {"331", "User name okay, need password."},
  {"332", "Need account for login."},
  {"530", "Not logged in."},
  {"532", "Need account for storing files."},
  {"502", "Command not implemented."},
  {"501", "Syntax error in parameters or arguments."},
  {"500", "Syntax error, command unrecognized."},
  {NULL, NULL}
};

static int	get_msg_index(const char *code)
{
  int		i;

  i = 0;
  while (g_msg_types[i].code && g_msg_types[i].text)
    {
      if (strcmp(g_msg_types[i].code, code) == 0)
	return (i);
      i++;
    }
  return (UNKNOW_MSG_TYPE_IDX);
}

int		send_msg_response(int socket_fd,
				  const char *code,
				  const char *text)
{
  int		msg_idx;
  t_msg		msg;

  if ((msg_idx = get_msg_index(code)) == UNKNOW_MSG_TYPE_IDX)
    return (0);
  if (text != NULL)
    msg = msg_create(code, text);
  else
    msg = g_msg_types[msg_idx];
  return (packet_msg_send(socket_fd, &msg));
}
