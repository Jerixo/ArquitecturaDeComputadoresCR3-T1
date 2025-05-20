# Arquitectura de Computadores CR3 - Tarea 1

## Finalidad del Repositorio

Este repositorio contiene la implementación y evaluación comparativa de algoritmos clásicos de multiplicación de matrices —Naive y Strassen— desarrollados como parte de la Tarea 1 del curso de Arquitectura de Computadores CR3. El objetivo principal es analizar el impacto del algoritmo, el lenguaje de programación (C, C++, Java, Python) y las características del entorno de ejecución en el rendimiento computacional.

El proyecto permite:

Evaluar la eficiencia algorítmica bajo métricas como tiempo de ejecución y uso de memoria.

Comparar la relación entre modelo de ejecución (compilado vs. interpretado) y el comportamiento real del hardware.

---

## Objetivo

- tiene como objetivo analizar y comparar el comportamiento de dos algoritmos clásicos de multiplicación de matrices: el algoritmo ingenuo (naive) y el algoritmo de Strassen. La implementación se desarrolló en lenguaje C para aprovechar la cercanía al hardware y observar el rendimiento computacional de forma más precisa. Se valuaron aspectos como el tiempo de ejecución y la memoria estimada para diferentes tamaños de matrices cuadradas.

- Comprender cómo se declaran, inicializan y manipulan matrices en Java, C++, C y Python.
- Analizar ventajas, diferencias y particularidades de cada lenguaje al trabajar con estructuras bidimensionales.
- Desarrollar la habilidad de adaptar algoritmos de arquitectura de computadores a diferentes entornos de programación.

---

## 👣 Paso a Paso: ¿Cómo se hizo este repositorio y cada código?

### 1. Selección del ejercicio principal

Se eligió como ejercicio fundamental la creación, llenado y recorrido de matrices, así como la realización de operaciones básicas (como suma de elementos) sobre ellas,
    Desde el punto de vista algorítmico, el método clásico o Naive presenta una complejidad computacional de orden cúbico O(n³), mientras que el algoritmo de Strassen, basado en el paradigma de divide y vencerás, reduce el número de multiplicaciones necesarias, alcanzando una complejidad aproximada de O(n^2.81).
     Experimentalmente, esta mejora teórica se manifiesta parcialmente según el tamaño de las matrices. Para dimensiones pequeñas (por ejemplo, n = 128), ambas técnicas arrojan tiempos comparables debido a que la sobrecarga recursiva de Strassen compensa su ventaja teórica. Sin embargo, a partir de tamaños mayores (n ≥ 512), Strassen comienza a superar consistentemente al algoritmo ingenuo en lenguajes compilados como C y C++. En contraste, en entornos interpretados como Python, los beneficios del algoritmo de Strassen se ven atenuados por la sobrecarga del runtime.


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

- Cada lenguaje tiene su carpeta con el archivo principal de la matriz:
    - `C/`
    - `CPP/`
    - `Multp.Matriz JAVA/`
    - `Python/`
- Estructura clara para facilitar la comparación y reutilización de los códigos.

---

### 5. Documentación

- Este README explica la finalidad, los objetivos, el proceso de desarrollo y el contenido de cada archivo y lenguaje.

---

## 📁 Archivos y carpetas del repositorio

- **C/**  
  - Código en C que llena la matriz con la suma de los índices, la imprime y suma los elementos.
- **CPP/**  
  - Código en C++ que llena la matriz con productos de los índices, la imprime y suma los elementos.
- **Multp.Matriz JAVA/**  
  - Código en Java que llena la matriz con valores del 1 al 9, la imprime y suma los elementos.
- **Python/**  
  - Código en Python que llena la matriz con el cuadrado de la suma de los índices, la imprime y suma los elementos.

---
## Conclusiones del Proyecto
Se implementaron y compararon dos algoritmos de multiplicación de matrices: el algoritmo Naive (clásico de triple bucle) y el algoritmo de Strassen (divide y vencerás), evaluando su rendimiento en C, C++, Java y Python.

El algoritmo Naive demostró ser más eficiente y estable en matrices pequeñas o medianas, debido a su bajo uso de memoria y mejor comportamiento con la jerarquía de caché.

El algoritmo Strassen mostró ventajas en tiempo de ejecución únicamente para matrices grandes (n ≥ 512), a costa de un uso significativamente mayor de memoria y mayor complejidad en su implementación.

Los lenguajes C y C++ ofrecieron el mejor rendimiento gracias a su cercanía al hardware y la posibilidad de aplicar optimizaciones del compilador (-O3). En contraste, Python tuvo el peor desempeño debido a su naturaleza interpretada.

Java, aunque menos eficiente que C++, logró tiempos razonables gracias a la optimización en tiempo de ejecución (JIT), pero con mayor consumo de memoria.

Este proyecto demuestra que la eficiencia algorítmica depende tanto de la complejidad teórica como del entorno de ejecución y el lenguaje utilizado.




Desarrollado por Jerixo y colaboradores para fines educativos.
