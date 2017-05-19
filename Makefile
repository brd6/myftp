##
## Makefile for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp
## 
## Made by Berdrigue Bongolo-Beto
## Login   <bongol_b@epitech.net>
## 
## Started on  Mon May  8 16:38:17 2017 Berdrigue Bongolo-Beto
## Last update Fri May 19 17:36:29 2017 bongol_b
##

CC		=	gcc

DEBUG_CFLAGS	=	-g3 -DDEBUG
RELEASE_CFLAGS	=	-W -Wall -Wextra -Werror

DIR_SERVER	=	ftpserver
NAME_SERVER	= 	server

SRCS_SERVER_CMD	=	$(DIR_SERVER)/src/command_manager.c \
			$(DIR_SERVER)/src/commands/cmd_user.c \
			$(DIR_SERVER)/src/commands/cmd_pass.c \
			$(DIR_SERVER)/src/commands/cmd_quit.c \
			$(DIR_SERVER)/src/commands/cmd_pwd.c \
			$(DIR_SERVER)/src/commands/cmd_cwd.c \
			$(DIR_SERVER)/src/commands/cmd_cdup.c \
			$(DIR_SERVER)/src/commands/cmd_dele.c \
			$(DIR_SERVER)/src/commands/cmd_pasv.c \
			$(DIR_SERVER)/src/commands/cmd_port.c \
			$(DIR_SERVER)/src/commands/cmd_help.c \
			$(DIR_SERVER)/src/commands/cmd_noop.c \
			$(DIR_SERVER)/src/commands/cmd_retr.c \
			$(DIR_SERVER)/src/commands/cmd_stor.c \
			$(DIR_SERVER)/src/commands/cmd_list.c \
			$(DIR_SERVER)/src/commands/cmd_syst.c \
			$(DIR_SERVER)/src/commands/cmd_type.c \
			$(DIR_SERVER)/src/commands/cmd_size.c \

SRCS_MY_LIB	=	$(DIR_SERVER)/src/lib/my_wordtab_to_str.c \
			$(DIR_SERVER)/src/lib/my_get_char_pos.c \
			$(DIR_SERVER)/src/lib/my_str_split.c \
			$(DIR_SERVER)/src/lib/my_free_wordtab.c \
			$(DIR_SERVER)/src/lib/my_wordtab_count.c \
			$(DIR_SERVER)/src/lib/my_str_replace.c \
			$(DIR_SERVER)/src/lib/get_next_line.c \


SRCS_SERVER	= 	$(DIR_SERVER)/src/main.c \
			$(DIR_SERVER)/src/myftp_server.c \
			$(DIR_SERVER)/src/server_create.c \
			$(DIR_SERVER)/src/socket_debug_utils.c \
			$(DIR_SERVER)/src/user_manager.c \
			$(DIR_SERVER)/src/service_handler.c \
			$(DIR_SERVER)/src/packet_manager.c \
			$(DIR_SERVER)/src/packet_manager_message.c \
			$(DIR_SERVER)/src/response_manager.c \
			$(SRCS_SERVER_CMD) \
			$(DIR_SERVER)/src/utils.c \
			$(SRCS_MY_LIB) \
			$(DIR_SERVER)/src/service_authentification.c \
			$(DIR_SERVER)/src/client_create.c \
			$(DIR_SERVER)/src/execute_system_command.c \
			$(DIR_SERVER)/src/setup_data_mode.c \
			$(DIR_SERVER)/src/parse_packet_args.c \


OBJS_SERVER	= 	$(SRCS_SERVER:.c=.o)

all: CFLAGS += 	$(RELEASE_CFLAGS)
all: $(NAME_SERVER)

$(NAME_SERVER): CFLAGS += -I./$(DIR_SERVER)/include/
$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(OBJS_SERVER) -o $(NAME_SERVER)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(NAME_SERVER)

clean:
	$(RM) $(OBJS_SERVER)

fclean: clean
	$(RM) $(NAME_SERVER)

re: fclean all

.PHONY: clean, re, all, fclean
