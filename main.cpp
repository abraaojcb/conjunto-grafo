#include <iostream>
#include "conjunto.hpp"
#include "grafo.hpp"

int main() {
    // --- Conjunto ---
    std::cout << "=== Conjunto ===\n";
    Conjunto A, B;
    A += 1; A += 2; A += 3; A += 4;
    B += 3; B += 4; B += 5; B += 6;

    std::cout << "A = " << A << "\n";
    std::cout << "B = " << B << "\n";
    std::cout << "3 em A? " << (A << 3 ? "sim" : "nao") << "\n";
    std::cout << "|A| = " << ~A << "\n";
    std::cout << "A | B = " << (A | B) << "\n";
    std::cout << "A & B = " << (A & B) << "\n";
    std::cout << "A - B = " << (A - B) << "\n";
    std::cout << "A == B? " << (A == B ? "sim" : "nao") << "\n";
    std::cout << "A != B? " << (A != B ? "sim" : "nao") << "\n";
    A.remover(4);
    std::cout << "A sem 4: " << A << "\n";

    // --- Grafo ---
    std::cout << "\n=== Grafo ===\n";
    Grafo g(5);
    g.adicionarAresta(0, 1);
    g.adicionarAresta(0, 2);
    g.adicionarAresta(1, 3);
    g.adicionarAresta(2, 3);
    g.adicionarAresta(3, 4);
    std::cout << g;

    std::cout << "\n=== BFS ===\n";
    g.bfs(0);

    std::cout << "\n=== DFS ===\n";
    g.dfs(0);

    std::cout << "\n=== Caminhos ===\n";
    std::cout << "Caminho 0->4? " << (g.temCaminho(0, 4) ? "sim" : "nao") << "\n";
    g.imprimirCaminho(0, 4);

    Grafo gDir(4, true);
    gDir.adicionarAresta(0, 1);
    gDir.adicionarAresta(1, 2);
    gDir.adicionarAresta(2, 3);
    std::cout << "Caminho 3->0 (dir)? " << (gDir.temCaminho(3, 0) ? "sim" : "nao") << "\n";
    gDir.imprimirCaminho(3, 0);

    std::cout << "\n=== Circuito ===\n";
    Grafo semCiclo(4, true);
    semCiclo.adicionarAresta(0, 1);
    semCiclo.adicionarAresta(1, 2);
    semCiclo.adicionarAresta(2, 3);
    std::cout << "Tem circuito (DAG)? " << (semCiclo.temCircuito() ? "sim" : "nao") << "\n";

    Grafo comCiclo(4, true);
    comCiclo.adicionarAresta(0, 1);
    comCiclo.adicionarAresta(1, 2);
    comCiclo.adicionarAresta(2, 0);
    std::cout << "Tem circuito (0->1->2->0)? " << (comCiclo.temCircuito() ? "sim" : "nao") << "\n";

    std::cout << "\n=== Componentes Conexas ===\n";
    Grafo gComp(7);
    gComp.adicionarAresta(0, 1);
    gComp.adicionarAresta(1, 2);
    gComp.adicionarAresta(3, 4);
    std::cout << "Componentes: " << gComp.componentesConexas() << "\n";

    return 0;
}