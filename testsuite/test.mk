# Set VALGRIND to 1 to use valgrind
VALGRIND = 0
# Set TEE to 1 to tee ouput to stdout
TEE = 0

INC_DIR = ../../include/

HDRS = $(shell find . -name "*.h")
SRCS = $(shell find . -name "*.c")
OBJS = $(patsubst %.c,%.o,$(SRCS))
LIB = ../../lib/libohcp.a
EXE = $(patsubst %.c,%.out,$(SRCS))
LOG = $(patsubst %.c,%.log,$(SRCS))

ifeq ($(VALGRIND),1)
VALGRIND_BIN = $(shell which valgrind)
VALGRIND_CMD = $(subst valgrind,valgrind --leak-check=full --show-leak-kinds=all,$(VALGRIND_BIN))
else
VALGRIND_CMD =
endif

ifeq ($(TEE),1)
CMD = $(VALGRIND_CMD) ./$(EXE) 2>&1 | tee $(LOG)
else
CMD = $(VALGRIND_CMD) ./$(EXE) > $(LOG) 2>&1
endif

.PHONY: build test clean distclean selftest

build: $(EXE)

test: $(EXE)
	$(CMD)

$(EXE): $(OBJS) $(LIB)
	gcc -g -o $@ $^

%.o: %.c $(HDRS) $(INC_DIR)
	gcc -c -g -std=c99 -pedantic -Wall -Wextra -Wshadow $(addprefix -I,$(INC_DIR)) -o $@ $<

%.o: %.cpp $(HDRS) $(INC_DIR)
	g++ -c -g -std=c++11 -pedantic -Wall -Wextra -Wshadow $(addprefix -I,$(INC_DIR)) -o $@ $<

clean:
	@rm -vf $(OBJS)
	@rm -vf *.log

distclean: clean
	@rm -vf $(EXE)

selftest:
	@echo 'INC_DIR = $(INC_DIR)'
	@echo 'HDRS = $(HDRS)'
	@echo 'SRCS = $(SRCS)'
	@echo 'OBJS = $(OBJS)'
	@echo 'LIB = $(LIB)'
	@echo 'EXE = $(EXE)'
	@echo 'VALGRIND_BIN = $(VALGRIND_BIN)'
	@echo 'VALGRIND = $(VALGRIND)'
	@echo 'CMD = "'"$(CMD)"'"'
