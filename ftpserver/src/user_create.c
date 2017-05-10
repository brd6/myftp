/*
** user_create.c for user_create in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 22:05:55 2017 bongol_b
** Last update Wed May 10 22:06:59 2017 bongol_b
*/

#include <string.h>
#include "myftp_server.h"

int	user_create(t_user *user,
		    char const *name,
		    char const *passwd,
		    char const *path)
{
  if ((user->name = strdup(name)) == NULL)
    return (0);
  if (passwd)
    {
      if ((user->password = strdup(passwd)) == NULL)
	return (0);
    }
  else
    user->password = NULL;
  if ((user->home_dir = strdup(path)) == NULL)
    return (0);
  return (1);
}
