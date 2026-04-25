PLATFORM ?= SDL

all:
ifeq ($(PLATFORM),SDL)
	cmake -S. -Bbuild
	cmake --build build
else ifeq ($(PLATFORM),N64)
	+$(MAKE) -f Makefile_n64.mk
else ifeq ($(PLATFORM),WII)
	+$(MAKE) -f Makefile_wii.mk
else
	@echo error: No platform named $(PLATFORM)!
endif

clean:
	rm -rf build filesystem *.dol *.elf *.z64 *.pak
.PHONY: clean