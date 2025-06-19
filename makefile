SUBDIRS := Registry-Based-Persistence Service-Hijacking-Persistence

all:
	@for %%D in ($(SUBDIRS)) do ( \
		cd %%D && $(MAKE) && cd .. \
	)

clean:
	@for %%D in ($(SUBDIRS)) do ( \
		cd %%D && $(MAKE) clean && cd .. \
	)
