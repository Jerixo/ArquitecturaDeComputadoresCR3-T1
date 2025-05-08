# Multiplicación de Matrices en Java

Este proyecto implementa y compara diferentes algoritmos de multiplicación de matrices en Java, proporcionando herramientas para generar matrices, realizar multiplicaciones utilizando distintos métodos, validar los resultados y medir el rendimiento.

## Objetivo

El objetivo principal del programa es analizar y comparar el rendimiento de dos algoritmos de multiplicación de matrices:
1. **Multiplicación Ingenua (Naive Multiplication)**: Utiliza un enfoque básico de tres bucles anidados.
2. **Multiplicación de Strassen**: Un algoritmo más avanzado y eficiente que reduce la complejidad computacional.

## Estructura del Proyecto

El proyecto contiene los siguientes archivos principales:

### Archivos
1. **`MatrixUtils.java`**:
   Este archivo contiene métodos de utilidad para matrices. Ejemplo de generación de matrices aleatorias:
   ```java
   public static double[][] generateRandomMatrix(int rows, int cols) {
       Random random = new Random();
       double[][] matrix = new double[rows][cols];
       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < cols; j++) {
               matrix[i][j] = random.nextDouble() * 10;
           }
       }
       return matrix;
   }
   ```
    - Genera matrices aleatorias con valores entre 0 y 10.
    - Compara dos matrices para verificar si son iguales dentro de un margen de error.
    - Imprime matrices en la consola para facilitar la depuración.
    
2. **`NaiveMultiplication.java`**:
   Implementa el algoritmo ingenuo para la multiplicación de matrices:
   ```java
   public static double[][] multiply(double[][] a, double[][] b) {
       int m = a.length;
       int p = a[0].length;
       int n = b[0].length;

       if (a[0].length != b.length) {
           throw new IllegalArgumentException("Dimensiones incompatibles para multiplicación");
       }

       double[][] c = new double[m][n];
       for (int i = 0; i < m; i++) {
           for (int j = 0; j < n; j++) {
               for (int k = 0; k < p; k++) {
                   c[i][j] += a[i][k] * b[k][j];
               }
           }
       }
       return c;
   }
   ```
    - Este archivo implementa dos versiones del algoritmo de multiplicación de matrices:

      - `multiply`: Es el método básico que utiliza un triple bucle para calcular el producto de dos matrices (complejidad O(n³)).
      - `multiplyOptimized`: Es una versión optimizada que altera el orden de los bucles para aprovechar mejor la memoria caché.
   
    *Rol en el sistema*: Implementa el algoritmo estándar para la multiplicación de matrices, proporcionando una solución simple pero eficiente para tamaños pequeños.
  
4. **`StrassenMultiplication.java`**:
   Utiliza el algoritmo de Strassen para multiplicar matrices más grandes de manera eficiente:
   ```java
   public static double[][] multiply(double[][] a, double[][] b) {
       int n = a.length;
       if (n <= CUTOFF) {
           return NaiveMultiplication.multiply(a, b);
       }
       return strassenMultiply(a, b);
   }
   ```
    - Este archivo implementa el algoritmo de Strassen, que es una técnica más avanzada y eficiente para multiplicar matrices (complejidad O(n^2.807)):

        - Divide las matrices en submatrices más pequeñas y utiliza una combinación de operaciones de suma, resta y multiplicación para calcular el resultado.
        - Incluye un umbral (CUTOFF) que determina cuándo usar el algoritmo ingenuo en lugar del de Strassen.
        - Utiliza un enfoque recursivo y cambia al algoritmo ingenuo para matrices pequeñas.
  
    *Rol en el sistema*: Proporciona una alternativa más eficiente para multiplicar matrices grandes, especialmente cuando los tamaños son potencias de 2.

5. **`PerformanceTest.java`**:
   Realiza pruebas de rendimiento y mide el tiempo de ejecución y el uso de memoria para los algoritmos:
   ```java
   public static void main(String[] args) {
       for (int size : MATRIX_SIZES) {
           testNaiveMultiplication(size);
           testStrassenMultiplication(size);
       }
   }
   ```
    - Este archivo ejecuta pruebas de rendimiento para comparar los algoritmos de multiplicación:
    
      - Genera matrices aleatorias utilizando `MatrixUtils`.
      - Evalúa la eficiencia (tiempo de ejecución y uso de memoria) de los algoritmos (ingenuo (triple bucle) vs Algoritmo de Strassen) en matrices de diferentes tamaños.
      - Incluye pruebas para los métodos de multiplicación ingenua (Complejidad: Θ(n³)) y multiplicación de Strassen (Complejidad aproximada: O(n^2.807)), mostrando sus resultados en la consola.
        
    *Rol en el sistema*: Actúa como un banco de pruebas que mide la velocidad y el consumo de recursos de los algoritmos implementados.

## Cómo Ejecutar el Programa

### Requisitos Previos
- Tener instalado Java (versión 8 o superior).
- Un IDE como IntelliJ IDEA, Eclipse, o simplemente una terminal con `javac` y `java` en el sistema operativo.

### Pasos
1. **Clonar el repositorio**:
   ```bash
   git clone https://github.com/SantiagoRodriguez114/ArquitecturaDeComputadoresCR3-T1.git
   cd ArquitecturaDeComputadoresCR3-T1/Multp.Matriz\ JAVA
   ```

2. **Compilar los archivos Java**:
   ```bash
   javac *.java
   ```

3. **Ejecutar las pruebas de rendimiento**:
   ```bash
   java PerformanceTest
   ```

4. **Resultados esperados**:
   Una tabla que muestra el tiempo de ejecución y el uso de memoria para diferentes tamaños de matrices y algoritmos.

### Personalización
- Puedes modificar los tamaños de las matrices a probar en el archivo `PerformanceTest.java`, ajustando la variable `MATRIX_SIZES`.

## Notas Relevantes
- El algoritmo de Strassen requiere que las matrices sean cuadradas y de un tamaño que sea potencia de 2. Si no es así, el programa mostrará un mensaje de error.
- Para obtener mejores resultados de rendimiento, ejecutar el programa con el comando:
  ```bash
  java -server PerformanceTest
  ```

## Ejemplo de Salida
```plaintext
Iniciando pruebas de rendimiento de multiplicación de matrices en Java
==================================================================
JVM: 11.0.16
Ejecutar con: java -server PerformanceTest para mejor rendimiento
==================================================================

Tamaño     Algoritmo            Tiempo (ms)          Memoria (MB)
------------------------------------------------------------------
128        Naive                3,63                 1.28
128        Strassen             6,53                 2.05
256        Naive                31.10                2.08
256        Strassen             23.57                14,60
...
```
