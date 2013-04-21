V = 1 
B = bin
O = obj
L = lib

LIB_COMPILE = gcc -g -std=gnu11 -fPIC -c -Wall
TEST_COMPILE = gcc -g -std=gnu11 -c -fPIC

all: init lib_objects test_objects libso
cleanall: clean all
test: clean all
	./bin/hashtable_test
	echo 
	./bin/ordered_tree_generic_test
	echo 
	./bin/ordered_tree_str_test
	echo 
	./bin/str_test
	echo 
	./bin/script_test
	echo 
	./bin/cfg_test
	echo 
	#./bin/db_test

lib_objects: $O/script.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/prompt.o \
	$O/db.o \
	$O/cfg.o \
	$O/cfg_simple.o \
	$O/str.o \
	$O/run_cmd.o

test_objects: $B/hashtable_test \
	$B/script_test \
	$B/ordered_tree_str_test \
	$B/ordered_tree_generic_test \
	$B/str_test \
	$B/cfg_test \
	$B/db_test

init:
	mkdir -p $O $B $L

clean:
	rm -rf $O $B $L

doxy:
	doxygen Doxyfile
	rm -rf doc/latex

libso:
	gcc -shared -fPIC -Wl,-soname,libkitchensink.so.$V -o $L/libkitchensink.so.$V \
	$O/script.o \
	$O/cfg.o \
	$O/cfg_simple.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/db.o \
	$O/prompt.o \
	$O/str.o \
	$O/run_cmd.o


## TESTS

$B/cfg_test: $O/cfg.o  $O/cfg_test.o
	gcc -fPIC -std=gnu11 -g -o $B/cfg_test $O/cfg_test.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o -Wall

$O/cfg_test.o: src/cfg_test.c 
	gcc -fPIC -std=gnu11 -g -c src/cfg_test.c -o $O/cfg_test.o

$B/str_test: $O/str.o  $O/str_test.o
	gcc -fPIC -std=gnu11 -g -o $B/str_test $O/str_test.o $O/str.o -Wall

$O/str_test.o: src/str_test.c 
	gcc -fPIC -std=gnu11 -g -c src/str_test.c -o $O/str_test.o

$B/script_test: $O/script.o  $O/script_test.o
	gcc -fPIC -std=gnu11 -g -o $B/script_test $O/script_test.o $O/script.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o -Wall

$O/script_test.o: src/script_test.c 
	gcc -fPIC -std=gnu11 -g -c src/script_test.c -o $O/script_test.o

$B/db_test: $O/db.o  $O/db_test.o
	gcc -fPIC -std=gnu11 -g -o $B/db_test $O/db_test.o $O/db.o $O/prompt.o -Wall -lmysqlclient

$O/db_test.o: src/db_test.c 
	gcc -fPIC -std=gnu11 -g -c src/db_test.c -o $O/db_test.o

$B/timing_test: $O/timing_test.o $O/script.o
	gcc -fPIC -std=gnu11 -g -o $B/timing_test $O/timing_test.o $O/script.o -Wall -lrt -Isrc/vendor

$O/timing_test.o: src/timing_test.c src/script.h
	gcc -fPIC -std=gnu11 -g -c src/timing_test.c -o $O/timing_test.o

$B/hashtable_test: $O/hashtable_test.o $O/hashtable.o
	gcc -fPIC -std=gnu11 -g -o $B/hashtable_test $O/hashtable_test.o $O/hashtable.o -Isrc/vendor

$O/hashtable_test.o: src/hashtable_test.c 
	gcc -fPIC -std=gnu11 -g -c src/hashtable_test.c -o $O/hashtable_test.o -Isrc/vendor

$B/ordered_tree_str_test: $O/ordered_tree_str_test.o $O/ordered_tree.o
	gcc -fPIC -std=gnu11 -g -o $B/ordered_tree_str_test $O/ordered_tree_str_test.o $O/ordered_tree.o

$O/ordered_tree_str_test.o: src/ordered_tree_str_test.c src/ordered_tree.h
	gcc -fPIC -std=gnu11 -g -c src/ordered_tree_str_test.c -o $O/ordered_tree_str_test.o

$B/ordered_tree_generic_test: $O/ordered_tree_generic_test.o $O/ordered_tree.o
	gcc -fPIC -std=gnu11 -g -o $B/ordered_tree_generic_test $O/ordered_tree_generic_test.o $O/ordered_tree.o

$O/ordered_tree_generic_test.o: src/ordered_tree_generic_test.c src/ordered_tree.h
	gcc -fPIC -std=gnu11 -g -c src/ordered_tree_generic_test.c -o $O/ordered_tree_generic_test.o





## LIB OBJECTS

$O/str.o: src/str.c
	gcc -fPIC -std=gnu11 -g -c src/str.c -o $O/str.o

$O/cfg.o: src/cfg.c
	gcc -fPIC -std=gnu11 -g -c src/cfg.c -o $O/cfg.o

$O/cfg_simple.o: src/cfg_simple.c
	gcc -fPIC -std=gnu11 -g -c src/cfg_simple.c -o $O/cfg_simple.o $O/hashtable.o

$O/hashtable.o: src/vendor/hashtable.c
	gcc -fPIC -std=gnu11 -g -c src/vendor/hashtable.c -o $O/hashtable.o

$O/run_cmd.o: src/run_cmd.c
	gcc -fPIC -std=gnu11 -g -c src/run_cmd.c -o $O/run_cmd.o

$O/prompt.o: src/prompt.c
	gcc -fPIC -std=gnu11 -g -c src/prompt.c -o $O/prompt.o

$O/db.o: src/db.c
	gcc -fPIC -std=gnu11 -g -c src/db.c -o $O/db.o $O/prompt.o

$O/script.o: src/script.h src/script.c
	gcc -fPIC -fPIC -std=gnu11 -g -c src/script.c -o $O/script.o

$O/ordered_tree.o: src/ordered_tree.h src/ordered_tree.c
	gcc -fPIC -std=gnu11 -g -c src/ordered_tree.c -o $O/ordered_tree.o

