#include <iostream>
#include <cstdlib> //para funciones de numero aleatorioss
#include <ctime> //para establecer la semilla de numeros aleatorios
#include <iomanip> //para controlar el formato de salida

using namespace std;
//declaracion de funciones para utilizarlas en el main y no tener todo el codigo en la funcion principal
void llenar_matriz(int matriz[][10], int tam);
void mostrar_matriz(int matriz[][10], int tam, string titulo);
int suma_total(int matriz[][10], int tam);
void contar_pares_impares(int matriz[][10], int tam, int &pares, int &impares);
int contar_divisibles_siete(int matriz[][10], int tam);
void mostrar_transpuesta(int matriz[][10], int tam);
void mostrar_resultados(int matriz[][10], int tam);

int main() {
    srand(time(0)); //semilla para generar numero aleatorios basados en el tiempo actual y cada que se ejecute los numeos cambian
    int tam;
    int matriz[10][10];
    
    do {
        cout << "\nIngrese el tamano de la matriz 1-10: ";
        cin >> tam;
    
    } while ((tam < 1 || tam > 10) && cout<<"Error seleccione del 1-10"); //condicion de la matriz correctamente si no vuelve a preguntar 
    
    llenar_matriz(matriz, tam);
    mostrar_matriz(matriz, tam, "Matriz");
    mostrar_resultados(matriz, tam);
    mostrar_transpuesta(matriz, tam);
    
    return 0;
}

void llenar_matriz(int matriz[][10], int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matriz[i][j] = rand() % 100 + 1;    // para generar números dentro del rango
        }
    }
}

void mostrar_matriz(int matriz[][10], int tam, string titulo) {
    cout << "\n" << titulo << ":";
    cout << "\n" << string(tam* 6, '-'); // imprime una linea de guiones para formato.
    
    for (int i = 0; i < tam; i++) {
        cout << "\n";
        for (int j = 0; j < tam; j++) {
            cout << setw(4) << matriz[i][j] << " "; // Muestra cada numero con un espacio de 4 caracteres
        }
    }
    cout << "\n" << string(tam * 6, '-');
}

int suma_total(int matriz[][10], int tam) {
    int suma = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            suma += matriz[i][j]; // Suma todos los elementos de la matriz
        }
    }
    return suma;
}

void contar_pares_impares(int matriz[][10], int tam, int &pares, int &impares) {
    pares = 0;
    impares = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (matriz[i][j] % 2 == 0) {
                pares++;  // Si el número es par, incrementa el contador de pares.
            } else {
                impares++;  //// Si es impar, incrementa el contador de impares.
            }
        }
    }
}

int contar_divisibles_siete(int matriz[][10], int tam) {
    int count = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (matriz[i][j] % 7 == 0) {
                count++;  //// Cuenta cuántos números son divisibles por siete
            }
        }
    }
    return count;
}

void mostrar_transpuesta(int matriz[][10], int tam) {
    int transpuesta[10][10];
    
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            transpuesta[j][i] = matriz[i][j];  //cambia las filas por columnas
        }
    }
    
    mostrar_matriz(transpuesta, tam, "\nMatriz transpuest");
}
void mostrar_resultados(int matriz[][10], int tam) {
    int suma = suma_total(matriz, tam);
    int pares, impares;
    int divisibles_siete = contar_divisibles_siete(matriz, tam);
    
    contar_pares_impares(matriz, tam, pares, impares);
    
    cout << "\nResultados\n";
    cout << "\n--------------\n";
    cout << "\nSuma total de elementos: " << suma;
    cout << "\nCantidad de elementos pares: " << pares;
    cout << "\nCantidad de elementos impares: " << impares;
    cout << "\nCantidad de elementos divisibles entre siete: " << divisibles_siete;
    cout << "\nTotal de elementos: " << tam * tam;
}
