#include <iostream>  // Biblioteca para la entrada y salida estándar (cout, endl, etc.)
#include <omp.h>     // Biblioteca para trabajar con OpenMP y paralelismo

// Definimos constantes
#define N 10000      // Tamaño de los arreglos
#define chunk 1000   // Tamaño de los bloques para distribuir las iteraciones
#define mostrar 40   // Número de elementos a mostrar de los arreglos

// Declaración de una función para imprimir un arreglo
void imprimeArreglo(float *d);

int main()
{
    // Mensaje inicial
    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Declaración de arreglos de tamaño N
    float a[N], b[N], c[N];  // Arreglo a, b y c (donde c será la suma de a y b)
    int i;                   // Variable para el bucle

    // Inicialización de los arreglos a y b con valores específicos
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;               // Cada elemento de 'a' se inicializa como i * 10
        b[i] = (i + 3) * 3.7;        // Cada elemento de 'b' se inicializa como (i+3) * 3.7
    }

    int pedazos = chunk; // Tamaño de los bloques para el paralelismo

    // Bucle paralelo con OpenMP
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++)          // Cada iteración calcula c[i] = a[i] + b[i]
        c[i] = a[i] + b[i];

    // Imprimir los primeros 'mostrar' elementos de cada arreglo
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);  // Llamada a la función para imprimir el arreglo 'a'

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);  // Llamada a la función para imprimir el arreglo 'b'

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);  // Llamada a la función para imprimir el arreglo 'c'

    return 0; // Fin del programa principal
}

// Función para imprimir un arreglo
void imprimeArreglo(float *d)
{
    for (int x = 0; x < mostrar; x++) // Iteramos sobre los primeros 'mostrar' elementos
        std::cout << d[x] << " - ";   // Imprimimos el elemento seguido de un guion
    std::cout << std::endl;           // Salto de línea al final
}
