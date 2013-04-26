V = 1 #lib version
B = bin
T = bin-test
O = obj
L = lib
M = -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -lrt -ldl


LIB_COMPILE = gcc -g -std=gnu11 -fPIC -c -Wall
X = gcc -g -std=gnu11 -fPIC -c -Wall
TEST_COMPILE = gcc -g -std=gnu11 -c -fPIC

all: init lib_objects test_objects libso
cleanall: clean all
test: clean all
	perl ./scripts/test.pl $T

lib_objects: $O/script.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/prompt.o \
	$O/db.o \
	$O/cfg.o \
	$O/obj.o \
	$O/cfg_simple.o \
	$O/str.o \
	$O/user.o \
	$O/account.o \
	$O/run_cmd.o

test_objects: $T/hashtable_test \
	$T/script_test \
	$T/ordered_tree_str_test \
	$T/ordered_tree_generic_test \
	$T/str_test \
	$T/cfg_test \
	$T/obj_test \
	$T/user_test \
	$T/account_test \
	$T/db_test

init:
	mkdir -p $O $B $L $T

clean:
	rm -rf $O $B $L $T

doxy:
	doxygen Doxyfile
	rm -rf doc/latex

libso:
	gcc -shared -fPIC -Wl,-soname,libkitchensink.so.$V -o $L/libkitchensink.so.$V \
	$O/script.o \
	$O/obj.o \
	$O/cfg.o \
	$O/cfg_simple.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/db.o \
	$O/prompt.o \
	$O/str.o \
	$O/user.o \
	$O/account.o \
	$O/run_cmd.o


## TESTS

$T/user_test: $O/user.o  $O/user_test.o
	gcc -fPIC -std=gnu11 -g -o $T/user_test $O/user_test.o $O/user.o $O/obj.o $O/hashtable.o -Wall

$O/user_test.o: test/model/user_test.c 
	gcc -fPIC -std=gnu11 -g -c test/model/user_test.c -o $O/user_test.o

$T/account_test: $O/account.o  $O/account_test.o
	gcc -fPIC -std=gnu11 -g -o $T/account_test $O/account_test.o $O/account.o $O/obj.o $O/hashtable.o -Wall

$O/account_test.o: test/model/account_test.c 
	gcc -fPIC -std=gnu11 -g -c test/model/account_test.c -o $O/account_test.o

$T/obj_test: $O/obj.o  $O/obj_test.o
	gcc -fPIC -std=gnu11 -g -o $T/obj_test $O/obj_test.o $O/obj.o $O/hashtable.o -Wall

$O/obj_test.o: test/obj_test.c 
	gcc -fPIC -std=gnu11 -g -c test/obj_test.c -o $O/obj_test.o

$T/cfg_test: $O/cfg.o  $O/cfg_test.o
	gcc -fPIC -std=gnu11 -g -o $T/cfg_test $O/cfg_test.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o -Wall

$O/cfg_test.o: test/cfg_test.c 
	gcc -fPIC -std=gnu11 -g -c test/cfg_test.c -o $O/cfg_test.o

$T/str_test: $O/str.o  $O/str_test.o
	gcc -fPIC -std=gnu11 -g -o $T/str_test $O/str_test.o $O/str.o -Wall

$O/str_test.o: test/str_test.c 
	gcc -fPIC -std=gnu11 -g -c test/str_test.c -o $O/str_test.o

$T/script_test: $O/script.o  $O/script_test.o
	gcc -fPIC -std=gnu11 -g -o $T/script_test $O/script_test.o $O/script.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o -Wall

$O/script_test.o: test/script_test.c 
	gcc -fPIC -std=gnu11 -g -c test/script_test.c -o $O/script_test.o

$T/db_test: $O/db.o  $O/db_test.o
	gcc -fPIC -std=gnu11 -g -o $T/db_test $O/db_test.o $O/db.o $O/prompt.o -Wall $M


