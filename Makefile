HEADER		= includes/Map/map.h includes/Map/tree.h includes/Stack/stack.h includes/Map/tree_iterator.h includes/tree_u.h includes/pair.h includes/rev_iter.h\

LIB			= -Iincludes -Iincludes/Vector -Iincludes/Map -Iincludes/Stack

FLAGS		= -std=c++98 -Wall -Wextra -Werror
TEST_FLAGS	= -std=c++98 -g -Wall -Wextra -Werror

CC			= clang++

all:		main


main:		$(HEADER) main.cpp
			$(CC) $(TEST_FLAGS) $(LIB) main.cpp -o main

%.o:		%.cpp $(HEADER)
			$(CC) -g $(FLAGS) $(LIB) -c $< -o $@

clean:

fclean:		clean
			rm -rf main
			rm -rf map
			rm -rf vector
			rm -rf stack


re:			fclean all

.PHONY:		all clean fclean re