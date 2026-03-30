#include "conjunto.hpp"

void Conjunto::crescer() {
    cap *= 2;
    int* novo = new int[cap];
    for (int i = 0; i < tam; i++) novo[i] = elementos[i];
    delete[] elementos;
    elementos = novo;
}

Conjunto::Conjunto(int capInicial)
    : tam(0), cap(capInicial), elementos(new int[capInicial]) {}

Conjunto::~Conjunto() {
    delete[] elementos;
}

Conjunto::Conjunto(const Conjunto& outro)
    : tam(outro.tam), cap(outro.cap), elementos(new int[outro.cap]) {
    for (int i = 0; i < tam; i++) elementos[i] = outro.elementos[i];
}

Conjunto& Conjunto::operator=(const Conjunto& outro) {
    if (this == &outro) return *this;
    delete[] elementos;
    tam = outro.tam;
    cap = outro.cap;
    elementos = new int[cap];
    for (int i = 0; i < tam; i++) elementos[i] = outro.elementos[i];
    return *this;
}

bool Conjunto::pertence(int x) const {
    for (int i = 0; i < tam; i++)
        if (elementos[i] == x) return true;
    return false;
}

void Conjunto::adicionar(int x) {
    if (pertence(x)) return;
    if (tam == cap) crescer();
    elementos[tam++] = x;
}

void Conjunto::remover(int x) {
    for (int i = 0; i < tam; i++) {
        if (elementos[i] == x) {
            elementos[i] = elementos[tam - 1];
            tam--;
            return;
        }
    }
}

int Conjunto::tamanho() const { return tam; }
int Conjunto::operator~() const { return tam; }
bool Conjunto::operator<<(int x) const { return pertence(x); }

Conjunto& Conjunto::operator+=(int x) {
    adicionar(x);
    return *this;
}

bool Conjunto::operator==(const Conjunto& outro) const {
    if (tam != outro.tam) return false;
    for (int i = 0; i < tam; i++)
        if (!outro.pertence(elementos[i])) return false;
    return true;
}

bool Conjunto::operator!=(const Conjunto& outro) const {
    return !(*this == outro);
}

bool Conjunto::operator<=(const Conjunto& outro) const {
    for (int i = 0; i < tam; i++)
        if (!outro.pertence(elementos[i])) return false;
    return true;
}

Conjunto Conjunto::operator|(const Conjunto& outro) const {
    Conjunto r;
    for (int i = 0; i < tam; i++) r.adicionar(elementos[i]);
    for (int i = 0; i < outro.tam; i++) r.adicionar(outro.elementos[i]);
    return r;
}

Conjunto Conjunto::operator&(const Conjunto& outro) const {
    Conjunto r;
    for (int i = 0; i < tam; i++)
        if (outro.pertence(elementos[i])) r.adicionar(elementos[i]);
    return r;
}

Conjunto Conjunto::operator-(const Conjunto& outro) const {
    Conjunto r;
    for (int i = 0; i < tam; i++)
        if (!outro.pertence(elementos[i])) r.adicionar(elementos[i]);
    return r;
}

std::ostream& Conjunto::imprimir(std::ostream& os) const {
    os << "{ ";
    for (int i = 0; i < tam; i++) {
        os << elementos[i];
        if (i < tam - 1) os << ", ";
    }
    os << " }";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Conjunto& c) {
    return c.imprimir(os);
}