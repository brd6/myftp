##
## Makefile for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp
## 
## Made by Berdrigue Bongolo-Beto
## Login   <bongol_b@epitech.net>
## 
## Started on  Mon May  8 16:38:17 2017 Berdrigue Bongolo-Beto
## Last update Wed May 10 23:46:19 2017 bongol_b
##

CC		=	gcc

DEBUG_CFLAGS	=	-g3 -DDEBUG
RELEASE_CFLAGS	=	-W -Wall -Wextra -Werror

DIR_SERVER	=	ftpserver
NAME_SERVER	= 	server

SRCS_SERVER	= 	$(DIR_SERVER)/src/main.c \
			$(DIR_SERVER)/src/myftp_server.c \
			$(DIR_SERVER)/src/server_create.c \
			$(DIR_SERVER)/src/socket_debug_utils.c \
			$(DIR_SERVER)/src/user_create.c \
			$(DIR_SERVER)/src/service_handler.c \

OBJS_SERVER	= 	$(SRCS_SERVER:.c=.o)

DIR_CLIENT	=	ftpclient
NAME_CLIENT	=	client

SRCS_CLIENT	= 	$(DIR_CLIENT)/src/main.c \

OBJS_CLIENT	= 	$(SRCS_CLIENT:.c=.o)

#CFLAGS 		+= 	$(RELEASE_CFLAGS)

#CFLAGS		+= 	-I./$(DIR_SERVER)/include/
#CFLAGS 		+= 	-I./$(DIR_CLIENT)/include/


all: CFLAGS += 	$(RELEASE_CFLAGS)
all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): CFLAGS += -I./$(DIR_SERVER)/include/
$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): CFLAGS += -I./$(DIR_CLIENT)/include/
$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(NAME_SERVER)

clean:
	$(RM) $(OBJS_SERVER)
	$(RM) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(NAME_SERVER)
	$(RM) $(NAME_CLIENT)

re: fclean all

.PHONY: clean, re, all, fclean
