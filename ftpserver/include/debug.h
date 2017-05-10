/*
** debug.h for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 09:54:12 2017 bongol_b
** Last update Thu May 11 00:49:46 2017 bongol_b
*/

#ifndef DEBUG_H_
# define DEBUG_H_

# include <errno.h>
# include <string.h>
# include <stdio.h>

# define COLOR_RED	"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_BLUE	"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN	"\x1b[36m"
# define COLOR_RESET	"\x1b[0m"

# define PRINT_ERRNO() (errno != 0 ? strerror(errno) : 0)

# ifndef DEBUG
#  define PRINT_DEBUG(format, ...)
#  define PRINT_WARNING(format, ...)
#  define PRINT_ERROR(format, ...)
# else
#  define PRINT_DEBUG(format, ...) dprintf(2, "[DEBUG]" format "\n",	\
					   ##__VA_ARGS__)
#  define PRINT_WARNING(format, ...) dprintf(2, COLOR_YELLOW "[WARN]"	\
					     COLOR_RESET		\
					     " %s:%d: errno: %s - "format"\n", \
					     __FILE__, __LINE__, \
					     PRINT_ERRNO(),	 \
					     ##__VA_ARGS__)
#  define PRINT_ERROR(format, ...) dprintf(2, COLOR_RED "[ERROR]"	\
					   COLOR_RESET			\
					   " %s:%d: errno: %s - "format"\n", \
					   __FILE__, __LINE__, PRINT_ERRNO, \
					   ##__VA_ARGS__)
# endif

#endif /* !DEBUG_H_ */
