# Benchmark de Algoritmos de Multiplicación de Matrices en Python

Este proyecto implementa y compara tres algoritmos clásicos de multiplicación de matrices:

- **Naive** (clásico)
- **Blocked** (bloques de submatrices)
- **Strassen** (divide y vencerás)

Se miden **tiempos de ejecución** y **uso de memoria** para diferentes tamaños de matrices cuadradas. Los resultados se guardan en un archivo CSV y se visualizan mediante gráficos.

---

##  Estructura del Proyecto

- `main.py`: contiene todas las funciones, benchmarks y ejecución principal.
- `benchmark_results.csv`: archivo generado automáticamente con los resultados.
- Gráfico de rendimiento mostrado al finalizar la ejecución.

---

##  Requisitos

Asegúrate de tener Python 3.8 o superior.

### Dependencias

Instálalas con pip:

```bash
pip install matplotlib
```

---

##  Cómo Ejecutar

1. Clona o descarga este repositorio.
2. Abre una terminal en el directorio raíz.
3. Ejecuta el script:

```bash
python main.py
```

Esto:
- Ejecutará benchmarks para tamaños `[128, 256, 512, 1024]`.
- Generará un archivo `benchmark_results.csv`.
- Mostrará un gráfico comparativo de tiempo de ejecución por algoritmo.

---

##  Ejemplo de Resultados

| n    | algoritmo | tiempo (ms) | memoria (MB) |
|------|-----------|-------------|---------------|
128    | naive     | 78.6882593333785   | 0.5015869140625
128    | blocked   | 81.5762549999692   | 0.501678466796875
128    | strassen  | 868.5776410000017  | 2.098175048828125
256    | naive     | 560.756495666634   | 2.0094606876132812
256    | blocked   | 576.945813333387   | 2.00958251953125
256    | strassen  | 6109.14992233333   | 8.196495056152344
512    | naive     | 5026.90234433337   | 8.025291442871094
512    | blocked   | 5182.42342666676   | 8.025497436523438
512    | strassen  | 45596.23906266675  | 32.49197006225586
1024   | naive     | 45544.32537733356  | 32.05706024169922
1024   | blocked   | 46927.35164299996  | 32.05726623535156
1024   | strassen  | 326773.3232693333  | 128.91324996948242


---

##  Análisis de Rendimiento

- **Naive** y **Blocked** tienen un comportamiento muy similar en tiempo y memoria.
- **Strassen**, aunque teóricamente más eficiente para grandes tamaños, es más **lento y demandante en memoria** en esta implementación.
- Strassen no es recomendable para tamaños menores a 2048 sin optimizaciones.

---

## 📎 Notas Técnicas

- El algoritmo Strassen incluye padding a potencias de 2.
- La verificación de exactitud entre algoritmos se hace con una tolerancia de `1e-6`.
- `tracemalloc` se utiliza para medir memoria pico de forma precisa.

---
