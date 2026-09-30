# Ranking de una competencia — Equipo 3

## Objetivo
Programa en C++ que registra participantes con nombre y puntuacion,
ordena el ranking de mayor a menor, busca por nombre y calcula
el promedio mediante recursion.

## Programacion orientada a objetos
- Participante: encapsula el nombre y la puntuacion.
- Competencia: administra los participantes y las operaciones.
- Los atributos son privados y se accede a ellos mediante metodos publicos.

## Algoritmos
- Ordenamiento: stable_sort, en orden descendente de puntuacion.
  Los empates conservan el orden de registro.
- Busqueda: recorrido lineal por nombre, con coincidencia exacta.
- Promedio: una funcion recursiva suma las puntuaciones.
  El caso base devuelve 0 al llegar al final.
  La suma se divide entre el numero de participantes.

## Complejidad
n = cantidad de participantes; L = longitud maxima de un nombre.
Se consideran las operaciones numericas de costo constante.

| Funcion | Tiempo | Espacio auxiliar |
|---|---|---|
| Constructor de Participante | O(L), por copiar el nombre | O(L) |
| getNombre y getPuntuacion | O(1) | O(1) |
| registrar | O(L) amortizado; O(n + L) si el vector se realoca | O(L) para el nuevo nombre |
| sumarRecursivo | O(n) | O(n), por las llamadas recursivas |
| mostrarPromedio | O(n) | O(n) |
| buscar | O(nL), por comparar los nombres | O(1) |
| mostrarRanking | O(n log n + nL) con memoria disponible | O(n) para ordenar |
| leerNumero | O(m), siendo m la longitud de la entrada | O(m) |
| main | Depende de las opciones ejecutadas | Incluye los datos y las operaciones |

stable_sort realiza O(n log n) comparaciones si dispone de memoria
auxiliar suficiente; en caso contrario puede requerir O(n log² n).
Mostrar el ranking tambien imprime todos los nombres: O(nL).

Para un ciclo de registrar n participantes, ordenar, buscar y calcular
el promedio, con nombres de longitud acotada y memoria suficiente,
el tiempo total es O(n log n) y el espacio total O(n).
El menu puede repetirse, por lo que su costo depende de las operaciones
que seleccione el usuario.

## Compilar en PowerShell
g++ -std=c++17 -Wall -Wextra COMPETITION-RANKING.cpp -o ranking.exe

## Ejecutar en PowerShell
.\ranking.exe

## Pruebas realizadas
Participantes:
- Luis: 100
- Ana: 80
- Pedro: 60
- Sebastian: 0

Resultados:
- Ranking: Luis, Ana, Pedro, Sebastian.
- Buscar Ana: 80.00 puntos.
- Promedio: (100 + 80 + 60 + 0) / 4 = 60.00.

## Limitaciones
Los datos se mantienen en memoria y se pierden al cerrar el programa.
La busqueda distingue mayusculas y minusculas.
La recursion utiliza una llamada por participante.