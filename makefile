#modifier la valeur de ce paramètre pour compiler avec options debug ou optimisation
TYPE=debug
#	debug / opt
	
CC= g++ -Iinclude/
CFLAGS = -W -Wall -ansi -pedantic -pipe
OPT= -O3
EXEC= prog
ifeq ($(TYPE),debug)
	FLAGS=$(CFLAGS) -g
else 
	ifeq ($(TYPE),opt)
		FLAGS=$(CFLAGS) $(OPT)
	else
		FLAGS=$(CFLAGS)
	endif
endif

# all : $(EXEC)
prog: Graph.o src/main.cpp
	$(CC) $^ -o bin/$@ $(FLAGS)

%.o : src/%.cpp include/%.h
	$(CC) -c $^ $(FLAGS) -o $@
clean:
	@ rm -f *.o
mrproper: clean
	@ rm -f bin/$(EXEC)  
