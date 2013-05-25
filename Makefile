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
test: all
	perl ./scripts/ctest.pl test/ctest.json $T

lib_objects: $O/script.o \
	$O/arraylist_objn.o \
	$O/arraylist_double.o \
	$O/arraylist_int.o \
	$O/arraylist_int_ptr.o \
	$O/arraylist_str.o \
	$O/arraylist_string.o \
	$O/timing.o \
	$O/hashtable.o \
	$O/ordered_tree.o \
	$O/prompt.o \
	$O/db.o \
	$O/obj.o \
	$O/cfg.o \
	$O/cfg_simple.o \
	$O/objn.o \
	$O/objn_hashtable.o \
	$O/str.o \
	$O/user.o \
	$O/account.o \
	$O/org.o \
	$O/perm.o \
	$O/group.o \
	$O/run_cmd.o

test_objects: $T/hashtable \
	$T/omp_mapreduce_friendlynumbers \
	$T/intel_tbb \
	$T/intel_tbb_parallel_for \
	$T/intel_tbb_parallel_for_w_lambda \
	$T/openmp \
	$T/arraylist_objn \
	$T/arraylist_double \
	$T/arraylist_int \
	$T/arraylist_int_ptr \
	$T/arraylist_str \
	$T/arraylist_string \
	$T/timing \
	$T/script \
	$T/ordered_tree_str \
	$T/ordered_tree_generic \
	$T/str \
	$T/cfg \
	$T/obj \
	$T/objn \
	$T/user \
	$T/account \
	$T/org \
	$T/perm \
	$T/group \
	$T/db \
	$T/job_producer_consumer_hw

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
	$O/arraylist_objn.o \
	$O/arraylist_double.o \
	$O/arraylist_int.o \
	$O/arraylist_int_ptr.o \
	$O/arraylist_str.o \
	$O/arraylist_string.o \
	$O/obj.o \
	$O/cfg.o \
	$O/cfg_simple.o \
	$O/objn.o \
	$O/objn_hashtable.o \
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

$T/omp_mapreduce_friendlynumbers: $(TO)/omp_mapreduce_friendlynumbers.o 
	g++ -fPIC -g -o $T/omp_mapreduce_friendlynumbers $(TO)/omp_mapreduce_friendlynumbers.o -fopenmp -Wall

$(TO)/omp_mapreduce_friendlynumbers.o: test/omp_mapreduce_friendlynumbers.cpp
	g++ -fPIC -g -c test/omp_mapreduce_friendlynumbers.cpp -o $(TO)/omp_mapreduce_friendlynumbers.o 

$T/intel_tbb_parallel_for_w_lambda: $(TO)/intel_tbb_parallel_for_w_lambda.o 
	g++ -fPIC -std=c++11 -g -o $T/intel_tbb_parallel_for_w_lambda $(TO)/intel_tbb_parallel_for_w_lambda.o -ltbb -Wall

$(TO)/intel_tbb_parallel_for_w_lambda.o: test/intel_tbb_parallel_for_w_lambda.cpp
	g++ -fPIC -std=c++11 -g -c test/intel_tbb_parallel_for_w_lambda.cpp -o $(TO)/intel_tbb_parallel_for_w_lambda.o 

$T/intel_tbb_parallel_for: $(TO)/intel_tbb_parallel_for.o 
	g++ -fPIC -std=c++11 -g -o $T/intel_tbb_parallel_for $(TO)/intel_tbb_parallel_for.o -ltbb -Wall

$(TO)/intel_tbb_parallel_for.o: test/intel_tbb_parallel_for.cpp
	g++ -fPIC -std=c++11 -g -c test/intel_tbb_parallel_for.cpp -o $(TO)/intel_tbb_parallel_for.o 

$T/intel_tbb: $(TO)/intel_tbb.o 
	g++ -fPIC -std=c++11 -g -o $T/intel_tbb $(TO)/intel_tbb.o -ltbb -Wall

$(TO)/intel_tbb.o: test/intel_tbb.cpp
	g++ -fPIC -std=c++11 -g -c test/intel_tbb.cpp -o $(TO)/intel_tbb.o 

$T/openmp: $(TO)/openmp.o 
	gcc -fPIC -std=gnu11 -g -o $T/openmp $(TO)/openmp.o -fopenmp -Wall

$(TO)/openmp.o: test/openmp.c 
	gcc -fPIC -std=gnu11 -g -c test/openmp.c -o $(TO)/openmp.o

$T/arraylist_objn: $O/arraylist_objn.o  $(TO)/arraylist_objn.o
	gcc -fPIC -std=gnu11 -g -o $T/arraylist_objn $(TO)/arraylist_objn.o $O/arraylist_objn.o $O/objn.o $O/objn_hashtable.o $O/str.o $O/hashtable.o -Wall

$(TO)/arraylist_objn.o: test/arraylist_objn.c 
	gcc -fPIC -std=gnu11 -g -c test/arraylist_objn.c -o $(TO)/arraylist_objn.o

$T/arraylist_double: $O/arraylist_double.o  $(TO)/arraylist_double.o
	gcc -fPIC -std=gnu11 -g -o $T/arraylist_double $(TO)/arraylist_double.o $O/arraylist_double.o -Wall

$(TO)/arraylist_double.o: test/arraylist_double.c 
	gcc -fPIC -std=gnu11 -g -c test/arraylist_double.c -o $(TO)/arraylist_double.o

