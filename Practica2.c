#include <stdio.h>

#define MAX_TEXTO 1000

// funciones
void llenarTexto(char *texto);
void mostrarTexto(const char *texto);
void buscarYReemplazar(char *texto, const char *buscar, const char *reemplazar);
int longitudCadena(const char *cadena);
int compararCadenas(const char *cadena1, const char *cadena2);
void copiarCadena(char *destino, const char *origen);
void concatenarCadenas(char *destino, const char *origen);
int buscarSubcadena(const char *texto, const char *subcadena);
void mostrarBusqueda(const char *texto, const char *buscar);
void mostrarReemplazo(const char *reemplazar);

int main() {
    char texto[MAX_TEXTO] = "";
    char buscar[100];
    char reemplazar[100];
    int opcion;
    
    printf("\n**********************\n");
    
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Llenar texto\n");
        printf("2. Mostrar texto actual\n");
        printf("3. Buscar texto\n");
        printf("4. Reemplazar texto\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();      

        switch(opcion) {
            case 1:
                llenarTexto(texto);
                break;
                
            case 2:
                mostrarTexto(texto);
                break;
                
            case 3:
                if (longitudCadena(texto) == 0) {
                    printf("El texto esta vacio.\n");
                    break;
                }
                printf("Ingrese el texto para buscar: ");
                fgets(buscar, sizeof(buscar), stdin);
                for(int i = 0; buscar[i] != '\0'; i++) {
                    if(buscar[i] == '\n') {
                        buscar[i] = '\0';
                        break;
                    }
                }

                printf("\n--- BUSQUEDA DE TEXTO ---\n");
                mostrarTexto(texto);
                mostrarBusqueda(texto, buscar);
                break;

            case 4:
                if (longitudCadena(texto) == 0) {
                    printf("El texto esta vacio.\n");
                    break;
                }

                printf("Ingrese el texto a buscar: ");
                fgets(buscar, sizeof(buscar), stdin);
                for(int i = 0; buscar[i] != '\0'; i++) {
                    if(buscar[i] == '\n') {
                        buscar[i] = '\0';
                        break;
                    }
                }

                printf("Ingrese el texto de reemplazo: ");
                fgets(reemplazar, sizeof(reemplazar), stdin);
                for(int i = 0; reemplazar[i] != '\0'; i++) {
                    if(reemplazar[i] == '\n') {
                        reemplazar[i] = '\0';
                        break;
                    }
                }

                printf("\n--- REEMPLAZO DE TEXTO ---\n");
                mostrarTexto(texto);
                mostrarReemplazo(reemplazar);
                buscarYReemplazar(texto, buscar, reemplazar);
                
                printf("\n--- TEXTO FINAL ---\n");
                mostrarTexto(texto);
                break;

            case 5:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
        
    } while(opcion != 5);
    
    return 0;
}

// Funcion calcula la longitud de cadena
int longitudCadena(const char *cadena) {
    int longitud = 0;
    while(*cadena != '\0') {
        longitud++;
        cadena++;
    }
    return longitud;
}

// Funcion compara dos cadenas
int compararCadenas(const char *cadena1, const char *cadena2) {
    while(*cadena1 != '\0' && *cadena2 != '\0') {
        if(*cadena1 != *cadena2) {
            return 0;
        }
        cadena1++;
        cadena2++;
    }
    return (*cadena1 == '\0' && *cadena2 == '\0');
}

// Funcion para copiar una cadena
void copiarCadena(char *destino, const char *origen) {
    while(*origen != '\0') {
        *destino = *origen;
        destino++;
        origen++;
    }
    *destino = '\0';
}

// Funcion para concatenar cadenas
void concatenarCadenas(char *destino, const char *origen) {
    while(*destino != '\0') {
        destino++;
    }
    while(*origen != '\0') {
        *destino = *origen;
        destino++;
        origen++;
    }
    *destino = '\0';
}

// Funcion para llenar el texto
void llenarTexto(char *texto) {
    printf("Ingrese el texto :\n", MAX_TEXTO - 1);
    fgets(texto, MAX_TEXTO, stdin);
    for(int i = 0; texto[i] != '\0'; i++) {
        if(texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
    printf("Texto guardado exitosamente.\n");
}

// Funcion para mostrar el texto completo
void mostrarTexto(const char *texto) {
    printf("\n--- TEXTO ACTUAL ---\n");
    if (longitudCadena(texto) == 0) {
        printf("El texto esta vacio.\n");
    } else {
        printf("%s\n", texto);
    }
    printf("Longitud: %d caracteres\n", longitudCadena(texto));
}

// Funcion para buscar una subcadena
int buscarSubcadena(const char *texto, const char *subcadena) {
    int len_texto = longitudCadena(texto);
    int len_sub = longitudCadena(subcadena);
    
    if(len_sub == 0) return 0;
    
    for(int i = 0; i <= len_texto - len_sub; i++) {
        int encontrado = 1;
        for(int j = 0; j < len_sub; j++) {
            if(texto[i + j] != subcadena[j]) {
                encontrado = 0;
                break;
            }
        }
        if(encontrado) {
            return i;
        }
    }
    return -1;
}

// Funcion buscar y reemplazar
void buscarYReemplazar(char *texto, const char *buscar, const char *reemplazar) {
    char buffer[MAX_TEXTO];
    int len_buscar = longitudCadena(buscar);
    int len_reemplazar = longitudCadena(reemplazar);
    int contador = 0;
    
    if (len_buscar == 0) {
        printf("Error: El texto a buscar no puede estar vacio.\n");
        return;
    }
    
    if (buscarSubcadena(texto, buscar) == -1) {
        printf("El texto '%s' no fue encontrado.\n", buscar);
        return;
    }
    
    buffer[0] = '\0';
    int i = 0;
    while(texto[i] != '\0') {
        int coincide = 1;
        for(int j = 0; j < len_buscar; j++) {
            if(texto[i + j] != buscar[j] || texto[i + j] == '\0') {
                coincide = 0;
                break;
            }
        }
        
        if(coincide) {
            concatenarCadenas(buffer, reemplazar);
            i += len_buscar;
            contador++;
        } else {
            char temp[2] = {texto[i], '\0'};
            concatenarCadenas(buffer, temp);
            i++;
        }
    }
    
    if (longitudCadena(buffer) < MAX_TEXTO) {
        copiarCadena(texto, buffer);
        printf("Reemplazo completado. Se reemplazaron %d ocurrencias.\n", contador);
    } else {
        printf("Error: El texto resultante excede el tamaño maximo permitido.\n");
    }
}

// Funcion para mostrar el texto a buscar
void mostrarBusqueda(const char *texto, const char *buscar) {
    printf("\n--- TEXTO A BUSCAR ---\n");
    printf("'%s'\n", buscar);
    
    int len_buscar = longitudCadena(buscar);
    int len_texto = longitudCadena(texto);
    int contador = 0;
    
    printf("Posiciones encontradas: ");
    
    for(int i = 0; i <= len_texto - len_buscar; i++) {
        int encontrado = 1;
        for(int j = 0; j < len_buscar; j++) {
            if(texto[i + j] != buscar[j]) {
                encontrado = 0;
                break;
            }
        }
        if(encontrado) {
            printf("%d ", i);
            contador++;
        }
    }
    
    if (contador == 0) {
        printf("No encontrado");
    }
    printf("\nTotal de ocurrencias: %d\n", contador);
}

// Funcion para mostrar el texto de reemplazo
void mostrarReemplazo(const char *reemplazar) {
    printf("\n--- TEXTO DE REEMPLAZO ---\n");
    printf("'%s'\n", reemplazar);
    printf("Longitud: %d caracteres\n", longitudCadena(reemplazar));
}

