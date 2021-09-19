#ifndef _PILA_HPP_
#define _PILA_HPP_

#include <cassert>

/*
 * TAD stack with generic pseudostatic vectorial implementation
 * 
 * Vector with fixed size specified by the user. The user is in charge of storing
 * the values that will be inserting onto the stack.
 * 
 */

template <typename tElement>
class stack
{
public:
	/* Requiere pasar TamMax */
	explicit stack( size_t );

	stack( const stack& );
	stack& operator =( const stack& );
	/* Funciones observadoras */
	bool empty() const;
	bool full() const;
	const tElement& top() const;
	
	void pop();
	void push( const tElement& );

	~stack();
private:
	/* Vector de elements */
	tElement* elements;
	/* Tam del vector */
	size_t Lmax;
	/* Posicion del _top */
	int _top;
};

template <typename T>
stack<T>::stack( size_t TamMax ) :
	Lmax(TamMax),
	_top(-1),
	elements(new T[TamMax]) 
{ }

template <typename T>
stack<T>::stack( const stack& P ) :
	elements( new T[P.Lmax]),
	Lmax( P.Lmax ),
	_top( P._top )
{
	for( size_t i = 0; i < _top; i++ )
	{
		elements[i] = P.elements[i];
	}
}

template <typename T>
stack<T>& stack<T>::operator =( const stack<T>& P )
{
	/* Evitamos autoasignacion */
	if ( this != &P )
	{
		if ( Lmax != P.Lmax )
		{
			delete[] elements;
			Lmax = P.Lmax;
			elements = new T[Lmax];
		}
		_top = P._top;
		for ( size_t i = 0; i < _top; i++ )
		{
			elements[i] = P.elements[i];
		}
	}
	return *this;
}

template <typename T>
inline bool stack<T>::empty() const
{
	return ( _top == -1 );
}

template <typename T>
inline bool stack<T>::full() const
{
	return ( _top == Lmax - 1);
}

template <typename T>
inline const T& stack<T>::top() const
{
	assert( !empty() );
	return elements[_top];
}

template <typename T>
inline void stack<T>::pop()
{
	assert( !empty() );
	--_top;
}

template <typename T>
inline void stack<T>::push( const T& x )
{
	assert( !full() );
	++_top;
	elements[_top] = x;
}

template <typename T>
inline stack<T>::~stack()
{
	delete[] elements; 
}

#endif
