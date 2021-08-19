#ifndef _PILA_H_
#define _PILA_H_

#include <cassert>

template <typename T>
class Pila
{
    private:
        /* Struct encargado de almacenar la informacion de la Pila */
        struct cell
        {
            /* data */
            T element;
            struct cell *next;
            /* Constructor de la celda, guarda el elemento introducido y genera la siguiente celda como nullptr */
            cell (const T& new_element, cell *p = nullptr): element(new_element), next(p) {}
        };

        cell *top_cell;
        /* Coge la Pila actual y la copia en uno nuevo */
        void copy(const Pila<T>& p);
    public:
        // Constructor de Pila
        Pila();
        // Devuelve V si esta vacia, F en caso contrario
        bool vacia() const;
        // Introduce nuevo elemento en la Pila
        void push(const T& element);
        // Sobrecarga del operador =
        Pila<T>& operator = (const Pila<T>& p);
        // Saca el ultimo elemento introducido
        void pop();
        // Devuelve el elemento que se encuentra en el tope de la Pila
        const T& tope() const;
        // Destructor de Pila
        ~Pila();
};

template <typename T>
inline Pila<T>::Pila(): top_cell(nullptr) {}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila<T>& p) {
    // Evitamos autoasignacion
    if(this != *p){
        // Vaciamos la Pila en la que nos encontramos
        this->~Pila();
        copy(p);
    }
    return *this;
}

template <typename T>
void Pila<T>::copy(const Pila<T>& p) {
    // Copia la celda que se encuentra en el tope
    top_cell = new cell(p.tope(), nullptr);
    // Recorrera la Pila destino
    cell *destination = top_cell;
    // Recorrera la Pila origen
    cell *source = p.top_cell->next;
    // Mientras que exista una siguiente celda, continuamos
    while(source->next) {
        destination->next = new cell(source->element, nullptr);
        destination = destination->next;
        source = source->next;
    }
}

template <typename T>
inline bool Pila<T>::vacia() const {
    // Si hay celda, devuelve falso
    return (!top_cell); // top_cell == true, returns false, else true
}

template <typename T>
inline const T& Pila<T>::tope() const {
    // Nos aseguramos de que la Pila no este vacia
    assert(!vacia()); // assert(vacia() == false)
    // Devolvemos el elemento del tope
    return top_cell->element;
}

template <typename T>
inline void Pila<T>::push(const T& element) {
    top_cell = new cell(element, top_cell);
}

template <typename T>
inline void Pila<T>::pop() {
    assert(!vacia());
    cell *temp = top_cell;
    top_cell = top_cell->next;
    delete temp;
}

template <typename T>
Pila<T>::~Pila() {
    cell *p;
    while (top_cell) {
        p = top_cell->next;
        delete top_cell;
        top_cell = p;
    }
}

#endif