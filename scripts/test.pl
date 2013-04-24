#!/perl

use strict;
use warnings;

use Test::More;

my $test_dir = shift;

my $cfg = 
{
	hashtable_test => {
		name=>'Hashtable test',
		expected => q#
Key NOT found 300
found 299 keys
j -> 300
*value is (nil)
#,
	},
	ordered_tree_generic_test => {
		name => 'Ordered Generic Tree test',
		expected => q#
Title blah has 12 pages
aSasfsdfdsTitle blah has 14 pages
ignore has 10 pages
#,
	},
	ordered_tree_str_test => {
		name => 'Ordered String Tree test',
		expected => q#
beginning
middle
z end
#,
	},
	str_test => {
		name => 'Str test',
		expected => q##,
	},
	script_test => {
		name => 'Script test',
		expected => q#
script_get_progname end script_test
script_test
rcfile None
Looking up "sc_dir", w/ default value "shouldn't be used": returned: shouldn't be used
Looking up "asdfasdf", w/ default value "should be used": returned: should be used
#,
	},
	cfg_test => 
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
	obj_test => 
	{
		name => 'Obj test',
		regex_expected => q'/\s*init obj 0x[0-9A-Za-z]+
created obj 0x[0-9A-Za-z]+
created obj data 0x[0-9A-Za-z]+
obj_set 0x[0-9A-Za-z]+, key key1, val val1
set key1 to val1
key1 with getter = val1
key1 = val1
obj_set 0x[0-9A-Za-z]+, key key1, val val1 changed
key1 = val1
obj dump
----------
obj data dump
key1 = val1
key1 = val1 changed
----------
obj_set 0x[0-9A-Za-z]+, key key2, val val2
key2 = val2
obj dump
----------
obj data dump
key1 = val1
key1 = val1 changed
key2 = val2
----------\s*/',
	},

	user_test => 
	{
		name => 'Model/user test',
		regex_expected => q'/\s*init obj 0x[0-9A-Za-z]+
created user 0x[0-9A-Za-z]+
obj_set 0x[0-9A-Za-z]+, key name, val ken
set user ken\s*/',
	},

};

walk( $test_dir, \&run_tests );
done_testing();
exit;


sub run_tests
{
	my($path) = shift;
	my($name) = $path =~ m/\/+(.*?)$/;
	print "name $name\n";
	unless(exists $cfg->{$name})
	{
		print "Found test, $path, but $name doesn't exist in test config...Skipping\n";
		return;
	}
	my $t_cfg = $cfg->{$name};
	unless(exists $t_cfg->{expected} or exists $t_cfg->{regex_expected})
	{
		print "Found test with $name but no 'expected' or 'regex_expected' is set...Skipping\n";
		return;
	}
	my $got = &trim(join '',`$path`);
	if(exists $t_cfg->{regex_expected})
	{
		like($got, $t_cfg->{regex_expected} , $name);
	}
	else
	{
		is($got, &trim($t_cfg->{expected}) , $name);
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
