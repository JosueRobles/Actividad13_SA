#ifndef GRAFO_H
#define GRAFO_H
#include <deque>
#include <queue>
#include <unordered_map>
#include "arista.h"
#include "nodo.h"

class Grafo {
private:
    std::deque<Arista> __aristas;
    std::unordered_map<Nodo, std::deque<std::pair<Nodo, int>>> __ady;

public:
    void agregar_arista(Arista arista) {
        if (std::find(__aristas.begin(), __aristas.end(), arista) == __aristas.end()) {
            __aristas.push_back(arista);
        }
    }

    std::string to_string() {
        std::string result;
        for (const auto& arista : __aristas) {
            result += arista.to_string() + " ";
        }
        return result;
    }

    void eliminar_arista(Arista arista) {
        __aristas.erase(std::remove(__aristas.begin(), __aristas.end(), arista), __aristas.end());
    }

    std::unordered_map<Nodo, std::deque<std::pair<Nodo, int>>> get_lista_ady() {
        for (const auto& arista : __aristas) {
            if (arista.dirigido()) {
                continue;
            } else {
                Nodo n1 = arista.get_nodo1();
                Nodo n2 = arista.get_nodo2();
                agregar_ady(n1, n2, arista.get_peso());
                agregar_ady(n2, n1, arista.get_peso());
            }
        }
        return __ady;
    }

    void print_ady() {
        __ady.clear();
        get_lista_ady();
        for (const auto& pair : __ady) {
            std::cout << pair.first.get_dato() << " ---> ";
            for (const auto& value : pair.second) {
                Nodo nodo = value.first;
                int peso = value.second;
                std::cout << "[" << nodo << ", " << peso << "], ";
            }
            std::cout << std::endl;
        }
    }

    void agregar_ady(Nodo n1, Nodo n2, int peso) {
        if (__ady.find(n1) != __ady.end()) {
            __ady[n1].push_back(std::make_pair(n2, peso));
        } else {
            __ady[n1] = std::vector<std::pair<Nodo, int>>{{n2, peso}};
        }
    }
    std::vector<Nodo> recorrido_profundidad(Nodo inicio) {
        std::vector<Nodo> visitados;
        std::deque<Nodo> pila;
        std::vector<Nodo> recorrido;
        std::unordered_map<Nodo, std::vector<std::pair<Nodo, int>>> grafo = get_lista_ady();
        if (grafo.find(inicio) == grafo.end()) {
            return recorrido;
        }
        pila.push_back(inicio);
        visitados.push_back(inicio);
        while (!pila.empty()) {
            Nodo nodo = pila.back();
            pila.pop_back();
            recorrido.push_back(nodo);
            for (auto ady : grafo[nodo]) {
                if (std::find(visitados.begin(), visitados.end(), ady.first) == visitados.end()) {
                    pila.push_back(ady.first);
                    visitados.push_back(ady.first);
                }
            }
        }
        return recorrido;
    }
};
#endif // GRAFO_H
