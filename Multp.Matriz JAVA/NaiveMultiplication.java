public class NaiveMultiplication {
    
    /**
     * Implementación del algoritmo ingenuo (triple bucle) para multiplicación de matrices
     * Complejidad: O(n³)
     */
    public static double[][] multiply(double[][] a, double[][] b) {
        int m = a.length;    // filas de A
        int p = a[0].length; // columnas de A = filas de B
        int n = b[0].length; // columnas de B
        
        // Verificar dimensiones compatibles
        if (a[0].length != b.length) {
            throw new IllegalArgumentException("Dimensiones incompatibles para multiplicación");
        }
        
        double[][] c = new double[m][n];
        
        // Implementación triple bucle
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < p; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        
        return c;
    }
    
    /**
     * Versión optimizada para caché del algoritmo ingenuo (cambiando el orden de los bucles)
     */
    public static double[][] multiplyOptimized(double[][] a, double[][] b) {
        int m = a.length;    // filas de A
        int p = a[0].length; // columnas de A = filas de B
        int n = b[0].length; // columnas de B
        
        // Verificar dimensiones compatibles
        if (a[0].length != b.length) {
            throw new IllegalArgumentException("Dimensiones incompatibles para multiplicación");
        }
        
        double[][] c = new double[m][n];
        
        // Implementación con orden de bucles optimizado para mejor localidad de caché
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < p; k++) {
                for (int j = 0; j < n; j++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        
        return c;
    }
}
