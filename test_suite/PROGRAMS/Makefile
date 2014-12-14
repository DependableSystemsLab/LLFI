progs = deadlock factorial mcf memcpy1 mpi sudoku2 bfs 

defalt: all

all:
	for prog in $(progs); do \
		$(MAKE) -C $$prog; \
	done
    
clean:
	for prog in $(progs); do \
		$(MAKE) -C $$prog clean; \
	done
