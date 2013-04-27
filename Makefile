V = 1 # lib version
B = bin
T = bin-test
TO = obj-test
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
	$O/org.o \
	$O/perm.o \
	$O/group.o \
	$O/run_cmd.o

test_objects: $T/hashtable \
	$T/script \
	$T/ordered_tree_str \
	$T/ordered_tree_generic \
	$T/str \
	$T/cfg \
	$T/obj \
	$T/user \
	$T/account \
	$T/org \
	$T/perm \
	$T/group \
	$T/db

init:
	mkdir -p $O $B $L $T $(TO)

clean:
	rm -rf $O $B $L $T $(TO)

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
	$O/org.o \
	$O/perm.o \
	$O/group.o \
	$O/run_cmd.o


## TESTS

$T/user: $O/user.o  $(TO)/user.o
	gcc -fPIC -std=gnu11 -g -o $T/user $(TO)/user.o $O/user.o $O/obj.o $O/hashtable.o $O/str.o -Wall

$(TO)/user.o: test/model/user.c 
	gcc -fPIC -std=gnu11 -g -c test/model/user.c -o $(TO)/user.o

$T/account: $O/account.o  $(TO)/account.o
	gcc -fPIC -std=gnu11 -g -o $T/account $(TO)/account.o $O/account.o $O/obj.o $O/hashtable.o $O/str.o -Wall

$(TO)/account.o: test/model/account.c 
	gcc -fPIC -std=gnu11 -g -c test/model/account.c -o $(TO)/account.o

$T/org: $O/org.o  $(TO)/org.o
	gcc -fPIC -std=gnu11 -g -o $T/org $(TO)/org.o $O/org.o $O/obj.o $O/hashtable.o $O/str.o -Wall

$(TO)/org.o: test/model/org.c 
	gcc -fPIC -std=gnu11 -g -c test/model/org.c -o $(TO)/org.o

$T/perm: $O/perm.o  $(TO)/perm.o
	gcc -fPIC -std=gnu11 -g -o $T/perm $(TO)/perm.o $O/perm.o $O/obj.o $O/hashtable.o $O/str.o -Wall

$(TO)/perm.o: test/model/perm.c 
	gcc -fPIC -std=gnu11 -g -c test/model/perm.c -o $(TO)/perm.o

$T/group: $O/group.o  $(TO)/group.o
	gcc -fPIC -std=gnu11 -g -o $T/group $(TO)/group.o $O/group.o $O/perm.o $O/obj.o $O/hashtable.o $O/str.o -Wall

$(TO)/group.o: test/model/group.c 
	gcc -fPIC -std=gnu11 -g -c test/model/group.c -o $(TO)/group.o

$T/obj: $O/obj.o  $(TO)/obj.o
	gcc -fPIC -std=gnu11 -g -o $T/obj $(TO)/obj.o $O/obj.o $O/hashtable.o $O/str.o -Wall

$(TO)/obj.o: test/obj.c 
	gcc -fPIC -std=gnu11 -g -c test/obj.c -o $(TO)/obj.o

$T/cfg: $O/cfg.o  $(TO)/cfg.o
	gcc -fPIC -std=gnu11 -g -o $T/cfg $(TO)/cfg.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o $O/str.o -Wall

$(TO)/cfg.o: test/cfg.c 
	gcc -fPIC -std=gnu11 -g -c test/cfg.c -o $(TO)/cfg.o

$T/str: $O/str.o  $(TO)/str.o
	gcc -fPIC -std=gnu11 -g -o $T/str $(TO)/str.o $O/str.o -Wall

$(TO)/str.o: test/str.c 
	gcc -fPIC -std=gnu11 -g -c test/str.c -o $(TO)/str.o

$T/script: $O/script.o  $(TO)/script.o
	gcc -fPIC -std=gnu11 -g -o $T/script $(TO)/script.o $O/script.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o $O/str.o -Wall

$(TO)/script.o: test/script.c 
	gcc -fPIC -std=gnu11 -g -c test/script.c -o $(TO)/script.o

$T/db: $O/db.o  $(TO)/db.o
	gcc -fPIC -std=gnu11 -g -o $T/db $(TO)/db.o $O/db.o $O/prompt.o -Wall $M

$(TO)/db.o: test/db.c 
	gcc -fPIC -std=gnu11 -g -c test/db.c -o $(TO)/db.o

$T/timing: $(TO)/timing.o $O/script.o
	gcc -fPIC -std=gnu11 -g -o $T/timing $(TO)/timing.o $O/timing.o $O/script.o -Wall -lrt -Isrc/vendor

$(TO)/timing.o: test/timing.c src/script.h
	gcc -fPIC -std=gnu11 -g -c test/timing.c -o $(TO)/timing.o

$T/hashtable: $O/hashtable.o $(TO)/hashtable.o
	gcc -fPIC -std=gnu11 -g -o $T/hashtable $(TO)/hashtable.o $O/hashtable.o $O/str.o -Isrc/vendor

$(TO)/hashtable.o: test/data/hashtable.c 
	gcc -fPIC -std=gnu11 -g -c test/data/hashtable.c -o $(TO)/hashtable.o -Isrc/vendor

$T/ordered_tree_str: $(TO)/ordered_tree_str.o $O/ordered_tree.o
	gcc -fPIC -std=gnu11 -g -o $T/ordered_tree_str $(TO)/ordered_tree_str.o $O/ordered_tree.o

$(TO)/ordered_tree_str.o: test/data/ordered_tree_str.c src/data/ordered_tree.h
	gcc -fPIC -std=gnu11 -g -c test/data/ordered_tree_str.c -o $(TO)/ordered_tree_str.o

$T/ordered_tree_generic: $(TO)/ordered_tree_generic.o $O/ordered_tree.o
	gcc -fPIC -std=gnu11 -g -o $T/ordered_tree_generic $(TO)/ordered_tree_generic.o $O/ordered_tree.o

$(TO)/ordered_tree_generic.o: test/data/ordered_tree_generic.c src/data/ordered_tree.h
	gcc -fPIC -std=gnu11 -g -c test/data/ordered_tree_generic.c -o $(TO)/ordered_tree_generic.o





## LIB OBJECTS

$O/str.o: src/str.c
	gcc -fPIC -std=gnu11 -g -c src/str.c -o $O/str.o

$O/user.o: src/model/user.c
	gcc -fPIC -std=gnu11 -g -c src/model/user.c -o $O/user.o

$O/account.o: src/model/account.c
	gcc -fPIC -std=gnu11 -g -c src/model/account.c -o $O/account.o

$O/org.o: src/model/org.c
	gcc -fPIC -std=gnu11 -g -c src/model/org.c -o $O/org.o

$O/perm.o: src/model/perm.c
	gcc -fPIC -std=gnu11 -g -c src/model/perm.c -o $O/perm.o

$O/group.o: src/model/group.c
	gcc -fPIC -std=gnu11 -g -c src/model/group.c -o $O/group.o

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

