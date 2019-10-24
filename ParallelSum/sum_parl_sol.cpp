#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <ctime>
#include <random>

void partial_sum(unsigned& result, unsigned a, unsigned b){
   std::mt19937 rng(0); //base cientifica para mantener los experimentos. 
   std::uniform_int_distribution<unsigned> uint_dist(a, b);
   for(unsigned i = a; i <= b; i++){
      // generates number in the range a...b
      result = uint_dist(rng) + result;
   }
}

int main(int argc, char const *argv[]){

	unsigned p = std::thread::hardware_concurrency();
   unsigned n = atoi(argv[1]); //Obtenerlo desde la terminal
	unsigned chunk_size = n/p;
	std::vector<unsigned> acum(p);
	unsigned t0, t1;

	std::vector<std::thread> task(p);
	
	//Muestra el tamaño correspondiente para cada p
	for(size_t i = 0; i < p; i++){
	   acum[i] = 0;
	   //std::cout << "acum: " << acum[i] << std::endl;
	}
	
	for(size_t i = 0; i < p; i++){
		unsigned a = i * chunk_size;
      unsigned b = (i + 1) * chunk_size - 1;
		task[i] = std::thread(partial_sum, std::ref(acum[i]), a, b);
	}
	
	for(auto& t : task){
		t.join();
	}
	
	//Suma para resultado final
   int res = 0;
   for(size_t i = 0; i < p; i++){
      //std::cout << "acum["<< i << "]: " << acum[i] << std::endl;
      res = res + acum[i];
      std::cout << "Res: " << res << std::endl;
   }
   
	std::cout << "Result: " << res << std::endl;
   
	return 0;
}