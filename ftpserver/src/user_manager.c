/*
** user_create.c for user_create in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 22:05:55 2017 bongol_b
** Last update Sat May 13 12:05:50 2017 bongol_b
*/

#include <stdio.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

static t_user	g_users[] = {
  {"anonymous", "", "/"},
  {"brd6", "brd6", "/home/brd6"},
  {"bongol_b", "123", "/home/bongol_b"},
  {0, 0, 0}
};

static int	get_user_index(const char *name)
{
  int		i;

  i = 0;
  while (g_users[i].name[0])
    {
      PRINT_DEBUG("user_index : name='%s', pass='%s'", g_users[i].name, g_users[i].pass);
      if (strcasecmp(g_users[i].name, name) == 0)
	return (i);
      i++;
    }
  return (UNKNOW_USER_IDX);
}

int		user_get(const char *name, t_user *user)
{
  int		user_idx;

  if ((user_idx = get_user_index(name)) == UNKNOW_USER_IDX)
    return (0);
  *user = g_users[user_idx];
  PRINT_DEBUG("user_get : name='%s', pass='%s'", user->name, user->pass);
  return (1);
}

int		user_change_home(const char *user_name, const char *home_dir)
{
  int		user_idx;

  if ((user_idx = get_user_index(user_name)) == UNKNOW_USER_IDX)
    return (0);
  strcpy(g_users[user_idx].home_dir, home_dir);
  g_users[user_idx].home_dir[strlen(home_dir)] = 0;
  return (1);
}

int		user_try_auth(const char *user_name,
			      const char *pass)
{
  t_user	user;

  PRINT_DEBUG("user_try_auth: name='%s' pass='%s'", user_name, pass);
  if (user_get(user_name, &user) == 0)
    {
      PRINT_DEBUG("user_try_auth: name='%s' pass='%s' > fail", user_name, pass);
      return (0);
    }
  PRINT_DEBUG("user_get : name='%s', pass='%s'", user.name, user.pass);
  PRINT_DEBUG("user_try_auth: true pass='%s' vs user_pass=%s", user.pass, pass);
  return (strcmp(user.pass, pass) == 0);
}
