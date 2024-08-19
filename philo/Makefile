# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2024/08/19 12:48:35 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM_NAME = philo

NAME = ${PROGRAM_NAME}
ARGS = 4 400 200 201
ARGS_HELGRIND = 4 400 200 201 3
CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3 -fsanitize=address
ifdef WITH_DEBUG
  NAME = ${PROGRAM_NAME}_debug
  CFLAGS = ${DFLAGS}
endif

INCLUDE_DIR = ./
INCLUDE_PATH = philo.h
INCLUDE = ${notdir $(INCLUDE_PATH)}

SRC_DIR = ./
SRC_PATH = main.c 01_args_utils.c 01_args.c 02_buffet_utils.c 02_buffet.c 03_diners.c 03_diners_utils.c 04_the_reaper.c
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

dataracescheck: all
	valgrind -q --tool=helgrind --log-file=valgrind.log ./${NAME} ${ARGS_HELGRIND}
	sh qa/mem_check.sh

run: all
	./${NAME} ${ARGS}

sanatize: debug
	./${PROGRAM_NAME}_debug ${ARGS}

one: all
	@echo "./philo 1 800 200 200"
	@echo "800 1 is thinking\n800 1 died" > ref.txt
	@./${NAME} 1 800 200 200 > stdout.txt
	@sh qa/tdd.sh
	@rm -f ref.txt stdout.txt
	
seven: all
	@echo "./philo 5 800 200 200 7"
	@echo "35" > ref.txt
	@./${NAME} 5 800 200 200 7 | grep "is eating" | wc -l | tr -d ' \t' > stdout.txt
	@sh qa/tdd.sh
	@rm -f ref.txt stdout.txt

onedeath: all
	@echo "./philo 4 310 200 100"
	@echo "1" > ref.txt
	@./${NAME} 4 310 200 100 | grep "died" | wc -l | tr -d ' \t' > stdout.txt
	@sh qa/tdd.sh
	@rm -f ref.txt stdout.txt

nodeath: all
	@echo "./philo 5 800 200 200"
	@echo "0" > ref.txt
	@timeout 10s ./${NAME} 5 800 200 200 | grep "died" | wc -l | tr -d ' \t' > stdout.txt
	@sh qa/tdd.sh
	@rm -f ref.txt stdout.txt
	
diehard: all
	@echo "./philo 4 410 200 100"
	@echo "0" > ref.txt
	@./${NAME} 4 310 200 100 | grep "died" | wc -l | tr -d ' \t' > stdout.txt
	@sh qa/tdd.sh
	@rm -f ref.txt stdout.txt

eval: one seven onedeath nodeath diehard

.PHONY: all clean fclean re debug print memcheck faultcheck dataracescheck run sanatize one seven onedeath nodeath diehard eval
