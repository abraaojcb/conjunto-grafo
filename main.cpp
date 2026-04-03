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
// TESTES DA CLASSE CONJUNTO (Testes 01 a 10)
// ============================================================

void teste00_construtor_polimorfismo() {
    cabecalho("TESTE 00 — Conjunto: construtor polimorfismo (vetor e string)");

    // Construtor por vetor de inteiros
    int v[] = {10, 20, 30, 20}; // 20 duplicado
    Conjunto A(v, 4);
    verificar("construtor por vetor: pertence(10)", A.pertence(10));
    verificar("construtor por vetor: pertence(30)", A.pertence(30));
    verificar("construtor por vetor: duplicata ignorada (~A==3)", ~A == 3);

    // ConjuntoStr
    ConjuntoStr S;
    S += "banana"; S += "maca"; S += "uva"; S += "maca";
    verificar("ConjuntoStr: pertence(\"banana\")", S << "banana");
    verificar("ConjuntoStr: pertence(\"uva\")", S << "uva");
    verificar("ConjuntoStr: duplicata ignorada (~S==3)", ~S == 3);
    verificar("ConjuntoStr: !pertence(\"laranja\")", !(S << "laranja"));

    // ConjuntoStr por vetor
    const char* palavras[] = {"azul", "verde", "azul"};
    ConjuntoStr C(palavras, 3);
    verificar("ConjuntoStr por vetor: pertence(\"azul\")", C.pertence("azul"));
    verificar("ConjuntoStr por vetor: duplicata ignorada (~C==2)", ~C == 2);

    // Operacoes entre ConjuntoStr
    ConjuntoStr X, Y;
    X += "a"; X += "b"; X += "c";
    Y += "b"; Y += "c"; Y += "d";
    ConjuntoStr U = X | Y;
    verificar("ConjuntoStr uniao tem 4 elementos", ~U == 4);
    ConjuntoStr I = X & Y;
    verificar("ConjuntoStr intersecao tem 2 elementos", ~I == 2);
    ConjuntoStr D = X - Y;
    verificar("ConjuntoStr diferenca contem \"a\"", D.pertence("a"));
    verificar("ConjuntoStr diferenca nao contem \"b\"", !D.pertence("b"));
}

void teste01_adicionar_pertence() {
    cabecalho("TESTE 01 — Conjunto: adicionar e pertence");
    Conjunto A;
    A.adicionar(10); A.adicionar(20);
    verificar("pertence(10) apos adicionar(10)", A.pertence(10));
    verificar("pertence(20) apos adicionar(20)", A.pertence(20));
    verificar("!pertence(99) para elemento nao inserido", !A.pertence(99));
    int tamAntes = A.tamanho();
    A.adicionar(10);
    verificar("adicionar duplicata nao aumenta tamanho", A.tamanho() == tamAntes);
}

void teste02_remover() {
    cabecalho("TESTE 02 — Conjunto: remover");
    Conjunto A;
    A.adicionar(1); A.adicionar(2); A.adicionar(3);
    A.remover(2);
    verificar("!pertence(2) apos remover(2)", !A.pertence(2));
    verificar("pertence(1) e pertence(3) apos remover(2)", A.pertence(1) && A.pertence(3));
    verificar("tamanho == 2 apos remover um elemento", A.tamanho() == 2);
    A.remover(99);
    verificar("tamanho continua 2 apos remover elemento ausente", A.tamanho() == 2);
}

void teste03_cardinalidade() {
    cabecalho("TESTE 03 — Conjunto: operador~ (cardinalidade)");
    Conjunto A;
    verificar("~A == 0 para conjunto vazio", ~A == 0);
    A.adicionar(1); A.adicionar(2); A.adicionar(3);
    verificar("~A == 3 apos inserir 3 elementos", ~A == 3);
    A.remover(1);
    verificar("~A == 2 apos remover um elemento", ~A == 2);
}

void teste04_pertinencia_insercao() {
    cabecalho("TESTE 04 — Conjunto: operador<< (pertinencia) e += (insercao)");
    Conjunto A;
    A += 5; A += 10; A += 15;
    verificar("A << 5 retorna true", A << 5);
    verificar("A << 10 retorna true", A << 10);
    verificar("A << 99 retorna false", !(A << 99));
    A += 5;
    verificar("A += duplicata nao altera tamanho", ~A == 3);
}

