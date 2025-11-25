#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  

#define MAX_TEXTO 500  // Tama del buffer de texto

// Estructura para almacenar información de cada persona
typedef struct {
    int id;             // Identificador
    char nombre[50];    // Nombre de la persona
    char cargo[50];     // Cargo de la persona
} Persona;

char* crearTexto();                             // Crear texto base
void editarTexto(char *buffer);                 // Modificar el texto existente
Persona* registrarPersonas(int *total);        // Registrar personas y cargos
//void mostrarMezcla(Persona *lista, int total, char *texto); // Mostrar texto personalizado con cada persona//
void mostrarTabla(Persona *lista, int total, char *texto);   // Mostrar tabla con personas y mensaje

int main() {
    char *texto = NULL;     // Puntero para almacenar el texto creado
    Persona *lista = NULL;  // Puntero a arreglo dinamico
    int total = 0;          
    int opcion;             

    do {
        // Mostrar menu
        printf("\n---Menu---\n");
        printf("1. Crear texto\n");
        printf("2. Modificar texto\n");
        printf("3. Registrar personas y cargo\n");
        printf("4. Mostar Informacion\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar buffer de entrada

        switch (opcion) {
            case 1:
                // Llamar a la función para crear el texto base
                texto = crearTexto();
                break;

            case 2:
                // Modificar el texto solo si ya fue creado
                if (texto)
                    editarTexto(texto);
                else
                    printf("Primero debe crear un texto.\n");
                break;

            case 3:
                // Registrar personas y sus cargos
                lista = registrarPersonas(&total);
                break;

            case 4:
                // Mostrar tabla con personas y el mensaje base
                mostrarTabla(lista, total, texto);
                break;

            case 5:
                printf("Saliendo\n");
                break;

            default:
                printf("Opcion invalida saliendo.\n");
        }

    } while (opcion != 5); // Repetir hasta que se seleccione salir

    // Liberar memoria dinámica antes de terminar
    if (texto) free(texto);
    if (lista) free(lista);

    return 0;
}

char* crearTexto() {
    // Reservar memoria para el buffer del texto
    char *buffer = (char*) malloc(MAX_TEXTO);

    printf("\nEscriba el texto base:\n ");
    fgets(buffer, MAX_TEXTO, stdin);                   // Leer texto con espacios
    buffer[strcspn(buffer, "\n")] = '\0';             // Eliminar el salto de linea

    printf("Texto guardado.\n");
    return buffer;  // Retornar puntero al texto creado
}

void editarTexto(char *buffer) {
    printf("\nTexto actual:\n%s\n", buffer);
    printf("Escriba el nuevo texto:\n ");
    fgets(buffer, MAX_TEXTO, stdin);                  // Leer nuevo texto
    buffer[strcspn(buffer, "\n")] = '\0';             

    printf("Texto modificado.\n");
}

Persona* registrarPersonas(int *total) {
    printf("Cuantas personas desea registrar: ");
    scanf("%d", total);      // Leer cantidad de personas
    getchar();               // Limpiar buffer de entrada

    // Reservar memoria dinamica para el arreglo de personas
    Persona *lista = (Persona*) malloc((*total) * sizeof(Persona));

    for (int i = 0; i < *total; i++) {
        lista[i].id = i + 1;  // Asignar ID incremental

        printf("\nPersona %d\n", lista[i].id);

        printf("Nombre: ");
        fgets(lista[i].nombre, 50, stdin);  // Leer nombre
        lista[i].nombre[strcspn(lista[i].nombre, "\n")] = '\0';

        printf("Cargo: ");
        fgets(lista[i].cargo, 50, stdin);   // Leer cargo
        lista[i].cargo[strcspn(lista[i].cargo, "\n")] = '\0';
    }

    return lista;  // Retornar arreglo de personas
}

void mostrarTabla(Persona *lista, int total, char *texto) {
    if (!lista || total == 0) {
        printf("No hay personas registradas.\n");
        return;
    }

    if (!texto) {
        printf("Primero debe crear un texto.\n");
        return;
    }

    // Encabezado de la tabla
    printf("\n================== TABLA DE PERSONAS ==================\n");
    printf("+------+------------------------------+------------------------------+------------------------------+\n");
    printf("| ID   | NOMBRE                       | CARGO                        | MENSAJE                      |\n");
    printf("+------+------------------------------+------------------------------+------------------------------+\n");

    // Mostrar cada persona con el mensaje base
    for (int i = 0; i < total; i++) {
        printf("| %-4d | %-28s | %-28s | %-28s |\n",
               lista[i].id,
               lista[i].nombre,
               lista[i].cargo,
               texto);  // Mensaje que se asigna a todos por igual
    }

    printf("+------+------------------------------+------------------------------+------------------------------+\n");
}

void mostrarMezcla(Persona *lista, int total, char *texto) {
    printf("\n========== MENSAJES PERSONALIZADOS ==========\n");

    // Mostrar cada mensaje personalizado para cada persona
    for (int i = 0; i < total; i++) {
        printf("\n--- Persona %d ---\n", lista[i].id);
        printf("Nombre: %s\nCargo: %s\n", lista[i].nombre, lista[i].cargo);
        printf("Mensaje:\n%s %s (%s)\n",
               texto,          // Texto base
               lista[i].nombre, // Nombre de la persona
               lista[i].cargo); // Cargo de la persona
    }
}

