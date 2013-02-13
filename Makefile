NAME	=	avm

SRC_EXT	=	cpp
OBJ_EXT	=	o

CPU	=	./src/CPU/
CHIPSET	=	./src/Chipset/
MEMORY	=	./src/Memory/


SRC	=	$(CPU)CPU.cpp \
		$(CPU)main.cpp \
		$(CHIPSET)Chipset.cpp \
		$(MEMORY)Memory.cpp

OBJ	=	$(SRC:.$(SRC_EXT)=.$(OBJ_EXT))

INC	=	-I $(CPU) -I $(CHIPSET) -I $(MEMORY)

CC	=	g++

CPPFLAGS	+=	-Wall -W $(INC) -g


# Rules

all:	$(NAME)

%.$(OBJ_EXT): %.$(SRC_EXT)
	$(CC) -o $@ -c $< $(INC) $(CPPFLAGS)

$(NAME):	$(OBJ)
	$(CC) -o $@ $^ $(INC) $(CPPFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean	all

.PHONY:	clean fclean

## END
