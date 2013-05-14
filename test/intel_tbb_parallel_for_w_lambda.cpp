#include <iostream>
#include <iterator>
#include <algorithm>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>


int len = 5000;
float *set1 = new float[len];
float *set2 = new float[len];
float *set3 = new float[len];

int main(int argc, char ** argv) 
{
	tbb::parallel_for( 0, len, [=](unsigned i) 
		{
			std::cout << "i: " << i << std::endl;
		}
	); 
	return 0;
}
