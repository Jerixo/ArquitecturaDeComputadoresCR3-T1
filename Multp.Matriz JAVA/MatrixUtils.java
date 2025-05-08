import java.util.Random;

public class MatrixUtils {
    
    /**
     * Genera una matriz aleatoria de tipo double con valores entre 0 y 10.
     * @param rows Número de filas de la matriz.
     * @param cols Número de columnas de la matriz.
     * @return Una matriz 2D de tamaño [rows x cols] con valores aleatorios.
     */
    public static double[][] generateRandomMatrix(int rows, int cols) {
        // Inicializar generador de números aleatorios
        Random random = new Random();
        // Crear matriz con el tamaño especificado
        double[][] matrix = new double[rows][cols];
        
        // Llenar la matriz con valores aleatorios entre 0 y 10
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = random.nextDouble() * 10;
            }
        }
        
        return matrix;
    }
    
    /**
     * Verifica si dos matrices son iguales dentro de un margen de error especificado.
     * @param a Primera matriz.
     * @param b Segunda matriz.
     * @param epsilon Margen de error permitido.
     * @return true si las matrices son iguales dentro del margen de error, false en caso contrario.
     */
    public static boolean areMatricesEqual(double[][] a, double[][] b, double epsilon) {
        // Verificar si las dimensiones de las matrices son diferentes
        if (a.length != b.length || a[0].length != b[0].length) {
            return false;
        }
        
        // Comparar elemento por elemento dentro del margen de error
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a[0].length; j++) {
                if (Math.abs(a[i][j] - b[i][j]) > epsilon) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    /**
     * Imprime una matriz en la consola. Útil para depuración.
     * @param matrix Matriz a imprimir.
     */
    public static void printMatrix(double[][] matrix) {
        // Recorrer filas y columnas de la matriz para imprimir sus valores
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                System.out.printf("%.2f\t", matrix[i][j]);
            }
            System.out.println();
        }
    }
}
