/**
 * @file carrera.cpp
 * @authors Marcelo Paz / Claudia Sobino
 * @version 1.0
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace std;

// Estructura que representa el podio de la carrera
struct podio_t {
    long nAuto;
    long posicion;
};

vector<podio_t> podio;
mutex permiso;

/**
 * La funcion genera un numero aleatoreo entre un rango especifico.
 * 
 * @param min Este parametro representa el minimo valor del numero aleatoreo a generar.
 * @param min Este parametro representa el maximo valor del numero aleatoreo a generar.
 * 
 * @return Un numero aleatoreo de tipo `long` entre `min` y `max`, incluyendolos.
 */
long numeroAleatorio(long min, long max) {
    return rand() % (max - min + 1) + min;
}

/**
 * La funcion `avanzar` simula el progreso de un auto en una carrera, en la simulacion se avanza un numero 
 * aleatoreo de metros y se detiene un tiempo aleatoreo entre 100 y 500 milisegundos. El auto avanza hasta 
 * llegar a la meta, una vez que llega a la meta se guarda el auto y su posicion en el podio.
 * 
 * @param M Este parametro representa la distancia total de la carrera, el auto avanza hasta llegar a la meta.
 * @param nAuto Este parametro representa el identificador del auto, se utiliza para identificar el auto en el podio.
 * @param semilla Este parametro representa la semilla que genera el numero aleatoreo, se utiliza una semilla distinta por cada hilo para evitar valores identicos entre los varios hilos en ejecución.
 */
void avanzar(long M, long nAuto, unsigned int semilla) {
    srand(semilla);
    long distanciaTotal = 0;
    while (true) {
        long nuevaDistancia = numeroAleatorio(1, 10); // El auto avana entre 1 y 10 metros
        distanciaTotal += nuevaDistancia; 

        // Si la distancia total es mayor o igual a la distancia de la carrera, se guarda el auto y su posicion en el podio utilizando un mutex, para evitar que varios hilos guarden el mismo auto en la misma posicion.
        if (distanciaTotal >= M) {
            permiso.lock();
            podio_t p = {nAuto, static_cast<long>(podio.size()) + 1};
            podio.push_back(p);
            printf("Auto%ld avanza %ld metros y termina la carrera en el lugar %ld!\n", nAuto, nuevaDistancia, podio.size());
            permiso.unlock();
            break;
        }

        // Se muestra el avance del auto en la carrera utilizando un mutex, para evitar que varios hilos escriban en la consola al mismo tiempo.
        permiso.lock();
        printf("Auto%ld avanza %ld metros (total: %ld metros)\n", nAuto, nuevaDistancia, distanciaTotal);
        long detenerse = (numeroAleatorio(100, 500));
        // printf("Auto%ld se detiene: %ld\n", nAuto, detenerse);
        permiso.unlock();
        this_thread::sleep_for(chrono::milliseconds(detenerse));// El auto se detiene entre 100 y 500 ms
    }
}

int main(int argc, char *argv[]) {
    // Verificamos que se hayan pasado la cantidad de argumentos correctos
    if (argc != 3) {
        printf("Uso %s <cantidad de metros totales> <cantidad de autos>\n", argv[0]);
        return -1;
    }

    // Verificamos que la distancia de la carrera sea mayor a 0
    if (atoll(argv[1]) <= 0) {
        printf("Uso %s <cantidad de metros totales> <cantidad de autos>\n", argv[0]);
        printf("Los metros deben ser > 0\n");
        return -1;
    }
    long M = atoll(argv[1]);

    // Verificamos que la cantidad de autos sea mayor a 0
    if (atoll(argv[2]) <= 0) {
        printf("Uso %s <cantidad de metros totales> <cantidad de autos>\n", argv[0]);
        printf("La cantidad de autos debe ser > 0\n");
        return -1;
    }
    long N = atoll(argv[2]);
    vector<thread> tids;

    printf("Distancia total carrera: %ld metros\n", M);
    printf("-----------------------------------\n");

    // Creamos un hilo por cada auto, cada uno con
    for (long i = 0; i < N; ++i) {
        unsigned int semilla = time(NULL) + i;
        tids.emplace_back(avanzar, M, i, semilla); // Se utiliza emplace_back para evitar copias
    }

    // Esperamos a que todos los hilos terminen
    for (auto& t : tids) {
        t.join();
    }

    // Mostramos el resultado final
    printf("Lugar\tAuto\n");
    printf("-------------\n");
    for (auto& p : podio) {
        printf("%ld\tAuto%ld\n", p.posicion, p.nAuto);
    }
    return 0;
}
