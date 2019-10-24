/*
Obj:
La clase pipeline tendrá por atributo un arreglo
stage de tipo array de objetos de tipo functional de tal
manera que cada objeto del arreglo stage está inicializado
con un método set de la clase automobile.
*/

#include <thread>
#include <array>
#include <functional>
#include <vector>
/*Creamos estos objetos*/
#include "automobile.h"
#include "semaphore.h"
#include <list>

using namespace std;

class pipeline{

private:
	/*Arreglo con objetos del tipo funcional*/
	std::array<std::function<void(pipeline&)>, 15> building;
	/*Semaforos*/
	std::array<semaphore, 15> sm;
	//automovil pasa por el arreglo en distintas etapas
	std::array<automobile*, 15> carArray;
	std::list<automobile> production;
	unsigned n;

	/*Iniciamos la Linea de Produccion*/
	void build_bodywork_1();
	void build_bodywork_2();
	void build_bodywork_3();

  void build_paint_1();
  void build_paint_2();

  void build_motor_1();
  void build_motor_2();
  void build_motor_3();

	void build_seating_1();
	void build_seating_2();

	void build_accesories_1();
	void build_accesories_2();
	void build_accesories_3();
	void build_accesories_4();
	void build_accesories_5();

public:
	pipeline(int n);
	/*Inicializar la pipeline de la produccion*/
	void automobileFactry();
	std::list<automobile> getProd();
};

/*Implementamos el metodo constructor*/
pipeline::pipeline(int n):n(n){
  pipeline::building[0] = &pipeline::build_bodywork_1;
	pipeline::building[1] = &pipeline::build_bodywork_2;
	pipeline::building[2] = &pipeline::build_bodywork_3;

	pipeline::building[3] = &pipeline::build_paint_1;
	pipeline::building[4] = &pipeline::build_paint_2;

	pipeline::building[5] = &pipeline::build_motor_1;
	pipeline::building[6] = &pipeline::build_motor_2;
	pipeline::building[7] = &pipeline::build_motor_3;

	pipeline::building[8] = &pipeline::build_seating_1;
	pipeline::building[9] = &pipeline::build_seating_2;

	pipeline::building[10] = &pipeline::build_accesories_1;
	pipeline::building[11] = &pipeline::build_accesories_2;
	pipeline::building[12] = &pipeline::build_accesories_3;
	pipeline::building[13] = &pipeline::build_accesories_4;
	pipeline::building[14] = &pipeline::build_accesories_5;
}

/*Metodos para la construccion de los automoviles*/
void pipeline::build_bodywork_1(){
	for(unsigned i = 0; i < n; i++){
		automobile* car = new automobile();
		car->set_bodywork_1();
		//std::cout << "1" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		carArray[0] = car;
		sm[1].notify();
		sm[0].wait();
		//car = nullptr;
	}
}
void pipeline::build_bodywork_2(){
  for(unsigned i = 0; i < n; i++){
    sm[1].wait();
    carArray[1] = carArray[0];
    carArray[0] = nullptr;    
    sm[0].notify();
    carArray[1]->set_bodywork_2();
  	//std::cout << "2" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[2].notify();
    sm[1].wait();
    //carArray[1] = nullptr;
  }
}
void pipeline::build_bodywork_3(){
  for(unsigned i = 0; i < n; i++){
    sm[2].wait();
    carArray[2] = carArray[1];
    carArray[1] = nullptr;    
    sm[1].notify();
    carArray[2]->set_bodywork_3();
  	//std::cout << "3" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[3].notify();
    sm[2].wait();
    //carArray[2] = nullptr;
  }
}

void pipeline::build_paint_1(){
  for(unsigned i = 0; i < n; i++){
    sm[3].wait();
    carArray[3] = carArray[2];
    carArray[2] = nullptr;    
    sm[2].notify();
    carArray[3]->set_paint_1();
  	//std::cout << "4" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[4].notify();
    sm[3].wait();
    //carArray[3] = nullptr;
  }
}
void pipeline::build_paint_2(){
  for(unsigned i = 0; i < n; i++){
    sm[4].wait();
    carArray[4] = carArray[3];
    carArray[3] = nullptr;    
    sm[3].notify();
    carArray[4]->set_paint_2();
  	//std::cout << "5" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[5].notify();
    sm[4].wait();
    //carArray[4] = nullptr;
  }
}

