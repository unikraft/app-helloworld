UK_ROOT ?= $(PWD)/../../unikraft
UK_LIBS ?= $(PWD)/../../libs
LIBS :=

# Set the default verbosity level to silent
MAKEFLAGS += -s

# Override the default verbosity level if V is defined
ifeq ($(V),1)
	MAKEFLAGS :=
endif

all:
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS) $(MAKECMDGOALS)
