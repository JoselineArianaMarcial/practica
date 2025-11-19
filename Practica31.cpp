#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
char *texto = NULL;
size_t tam = 100;     // tama inicial del buffer
size_t longitud = 0;  // longitud actual del texto

// Prototipos de funciones
void inicializar();
void insertarTexto();
void mostrarTexto();
void buscarYReemplazar();
void mostrarUsoMemoria();

int main() {
    int opcion;
    inicializar();

    do {
        printf("\n-- MENU PRINCIPAL --\n");
        printf("1. Insertar texto\n");
        printf("2. Mostrar texto\n");
        printf("3. Buscar y reemplazar\n");
        printf("4. Mostrar uso de memoria\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1:
                insertarTexto();
                break;
            case 2:
                mostrarTexto();
                break;
            case 3:
                buscarYReemplazar();
                break;
            case 4:
                mostrarUsoMemoria();
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 5);

    free(texto); // liberar memoria al salir
    return 0;
}


void inicializar() {
    texto = (char *)malloc(tam);
    if (!texto) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    texto[0] = '\0';
}

void insertarTexto() {
    char entrada[200];
    printf("Ingrese el texto a insertar:\n");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // eliminar salto 

    size_t len = strlen(entrada);
    if (longitud + len + 1 >= tam) {
        tam *= 2;
        texto = (char *)realloc(texto, tam);
        if (!texto) {
            printf("Error al redimensionar memoria.\n");
            exit(1);
        }
        printf("Memoria aumentada a %zu bytes.\n", tam);
    }

    strcat(texto, entrada);
    longitud += len;
    printf("Texto insertado (%zu caracteres).\n", longitud);
}

void mostrarTexto() {
    printf("\n--- TEXTO ACTUAL ---\n");
    if (longitud == 0)
        printf("(Vacio)\n");
    else
        printf("%s\n", texto);
}

void buscarYReemplazar() {
    char buscar[50], reemplazar[50];
    printf("Ingrese el texto a buscar: ");
    fgets(buscar, sizeof(buscar), stdin);
    buscar[strcspn(buscar, "\n")] = '\0';

    printf("Ingrese el texto de reemplazo: ");
    fgets(reemplazar, sizeof(reemplazar), stdin);
    reemplazar[strcspn(reemplazar, "\n")] = '\0';

    char *pos, *resultado;
    int ocurrencias = 0;
    size_t lenBuscar = strlen(buscar);
    size_t lenReemplazar = strlen(reemplazar);

    // Contar ocurrencias
    pos = texto;
    while ((pos = strstr(pos, buscar)) != NULL) {
        ocurrencias++;
        pos += lenBuscar;
    }

    if (ocurrencias == 0) {
        printf("No se encontro el texto '%s'.\n", buscar);
        return;
    }

    // Calcular tamaño nuevo y reservar memoria
    resultado = (char *)malloc(strlen(texto) + ocurrencias * (lenReemplazar - lenBuscar) + 1);
    if (!resultado) {
        printf("Error al asignar memoria para el texto nuevo.\n");
        exit(1);
    }

    // Reemplazar texto
    char *ptrResultado = resultado;
    pos = texto;
    while (*pos) {
        if (strstr(pos, buscar) == pos) {
            strcpy(ptrResultado, reemplazar);
            ptrResultado += lenReemplazar;
            pos += lenBuscar;
        } else {
            *ptrResultado++ = *pos++;
        }
    }
    *ptrResultado = '\0';

    // Actualizar texto original
    free(texto);
    texto = resultado;
    longitud = strlen(texto);

    printf("Reemplazo completado (%d ocurrencias).\n", ocurrencias);
    printf("Texto final: %s\n", texto);
}

void mostrarUsoMemoria() {
    printf("\n--- USO DE MEMORIA ---\n");
    printf("Tam total asignado: %zu bytes\n", tam);
    printf("Texto utilizado: %zu caracteres\n", longitud);
    printf("Espacio libre: %zu bytes\n", tam - longitud);
}