void pipeline::build_motor_1(){
  for(unsigned i = 0; i < n; i++){
    sm[5].wait();
    carArray[5] = carArray[4];
    carArray[4] = nullptr;    
    sm[4].notify();
    carArray[5]->set_motor_1();
  	//std::cout << "6" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[6].notify();
    sm[5].wait();
    //carArray[5] = nullptr;
  }
}
void pipeline::build_motor_2(){
  for(unsigned i = 0; i < n; i++){
    sm[6].wait();
    carArray[6] = carArray[5];
    carArray[5] = nullptr;    
    sm[5].notify();
    carArray[6]->set_motor_2();
  	//std::cout << "7" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[7].notify();
    sm[6].wait();
    //carArray[6] = nullptr;
  }
}
void pipeline::build_motor_3(){
  for(unsigned i = 0; i < n; i++){
    sm[7].wait();
    carArray[7] = carArray[6];
    carArray[6] = nullptr;    
    sm[6].notify();
    carArray[7]->set_motor_3();
  	//std::cout << "8" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[8].notify();
    sm[7].wait();
    //carArray[7] = nullptr;
  }
}

void pipeline::build_seating_1(){
  for(unsigned i = 0; i < n; i++){
    sm[8].wait();
    carArray[8] = carArray[7];
    carArray[7] = nullptr;
    sm[7].notify();
    carArray[8]->set_seating_1();
  	//std::cout << "9" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[9].notify();
    sm[8].wait();
    //carArray[8] = nullptr;
  }
}
void pipeline::build_seating_2(){
  for(unsigned i = 0; i < n; i++){
    sm[9].wait();
    carArray[9] = carArray[8];
    carArray[8] = nullptr;  
    sm[8].notify();
    carArray[9]->set_seating_2();
  	//std::cout << "10" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(500));
    sm[10].notify();
    sm[9].wait();
    //carArray[9] = nullptr;
  }
}

void pipeline::build_accesories_1(){
  for(unsigned i = 0; i < n; i++){
    sm[10].wait();
    carArray[10] = carArray[9];
    carArray[9] = nullptr;
    sm[9].notify();
    carArray[10]->set_accesories_1();
  	//std::cout << "11" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    sm[11].notify();
    sm[10].wait();
    //carArray[10] = nullptr;
  }
}
void pipeline::build_accesories_2(){
  for(unsigned i = 0; i < n; i++){
    sm[11].wait();
    carArray[11] = carArray[10];
    carArray[10] = nullptr;
    sm[10].notify();
    carArray[11]->set_accesories_2();
  	//std::cout << "12" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    sm[12].notify();
    sm[11].wait();
    //carArray[11] = nullptr;
  }
}
void pipeline::build_accesories_3(){
  for(unsigned i = 0; i < n; i++){
    sm[12].wait();
    carArray[12] = carArray[11];
    carArray[11] = nullptr;
    sm[11].notify();
    carArray[12]->set_accesories_3();
  	//std::cout << "13" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    sm[13].notify();
    sm[12].wait();
    //carArray[12] = nullptr;
  }
}
void pipeline::build_accesories_4(){
  for(unsigned i = 0; i < n; i++){
    sm[13].wait();
    carArray[13] = carArray[12];
    carArray[12] = nullptr;
    sm[12].notify();
    carArray[13]->set_accesories_4();
  	//std::cout << "14" << std::endl;
  	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    sm[14].notify();
    sm[13].wait();
    //carArray[13] = nullptr;
  }
}
void pipeline::build_accesories_5(){
	for (unsigned i = 0; i < n ; i++)	{
		sm[14].wait();
		carArray[14] = carArray[13];
  carArray[13] = nullptr;
		sm[13].notify();
		carArray[14]->set_accesories_5();
  //std::cout << "15" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		production.push_back(*carArray[14]);
		//carArray[14] = nullptr;
	}
}

/*Implementamos la pipeline de autos*/
void pipeline::automobileFactry(){
	/*Arreglo de hilos correspondientes a cada stage*/
	std::array<thread, 15> task;
	/*launch - task*/
	for (unsigned stage = 0; stage < 15; stage++)	{
		task[stage] = std::thread(pipeline::building[stage],std::ref(*this));
    //std::cout << "task: " << stage << std::endl;
	}
	/*Join thread´s*/
	for (auto& t:task)	{
		t.join();
	}
}

std::list<automobile> pipeline::getProd(){
	return production;
}
