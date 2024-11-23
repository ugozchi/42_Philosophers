# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 23:04:20 by uzanchi           #+#    #+#              #
#    Updated: 2024/11/23 23:26:15 by uzanchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g

# Directories
SRCS_DIR	=	./sources/
HEAD_DIR	=	./includes/
OBJ_DIR		=	./objects/

RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
NC			=	\033[0m
BOLD		=	\033[1m


OK		=	✓
FAIL	=	✗
INFO	=	ⓘ
CLEAN	=	♻
TRASH	=	🗑
BAR_SIZE	=	50

# Source files
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
OBJS		=	$(addprefix ${OBJ_DIR}, $(notdir $(SRCS:.c=.o)))

all: project_logo ${OBJ_DIR} ${NAME}
	@echo "\n${GREEN}Compilation complete! ${NAME} is ready.${NC}"

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -I${HEAD_DIR} -o ${NAME}

${OBJ_DIR}:
	@if [ ! -d "${OBJ_DIR}" ]; then mkdir -p "${OBJ_DIR}"; fi

${OBJ_DIR}%.o: ${SRCS_DIR}%.c
	@TOTAL_FILES=${SRC_NR}; \
	COMPILED_FILES=$$(ls -1 $(OBJ_DIR) 2>/dev/null | wc -l); \
	COMPILED_FILES=$$(($$COMPILED_FILES + 1)); \
	PERCENT=$$(($$COMPILED_FILES * 100 / $$TOTAL_FILES)); \
	BLOCKS_FILLED=$$(($$PERCENT * $(BAR_SIZE) / 100)); \
	SPACES=$$(($(BAR_SIZE) - $$BLOCKS_FILLED)); \
	${CC} ${CFLAGS} -I${HEAD_DIR} -c $< -o $@; \
	clear; \
	printf "\n${BLUE} ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗ ${NC}\n"; \
	printf "${BLUE} ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝ ${NC}\n"; \
	printf "${BLUE} ██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗ ${NC}\n"; \
	printf "${BLUE} ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██║  ██║██╔══╝  ██╔═══╝ ╚════██║ ${NC}\n"; \
	printf "${BLUE} ██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║     ███████║ ${NC}\n"; \
	printf "${BLUE} ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝     ╚══════╝ ${NC}\n"; \
	printf "                             						 a 42 Project by ZANCHI Ugo      \n\n"; \
	printf "${CYAN}COMPILING PHILO\n\n${NC}"; \
	printf "Progress: ${GREEN}"; \
	for i in `seq 1 $$BLOCKS_FILLED`; do printf "▰"; done; \
	for i in `seq 1 $$SPACES`; do printf " "; done; \
	printf "   $$PERCENT%%\n${NC}"; \
	printf "Compiling $(notdir $<) ${GREEN}${OK}${NC}\n"; \
	sleep 0.1

clean:
				@if [ ! -d "${OBJ_DIR}" ]; \
				then \
					echo "${YELLOW}${INFO} Repo .o already clean${RESET}"; \
				else \
					echo "${RED}Removing all .o files${RESET}"; \
					rm -r ${OBJ_DIR}; \
				fi

fclean: clean
				@if [ -f "${NAME}" ]; then \
					echo "${RED}Removing ${NAME} files from root${RESET}"; \
					rm -f ${NAME}; \
				else \
					echo "${YELLOW}${INFO} ${NAME} already removed${RESET}"; \
				fi

re: fclean all

project_logo:
	@echo "																												   "
	@echo "${BLUE} ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗ ${NC}"
	@echo "${BLUE} ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝ ${NC}"
	@echo "${BLUE} ██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗ ${NC}"
	@echo "${BLUE} ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██║  ██║██╔══╝  ██╔═══╝ ╚════██║ ${NC}"
	@echo "${BLUE} ██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║     ███████║ ${NC}"
	@echo "${BLUE} ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝     ╚══════╝ ${NC}"
	@echo "                              a 42 Project by ZANCHI Ugo                               "

.PHONY: all clean fclean re 

