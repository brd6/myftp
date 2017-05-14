/*
** my_str_replace.c for my_str_replace in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 12:46:38 2016 Berdrigue BONGOLO BETO
** Last update Sun May 14 14:17:22 2017 bongol_b
*/

#include <string.h>
#include <stdlib.h>

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
      s = strstr(s + strlen(search), search);
    }
  *cp2 = 0;
  return (cp);
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
  size = (strlen(replace) - strlen(search)) * size + strlen(subject);
  if ((str = malloc(sizeof(*str) * (size + 1))) == NULL)
    return (NULL);
  str[0] = 0;
  old = subject;
  s = strstr(subject, search);
  while (s)
    {
      strncpy(str + strlen(str), old, s - old);
      strcpy(str + strlen(str), replace);
      old = s + strlen(search);
      s = strstr(s + strlen(search), search);
      if (n > 1 && cp == n)
	break;
      cp++;
    }
  strcpy(str + strlen(str), old);
  return (str);
}
