SRCDIR = src
INCDIR = include
OBJDIR = build

SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCS = $(wildcard $(INCDIR)/*.hpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o) $(OBJDIR)/$(MAIN_FILE:.cpp=.o)

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++23
CFLAGS2 = -lsfml-graphics -lsfml-window -lsfml-system

NAME = main.out
MAIN_FILE = main.cpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CFLAGS2) 

$(OBJDIR)/$(MAIN_FILE:.cpp=.o): $(MAIN_FILE) $(INCS)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCS)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

clean:
	rm -f $(OBJS)
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f *.out

re: fclean all

run: all
	./$(NAME)