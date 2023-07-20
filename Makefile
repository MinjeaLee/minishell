NAME	=	minishell

cc 		= 	cc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
RM		=	rm -rf

READLINE_FLAGS		= -L$(HOME)/.brew/opt/readline/lib
READLINE_INCLUDE	= -I$(HOME)/.brew/opt/readline/include

INCLUDES	=	includes/
LIBFT_DIR	=	srcs/Libft
LIBFT		= 	srcs/Libft/libft.a
LIBFT_INC	=	-L$(LIBFT_DIR) -lft


SRCS		=	srcs/main.c							\
				srcs/utils/init.c					\
				srcs/utils/error.c					\
				srcs/utils/free.c					\
				srcs/utils/sig.c					\
				srcs/utils/export_utils.c			\
				srcs/lst/ft_lstclear.c				\
				srcs/lst/ft_lstinit.c				\
				srcs/lst/ft_lstdelone.c				\
				srcs/lst/ft_lstpush_back.c			\
				srcs/make_cmd_info/make_cmd_info.c	\
				srcs/make_cmd_info/syntax_check.c	\
				srcs/make_cmd_info/change_env.c		\
				srcs/make_cmd_info/special_env.c	\
				srcs/make_cmd_info/make_pipe.c		\
				srcs/builtin/builtin.c				\
				srcs/exe_cmd/exe_cmd.c				\
				srcs/exe_cmd/here_doc.c				\
				srcs/exe_cmd/exe_child.c			\
				srcs/exe_cmd/set_fd.c				\
				srcs/exe_cmd/re_set_fd.c			\
				srcs/builtin/exe_cd.c				\
				srcs/builtin/exe_echo.c				\
				srcs/builtin/exe_env.c				\
				srcs/builtin/exe_exit.c				\
				srcs/builtin/exe_export.c			\
				srcs/builtin/exe_pwd.c				\
				srcs/builtin/exe_unset.c			\
				srcs/parsing/dequoted_merge_utils.c	\
				srcs/parsing/make_quote_split_strs_utils.c	\
				srcs/parsing/new_quote_split_list_utils.c	\
				srcs/parsing/node_free.c			\
				srcs/parsing/parsing_utils.c		\
				srcs/parsing/parsing.c				\
				srcs/parsing/quote_utils.c			\
				srcs/parsing/quote.c				\
				srcs/parsing/remove_quote_node.c	\
				srcs/parsing/remove_quote.c			\
				srcs/parsing/split_quote_utils.c



OBJS 		= $(SRCS:.c=.o)

.PHONY	: all
all		: $(NAME)

$(NAME)	: $(OBJS) $(INCLUDES)
	$(MAKE) -C $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -lreadline -o $(NAME)

%.o		: %.c
			$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES) $(READLINE_INCLUDE)


.PHONY	: clean
clean	:
			@$(MAKE) -C $(LIBFT_DIR) clean
			rm -rf $(OBJS) 

.PHONY	: fclean
fclean	:
			@$(MAKE) -C $(LIBFT_DIR) fclean
			rm -rf $(OBJS)
			rm -rf $(NAME)

.PHONY	: re
re		:
			@make fclean
			@make all