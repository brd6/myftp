/*
** commands.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 18:38:09 2017 bongol_b
** Last update Sat May 13 11:21:26 2017 bongol_b
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
  {"CWD", cmd_cwd_execute},
  {"CDUP", cmd_cdup_execute},
  {"DELE", cmd_dele_execute},
  {"PASV", cmd_pasv_execute},
  {"PORT", cmd_port_execute},
  {"HELP", cmd_help_execute},
  {"NOOP", cmd_noop_execute},
  {"RETR", cmd_retr_execute},
  {"STOR", cmd_stor_execute},
  {"LIST", cmd_list_execute},
  {"SYST", cmd_syst_execute},
  {NULL, NULL}
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

void		get_debug_available_cmds(char *buff)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  buff[0] = 0;
  while (g_cmds[i].command)
    {
      sprintf(&buff[strlen(buff)], " %s", g_cmds[i].command);
      if (i % 14 == 0 && i != 0 && g_cmds[i + 1].command)
	sprintf(&buff[strlen(buff)], "\r\n");
      i++;
    }
  sprintf(&buff[strlen(buff)], "\r\n");
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
