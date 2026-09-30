#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

class Participante {
private:
    string nombre;
    double puntuacion;

public:
    Participante(string nombre, double puntuacion)
        : nombre(nombre), puntuacion(puntuacion) {}

    const string& getNombre() const { return nombre; }
    double getPuntuacion() const { return puntuacion; }
};

class Competencia {
private:
    vector<Participante> participantes;

    // Caso base: ya recorrimos todos los participantes.
    double sumarRecursivo(size_t indice) const {
        if (indice == participantes.size()) return 0;
        return participantes[indice].getPuntuacion()
             + sumarRecursivo(indice + 1);
    }

public:
    void registrar(const string& nombre, double puntuacion) {
        participantes.emplace_back(nombre, puntuacion);
    }

    void mostrarRanking() {
        if (participantes.empty()) {
            cout << "No hay participantes registrados.\n";
            return;
        }

        // Orden descendente; los empates conservan el orden de registro.
        stable_sort(participantes.begin(), participantes.end(),
            [](const Participante& a, const Participante& b) {
                return a.getPuntuacion() > b.getPuntuacion();
            });

        cout << "\n--- RANKING ---\n";
        for (size_t i = 0; i < participantes.size(); ++i) {
            cout << i + 1 << ". "
                 << participantes[i].getNombre() << " | "
                 << participantes[i].getPuntuacion() << " puntos\n";
        }
    }

    void buscar(const string& nombre) const {
        bool encontrado = false;
        for (const auto& participante : participantes) {
            if (participante.getNombre() == nombre) {
                cout << "Encontrado: " << participante.getNombre()
                     << " | " << participante.getPuntuacion()
                     << " puntos\n";
                encontrado = true;
            }
        }
        if (!encontrado) cout << "Participante no encontrado.\n";
    }

    void mostrarPromedio() const {
        if (participantes.empty()) {
            cout << "No hay participantes para calcular el promedio.\n";
            return;
        }
        cout << "Promedio: "
             << sumarRecursivo(0) / participantes.size() << "\n";
    }
};

// Lee una linea completa y rechaza letras o contenido sobrante.
bool leerNumero(double& numero) {
    string linea;
    if (!getline(cin, linea)) return false;

    istringstream entrada(linea);
    if (!(entrada >> numero) || !isfinite(numero)) return false;
    entrada >> ws;
    return entrada.eof();
}

int main() {
    Competencia competencia;
    cout << fixed << setprecision(2);

    while (true) {
        cout << "\n=== COMPETENCIA - EQUIPO 3 ===\n"
             << "1. Registrar participante\n"
             << "2. Mostrar ranking\n"
             << "3. Buscar participante por nombre\n"
             << "4. Calcular promedio recursivo\n"
             << "0. Salir\n"
             << "Opcion: ";

        double opcion;
        if (!leerNumero(opcion)) {
            if (cin.eof()) break;
            cout << "Introduce una opcion numerica valida.\n";
            continue;
        }

        if (opcion == 0) break;

        if (opcion == 1) {
            string nombre;
            double puntuacion;

            cout << "Nombre: ";
            if (!getline(cin, nombre)) break;

            if (nombre.find_first_not_of(" \t\r") == string::npos) {
                cout << "El nombre no puede estar vacio.\n";
                continue;
            }

            cout << "Puntuacion (usa punto para decimales): ";
            if (!leerNumero(puntuacion)) {
                if (cin.eof()) break;
                cout << "Puntuacion invalida.\n";
                continue;
            }

            competencia.registrar(nombre, puntuacion);
            cout << "Participante registrado.\n";
        } else if (opcion == 2) {
            competencia.mostrarRanking();
        } else if (opcion == 3) {
            string nombre;
            cout << "Nombre a buscar (escribelo igual al registrado): ";
            if (!getline(cin, nombre)) break;
            competencia.buscar(nombre);
        } else if (opcion == 4) {
            competencia.mostrarPromedio();
        } else {
            cout << "Opcion invalida.\n";
        }
    }

    cout << "Programa finalizado.\n";
    return 0;
}