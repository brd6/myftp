/*
** errors.h for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 08:24:59 2017 bongol_b
** Last update Wed May 10 21:56:09 2017 bongol_b
*/

#ifndef ERRORS_H_
# define ERRORS_H_

# define USAGE			"Usage : %s port path\n"

# define ERR_PROG_FIRST_ARG	"Error: the port must be superior to 0\n"

# define ERR_SERVER_CREATE	"Error: Unable to create the ftp server \
on port: %d\n"
# define ERR_INIT_SOCKET	"Error: Unable to initialize the socket\n"
# define ERR_INIT_SOCKET_BIND	"Error: Unable to bind the socket\n"
# define ERR_INIT_SOCKET_LISTEN	"Error: Unable to listen the socket\n"
# define ERR_SOCKET_ACCEPT	"Error: Unable to accept client on the socket\n"
# define ERR_CREATE_USER	"Error: Unable to create an user\n"

#endif /* !ERRORS_H_ */
