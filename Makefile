V = 1 
B = bin
O = obj
L = lib

LIB_COMPILE = gcc -g -std=gnu11 -fPIC -c -Wall
TEST_COMPILE = gcc -g -std=gnu11 -c

all: init lib_objects test_objects libso
cleanall: clean all

lib_objects: $O/script.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/ini.o \
	$O/prompt.o \
	$O/db.o \
	$O/cfg.o \
	$O/str.o \
	$O/run_cmd.o

test_objects: $B/hashtable_test \
	$B/script_test \
	$B/ordered_tree_str_test \
	$B/ordered_tree_generic_test \
	$B/ini_test \
	$B/str_test \
	$B/db_test

init:
	mkdir -p $O $B $L

clean:
	rm -rf $O $B $L

doxy:
	doxygen Doxyfile
	rm -rf doc/latex

libso:
	gcc -shared -Wl,-soname,libkitchensink.so.$V -o $L/libkitchensink.so.$V \
	$O/script.o \
	$O/cfg.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/ini.o \
	$O/db.o \
	$O/prompt.o \
	$O/str.o \
	$O/run_cmd.o


## TESTS

$B/str_test: $O/str.o  $O/str_test.o
	gcc -std=gnu11 -g -o $B/str_test $O/str_test.o $O/str.o -Wall

$O/str_test.o: src/str_test.c 
	gcc -std=gnu11 -g -c src/str_test.c -o $O/str_test.o

$B/script_test: $O/script.o  $O/script_test.o
	gcc -std=gnu11 -g -o $B/script_test $O/script_test.o $O/script.o $O/hashtable.o -Wall

$O/script_test.o: src/script_test.c 
	gcc -std=gnu11 -g -c src/script_test.c -o $O/script_test.o

$B/db_test: $O/db.o  $O/db_test.o
	gcc -std=gnu11 -g -o $B/db_test $O/db_test.o $O/db.o $O/prompt.o -Wall -lmysqlclient

$O/db_test.o: src/db_test.c 
	gcc -std=gnu11 -g -c src/db_test.c -o $O/db_test.o

$B/benchmark_test: $O/benchmark_test.o $O/script.o
	gcc -std=gnu11 -g -o $B/benchmark_test $O/benchmark_test.o $O/script.o -Wall -lrt -Isrc/vendor

$O/benchmark_test.o: src/benchmark_test.c src/script.h
	gcc -std=gnu11 -g -c src/benchmark_test.c -o $O/benchmark_test.o

$B/hashtable_test: $O/hashtable_test.o $O/hashtable.o
	gcc -std=gnu11 -g -o $B/hashtable_test $O/hashtable_test.o $O/hashtable.o -Isrc/vendor

$O/hashtable_test.o: src/hashtable_test.c 
	gcc -std=gnu11 -g -c src/hashtable_test.c -o $O/hashtable_test.o -Isrc/vendor

$B/ordered_tree_str_test: $O/ordered_tree_str_test.o $O/ordered_tree.o
	gcc -std=gnu11 -g -o $B/ordered_tree_str_test $O/ordered_tree_str_test.o $O/ordered_tree.o

$O/ordered_tree_str_test.o: src/ordered_tree_str_test.c src/ordered_tree.h
	gcc -std=gnu11 -g -c src/ordered_tree_str_test.c -o $O/ordered_tree_str_test.o

$B/ordered_tree_generic_test: $O/ordered_tree_generic_test.o $O/ordered_tree.o
	gcc -std=gnu11 -g -o $B/ordered_tree_generic_test $O/ordered_tree_generic_test.o $O/ordered_tree.o

$O/ordered_tree_generic_test.o: src/ordered_tree_generic_test.c src/ordered_tree.h
	gcc -std=gnu11 -g -c src/ordered_tree_generic_test.c -o $O/ordered_tree_generic_test.o

## LIB OBJECTS

$O/str.o: src/str.c
	gcc -std=gnu11 -g -c src/str.c -o $O/str.o

$O/cfg.o: src/cfg.c
	gcc -std=gnu11 -g -c src/cfg.c -o $O/cfg.o

$O/hashtable.o: src/vendor/hashtable.c
	gcc -std=gnu11 -g -c src/vendor/hashtable.c -o $O/hashtable.o

$O/run_cmd.o: src/run_cmd.c
	gcc -std=gnu11 -g -c src/run_cmd.c -o $O/run_cmd.o

$O/prompt.o: src/prompt.c
	gcc -std=gnu11 -g -c src/prompt.c -o $O/prompt.o

$O/db.o: src/db.c
	gcc -std=gnu11 -g -c src/db.c -o $O/db.o $O/prompt.o

$O/script.o: src/script.h src/script.c
	gcc -std=gnu11 -g -c src/script.c -o $O/script.o

$O/ordered_tree.o: src/ordered_tree.h src/ordered_tree.c
	gcc -std=gnu11 -g -c src/ordered_tree.c -o $O/ordered_tree.o

$O/ini.o: src/ini.h src/ini.c
	gcc -std=gnu11 -g -c src/ini.c -o $O/ini.o $O/hashtable.o

$B/ini_test: $O/ini_test.o $O/ini.o
	gcc -std=gnu11 -g -o $B/ini_test $O/ini_test.o $O/ini.o $O/hashtable.o

$O/ini_test.o: src/ini_test.c src/ini.h
	gcc -std=gnu11 -g -c src/ini_test.c -o $O/ini_test.o

