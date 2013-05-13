#include <stdio.h>

#include <tbb/parallel_reduce.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/blocked_range.h>
#include <tbb/partitioner.h>

using namespace std;
using namespace tbb;

static long num_rects = 1000000;

class MyPI
{
private:
	double * const my_rects;

public:
	double partialHeight;

	MyPI(double * const width) : my_rects(width),partialHeight(0){}
	MyPI( MyPI& x, split):  my_rects(x.my_rects),partialHeight(0){}
	void operator()(const blocked_range<size_t>& r)
	{
		double rectWidth = * my_rects;
		double x;
		for(size_t i = r.begin(); i != r.end(); ++i)
		{
			x = (i + 0.5) * rectWidth;
			partialHeight += 4.0 / (1.0 + x * x );
		}
	}

	void join(const MyPI& y)
	{
		partialHeight += y.partialHeight;
	}
};

int main(int argc, char ** argv)
{
	double area;
	double width = 1.0 / (double)num_rects;
	MyPI my_block( (double * const ) &width);
	task_scheduler_init init;
	
	parallel_reduce(blocked_range<size_t>(0,num_rects), my_block, auto_partitioner() );
	area = my_block.partialHeight * width;	

	printf("The value of PI is %f\n",area);
	
	return 0;
}

