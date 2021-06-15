#ifndef _CRONOMETRO_HPP_
#define _CRONOMETRO_HPP_

#include <ctime>

class Cronometro
{
public:
	Cronometro() : activo( false ) {}
	void activar()
	{
		activo = true;
		t0     = std::clock();
	}
	void parar()
	{
		if (activo)
		{
			t1     = std::clock();
			activo = false;
		}
	}
	double tiempo() const { return ((activo ? std::clock() : t1) - t0) / CPS; }
private:
	/* Cronometro activo o inactivo */
	bool activo;
	/* Almacena el tiempo de incio y el tiempo de finalizacion */
	std::clock_t t0, t1;
	/* CLOCKS PER SEC*/
	static double CPS;
};

double Cronometro::CPS(CLOCKS_PER_SEC);

#endif