#include <iostream>
#include <random>
#include <cstdlib>

int main(int argc, char const *argv[])
{
  unsigned n = std::atoi(argv[1]); //sample size
  unsigned p = std::atoi(argv[2]); //number of classes
  unsigned chunk_size = n/p;
  unsigned acum = 0;
  for (unsigned i = 0; i < p; i++)
  {
    unsigned a = i * chunk_size;
    unsigned b = (i+1) * chunk_size - 1;
    std::mt19937 rng(0);
    std::uniform_int_distribution<unsigned> uint_dist(a, b);
    for(unsigned j = 0; j < chunk_size; j++)
      acum = uint_dist(rng) + acum;
  }
  std::cout << "Sum: " << acum << std::endl;
  return 0;
}
