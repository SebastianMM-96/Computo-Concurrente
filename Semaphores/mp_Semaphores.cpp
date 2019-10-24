#include "semaphores.h"
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <chrono>

using namespace std::chrono;

/*Creamos nuestro mutex*/
std::mutex m_mux;

/*Declaracíon de las funciones*/
void producer(string& msg, unsigned id);
void consumer(string& msg, unsigned id);
void task_proCon(semaphores& sm0, semaphores& sm1, vector<string>& msg, unsigned id, unsigned modVal);

/*Implementacion de la funciones*/
void task_proCon(semaphores& sm0, semaphores& sm1, vector<string>& msg, unsigned id, unsigned modVal){
	producer(msg[id], id);
	sm0.notify();
	sm1.wait();
	consumer(msg[modVal], id);
}

void producer(string& msg, unsigned id){
	msg = " msg created by: " + to_string(id);
}

void consumer(string& msg, unsigned id){
	std::unique_lock<mutex> lck(m_mux);
	std::cout << "I'm thread: " << id << msg << '\n';
	msg.clear();
}
//////////////////////////////
/*Procedimiento del main*/
int main(int argc, char const *argv[])
{

    /*Obtener n hilos para simulacion*/
	size_t n = std::atoi(argv[1]);
	/*Creamos un vector que almacene las tareas*/
	std::vector<thread> task(n);
	/*Vector para almacenar las cadenas*/
	std::vector<string> msg(n);
	/*Vector para almacenar lo semaforos*/
	std::vector<semaphores> sm_value(n);
	/*Medimos el tiempo*/
	std::cout << "-----------------------------------------------------------" << '\n';
	auto start = system_clock::now();
	auto seq_elapsed = system_clock::now() - start;
	std::cout << "Concurrent time: " 
    << duration_cast<microseconds>(seq_elapsed).count()
    << " us " << std::endl;
  	std::cout << "-----------------------------------------------------------" << '\n';
  	std::cout << '\n';

	/*Mensajes*/
	for (unsigned i = 0; i < n; i++) {
		/*Obtener el antesesor*/
		unsigned modVal = (i+n-1)%n; 
		/*Lanzamos las tareas*/
		task[i] = std::thread(task_proCon, ref(sm_value[i]), ref(sm_value[modVal]), ref(msg), i, modVal);
  	}

  	/*Unimos las tareas*/
  	for (auto& t : task)
  	{
  		/*Join*/
  		t.join();
  	}
    return 0;
}