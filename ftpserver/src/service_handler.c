/*
** service_handle.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 23:42:04 2017 bongol_b
** Last update Sun May 14 22:35:26 2017 bongol_b
*/

#include <stdio.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static void	set_current_auth_state(const char *command, t_auth_state *state)
{
  if (strcasecmp(command, "USER") == 0 && *state != NAME_STEP)
    *state = NAME_STEP;
  else if (strcasecmp(command, "PASS") == 0 && *state == NAME_STEP)
    *state = SUCCESS;
  PRINT_DEBUG("auth_process: state=%d", *state);
}

static int	service_loop_dispatch(int sock_fd, t_auth_state *auth_state)
{
  t_cmd		cmd;
  char		**args;

  PRINT_DEBUG("user connected : name='%s', home='%s' - auth=%d",
	      g_config.current_user.name,
	      g_config.current_user.home_dir,
	      g_config.current_user.is_auth);
  if ((args = parse_packet_args(sock_fd)) == NULL)
    return (0);
  if (*auth_state != SUCCESS && !is_auth_cmd_allowed(args[0]))
    send_msg_response(sock_fd, "530", NULL);
  else if (get_cmd(args[0], &cmd) == 0)
    send_msg_response(sock_fd, "500", NULL);
  else if (strcasecmp(cmd.command, "PASS") == 0 && *auth_state == NONE)
    send_msg_response(sock_fd, "530", NULL);
  else if (cmd.execute(sock_fd, (const char **)args))
    set_current_auth_state(cmd.command, auth_state);
  return (my_free_wordtab(args), 0);
}

int		service_handler(int sock_fd)
{
  t_auth_state	auth_state;

  auth_state = NONE;
  init_sock_addr(sock_fd, &g_config.server.addr_in);
  if (send_msg_response(sock_fd, "220", NULL) == 0)
    return (dprintf(2, ERR_SEND_MSG), 0);
  while (!g_config.should_stop)
    service_loop_dispatch(sock_fd, &auth_state);
  return (1);
}
