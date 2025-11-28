#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 500
#define NOMBRE_ARCHIVO "mensajes.txt"
// Estructura para almacenar informacion de cada persona
typedef struct {
    int id;  // Identificador
    char nombre[50];   // Nombre de la persona
    char cargo[50];   // Cargo de la persona
} Persona;

char* crearTexto();
void editarTexto(char *buffer);
Persona* registrarPersonas(int *total);
void mostrarMezcla(Persona *lista, int total, char *texto);
void guardarEnArchivo(Persona *lista, int total, char *texto);
void mostrarTabla(Persona *lista, int total, char *texto);
void limpiarArchivo();   //funcion para limpiar archivo


int main() {
    char *texto = NULL;       // Puntero para almacenar el texto creado
    Persona *lista = NULL;  // Puntero a arreglo dinamico
    int total = 0;
    int opcion;

    do {
        printf("\n---Menu---\n");
        printf("1. Crear texto\n");
        printf("2. Modificar texto\n");
        printf("3. Registrar personas\n");
        printf("4. Mostrar informacion en tabla\n");
        printf("5. Guardar documento en archivo\n");
        printf("6. Limpiar archivo\n");   
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer de entrada

        switch (opcion) {
            case 1:
                texto = crearTexto();
                break;

            case 2:
                if (texto)
                    editarTexto(texto);
                else
                    printf("Primero cree un texto.\n");
                break;

            case 3:
                lista = registrarPersonas(&total);
                break;

            case 4:
                mostrarTabla(lista, total, texto);
                break;

            case 5:
                if (texto && lista)
                    guardarEnArchivo(lista, total, texto);
                else
                    printf("Debe registrar personas y crear texto primero.\n");
                break;

            case 6:
                limpiarArchivo();
                break;

            case 7:
                printf("Saliendo.\n");
                break;

            default:
                printf("Opción no valida.\n");
        }

    } while (opcion != 7);
 // Liberar memoria dinamica antes de terminar
    if (texto) free(texto);
    if (lista) free(lista);

    return 0;
}


//crear mensaje 
char* crearTexto() {  // Reservar memoria para el buffer del texto
    char *buffer = (char*) malloc(MAX_TEXTO);
    printf("\nEscriba el texto base:\n ");
    fgets(buffer, MAX_TEXTO, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Texto guardado.\n");
    return buffer; // Retornar puntero al texto creado
}

//editar mensaje 

void editarTexto(char *buffer) {
    printf("\nTexto actual:\n%s\n", buffer);
    printf("Escriba el nuevo texto:\n ");
    fgets(buffer, MAX_TEXTO, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Texto modificado.\n");
}


//registra personas
Persona* registrarPersonas(int *total) {
    printf("Cuantas personas desea registrar: ");
    scanf("%d", total);
    getchar();
  // Reservar memoria dinamica para el arreglo de personas
    Persona *lista = (Persona*) malloc((*total) * sizeof(Persona));

    for (int i = 0; i < *total; i++) {
        lista[i].id = i + 1;

        printf("\nPersona %d\n", lista[i].id);

        printf("Nombre: ");
        fgets(lista[i].nombre, 50, stdin);
        lista[i].nombre[strcspn(lista[i].nombre, "\n")] = '\0';

        printf("Cargo: ");
        fgets(lista[i].cargo, 50, stdin);
        lista[i].cargo[strcspn(lista[i].cargo, "\n")] = '\0';
    }
// Retornar arreglo de personas
    return lista;
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

    printf("\n================== TABLA DE PERSONAS ==================\n");
    printf("+------+------------------------------+------------------------------+------------------------------+\n");
    printf("| ID   | NOMBRE                       | CARGO                        | MENSAJE                      |\n");
    printf("+------+------------------------------+------------------------------+------------------------------+\n");

    for (int i = 0; i < total; i++) {
        printf("| %-4d | %-28s | %-28s | %-28s |\n",
               lista[i].id,
               lista[i].nombre,
               lista[i].cargo,
               texto);
    }

    printf("+------+------------------------------+------------------------------+------------------------------+\n");
}


//guardar en archivo txt
void guardarEnArchivo(Persona *lista, int total, char *texto) {
    FILE *f = fopen(NOMBRE_ARCHIVO, "a");

    if (!f) {
        printf("Error al crear archivo.\n");
        return;
    }

    fprintf(f, "ID\tNombre\t\tCargo\t\tMensaje\n");

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d\t%-10s\t%-10s\t%s\n",
                lista[i].id,
                lista[i].nombre,
                lista[i].cargo,
                texto);
    }

    fprintf(f, "\n----------------------------------------------\n");

    fclose(f);
    printf("\nArchivo '%s' generado correctamente.\n", NOMBRE_ARCHIVO);
}


//limpiar el archivo
void limpiarArchivo() {
    FILE *f = fopen(NOMBRE_ARCHIVO, "w");

    if (!f) {
        printf("Error al limpiar el archivo.\n");
        return;
    }

    fclose(f);
    printf("Archivo '%s' limpiado correctamente.\n", NOMBRE_ARCHIVO);
}

void mostrarMezcla(Persona *lista, int total, char *texto) {
    printf("\n========== MENSAJES PERSONALIZADOS ==========\n");

    for (int i = 0; i < total; i++) {
        printf("\n--- Persona %d ---\n", lista[i].id);
        printf("Nombre: %s\nCargo: %s\n", lista[i].nombre, lista[i].cargo);
        printf("Mensaje:\n%s %s\n",
               texto,
               lista[i].nombre);
    }
}

