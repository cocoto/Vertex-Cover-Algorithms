#modifier la valeur de ce paramètre pour compiler avec options debug ou optimisation
TYPE=opt
#	debug / opt
	
CC= g++ -Iinclude/
CFLAGS = -W -Wall -ansi -pedantic -pipe -lpthread
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
prog: Graph.o arb-vc.o function2approx.o functionKernelVC.o heuristic.o src/main.cpp
	$(CC) $^ -o bin/$@ $(FLAGS)

%.o : src/%.cpp include/%.h
	$(CC) $< -c $(FLAGS)
	
clean:
	@ rm -f *.o
mrproper: clean
	@ rm -f bin/$(EXEC)  
