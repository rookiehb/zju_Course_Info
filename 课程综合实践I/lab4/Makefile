CC=mpiicc
CFLAGS=-mcmodel=medium
# compiler may crash when static array too large,
# add `-mcmodel=medium` in this case.

all:
	$(CC) -o gemm hw_baseline.cpp -Ofast $(CFLAGS) -mavx2 -g -fopenmp -parallel

.PHONY: run
run: all
	I_MPI_PMI_LIBRARY=/usr/lib/x86_64-linux-gnu/libpmi.so.0 srun -N 4 -n 16 -c 8 ./gemm

.PHONY: clean
clean:
	rm -rf *.o gemm
