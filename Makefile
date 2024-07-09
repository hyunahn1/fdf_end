# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunahn <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 13:27:50 by hyunahn           #+#    #+#              #
#    Updated: 2024/07/05 14:38:55 by hyunahn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I minilibx-linux -I srcs/include -I srcs_bonus/include_bonus -I common_utils
LDFLAGS = -L minilibx-linux -lmlx -lXext -lX11 -lm

RM = rm -f

# 공통 유틸리티 파일들
COMMON_UTILS_PATH = common_utils/
COMMON_UTILS_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_error.c ft_putendl_fd.c ft_split.c ft_strchr.c ft_strjoin.c ft_strlen.c ft_strrstr.c get_next_line.c
COMMON_UTILS_SRCS = $(addprefix ${COMMON_UTILS_PATH}, ${COMMON_UTILS_FILES})
COMMON_UTILS_OBJS = $(COMMON_UTILS_SRCS:.c=.o)

# 메인 유틸리티 파일들
UTILS_PATH = srcs/utils/
UTILS_FILES = act_map_func.c command_set.c draw.c iso.c parsing.c ft_free.c
UTILS_SRCS = $(addprefix ${UTILS_PATH}, ${UTILS_FILES})
UTILS_OBJS = $(UTILS_SRCS:.c=.o) $(COMMON_UTILS_OBJS)

# 메인 소스 파일들
MAIN_SRCS = srcs/main.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

# 보너스 유틸리티 파일들
BONUS_UTILS_PATH = srcs_bonus/utils_bonus/
BONUS_UTILS_FILES = act_map_func_bonus.c command_set_bonus.c draw_bonus.c iso_bonus.c parsing_bonus.c ft_free_bonus.c
BONUS_UTILS_SRCS = $(addprefix ${BONUS_UTILS_PATH}, ${BONUS_UTILS_FILES})
BONUS_UTILS_OBJS = $(BONUS_UTILS_SRCS:.c=.o) $(COMMON_UTILS_OBJS)

# 보너스 소스 파일들
BONUS_MAIN_SRCS = srcs_bonus/main_bonus.c
BONUS_MAIN_OBJS = $(BONUS_MAIN_SRCS:.c=.o)

# 헤더 파일들
BONUS_HEADERS = srcs_bonus/include_bonus/fdf_bonus.h
HEADERS = srcs/include/fdf.h

ifdef BONUS
	CUR_MAIN_OBJS = $(BONUS_MAIN_OBJS)
	CUR_UTILS_OBJS = $(BONUS_UTILS_OBJS)
	CUR_HEADERS = $(BONUS_HEADERS)
else
	CUR_MAIN_OBJS = $(MAIN_OBJS)
	CUR_UTILS_OBJS = $(UTILS_OBJS)
	CUR_HEADERS = $(HEADERS)
endif

.PHONY: all re clean fclean

all: ${NAME}

%.o: %.c ${CUR_HEADERS} common_utils/common_utils.h
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${CUR_UTILS_OBJS} ${CUR_MAIN_OBJS}
	${CC} ${CUR_UTILS_OBJS} ${CUR_MAIN_OBJS} ${LDFLAGS} -o $@
	@echo "Build complete: ${NAME} has been created."

bonus:
	${MAKE} BONUS=1 ${NAME}

clean:
	${RM} $(UTILS_OBJS) $(MAIN_OBJS) $(BONUS_UTILS_OBJS) $(BONUS_MAIN_OBJS) $(COMMON_UTILS_OBJS)
	@echo "Clean complete: Object files removed."

fclean: clean
	${RM} ${NAME}
	@echo "Full clean complete: ${NAME} removed."

re: fclean all

