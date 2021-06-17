#ifndef _PILA_H_
#define _PILA_H_

#include <cassert>

template <typename T>
class pila
{
    private:
        /* Struct encargado de almacenar la informacion de la pila */
        struct cell
        {
            /* data */
            T element;
            struct cell *next;
            /* Constructor de la celda, guarda el elemento introducido y genera la siguiente celda como nullptr */
            cell (const T& new_element, cell *p = nullptr): element(new_element), next(p) {}
        };

        cell *top_cell;
        /* Coge la pila actual y la copia en uno nuevo */
        void copy(const pila<T>& p);
    public:
        // Constructor de pila
        pila();
        // Devuelve V si esta vacia, F en caso contrario
        bool vacia() const;
        // Introduce nuevo elemento en la pila
        void push(const T& element);
        // Sobrecarga del operador =
        pila<T>& operator = (const pila<T>& p);
        // Saca el ultimo elemento introducido
        void pop();
        // Devuelve el elemento que se encuentra en el tope de la pila
        const T& show_top() const;
        // Destructor de pila
        ~pila();
};

template <typename T>
inline pila<T>::pila(): top_cell(nullptr) {}

template <typename T>
pila<T>& pila<T>::operator = (const pila<T>& p) {
    // Evitamos autoasignacion
    if(this != *p){
        // Vaciamos la pila en la que nos encontramos
        this->~pila();
        copy(p);
    }
    return *this;
}

template <typename T>
void pila<T>::copy(const pila<T>& p) {
    // Copia la celda que se encuentra en el tope
    top_cell = new cell(p.show_top(), nullptr);
    // Recorrera la pila destino
    cell *destination = top_cell;
    // Recorrera la pila origen
    cell *source = p.top_cell->next;
    // Mientras que exista una siguiente celda, continuamos
    while(source->next) {
        destination->next = new cell(source->element, nullptr);
        destination = destination->next;
        source = source->next;
    }
}

template <typename T>
inline bool pila<T>::vacia() const {
    // Si hay celda, devuelve falso
    return (!top_cell); // top_cell == true, returns false, else true
}

template <typename T>
inline const T& pila<T>::show_top() const {
    // Nos aseguramos de que la pila no este vacia
    assert(!vacia()); // assert(vacia() == false)
    // Devolvemos el elemento del tope
    return top_cell->element;
}

template <typename T>
inline void pila<T>::push(const T& element) {
    top_cell = new cell(element, top_cell);
}

template <typename T>
inline void pila<T>::pop() {
    assert(!vacia());
    cell *temp = top_cell;
    top_cell = top_cell->next;
    delete temp;
}

template <typename T>
pila<T>::~pila() {
    cell *p;
    while (top_cell) {
        p = top_cell->next;
        delete top_cell;
        top_cell = p;
    }
}

#endif