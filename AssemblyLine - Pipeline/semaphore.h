#include <mutex>
#include <condition_variable>

class semaphore {
	private:
		std::mutex mtx;
		std::condition_variable cv;
		unsigned sm;
	public:
		/*Construccion del semaforo*/
		semaphore(unsigned n = 0) {
			this->sm = n;
		}
		/*Permitir el acceso a lo recursos de los hilos*/
		void wait(){
			std::unique_lock<std::mutex> lk(mtx);
			cv.wait(lk, [&]{return sm > 0;});
			sm--;
		}
		/*Metodo para dar aviso de que el hilo esta libre*/
		void notify(){
			std::unique_lock<std::mutex> lk(mtx);
			sm++;
			cv.notify_one();
		}
};
