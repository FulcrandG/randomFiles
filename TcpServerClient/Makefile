##
## Makefile for UdpMulticastSocket in /home/guilhem/Bureau/testUdp/C/
##
## Made by Guilhem Fulcrand
## Login   <guilhem.fulcrand@epitech.eu>
##
## Started on  Fri Sep 22 10:26:13 2017 Guilhem Fulcrand
## Last update Thu Oct 12 14:40:36 2017 Guilhem Fulcrand
##

CC	=	gcc

CFLAGS 	=	-Wall -Wextra
CFLAGS	+=	$(INCLUDE)

SRC 	= 	main.c		\
		client.c	\
		server.c	\
		utils.c

OBJ 	= 	$(SRC:.c=.o)

INCLUDE	=	-Iinclude/

NAME	=	testTcp

RM 	=	rm -f

all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
