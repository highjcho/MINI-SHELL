NAME = minishell

INCLUDE_DIR = ./incudes/

RM = rm -rf

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)

SRCS_DIR = ./srcs/

OBJ_DIR = objs

SRCS = main.c \
		builtin/mini_pwd.c \
		# utils/art.c


MAN_SRCS = $(addprefix $(SRCS_DIR), $(SRCS))

# MAN_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(MAN_SRCS:.c=.o)))
MAN_OBJS = $(MAN_SRCS:.c=.o)

vpath %.c $(SRCS_DIR)

all: $(LIBFT) $(NAME)

$(NAME): $(MAN_OBJS)
	@$(CC) $(FLAG) $(LIBFT) -o $@ $(MAN_OBJS)
	@echo "making minishell"

$(LIBFT):
	@make -C ./libft

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c $(OBJ_DIR)
	@$(CC) $(FLAG) -c $< -o $@
clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./libft
	@echo "cleaning"
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft
	@echo "fcleaning"

re:
	make fclean
	make all

.PHONY: all re clean fclean bonus