CC = cc
C_FLAGS = -Wall -Wextra -Werror -Ift
LIBFLAGS = -lreadline -Lft -lft
SRCS =
OBJS =
NAME = minishell
LIBFT = libft.a

all: $(NAME)

$(NAME): 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS)

%.o: %.c


