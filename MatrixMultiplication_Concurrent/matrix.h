#if !defined(MATRIX_H)
#define MATRIX_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <thread>
#include <vector>
using namespace std;

//Forward declaration
template <typename T> 
class matrix;
template<typename T>
std::ostream& operator<<(std::ostream&, const matrix<T>&);

//Class template definition
template <typename T> 
class matrix {
private:
    size_t row_num, col_num, length;
    T* data;
public:
    /* @brief Default constructor */
    matrix();
    /* @brief Default destructor */
    ~matrix();
    /* @brief initializer constructor receiving the matrix dimension */
    matrix(size_t, size_t, const T& value = T());
    /* @brief Copy constructor */
    matrix(const matrix<T>&);
    /* @brief Move constructor */
    matrix(matrix<T>&&);
    /* @brief Copy assignment operator*/
    matrix<T>& operator = (const matrix<T>&);   
    /* @brief Move assignment operator*/
    matrix<T>& operator = (matrix<T>&&);
    /* @brief Serial matrix multiplication */
    matrix<T> sequential_multiplication(const matrix<T>&);
    /* @brief Concurrent matrix multiplication */
    void concurrent_matMul(matrix<T>& result, const matrix<T>& other, size_t, size_t);
    matrix<T> concurrent_matrix_multiplication(const matrix<T> &B);
    /* @brief Cache matrix, cache sensitive */
    //matrix<T> concurrent_matrix_multiplication(const matrix<T>&);
    matrix<T> cache_multiplication(const matrix<T>&);
    /* @brief Concurrent matrix multiplication, cache sensitive */
    void concurrentCache(matrix<T>& result, const matrix<T>& other, size_t matA, size_t matB);
    matrix<T> cache_mult_concurrent(const matrix<T>& other);
    matrix<T> operator * (const matrix<T>&);
    /* @brief returns the reference of data in position i*/
    T& operator () (size_t);
    /* @brief returns the reference of data in position i*/
    T operator () (size_t) const;
    /* @brief returns a reference to the value of index (i,j). No bound checking is performed */
    T& operator () (size_t, size_t);
    /* @brief returns a reference to the value of index (i,j). No bound checking is performed */
    T operator () (size_t, size_t) const;
    /* @brief returns the matrix dimension*/
    size_t size() {return length;}
    /* @brief returns the number of rows*/
    size_t row_size() {return row_num;}
    /* @brief returns the number of rows*/
    size_t col_size() {return col_num;}
    /** @brief prints an object of class matrix*/
    //information about friend declaration: http://bit.ly/2VFZuIa
    friend std::ostream& operator << <>(std::ostream&, const matrix<T>&);
};

//Member-function definitions

//Information about C++ constructors: http://bit.ly/2Qclolt

template <typename T> 
matrix<T>::matrix()
    : row_num(0), col_num(0), length(0)
{ }

template <typename T> 
matrix<T>::~matrix()
{
    if (data != nullptr) {
            std::cout << " Deleting resource.\n";
            delete[] data;
    }
}

template <typename T> 
matrix<T>::matrix(size_t m, size_t n, const T& value) 
    : row_num(m), col_num(n), length(m*n)
{
    data = new int[length];
    std::fill_n(data, length, value);
}

template <typename T> 
matrix<T>::matrix(const matrix<T>& other) 
    : row_num(other.row_num)
    , col_num(other.col_num)
    , length(other.length)
    , data(new int[length])
{
    std::copy(other.data, other.data+length, data);
}

template <typename T> 
matrix<T>::matrix(matrix<T>&& other) 
    : row_num(other.row_num)
    , col_num(other.col_num)
    , length(other.length)
    , data(nullptr)
{
    data = other.data;
    other.data = nullptr;
    other.row_num = 0;
    other.col_num = 0;
    other.length = 0;
}

template <typename T> 
matrix<T>& matrix<T>::operator = (const matrix<T>& other)
{
    if (this != &other) {
        delete[] data;
        row_num = other.row_num;
        col_num = other.col_num;
        length = other.length;
        data = new int[length];
        std::copy(other.data, other.data + length, data);
    }
    return *this;
}

template <typename T> 
matrix<T>& matrix<T>::operator = (matrix<T>&& other)
{
    if (this != &other) {
        delete[] data;
        row_num = other.row_num;
        col_num = other.col_num;
        length = other.length;
        data = other.data;
        other.data = nullptr;
        other.row_num = 0;
        other.col_num = 0;
        other.length = 0;
    }
    return *this;
}

template <typename T>
T& matrix<T>::operator () (size_t i, size_t j)
{
    return data[col_num*i + j];
}

template <typename T>
T matrix<T>::operator () (size_t i, size_t j) const
{
    return data[col_num*i + j];
}

