#ifndef _BIQUEUE_H_
#define _BIQUEUE_H_

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class biqueue
{
private:
    struct node
    {
        T element;
        node *next;
        node (T elem, node *p = nullptr):
            element(elem),
            next(p)
        {}
    };

    node *start, *end;
    void copia (const biqueue<T>& bc);
public:
    /// Constructor de la clase
    biqueue();

    /// Constructor de la copia
    biqueue(const biqueue<T>& bc);

    /// Sobrecarga del operador asignacion
    biqueue<T>& operator =(const biqueue<T>& bc);

    /// Devuelve true si se encuentra vacia
    bool vacia() const;

    /// Devuelve el valor del start
    const T& return_start() const;

    /// Devuelve el valor del end
    const T& return_end() const;

    /// Operacion pop en el start
    void pop_start();

    /// Operacion pop en el end
    void pop_end();

    /// Operacion push desde el principio
    void push_start(const T& element);

    /// Operacion push desde el end
    void push_end(const T& element);

    /// Destructor de la clase
    ~biqueue();
};

template <typename T>
biqueue<T>::biqueue():
    start(nullptr),
    end(nullptr)
{}

template <typename T>
void biqueue<T>::copia(const biqueue<T>& bc)
{
    /// Iniciamos los nodes de la nueva clase
    start = end = new node(bc.start->element);
    node *p = bc.start->next;
    /// Mientras que exista un element anterior al que es en start,
    /// end debe actualizarse, por tanto, end->next apunta al nextuiente element
    /// y end = end->next, asi tenemos el nuevo element en end.
    /// Recordemos que end almacena el ultimo element introducido, por tanto,
    /// por cada start->next, quiere decir, que hay un element posteriormente 
    /// introducido.
    while(p)
    {
        end->next = new node(p->element);
        end = end->next;
        p = p->next;
    }
}

template <typename T>
biqueue<T>::biqueue(const biqueue<T>& bc)
{
    cout << "Llamado al constructor de copia" << endl;  
}

template <typename T>
biqueue<T>& biqueue<T>::operator =(const biqueue<T>& bc)
{
    /// Evitamos la autoanextnacion
    if (this != &bc)
    {
        /// Destruimos la clase actual
        this->~biqueue();
        /// Llamamos a la funcion copia, pasamos 
        /// como parametro la clase a copiar
        copia(bc);
    }
    return *this;
}

template <typename T>
inline bool biqueue<T>::vacia() const
{
    return (start == nullptr);
}

template <typename T>
void biqueue<T>::push_start(const T& element)
{
    node *p = new node(element);
    if (vacia())
        start = end = p;
    else
    {
        start->next = p;
        start = start->next;
    }
    start->next = end;
}

template <typename T>
void biqueue<T>::pop_start()
{
    assert(!vacia());
    node *p = start;
    start = p->next;

    delete p;
}

template <typename T>
void biqueue<T>::push_end(const T& element)
{
    node *p = new node(element);
    if (vacia())
        start = end = p;
    else
    {
        end->next = p;
        end = end->next;
    }
}

template <typename T>
void biqueue<T>::pop_end()
{
    node *p = start;
    while (p->next != end) {
        p = p->next;
    }
    delete end;
    end = p;
}

template <typename T>
const T& biqueue<T>::return_start() const
{
    return start->element;
}

template <typename T>
const T& biqueue<T>::return_end() const
{
    return end->element;
}

template <typename T>
biqueue<T>::~biqueue()
{
    node *p;
    while(start)
    {
        p = start->next;
        delete start;
        start = p;
    }
    end = nullptr;
}

#endif
