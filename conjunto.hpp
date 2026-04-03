#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP
#include <iostream>
#include <stdexcept>
#include <string.h>

// ============================================================
// Classe Conjunto — elementos inteiros
// ============================================================
class Conjunto {
protected:
    int* elementos;
    int tam;
    int cap;
    void crescer();
public:
    // Construtor padrão
    Conjunto(int capInicial = 16);
    // Construtor por vetor de inteiros
    Conjunto(const int* vetor, int tamanhoVetor);
    ~Conjunto();
    Conjunto(const Conjunto& outro);
    Conjunto& operator=(const Conjunto& outro);
    bool pertence(int x) const;
    void adicionar(int x);
    void remover(int x);
    int tamanho() const;
    int operator~() const;
    bool operator<<(int x) const;
    Conjunto& operator+=(int x);
    bool operator==(const Conjunto& outro) const;
    bool operator!=(const Conjunto& outro) const;
    bool operator<=(const Conjunto& outro) const;
    Conjunto operator|(const Conjunto& outro) const;
    Conjunto operator&(const Conjunto& outro) const;
    Conjunto operator-(const Conjunto& outro) const;
    std::ostream& imprimir(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Conjunto& c);

// ============================================================
// Classe ConjuntoStr — elementos strings (char*)
// ============================================================
class ConjuntoStr {
private:
    char** elementos;
    int tam;
    int cap;
    void crescer();
    char* copiarStr(const char* s) const;
public:
    // Construtor padrão
    ConjuntoStr(int capInicial = 16);
    // Construtor por vetor de strings
    ConjuntoStr(const char** vetor, int tamanhoVetor);
    ~ConjuntoStr();
    ConjuntoStr(const ConjuntoStr& outro);
    ConjuntoStr& operator=(const ConjuntoStr& outro);
    bool pertence(const char* s) const;
    void adicionar(const char* s);
    void remover(const char* s);
    int tamanho() const;
    int operator~() const;
    bool operator<<(const char* s) const;
    ConjuntoStr& operator+=(const char* s);
    bool operator==(const ConjuntoStr& outro) const;
    bool operator!=(const ConjuntoStr& outro) const;
    bool operator<=(const ConjuntoStr& outro) const;
    ConjuntoStr operator|(const ConjuntoStr& outro) const;
    ConjuntoStr operator&(const ConjuntoStr& outro) const;
    ConjuntoStr operator-(const ConjuntoStr& outro) const;
    std::ostream& imprimir(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const ConjuntoStr& c);

#endif