void teste05_igualdade() {
    cabecalho("TESTE 05 — Conjunto: operadores == e !=");
    Conjunto A, B, C;
    A += 1; A += 2; A += 3;
    B += 3; B += 1; B += 2;
    C += 1; C += 2;
    verificar("A == B (mesmos elementos, ordem diferente)", A == B);
    verificar("A != C (tamanhos diferentes)", A != C);
    verificar("!(A == C)", !(A == C));
}

void teste06_subconjunto() {
    cabecalho("TESTE 06 — Conjunto: operador<= (subconjunto)");
    Conjunto A, B, C;
    A += 1; A += 2;
    B += 1; B += 2; B += 3;
    C += 4;
    verificar("A <= B (A subconjunto de B)", A <= B);
    verificar("!(B <= A) (B nao e subconjunto de A)", !(B <= A));
    verificar("!(A <= C) (sem elementos em comum)", !(A <= C));
}

void teste07_uniao() {
    cabecalho("TESTE 07 — Conjunto: operador| (uniao)");
    Conjunto A, B;
    A += 1; A += 2; A += 3;
    B += 3; B += 4; B += 5;
    Conjunto U = A | B;
    verificar("uniao contem 1", U.pertence(1));
    verificar("uniao contem 3 (elemento comum)", U.pertence(3));
    verificar("uniao contem 5", U.pertence(5));
    verificar("uniao tem 5 elementos (sem duplicata)", ~U == 5);
}

void teste08_intersecao() {
    cabecalho("TESTE 08 — Conjunto: operador& (intersecao)");
    Conjunto A, B;
    A += 1; A += 2; A += 3;
    B += 2; B += 3; B += 4;
    Conjunto I = A & B;
    verificar("intersecao contem 2", I.pertence(2));
    verificar("intersecao contem 3", I.pertence(3));
    verificar("intersecao nao contem 1", !I.pertence(1));
    verificar("intersecao tem 2 elementos", ~I == 2);
}

void teste09_diferenca() {
    cabecalho("TESTE 09 — Conjunto: operador- (diferenca)");
    Conjunto A, B;
    A += 1; A += 2; A += 3;
    B += 2; B += 3; B += 4;
    Conjunto D = A - B;
    verificar("diferenca contem 1", D.pertence(1));
    verificar("diferenca nao contem 2", !D.pertence(2));
    verificar("diferenca nao contem 3", !D.pertence(3));
    verificar("diferenca tem 1 elemento", ~D == 1);
}

void teste10_copia_atribuicao() {
    cabecalho("TESTE 10 — Conjunto: construtor de copia e operador=");
    Conjunto A;
    A += 10; A += 20; A += 30;
    Conjunto B(A);
    verificar("copia contem os mesmos elementos que o original", B == A);
    B.adicionar(40);
    verificar("modificar copia nao altera o original", !A.pertence(40));
    Conjunto C;
    C = A;
    verificar("atribuicao copia os elementos corretamente", C == A);
    A = A;
    verificar("auto-atribuicao nao corrompe o objeto",
        A.pertence(10) && A.pertence(20) && A.pertence(30));
}

// ============================================================
// TESTES DA CLASSE GRAFO (Testes 11 a 20)
// ============================================================

void teste11_construtor_heranca() {
    cabecalho("TESTE 11 — Grafo: construtor e heranca de Conjunto");
    Grafo g(5);
    verificar("vertice 0 pertence ao grafo (heranca de Conjunto)", g << 0);
    verificar("vertice 4 pertence ao grafo", g << 4);
    verificar("vertice 5 nao pertence (fora do intervalo)", !(g << 5));
    verificar("numero de vertices == 5 (tamanho herdado)", g.tamanho() == 5);
}

void teste12_adicionar_existeAresta() {
    cabecalho("TESTE 12 — Grafo: adicionarAresta e existeAresta");
    Grafo g(4);
    g.adicionarAresta(0, 1);
    g.adicionarAresta(1, 2);
    g.adicionarAresta(2, 3);
    verificar("existeAresta(0,1) apos adicionarAresta(0,1)", g.existeAresta(0, 1));
    verificar("existeAresta(1,0) (nao-dir: aresta vale nos dois sentidos)", g.existeAresta(1, 0));
    verificar("!existeAresta(0,3) (aresta nao adicionada)", !g.existeAresta(0, 3));
    verificar("adicionar aresta duplicata nao altera numArestas",
        (g.adicionarAresta(0, 1), ~g == 3));
}

