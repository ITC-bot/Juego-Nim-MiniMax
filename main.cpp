/*Hecho por Marcos Abaroa para la materia de Inteligencia Artificial I
Programa basado en el juego Nim de 2 jugadores: Maquina vs Maquina*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <ctime>
#include <cstdlib>

using namespace std;
const int INF = numeric_limits<int>::max(); // valor infinito
const int MAX_PROF = 15; // Si se requiere mas precision, aumente la profundidad maxima

// Estructura para representar un estado del juego
struct Estado {
    int palitos;
    int jugadorActual;
};

// Variable global para llevar la cuenta de los nodos visitados
long long contadorNodos = 0;

// Funcion que genera los sucesores de un estado
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

// Funcion minimax
int MiniMax(Estado u, int Prof, bool Mano) {
    contadorNodos++; // Incrementamos el contador de nodos
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

//Funcion que controla los movimientos de la "Maquina inteligente"
int maquina(int palos) {
    int m = -2;
    int mejorMovimiento = 1;
    vector<Estado> sucesores = generarSucesores({palos, 1});
    for (Estado v : sucesores) {
        int t = MiniMax(v, MAX_PROF, false);
        if (t > m) {
            m = t;
            mejorMovimiento = palos - v.palitos;
        }
    }
    return mejorMovimiento;
}

//Funcion para la maquina "Menos inteligente" haga sus jugadas
int aleatorio(int palos) {
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
    int palitos = 19; //Si se requiere que el juego sea con mas o menos palitos altere esta variable
    int jugadorActual = rand() % 2 + 1; //Numero aleatorio entre 1 y 2 para ver que jugador inicia
    cout << "Juego de los Palillos" << endl;
    cout << "=====================" << endl;
    while (palitos > 1) {
        cout << "Palitos restantes: ";
        for (int i = 0; i < palitos; i++) {
            cout << "|";
        }
        cout << endl;

        if (jugadorActual == 1) {
            int palitosQuitados = aleatorio(palitos);
            palitos -= palitosQuitados;
            cout << "La maquina Aleatoria quita " << palitosQuitados << " palos." << endl;
            jugadorActual = 0;
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
    cout << "Nodos visitados por la maquina Minimax: " << contadorNodos << endl; // imprimir el número de nodos visitados
    return 0;
}
