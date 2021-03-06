# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: p <p@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/12 23:33:03 by p                 #+#    #+#              #
#    Updated: 2015/07/26 19:00:22 by p                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = npuzzle

# Compilation settings
CC = clang++ -std=c++11
CFLAGS = -Werror -Wextra -Wall -O3

# Custom paths
DIR_SRCS = srcs/
DIR_OBJS = objs/
DIR_INCS = -Iincs/

#------------------------------------------------------------------------------#

FILES =	main.cpp \
		Grid.cpp \
		Solver.cpp \
		Parser.cpp \
		Heuristics.cpp \
		Exceptions.cpp \

#------------------------------------------------------------------------------#

# Apply custom paths
SRCS = $(addprefix $(DIR_SRCS), $(FILES))
OBJS = $(addprefix $(DIR_OBJS), $(FILES:.cpp=.o))

# Colors
RED = \x1b[31;01m
GREEN = \x1b[32;01m
CYAN = \x1b[34;01m
RESET = \x1b[39;49;00m

# Rules
all: $(NAME)
	
$(NAME): $(OBJS)
	@ printf "Linking  "
	@ $(CC) $(OBJS) $(CFLAGS) $(DIR_INCS) -o $(NAME)
	@ printf "$(GREEN)DONE$(RESET)\n"
	@ echo "Program $(RED)$(NAME)$(RESET) -> $(GREEN)COMPLETED$(RESET)"

$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
	@ echo "Building $(CYAN)$< $(RESET)"
	@ mkdir -p $(DIR_OBJS)
	@ $(CC) $(CFLAGS) $(DIR_INCS) -c $< -o $@

clean:
	@ rm -f $(OBJS)
	@ rm -rf $(DIR_OBJS)
	@ echo "Clean    $(GREEN)DONE$(RESET)"

fclean: clean
	@ rm -f $(NAME)
	@ echo "Fclean   $(GREEN)DONE$(RESET)"

re: fclean all

.PHONY: all clean fclean re