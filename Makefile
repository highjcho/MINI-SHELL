NAME = minishell

INCLUDE_DIR = ./incudes/

RM = rm -rf

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)

SRCS_DIR = ./srcs/

SRCS = main.c \
		init/init_env.c \
		builtins/mini_echo.c \
		builtins/mini_cd.c \
		builtins/mini_pwd.c \
		builtins/mini_export.c \
		builtins/mini_unset.c \
		builtins/mini_env.c \
		builtins/mini_exit.c \
		error/error.c \
		utils/env_utils.c \
		utils/free.c \
		parse/tokenize.c \
		parse/tokenlist.c \
		parse/ast.c \
		parse/astnode.c \
		parse/env_substitution.c \
		parse/syntaxcheck.c \
		parse/ast_merge.c \
		test/test.c \
		# utils/art.c


MAN_SRCS = $(addprefix $(SRCS_DIR), $(SRCS))

# MAN_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(MAN_SRCS:.c=.o)))
MAN_OBJS = $(MAN_SRCS:.c=.o)

vpath %.c $(SRCS_DIR)

all: $(LIBFT) $(NAME)

$(NAME): $(MAN_OBJS)
	@$(CC) $(FLAGS) $(LIBFT) -o $@ $(MAN_OBJS)
	@echo "making minishell"

$(LIBFT):
	@make -C ./libft

clean:
	@$(RM) $(MAN_OBJS)
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