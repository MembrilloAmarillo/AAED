#ifndef _LISTA_ENLA_CABECERA_HPP
#define _LISTA_ENLA_CABECERA_HPP

#include <cassert>

template <class T>
class List
{
	/* Declaracion adelantada */
	struct node;
public:
	/* Position de un element */
	typedef node* position;
	List();
	List( const List<T>& );

	List<T>& operator =( const List<T>& );

	void insert( const T&, position );
	void erase( position );

	/* Funcion devuelve element lvalor */
	T& element( position );
  
	/* Funciones no modificadoras */
	const T& element  ( position ) const;
	position search   ( const T& ) const;
	position next     ( position ) const;
	position previous ( position ) const;
	position first    (          ) const;
	position end      ( 		 ) const;


   List<T>& operator +=(const List<T>& l); // Concatenacion

	~List();

private:
	struct node
	{
		T elto;
		node* n_next;
		node( const T& e, node* p = nullptr ) :
			elto( e ), n_next( p )
		{}
	};

	/* List enlazada de nodes */
	node* L;

	void copiar( const List<T>& );
};

/* Metodo privado */
template <class T>
void List<T>::copiar( const List<T>& Lis )
{
	/* Crea el node cabecera */
	L = new node( T() );
	/* Apunta al node cabecera */
	node* q = L;
	for ( node* r = Lis.L->n_next; r; r = r->n_next )
	{
		q->n_next = new node( r->elto );
		q      = q->n_next;
	}
}

/* Metodos publicos */
template <class T>
inline List<T>::List() : 
	L( new node( T() ) )
{}

template <class T>
inline List<T>::List( const List<T>& Lis )
{
	copiar( Lis );
}

template <class T>
List<T>& List<T>::operator =( const List<T>& Lis )
{
	/* Evitar autoan_nextnacion */
	if ( this != &Lis )
	{
		this->~List();
		copiar( Lis );
	}
	return *this;
}

/*
 * Imaginemos una lista enlazada con cabecera:
 * 
 * Positiones:
 * +---+  +----+  +----+  +----+
 * | C |->| sg |->| sg |->| sg |
 * +---+  +----+  +----+  +----+
 * |   |  |  2 |  |  4 |  |  5 |
 * +---+  +----+  +----+  +----+
 * Si quisieramos insert un element en la position 0,
 * teniendo en cuenta que en se empieza desde un node cabecera,
 * todos los elements se encuentran en la position p + 1 de
 * la que realmente queremos insert.
 *
 * Position en la que queremos insert en la first position
 * Nuevo element a insert: 4
 * La position que se pasa:
 *   |
 *   v
 * +---+  +----+  +----+  +----+
 * | C |->| sg |->| sg |->| sg |
 * +---+  +----+  +----+  +----+
 * |   |  |  2 |  |  4 |  |  5 |
 * +---+  +----+  +----+  +----+
 *
 * Por tanto, tenemos que an_nextnar en p->n_next, y hacer que el
 * padre sea p->n_next antes de an_nextnarse, es decir:
 * La position p->n_next se mueve a otra position de memoria,
 * aunque n_nextue apuntando a sus nexts en la lista, pero, en la
 * position p->n_next ahora esta nuestro nuevo node, y apunta como next
 * al antiguo p->n_next reciendo movido.
 *
 *   	   +----+   
 * Position| +1 |---+ 
 *         +----+   |
 * Element|  4 |   |
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
 * List L;
 * L.insert( 1, L.first() );
 *
 * auto p = L.next( L.first() );
 * L.insert( 2, p );
 *
 * p      = L.next( p );
 * L.insert( 3, p );
 *
 * Ahora insertamos en la first position de nuevo
 * L.insert( 4, L.first() );
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
 * Como podemos ver, ahora tenemos 4 en la misma position
 * donde teniamos 1. Este ultimo se ha movido a otra position
 * de memoria, pero conservando los punteros a las nexts
 * celdas.
 */

template <class T>
void List<T>::insert( const T& x, List<T>::position p )
{
	p->n_next = new node( x, p->n_next );
}

template <class T>
inline void List<T>::erase( List<T>::position p )
{
	/* No es node endal */
	assert( p->n_next );
	/* Hacemos un salto, q va a apuntar a la position next
	 * y la p->n_next va a ser la p->n_next.
	 * luego p->n_next = p->n_next->n_next y se borra p->n_next.
	 *
	 * Recordamos que existe un node cabecera que no apunta a
	 * ninguna position que contenga elements en la lista
	 */
	node* q = p->n_next;
	p->n_next  = q->n_next;

	delete q;
}

template <class T>
const T& List<T>::element( List<T>::position p ) const
{
	/* p no es endal */
	assert( p->n_next );
	return p->n_next->elto;
}

template <class T>
inline T& List<T>::element( List<T>::position p )
{
	assert( p->n_next );
	return p->n_next->elto;
}

template <class T>
typename List<T>::position List<T>::search( const T& x ) const
{
	node* q = L;
	bool encontrado = false;
	while ( q->n_next and !encontrado )
	{
		if ( q->n_next->elto == x )
		{
			encontrado = true;
		}
		else
		{
			q = q->n_next;
		}
	}
	return q;
}

template <class T>
inline typename List<T>::position
	List<T>::next( List<T>::position p ) const
{
	assert( p->n_next );
	return p->n_next;
}

template <class T>
typename List<T>::position
	List<T>::previous( List<T>::position p ) const
{
	node* q;

	/* p no es el node cabecera */
	assert( p != L );
	for ( q = L; q->n_next != p; q = q->n_next );

	return q;
}

template <class T>
inline typename List<T>::position List<T>::first() const
{
	return L;
}

template <class T>
typename List<T>::position List<T>::end() const
{
	node* p;
	/* Mientras que exista p->n_next, aun no ha llegado
	 * al endal de la lista
	 * */
	for ( p = L; p->n_next; p = p->n_next );

	return p;
}

template <class T>
List<T>::~List()
{
	node* q;
	/* Hace lo mismo que la funcion erase, pero en bucle*/
	while ( L )
	{
		q = L->n_next;
		delete L;
		L = q;
	}
}

// Concatenacion de listas (para recorridos)
template<typename T>
List<T>& List<T>::operator +=(const List<T>& L)
{
   for (List<T>::position i = L.first(); i != L.end(); i = L.next(i))
      insert(L.element(i), end());
   return *this;
}

template<typename T>
List<T> operator +(const List<T>& L1, const List<T>& L2)
{
   return List<T>(L1) += L2;
}

#endif
