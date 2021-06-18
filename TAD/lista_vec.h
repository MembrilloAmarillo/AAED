#ifndef _LISTA_VEC_HPP_
#define _LISTA_VEC_HPP_

template <class T>
class Lista
{
public:
	// Definimos la posicion de un elemento
	typedef size_t posicion;
	// Constructor explicito
	explicit Lista( size_t TamaMax );
	// Constructor de copia
	Lista( const Lista<T>& );
	// Sobrecarga del operador de asignacion
	Lista<T>& operator =( const Lista<T>& );
	
	void insertar( const T&, posicion );
	void eliminar( posicion );

	// Funcion observadora. Devuelve el elemento de
	// la posicion pasada por argumento
	const T& elemento( posicion ) const;
	// Sobrecarga de la funcion observadora elemento,
	// para asignar un elemento a la posicion pasada
	// por argumento
	T& elemento( posicion );

	posicion buscar   ( const T& ) const;
	posicion siguiente( posicion ) const;
	posicion anterior ( posicion ) const;
	posicion primera  (          ) const;
	//Devuelve la posicion despues del ultimo
	posicion fin      (          ) const;

	~Lista(); 
private:
	T* elementos; // Vector de elementos de la lista
	size_t Lmax;  // Tam del vector
	size_t n;     // Longitud de la lista
};

template <class T>
inline Lista<T>::Lista( size_t TamaMax ) :
	elementos( new T[TamaMax] ),
	Lmax( TamaMax ),
	n( 0 ) 
{}

template <class T>
Lista<T>::Lista( const Lista<T>& L ) :
	elementos( new T[L.Lmax] ),
	Lmax( T.Lmax ),
	n( L.n )
{
	for ( Lista<T>::posicion = 0; p < n ; ++p )
	{
		elementos[p] = L.elementos[p];
	}
}

template <class T>
Lista<T>& Lista<T>::operator =( const Lista<T>& L )
{
	// Evitamos autoasignacion
	if ( this != &L )
	{
		if ( Lmax != L.Lmax )
		{
			delete[] elementos;
			Lmax 	  = L.Lmax;
			elementos = new T[Lmax];
		}
		n = L.n;

		for ( Lista<T>::posicion p = 0; p < n; ++p )
		{
			elementos[p] = L.elementos[p];
		}
	}

	return *this;
}

template <class T>
void Lista<T>::insertar( const T& x, Lista<T>::posicion p )
{
	assert( p >= 0 and p <= n );
	assert( n < Lmax          );

	// Se desplazan los elementos desde la posicion p, hasta 
	// n - 1, a la siguiente posicion
	for ( Lista<T>::posicion q = n; q > p; --q )
	{
		elementos[q] = elementos[q-1];
	}

	elementos[p] = x;
	++n;
}

template <class T>
void Lista<T>::eliminar( Lista<T>::posicion p )
{
	assert( p >= 0 and p < n );
	--n;

	// Desplazamos los elementos desde p + 1 hasta n, a 
	// la posicion anterior
	for ( Lista<T>::posicion q = p; q < n; ++q )
	{
		elementos[q] = elementos[q+1];
	}
}

template <class T>
inline const T& Lista<T>::elemento( Lista<T>::posicion p ) const
{
	assert( p >= and p < n );
	return elementos[p];
}

template <class T>
inline T& Lista<T>::elemento( Lista<T>::posicion p )
{
	assert( p >= 0 and p < n );
	return elementos[p];
}

template <class T>
typename Lista<T>::posicion
	Lista<T>::buscar( const T& x ) const
{
	Lista<T>::posicion q = 0;
	bool encontrado = false;
	while ( q < n and !encontrado )
	{
		if ( elementos[q] == x )
		{
			encontrado = true;
		}
		else
		{
			++q;
		}
	}
	return q;
}

template <class T> 
inline typename Lista<T>::posicion
	Lista<T>::siguiente( Lista<T>::posicion p ) const
{
	assert( p >= and p < n );
	return p + 1;
}

template <class T>
typename Lista<T>::posicion
	Lista<T>::anterior( Lista<T>::posicion p ) const
{
	assert( p > 0 and p <= n );
	return p - 1;
}

template <class T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
	return 0;
}

template <class T>
inline typename Lista<T>::posicion Lista<T>::fin() const
{
	return n;
}

template <class T>
inline Lista<T>::~Lista()
{
	delete[] elementos;
}


#endif
