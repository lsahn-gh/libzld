CFLAGS = -fPIC -Wall -Wextra -Werror -pedantic -O2 -g
CFLAGS += -Wno-error=unused-function
LDFLAGS = -shared
TARGET_LIB = libzld.so

CFLAGS += $(shell find . -type d | xargs printf -- '-I%s ')
SOURCES = $(shell find . -name "*.c")
OBJS = $(SOURCES:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS}
