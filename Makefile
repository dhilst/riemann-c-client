subdirs := src

.PHONY : all 
all :
	cd src; $(MAKE)

clean : 
	find . -name "*~" -exec rm {} \;
	find . -name "cscope.*" -exec rm {} \;
	for d in $(subdirs) ; do \
		cd $$d ; $(MAKE) clean ; \
	done
