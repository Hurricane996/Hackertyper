bin_PROGRAMS = hackertyper
hackertyper_SOURCES = hackertyper.c hackertyper.h
hackertyper_LDADD = program_data.o

program_data.o:
	cp @program_data@ program_data
	$(LD) -r -b binary -o $@ program_data
	rm program_data
