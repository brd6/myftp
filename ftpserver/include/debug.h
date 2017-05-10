/*
** debug.h for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 09:54:12 2017 bongol_b
** Last update Wed May 10 10:46:20 2017 bongol_b
*/

#ifndef DEBUG_H_
# define DEBUG_H_

# define COLOR_RED	"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_YELLOW	"\x1b[33m"
# define COLOR_BLUE	"\x1b[34m"
# define COLOR_MAGENTA	"\x1b[35m"
# define COLOR_CYAN	"\x1b[36m"
# define COLOR_RESET	"\x1b[0m"

# ifndef DEBUG
#  define PRINT_DEBUG(format, ...)
# else
#  define PRINT_DEBUG(format, ...) dprintf(2, COLOR_RED "[DEBUG]" COLOR_RESET \
					   " %s:%d: " format "\n", \
					   __FILE__, __LINE__, ##__VA_ARGS__)
# endif

#endif /* !DEBUG_H_ */
