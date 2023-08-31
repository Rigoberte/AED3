#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

/* Problema 4
N puestos a lo largo de esta con números naturales
Colocar K proveedurías, y puede poner estas en cualquier posición 
El costo se define como la suma de las distancias de cada restaurante a su proveeduría más cercana
Se quiere conocer qué tan bajo puede ser el costo, y una de las disposiciones que alcance este valor óptimo
*/


/* Descripción de una instancia
La entrada contiene múltiples casos de test. La primera línea consiste de un número c indicando su cantidad de casos.
La primera línea de cada caso contiene dos enteros N y K, indicando respectivamente la cantidad de puestos y la cantidad de proveedurías que se quieren colocar
Luego sigue una línea con N enteros xi, con 1 ≤ xi ≤ 107, denotando las posiciones de los distintos puestos. Esta lista de posiciones está ordenada
*/

/* Descripción de la salida
Para cada caso de test se debe imprimir una línea indicando el mínimo valor que puede alcanzar el costo de la distribución de las proveedurías. 
Luego se debe imprimir otra línea, describiendo de forma ordenada la disposición que alcanza este valor y es lexicográficamente mínima.
*/

using namespace std;

vector<int> puestos;
vector<int> proveedores;

int proveedorMasCercano(int p){
    int minimo = 0;
    int diff = 0;
    int pos = 0;
    int i = 0;

    while (i < proveedores.size()){
        diff = abs(puestos[p] - proveedores[i]);
        if (diff < minimo){
            minimo = diff;
            pos = i;
        }
        i++;
    }

    return pos;
}

int costoTotal(){
    int costo = 0;
    int i = 0;

    while (i < puestos.size()){
        costo += puestos[i] - proveedores[proveedorMasCercano(i)];
        i++;
    }

    return costo;
}

int costoMinimo(int i, int p, vector<int> prov){
    if (i == puestos.size()) {return costoTotal();}
    if (p == 0) {return costoTotal();}
    else{
        vector<int> provv = prov;
        provv.push_back(puestos[i]);
        return min(costoMinimo(i+1, p, prov), costoMinimo(i+1, p-1, provv));
    }

}

int main()
{
    int n, k, c;
    int costoMin;

    cin >> c; // numero de casos 
    for (int i = 0; i < c; i++){
        cin >> n >> k; // numero de puestos y numero de proveedurias
        puestos.resize(n);

        for (int j = 0; j < n; j++){
            cin >> puestos[j];
        }
        
        costoMin = costoMinimo(0, k, proveedores);

        cout << costoMin << endl;
        for (int j = 0; j < proveedores.size(); j++){
            cout << proveedores[j] << " ";
        }
    }

    return 0;
}
