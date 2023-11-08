#ifndef ARISTA_H
#define ARISTA_H
#include <iostream>
#include <vector>

class Arista
{
private:
    std::vector<Nodo> __par;
public:
    Arista(Nodo n1, Nodo n2) {
        __par.push_back(n1);
        __par.push_back(n2);
    }
    bool dirigido() {
        return false;
    }
    bool ponderada() {
        return false;
    }
    std::vector<Nodo> get_par() {
        return __par;
    }
    std::string toString() {
        return "(Nodo: " + std::to_string(get_par()[0]) + " ?---- Arista ----? (Nodo: " + std::to_string(get_par()[1]) + ")";
    }
};

class AristaNoDirigida : public Arista {
public:
    AristaNoDirigida(Nodo n1, Nodo n2) : Arista(n1, n2) {}
    bool dirigido() {
        return false;
    }
    Nodo get_nodo1() {
        return get_par()[0];
    }
    Nodo get_nodo2() {
        return get_par()[1];
    }
    std::string toString() {
        return "((Nodo: " + std::to_string(get_nodo1()) + ")) <----|Arista|----> ((Nodo: " + std::to_string(get_nodo2()) + "))";
    }
    bool operator==(const AristaNoDirigida& o) {
        if (get_par()[0] == o.get_par()[0] && get_par()[1] == o.get_par()[1]) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Ponderada {
private:
    int __peso;
public:
    Ponderada(int peso) {
        __peso = peso;
    }
    int getPeso() {
        return __peso;
    }
};

class AristaNoDirigidaPonderada : public AristaNoDirigida, public Ponderada {
public:
    AristaNoDirigidaPonderada(Nodo* n1, Nodo* n2, int peso) : AristaNoDirigida(n1, n2), Ponderada(peso) {}

    bool ponderada() {
        return true;
    }

    std::string toString() {
        return "((Nodo: " + getNodo1()->toString() + ")) <----|Arista: " + std::to_string(getPeso()) + "|----> ((Nodo: " + getNodo2()->toString() + "))";
    }
};



#endif // ARISTA_H
