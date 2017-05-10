/*
** myftp_server.h for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:36:13 2017 Berdrigue Bongolo-Beto
** Last update Wed May 10 10:07:33 2017 bongol_b
*/

#ifndef MYFTP_SERVER_H_
# define MYFTP_SERVER_H_

/*
** Config
*/
# define SERVER_LISTEN_BACKLOG	5

typedef struct	s_user
{
  char		*name;
  char		*password;
  char		*home_dir;
}		t_user;

int		server_create(int *sock_fd, int port);

#endif /* !MYFTP_SERVER_H_ */