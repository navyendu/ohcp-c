# Set to 1 to tee output to stdout
TEE = 0

LIST = $(filter %/,$(shell ls -p))

.PHONY: test clean distclean selftest

build test clean distclean:
	for i in $(LIST); do \
		$(MAKE) -f ../test.mk TEE='$(TEE)' -C $$i $@; \
	done

selftest:
	@echo "LIST = $(LIST)"
