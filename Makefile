# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 13:20:12 by uzanchi           #+#    #+#              #
#    Updated: 2024/10/19 18:12:52 by uzanchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler targets and libraries
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
NAME		=	philo

# Directories
SRCS_DIR	=	./sources/
HEAD_DIR	=	./includes/
OBJ_DIR		=	${SRCS_DIR}.o

# Colours, symbols and utils
GREEN		=	\033[1;32m
CYAN		=	\033[1;36m
YELLOW		=	\033[1;33m
RED			=	\033[1;31m
NC			=	\033[0m
BOLD		=	\033[1m
TICK		=	✓

SRC			=	utils1.c \
				utils2.c \
				end.c \
				init.c \
				main.c \
				monitor_routine.c \
				philo_routine.c

SRCS		=	$(addprefix ${SRCS_DIR}, ${SRC})
SRC_NR		=	$(words ${SRCS})

OBJS		=	$(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

all:			project_logo ${OBJ_DIR}
				@make -s ${NAME}

${NAME}:		entry_message ${OBJS}
				@${CC} ${CFLAGS} ${SRCS} -I${HEAD_DIR} -o ${NAME}
				@echo "${YELLOW}\nCompilation complete, ${NAME} executable at the root of the directory${NC}\n"

${OBJ_DIR}:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then mkdir -p "${OBJ_DIR}"; \
				fi

$(OBJ_DIR)/%.o:	$(SRCS_DIR)%.c
				@printf "%s" "Compiling $(notdir $<)"; \
				${CC} ${CFLAGS} -I${HEAD_DIR} -c $< -o $@; \
				printf "${GREEN}";
				printf " ${TICK}\n"; 
				printf "${NC}"; 

clean:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then \
					echo "Repo already clean"; \
				else \
					echo "Removing all .o files"; \
					rm -r ${OBJ_DIR}; \
				fi

fclean:			clean
				@echo "Removing ${NAME} executable"
				@rm -f ${NAME}

re:				fclean all

project_logo:
				@echo "${RED}   _     _     _     _     _     _     _     _     _     _     _     _  \n  / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \   / \ \n ( ${CYAN}P${RED} ) ( ${CYAN}h${RED} ) ( ${CYAN}i${RED} ) ( ${CYAN}l${RED} ) ( ${CYAN}o${RED} ) ( ${CYAN}s${RED} ) ( ${CYAN}o${RED} ) ( ${CYAN}p${RED} ) ( ${CYAN}h${RED} ) ( ${CYAN}e${RED} ) ( ${CYAN}r${RED} ) ( ${CYAN}s${RED} )\n  \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/ \n\n                                             ${NC}a 42 project by ${BOLD}Ugo Zanchi${NC}"

entry_message:
				@echo "${CYAN}\nCOMPILING $$(echo ${NAME} | tr '[:lower:]' '[:upper:]')\n${NC}${BOLD}Compiling necessary .o files out of ${SRC_NR} .c files in total${NC}"

.PHONY:			all clean fclean re project_logo entry_message