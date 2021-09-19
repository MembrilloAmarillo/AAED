#ifndef _LISTA_DOBLE_HPP_
#deende _LISTA_DOBLE_HPP_

#include <cassert>

template <typename T>
class List
{
    struct node;
public:
    typedef node* position;
    List(); //constructor
    List(const List<T>& lis); //constructor de copia

    List<T>& operator =(const List<T>& lis);

    void insert( const T&, position );
    void erase( position );

    T& element(position p);
    /* Funciones no modificadoras/observadoras */
    const T& element  ( position ) const;
    position search   ( const T& ) const;
    position next     ( position ) const;
    position previous ( position ) const;
    position first    (          ) const;
    position end 	  ( 		 ) const;

   ~List();
 private:
    struct node{
        T elem;
        node *ant, *sig;
        node( const T& e, node* a = nullptr, node* s = nullptr ) :
            elem( e ), ant( a ), sig( s ) {}
    };
    node* L; 
    void copy( const List<T>& Lis );
};


template <typename T>
void List<T>::copy( const List<T>& Lis )
{
    L = new node( T() );
    L->ant = L->sig = L;
    for( node* q = lis.L->sig; q != lis.L; q = q->sig )
        L->ant = L->ant->sig = new node( q->elto, L->ant, L );
}

template <typename T>
inline List<T>::List() : L( new node( T() ) )
{
    L->ant = L->sig = L;
}

template <typename T>
inline List<T>::List( const List<T>& Lis )
{
    copy( Lis );
}

template <typename T>
List<T>& List<T>::operator =( const List<T>& Lis )
{
    if(this != &lis){
        this->~List();
        copy( Lis );
    }
    return *this;
}

template <typename T>
void List<T>::insert( const T& x, List<T>::position p ) 
{
    p->sig = p->sig->ant = new node( x, p, p->sig );
}

template <typename T>
inline void List<T>::erase( List<T>::position p )
{
	/* p->sig no es endal */
    assert( p->sig != L ); 

    node* q 	= p->sig; 
    p->sig  	= q->sig; 
    p->sig->ant = p;

    delete q;
}

template <typename T>
inline T& List<T>::element( List<T>::position p )
{
    assert( p->sig != L );

    return p->sig->elem;
}

template <typename T>
typename List<T>::position List<T>::search( const T& x ) const
{
    node* q = L;
    bool encontrado = false;

    while( q->sig != L and !encontrado )
	{ 
        if( q->sig->elem == x )
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

template <typename T>
typename List<T>::position List<T>::next( List<T>::position p ) const
{
    assert( p->sig != L );

    return p->sig;
}

template <typename T>
typename List<T>::position List<T>::previous( List<T>::position p ) const
{
	/* Comprobamos que no pida la position previous a la del node cabecera */
    assert(p->sig != L);

    return p->ant;
}

template <typename T>
typename List<T>::position List<T>::first() const
{
    return L;
}

template <typename T>
typename List<T>::position List<T>::end() const
{
    return L->ant;
}

template <typename T>
List<T>::~List()
{
    node* q;

    while( L->sig != L )
	{
        q      = q->sig;
        L->sig = q->sig;

        delete q;
    }
}

#endif
