NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD -MP -I ./includes -I ./libft/includes
MAKEFLAGS += --no-print-directory
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
DIR_DUP = mkdir -p $(@D)

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

SRCS_DIR = src
OBJS_DIR = objs
LEXER_DIR := $(SRCS_DIR)/lexer

SRCS := main.c \
				interactive_mode.c \
				non_interactive_mode.c \
				signals.c \
				set_env.c

LEXER_SRC := lexer_utils.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
LEXER_SRC := $(addprefix $(LEXER_DIR)/, $(LEXER_SRC))

ALL_SRCS := $(SRCS) $(LEXER_SRC)
# LEXER_OBJS := $(patsubst $(LEXER_DIR)/%.c, $(OBJS_DIR)/%.o, $(LEXER_SRC))
#
OBJS := $(ALL_SRCS:%.c=$(OBJS_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBFT) -lreadline -o $@
	@echo "$(GREEN)🛠️ Finished compiling $(NAME) objects$(RESET)"
	@echo "$(GREEN)🚀 $@ was created$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJS_DIR)
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) clean
	@echo "$(RED)🧹 $(NAME) objects removed$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) fclean
	@echo "$(RED)💥 $(NAME) deleted$(RESET)"

re: fclean all
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) re
	@echo "$(BLUE)🔄 $(NAME) rebuild$(RESET)"


.PHONY: all clean fclean re
