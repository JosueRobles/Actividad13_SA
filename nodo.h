#ifndef NODO_H
#define NODO_H
#include <iostream>
#include <string>

class Nodo
{
private:
    int dato;
public:
    Nodo(int dato) : dato(dato) {}

    int getDato() const {
        return dato;
    }

    void setDato(int dato) {
        this->dato = dato;
    }

    std::string toString() const {
        return std::to_string(dato);
    }

    bool operator==(const Nodo& o) const {
        return dato == o.getDato();
    }

    size_t hash() const {
        return std::hash<int>{}(dato);
    }
};

/*int main() {
    Nodo nodo(5);
    std::cout << nodo.toString() << std::endl;
    return 0;
}*/

#endif // NODO_H
