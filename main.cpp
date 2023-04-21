/*Hecho por Marcos Abaroa para la materia de Inteligencia Artificial I
Programa basado en el juego Nim de 2 jugadores: Maquina vs Maquina*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <ctime>

using namespace std;
const int INF = numeric_limits<int>::max(); // valor infinito
const int MAX_PROF = 4; // profundidad maxima

// Estructura para representar un estado del juego
struct Estado {
    int palitos;
    int jugadorActual;
};

// Función que genera los sucesores de un estado
vector<Estado> generarSucesores(Estado estado) {
    vector<Estado> sucesores;
    for (int i = 1; i <= 3; i++) {
        if (i <= estado.palitos) {
            Estado sucesor = {estado.palitos - i, estado.jugadorActual == 1 ? 2 : 1};
            sucesores.push_back(sucesor);
        }
    }
    return sucesores;
}

int MiniMax(Estado u, int Prof, bool Mano) {
    if (u.palitos == 1) {
        return Mano ? -1 : 1;
    }
    if (Prof == 0) {
        return 0;
    }
    int m = Mano ? -1 : 1;
    vector<Estado> sucesores = generarSucesores(u);
    for (Estado v : sucesores) {
        int t = MiniMax(v, Prof - 1, !Mano);
        if ((Mano && t > m) || (!Mano && t < m)) {
            m = t;
        }
    }
    return m;
}

int maquina(int palos) {
    int m = -2;
    int mejorMovimiento = 1;
    vector<Estado> sucesores = generarSucesores({palos, 1});
    for (Estado v : sucesores) {
        int t = MiniMax(v, 4, false);
        if (t > m) {
            m = t;
            mejorMovimiento = palos - v.palitos;
        }
    }
    return mejorMovimiento;
}

//Funcion para que el usuario seleccione cuantos palitos quitar
int jugador(int palos) {
    int maquina = rand() % 3 + 1;
    if (palos < 3) {
        maquina = palos;
    }
    if (palos == 1) {
        maquina = 1;
    }
    return maquina;
}


int main() {
    int palitos = 21;
    int jugadorActual = 2;
    cout << "Juego de los Palillos" << endl;
    cout << "=====================" << endl;
    while (palitos > 1) {
        cout << "Palitos restantes: ";
        for (int i = 0; i < palitos; i++) {
            cout << "|";
        }
        cout << endl;
        if (jugadorActual == 1) {
            int palitosQuitados = jugador(palitos);
            palitos -= palitosQuitados;
            cout << "La maquina Aleatoria quita " << palitosQuitados << " palos." << endl;
            jugadorActual = 2;
        }
        else {
            int palitosQuitadosMaquina = maquina(palitos);
            palitos -= palitosQuitadosMaquina;
            cout << "La maquina Minimax quita " << palitosQuitadosMaquina << " palos." << endl;
            jugadorActual = 1;
        }
    }
    cout << "Palos restantes: ";
    for (int i = 0; i < palitos; i++) {
        cout << "|";
    }
    cout << endl;
    if (jugadorActual == 1) {
        cout << "La maquina Minimax gana" << endl;
    }
    else {
        cout << "El maquina Aleatoria gana" << endl;
    }
    return 0;
}
