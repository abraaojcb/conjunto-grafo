#include "grafo.hpp"

void Grafo::alocarAdj() {
    adj    = new int*[V];
    adjTam = new int[V];
    adjCap = new int[V];
    for (int i = 0; i < V; i++) {
        adjTam[i] = 0;
        adjCap[i] = 4;
        adj[i]    = new int[4];
    }
}

void Grafo::liberarAdj() {
    for (int i = 0; i < V; i++) delete[] adj[i];
    delete[] adj;
    delete[] adjTam;
    delete[] adjCap;
}

void Grafo::crescerAdj(int v) {
    adjCap[v] *= 2;
    int* novo = new int[adjCap[v]];
    for (int i = 0; i < adjTam[v]; i++) novo[i] = adj[v][i];
    delete[] adj[v];
    adj[v] = novo;
}

Grafo::Grafo(int numVertices, bool dir)
    : Conjunto(numVertices), V(numVertices), direcionado(dir) {
    alocarAdj();
    for (int i = 0; i < V; i++) adicionar(i);
}

Grafo::Grafo(const Grafo& outro)
    : Conjunto(outro), V(outro.V), direcionado(outro.direcionado) {
    alocarAdj();
    for (int v = 0; v < V; v++)
        for (int i = 0; i < outro.adjTam[v]; i++) {
            if (adjTam[v] == adjCap[v]) crescerAdj(v);
            adj[v][adjTam[v]++] = outro.adj[v][i];
        }
}

Grafo::~Grafo() {
    liberarAdj();
}

Grafo& Grafo::operator=(const Grafo& outro) {
    if (this == &outro) return *this;
    Conjunto::operator=(outro);
    liberarAdj();
    V          = outro.V;
    direcionado = outro.direcionado;
    alocarAdj();
    for (int v = 0; v < V; v++)
        for (int i = 0; i < outro.adjTam[v]; i++) {
            if (adjTam[v] == adjCap[v]) crescerAdj(v);
            adj[v][adjTam[v]++] = outro.adj[v][i];
        }
    return *this;
}

bool Grafo::existeAresta(int u, int v) const {
    if (!pertence(u)) return false;
    for (int i = 0; i < adjTam[u]; i++)
        if (adj[u][i] == v) return true;
    return false;
}

int Grafo::grau(int v) const {
    return adjTam[v];
}

void Grafo::adicionarAresta(int u, int v) {
    if (existeAresta(u, v)) return;
    if (adjTam[u] == adjCap[u]) crescerAdj(u);
    adj[u][adjTam[u]++] = v;
    if (!direcionado) {
        if (adjTam[v] == adjCap[v]) crescerAdj(v);
        adj[v][adjTam[v]++] = u;
    }
}

// --- auxiliares DFS ---

void Grafo::dfsVisitar(int v, bool* vis) const {
    vis[v] = true;
    std::cout << v << " ";
    for (int i = 0; i < adjTam[v]; i++)
        if (!vis[adj[v][i]]) dfsVisitar(adj[v][i], vis);
}

bool Grafo::dfsAlcanca(int v, int destino, bool* vis) const {
    if (v == destino) return true;
    vis[v] = true;
    for (int i = 0; i < adjTam[v]; i++)
        if (!vis[adj[v][i]] && dfsAlcanca(adj[v][i], destino, vis))
            return true;
    return false;
}

bool Grafo::dfsCircuito(int v, int* cor) const {
    cor[v] = 1;
    for (int i = 0; i < adjTam[v]; i++) {
        int u = adj[v][i];
        if (cor[u] == 1) return true;
        if (cor[u] == 0 && dfsCircuito(u, cor)) return true;
    }
    cor[v] = 2;
    return false;
}

void Grafo::dfsMarcar(int v, bool* vis) const {
    vis[v] = true;
    for (int i = 0; i < adjTam[v]; i++)
        if (!vis[adj[v][i]]) dfsMarcar(adj[v][i], vis);
}

// --- algoritmos ---

void Grafo::bfs(int origem) const {
    bool* vis  = new bool[V];
    int*  dist = new int[V];
    int*  fila = new int[V];
    for (int i = 0; i < V; i++) { vis[i] = false; dist[i] = -1; }

    int ini = 0, fim = 0;
    vis[origem] = true; dist[origem] = 0;
    fila[fim++] = origem;

    while (ini < fim) {
        int u = fila[ini++];
        std::cout << "Vertice " << u << " | distancia " << dist[u] << "\n";
        for (int i = 0; i < adjTam[u]; i++) {
            int v = adj[u][i];
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = dist[u] + 1;
                fila[fim++] = v;
            }
        }
    }
    delete[] vis; delete[] dist; delete[] fila;
}

void Grafo::dfs(int origem) const {
    bool* vis = new bool[V];
    for (int i = 0; i < V; i++) vis[i] = false;
    std::cout << "DFS a partir de " << origem << ": ";
    dfsVisitar(origem, vis);
    std::cout << "\n";
    delete[] vis;
}

bool Grafo::temCaminho(int origem, int destino) const {
    bool* vis = new bool[V];
    for (int i = 0; i < V; i++) vis[i] = false;
    bool r = dfsAlcanca(origem, destino, vis);
    delete[] vis;
    return r;
}

void Grafo::imprimirCaminho(int origem, int destino) const {
    bool* vis      = new bool[V];
    int*  anterior = new int[V];
    int*  fila     = new int[V];
    for (int i = 0; i < V; i++) { vis[i] = false; anterior[i] = -1; }

    int ini = 0, fim = 0;
    vis[origem] = true;
    fila[fim++] = origem;

    while (ini < fim) {
        int u = fila[ini++];
        if (u == destino) break;
        for (int i = 0; i < adjTam[u]; i++) {
            int v = adj[u][i];
            if (!vis[v]) {
                vis[v] = true; anterior[v] = u;
                fila[fim++] = v;
            }
        }
    }

    if (anterior[destino] == -1 && origem != destino) {
        std::cout << "Caminho inexistente\n";
    } else {
        int* caminho = new int[V];
        int cTam = 0, atual = destino;
        while (atual != -1) { caminho[cTam++] = atual; atual = anterior[atual]; }
        std::cout << "Caminho de " << origem << " ate " << destino << ": ";
        for (int i = cTam - 1; i >= 0; i--) {
            std::cout << caminho[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] caminho;
    }
    delete[] vis; delete[] anterior; delete[] fila;
}

bool Grafo::temCircuito() const {
    int* cor = new int[V];
    for (int i = 0; i < V; i++) cor[i] = 0;
    for (int v = 0; v < V; v++)
        if (cor[v] == 0 && dfsCircuito(v, cor)) {
            delete[] cor; return true;
        }
    delete[] cor; return false;
}

int Grafo::componentesConexas() const {
    bool* vis = new bool[V];
    for (int i = 0; i < V; i++) vis[i] = false;
    int count = 0;
    for (int v = 0; v < V; v++)
        if (!vis[v]) { dfsMarcar(v, vis); count++; }
    delete[] vis;
    return count;
}

std::ostream& Grafo::imprimir(std::ostream& os) const {
    os << "Grafo (" << (direcionado ? "direcionado" : "nao-direcionado") << ") | V=" << V << "\n";
    for (int i = 0; i < V; i++) {
        os << i << ": [ ";
        for (int j = 0; j < adjTam[i]; j++) os << adj[i][j] << " ";
        os << "]\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Grafo& g) {
    return g.imprimir(os);
}