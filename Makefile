CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
OBJS = main.o common.o employees.o budget.o suppliers.o assets.o reports.o

mfms: $(OBJS)
	$(CC) $(CFLAGS) -o mfms $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o mfms
