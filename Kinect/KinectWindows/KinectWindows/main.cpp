#include "SimonSays.h"


#define log(x) std::cout << x << std::endl;


int main(int argc, char** argv)
{
	SimonSays simon;
	simon.init();
	simon.run();
	return 0;
}