#ifndef _BICOLA_H_
#define _BICOLA_H_

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class bicola
{
private:
    struct nodo
    {
        T elemento;
        nodo *sig;
        nodo (T elem, nodo *p = nullptr):
            elemento(elem),
            sig(p)
        {}
    };

    nodo *inicio, *fin;
    void copia (const bicola<T>& bc);
public:
    /// Constructor de la clase
    bicola();

    /// Constructor de la copia
    bicola(const bicola<T>& bc);

    /// Sobrecarga del operador asignacion
    bicola<T>& operator =(const bicola<T>& bc);

    /// Devuelve true si se encuentra vacia
    bool vacia() const;

    /// Devuelve el valor del inicio
    const T& return_inicio() const;

    /// Devuelve el valor del final
    const T& return_final() const;

    /// Operacion pop en el inicio
    void pop_inicio();

    /// Operacion pop en el final
    void pop_final();

    /// Operacion push desde el principio
    void push_inicio(const T& elemento);

    /// Operacion push desde el final
    void push_final(const T& elemento);

    /// Destructor de la clase
    ~bicola();
};

template <typename T>
bicola<T>::bicola():
    inicio(nullptr),
    fin(nullptr)
{}

template <typename T>
void bicola<T>::copia(const bicola<T>& bc)
{
    /// Iniciamos los nodos de la nueva clase
    inicio = fin = new nodo(bc.inicio->elemento);
    nodo *p = bc.inicio->sig;
    /// Mientras que exista un elemento anterior al que es en inicio,
    /// fin debe actualizarse, por tanto, fin->sig apunta al siguiente elemento
    /// y fin = fin->sig, asi tenemos el nuevo elemento en fin.
    /// Recordemos que fin almacena el ultimo elemento introducido, por tanto,
    /// por cada inicio->sig, quiere decir, que hay un elemento posteriormente 
    /// introducido.
    while(p)
    {
        fin->sig = new nodo(p->elemento);
        fin = fin->sig;
        p = p->sig;
    }
}

template <typename T>
bicola<T>::bicola(const bicola<T>& bc)
{
    cout << "Llamado al constructor de copia" << endl;  
}

template <typename T>
bicola<T>& bicola<T>::operator =(const bicola<T>& bc)
{
    /// Evitamos la autoasignacion
    if (this != &bc)
    {
        /// Destruimos la clase actual
        this->~bicola();
        /// Llamamos a la funcion copia, pasamos 
        /// como parametro la clase a copiar
        copia(bc);
    }
    return *this;
}

template <typename T>
inline bool bicola<T>::vacia() const
{
    return (inicio == nullptr);
}

template <typename T>
void bicola<T>::push_inicio(const T& elemento)
{
    nodo *p = new nodo(elemento);
    if (vacia())
        inicio = fin = p;
    else
    {
        inicio->sig = p;
        inicio = inicio->sig;
    }
    inicio->sig = fin;
}

template <typename T>
void bicola<T>::pop_inicio()
{
    assert(!vacia());
    nodo *p = inicio;
    inicio = p->sig;

    delete p;
}

template <typename T>
void bicola<T>::push_final(const T& elemento)
{
    nodo *p = new nodo(elemento);
    if (vacia())
        inicio = fin = p;
    else
    {
        fin->sig = p;
        fin = fin->sig;
    }
}

template <typename T>
void bicola<T>::pop_final()
{
    nodo *p = inicio;
    while (p->sig != fin) {
        p = p->sig;
    }
    delete fin;
    fin = p;
}

template <typename T>
const T& bicola<T>::return_inicio() const
{
    return inicio->elemento;
}

template <typename T>
const T& bicola<T>::return_final() const
{
    return fin->elemento;
}

template <typename T>
bicola<T>::~bicola()
{
    nodo *p;
    while(inicio)
    {
        p = inicio->sig;
        delete inicio;
        inicio = p;
    }
    fin = nullptr;
}

#endif