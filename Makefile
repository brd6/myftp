##
## Makefile for my_objdump-my_nm in /home/bongol_b/Epitech-rendu/TEK2/B4 - Système Unix - Mémoire/PSU_2016_nmobjdump
## 
## Made by Berdrigue Bongolo-Beto
## Login   <bongol_b@epitech.net>
## 
## Started on  Wed Feb 22 23:30:52 2017 Berdrigue Bongolo-Beto
## Last update Sat Feb 25 00:17:44 2017 Berdrigue Bongolo-Beto
##

DEBUG_CFLAGS	=	-g3 -DDEBUG

RELEASE_CFLAGS	=	-W -Wall -Wextra -Werror

DIR_OBJDUMP	=	objdump

NAME_OBJDUMP	= 	my_objdump

DIR_NM		=	nm

NAME_NM		=	my_nm

SRCS_OBJDUMP	= 	$(DIR_OBJDUMP)/src/main.c \
			$(DIR_OBJDUMP)/src/my_objdump.c \
			$(DIR_OBJDUMP)/src/error_check.c \
			$(DIR_OBJDUMP)/src/print_file_header.c \
			$(DIR_OBJDUMP)/src/print_section_contents.c \
			$(DIR_OBJDUMP)/src/print_file_header_utils.c \
			$(DIR_OBJDUMP)/src/print_section_contents_utils.c

SRCS_NM		= 	$(DIR_NM)/src/main.c \
			$(DIR_NM)/src/my_nm.c \
			$(DIR_NM)/src/error_check.c \
			$(DIR_NM)/src/sort_syms.c \
			$(DIR_NM)/src/cmp_sym_names.c \
			$(DIR_NM)/src/get_sym_type.c \
			$(DIR_NM)/src/print_sym.c \

OBJS_OBJDUMP	= 	$(SRCS_OBJDUMP:.c=.o)

OBJS_NM		= 	$(SRCS_NM:.c=.o)

CFLAGS 		+= 	$(RELEASE_CFLAGS)

CFLAGS		+=	-I./$(DIR_NM)/include/ -I./$(DIR_OBJDUMP)/include/

all: $(NAME_OBJDUMP) $(NAME_NM)

nm: $(NAME_NM)

objdump: $(NAME_OBJDUMP)

$(NAME_OBJDUMP): $(OBJS_OBJDUMP)
	$(CC) $(OBJS_OBJDUMP) -o $(NAME_OBJDUMP)

$(NAME_NM): $(OBJS_NM)
	$(CC) $(OBJS_NM) -o $(NAME_NM)

debug: CFLAGS += $(DEBUG_CFLAGS)

debug: all

clean:
	$(RM) $(OBJS_NM)
	$(RM) $(OBJS_OBJDUMP)

fclean:
	$(RM) $(NAME_NM)
	$(RM) $(NAME_OBJDUMP)

re: fclean all

.PHONY: clean, re, all, fclean nm objdump
