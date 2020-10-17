#include <bits/stdc++.h>
using namespace std;

struct vehicle {
    string name;
    float length;
};

int main() {
    int G, H, L;
    vector<vehicle> vehicles;
    cout << "Ingrese la ganancia minima necesaria: ";
    cin >> G;
    cout << endl << "Ingrese el largo del Ferry: ";
    cin >> L;
    cout << endl << "Ingrese la cantidad de hileras del Ferry: ";
    cin >> H;
    while(true) {
        cout << endl << "Ingrese 'a' para agregar vehiculos o 'e' para dejar de agregar vehiculos: ";
        char k;
        cin >> k;
        if (k == 'a') {
            cout << endl << "Ingrese un tipo de vehiculo del cual quiere saber el precio: ";
            vehicle x;
            cin >> x.name;
            cout << endl << "Ingrese el largo tipo de vehiculo: ";
            cin >> x.length;
            vehicles.push_back(x);
        } else if (k == 'e') {
            break;
        } else {
            cout << endl << "Comando invalido";
            continue;
        }
    }

    for (int i = 0; i < vehicles.size(); i++) {
        int P;
        P = G / (int(L / vehicles[i].length) * H);
        cout << "El precio de " << vehicles[i].name << " debiera ser: $" << P << endl;

    }
       
}