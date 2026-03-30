#ifndef CONJUNTO_HPP
#define CONJUNTO_HPP
#include <iostream>
#include <stdexcept>

class Conjunto {
protected:
    int* elementos;
    int tam;
    int cap;
    void crescer();
public:
    Conjunto(int capInicial = 16);
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

#endif