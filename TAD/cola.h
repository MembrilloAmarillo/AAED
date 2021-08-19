#ifndef _COLA_H_
#define _COLA_H_

#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;

/// Implementacion de Cola dinamica

template <class T>
class Cola 
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

	/// inicio_Cola: inicio de la Cola, donde se encuentra el primer elemento
	/// fin_Cola : fin de la Cola, donde se encuentra el ultimo elemento introducido
	node *inicio_Cola, *fin_Cola;
	
	/// Copia de la pila actual en una nueva clase Cola
	void copy (const Cola<T>& c);
public:
	/// Crea una Cola vacia
	Cola();
	
	/// Devuelve true si la Cola esta vacia
	bool vacia () const;
	
	/// Precondicion: La Cola no esta vacia
	/// Postcondicion: Devuelve el elemento del fin_Cola(output) de la Cola
	const T& frente() const;
	
	/// Precondicion: La Cola no esta vacia
	/// Postcondicion: Elimina el elemento del fin_Cola de la Cola y el siguiente
	/// se convierete en el nuevo incio.
	void pop ();

	/// Postcondicion: Inserta el elemento x al inicio_Cola(input) de la Cola
	void push (const T& x);

	/// Constructor de copia
	Cola (const Cola <T>& c);

	/// Sobrecarga del operador = para la asignacion de Colas
	Cola<T>& operator =(const Cola<T>& c);

	/// Destructor de la clase Cola
	~Cola();
};

template <typename T>
inline Cola<T>::Cola():
	inicio_Cola(nullptr),
	fin_Cola(nullptr)
{ }

template <typename T>
inline Cola<T>::Cola(const Cola<T>& )
{ }

template <typename T>
inline void Cola<T>::copy(const Cola<T>& c)
{
	/// Construimos los nodos de la nueva clase
	fin_Cola = inicio_Cola = new node (c.inicio_Cola->element);	
	node *p = c.inicio_Cola->next;
	while (p) {
		fin_Cola->next = new node(p->element);
		fin_Cola = fin_Cola->next;
		p = p->next;
	}
}

template <typename T>
inline Cola<T>& Cola<T>::operator =(const Cola<T>& c)
{
	/// evitamos la autoasignacion
	if (this != &c)
	{	
		/// vaciamos la Cola actual
		this->~Cola();
		/// Llamamos a la funcion copia
		copy(c);
	}
	return *this;
}

template <typename T>
inline bool Cola<T>::vacia() const 
{
	return (inicio_Cola == nullptr);
}

template <typename T>
inline const T& Cola<T>::frente() const
{
	assert(!vacia());
	return inicio_Cola->element;
}

template <typename T>
inline void Cola<T>::pop()
{
	assert(!vacia());
	node *p = inicio_Cola;
	inicio_Cola = p->next;

	if (!inicio_Cola) 
		fin_Cola = nullptr;
	delete p;
}

template <typename T>
inline void Cola<T>::push (const T& x)
{
	node *p = new node(x);
	/// Si la Cola esta vacia, la entrada es igual a la salida
	if (inicio_Cola == nullptr) {
		/// En esta asignacion, fin_Cola e inicio Cola comparten el mismo puntero
		fin_Cola = inicio_Cola = p;
	} else {
		/// Introducimos nuevo elemento en la Cola
		/// Actualizamos el valor de fin_Cola
		fin_Cola->next = p;
		fin_Cola = fin_Cola->next;
	}
}

template <typename T>
inline Cola<T>::~Cola()
{
	node *p;
	/// Mientras que exista una entrada, seguimos borrando elementos
	while (inicio_Cola)
	{
		p = inicio_Cola->next; /// Apuntamos al elemento detras del elemento del fin_Cola
		delete inicio_Cola; 	 /// Ahora podemos borrar la entrada
		inicio_Cola = p;	 /// La nueva entrada se convierte en el siguiente
	}
	fin_Cola = nullptr;
}

#endif
