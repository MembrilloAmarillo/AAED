#ifndef _LISTA_DOBLE_HPP_
#define _LISTA_DOBLE_HPP_

#include <cassert>

template <typename T>
class Lista
{
    struct nodo;
public:
    typedef nodo* posicion;
    Lista(); //constructor
    Lista(const Lista<T>& lis); //constructor de copia

    Lista<T>& operator =(const Lista<T>& lis);

    void insertar( const T&, posicion );
    void eliminar( posicion );

    T& elemento(posicion p);
    /* Funciones no modificadoras/observadoras */
    const T& elemento ( posicion ) const;
    posicion buscar   ( const T& ) const;
    posicion siguiente( posicion ) const;
    posicion anterior ( posicion ) const;
    posicion primera  (          ) const;
    posicion fin 	  ( 		 ) const;

   ~Lista();
 private:
    struct nodo{
        T elem;
        nodo *ant, *sig;
        nodo( const T& e, nodo* a = nullptr, nodo* s = nullptr ) :
            elem( e ), ant( a ), sig( s ) {}
    };
    nodo* L; 
    void copiar( const Lista<T>& Lis );
};


template <typename T>
void Lista<T>::copiar( const Lista<T>& Lis )
{
    L = new nodo( T() );
    L->ant = L->sig = L;
    for( nodo* q = lis.L->sig; q != lis.L; q = q->sig )
        L->ant = L->ant->sig = new nodo( q->elto, L->ant, L );
}

template <typename T>
inline Lista<T>::Lista() : L( new nodo( T() ) )
{
    L->ant = L->sig = L;
}

template <typename T>
inline Lista<T>::Lista( const Lista<T>& Lis )
{
    copiar( Lis );
}

template <typename T>
Lista<T>& Lista<T>::operator =( const Lista<T>& Lis )
{
    if(this != &lis){
        this->~Lista();
        copiar( Lis );
    }
    return *this;
}

template <typename T>
void Lista<T>::insertar( const T& x, Lista<T>::posicion p ) 
{
    p->sig = p->sig->ant = new nodo( x, p, p->sig );
}

template <typename T>
inline void Lista<T>::eliminar( Lista<T>::posicion p )
{
	/* p->sig no es final */
    assert( p->sig != L ); 

    nodo* q 	= p->sig; 
    p->sig  	= q->sig; 
    p->sig->ant = p;

    delete q;
}

template <typename T>
inline T& Lista<T>::elemento( Lista<T>::posicion p )
{
    assert( p->sig != L );

    return p->sig->elem;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::buscar( const T& x ) const
{
    nodo* q = L;
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
typename Lista<T>::posicion Lista<T>::siguiente( Lista<T>::posicion p ) const
{
    assert( p->sig != L );

    return p->sig;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::anterior( Lista<T>::posicion p ) const
{
	/* Comprobamos que no pida la posicion anterior a la del nodo cabecera */
    assert(p->sig != L);

    return p->ant;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::primera() const
{
    return L;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::fin() const
{
    return L->ant;
}

template <typename T>
Lista<T>::~Lista()
{
    nodo* q;

    while( L->sig != L )
	{
        q      = q->sig;
        L->sig = q->sig;

        delete q;
    }
}

#endif
