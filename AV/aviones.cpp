#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Avion {
    int tiempoLimite;
    int beneficio;
};

// Ordenar por beneficio
bool comp(Avion a, Avion b) {
    return a.beneficio > b.beneficio;
}

int obtenerBeneficioMaximo(int Ut, vector<Avion>& aviones) {
    // Vector que indica si una unidad de tiempo ya está ocupada
    bool *tiempo = new bool[Ut+1];
    fill(tiempo,tiempo+Ut+1,false); // Inicializacion a false
    int beneficioTotal = 0;

    // Ordenar los aviones de mayor a menor
    sort(aviones.begin(), aviones.end(), comp);

    for (Avion avion : aviones) {
        // Buscar el último instante libre antes del límite del avión y dentro del horario
        for (int t = min(avion.tiempoLimite, Ut); t >= 1; --t) {
            if (!tiempo[t]) {
                tiempo[t] = true;
                beneficioTotal += avion.beneficio;
                break;
            }
        }
    }

    delete[] tiempo;

    return beneficioTotal;
}

int main() {
    int N;
    cin >> N;

    for(int i=0; i<N; i++) {
        int Ut, A;
        cin >> Ut >> A;

        int T[A], B[A];
        for (int i = 0; i < A; ++i) cin >> T[i];
        for (int i = 0; i < A; ++i) cin >> B[i];

        vector<Avion> aviones(A);
        for (int i = 0; i < A; ++i) {
            aviones[i].tiempoLimite = T[i];
            aviones[i].beneficio = B[i];
        }

        cout << obtenerBeneficioMaximo(Ut, aviones) << endl;
    }

    return 0;
}
