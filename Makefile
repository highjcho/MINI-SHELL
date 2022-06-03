NAME = minishell

INCLUDE_DIR = ./incudes/

RM = rm -rf

LIBFT = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror -g3 -I $(INCLUDE_DIR)

READLINE_FLAG = -I $(HOME)/.brew/opt/readline/include -lreadline -L${HOME}/.brew/opt/readline/lib


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
		parse/pipelinelist.c \
	    redirect/dup_file.c \
		redirect/ast_redirect_process.c \
		execute/execute.c \
		execute/builtin.c \
		execute/execve.c \
		test/test.c \
		# utils/art.c


MAN_SRCS = $(addprefix $(SRCS_DIR), $(SRCS))

# MAN_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(MAN_SRCS:.c=.o)))
MAN_OBJS = $(MAN_SRCS:.c=.o)

vpath %.c $(SRCS_DIR)

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(MAN_OBJS)
	@$(CC) $(FLAGS) $(READLINE_FLAG) $(LIBFT) -o $@ $(MAN_OBJS)
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