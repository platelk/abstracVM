NAME	=	avm

SRC_EXT	=	cpp
OBJ_EXT	=	o

SRC	=

OBJ	=	$(SRC:.$(SRC_EXT)=.$(OBJ_EXT))

INC	=	-I $(INC_DIR)

CC	=	g++

CFLAGS	+=	-Wall -W


# Rules

all:	$(NAME)

%.$(OBJ_EXT): %.$(SRC_EXT)
	$(CC) -o $@ -c $< $(INC) $(CFLAGS)

$(NAME):	$(OBJ)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean	all

.PHONY:	clean fclean

## END
