
all: prisoners-1 prisoners-2
	@echo All done.

prisoners-1:
	cc -Wall -o $@ ./prisoners-solution-1.c

prisoners-2:
	cc -Wall -o $@ ./prisoners-solution-2.c
