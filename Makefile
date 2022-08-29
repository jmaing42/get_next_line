Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := make $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

all: test
clean:
	$Qrm -rf ./tmp
	$Q$(MAKE) -C src clean
	$Q$(MAKE) -C test clean
	@printf "\033[0m"
fclean: clean
	$Q$(MAKE) -C src fclean
	$Q$(MAKE) -C test fclean
	@printf "\033[0m"
re:
	$Q$(MAKE) -C src fclean
	$Q$(MAKE) test
init:
	$Q$(MAKE) -C test init
deinit:
	$Q$(MAKE) -C test deinit
reinit:
	$Q$(MAKE) -C test reinit
refresh:
	$Q$(MAKE) -C test refresh
test: generate_bonus
	$Q$(MAKE) -C src/test test
	$Q$(MAKE) -C test test
	@echo "Some test might need manual review"
generate_bonus:
	$Qpatch -o src/get_next_line_bonus.h src/get_next_line.h src/get_next_line.h.patch
	$Qpatch -o src/get_next_line_bonus.c src/get_next_line.c src/get_next_line.c.patch
	$Qpatch -o src/get_next_line_utils_bonus.c src/get_next_line_utils.c src/get_next_line_utils.c.patch
publish_without_test: generate_bonus
ifndef GIT_REMOTE_URL
	$(error GIT_REMOTE_URL is undefined)
endif
	$Qrm -rf tmp
	$Qmkdir tmp
	$Qcp ./src/get_next_line.h ./src/get_next_line.c ./src/get_next_line_utils.c ./src/get_next_line_bonus.h ./src/get_next_line_bonus.c ./src/get_next_line_utils_bonus.c ./tmp
	$Q(cd tmp && git init && git add . && git commit -m "Initial commit" && git push "$(GIT_REMOTE_URL)" HEAD:master) || (echo "Failed to publish" && false)
	$Qrm -rf tmp
	$Qgit push "$(GIT_REMOTE_URL)" HEAD:source || echo "Failed to push HEAD to source"
publish: test publish_without_test
.PHONY: all clean fclean re init deinit reinit refresh test generate_bonus publish publish_without_test

.PHONY: compile_commands.json
compile_commands.json:
	@make -C src ../compile_commands.json
