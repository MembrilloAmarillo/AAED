#ifndef _ALGORITMOS_HPP_
#define _ALGORITMOS_HPP_

#include <cstddef>

/* 
 * Busqueda Secuencial
 * Definicion -> Sea V un conjunto, y un x de V el elemento a buscar y 
 * v el vector.
 * Se desea la posicion de la primera aparicion de x en v, si este aparece, o
 * bien n + 1 en caso contrario.
 * Mejor caso : p = 1
 *	Se encuentra x en la primera comparacion
 *	tmin( n ) = 1 O(1) 
 * Peor caso: p = n o p = n + 1
 *	tmax( n ) = O(n)
 * Caso promedio: probabilidad B = 1 - a, siendo a la probabilidad de se encontrado
	tprom( n ) = O(n)
 */

template <typename input,typename type>
size_t busqueda_secuencial( const input v, const type& x, const size_t& size )
{
	size_t posicion;
	for (posicion = 0; posicion < size && *(v + posicion) != x; posicion++);
	return posicion;
}

/* FIN BUSQUEDA SECUENCIAL */

/*
 * Ordenacion por intercambio directo
 * Caso peor, mejor y promedio
 *		El numero de comparaciones no depende de v, solo de n
 *		No hay diferencia entre los casos
 *	Analisis del bucle externo
 *		Varia 'i' desde 1 hasta n - 1, realizando n - i comparaciones
 *		sum(n-i, i=1) = (n * (n-1)) / 2 
 *		Coste Theta(n^2)
 * =====================================================================
 * Imaginemos el vector v [9 8 7 6 5]
 * burbujeo( v, 0, 5 ), hacemos paso a paso
 * si v[k] < v[k-1], es decir, 5 < 6:
 *		v[k] = 6; v[k-1] = 5; k--;
 * si v[k] < v[k-1], es decir, 5 < 7:
 *		v[k] = 7; v[k-1] = 5; k--;
 * Como vemos, por cada llamada a burbujeo, ordenamos un
 * elemento. Por tanto, necesitamos llamar a burbujeo n - 1
 * veces para ordenar al completo el vector.
 */

template <typename input>
static void burbujeo( input ini, input fin )
{
	for ( input it = fin - 1; it > ini; it-- )
	{
		if ( *it < *(it - 1) )
		{
			auto temp_value = *it;
			*it = *(it - 1);
			*(it - 1) = temp_value;
		}
	}
}

template <typename input>
void ordenacion_intercambio_directo( input vini, input vfin )
{
	for ( ; vini != vfin; vini++ )
	{
		burbujeo(vini, vfin);
	}
}

/*
 * Ordenacion por seleccion directa
 * El analisis es el mismo que al del algoritmo de intercambio 
 * directo
 */

template <typename input>
size_t posicion_minimo(input ini, input fin, size_t i)
{
	size_t posicion = i;
	auto m = *(ini + i);

	for (auto k = i + 1; ini + k < fin; k++)
	{
		if (*(ini + k) < m)
		{
			posicion = k;
			m = *( ini + k );
		}
	}
	return posicion;
}

template <typename input>
void ordenacion_seleccion_directa(input ini, input fin)
{
	for ( size_t i = 0; ini + i < fin; i++ )
	{
		size_t posicion = posicion_minimo(ini, fin, i);
		auto temp = *(ini + posicion);
		*(ini + posicion) = *(ini + i);
		*(ini + i) = temp;
	}
}

/*
 * Ordenacion por insercion directa
 * Mejor caso: el vector esta ordenado, orden Theta(n)
 * Pero caso: el vector esta ordenado inversamente, orden Theta(n^2)
 * Caso promedio: orden Theta(log n)
 */

template <typename input>
void insercion(input v, input j)
{
	input i = j;
	auto x = *i;
	while (i != v and x < *(i-1))
	{
		*(i) = *(i - 1);
		i--;
	}
	*(i) = x;
}

template <typename input>
void ordenacion_insercion_directa(input ini, input fin)
{
	for (input i = (ini + 1); i != fin; i++)
	{
		insercion(ini, i);
	}
}

#endif
