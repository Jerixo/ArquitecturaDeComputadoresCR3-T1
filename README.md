# Arquitectura de Computadores CR3 - Tarea 1

## 📝 Finalidad del Repositorio

Este repositorio reúne los ejercicios desarrollados para la Tarea 1 del curso de Arquitectura de Computadores CR3. El objetivo es mostrar, de manera comparativa, cómo se implementan y manipulan matrices en distintos lenguajes de programación, permitiendo analizar las diferencias en sintaxis, lógica y funcionamiento.

---

## 🎯 Objetivo

- Comprender cómo se declaran, inicializan y manipulan matrices en Java, C++, C y Python.
- Analizar ventajas, diferencias y particularidades de cada lenguaje al trabajar con estructuras bidimensionales.
- Desarrollar la habilidad de adaptar algoritmos de arquitectura de computadores a diferentes entornos de programación.

---

## 👣 Paso a Paso: ¿Cómo se hizo este repositorio?

1. **Selección de ejercicios:**  
   Se seleccionaron problemas fundamentales relacionados con el manejo de matrices, operaciones aritméticas y lógica computacional.

2. **Implementación en varios lenguajes:**  
   Cada ejercicio fue resuelto en Java, C++, C y Python, aplicando las mejores prácticas y características propias de cada lenguaje.

3. **Pruebas y comparación:**  
   Se ejecutaron los programas para garantizar equivalencia en resultados y se documentaron diferencias relevantes.

4. **Organización:**  
   Los archivos se estructuraron en carpetas por lenguaje, facilitando la navegación y comparación.

5. **Documentación:**  
   Se elaboró este README detallando el objetivo, la finalidad, el proceso y el contenido del repositorio.

---

## 📁 Archivos y carpetas del repositorio

- **Java/**  
  - `MatrizPrincipal.java`: Programa principal que muestra creación, llenado, recorrido y operaciones con matrices en Java.

- **C++/**  
  - `matriz_principal.cpp`: Implementación principal de matrices en C++, con ejemplos de llenado, suma y recorrido.

- **C/**  
  - `matriz_principal.c`: Ejemplo de manejo de matrices en C, mostrando funciones básicas para manipulación y visualización.

- **Python/**  
  - `matriz_principal.py`: Script principal en Python para trabajar con listas anidadas (matrices), mostrando operaciones y ejemplos.

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
