# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2024/06/26 13:32:11 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = new_project

NAME = ${PROJECT_NAME}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3
ifdef WITH_DEBUG
  NAME = ${PROJECT_NAME}_debug
  CFLAGS = ${DFLAGS}
endif

INCLUDE_DIR = ./include
INCLUDE_PATH = ${wildcard $(INCLUDE_DIR)/*.h}
INCLUDE = ${notdir $(INCLUDE_PATH)}

SRC_DIR = ./src
SRC_PATH = ${wildcard $(SRC_DIR)/*.c}
SRC = ${notdir $(SRC_PATH)}

OBJ_DIR = ./obj
ifdef WITH_DEBUG
  OBJ_DIR = ./obj_debug
endif
OBJ_PATH = ${addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o)}

LIBFT_DIR = ./lib/libft
LIBFT = libft.a
LIBFT_PATH = ${addprefix $(LIBFT_DIR), $(LIBFT)}

RM = rm -rf

all: libft ${OBJ_DIR} ${NAME}

libft:
	@make -C ${LIBFT_DIR} --no-print-directory

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE_PATH}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -c $< -o $@
	
$(OBJ_DIR)/main.o: main.c ${INCLUDE_PATH}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -c $< -o $@

${NAME}: ${OBJ_PATH} $(OBJ_DIR)/main.o
	${CC} ${CFLAGS} -o ${NAME} ${OBJ_PATH} $(OBJ_DIR)/main.o -L $(LIBFT_DIR) -lft

clean:
	${RM} ${OBJ_DIR}
	${RM} ${OBJ_DIR}_debug

fclean: clean
	${RM} ${NAME}
	${RM} ${NAME}_debug
	@make fclean -C ${LIBFT_DIR} --no-print-directory

re: fclean all

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

print:
	@echo "INCLUDE_PATH: ${INCLUDE_PATH}"
	@echo "SRC_PATH: ${SRC_PATH}"
	@echo "OBJ_PATH: ${OBJ_PATH}"

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}

.PHONY: all libft clean fclean re debug print valgrind


