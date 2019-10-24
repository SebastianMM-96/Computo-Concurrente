#include <mutex>	
#include <condition_variable>

using namespace std;

class semaphores
{
private:

	/*Declaramos las variables*/
	unsigned sm_value; // Valor del semaforo
    mutex m_mux; // Variable de control de acceso
    condition_variable cv; // Variable de control
public:
	/*Constructor del Semaforo*/
	semaphores();
	/*Declaracion de los metodos*/
	void wait(){
		// Esto bloquea el mutex hasta que se destruye al salir del método.
		unique_lock<mutex> lck(m_mux);
		/*se puede desbloquear el mutex ates de que la vida de la clase termine.
		Despues de que se desbloque el mutex el mismo programa 
		puede bloquearlo nuevamente
		*/
		while(!sm_value) // Compruebe el valor de exclusión mutua y espere si es necesario.
			// Mientras espera, el mutex se desbloquea hasta que la espera termine.
			cv.wait(lck);
			/*
		    La ejecución del hilo actual se bloquea hasta que se notifique .
		    En el momento de bloquear el hilo, la función llama automáticamente, permitiendo 
		    que otros hilos bloqueados continúen.
		    Una vez notificada (explícitamente, por algún otro hilo)
		    la función se desbloquea y llama 
		    dejando a lck en el mismo estado que cuando se llamó a la función.
		    */     
		sm_value--;
	}
	void notify(){
		// Esto bloquea el mutex hasta que se destruye al salir del método.
		unique_lock<mutex> lck(m_mux);
		sm_value++;
		cv.notify_one();
		/*
			Desbloquea uno de los subprocesos actualmente en espera de esta condición.
			Si no hay hilos esperando, la función no hace nada.
			Si hay más de uno, no se especifica cuál de los hilos está seleccionado.
			*/
	}
};
/*Inicializamos el metodo constructor del semaforo*/
semaphores::semaphores(){
	this ->sm_value = 1;
}