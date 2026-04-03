#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "conjunto.hpp"

class Grafo : public Conjunto {
private:
    int** adj;
    int* adjTam;
    int* adjCap;
    int numArestas;
    int V;

    void alocarAdj();
    void liberarAdj();
    void crescerAdj(int v);

    // auxiliares internos
    void dfsVisitar(int v, bool* vis) const;
    bool dfsAlcanca(int v, int destino, bool* vis) const;
    bool dfsCircuito(int v, int* cor) const;
    bool dfsCircuitoAux(int v, int pai, int* cor) const;
    void dfsMarcar(int v, bool* vis) const;

public:
    Grafo(int numVertices, bool dir = false);
    Grafo(const Grafo& outro);
    ~Grafo();
    Grafo& operator=(const Grafo& outro);

    void adicionarAresta(int u, int v);
    bool existeAresta(int u, int v) const;
    int grau(int v) const;

    // operadores
    Grafo& operator+=(int* aresta);   // g += int[2]
    bool   operator^(int* par) const; // g ^ int[2]
    const int* operator()(int v) const; // g(v) -> vizinhos
    int    operator~() const;         // ~g -> num arestas
    Grafo  operator|(const Grafo& outro) const;
    Grafo  operator&(const Grafo& outro) const;
    Grafo  operator-(const Grafo& outro) const;

    // busca
    void bfs(int origem) const;
    void dfs(int origem) const;

    // caminho e circuito
    bool temCaminho(int origem, int destino) const;
    void imprimirCaminho(int origem, int destino) const;
    bool temCircuito() const;
    int componentesConexas() const;

    std::ostream& imprimir(std::ostream& os) const;

private:
    bool direcionado;
};

std::ostream& operator<<(std::ostream& os, const Grafo& g);

#endif
