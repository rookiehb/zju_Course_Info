C_SRC = $(sort $(wildcard *.c))
OBJ = $(patsubst %.c,%.o,$(C_SRC))

file = print.o
all:$(OBJ)
	

%.o:%.c
	@echo ${OBJ}
	@echo $(shell pwd)	
	${GCC} ${CFLAG} -c $< -o $@ 

clean:
	$(shell rm *.o 2>/dev/null)
