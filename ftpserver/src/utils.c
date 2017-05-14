/*
** utils.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 20:33:33 2017 bongol_b
** Last update Sun May 14 12:35:24 2017 bongol_b
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "myftp_server.h"

int		skip_space(const char *str)
{
  int		i;

  i = 0;
  while (str && (str[i] == WORD_SEPS[0] || str[i] == WORD_SEPS[1]))
    i++;
  return (i);
}

int		get_file_size(const char *file_name)
{
  struct stat	st;

  return (stat(file_name, &st) == 0 ? st.st_size : -1);
}
