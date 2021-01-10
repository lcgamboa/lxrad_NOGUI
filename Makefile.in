include Makefile.Conf

SUBDIRS= lib include docs utils
.PHONY: $(SUBDIRS) 

all:$(SUBDIRS) 

static:$(SUBDIRS) 

install:$(SUBDIRS)
	
clean:$(SUBDIRS)

uninstall:$(SUBDIRS)
	
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


