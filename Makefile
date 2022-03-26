# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouqssi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 15:40:56 by hbouqssi          #+#    #+#              #
#    Updated: 2022/02/11 15:41:04 by hbouqssi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SERVER = server.c
CLIENT = client.c

SRC = ft_putchar.c \
	  ft_putnbr.c \
	  ft_atoi.c

SERVER_BONUS = server_bonus.c
CLIENT_BONUS = client_bonus.c

OBJ_S = $(SERVER:.c=.o)
OBJ_C = $(CLIENT:.c=.o)

OBJ = $(SRC:.c=.o)

OBJ_S_BONUS = $(SERVER_BONUS:.c=.o)
OBJ_C_BONUS = $(CLIENT_BONUS:.c=.o)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(OBJ_S) $(OBJ_C)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_S)  -o server
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_C)  -o client

all : $(NAME)

bonus : $(OBJ) $(OBJ_S_BONUS) $(OBJ_C_BONUS)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_S_BONUS)  -o server_bonus
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_C_BONUS)  -o client_bonus

clean :
	$(RM) $(OBJ) $(OBJ_S) $(OBJ_C) $(OBJ_S_BONUS) $(OBJ_C_BONUS) server client server_bonus client_bonus

fclean : clean
	$(RM) $(NAME)

re: fclean $(NAME)
