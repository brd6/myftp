/*
** service_handle.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 23:42:04 2017 bongol_b
** Last update Thu May 11 01:05:48 2017 bongol_b
*/

#include "myftp_server.h"

/* static int	service_loop() */
/* { */
/*   return (1); */
/* } */

/* static void	service_stop() */
/* { */

/* } */

void		service_handler(t_config const *config, int client_sock_fd)
{
  //printf("ok");
  (void)config;
  (void)client_sock_fd;
}
