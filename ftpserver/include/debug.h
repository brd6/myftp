/*
** debug.h for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 09:54:12 2017 bongol_b
** Last update Wed May 10 09:54:19 2017 bongol_b
*/

#ifndef DEBUG_H_
# define DEBUG_H_

# ifndef DEBUG
#  define PRINT_DEBUG(format, ...)
# else
#  define PRINT_DEBUG(format, ...) dprintf(2, "[DEBUG] %s:%d: "M"\n",\
					   __FILE__, __LINE__, ##VA_ARGS__)
# endif

#endif /* !DEBUG_H_ */
