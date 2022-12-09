NAME	= libft.a

GCC		= gcc -Wall -Werror -Wextra

SRC		+= ft_memset.c
SRC		+= ft_bzero.c
SRC		+= ft_memcpy.c
SRC		+= ft_memccpy.c
SRC		+= ft_memchr.c
SRC		+= ft_memcmp.c
SRC		+= ft_strlen.c
SRC		+= ft_strdup.c
SRC		+= ft_strlcat.c
SRC		+= ft_strlcpy.c
SRC		+= ft_strchr.c
SRC		+= ft_strrchr.c
SRC		+= ft_strncmp.c
SRC		+= ft_atoi.c
SRC		+= ft_isalpha.c
SRC		+= ft_isdigit.c
SRC		+= ft_isalnum.c
SRC		+= ft_isprint.c
SRC		+= ft_toupper.c
SRC		+= ft_tolower.c
SRC		+= ft_strnstr.c
SRC		+= ft_itoa.c
SRC		+= ft_putchar_fd.c
SRC		+= ft_putendl_fd.c
SRC		+= ft_putstr_fd.c
SRC		+= ft_putnbr_fd.c
SRC		+= ft_strjoin.c
SRC		+= ft_substr.c
SRC		+= ft_strmapi.c
SRC		+= ft_memmove.c
SRC		+= ft_isascii.c
SRC		+= ft_calloc.c
SRC		+= ft_strtrim.c
SRC		+= ft_split.c
SRCBON	+= ft_lstnew.c
SRCBON	+= ft_lstadd_front.c
SRCBON	+= ft_lstsize.c
SRCBON	+= ft_lstlast.c
SRCBON	+= ft_lstadd_back.c
SRCBON	+= ft_lstdelone.c
SRCBON	+= ft_lstclear.c
SRCBON	+= ft_lstiter.c
SRCBON	+= ft_lstmap.c

OBJ		+= $(subst .c,.o,$(SRC))

OBJBON	+= $(subst .c,.o,$(SRCBON))

INC		+= libft.h

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	ar rc $@ $^
	ranlib $@

bonus : $(OBJBON) $(INC)
	ar rc libft.a $^
	ranlib libft.a

%.o: %.c $(INC)
	$(GCC) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(OBJBON)

fclean: clean
	rm -rf $(NAME)

re: fclean all
