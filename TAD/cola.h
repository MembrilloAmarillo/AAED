#ifndef _COLA_H_
#define _COLA_H_

#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;

/// Implementacion de cola dinamica

template <class T>
class cola 
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

	/// inicio_cola: inicio de la cola, donde se encuentra el primer elemento
	/// fin_cola : fin de la cola, donde se encuentra el ultimo elemento introducido
	node *inicio_cola, *fin_cola;
	
	/// Copia de la pila actual en una nueva clase cola
	void copy (const cola<T>& c);
public:
	/// Crea una cola vacia
	cola();
	
	/// Devuelve true si la cola esta vacia
	bool vacia () const;
	
	/// Precondicion: La cola no esta vacia
	/// Postcondicion: Devuelve el elemento del fin_cola(output) de la cola
	const T& return_output() const;
	
	/// Precondicion: La cola no esta vacia
	/// Postcondicion: Elimina el elemento del fin_cola de la cola y el siguiente
	/// se convierete en el nuevo incio.
	void pop ();

	/// Postcondicion: Inserta el elemento x al inicio_cola(input) de la cola
	void push (const T& x);

	/// Constructor de copia
	cola (const cola <T>& c);

	/// Sobrecarga del operador = para la asignacion de colas
	cola<T>& operator =(const cola<T>& c);

	/// Destructor de la clase cola
	~cola();
};

template <typename T>
inline cola<T>::cola():
	fin_cola(nullptr),
	inicio_cola(nullptr)
{
	std::cout << "Constructor called\n";
}

template <typename T>
inline cola<T>::cola(const cola<T>& bc)
{
	cout << "Llamado a constructor de copia" << endl;
}

template <typename T>
inline void cola<T>::copy(const cola<T>& c)
{
	/// Construimos los nodos de la nueva clase
	fin_cola = inicio_cola = new node (c.inicio_cola->element);	
	node *p = c.inicio_cola->next;
	while (p) {
		fin_cola->next = new node(p->element);
		fin_cola = fin_cola->next;
		p = p->next;
	}
}

template <typename T>
inline cola<T>& cola<T>::operator =(const cola<T>& c)
{
	/// evitamos la autoasignacion
	if (this != &c)
	{	
		/// vaciamos la cola actual
		this->~cola();
		/// Llamamos a la funcion copia
		copy(c);
	}
	return *this;
}

template <typename T>
inline bool cola<T>::vacia() const 
{
	return (inicio_cola == nullptr);
}

template <typename T>
inline const T& cola<T>::return_output() const
{
	assert(!vacia());
	return inicio_cola->element;
}

template <typename T>
inline void cola<T>::pop()
{
	assert(!vacia());
	node *p = inicio_cola;
	inicio_cola = p->next;

	if (!inicio_cola) 
		fin_cola = nullptr;
	delete p;
}

template <typename T>
inline void cola<T>::push (const T& x)
{
	node *p = new node(x);
	/// Si la cola esta vacia, la entrada es igual a la salida
	if (inicio_cola == nullptr) {
		/// En esta asignacion, fin_cola e inicio cola comparten el mismo puntero
		fin_cola = inicio_cola = p;
	} else {
		/// Introducimos nuevo elemento en la cola
		/// Actualizamos el valor de fin_cola
		fin_cola->next = p;
		fin_cola = fin_cola->next;
	}
}

template <typename T>
inline cola<T>::~cola()
{
	node *p;
	/// Mientras que exista una entrada, seguimos borrando elementos
	while (inicio_cola)
	{
		p = inicio_cola->next; /// Apuntamos al elemento detras del elemento del fin_cola
		delete inicio_cola; 	 /// Ahora podemos borrar la entrada
		inicio_cola = p;	 /// La nueva entrada se convierte en el siguiente
	}
	fin_cola = nullptr;
	std::cout << "Destructor called\n";

}

#endif