template <typename T>
T& matrix<T>::operator () (size_t i)
{
    return data[i];
}

template <typename T>
T matrix<T>::operator () (size_t i) const
{
    return data[i];
}

template <typename T>
std::ostream& operator << (std::ostream& os, const matrix<T>& M)
{
    for (size_t i = 0; i < M.row_num; ++i) {
        for (size_t j = 0; j < M.col_num; ++j) 
            os << M(i, j) << ' ';
        os << '\n';
    }
    return os;
}
/*###################### FUNCTION TEMPLATES ############################*/
/*-------------------------------------------------------------------*/
/*Matrix Multiplication - Sequential*/
template <typename T>
matrix<T> matrix<T>::sequential_multiplication(const matrix<T>& other) {
    matrix<T> C(this->row_num, other.col_num, 0);
    for (size_t i = 0; i < this->row_num; i++)
        for (size_t j = 0; j < other.col_num; j++)
            for (size_t k = 0; k < this->col_num; k++)
                C(i, j) += (*this)(i, k) * other(k, j);
    return C;
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*Matrix Multiplication - Concurrent*/

template <typename T>
matrix<T> matrix<T>::concurrent_matrix_multiplication(const matrix<T>& other){
  //Obtenemos los hilos soportados por la computadora
  unsigned n_threads = std::thread::hardware_concurrency();
  std::cout << n_threads << " Subprocesos concurretes soportados.\n"; 
  matrix<T> C(this->row_num, other.col_num, 0);
  // Declaramos un vector que guardara las tareas que deberán ejecutar los hilos
  vector<thread> task(n_threads);
  // Partimos la matriz en pedazos para ejecutarse en cada hilo
  size_t chunck_size = this->row_num / n_threads; 
  for (size_t i = 0; i < n_threads; i++)
  {
    /* code */
    size_t matA = i * chunck_size;
    size_t matB = (i+1) * chunck_size - 1;
    // Las tareas son enviadas a los hilos correspondientes. 
    // thread implementa la funcion para separar en pedazos las tareas y asignarlas a los hilos. 
    task[i] = thread(&matrix<T>::concurrent_matMul, this, ref(C), other, matA, matB); 
  }
  for (auto& t : task)
  {
    /* code */
    // Esperamos a que los hilos terminen la tarea asignada para unirlos. 
    t.join(); 
  }
  return C;
}

// Está funcion se encarga de realizar la multiplicacion de manera concurrente
template <typename T>
void matrix<T>::concurrent_matMul(matrix<T>& result, const matrix<T>& other, size_t matA, size_t matB){
  for(size_t i = matA; i <= matB; i++)
    for(size_t j = 0; j < other.col_num; j++)
      for(size_t k = 0; k < this->col_num; k++)
        result(i, j) += (*this)(i, k) * other(k, j); 
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*Matrix Muliplication - Cache Sensitive*/
template <typename T> 
matrix<T> matrix<T>::cache_multiplication(const matrix<T>& other) {
   matrix<T> C(this->row_num, other.col_num, 0);
   for (size_t i = 0; i < this->row_num; i++)
      for (size_t j = 0; j < other.row_num; j++)
         for (size_t k = 0; k < other.col_num; k++)
            C(i,k) += (*this)(i,j) * other(j,k);
   return C;
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*Sensitive - Concurrent Matrix Multiplication*/
template <typename T> 
matrix<T> matrix<T>::cache_mult_concurrent(const matrix<T>& other) {
   unsigned p = std::thread::hardware_concurrency();
   //std::cout << p << " Subprocesos concurretes soportados.\n"; 
   matrix<T> C(this->row_num, other.col_num, 0);
   vector<thread> task(p);
   // En este loop nos aseguramos de que sea sensible a la cache.
   size_t chunck_size = this->row_num / p; 
   // size.C / p 
  // size_t kIt = k / C.col_num;
  for(size_t i = 0; i < p; i++) {
    size_t matA = i * chunck_size;
    size_t matB = (i+1) * chunck_size - 1; 
    task[i] = thread(&matrix<T>::concurrentCache, this, ref(C), other, matA, matB); 
  }
  for (auto& t : task) {
         // Esperamos a que los hilos terminen la tarea asignada para unirlos. 
    t.join(); 
  }
  return C;
}

//Esta función se encarga de multiplicar respetando la cache
template <typename T>
void matrix<T>::concurrentCache(matrix<T>& result, const matrix<T>& other, size_t matA, size_t matB) {
   for (size_t i = matA; i <= matB; i++)
      for (size_t j = 0; j < this->row_num; j++)
         for (size_t k = 0; k < this->col_num; k++)
            result(i,k) += (*this)(i,j) * other(j,k);
}
/*-------------------------------------------------------------------*/
	

#endif // MATRIX_H
