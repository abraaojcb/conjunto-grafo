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

// ============================================================
// Construtor por vetor de inteiros
// ============================================================
Conjunto::Conjunto(const int* vetor, int tamanhoVetor)
    : tam(0), cap(tamanhoVetor < 16 ? 16 : tamanhoVetor),
      elementos(new int[tamanhoVetor < 16 ? 16 : tamanhoVetor]) {
    for (int i = 0; i < tamanhoVetor; i++) adicionar(vetor[i]);
}

// ============================================================
// ConjuntoStr — implementação
// ============================================================
char* ConjuntoStr::copiarStr(const char* s) const {
    int len = strlen(s);
    char* copia = new char[len + 1];
    strcpy(copia, s);
    return copia;
}

void ConjuntoStr::crescer() {
    cap *= 2;
    char** novo = new char*[cap];
    for (int i = 0; i < tam; i++) novo[i] = elementos[i];
    delete[] elementos;
    elementos = novo;
}

ConjuntoStr::ConjuntoStr(int capInicial)
    : tam(0), cap(capInicial), elementos(new char*[capInicial]) {}

ConjuntoStr::ConjuntoStr(const char** vetor, int tamanhoVetor)
    : tam(0), cap(tamanhoVetor < 16 ? 16 : tamanhoVetor),
      elementos(new char*[tamanhoVetor < 16 ? 16 : tamanhoVetor]) {
    for (int i = 0; i < tamanhoVetor; i++) adicionar(vetor[i]);
}

ConjuntoStr::~ConjuntoStr() {
    for (int i = 0; i < tam; i++) delete[] elementos[i];
    delete[] elementos;
}

ConjuntoStr::ConjuntoStr(const ConjuntoStr& outro)
    : tam(outro.tam), cap(outro.cap), elementos(new char*[outro.cap]) {
    for (int i = 0; i < tam; i++) elementos[i] = copiarStr(outro.elementos[i]);
}

ConjuntoStr& ConjuntoStr::operator=(const ConjuntoStr& outro) {
    if (this == &outro) return *this;
    for (int i = 0; i < tam; i++) delete[] elementos[i];
    delete[] elementos;
    tam = outro.tam;
    cap = outro.cap;
    elementos = new char*[cap];
    for (int i = 0; i < tam; i++) elementos[i] = copiarStr(outro.elementos[i]);
    return *this;
}

bool ConjuntoStr::pertence(const char* s) const {
    for (int i = 0; i < tam; i++)
        if (strcmp(elementos[i], s) == 0) return true;
    return false;
}

void ConjuntoStr::adicionar(const char* s) {
    if (pertence(s)) return;
    if (tam == cap) crescer();
    elementos[tam++] = copiarStr(s);
}

void ConjuntoStr::remover(const char* s) {
    for (int i = 0; i < tam; i++) {
        if (strcmp(elementos[i], s) == 0) {
            delete[] elementos[i];
            elementos[i] = elementos[tam - 1];
            tam--;
            return;
        }
    }
}

int ConjuntoStr::tamanho() const { return tam; }
int ConjuntoStr::operator~() const { return tam; }
bool ConjuntoStr::operator<<(const char* s) const { return pertence(s); }

ConjuntoStr& ConjuntoStr::operator+=(const char* s) {
    adicionar(s);
    return *this;
}

bool ConjuntoStr::operator==(const ConjuntoStr& outro) const {
    if (tam != outro.tam) return false;
    for (int i = 0; i < tam; i++)
        if (!outro.pertence(elementos[i])) return false;
    return true;
}

bool ConjuntoStr::operator!=(const ConjuntoStr& outro) const {
    return !(*this == outro);
}

bool ConjuntoStr::operator<=(const ConjuntoStr& outro) const {
    for (int i = 0; i < tam; i++)
        if (!outro.pertence(elementos[i])) return false;
    return true;
}

ConjuntoStr ConjuntoStr::operator|(const ConjuntoStr& outro) const {
    ConjuntoStr r;
    for (int i = 0; i < tam; i++) r.adicionar(elementos[i]);
    for (int i = 0; i < outro.tam; i++) r.adicionar(outro.elementos[i]);
    return r;
}

ConjuntoStr ConjuntoStr::operator&(const ConjuntoStr& outro) const {
    ConjuntoStr r;
    for (int i = 0; i < tam; i++)
        if (outro.pertence(elementos[i])) r.adicionar(elementos[i]);
    return r;
}

ConjuntoStr ConjuntoStr::operator-(const ConjuntoStr& outro) const {
    ConjuntoStr r;
    for (int i = 0; i < tam; i++)
        if (!outro.pertence(elementos[i])) r.adicionar(elementos[i]);
    return r;
}

std::ostream& ConjuntoStr::imprimir(std::ostream& os) const {
    os << "{ ";
    for (int i = 0; i < tam; i++) {
        os << elementos[i];
        if (i < tam - 1) os << ", ";
    }
    os << " }";
    return os;
}

std::ostream& operator<<(std::ostream& os, const ConjuntoStr& c) {
    return c.imprimir(os);
}
