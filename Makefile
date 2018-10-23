# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abytko <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/31 20:02:17 by abytko            #+#    #+#              #
#    Updated: 2018/09/27 17:23:51 by abytko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
SRCDIR = ./src/
OBJDIR = ./obj/
INC = ./includes/
LIBDIR = ./lib
SRC = ft_ssl.c ft_md5.c ft_func.c ft_view_hash.c ft_flag_hash.c ft_sha256.c
FLAG = -Wall -Werror -Wextra
LIBFTFLAGS = -lft -L $(LIBDIR)/libft/
LIBFTPRINTFFLAGS = -lftprintf -L $(LIBDIR)/ft_printf/
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME):$(OBJ)
	make -C $(LIBDIR)/libft/
	make -C $(LIBDIR)/ft_printf/
	gcc $(FLAG) -o $(NAME) $(OBJ) -I $(INC) $(LIBFTFLAGS) $(LIBFTPRINTFFLAGS)

$(OBJDIR)%.o: %.c
	gcc -c $< -o $@ $(FLAG) -I $(INC)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)/libft
	make clean -C $(LIBDIR)/ft_printf

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBDIR)/libft
	make fclean -C $(LIBDIR)/ft_printf

re: fclean all

vpath %.c $(SRCDIR)
