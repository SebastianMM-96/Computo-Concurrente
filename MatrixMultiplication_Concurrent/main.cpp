#include <iostream>
#include <cstdlib>
#include <chrono>
#include "matrix.h"

//g++ main.cc -o Matrix -std=c++17 -Wall -g -I.

using namespace std::chrono;

int main(int argc, char const *argv[]){
  size_t m = std::atoi(argv[1]), n = std::atoi(argv[2]);
  size_t p = std::atoi(argv[3]);
  matrix<int> M(m, n, 1), N(n, p, 2), C(m, p, 0);

  /*------------------------- PROBLEM 1 - SEQUENTIAL -----------------------*/
  

  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << "1. Matrix Multiplication - Sequential" << '\n';
  auto start = system_clock::now();
  C = M.sequential_multiplication(N);
  auto seq_elapsed = system_clock::now() - start;
  std::cout << "Sequential time : " 
    << duration_cast<microseconds>(seq_elapsed).count()
    << " us " << std::endl;
  std::cout << "-----------------------------------------------------------" << '\n';
  
  std::cout << '\n';
  

  /*------------------------- PROBLEM 2 - CONCURRENT -----------------------*/
  
  
  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << "2. Concurrent Matrix Multiplication" << '\n';
  start = system_clock::now();
  C = M.concurrent_matrix_multiplication(N);
  seq_elapsed = system_clock::now() - start;
  std::cout << "Concurrent time: " 
    << duration_cast<microseconds>(seq_elapsed).count()
    << " us " << std::endl;
  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << '\n';
  

  /*-------------------- PROBLEM 3 - CACHE SENSITIVE ---------------------*/  
  

  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << "3. Cache Multiplication Sensitive" << '\n';
  start = system_clock::now();
  C = M.cache_multiplication(N);
  seq_elapsed = system_clock::now() - start;
  std::cout << "Cache Sensitive time: " 
    << duration_cast<microseconds>(seq_elapsed).count()
    << " us " << std::endl;
  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << '\n';
  

  /*------------- PROBLEM 4 - CACHE SENSITIVE CONCURRENT -----------------*/  
  
  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << "4. Cache Concurrent Multiplication Sensitive" << '\n';
  auto start = system_clock::now();
  C = M.cache_mult_concurrent(N);
  auto seq_elapsed = system_clock::now() - start;
  std::cout << "Cache Concurrent Sensitive time: " 
    << duration_cast<microseconds>(seq_elapsed).count()
    << " us " << std::endl;
  std::cout << "-----------------------------------------------------------" << '\n';
  std::cout << '\n';
  
  return 0;
}