TARGETS = c1 c2 c3 controller

CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=gnu99 -Werror

all: clean $(TARGETS)

$(TARGETS):
		$(CC_C) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(TARGETS)
