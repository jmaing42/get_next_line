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
test:
	$Q$(MAKE) -C test test
	@echo "Some test might need manual review"
publish_without_test:
ifndef GIT_REMOTE_URL
	$(error GIT_REMOTE_URL is undefined)
endif
	$Qrm -rf tmp
	$Qcp -r ./src ./tmp
	$Q$(MAKE) -C tmp fclean
	$Qprintf "# script-generated file list\nSRCS := %s\n\n" "$$(cd src && find . -name "*.c" | xargs)" | cat - src/Makefile > tmp/Makefile
	$Q(cd tmp && git init && git add . && git commit -m "Initial commit" && git push "$(GIT_REMOTE_URL)" HEAD:master) || (echo "Failed to publish" && false)
	$Qrm -rf tmp
	$Qgit push "$(GIT_REMOTE_URL)" HEAD:source || echo "Failed to push HEAD to source"
publish: test publish_without_test
.PHONY: all clean fclean re init deinit reinit refresh test publish publish_without_test
