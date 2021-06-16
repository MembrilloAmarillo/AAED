#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "algoritmos.h"
#include "cronometro.h"

template <typename T>
double test_algoritmos(T inicio, T fin, uint8_t eleccion)
{
	Cronometro C;
	long int r = 0;
	const double error_absoluto = 0.01; 
	const double error_relativo = 0.001; // Error relativo aceptado

	C.activar();

	do
	{
		switch (eleccion)
		{
		case 0:
			std::random_shuffle(inicio, fin);
			ordenacion_seleccion_directa(inicio, fin);
			break;
		case 1:
			std::random_shuffle(inicio, fin);
			ordenacion_intercambio_directo(inicio, fin);
			break;
		case 2:
			std::random_shuffle(inicio, fin);
			ordenacion_insercion_directa(inicio, fin);
			break;
		default:
			break;
		}
		++r;
	} while (C.tiempo() < (error_absoluto / (error_relativo + error_absoluto)));

	C.parar();

	/* Tiempo medio */
	double t = C.tiempo() / r;

	return t;
}

int main()
{
	enum algoritmo { SELECCION, INTERCAMBIO, INSERCION };

	const int N = 20000;  
	const int INCR = 1000;

	double t1, t2, t3; // Almacenan los tiempos

	int* v2 = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++) v2[i] = i;

	for (int i = INCR; i <= N; i += INCR )
	{
		/* Llamada con cada una de los algoritmos de insercion */
		t1 = test_algoritmos(v2, v2 + i, algoritmo::SELECCION);
		std::cout << "Seleccion   "<< i << " " << t1 << std::endl;
		t2 = test_algoritmos(v2, v2 + i, algoritmo::INSERCION);
		std::cout << "Insercion   "<< i << " " << t2 << std::endl;
		t3 = test_algoritmos(v2, v2 + i, algoritmo::INTERCAMBIO);
		std::cout << "Intercambio "<< i << " " << t3 << std::endl;
	}
	std::cout << "SELECCION"   << std::endl;
	std::cout << t1			   << std::endl;
	std::cout << "INSERCION"   << std::endl;
	std::cout << t2			   << std::endl;
	std::cout << "INTERCAMBIO" << std::endl;
	std::cout << t3            << std::endl;

	return EXIT_SUCCESS;
}
