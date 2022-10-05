ifeq ($(BUFFER_SIZE),)
$(error Bad BUFFER_SIZE)
else
export BUFFER_SIZE
endif

.PHONOY: test
test:
	$Q-$(MAKE) -C tmp PROFILE=debug
	$Q-$(MAKE) -C tmp PROFILE=release
	$Q-$(MAKE) -C tmp SANITIZER=address PROFILE=debug
	$Q-$(MAKE) -C tmp SANITIZER=address PROFILE=release
	$Q-$(MAKE) -C tmp SANITIZER=leak PROFILE=debug
	$Q-$(MAKE) -C tmp SANITIZER=leak PROFILE=release
	$Q-$(MAKE) -C tmp SANITIZER=memory PROFILE=debug
	$Q-$(MAKE) -C tmp SANITIZER=memory PROFILE=release
	$Q-$(MAKE) -C tmp SANITIZER=undefined PROFILE=debug
	$Q-$(MAKE) -C tmp SANITIZER=undefined PROFILE=release
