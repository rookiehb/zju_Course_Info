TARGET = conv
SOURCE = conv.cu

NVCC = nvcc
NVCCFLAGS += -O3 -cudart=shared -Xcompiler -fopenmp

$(TARGET):$(SOURCE)
	$(NVCC) $(SOURCE) -o $(TARGET) $(NVCCFLAGS)

.PHONY:run
run:
	$(NVCC) $(SOURCE) -o $(TARGET) $(NVCCFLAGS)
	./$(TARGET)

.PHONY:clean
clean:
	rm -rf $(TARGET)
