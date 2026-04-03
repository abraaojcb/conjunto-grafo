#include <iostream>
#include "conjunto.hpp"
#include "grafo.hpp"

// ============================================================
// Infraestrutura de testes
// ============================================================
static int testesOK     = 0;
static int testesFalhou = 0;

void cabecalho(const char* titulo) {
    std::cout << "\n============================================================\n";
    std::cout << " " << titulo << "\n";
    std::cout << "============================================================\n";
}

void verificar(const char* descricao, bool resultado) {
    if (resultado) {
        std::cout << " [OK] " << descricao << "\n";
        testesOK++;
    } else {
        std::cout << " [FALHOU] " << descricao << "\n";
        testesFalhou++;
    }
}

void resumo() {
    std::cout << "\n============================================================\n";
    std::cout << " RESULTADO FINAL\n";
    std::cout << "============================================================\n";
    std::cout << " Total  : " << (testesOK + testesFalhou) << "\n";
    std::cout << " OK     : " << testesOK << "\n";
    std::cout << " Falhou : " << testesFalhou << "\n";
    std::cout << "============================================================\n";
}

// ============================================================
// TESTE 01 — Polimorfismo do construtor
// ============================================================
void teste01_polimorfismo() {
    cabecalho("TESTE 01 — Conjunto: polimorfismo (int, vetor, string)");

    // Construtor padrao com inteiros
    Conjunto A;
    A += 1; A += 2; A += 3;
    verificar("Conjunto(int): pertence(1)", A.pertence(1));
    verificar("Conjunto(int): ~A == 3", ~A == 3);

    // Construtor por vetor de inteiros
    int v[] = {10, 20, 30, 20};
    Conjunto B(v, 4);
    verificar("Conjunto(vetor): pertence(10)", B.pertence(10));
    verificar("Conjunto(vetor): duplicata ignorada (~B==3)", ~B == 3);

    // ConjuntoStr com strings
    ConjuntoStr S;
    S += "banana"; S += "maca"; S += "uva"; S += "maca";
    verificar("ConjuntoStr: pertence(\"banana\")", S.pertence("banana"));
    verificar("ConjuntoStr: duplicata ignorada (~S==3)", ~S == 3);

    // ConjuntoStr por vetor de strings
    const char* palavras[] = {"azul", "verde", "azul"};
    ConjuntoStr C(palavras, 3);
    verificar("ConjuntoStr(vetor): pertence(\"azul\")", C.pertence("azul"));
    verificar("ConjuntoStr(vetor): duplicata ignorada (~C==2)", ~C == 2);
}

// ============================================================
// TESTE 02 — Operacoes entre Conjuntos
// ============================================================
void teste02_operacoes_conjunto() {
    cabecalho("TESTE 02 — Conjunto: uniao, intersecao e diferenca");

    Conjunto A, B;
    A += 1; A += 2; A += 3;
    B += 2; B += 3; B += 4;

    Conjunto U = A | B;
    verificar("uniao tem 4 elementos", ~U == 4);
    verificar("uniao contem 1 (exclusivo A)", U.pertence(1));
    verificar("uniao contem 4 (exclusivo B)", U.pertence(4));

    Conjunto I = A & B;
    verificar("intersecao tem 2 elementos", ~I == 2);
    verificar("intersecao contem 2 (comum)", I.pertence(2));
    verificar("intersecao nao contem 1", !I.pertence(1));

    Conjunto D = A - B;
    verificar("diferenca contem 1 (so em A)", D.pertence(1));
    verificar("diferenca nao contem 2 (esta em B)", !D.pertence(2));
}

// ============================================================
// TESTE 03 — Propriedades e copia
// ============================================================
void teste03_propriedades_conjunto() {
    cabecalho("TESTE 03 — Conjunto: ==, !=, <=, copia");

    Conjunto A, B, C;
    A += 1; A += 2; A += 3;
    B += 3; B += 1; B += 2;
    C += 1; C += 2;

    verificar("A == B (mesmos elementos, ordem diferente)", A == B);
    verificar("A != C", A != C);
    verificar("C <= A (subconjunto)", C <= A);
    verificar("!(A <= C)", !(A <= C));

    Conjunto Bcopia(A);
    verificar("copia == original", Bcopia == A);
    Bcopia += 99;
    verificar("modificar copia nao altera original", !A.pertence(99));
}

// ============================================================
// TESTE 04 — Grafo: construtor e heranca
// ============================================================
void teste04_grafo_construtor() {
    cabecalho("TESTE 04 — Grafo: construtor e heranca de Conjunto");

    Grafo g(5);
    verificar("vertice 0 pertence ao grafo", g << 0);
    verificar("vertice 4 pertence ao grafo", g << 4);
    verificar("vertice 5 nao pertence", !(g << 5));
    verificar("tamanho herdado == 5", g.tamanho() == 5);
}

// ============================================================
// TESTE 05 — Grafo: arestas e operadores
// ============================================================
void teste05_grafo_arestas() {
    cabecalho("TESTE 05 — Grafo: arestas, operadores += ^ ~");

    Grafo g(5);
    int e1[2]={0,1}; int e2[2]={1,2};
    int e3[2]={2,3}; int e4[2]={3,4};
    g += e1; g += e2; g += e3; g += e4;

    int p1[2]={0,1}; int p2[2]={0,4};
    verificar("g ^ {0,1} aresta existe", g ^ p1);
    verificar("g ^ {0,4} aresta nao existe", !(g ^ p2));
    verificar("~g == 4 (num arestas)", ~g == 4);
    verificar("grau(1) == 2", g.grau(1) == 2);
    verificar("existeAresta(1,0) nao-dir", g.existeAresta(1, 0));
    verificar("duplicata nao altera numArestas", (g.adicionarAresta(0,1), ~g == 4));
}

