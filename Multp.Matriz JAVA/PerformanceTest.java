import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.lang.management.MemoryUsage;

public class PerformanceTest {

    // Tamaños de matrices a probar (potencias de 2)
    private static final int[] MATRIX_SIZES = {128, 256, 512, 1024};
    // Número de repeticiones para cada prueba
    private static final int REPETITIONS = 3;
    // Tolerancia para comparar matrices
    private static final double EPSILON = 1e-9;

    public static void main(String[] args) {
        System.out.println("Iniciando pruebas de rendimiento de multiplicación de matrices en Java");
        System.out.println("==================================================================");
        System.out.println("JVM: " + System.getProperty("java.version"));
        System.out.println("Ejecutar con: java -server PerformanceTest para mejor rendimiento");
        System.out.println("==================================================================\n");

        // Encabezado de la tabla de resultados
        System.out.printf("%-10s %-20s %-20s %-20s\n", "Tamaño", "Algoritmo", "Tiempo (ms)", "Memoria (MB)");
        System.out.println("------------------------------------------------------------------");

        // Probar multiplicación para cada tamaño de matriz
        for (int size : MATRIX_SIZES) {
            // Probar algoritmo de multiplicación ingenua
            testNaiveMultiplication(size);
            // Probar algoritmo de Strassen
            testStrassenMultiplication(size);
            System.out.println(); // Separador entre tamaños
        }
    }

    /**
     * Prueba de rendimiento para el algoritmo de multiplicación ingenua.
     * @param size Tamaño de la matriz a probar.
     */
    private static void testNaiveMultiplication(int size) {
        // Generar matrices aleatorias de entrada
        double[][] a = MatrixUtils.generateRandomMatrix(size, size);
        double[][] b = MatrixUtils.generateRandomMatrix(size, size);

        // Calentar la JVM ejecutando una vez el algoritmo (para asegurar mediciones consistentes)
        NaiveMultiplication.multiply(a, b);

        // Variables para medir rendimiento
        long totalTime = 0; // Tiempo total acumulado
        double peakMemory = 0; // Máxima memoria utilizada

        // Ejecutar varias repeticiones
        for (int i = 0; i < REPETITIONS; i++) {
            System.gc(); // Solicitar recolección de basura para minimizar interferencias

            MemoryMXBean memoryBean = ManagementFactory.getMemoryMXBean(); // Monitoreo de memoria

            // Medir el tiempo de ejecución
            long startTime = System.nanoTime(); // Inicia el cronómetro
            double[][] result = NaiveMultiplication.multiply(a, b); // Realizar la multiplicación
            long endTime = System.nanoTime(); // Termina el cronómetro

            // Obtener uso de memoria después de la ejecución
            MemoryUsage heapMemory = memoryBean.getHeapMemoryUsage();
            double usedMemoryMB = (double) heapMemory.getUsed() / (1024 * 1024); // Convertir a MB

            // Actualizar el pico de memoria si es mayor
            if (usedMemoryMB > peakMemory) {
                peakMemory = usedMemoryMB;
            }

            // Acumular el tiempo de ejecución
            totalTime += (endTime - startTime);
        }

        // Calcular el tiempo promedio en milisegundos
        double averageTime = (double) totalTime / (REPETITIONS * 1_000_000);

        // Imprimir resultados
        System.out.printf("%-10d %-20s %-20.2f %-20.2f\n", size, "Naive", averageTime, peakMemory);
    }

    /**
     * Prueba de rendimiento para el algoritmo de multiplicación de Strassen.
     * @param size Tamaño de la matriz a probar.
     */
    private static void testStrassenMultiplication(int size) {
        // Generar matrices aleatorias de entrada
        double[][] a = MatrixUtils.generateRandomMatrix(size, size);
        double[][] b = MatrixUtils.generateRandomMatrix(size, size);
        // Calcular el resultado esperado usando el algoritmo ingenuo
        double[][] expectedResult = NaiveMultiplication.multiply(a, b);

        // Calentar la JVM ejecutando una vez el algoritmo (si aplica para el tamaño)
        try {
            StrassenMultiplication.multiply(a, b);
        } catch (IllegalArgumentException e) {
            // Si el tamaño no es potencia de 2, imprimir mensaje y finalizar prueba
            System.out.printf("%-10d %-20s %-20s %-20s\n", size, "Strassen", "N/A (requiere potencia de 2)", "N/A");
            return;
        }

        // Variables para medir rendimiento
        long totalTime = 0; // Tiempo total acumulado
        double peakMemory = 0; // Máxima memoria utilizada
        boolean resultCorrect = false; // Verificación de la corrección del resultado

        // Ejecutar varias repeticiones
        for (int i = 0; i < REPETITIONS; i++) {
            System.gc(); // Solicitar recolección de basura

            MemoryMXBean memoryBean = ManagementFactory.getMemoryMXBean(); // Monitoreo de memoria

            // Medir el tiempo de ejecución
            long startTime = System.nanoTime(); // Inicia el cronómetro
            double[][] c = StrassenMultiplication.multiply(a, b); // Realizar la multiplicación
            long endTime = System.nanoTime(); // Termina el cronómetro

            // Obtener uso de memoria después de la ejecución
            MemoryUsage heapMemory = memoryBean.getHeapMemoryUsage();
            double usedMemoryMB = (double) heapMemory.getUsed() / (1024 * 1024); // Convertir a MB

            // Actualizar el pico de memoria si es mayor
            if (usedMemoryMB > peakMemory) {
                peakMemory = usedMemoryMB;
            }

            // Acumular el tiempo de ejecución
            totalTime += (endTime - startTime);

            // Verificar resultado en la primera iteración
            if (i == 0) {
                resultCorrect = MatrixUtils.areMatricesEqual(c, expectedResult, EPSILON);
            }
        }

        // Calcular el tiempo promedio en milisegundos
        double averageTime = (double) totalTime / (REPETITIONS * 1_000_000);

        // Imprimir resultados
        System.out.printf("%-10d %-20s %-20.2f %-20.2f %s\n", 
                size, "Strassen", averageTime, peakMemory, 
                resultCorrect ? "(correcto)" : "(incorrecto)");
    }
}
