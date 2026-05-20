#include <bits/stdc++.h>
#ifdef DEMETRIO
#define deb(...) fprintf(stderr,__VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif

// --- DEBUGGING TOOLS ---
void void_debug() { std::cerr << std::endl; }
template<typename Head, typename... Tail>
void void_debug(const Head& H, const Tail&... T) { std::cerr << " " << H; void_debug(T...); }

#ifdef LOCAL
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]:", void_debug(__VA_ARGS__)
#else
#define debug(...) 42
#endif

/*
Uso en competencia:
Compila localmente con el flag -DLOCAL para activar las salidas por cerr, por
ejemplo:
    g++ -std=c++17 -O2 -Wall -Wextra -DLOCAL main.cpp -o main

Dentro del codigo puedes escribir:
    debug(variable_x, mi_vector[0], "llegue aqui");

Cuando LOCAL no esta definido, como ocurre normalmente al enviar al juez en
linea, debug(...) se expande a una expresion inocua y no imprime nada. Esto
mantiene las trazas fuera del output oficial sin tener que borrar llamadas de
debug antes de enviar gracias a #ifdef LOCAL. Si tu entorno usa
#ifndef ONLINE_JUDGE, puedes mantener la misma idea: compila localmente con
-DLOCAL y envia sin ese flag.
*/

#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;

int main(){
	return 0;
}
