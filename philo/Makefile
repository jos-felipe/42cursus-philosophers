# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2024/08/05 12:52:56 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM_NAME = philo

NAME = ${PROGRAM_NAME}
ARGS = 4 200 400 201 3
ARGS_HELGRIND = 2 200 400 201 1
CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3
ifdef WITH_DEBUG
  NAME = ${PROGRAM_NAME}_debug
  CFLAGS = ${DFLAGS}
endif

INCLUDE_DIR = ./
INCLUDE_PATH = philo.h
INCLUDE = ${notdir $(INCLUDE_PATH)}

SRC_DIR = ./
SRC_PATH = main.c 01_args_utils.c 01_args.c 02_buffet_utils.c 02_buffet.c 03_start_the_meal.c 04_diners.c
SRC = ${notdir $(SRC_PATH)}

OBJ_DIR = ./obj
ifdef WITH_DEBUG
  OBJ_DIR = ./obj_debug
endif
OBJ_PATH = ${addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o)}

RM = rm -rf

all: ${OBJ_DIR} ${NAME}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE_PATH}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -c $< -o $@
	
${NAME}: ${OBJ_PATH}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ_PATH} -pthread

clean:
	${RM} ${OBJ_DIR}
	${RM} ${OBJ_DIR}_debug

fclean: clean
	${RM} ${NAME}
	${RM} ${NAME}_debug

re: fclean all

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

print:
	@echo "INCLUDE_PATH: ${INCLUDE_PATH}"
	@echo "SRC_PATH: ${SRC_PATH}"
	@echo "OBJ_PATH: ${OBJ_PATH}"

memcheck: all
	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./${NAME} ${ARGS}
	sh qa/mem_check.sh

faultcheck: all
	valgrind -s --track-origins=yes ./${NAME} ${ARGS}

dataracescheck: debug
	valgrind --tool=helgrind ./${NAME} ${ARGS_HELGRIND}

run: all
	./${NAME} ${ARGS}

.PHONY: all clean fclean re debug print memcheck faultcheck dataracescheck run 