void teste13_operador_aresta() {
    cabecalho("TESTE 13 — Grafo: operadores += e ^");
    Grafo g(5);
    int e1[2]={0,1}; int e2[2]={1,2}; int e3[2]={2,3}; int e4[2]={3,4};
    g += e1; g += e2; g += e3; g += e4;
    int p1[2]={0,1}; int p2[2]={0,4}; int p3[2]={3,4};
    verificar("g ^ {0,1} retorna true (aresta existe)", g ^ p1);
    verificar("g ^ {3,4} retorna true (aresta existe)", g ^ p3);
    verificar("g ^ {0,4} retorna false (aresta nao existe)", !(g ^ p2));
}

void teste14_num_arestas_grau() {
    cabecalho("TESTE 14 — Grafo: operador~ (arestas) e grau");
    Grafo g(5);
    g.adicionarAresta(0, 1); g.adicionarAresta(0, 2);
    g.adicionarAresta(1, 3); g.adicionarAresta(2, 3);
    g.adicionarAresta(3, 4);
    verificar("~g == 5 (cinco arestas no grafo nao-direcionado)", ~g == 5);
    verificar("grau(0) == 2 (vizinhos: 1 e 2)", g.grau(0) == 2);
    verificar("grau(3) == 3 (vizinhos: 1, 2 e 4)", g.grau(3) == 3);
    verificar("grau(4) == 1 (vizinho: apenas 3)", g.grau(4) == 1);
}

void teste15_vizinhos_direcionado() {
    cabecalho("TESTE 15 — Grafo: operador() e grafo direcionado");
    Grafo gDir(4, true);
    gDir.adicionarAresta(0, 1); gDir.adicionarAresta(0, 2); gDir.adicionarAresta(1, 3);
    const int* viz0 = gDir(0);
    verificar("grafo direcionado: grau de saida de 0 == 2", gDir.grau(0) == 2);
    verificar("grafo direcionado: vizinhos de 0 incluem 1 e 2",
        (viz0[0]==1||viz0[1]==1) && (viz0[0]==2||viz0[1]==2));
    verificar("grafo direcionado: aresta 0->1 existe", gDir.existeAresta(0, 1));
    verificar("grafo direcionado: aresta 1->0 NAO existe", !gDir.existeAresta(1, 0));
}

void teste16_bfs() {
    cabecalho("TESTE 16 — Grafo: bfs (busca em largura)");
    Grafo g(5);
    g.adicionarAresta(0, 1); g.adicionarAresta(0, 2);
    g.adicionarAresta(1, 3); g.adicionarAresta(2, 4);
    verificar("BFS alcanca vertice 3 a partir de 0 (2 saltos via 1)", g.temCaminho(0, 3));
    verificar("BFS alcanca vertice 4 a partir de 0 (2 saltos via 2)", g.temCaminho(0, 4));
    std::cout << "  [VISUAL] Saida esperada: vertices 0,1,2,3,4 em ordem de distancia\n";
    std::cout << "  ";
    g.bfs(0);
}

void teste17_dfs() {
    cabecalho("TESTE 17 — Grafo: dfs (busca em profundidade)");
    Grafo g(5);
    g.adicionarAresta(0, 1); g.adicionarAresta(0, 2);
    g.adicionarAresta(1, 3); g.adicionarAresta(3, 4);
    verificar("DFS alcanca todos os vertices (grafo conexo)", g.componentesConexas() == 1);
    verificar("DFS alcanca vertice 4 a partir de 0", g.temCaminho(0, 4));
    std::cout << "  [VISUAL] Saida esperada: 0 seguido de vizinhos em profundidade\n";
    std::cout << "  ";
    g.dfs(0);
}

void teste18_caminho() {
    cabecalho("TESTE 18 — Grafo: temCaminho e imprimirCaminho");
    Grafo g(5);
    g.adicionarAresta(0,1); g.adicionarAresta(1,2);
    g.adicionarAresta(2,3); g.adicionarAresta(3,4);
    verificar("temCaminho(0,4) == true em cadeia conexa", g.temCaminho(0, 4));
    verificar("temCaminho(4,0) == true (nao-dir: caminho nos dois sentidos)", g.temCaminho(4, 0));
    Grafo gDir(4, true);
    int d1[2]={0,1}; int d2[2]={1,2}; int d3[2]={2,3};
    gDir += d1; gDir += d2; gDir += d3;
    verificar("temCaminho(0,3) == true em grafo dir (0->1->2->3)", gDir.temCaminho(0, 3));
    verificar("temCaminho(3,0) == false em grafo dir (sem caminho de volta)", !gDir.temCaminho(3, 0));
    std::cout << "  [VISUAL] Caminho esperado de 0 ate 4: 0 -> 1 -> 2 -> 3 -> 4\n";
    std::cout << "  ";
    g.imprimirCaminho(0, 4);
    std::cout << "  [VISUAL] Deve exibir: Caminho inexistente\n";
    std::cout << "  ";
    gDir.imprimirCaminho(3, 0);
}

