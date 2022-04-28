Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := make $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

all: test
clean:
	$Qrm -rf tmp get_next_line
fclean: clean
re: fclean all
init: | gnl_tester
deinit: fclean
	$Qrm -rf tmp
	$Qrm -rf gnl_tester
reinit: deinit init
refresh:
	$Qrm -rf get_next_line
	$Qcp -r ../../src get_next_line
test: init clean
	$Q$(MAKE) refresh
	$Qcp -r gnl_tester get_next_line
	$Q$(MAKE) -C get_next_line/gnl_tester a
.PHONY: all clean fclean re init deinit reinit refresh test

gnl_tester:
	$Qrm -rf tmp
	$Qgit clone --depth=1 https://github.com/Tripouille/gnlTester.git tmp
	$Qmv tmp gnl_tester
