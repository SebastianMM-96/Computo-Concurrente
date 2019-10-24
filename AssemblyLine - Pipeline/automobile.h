/*
Obj:
La clase automobile tendrá todos los métodos
set necesarios para que el carro pueda ser ensamblado.
*/
class automobile {
	private:
		/*Partes que componen el automovil*/

		/*Bodywork*/
		bool bodywork_1;
		bool bodywork_2;
		bool bodywork_3;

		/*Paint*/
		bool paint_1;
		bool paint_2;

		/*Motor*/
		bool motor_1;
		bool motor_2;
		bool motor_3;

		/*Seating´s*/
		bool seating_1;
		bool seating_2;

		/*Accesories*/
		bool accesories_1;
		bool accesories_2;
		bool accesories_3;
		bool accesories_4;
		bool accesories_5;

	public:
		/*Inicializamos el constructor de la clase*/
		automobile();

		void set_bodywork_1();
		void set_bodywork_2();
		void set_bodywork_3();

		void set_paint_1();
		void set_paint_2();

		void set_motor_1();
		void set_motor_2();
		void set_motor_3();

		void set_seating_1();
		void set_seating_2();

		void set_accesories_1();
		void set_accesories_2();
		void set_accesories_3();
		void set_accesories_4();
		void set_accesories_5();

		/*Getter´s?*/

		bool get_bodywork_1();
		bool get_bodywork_2();
		bool get_bodywork_3();

		bool get_paint_1();
		bool get_paint_2();

		bool get_motor_1();
		bool get_motor_2();
		bool get_motor_3();

		bool get_seating_1();
		bool get_seating_2();

		bool get_accesories_1();
		bool get_accesories_2();
		bool get_accesories_3();
		bool get_accesories_4();
		bool get_accesories_5();

};

/*Creamos el método constructor*/
automobile::automobile(){

	/*Bodywork*/
	this->bodywork_1 = false;
	this->bodywork_2 = false;
	this->bodywork_3 = false;

	/*Paint*/
	this->paint_1 = false;
	this->paint_2 = false;

	/*Motor*/
	this->motor_1 = false;
	this->motor_2 = false;
	this->motor_3 = false;

	/*Seating´s*/
	this->seating_1 = false;
	this->seating_2 = false;

	/*Accesories*/
	this->accesories_1 = false;
	this->accesories_2 = false;
	this->accesories_3 = false;
	this->accesories_4 = false;
	this->accesories_5 = false;
};

/*BodyWork*/
void automobile::set_bodywork_1(){
	this->bodywork_1 = true;
}
void automobile::set_bodywork_2(){
	this->bodywork_2 = true;
}
void automobile::set_bodywork_3(){
	this->bodywork_3 = true;
}
/*Paint*/

void automobile::set_paint_1(){
	this->paint_1 = true;
}
void automobile::set_paint_2(){
	this->paint_2 = true;
}

/*Motor*/
void automobile::set_motor_1(){
	this->motor_1 = true;
}
void automobile::set_motor_2(){
	this->motor_2 = true;
}
void automobile::set_motor_3(){
	this->motor_3 = true;
}

/*Seating´s*/
void automobile::set_seating_1(){
	this->seating_1 = true;
}
void automobile::set_seating_2(){
	this->seating_2 = true;
}

/*Accesories*/
void automobile::set_accesories_1(){
	this->accesories_1 = true;
}
void automobile::set_accesories_2(){
	this->accesories_2 = true;
}
void automobile::set_accesories_3(){
	this->accesories_3 = true;
}
void automobile::set_accesories_4(){
	this->accesories_4 = true;
}
void automobile::set_accesories_5(){
	this->accesories_5 = true;
}
/*Getter´s */

/*Bodywork*/
bool automobile::get_bodywork_1(){
	return this->bodywork_1;
}
bool automobile::get_bodywork_2(){
	return this->bodywork_2;
}
bool automobile::get_bodywork_3(){
	return this->bodywork_3;
}

/*Paint*/
bool automobile::get_paint_1(){
	return this->paint_1;
}
bool automobile::get_paint_2(){
	return this->paint_2;
}

/*Motor*/
bool automobile::get_motor_1(){
	return this->motor_1;
}
bool automobile::get_motor_2(){
	return this->motor_2;
}
bool automobile::get_motor_3(){
	return this->motor_3;
}

/*Seating*/
bool automobile::get_seating_1(){
	return this->seating_1;
}
bool automobile::get_seating_2(){
	return this->seating_2;
}

/*Accesories*/
bool automobile::get_accesories_1(){
	return this->accesories_1;
}
bool automobile::get_accesories_2(){
	return this->accesories_2;
}
bool automobile::get_accesories_3(){
	return this->accesories_3;
}
bool automobile::get_accesories_4(){
	return this->accesories_4;
}
bool automobile::get_accesories_5(){
	return this->accesories_5;
}