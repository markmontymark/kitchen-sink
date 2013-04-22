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
		expected => q##,
	}
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
	my $got = &trim(join '',`$path`);
	my $expected = &trim($cfg->{$name}->{expected});
	
	is($got, $expected, $name);
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
