SUBDIRS = PortMonitors PrintMonitors SSP-SecuritySupportProvider TimeProvider

all:
	@for %%D in ($(SUBDIRS)) do ( \
		cd %%D && $(MAKE) && cd .. \
	)

clean:
	@for %%D in ($(SUBDIRS)) do ( \
		cd %%D && $(MAKE) clean && cd .. \
	)