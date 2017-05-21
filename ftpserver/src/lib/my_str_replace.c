/*
** my_str_replace.c for my_str_replace in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 12:46:38 2016 Berdrigue BONGOLO BETO
** Last update Sun May 21 21:27:15 2017 Berdrigue Bongolo-Beto
*/

#include <string.h>
#include <stdlib.h>

static int	my_strlen(const char *str)
{
  return ((str == NULL || str[0] == 0) ? 0 : strlen(str));
}

int		count_occurence(char *search, char *subject, int n, int *cp2)
{
  int		cp;
  char		*s;

  cp = 0;
  s = strstr(subject, search);
  while (s)
    {
      cp++;
      if (n > 1 && cp == n)
	break;
      s = strstr(s + my_strlen(search), search);
    }
  *cp2 = 0;
  return (cp);
}

static char	*my_strncpy(char *dest, char *src, int n)
{
  int		i;

  i = 0;
  while (src[i] && i < n)
    {
      dest[i] = src[i];
      i = i + 1;
    }
  if (n >= i)
    dest[i] = 0;
  return (dest);
}

char		*my_str_replace(char *search,
				char *replace,
				char *subject,
				int n)
{
  int		size;
  char		*str;
  char		*old;
  char		*s;
  int		cp;

  size = count_occurence(search, subject, n, &cp);
  size = (my_strlen(replace) - my_strlen(search)) * size + my_strlen(subject);
  if ((str = malloc(sizeof(*str) * (size + 1))) == NULL)
    return (NULL);
  str[0] = 0;
  old = subject;
  s = strstr(subject, search);
  while (s)
    {
      my_strncpy(str + my_strlen(str), old, s - old);
      strcpy(str + my_strlen(str), replace);
      old = s + my_strlen(search);
      s = strstr(s + my_strlen(search), search);
      if (n > 1 && cp == n)
	break;
      cp++;
    }
  strcpy(str + my_strlen(str), old);
  return (str);
}
