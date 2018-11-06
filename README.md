# Tarea 1 CC4102-Diseño y Análisis de Algoritmos
Tarea 1 del curso Diseño y Análisis de Algoritmos

## Integrantes
* Pedro Belmonte
* Víctor Garrido
* Gabriela Mendoza

## Requisitos
La tarea fue resuelta en C++11. Para compilar se requiere CMake versión >= 3.0.0.

## Compilación
Para compilar se deben ejecutar los siguientes comandos:

```
$ cmake .
```

```
$ cmake --build .
```

Esto genera los ejecutables para cada una de las preguntas.
## Ejecución
Para ejecutar se usa el siguiente comando para cada pregunta:
### P1
Recibe N, que indica ingresar 10^N datos, y opcionalmente M (default = 100000) cantidad de memoria. Luego estos datos los ordena. Para que el ordenamiento funcione correctamente, se toma como supuesto que N / M es múltiplo de 2.

Ej:
```
$ ./mainP1 6
```
```
$ ./mainP1 6 15625
```
### P2 
Recibe N y la columna por la cual se desea ordenar

Ej:
```
$ ./mainP2 3 id
```
### P3
Recibe C y P, que indican la cantidad de consumidores y productos, y opcionalmente M.

Ej:
```
$ ./mainP3 1 1 5
```
