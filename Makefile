##
## EPITECH PROJECT, 2024
## nm_objdump
## File description:
## Makefile
##

CC 			= 	gcc

NAME		=	ftrace

SRC			:= main.c
SRC			+= ftrace.c
SRC			+= c_syscall.c
# Finder
SRC			+= e8_finder.c
SRC			+= 9a_finder.c
SRC			+= symbole_finder.c
# Utils
SRC			+= my_str_to_word_array.c
SRC			+= exit.c
SRC			+= help.c
# TO MOVE
SRC			+= stack.c

VPATH		:=	src/
VPATH		+=	src/finder/
VPATH		+=	src/utils/

vpath %.c $(VPATH)

BUILD_DIR	=	build

OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)

DIE			=	exit 84

IFLAGS		=	-I ./include/
CFLAGS		=	-Wall -Wextra $(IFLAGS)

TMP_FILES	=	*.gcno					\
    			*.gcda					\
    			vgcore.*				\
    			*.log					\
    			temp.txt				\
    			coding-style-reports.log\
    			-r $(BUILD_DIR)			\
    			$(OBJ)

# ------ DISPLAY -------- #

NB_FILES	= $(shell echo $(SRC) | wc -w)

ECHO 		= echo
C_RESET 	= \033[00m
C_RED		= \e[31m
C_GREEN 	= \e[32m
C_YELLOW 	= \e[33m
C_BLUE		= \e[34m
C_PINK		= \e[35m
C_GREY		= \e[37m
C_FULL_RED	= \e[41m
# ----------------------- #

all:		$(NAME)

%:
	@ $(ECHO) "$(C_RED)|==========> RULE NOT FOUND. <==========|$(C_RESET)"

%.c:
	@ $(ECHO) "$(C_RED)[KO] -> $@$(C_RESET)" && $(DIE)

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ $(ECHO) "$(C_GREEN)[OK]$(C_GREY) -> $<$(C_RESET)"

$(NAME):	$(OBJ)
	@ $(CC) -o $@ $^ -lelf
	@ $(ECHO) -n "$(C_PINK)|==========> $(NAME) compiled "
	@ $(ECHO) "with $(NB_FILES) file(s). <==========|$(C_RESET)"

clean:
	@ $(RM) $(TMP_FILES)

fclean:		clean
	@ $(RM) $(NAME)

re:		fclean all

debug: CFLAGS += -g
debug: CFLAGS += -Werror
debug: re

.PHONY: all re clean fclean debug