void teste19_circuito() {
    cabecalho("TESTE 19 — Grafo: temCircuito");
    Grafo dag(4, true);
    int s1[2]={0,1}; int s2[2]={1,2}; int s3[2]={2,3};
    dag += s1; dag += s2; dag += s3;
    verificar("temCircuito == false em DAG (0->1->2->3)", !dag.temCircuito());

    Grafo comCiclo(4, true);
    int c1[2]={0,1}; int c2[2]={1,2}; int c3[2]={2,0};
    comCiclo += c1; comCiclo += c2; comCiclo += c3;
    verificar("temCircuito == true em grafo com ciclo (0->1->2->0)", comCiclo.temCircuito());

    Grafo triangulo(3);
    int t1[2]={0,1}; int t2[2]={1,2}; int t3[2]={2,0};
    triangulo += t1; triangulo += t2; triangulo += t3;
    verificar("temCircuito == true em triangulo nao-direcionado", triangulo.temCircuito());

    Grafo arvore(4);
    int a1[2]={0,1}; int a2[2]={0,2}; int a3[2]={0,3};
    arvore += a1; arvore += a2; arvore += a3;
    verificar("temCircuito == false em arvore (estrela sem ciclo)", !arvore.temCircuito());
}

void teste20_componentes_operacoes() {
    cabecalho("TESTE 20 — Grafo: componentesConexas e operacoes | & -");
    Grafo gComp(7);
    int c1[2]={0,1}; int c2[2]={1,2}; int c3[2]={3,4};
    gComp += c1; gComp += c2; gComp += c3;
    verificar("componentesConexas == 4 ({0,1,2},{3,4},{5},{6})", gComp.componentesConexas() == 4);

    Grafo gConexo(4);
    int k1[2]={0,1}; int k2[2]={1,2}; int k3[2]={2,3}; int k4[2]={0,3};
    gConexo += k1; gConexo += k2; gConexo += k3; gConexo += k4;
    verificar("componentesConexas == 1 em grafo totalmente conexo", gConexo.componentesConexas() == 1);

    Grafo g1(4), g2(4);
    int a1[2]={0,1}; int a2[2]={1,2};
    int a3[2]={1,2}; int a4[2]={2,3};
    g1 += a1; g1 += a2;
    g2 += a3; g2 += a4;

    Grafo gUniao = g1 | g2;
    verificar("uniao G1|G2 contem aresta 0-1 (exclusiva de G1)", gUniao.existeAresta(0, 1));
    verificar("uniao G1|G2 contem aresta 2-3 (exclusiva de G2)", gUniao.existeAresta(2, 3));
    verificar("uniao G1|G2 contem aresta 1-2 (comum a ambos, sem duplicata)",
        gUniao.existeAresta(1, 2) && ~gUniao == 3);

    Grafo gInter = g1 & g2;
    verificar("intersecao G1&G2 contem apenas aresta 1-2 (comum)",
        gInter.existeAresta(1, 2) && ~gInter == 1);
    verificar("intersecao G1&G2 nao contem aresta 0-1 (exclusiva de G1)", !gInter.existeAresta(0, 1));

    Grafo gDif = g1 - g2;
    verificar("diferenca G1-G2 contem aresta 0-1 (exclusiva de G1)", gDif.existeAresta(0, 1));
    verificar("diferenca G1-G2 nao contem aresta 1-2 (esta em G2)", !gDif.existeAresta(1, 2));
}

int main() {
    std::cout << "\n";
    std::cout << "############################################################\n";
    std::cout << "  BATERIA DE TESTES — Biblioteca Conjuntos e Grafos\n";
    std::cout << "############################################################\n";

    teste00_construtor_polimorfismo();
    teste01_adicionar_pertence();
    teste02_remover();
    teste03_cardinalidade();
    teste04_pertinencia_insercao();
    teste05_igualdade();
    teste06_subconjunto();
    teste07_uniao();
    teste08_intersecao();
    teste09_diferenca();
    teste10_copia_atribuicao();
    teste11_construtor_heranca();
    teste12_adicionar_existeAresta();
    teste13_operador_aresta();
    teste14_num_arestas_grau();
    teste15_vizinhos_direcionado();
    teste16_bfs();
    teste17_dfs();
    teste18_caminho();
    teste19_circuito();
    teste20_componentes_operacoes();

    resumo();

    return (testesFalhou == 0) ? 0 : 1;
}
