# Arquitectura de Computadores CR3 - Tarea 1

## Finalidad del Repositorio

Este repositorio reúne los ejercicios desarrollados para la Tarea 1 del curso de Arquitectura de Computadores CR3. El objetivo es mostrar, de manera comparativa, cómo se implementan y manipulan matrices en distintos lenguajes de programación, permitiendo analizar las diferencias en sintaxis, lógica y funcionamiento.

---

## Objetivo

- tiene como objetivo analizar y comparar el comportamiento de dos algoritmos clásicos de multiplicación de matrices: el algoritmo ingenuo (naive) y el algoritmo de Strassen. La implementación se desarrolló en lenguaje C para aprovechar la cercanía al hardware y observar el rendimiento computacional de forma más precisa. Se valuaron aspectos como el tiempo de ejecución y la memoria estimada para diferentes tamaños de matrices cuadradas.

- Comprender cómo se declaran, inicializan y manipulan matrices en Java, C++, C y Python.
- Analizar ventajas, diferencias y particularidades de cada lenguaje al trabajar con estructuras bidimensionales.
- Desarrollar la habilidad de adaptar algoritmos de arquitectura de computadores a diferentes entornos de programación.

---

## 👣 Paso a Paso: ¿Cómo se hizo este repositorio y cada código?

### 1. Selección del ejercicio principal

Se eligió como ejercicio fundamental la creación, llenado y recorrido de matrices, así como la realización de operaciones básicas (como suma de elementos) sobre ellas.

---

### 2. Implementación en varios lenguajes

#### Java (`Java/MatrizPrincipal.java`)

- **Declaración de la matriz**: Se define una matriz bidimensional de tipo int.
- **Llenado de la matriz**: Se usan bucles anidados para asignar valores a cada posición.
- **Recorrido e impresión**: Se recorre la matriz y se imprime cada elemento.
- **Operaciones adicionales**: Puede incluir suma de todos los elementos o búsqueda de un valor específico.

#### C++ (`C++/matriz_principal.cpp`)

- **Declaración de la matriz**: Se declara una matriz de tamaño fijo.
- **Llenado de la matriz**: Se pide al usuario ingresar los valores o se llenan automáticamente con bucles.
- **Recorrido e impresión**: Se recorre la matriz con bucles for y se imprime cada elemento.
- **Operaciones adicionales**: Suma de elementos, cálculo de promedios o búsqueda de valores.

#### C (`C/matriz_principal.c`)

- **Declaración de la matriz**: Se utiliza un arreglo bidimensional de tamaño fijo.
- **Llenado de la matriz**: Se utiliza scanf o asignación automática para llenar la matriz.
- **Recorrido e impresión**: Mediante bucles for, se recorre y se imprime la matriz.
- **Operaciones adicionales**: Suma de elementos o manipulación básica de los datos.

#### Python (`Python/matriz_principal.py`)

- **Declaración de la matriz**: Se usan listas anidadas para simular una matriz.
- **Llenado de la matriz**: Se generan los valores usando comprensión de listas o input del usuario.
- **Recorrido e impresión**: Se usan bucles for para mostrar el contenido.
- **Operaciones adicionales**: Suma de filas/columnas, búsqueda de valores o uso de librerías como NumPy para operaciones más avanzadas.

---

### 3. Pruebas y comparación

- Se ejecutó cada código verificando que los resultados fueran equivalentes en todos los lenguajes.
- Se documentaron diferencias, por ejemplo, la necesidad de manejo de memoria en C o la facilidad de manipulación en Python.

---

### 4. Organización del repositorio

- Se crearon carpetas para cada lenguaje, con el archivo principal de la matriz y posibles variantes o archivos auxiliares.
- Se mantuvo una estructura clara para facilitar la comparación, navegación y reutilización de los códigos.

---

### 5. Documentación

- Se elaboró este README explicando la finalidad, los objetivos, el proceso de desarrollo y el contenido de cada archivo y lenguaje.

---

## 📁 Archivos y carpetas del repositorio

- **Java/**  
  - `MatrizPrincipal.java`: Crea, llena, recorre e imprime una matriz. Muestra operaciones básicas como suma de elementos.

- **C++/**  
  - `matriz_principal.cpp`: Muestra la declaración, llenado e impresión de una matriz, así como operaciones como suma o búsqueda.

- **C/**  
  - `matriz_principal.c`: Implementa una matriz bidimensional, la recorre e imprime, y realiza operaciones básicas.

- **Python/**  
  - `matriz_principal.py`: Usa listas anidadas para simular matrices y realiza operaciones básicas y recorridos de manera sencilla.

---

## 🧮 Explicación de matrices en cada lenguaje

### Java

En Java, una matriz bidimensional se declara como un arreglo de arreglos.  
Ejemplo de declaración y uso:
```java
int[][] matriz = new int[3][3]; // Matriz de 3 filas y 3 columnas
matriz[0][0] = 5; // Asignar valor a la posición fila 0, columna 0

// Recorrido y llenado con bucles
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        matriz[i][j] = i + j;
    }
}
```
Java requiere especificar el tipo de datos y las dimensiones. El acceso a elementos se hace con `matriz[fila][columna]`.

---

### C++

En C++, las matrices son arreglos bidimensionales de tamaño fijo o pueden ser dinámicas usando punteros.
Ejemplo básico:
```cpp
int matriz[3][3];
matriz[0][0] = 5;

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        matriz[i][j] = i * j;
    }
}
```
C++ permite usar punteros para crear matrices dinámicamente, pero el ejemplo muestra la forma estática más habitual y clara para ejercicios básicos.

---

### C

En C, las matrices se manejan como arreglos bidimensionales estáticos.
Ejemplo:
```c
int matriz[3][3];
matriz[0][0] = 5;

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        matriz[i][j] = i - j;
    }
}
```
El manejo de memoria es explícito y el acceso a los elementos se hace igual que en C++: `matriz[fila][columna]`.

---

### Python

En Python no existen “matrices” como tipo nativo, pero se pueden simular usando listas anidadas o usar librerías como NumPy para operaciones avanzadas.
Ejemplo con listas anidadas:
```python
matriz = [[0 for j in range(3)] for i in range(3)]
matriz[0][0] = 5

for i in range(3):
    for j in range(3):
        matriz[i][j] = i + j
```
El acceso es igual: `matriz[fila][columna]`. Python es más flexible y permite crear matrices dinámicas fácilmente.

---

## ✅ Conclusiones

- Cada lenguaje tiene su propia forma de declarar y manipular matrices, lo que permite comparar enfoques y comprender mejor la relación entre la lógica computacional y la implementación concreta.
- Java, C y C++ requieren declarar el tamaño y tipo de la matriz; Python es más flexible pero menos estricto.
- Este repositorio sirve como guía y referencia para entender el manejo de matrices en distintos lenguajes y como punto de partida para ejercicios más avanzados en arquitectura de computadores.

---

Desarrollado por Jerixo y colaboradores para fines educativos.
