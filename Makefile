INCS = \
	include/*.h
SRCS = \
	src/ohcp_string.c \
	src/ohcp_deque.c \
	src/ohcp_stats.c \
	src/ohcp_type.c \
	src/ohcp_node.c \
	src/ohcp_port.c \
	src/ohcp_expr.c \
	src/ohcp_module.c \
	src/ohcp_bit.c \
	src/ohcp_logic.c \
	src/ohcp_expr_vector.c \
	src/ohcp_expr_struct.c \
	src/ohcp_expr_buf.c \
	src/ohcp_expr_inv.c \
	src/ohcp_expr_and.c \
	src/ohcp_expr_or.c \
	src/ohcp_expr_xor.c \
	src/ohcp_expr_mux.c \
	src/ohcp_expr_rel.c \
	src/ohcp_expr_flop.c \
	src/ohcp.c
OBJS = $(patsubst %.c,%.o,$(subst src/,obj/,$(SRCS)))
LIB = lib/libohcp.a

INC_DIRS = $(sort $(dir $(INCS)))
SRC_DIRS = $(sort $(dir $(SRCS)))
OBJ_DIRS = $(sort $(dir $(OBJS)))
LIB_DIR = $(dir $(LIB))

.PHONY: lib test clean distclean selftest

lib: $(LIB)

$(LIB): $(OBJS) | $(LIB_DIR)
	ar rcs $@ $^

$(LIB_DIR):
	@mkdir -pv $@

$(OBJ_DIRS):
	@mkdir -pv $@

obj/%.o: src/%.c $(INCS) | $(OBJ_DIRS)
	gcc -c -g -std=c11 -pedantic -Wall -Wextra -Wshadow $(addprefix -I,$(INC_DIRS)) -o $@ $<

obj/%.o: src/%.cpp $(INCS) | $(OBJ_DIRS)
	g++ -c -g -std=c++11 -Wall -Wextra -Wshadow $(addprefix -I,$(INC_DIRS)) -o $@ $<

clean:
	@$(MAKE) -C testsuite clean
	@rm -vf $(OBJS)
	@rm -vfr $(OBJ_DIRS)

distclean: clean
	@$(MAKE) -C testsuite distclean
	@rm -vf $(LIB)
	@rm -vfr $(LIB_DIR)

test: lib
	$(MAKE) -C testsuite test

selftest:
	@echo $(INCS)
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(LIB)
	@echo $(INC_DIRS)
	@echo $(SRC_DIRS)
	@echo $(OBJ_DIRS)
	@echo $(LIB_DIR)
	@echo $(MAKE)
	@echo $(MAKEFLAGS)
