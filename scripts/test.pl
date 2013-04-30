#!/perl

use strict;
use warnings;

use Test::More;
use File::Which;

my $test_dir = shift;

my $valgrind = File::Which::which('valgrind');
my $cfg = 
{
	hashtable => {
		name=>'Hashtable test',
		expected => q#
Key NOT found 300
found 299 keys
j -> 300
*value is (nil)
#,
	},
	ordered_tree_generic => {
		name => 'Ordered Generic Tree test',
		expected => q#
Title blah has 12 pages
aSasfsdfdsTitle blah has 14 pages
ignore has 10 pages
#,
	},
	ordered_tree_str => {
		name => 'Ordered String Tree test',
		expected => q#
beginning
middle
z end
#,
	},
	str => {
		name => 'Str test',
		expected => q#
Match one retval, This found in This is a line with text at position 0
Match two retval, line found in This is a line with text at position 10
#,
	},
	script => {
		name => 'Script test',
		expected => q#
script_get_progname end script
script
rcfile None
Looking up "sc_dir", w/ default value "shouldn't be used": returned: shouldn't be used
Looking up "asdfasdf", w/ default value "should be used": returned: should be used
#,
	},
	cfg => 
	{
		name => 'Cfg test',
		regex_expected => q#/\s*created cfg 0x[0-9A-Za-z]+
created cfg data 0x[0-9A-Za-z]+
key1 = val1
key1 = val1
cfg dump
----------
key1 = val1
key1 = val1 changed
----------
key2 = val2
cfg dump
----------
key1 = val1
key1 = val1 changed
key2 = val2
----------\s*/#,
	},
	obj => 
	{
		name => 'Obj test',
		regex_expected => q'/\s*created obj 0x[0-9A-Za-z]+
created obj data 0x[0-9A-Za-z]+
set [0-9A-Za-z]+ to [0-9A-Za-z]+
[0-9A-Za-z]+ with getter = [0-9A-Za-z]+
[0-9A-Za-z]+ = [0-9A-Za-z]+
[0-9A-Za-z]+ = [0-9A-Za-z]+
obj dump
----------
key1 = val1
key1 = val1 changed
----------
key2 = val2
obj dump
----------
key1 = val1
key1 = val1 changed
key2 = val2
----------
obj_set_obj looked up o2 \(0x[0-9A-Za-z]+\), got o2lookedup 0x[0-9A-Za-z]+
first dump o2
o2key = o2val
then dump o2lookedup
key1 = val1
key1 = val1 changed
key2 = val2
obj:o2 = \(obj_t\)
o2key = o2val\s*$/',
	},
	objn => 
	{
		name => 'Objn test',
		regex_expected => q'/\s*created obj 0x[0-9A-Za-z]+
created obj data 0x[0-9A-Za-z]+
set [0-9A-Za-z]+ to [0-9A-Za-z]+
[0-9A-Za-z]+ with getter = [0-9A-Za-z]+
[0-9A-Za-z]+ = [0-9A-Za-z]+
[0-9A-Za-z]+ = [0-9A-Za-z]+
obj dump
----------
key1 = val1
key1 = val1 changed
----------
key2 = val2
obj dump
----------
key1 = val1
key1 = val1 changed
key2 = val2
----------
obj_set_obj looked up o2 \(0x[0-9A-Za-z]+\), got o2lookedup 0x[0-9A-Za-z]+
first dump o2
o2key = o2val
then dump o2lookedup
key1 = val1
key1 = val1 changed
key2 = val2
obj:o2 = \(obj_t\)
o2key = o2val\s*$/',
	},

	user => 
	{
		name => 'Model/user test',
		regex_expected => q'/\s*created user 0x[0-9A-Za-z]+
set user \w+\s*/',
	},

	account => 
	{
		name => 'model/account test',
		regex_expected => q'/\s*created account 0x[0-9A-Za-z]+
set account id \d+
set account name \w+\s*/',
	},

	org => 
	{
		name => 'Model/org test',
		regex_expected => q'/\s*created org 0x[0-9A-Za-z]+
set org id 1
set org name [A-Za-z\s,]+\s*/',
	 },
	perm => 
	{
		name => 'Model/perm test',
		regex_expected => q'/\s*created perm 0x[0-9A-Za-z]+
set perm ken\s*$/',
	 },


	## db_test is commented out by default
	## prereqs - MySQL client libs, libmysqlclient and mysql/mysql.h
	## If you want to run this test, first run make, then 
	## run the ./bin-test/db binary as
	##		$ ./bin-test/db localhost # assuming you have mysqld running on localhost
	##		Note, you'll see two prompts, first for your mysql username and second, the user's password
	##		So, this script doesn't print out those "User: " and "Password: " but it does block on them,
	##		for now until I fix that.
	commentedout_db => {
		name=>'MySQL Database test',
		args => 'localhost',
		expected => q#User:
Password:
opened mysql connection
step1: create simple table
step2: insert simple table
step3: select from insert simple table, 1 stringy test string
step4: delete simple data
step5: drop simple table
close mysql connection#,
	},

	group => 
	{
		name => 'Model/group test',
		regex_expected => q'/\s*created group 0x[0-9A-Za-z]+
set group ken
created perm read perm
after obj_set_obj in group_add_perm
added perm read perm to group ken
group ken has perm read perm\s*$/',
	},

	timing => 
	{
		name => 'Timing test',
		regex_expected => q'/\s*mystrcat \d+ iters = \d+ seconds
timeval \d+, \d+, \d+ and \d+ = \d+\s*$/'
	},

};

