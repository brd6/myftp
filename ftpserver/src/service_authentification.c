/*
** service_authentification.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 10:15:03 2017 bongol_b
** Last update Fri May 12 10:21:30 2017 bongol_b
*/

#include <stdio.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static int	auth_process(int sock_fd, t_auth_state *state)
{
  char		buff[PACKET_BUFF_SIZE];
  t_cmd		cmd;
  char		**args;

  PRINT_DEBUG("auth_process: sock_fd=%d", sock_fd);
  if ((packet_receive(sock_fd, buff) == 0) ||
      ((args = my_str_split(buff, WORD_SEPS)) == NULL ||
       my_wordtab_count((const char **)args) < 1))
    return (0);
  if ((get_cmd(args[0], &cmd) == 0) ||
      !is_auth_cmd_allowed(args[0]))
    send_msg_response(sock_fd, "530", NULL);
  else if (strcasecmp(cmd.command, "PASS") == 0 && *state == NONE)
    send_msg_response(sock_fd, "530", NULL);
  else if (cmd.execute(sock_fd, (const char **)args))
    {
      if (strcasecmp(cmd.command, "USER") == 0 && *state != NAME_STEP)
	*state = NAME_STEP;
      else if (strcasecmp(cmd.command, "PASS") == 0 && *state == NAME_STEP)
	*state = SUCCESS;
      PRINT_DEBUG("auth_process: state=%d", *state);
      return (my_free_wordtab(args), 1);
    }
  return (my_free_wordtab(args), 0);
}

int		service_authentification(int sock_fd)
{
  t_auth_state	state;

  state = NONE;
  PRINT_DEBUG("service auth");
  while (!g_config.should_stop && state != SUCCESS)
    auth_process(sock_fd, &state);
  PRINT_DEBUG("service_auth : end");
  return (state == SUCCESS);
}