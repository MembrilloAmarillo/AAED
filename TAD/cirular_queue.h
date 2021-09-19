#ifndef _COLA_CIRC_H_
#define _COLA_CIRC_H_

#include <cassert>
#include <iostream>

template <typename T>
class circular_queue 
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
    explicit circular_queue(size_t size);

    /// Ctor. de copia, requiere ctor. T()
    circular_queue(const circular_queue<T>& c); 

    void pop();

    void push(const T& element);

    /// Asignacion requiere constructor T()
    circular_queue<T>& operator =(const circular_queue<T>& c);

    bool empty() const;

    bool full() const;

    const T& return_start() const;

    ~circular_queue();
};

template <typename T>
circular_queue<T>::circular_queue(size_t size):
    max(size),
    start(0),
    end(0),
    element_keeper(new T[size + 1]) /// +1 para detectar cola full
{}

template <typename T>
circular_queue<T>::circular_queue(const circular_queue<T>& c):
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
circular_queue<T>& circular_queue<T>::operator =(const circular_queue<T>& c)
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
inline bool circular_queue<T>::empty() const
{
    return (start == end ? true : false);
}

template <typename T>
inline bool circular_queue<T>::full() const
{
    return (end == max ? true : false);
}

template <typename T>
inline const T& circular_queue<T>::return_start() const
{
    assert(!empty());
    return element_keeper[start];
}

/// Dado que al hacer pop eliminamos el primer elemento en cola, 
/// este debe ser el start
template <typename T>
inline void circular_queue<T>::pop() 
{
    assert(!empty());
    ++start;
}

/// Cuando hacemos 'push', introducimos un nuevo valor en cola,
/// por tanto, empezamos desde end, asi, actualizamos su valor.
template <typename T>
inline void circular_queue<T>::push (const T& x) 
{
    assert(!full());
    element_keeper[end] = x;
    ++end;
}

template <typename T>
inline circular_queue<T>::~circular_queue()
{
    delete[] element_keeper;
}

#endif
