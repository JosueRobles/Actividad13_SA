#ifndef ALGORITMOS_H
#define ALGORITMOS_H
//tomado de https://github.com/micheldavalos/busqueda_grafos/blob/main/algoritmos.hpp
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

typedef map<string, vector<string> > Grafo;

vector<string> busqueda_profundidad(const Grafo &grafo, const string &origen="A")
{
    vector<string> visitados;
    stack<string> pila;
    vector<string> recorrido;

    visitados.push_back(origen);
    pila.push(origen);

    while (!pila.empty())
    {
        auto const &vertice = pila.top();
        recorrido.push_back(vertice);
        pila.pop();

        auto const &adyacentes = grafo.at(vertice);
        for (size_t i = 0; i < adyacentes.size(); i++) {
            auto const &ady = adyacentes[i];
            if (find(visitados.begin(), visitados.end(), ady) == visitados.end()) {
                visitados.push_back(ady);
                pila.push(ady);
            }
        }
    }

    return recorrido;
}

vector<string> busqueda_amplitud(const Grafo &grafo, const string &origen="A")
{
    vector<string> visitados;
    queue<string> cola;
    vector<string> recorrido;

    visitados.push_back(origen);
    cola.push(origen);

    while (!cola.empty())
    {
        auto const &vertice = cola.front();
        recorrido.push_back(vertice);
        cola.pop();

        auto const &adyacentes = grafo.at(vertice);
        for (size_t i = 0; i < adyacentes.size(); i++) {
            auto const &ady = adyacentes[i];
            if (find(visitados.begin(), visitados.end(), ady) == visitados.end()) {
                visitados.push_back(ady);
                cola.push(ady);
            }
        }
    }

    return recorrido;
}

#endif // ALGORITMOS_H
