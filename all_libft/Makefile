FT_PRINTF= ./ft_printf/
LIBFT= ./libft/
MAKE= make -C
MAKE_L= make bonus -C
all:
	@$(MAKE) $(FT_PRINTF) --no-print-directory
	@$(MAKE_L) $(LIBFT) --no-print-directory


clean:
	@$(MAKE) $(FT_PRINTF) clean --no-print-directory
	@$(MAKE_L) $(LIBFT) clean --no-print-directory

fclean: clean
	@$(MAKE) $(FT_PRINTF) fclean --no-print-directory
	@$(MAKE_L) $(LIBFT) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
