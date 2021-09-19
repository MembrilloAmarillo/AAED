#ifndef _COLA_H_
#define _COLA_H_

#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;

/// Implementacion de Queue dinamica

template <class T>
class Queue 
{
private:
	struct node 
	{
		/// data
		T element;
		struct node *next;
		/// Constructor del nodo
		node (const T& new_element, node *p = nullptr):
			element(new_element),
			next(p)
		{}
	};	

	/// start: inicio de la Queue, donde se encuentra el primer elemento
	/// end : fin de la Queue, donde se encuentra el ultimo elemento introducido
	node *start, *end;
	
	/// Copia de la pila actual en una nueva clase Queue
	void copy (const Queue<T>& c);
public:
	/// Crea una Queue empty
	Queue();
	
	/// Devuelve true si la Queue esta empty
	bool empty () const;
	
	/// Precondicion: La Queue no esta empty
	/// Postcondicion: Devuelve el elemento del end(output) de la Queue
	const T& top() const;
	
	/// Precondicion: La Queue no esta empty
	/// Postcondicion: Elimina el elemento del end de la Queue y el siguiente
	/// se convierete en el nuevo incio.
	void pop ();

	/// Postcondicion: Inserta el elemento x al start(input) de la Queue
	void push (const T& x);

	/// Constructor de copia
	Queue (const Queue <T>& c);
  
	/// Sobrecarga del operador = para la asignacion de Queues
	Queue<T>& operator =(const Queue<T>& c);

	/// Destructor de la clase Queue
	~Queue();
};

template <typename T>
inline Queue<T>::Queue():
	start(nullptr),
	end(nullptr)
{ }

template <typename T>
inline Queue<T>::Queue(const Queue<T>& )
{ }

template <typename T>
inline void Queue<T>::copy(const Queue<T>& c)
{
	/// Construimos los nodos de la nueva clase
	end = start = new node (c.start->element);	
	node *p = c.start->next;
	while (p) {
		end->next = new node(p->element);
		end = end->next;
		p = p->next;
	}
}

template <typename T>
inline Queue<T>& Queue<T>::operator =(const Queue<T>& c)
{
	/// evitamos la autoasignacion
	if (this != &c)
	{	
		/// emptymos la Queue actual
		this->~Queue();
		/// Llamamos a la funcion copia
		copy(c);
	}
	return *this;
}

template <typename T>
inline bool Queue<T>::empty() const 
{
	return (start == nullptr);
}

template <typename T>
inline const T& Queue<T>::top() const
{
	assert(!empty());
	return start->element;
}

template <typename T>
inline void Queue<T>::pop()
{
	assert(!empty());
	node *p = start;
	start = p->next;

	if (!start) 
		end = nullptr;
	delete p;
}

template <typename T>
inline void Queue<T>::push (const T& x)
{
	node *p = new node(x);
	/// Si la Queue esta empty, la entrada es igual a la salida
	if (start == nullptr) {
		/// En esta asignacion, end e inicio Queue comparten el mismo puntero
		end = start = p;
	} else {
		/// Introducimos nuevo elemento en la Queue
		/// Actualizamos el valor de end
		end->next = p;
		end = end->next;
	}
}

template <typename T>
inline Queue<T>::~Queue()
{
	node *p;
	/// Mientras que exista una entrada, seguimos borrando elementos
	while (start)
	{
		p = start->next; /// Apuntamos al elemento detras del elemento del end
		delete start; 	 /// Ahora podemos borrar la entrada
		start = p;	 /// La nueva entrada se convierte en el siguiente
	}
	end = nullptr;
}

#endif
