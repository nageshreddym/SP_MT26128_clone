CC = gcc
CFLAGS = -pthread
TARGET = matrix
SRC = MT26128_A2_Task4_pthread_matrix.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
