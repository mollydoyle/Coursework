CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
LIBS=		-lcrypto
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/duplicates

all:		$(TARGETS)

# TODO: Add rules for bin/unit_hash, bin/unit_pair, bin/unit_table, bin/duplicates
src/duplicates.o : src/duplicates.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^


src/hash.o : src/hash.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/pair.o : src/pair.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/table.o : src/table.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^



lib/libtable.a: src/hash.o src/pair.o src/table.o
	@echo Linking $@...
	@$(AR) $(ARFLAGS) $@ $^

bin/duplicates: src/duplicates.o lib/libtable.a
	@echo Linking $@...
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_hash: tests/unit_hash.o lib/libtable.a
	@echo Linking $@...
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_pair: tests/unit_pair.o lib/libtable.a
	@echo Linking $@...
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/unit_table: tests/unit_table.o lib/libtable.a
	@echo Linking $@...
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

tests/unit_hash.o : tests/unit_hash.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)

tests/unit_pair.o : tests/unit_pair.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)


tests/unit_table.o : tests/unit_table.c 
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^ $(LIBS)





test:			test-hash test-pair test-table test-duplicates test-quiz

test-pair:		bin/unit_pair
	@bin/test_pair.sh

test-hash:		bin/unit_hash
	@bin/test_hash.sh

test-table:		bin/unit_table
	@bin/test_table.sh

test-duplicates:	bin/test_duplicates.sh bin/duplicates
	@bin/test_duplicates.sh

test-quiz:		bin/test_quiz.py answers.json
	@bin/test_quiz.py

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_pair bin/unit_hash bin/unit_table lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
