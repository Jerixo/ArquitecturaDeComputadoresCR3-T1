public class StrassenMultiplication {
    
    private static final int CUTOFF = 64; // Umbral para cambiar al algoritmo ingenuo
    
    /**
     * Método principal para multiplicación de Strassen
     * Complejidad aproximada: O(n^2.807)
     */
    public static double[][] multiply(double[][] a, double[][] b) {
        // Verificar que las matrices sean cuadradas y de dimensiones potencia de 2
        int n = a.length;
        
        if (n != a[0].length || n != b.length || n != b[0].length) {
            throw new IllegalArgumentException("Las matrices deben ser cuadradas");
        }
        
        if ((n & (n - 1)) != 0) {
            throw new IllegalArgumentException("Las dimensiones deben ser potencia de 2");
        }
        
        return strassenMultiply(a, b);
    }
    
    /**
     * Método recursivo de multiplicación de Strassen
     */
    private static double[][] strassenMultiply(double[][] a, double[][] b) {
        int n = a.length;
        
        // Caso base: si la matriz es pequeña, usar algoritmo ingenuo
        if (n <= CUTOFF) {
            return NaiveMultiplication.multiply(a, b);
        }
        
        int halfSize = n / 2;
        
        // Dividir las matrices en submatrices
        double[][] a11 = new double[halfSize][halfSize];
        double[][] a12 = new double[halfSize][halfSize];
        double[][] a21 = new double[halfSize][halfSize];
        double[][] a22 = new double[halfSize][halfSize];
        
        double[][] b11 = new double[halfSize][halfSize];
        double[][] b12 = new double[halfSize][halfSize];
        double[][] b21 = new double[halfSize][halfSize];
        double[][] b22 = new double[halfSize][halfSize];
        
        // Copiar datos a las submatrices
        splitMatrix(a, a11, a12, a21, a22);
        splitMatrix(b, b11, b12, b21, b22);
        
        // Calcular las 7 multiplicaciones de Strassen
        double[][] m1 = strassenMultiply(add(a11, a22), add(b11, b22));
        double[][] m2 = strassenMultiply(add(a21, a22), b11);
        double[][] m3 = strassenMultiply(a11, subtract(b12, b22));
        double[][] m4 = strassenMultiply(a22, subtract(b21, b11));
        double[][] m5 = strassenMultiply(add(a11, a12), b22);
        double[][] m6 = strassenMultiply(subtract(a21, a11), add(b11, b12));
        double[][] m7 = strassenMultiply(subtract(a12, a22), add(b21, b22));
        
        // Calcular submatrices del resultado
        double[][] c11 = add(subtract(add(m1, m4), m5), m7);
        double[][] c12 = add(m3, m5);
        double[][] c21 = add(m2, m4);
        double[][] c22 = add(subtract(add(m1, m3), m2), m6);
        
        // Combinar submatrices en el resultado final
        return combineMatrices(c11, c12, c21, c22);
    }
    
    /**
     * Divide una matriz en cuatro submatrices
     */
    private static void splitMatrix(double[][] original, double[][] a11, double[][] a12, double[][] a21, double[][] a22) {
        int halfSize = original.length / 2;
        
        for (int i = 0; i < halfSize; i++) {
            for (int j = 0; j < halfSize; j++) {
                a11[i][j] = original[i][j];
                a12[i][j] = original[i][j + halfSize];
                a21[i][j] = original[i + halfSize][j];
                a22[i][j] = original[i + halfSize][j + halfSize];
            }
        }
    }
    
    /**
     * Combina cuatro submatrices en una matriz
     */
    private static double[][] combineMatrices(double[][] c11, double[][] c12, double[][] c21, double[][] c22) {
        int halfSize = c11.length;
        int fullSize = halfSize * 2;
        double[][] result = new double[fullSize][fullSize];
        
        for (int i = 0; i < halfSize; i++) {
            for (int j = 0; j < halfSize; j++) {
                result[i][j] = c11[i][j];
                result[i][j + halfSize] = c12[i][j];
                result[i + halfSize][j] = c21[i][j];
                result[i + halfSize][j + halfSize] = c22[i][j];
            }
        }
        
        return result;
    }
    
    /**
     * Suma dos matrices
     */
    private static double[][] add(double[][] a, double[][] b) {
        int n = a.length;
        double[][] result = new double[n][n];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = a[i][j] + b[i][j];
            }
        }
        
        return result;
    }
    
    /**
     * Resta dos matrices
     */
    private static double[][] subtract(double[][] a, double[][] b) {
        int n = a.length;
        double[][] result = new double[n][n];
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = a[i][j] - b[i][j];
            }
        }
        
        return result;
    }
}