walk( $test_dir, \&run_tests );
done_testing();
exit;


sub run_tests
{
	my($path) = shift;
	my($name) = $path =~ m/\/+(.*?)$/;
	unless(exists $cfg->{$name})
	{
		print "Found test, $path, but $name doesn't exist in test config...Skipping\n";
		return;
	}
	my $test_cfg = $cfg->{$name};
	my $test_args = exists $test_cfg->{args} ? $test_cfg->{args} : undef;
	unless(exists $test_cfg->{expected} or exists $test_cfg->{regex_expected})
	{
		print "Found test with $name but no 'expected' or 'regex_expected' is set...Skipping\n";
		return;
	}
	my $cmdline = $path;
	$cmdline .= " $test_args" if defined $test_args;
	&basic_test($cmdline,$test_cfg);
}

sub basic_test
{
	my($cmdline, $test_cfg) = @_;
	return unless exists $test_cfg->{expected} or exists $test_cfg->{regex_expected};
	my $test_name = $test_cfg->{name};
	my $got = &trim(join '',`$cmdline`);
	if(exists $test_cfg->{regex_expected})
	{
		like($got, $test_cfg->{regex_expected} , $test_name);
	}
	else
	{
		is($got, &trim($test_cfg->{expected}) , $test_name);
	}
}

sub valgrind_test
{
	my($cmdline, $test_cfg) = @_;
	return unless defined $valgrind;
	return unless exists $test_cfg->{expected} or exists $test_cfg->{regex_expected};
	my $test_name = $test_cfg->{name} . ' Valgrind';
	my $got = &trim(join '',`$valgrind -q --leak-check=full $cmdline`);
	if(exists $test_cfg->{regex_expected})
	{
		like($got, $test_cfg->{regex_expected} , $test_name);
	}
	else
	{
		is($got, &trim($test_cfg->{expected}) , $test_name);
	}
}


sub trim
{
	my $s = shift;
	$s =~ s/^\s+//;
	$s =~ s/\s+$//mg;
	$s
}

sub walk
{
	my($dir,$callback) = @_;
	$dir =~ s/\/$//; ## Remove trailing slash because we'll be adding one in `map` below
	opendir D,$dir || die "Can't opendir $dir, $!\n";
	my @entries = map{"$dir/$_"} grep !/^\./, readdir D;
	my @bins;
	my @dirs;
	for(@entries)
	{
		if( -d $_ )
		{
			push @dirs,$_;
		}
		elsif( -B $_ and -X $_ and (not -l $_) )
		{
			push @bins,$_;
		}
	}
	closedir D;
	$callback->($_) for sort @bins;
	&walk($callback,$_) for sort @dirs;
}
