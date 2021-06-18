#ifndef _LISTA_ENLA_CABECERA_HPP
#define _LISTA_ENLA_CABECERA_HPP

#include <cassert>

template <class T>
class Lista
{
	/* Declaracion adelantada */
	struct nodo;
public:
	/* Posicion de un elemento */
	typedef nodo* posicion;
	Lista();
	Lista( const Lista<T>& );

	Lista<T>& operator =( const Lista<T>& );

	void insertar( const T&, posicion );
	void eliminar( posicion );

	/* Funcion devuelve elemento lvalor */
	T& elemento( posicion );

	/* Funciones no modificadoras */
	const T& elemento ( posicion ) const;
	posicion buscar   ( const T& ) const;
	posicion siguiente( posicion ) const;
	posicion anterior ( posicion ) const;
	posicion primera  (          ) const;
	posicion fin      ( 		 ) const;

	~Lista();

private:
	struct nodo
	{
		T elto;
		nodo* sig;
		nodo( const T& e, nodo* p = nullptr ) :
			elto( e ), sig( p )
		{}
	};

	/* Lista enlazada de nodos */
	nodo* L;

	void copiar( const Lista<T>& );
};

/* Metodo privado */
template <class T>
void Lista<T>::copiar( const Lista<T>& Lis )
{
	/* Crea el nodo cabecera */
	L = new nodo( T() );
	/* Apunta al nodo cabecera */
	nodo* q = L;
	for ( nodo* r = Lis.L->sig; r; r = r->sig )
	{
		q->sig = new nodo( r->elto );
		q      = q->sig;
	}
}

/* Metodos publicos */
template <class T>
inline Lista<T>::Lista() : 
	L( new nodo( T() ) )
{}

template <class T>
inline Lista<T>::Lista( const Lista<T>& Lis )
{
	copiar( Lis );
}

template <class T>
Lista<T>& Lista<T>::operator =( const Lista<T>& Lis )
{
	/* Evitar autoasignacion */
	if ( this != &Lis )
	{
		this->~Lista();
		copiar( Lis );
	}
	return *this;
}

/*
 * Imaginemos una lista enlazada con cabecera:
 * 
 * Posiciones:
 * +---+  +----+  +----+  +----+
 * | C |->| sg |->| sg |->| sg |
 * +---+  +----+  +----+  +----+
 * |   |  |  2 |  |  4 |  |  5 |
 * +---+  +----+  +----+  +----+
 * Si quisieramos insertar un elemento en la posicion 0,
 * teniendo en cuenta que en se empieza desde un nodo cabecera,
 * todos los elementos se encuentran en la posicion p + 1 de
 * la que realmente queremos insertar.
 *
 * Posicion en la que queremos insertar en la primera posicion
 * Nuevo elemento a insertar: 4
 * La posicion que se pasa:
 *   |
 *   v
 * +---+  +----+  +----+  +----+
 * | C |->| sg |->| sg |->| sg |
 * +---+  +----+  +----+  +----+
 * |   |  |  2 |  |  4 |  |  5 |
 * +---+  +----+  +----+  +----+
 *
 * Por tanto, tenemos que asignar en p->sig, y hacer que el
 * padre sea p->sig antes de asignarse, es decir:
 * La posicion p->sig se mueve a otra posicion de memoria,
 * aunque sigue apuntando a sus siguientes en la lista, pero, en la
 * posicion p->sig ahora esta nuestro nuevo nodo, y apunta como siguiente
 * al antiguo p->sig reciendo movido.
 *
 *   	   +----+   
 * Posicion| +1 |---+ 
 *         +----+   |
 * Elemento|  4 |   |
 * 	   +----+   |
 *                  |
 *	 +----------+
 *       |
 *	 V
 * +---+  +----+  +----+  +----+
 * | C |->| sg |->| sg |->| sg |
 * +---+  +----+  +----+  +----+
 * |   |  |  2 |  |  4 |  |  5 |
 * +---+  +----+  +----+  +----+
 *
 * Un ejemplo en codigo:
 *
 * Lista L;
 * L.insertar( 1, L.primera() );
 *
 * auto p = L.siguiente( L.primera() );
 * L.insertar( 2, p );
 *
 * p      = L.siguiente( p );
 * L.insertar( 3, p );
 *
 * Ahora insertamos en la primera posicion de nuevo
 * L.insertar( 4, L.primera() );
 * 
 *  Antes de hacer nueva insercion
 *  0x55a3cca23eb0 1
 *  0x55a3cca23ed0 2
 *  0x55a3cca24300 3
 * ============================
 *  Despues de hacer insercion
 *  0x55a3cca23eb0 4
 *  0x55a3cca24340 1
 *  0x55a3cca23ed0 2
 *  0x55a3cca24300 3
 *
 * Como podemos ver, ahora tenemos 4 en la misma posicion
 * donde teniamos 1. Este ultimo se ha movido a otra posicion
 * de memoria, pero conservando los punteros a las siguientes
 * celdas.
 */

template <class T>
void Lista<T>::insertar( const T& x, Lista<T>::posicion p )
{
	p->sig = new nodo( x, p->sig );
}

template <class T>
inline void Lista<T>::eliminar( Lista<T>::posicion p )
{
	/* No es nodo final */
	assert( p->sig );
	/* Hacemos un salto, q va a apuntar a la posicion siguiente
	 * y la p->sig va a ser la p->sig.
	 * luego p->sig = p->sig->sig y se borra p->sig.
	 *
	 * Recordamos que existe un nodo cabecera que no apunta a
	 * ninguna posicion que contenga elementos en la lista
	 */
	nodo* q = p->sig;
	p->sig  = q->sig;

	delete q;
}

template <class T>
const T& Lista<T>::elemento( Lista<T>::posicion p ) const
{
	/* p no es final */
	assert( p->sig );
	return p->sig->elto;
}

template <class T>
inline T& Lista<T>::elemento( Lista<T>::posicion p )
{
	assert( p->sig );
	return p->sig->elto;
}

template <class T>
typename Lista<T>::posicion Lista<T>::buscar( const T& x ) const
{
	nodo* q = L;
	bool encontrado = false;
	while ( q->sig and !encontrado )
	{
		if ( q->sig->elto == x )
		{
			encontrado = true;
		}
		else
		{
			q = q->sig;
		}
	}
	return q;
}

template <class T>
inline typename Lista<T>::posicion
	Lista<T>::siguiente( Lista<T>::posicion p ) const
{
	assert( p->sig );
	return p->sig;
}

template <class T>
typename Lista<T>::posicion
	Lista<T>::anterior( Lista<T>::posicion p ) const
{
	nodo* q;

	/* p no es el nodo cabecera */
	assert( p != L );
	for ( q = L; q->sig != p; q = q->sig );

	return q;
}

template <class T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
	return L;
}

template <class T>
typename Lista<T>::posicion Lista<T>::fin() const
{
	nodo* p;
	/* Mientras que exista p->sig, aun no ha llegado
	 * al final de la lista
	 * */
	for ( p = L; p->sig; p = p->sig );

	return p;
}

template <class T>
Lista<T>::~Lista()
{
	nodo* q;
	/* Hace lo mismo que la funcion eliminar, pero en bucle*/
	while ( L )
	{
		q = L->sig;
		delete L;
		L = q;
	}
}

#endif
