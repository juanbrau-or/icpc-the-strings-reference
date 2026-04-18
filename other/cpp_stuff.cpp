// --- 1. PRECISION Y CONSTANTES ---
// Valor infinito para double. Mas seguro que usar 1e18 o similares.
const double DINF = numeric_limits<double>::infinity();

// Epsilon: margen de error para comparar flotantes. 
// Ajustar segun el problema (usualmente entre 1e-7 y 1e-9).
const double EPS = 1e-9; 

// Comparador personalizado para usar double como llave en set o map.
// Evita que 0.3000000000001 y 0.3 sean tratados como distintos.
struct DoubleComparator {
    bool operator()(const double& a, const double& b) const {
        // Se considera que a < b solo si a es menor que b por al menos EPS.
        return a + EPS < b;
    }
};

// Uso: set<double, DoubleComparator> mi_set;

// --- 2. TRUCOS DE BITMASKS ---

void bitmask_tricks(int m) {
    // Iterar sobre todos los subconjuntos de la mascara 'm' (Orden decreciente)
    // Ejemplo: si m = 1010 (10), iterara por 1010, 1000, 0010.
    for (int s = m; s > 0; s = (s - 1) & m) {
        // s es un subconjunto no vacio de m
    }

    // Iterar sobre todos los subconjuntos de 'm' (Orden creciente)
    // Esta sintaxis es muy compacta; 's = (s - m) & m' hace la magia.
    for (int s = 0; s = (s - m) & m; ) {
        // s es un subconjunto no vacio de m
    }
}

// --- 3. BUILT-INS DE GCC (Super rapidos) ---

void built_ins(unsigned int x, unsigned long long xll) {
    // Cuenta cuantos bits estan encendidos (en 1).
    int unos = __builtin_popcount(x);
    
    // Cuenta ceros al final (derecha). 
    // Util para saber la potencia de 2 mas grande que divide a x.
    // OJO: __builtin_ctz(0) es INDEFINIDO.
    if (x != 0) {
        int ceros_derecha = __builtin_ctz(x);
    }
    
    // Cuenta ceros al inicio (izquierda). 
    // Util para saber cuantos bits se necesitan para representar el numero.
    // OJO: __builtin_clz(0) es INDEFINIDO.
    if (x != 0) {
        int ceros_izquierda = __builtin_clz(x);
    }

    // Versiones para long long (64 bits): solo agrega el sufijo 'll'
    int unos_ll = __builtin_popcountll(xll);
}

// --- 4. LEAST SIGNIFICANT BIT (LSB) ---

int get_lsb(int x) {
    // Aisla el bit encendido mas a la derecha.
    // Ejemplo: x = 12 (1100), -x en binario es (0100), x & -x = 4 (0100).
    return x & (-x);
}