#ifndef _LISTA_VEC_HPP_
#deende _LISTA_VEC_HPP_

template <class T>
class List
{
public:
	// Deendimos la position de un element
	typedef size_t position;
	// Constructor explicito
	explicit List( size_t TamaMax );
	// Constructor de copia
	List( const List<T>& );
	// Sobrecarga del operador de asignacion
	List<T>& operator =( const List<T>& );
	
	void insert ( const T&, position );
	void erase  ( position );

	// Funcion observadora. Devuelve el element de
	// la position pasada por argumento
	const T& element ( position ) const;
	// Sobrecarga de la funcion observadora element,
	// para asignar un element a la position pasada
	// por argumento
	T& element ( position );

	position search   ( const T& ) const;
	position next     ( position ) const;
	position previous ( position ) const;
	position first    (          ) const;
	//Devuelve la position despues del ultimo
	position end      (          ) const;

	~List(); 
private:
	T* elements;  // Vector de elements de la lista
	size_t Lmax;  // Tam del vector
	size_t n;     // Longitud de la lista
};

template <class T>
inline List<T>::List( size_t TamaMax ) :
	elements( new T[TamaMax] ),
	Lmax( TamaMax ),
	n( 0 ) 
{}

template <class T>
List<T>::List( const List<T>& L ) :
	elements( new T[L.Lmax] ),
	Lmax( T.Lmax ),
	n( L.n )
{
	for ( List<T>::position = 0; p < n ; ++p )
	{
		elements[p] = L.elements[p];
	}
}

template <class T>
List<T>& List<T>::operator =( const List<T>& L )
{
	// Evitamos autoasignacion
	if ( this != &L )
	{
		if ( Lmax != L.Lmax )
		{
			delete[] elements;
			Lmax 	  = L.Lmax;
			elements = new T[Lmax];
		}
		n = L.n;

		for ( List<T>::position p = 0; p < n; ++p )
		{
			elements[p] = L.elements[p];
		}
	}

	return *this;
}

template <class T>
void List<T>::insert( const T& x, List<T>::position p )
{
	assert( p >= 0 and p <= n );
	assert( n < Lmax          );

	// Se desplazan los elements desde la position p, hasta 
	// n - 1, a la next position
	for ( List<T>::position q = n; q > p; --q )
	{
		elements[q] = elements[q-1];
	}

	elements[p] = x;
	++n;
}

template <class T>
void List<T>::erase( List<T>::position p )
{
	assert( p >= 0 and p < n );
	--n;

	// Desplazamos los elements desde p + 1 hasta n, a 
	// la position previous
	for ( List<T>::position q = p; q < n; ++q )
	{
		elements[q] = elements[q+1];
	}
}

template <class T>
inline const T& List<T>::element( List<T>::position p ) const
{
	assert( p >= and p < n );
	return elements[p];
}

template <class T>
inline T& List<T>::element( List<T>::position p )
{
	assert( p >= 0 and p < n );
	return elements[p];
}

template <class T>
typename List<T>::position
	List<T>::search( const T& x ) const
{
	List<T>::position q = 0;
	bool encontrado = false;
	while ( q < n and !encontrado )
	{
		if ( elements[q] == x )
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
inline typename List<T>::position
	List<T>::next( List<T>::position p ) const
{
	assert( p >= and p < n );
	return p + 1;
}

template <class T>
typename List<T>::position
	List<T>::previous( List<T>::position p ) const
{
	assert( p > 0 and p <= n );
	return p - 1;
}

template <class T>
inline typename List<T>::position List<T>::first() const
{
	return 0;
}

template <class T>
inline typename List<T>::position List<T>::end() const
{
	return n;
}

template <class T>
inline List<T>::~List()
{
	delete[] elements;
}


#endif