$O/db_test.o: test/db_test.c 
	gcc -fPIC -std=gnu11 -g -c test/db_test.c -o $O/db_test.o

$T/timing_test: $O/timing_test.o $O/script.o
	gcc -fPIC -std=gnu11 -g -o $T/timing_test $O/timing_test.o $O/script.o -Wall -lrt -Isrc/vendor

$O/timing_test.o: test/timing_test.c src/script.h
	gcc -fPIC -std=gnu11 -g -c test/timing_test.c -o $O/timing_test.o

$T/hashtable_test: $O/hashtable_test.o $O/hashtable.o
	gcc -fPIC -std=gnu11 -g -o $T/hashtable_test $O/hashtable_test.o $O/hashtable.o -Isrc/vendor

$O/hashtable_test.o: test/data/hashtable_test.c 
	gcc -fPIC -std=gnu11 -g -c test/data/hashtable_test.c -o $O/hashtable_test.o -Isrc/vendor

$T/ordered_tree_str_test: $O/ordered_tree_str_test.o $O/ordered_tree.o
	gcc -fPIC -std=gnu11 -g -o $T/ordered_tree_str_test $O/ordered_tree_str_test.o $O/ordered_tree.o

$O/ordered_tree_str_test.o: test/data/ordered_tree_str_test.c src/data/ordered_tree.h
	gcc -fPIC -std=gnu11 -g -c test/data/ordered_tree_str_test.c -o $O/ordered_tree_str_test.o

$T/ordered_tree_generic_test: $O/ordered_tree_generic_test.o $O/ordered_tree.o
	gcc -fPIC -std=gnu11 -g -o $T/ordered_tree_generic_test $O/ordered_tree_generic_test.o $O/ordered_tree.o

$O/ordered_tree_generic_test.o: test/data/ordered_tree_generic_test.c src/data/ordered_tree.h
	gcc -fPIC -std=gnu11 -g -c test/data/ordered_tree_generic_test.c -o $O/ordered_tree_generic_test.o





## LIB OBJECTS

$O/str.o: src/str.c
	gcc -fPIC -std=gnu11 -g -c src/str.c -o $O/str.o

$O/user.o: src/model/user.c
	gcc -fPIC -std=gnu11 -g -c src/model/user.c -o $O/user.o

$O/account.o: src/model/account.c
	gcc -fPIC -std=gnu11 -g -c src/model/account.c -o $O/account.o

$O/cfg.o: src/cfg.c
	gcc -fPIC -std=gnu11 -g -c src/cfg.c -o $O/cfg.o

$O/cfg_simple.o: src/cfg_simple.c
	gcc -fPIC -std=gnu11 -g -c src/cfg_simple.c -o $O/cfg_simple.o

$O/hashtable.o: src/vendor/hashtable.c
	gcc -fPIC -std=gnu11 -g -c src/vendor/hashtable.c -o $O/hashtable.o

$O/obj.o: src/obj.c
	gcc -fPIC -std=gnu11 -g -c src/obj.c -o $O/obj.o

$O/run_cmd.o: src/run_cmd.c
	gcc -fPIC -std=gnu11 -g -c src/run_cmd.c -o $O/run_cmd.o

$O/prompt.o: src/prompt.c
	gcc -fPIC -std=gnu11 -g -c src/prompt.c -o $O/prompt.o

$O/db.o: src/db.c
	gcc -fPIC -std=gnu11 -g -c src/db.c -o $O/db.o $M

$O/script.o: src/script.h src/script.c
	gcc -fPIC -fPIC -std=gnu11 -g -c src/script.c -o $O/script.o

$O/ordered_tree.o: src/data/ordered_tree.h src/data/ordered_tree.c
	gcc -fPIC -std=gnu11 -g -c src/data/ordered_tree.c -o $O/ordered_tree.o

$O/timing.o: src/timing.c
	gcc -fPIC -std=gnu11 -g -c src/timing.c -o $O/timing.o

