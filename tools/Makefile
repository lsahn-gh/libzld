CFLAGS = -I../src -I../src/include
CFLAGS += -g
LDFLAGS = -L../src -lzld

SOURCES = $(shell find . -name "*.c")
OBJS = $(SOURCES:.c=.o)

TARGET = send

.PHONY: all
all: ${TARGET}

$(TARGET): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

.PHONY: clean
clean:
	-${RM} ${TARGET} ${OBJS}
