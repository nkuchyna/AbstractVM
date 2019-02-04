# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 17:48:06 by nkuchyna          #+#    #+#              #
#    Updated: 2018/11/22 17:48:08 by nkuchyna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 = avm
OBJ_DIR  = ./obj/
SRC_DIR  = ./src/
COMPFLAG = -Wall -Wextra -Werror
SRC		 = main.cpp Lexer.cpp eOperand.cpp Token.cpp NewStack.cpp OperandFactory.cpp Parser.cpp Executor.cpp
OBJ		 = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
HDRS 	 =	-I ./inc/
INC		 = ./inc/Lexer.hpp ./inc/eOperand.hpp ./inc/Token.hpp ./inc/NewStack.hpp ./inc/OperandFactory.hpp\
			./inc/Parser.hpp ./inc/Executor.hpp ./inc/AbstractVM.hpp
COMP	 = clang++


all: $(NAME)

$(NAME): $(OBJ)
	$(COMP) $(OBJ) -o $(NAME) $(HDRS)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC)
	$(COMP) -c $< -o $@ $(COMPFLAG) $(HDRS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean format re
