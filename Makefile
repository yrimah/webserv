NAME	:= webserv

CC		:=	c++
CPPFLAGS:=	-Wall -Wextra -Werror -fsanitize=address
CPPFLAG	:=	-std=c++98

SRCS	:=	webserv.cpp srcs/conf_reader.cpp srcs/conf_parser.cpp
INCS	:=	incs/parse_config/
OBJS	:=	$(SRCS:.cpp=.o)

%.o:%.cpp
	$(CC)  $(CPPFLAGS) $(CPPFLAG) -c $< -o $@

all:		$(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(OBJS) -I $(INCS) $(CPPFLAGS) $(CPPFLAG) -o $@

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