$T/arraylist_int: $O/arraylist_int.o  $(TO)/arraylist_int.o
	gcc -fPIC -std=gnu11 -g -o $T/arraylist_int $(TO)/arraylist_int.o $O/arraylist_int.o -Wall

$(TO)/arraylist_int.o: test/arraylist_int.c 
	gcc -fPIC -std=gnu11 -g -c test/arraylist_int.c -o $(TO)/arraylist_int.o

$T/arraylist_int_ptr: $O/arraylist_int_ptr.o  $(TO)/arraylist_int_ptr.o
	gcc -fPIC -std=gnu11 -g -o $T/arraylist_int_ptr $(TO)/arraylist_int_ptr.o $O/arraylist_int_ptr.o -Wall

$(TO)/arraylist_int_ptr.o: test/arraylist_int_ptr.c 
	gcc -fPIC -std=gnu11 -g -c test/arraylist_int_ptr.c -o $(TO)/arraylist_int_ptr.o

$T/arraylist_string: $O/arraylist_string.o  $(TO)/arraylist_string.o
	gcc -fPIC -std=gnu11 -g -o $T/arraylist_string $(TO)/arraylist_string.o $O/arraylist_string.o -Wall

$(TO)/arraylist_string.o: test/arraylist_string.c 
	gcc -fPIC -std=gnu11 -g -c test/arraylist_string.c -o $(TO)/arraylist_string.o

$T/arraylist_str: $O/arraylist_str.o  $(TO)/arraylist_str.o
	gcc -fPIC -std=gnu11 -g -o $T/arraylist_str $(TO)/arraylist_str.o $O/arraylist_str.o -Wall

$(TO)/arraylist_str.o: test/arraylist_str.c 
	gcc -fPIC -std=gnu11 -g -c test/arraylist_str.c -o $(TO)/arraylist_str.o

$T/job_producer_consumer_hw: $(TO)/job_producer_consumer_hw.o
	gcc -fPIC -std=gnu11 -g -o $T/job_producer_consumer_hw $(TO)/job_producer_consumer_hw.o -Wall -lpthread

$(TO)/job_producer_consumer_hw.o: test/job_producer_consumer_hw.c 
	gcc -fPIC -std=gnu11 -g -c test/job_producer_consumer_hw.c -o $(TO)/job_producer_consumer_hw.o

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

$T/objn: $O/objn.o  $(TO)/objn.o
	gcc -fPIC -std=gnu11 -g -o $T/objn $(TO)/objn.o $O/objn.o $O/objn_hashtable.o $O/hashtable.o $O/str.o -Wall

$(TO)/objn.o: test/objn.c 
	gcc -fPIC -std=gnu11 -g -c test/objn.c -o $(TO)/objn.o

$T/str: $O/str.o  $(TO)/str.o
	gcc -fPIC -std=gnu11 -g -o $T/str $(TO)/str.o $O/str.o -Wall

$(TO)/str.o: test/str.c 
	gcc -fPIC -std=gnu11 -g -c test/str.c -o $(TO)/str.o

$T/script: $O/script.o  $(TO)/script.o
	gcc -fPIC -std=gnu11 -g -o $T/script $(TO)/script.o $O/script.o $O/cfg.o $O/cfg_simple.o $O/hashtable.o $O/str.o $O/obj.o -Wall

$(TO)/script.o: test/script.c 
	gcc -fPIC -std=gnu11 -g -c test/script.c -o $(TO)/script.o

$T/db: $O/db.o  $(TO)/db.o
	gcc -fPIC -std=gnu11 -g -o $T/db $(TO)/db.o $O/db.o $O/prompt.o -Wall $M

$(TO)/db.o: test/db.c 
	gcc -fPIC -std=gnu11 -g -c test/db.c -o $(TO)/db.o

$T/timing: $(TO)/timing.o 
	gcc -fPIC -std=gnu11 -g -o $T/timing $(TO)/timing.o $O/timing.o -Wall -lrt -Isrc/vendor

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

$O/arraylist_objn.o: src/arraylist_objn.c
	gcc -fPIC -std=gnu11 -g -c src/arraylist_objn.c -o $O/arraylist_objn.o

$O/arraylist_double.o: src/arraylist_double.c
	gcc -fPIC -std=gnu11 -g -c src/arraylist_double.c -o $O/arraylist_double.o

$O/arraylist_int.o: src/arraylist_int.c
	gcc -fPIC -std=gnu11 -g -c src/arraylist_int.c -o $O/arraylist_int.o

$O/arraylist_int_ptr.o: src/arraylist_int_ptr.c
	gcc -fPIC -std=gnu11 -g -c src/arraylist_int_ptr.c -o $O/arraylist_int_ptr.o

$O/arraylist_string.o: src/arraylist_string.c
	gcc -fPIC -std=gnu11 -g -c src/arraylist_string.c -o $O/arraylist_string.o

$O/arraylist_str.o: src/arraylist_str.c
	gcc -fPIC -std=gnu11 -g -c src/arraylist_str.c -o $O/arraylist_str.o

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

$O/objn.o: src/objn.c
	gcc -fPIC -std=gnu11 -g -c src/objn.c -o $O/objn.o

$O/objn_hashtable.o: src/objn_hashtable.c
	gcc -fPIC -std=gnu11 -g -c src/objn_hashtable.c -o $O/objn_hashtable.o

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

