/*
** service_handle.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 23:42:04 2017 bongol_b
** Last update Thu May 11 22:11:30 2017 bongol_b
*/

#include <stdio.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static int	service_loop()
{
  return (1);
}

static int	service_stop()
{
  return (1);
}

static int	auth_process(int sock_fd, t_auth_state *state)
{
  char		buff[PACKET_BUFF_SIZE];
  int		ret;
  t_cmd		cmd;
  char		**args;

  if ((ret = packet_receive(sock_fd, buff)) == 0)
    return (0);
  if ((args = my_str_split(buff, WORD_SEPS)) == NULL ||
      my_wordtab_count((const char **)args) < 1)
    return (0);
  if ((get_cmd(args[0], &cmd) == 0) ||
      !is_auth_cmd_allowed(args[0]) ||
      (strcasecmp(cmd.command, "PASS") == 0 && *state == NONE) ||
      !cmd.execute(sock_fd, (const char **)args))
    {
      my_free_wordtab(args);
      send_msg_response(sock_fd, "530", NULL);
      return (0);
    }
  if (strcasecmp(cmd.command, "USER") == 0 && *state != NAME_STEP)
    *state = NAME_STEP;
  else if (strcasecmp(cmd.command, "PASS") == 0 && *state == NAME_STEP)
    *state = SUCCESS;
  PRINT_DEBUG("auth state=%d", *state);
  my_free_wordtab(args);
  return (1);
}

static int	service_authentification(int sock_fd)
{
  t_auth_state	state;

  state = NONE;
  PRINT_DEBUG("service auth");
  /* while (!g_config.should_stop) */
  /*   { */
  /*   } */
  auth_process(sock_fd, &state);
  auth_process(sock_fd, &state);
  return (1);
}

int		service_handler(int client_sock_fd)
{
  if (send_msg_response(client_sock_fd, "220", NULL) == 0)
    return (dprintf(2, ERR_SEND_MSG), 0);
  service_authentification(client_sock_fd);
  return (1);
}
