#include <iostream>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>


long len = 5000;
float *set1 = new float[len];
float *set2 = new float[len];
float *set3 = new float[len];

class GrainTest 
{
	public:
	void operator()( const tbb::blocked_range<size_t>& r ) const 
	{ 
		std::cout << r.begin() << std::endl;
	}
};

int main(int argc, char ** argv) 
{
    parallel_for( tbb::blocked_range<size_t>(0,len, 100), GrainTest() );
    return 0;
}
