#ifndef _PILA_H_
#define _PILA_H_

#include <cassert>

template <typename T>
class Stack
{
    private:
        /* Struct encargado de almacenar la informacion de la Stack */
        struct cell
        {
            /* data */
            T element;
            struct cell *next;
            /* Constructor de la celda, guarda el elemento introducido y genera la siguiente celda como nullptr */
            cell (const T& new_element, cell *p = nullptr): element(new_element), next(p) {}
        };

        cell *top_cell;
        /* Coge la Stack actual y la copia en uno nuevo */
        void copy(const Stack<T>& p);
    public:
        // Constructor de Stack
        Stack();
        // Devuelve V si esta empty, F en caso contrario
        bool empty() const;
        // Introduce nuevo elemento en la Stack
        void push(const T& element);
        // Sobrecarga del operador =
        Stack<T>& operator = (const Stack<T>& p);
        // Saca el ultimo elemento introducido
        void pop();
        // Devuelve el elemento que se encuentra en el top de la Stack
        const T& top() const;
        // Destructor de Stack
        ~Stack();
};

template <typename T>
inline Stack<T>::Stack(): top_cell(nullptr) {}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& p) {
    // Evitamos autoasignacion
    if(this != *p){
        // Emptymos la Stack en la que nos encontramos
        this->~Stack();
        copy(p);
    }
    return *this;
}

template <typename T>
void Stack<T>::copy(const Stack<T>& p) {
    // Copia la celda que se encuentra en el top
    top_cell = new cell(p.top(), nullptr);
    // Recorrera la Stack destino
    cell *destination = top_cell;
    // Recorrera la Stack origen
    cell *source = p.top_cell->next;
    // Mientras que exista una siguiente celda, continuamos
    while(source->next) {
        destination->next = new cell(source->element, nullptr);
        destination = destination->next;
        source = source->next;
    }
}

template <typename T>
inline bool Stack<T>::empty() const {
    // Si hay celda, devuelve falso
    return (!top_cell); // top_cell == true, returns false, else true
}

template <typename T>
inline const T& Stack<T>::top() const {
    // Nos aseguramos de que la Stack no este empty
    assert(!empty()); // assert(empty() == false)
    // Devolvemos el elemento del top
    return top_cell->element;
}

template <typename T>
inline void Stack<T>::push(const T& element) {
    top_cell = new cell(element, top_cell);
}

template <typename T>
inline void Stack<T>::pop() {
    assert(!empty());
    cell *temp = top_cell;
    top_cell = top_cell->next;
    delete temp;
}

template <typename T>
Stack<T>::~Stack() {
    cell *p;
    while (top_cell) {
        p = top_cell->next;
        delete top_cell;
        top_cell = p;
    }
}

#endif