// ============================================================
// TESTE 06 — Grafo: BFS e DFS
// ============================================================
void teste06_bfs_dfs() {
    cabecalho("TESTE 06 — Grafo: BFS e DFS");

    Grafo g(5);
    g.adicionarAresta(0,1); g.adicionarAresta(0,2);
    g.adicionarAresta(1,3); g.adicionarAresta(2,4);

    verificar("BFS alcanca vertice 3 a partir de 0", g.temCaminho(0,3));
    verificar("BFS alcanca vertice 4 a partir de 0", g.temCaminho(0,4));
    verificar("DFS: grafo e conexo (1 componente)", g.componentesConexas() == 1);

    std::cout << "  [VISUAL] BFS:\n  ";
    g.bfs(0);
    std::cout << "  [VISUAL] DFS:\n  ";
    g.dfs(0);
}

// ============================================================
// TESTE 07 — Grafo: caminho
// ============================================================
void teste07_caminho() {
    cabecalho("TESTE 07 — Grafo: temCaminho e imprimirCaminho");

    Grafo g(5);
    g.adicionarAresta(0,1); g.adicionarAresta(1,2);
    g.adicionarAresta(2,3); g.adicionarAresta(3,4);

    verificar("temCaminho(0,4) == true", g.temCaminho(0,4));
    verificar("temCaminho(4,0) == true (nao-dir)", g.temCaminho(4,0));

    Grafo gDir(4, true);
    int d1[2]={0,1}; int d2[2]={1,2}; int d3[2]={2,3};
    gDir += d1; gDir += d2; gDir += d3;
    verificar("temCaminho(0,3) dir == true", gDir.temCaminho(0,3));
    verificar("temCaminho(3,0) dir == false", !gDir.temCaminho(3,0));

    std::cout << "  [VISUAL] ";
    g.imprimirCaminho(0,4);
    std::cout << "  [VISUAL] ";
    gDir.imprimirCaminho(3,0);
}

// ============================================================
// TESTE 08 — Grafo: circuito
// ============================================================
void teste08_circuito() {
    cabecalho("TESTE 08 — Grafo: temCircuito");

    Grafo dag(4, true);
    int s1[2]={0,1}; int s2[2]={1,2}; int s3[2]={2,3};
    dag += s1; dag += s2; dag += s3;
    verificar("temCircuito == false em DAG", !dag.temCircuito());

    Grafo comCiclo(4, true);
    int c1[2]={0,1}; int c2[2]={1,2}; int c3[2]={2,0};
    comCiclo += c1; comCiclo += c2; comCiclo += c3;
    verificar("temCircuito == true (0->1->2->0)", comCiclo.temCircuito());

    Grafo arvore(4);
    int a1[2]={0,1}; int a2[2]={0,2}; int a3[2]={0,3};
    arvore += a1; arvore += a2; arvore += a3;
    verificar("temCircuito == false em arvore", !arvore.temCircuito());
}

// ============================================================
// TESTE 09 — Grafo: componentes conexas
// ============================================================
void teste09_componentes() {
    cabecalho("TESTE 09 — Grafo: componentesConexas");

    Grafo g(7);
    int c1[2]={0,1}; int c2[2]={1,2}; int c3[2]={3,4};
    g += c1; g += c2; g += c3;
    verificar("4 componentes: {0,1,2},{3,4},{5},{6}", g.componentesConexas() == 4);

    Grafo gConexo(4);
    int k1[2]={0,1}; int k2[2]={1,2}; int k3[2]={2,3};
    gConexo += k1; gConexo += k2; gConexo += k3;
    verificar("1 componente em grafo conexo", gConexo.componentesConexas() == 1);
}

// ============================================================
// TESTE 10 — Grafo: operacoes entre grafos
// ============================================================
void teste10_operacoes_grafo() {
    cabecalho("TESTE 10 — Grafo: uniao |, intersecao &, diferenca -");

    Grafo g1(4), g2(4);
    int a1[2]={0,1}; int a2[2]={1,2};
    int a3[2]={1,2}; int a4[2]={2,3};
    g1 += a1; g1 += a2;
    g2 += a3; g2 += a4;

    Grafo gU = g1 | g2;
    verificar("uniao contem 0-1 (exclusivo g1)", gU.existeAresta(0,1));
    verificar("uniao contem 2-3 (exclusivo g2)", gU.existeAresta(2,3));
    verificar("uniao sem duplicata (~gU==3)", ~gU == 3);

    Grafo gI = g1 & g2;
    verificar("intersecao contem 1-2 (comum)", gI.existeAresta(1,2));
    verificar("intersecao nao contem 0-1", !gI.existeAresta(0,1));

    Grafo gD = g1 - g2;
    verificar("diferenca contem 0-1 (so em g1)", gD.existeAresta(0,1));
    verificar("diferenca nao contem 1-2 (esta em g2)", !gD.existeAresta(1,2));
}

// ============================================================
// MAIN
// ============================================================
int main() {
    std::cout << "\n############################################################\n";
    std::cout << "  BATERIA DE TESTES — Biblioteca Conjuntos e Grafos\n";
    std::cout << "############################################################\n";

    teste01_polimorfismo();
    teste02_operacoes_conjunto();
    teste03_propriedades_conjunto();
    teste04_grafo_construtor();
    teste05_grafo_arestas();
    teste06_bfs_dfs();
    teste07_caminho();
    teste08_circuito();
    teste09_componentes();
    teste10_operacoes_grafo();

    resumo();

    return (testesFalhou == 0) ? 0 : 1;
}
