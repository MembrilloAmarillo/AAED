#ifndef _COLA_CIRC_H_
#define _COLA_CIRC_H_

#include <cassert>
#include <iostream>

template <typename T>
class cola_circ 
{
private:
    /// Vector que almacena los elementos de la cola circular
    T *element_keeper;

    /// Tamano maximo de la cola circular
    size_t max;
    
    /// Posiciones de principio y fin
    /// Start: Elemento que se encuentra en la cabeza
    /// End: Ultimo elemento introducido
    size_t start, end;
public:
    /// Constructor, requiere constructor T()
    explicit cola_circ(size_t size);

    /// Ctor. de copia, requiere ctor. T()
    cola_circ(const cola_circ<T>& c); 

    void pop();

    void push(const T& element);

    /// Asignacion requiere constructor T()
    cola_circ<T>& operator =(const cola_circ<T>& c);

    bool vacia() const;

    bool llena() const;

    const T& return_start() const;

    ~cola_circ();
};

template <typename T>
cola_circ<T>::cola_circ(size_t size):
    max(size),
    start(0),
    end(0),
    element_keeper(new T[size + 1]) /// +1 para detectar cola llena
{}

template <typename T>
cola_circ<T>::cola_circ(const cola_circ<T>& c):
    element_keeper(new T[c.max]),
    max(c.max),
    start(c.start),
    end(c.end)
{
    /// Copia de los elementos en la nueva cola
    for (size_t i = start; i < end; i++)
    {
        element_keeper[i] = c.element_keeper[i];
    }
}

template <typename T>
cola_circ<T>& cola_circ<T>::operator =(const cola_circ<T>& c)
{
    /// Evitamos la autoasignacion
    if (this != &c)
    {
        if (max != c.max)
        {
            delete[] element_keeper;
            max = c.max;
            element_keeper = new T[max];
        }
        start = c.start;
        end = c.end;
        /// Copiarmos los elementos
        for (size_t i = start; i < end; i++)
            element_keeper[i] = c.element_keeper[i];
    }
    return *this;
}

template <typename T>
inline bool cola_circ<T>::vacia() const
{
    return (start == end ? true : false);
}

template <typename T>
inline bool cola_circ<T>::llena() const
{
    return (end == max ? true : false);
}

template <typename T>
inline const T& cola_circ<T>::return_start() const
{
    assert(!vacia());
    return element_keeper[start];
}

/// Dado que al hacer pop eliminamos el primer elemento en cola, 
/// este debe ser el start
template <typename T>
inline void cola_circ<T>::pop() 
{
    assert(!vacia());
    ++start;
}

/// Cuando hacemos 'push', introducimos un nuevo valor en cola,
/// por tanto, empezamos desde end, asi, actualizamos su valor.
template <typename T>
inline void cola_circ<T>::push (const T& x) 
{
    assert(!llena());
    element_keeper[end] = x;
    ++end;
}

template <typename T>
inline cola_circ<T>::~cola_circ()
{
    delete[] element_keeper;
}

#endif
