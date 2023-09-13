#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long C, N, K;
long long mejor_costo;
vector<long long> puestos;
vector<long long> proveedores;
vector<long long> mejor_proveedores;
vector<vector<long long>> memo;

long long costoTotal() {
    long long costo = 0;
    for (long long puesto : puestos) {
        long long costoMinimo = INT_MAX;
        for (long long prov : proveedores) {
            costoMinimo = min(costoMinimo, abs(puesto - prov));
        }
        costo += costoMinimo;
    }
    return costo;
}

long long costoMinimoTotal(long long i, long long k) {
    if (i >= N && k > 0) {
        return INT_MAX;
    }
    if (k <= 0) {
        long long costo = costoTotal();

        if (costo < mejor_costo) {
            mejor_costo = costo;
            mejor_proveedores = proveedores;
        }

        return costo;
    }
    if (memo[i][k] != -1) {
        return memo[i][k];
    }

    long long costoMinimo = INT_MAX;
    for (long long j = i; j < N ; j++){

        proveedores.push_back(puestos[j]);

        costoMinimo = min(costoMinimo, costoMinimoTotal(j+1, k-1));

        proveedores.pop_back();
    }

    memo[i][k] = costoMinimo;

    return costoMinimo;
}


int main() {
    vector<long long> respuestas;
    vector<vector<long long>> disposiciones;

    cin >> C;
    for (long long c = 0; c < C; c++) {
        puestos.clear();
        proveedores.clear();
        mejor_costo = INT_MAX;
        mejor_proveedores.clear();
        memo.clear();

        cin >> N >> K;
        memo.resize(N, vector<long long>(K+1, -1));

        for (long long i = 0; i < N; i++) {
            long long p;
            cin >> p;
            puestos.push_back(p);
        }

        costoMinimoTotal(0, K);

        respuestas.push_back(mejor_costo);
        disposiciones.push_back(mejor_proveedores);
    }
    for (long long i = 0; i < respuestas.size(); i++) {
        cout << respuestas[i] << endl;
        for (long long j = 0; j < disposiciones[i].size(); j++) {
            cout << disposiciones[i][j];
            if (j != disposiciones[i].size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
