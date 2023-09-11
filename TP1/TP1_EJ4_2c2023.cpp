#include <iostream>
#include <string>
#include <vector>

using namespace std;
int C, N, K;
vector<int> puestos;
vector<bool> proveedores;

int costoTotal(){
    int costo = 0;
    for (int i = 0; i < N; i++) {
        int costoMinimo = 10000;
        for (int j = 0; j < N; j++) {
            if (proveedores[j]) {
                int costoActual = abs(puestos[i] - puestos[j]);
                if (costoActual < costoMinimo) {
                    costoMinimo = costoActual;
                }
            }
        }
        costo += costoMinimo;
    }
    return costo;
}

int costoMinimoTotal(int i, int k) {
    if (i == N && k != 0) {return 10000;}
    if (k == 0) {
        return costoTotal();
    }
    int costoMinimo = 10000;
    for (int j = i; j < N; j++) {
        proveedores[j] = true;
        int costo = costoMinimoTotal(i + 1, k - 1);
        if (costo < costoMinimo) {
            costoMinimo = costo;
        }
        proveedores[j] = false;
    }
    return costoMinimo;
}

int main() {
    vector<int> respuestas;
    int respuesta;

    cin >> C;
    for (int c = 0; c < C; c++) {
        puestos.clear();
        proveedores.clear();
        cin >> N >> K;

        for (int i = 0; i < N; i++) {
            int p;
            cin >> p;
            puestos.push_back(p);
        }
        proveedores.resize(N, false);

        respuesta = costoMinimoTotal(0, K);
        respuestas.push_back(respuesta);
    }
    for (int i = 0; i < respuestas.size(); i++) {
        cout << respuestas[i] << endl;
    }

    return 0;
}
