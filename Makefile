NAME = 		pipex

SRC = 				pipex.c children.c split_command.c commands.c utils.c

SRC_BONUS = 		pipex_bonus.c children_bonus.c utils_bonus.c split_command.c commands.c utils.c

LIBFT =				libft/libft.a

MANDATORY_FLAG = 	.mandatory_built

BONUS_FLAG = 		.bonus_built


$(MANDATORY_FLAG): $(SRC) $(LIBFT) pipex.h
	cc -Wall -Wextra -Werror -Ilibft/include $(SRC) $(LIBFT) -o $(NAME)
	@touch $(MANDATORY_FLAG)
	@rm -f $(BONUS_FLAG)

$(BONUS_FLAG): $(SRC_BONUS) $(LIBFT) pipex_bonus.h
	cc -Wall -Wextra -Werror -Ilibft/include $(SRC_BONUS) $(LIBFT) -o $(NAME)
	@touch $(BONUS_FLAG)
	@rm -f $(MANDATORY_FLAG)

all: $(MANDATORY_FLAG)
bonus: $(BONUS_FLAG)

$(LIBFT): 
	make -C libft

clean:
	make -C libft clean

fclean:
	make -C libft fclean
	rm -f $(NAME)
	@rm -f  $(MANDATORY_FLAG) $(BONUS_FLAG)

re: fclean all

.PHONY: all bonus clean fclean re