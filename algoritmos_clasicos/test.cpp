#include <iostream>
#include <vector>
#include <random>

#include "algoritmos.h"

int main()
{
	std::vector<int> v = { 1,2,3,4,5,6,7 };
	int x = 3;

	size_t posicion = busqueda_secuencial(v.begin(), x, v.size());
	std::cout << "Encontrado en posicion: " << posicion << std::endl;

	char *c = _strdup("Hola");
	char cc = 'b';

	size_t posicion1 = busqueda_secuencial(c, cc, 12);
	std::cout << "Encontrado en posicion: " << posicion1 << std::endl;

	std::vector<int> vv{ 0, 1, 3, 4, 5, 6, 9 };
	std::random_shuffle(vv.begin(), vv.end());
	std::cout << "Vector desordenado" << std::endl;
	for ( auto x : vv )
		std::cout << x << ", ";
	std::cout << "\n";
	
	ordenacion_intercambio_directo(vv.begin(), vv.end());

	std::cout << "Ordenacion por intercambio" << std::endl;
	for ( auto x : vv )
		std::cout << x << ", ";
	std::cout << "\n";

	std::vector<int> v1{ 10, 1, 3, 4, 5, 6, 9 };
	std::random_shuffle(v1.begin(), v1.end());
	std::cout << "Vector desordenando" << std::endl;
	for (auto x : v1)
		std::cout << x << ", ";
	std::cout << "\n";

	ordenacion_seleccion_directa(v1.begin(), v1.end());

	std::cout << "Ordenacion por seleccion directa" << std::endl;
	for (auto x : v1)
		std::cout << x << ", ";
	std::cout << "\n";

	std::vector<int> v2{ 19, 2, 3, 4, 5, 6, 1 };
	std::random_shuffle(v2.begin(), v2.end());
	std::cout << "Vector desordenando" << std::endl;
	for (auto x : v2)
		std::cout << x << ", ";
	std::cout << "\n";

	ordenacion_insercion_directa(v2.begin(), v2.end());

	std::cout << "Ordenacion por insercion directa" << std::endl;
	for (auto x : v2)
		std::cout << x << ", ";
	std::cout << "\n";


	return EXIT_SUCCESS;
}