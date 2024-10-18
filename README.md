# Tarea-1_SSOO

Este proyecto es un programa en C++ que simula una carrera de autos utilizando hilos para controlar el movimiento de cada auto. Cada auto avanza aleatoriamente hasta completar una distancia determinada y luego se muestra un podio con las posiciones finales.

## Requisitos

>[!CAUTION]
>El codigo ocupa las libreria *thread* y *mutex*.

- g++ (compatible con C++11 o superior)
- make

## Instrucciones

### Clonar el repositorio

```sh
git clone https://github.com/MarceloPazPezo/Tarea1_SSOO.git
cd Tarea1_SSOO
```

### Compilar el programa

```sh
make
```

### Ejecutar el programa

```sh
./carrera <cantidad de metros totales> <cantidad de autos>
```

Ejemplo:

```sh
./carrera 100 5
```

Donde:

- 100 es la cantidad de metros de la carrera.
- 5 es la cantidad de autos.

### Eliminar archivos generados por make

```sh
make clean
```

### Instalar el programa

El ejecutable se instalara en /usr/local/bin.

```sh
make install
```

### Desinstalar el programa

```sh
make uninstall
```

## Autores

- [Marcelo Alfredo Paz Pezo](https://github.com/MarceloPazPezo)
- [Claudia Jimena Sobino Sobino](https://github.com/Clau-SS)
