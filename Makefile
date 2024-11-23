# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 13:20:12 by uzanchi           #+#    #+#              #
#    Updated: 2024/11/23 21:54:24 by uzanchi          ###   ########.fr        #
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

SRC			=	checkers_utils.c \
				clean.c \
				global_utils.c \
				init.c \
				main.c \
				monitor_routine.c \
				philo_routine.c \
				state.c \
				thread.c

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
	@echo "																												   "
	@echo "${ROSE}  ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗  ${RESET}"
	@echo "${ROSE}  ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝  ${RESET}"
	@echo "${ROSE}  ██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗  ${RESET}"
	@echo "${ROSE}  ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██║  ██║██╔══╝  ██╔═██╗ ╚════██║  ${RESET}"
	@echo "${ROSE}  ██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║ ╚██╗███████║  ${RESET}"
	@echo "${ROSE}  ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝  ${RESET}"
	@echo "									a 42 Project by ZANCHI Ugo													   "

entry_message:
				@echo "${CYAN}\nCOMPILING $$(echo ${NAME} | tr '[:lower:]' '[:upper:]')\n${NC}${BOLD}Compiling necessary .o files out of ${SRC_NR} .c files in total${NC}"

.PHONY:			all clean fclean re project_logo entry_message