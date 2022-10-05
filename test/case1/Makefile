Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := make $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

all: test
.PHONY: all

.PHONY: refresh
refresh:
	$Qrm -rf tmp
	$Qmkdir -p tmp
	$Qcp ../../src/get_next_line.h ../../src/get_next_line.c ../../src/get_next_line_utils.c tmp/
	$Qcp build.mk tmp/Makefile
	$Q$(MAKE) -f test.mk test BUFFER_SIZE=1
	$Q$(MAKE) -f test.mk test BUFFER_SIZE=2
	$Q$(MAKE) -f test.mk test BUFFER_SIZE=4
	$Q$(MAKE) -f test.mk test BUFFER_SIZE=42
	$Q$(MAKE) -f test.mk test BUFFER_SIZE=4242
	$Q$(MAKE) -f test.mk test BUFFER_SIZE=42424242

.PHONY: test
test: refresh
