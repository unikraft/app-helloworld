UK_ROOT ?= $(PWD)/.unikraft/unikraft
UK_LIBS ?= $(PWD)/.unikraft/libs
LIBS :=

all:
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS) $(MAKECMDGOALS)
