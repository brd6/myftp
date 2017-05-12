/*
** commands.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 18:38:09 2017 bongol_b
** Last update Fri May 12 12:11:36 2017 bongol_b
*/

#include <string.h>
#include <stdio.h>
#include "myftp_server.h"
#include "debug.h"

static t_cmd	g_cmds[] = {
  {"USER", cmd_user_execute},
  {"PASS", cmd_pass_execute},
  {"QUIT", cmd_quit_execute},
  {"PWD", cmd_pwd_execute},
  {"CWD", cmd_cwd_execute}
};

static int	get_command_index(const char *cmd)
{
  int		i;

  i = 0;
  while (g_cmds[i].command)
    {
      if (strcasecmp(g_cmds[i].command, cmd) == 0)
	return (i);
      i++;
    }
  return (UNKNOW_CMD_IDX);
}

int		get_cmd(const char *buff, t_cmd *cmd)
{
  int		i;

  PRINT_DEBUG("get_cmd : buff='%s'", buff);
  if ((i = get_command_index(buff)) == UNKNOW_CMD_IDX)
    return (0);
  *cmd = g_cmds[i];
  PRINT_DEBUG("get_cmd: %s", cmd->command);
  return (1);
}

int		is_auth_cmd_allowed(const char *cmd)
{
  int		check;
  check = (strcasecmp(cmd, "USER") == 0 ||
	   strcasecmp(cmd, "PASS") == 0 ||
	   strcasecmp(cmd, "QUIT") == 0);
  PRINT_DEBUG("is_auth_cmd_allowed: check=%d for '%s'", check, cmd);

  return (check);
}
