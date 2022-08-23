all: test

COMMON_RULES = test clean fclean
$(COMMON_RULES):
	find . -type d -maxdepth 1 -mindepth 1 | xargs -I {} $(MAKE) -C {} $@

re: fclean
	$(MAKE) all
