/*
** execute_system_command.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Sun May 14 12:21:35 2017 bongol_b
** Last update Sun May 21 21:28:20 2017 Berdrigue Bongolo-Beto
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "myftp_server.h"

static int	try_execute_cmd(const char *cmd, char *tmp_result_path)
{
  char		buff_cmd[BUFF_SIZE];

  sprintf(tmp_result_path, "%s/myftp_buff_%d", "/tmp", getpid());
  sprintf(buff_cmd, "%s > %s", cmd, tmp_result_path);
  system(buff_cmd);
  if (get_file_size(tmp_result_path) == -1)
    {
      memset(tmp_result_path, 0, sizeof(*tmp_result_path));
      memset(buff_cmd, 0, sizeof(buff_cmd));
      sprintf(tmp_result_path, "myftp_buff_%d", getpid());
      sprintf(buff_cmd, "%s > %s", cmd, tmp_result_path);
      system(buff_cmd);
    }
  return (1);
}

char		*execute_system_command(const char *cmd)
{
  char		*result;
  char		tmp_result_path[BUFF_SIZE];
  int		ret;
  int		file_size;
  int		fd;

  ret = try_execute_cmd(cmd, tmp_result_path);
  if (ret == 0 ||
      (file_size = get_file_size(tmp_result_path)) < 0 ||
      (result = malloc(sizeof(*result) * (file_size + 1))) == NULL ||
      (fd = open(tmp_result_path, O_RDONLY)) == -1 ||
      (ret = read(fd, result, file_size)) == -1)
    return (NULL);
  result[ret] = 0;
  close(fd);
  remove(tmp_result_path);
  return (result);
}
