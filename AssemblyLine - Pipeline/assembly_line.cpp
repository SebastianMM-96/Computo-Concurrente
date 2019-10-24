#include <iostream>
#include "pipeline.h"

using namespace std;
using namespace std::chrono;

/*Main function*/
int main(int argc, char const *argv[]){
	unsigned NumCar = atoi(argv[1]);
	//std::vector<automobile> autos(NumCar);
	pipeline pAssemblyLine(NumCar);

	/*Medimos el tiempo*/
	std::cout << "-----------------------------------------------------------" << '\n';
	auto start = system_clock::now();
	pAssemblyLine.automobileFactry();
	auto seq_elapsed = system_clock::now() - start;
	std::cout << "Assembly line build in time" << '\n';
	std::cout << "Concurrent time: "
    << duration_cast<std::chrono::milliseconds>(seq_elapsed).count()
    << " millisecond " << std::endl;
	std::cout << "-----------------------------------------------------------" << '\n';
	std::cout << '\n';

	std::list<automobile> production = pAssemblyLine.getProd();

	return 0;
}
