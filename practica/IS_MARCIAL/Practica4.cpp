#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
} Alumno;

typedef struct {
    int id;
    char descripcion[100];
} Tarea;

typedef struct {
    int idAlumno;
    int idTarea;
    float calificacion;
} Calificacion;
Alumno* ingresarAlumnos(int *n) {
    printf("Cuantos alumnos desea ingresar: ");
    scanf("%d", n);
    getchar(); // Limpiar buffer

    Alumno *alum = (Alumno*) malloc((*n) * sizeof(Alumno));
    for(int i=0; i<*n; i++) {
        alum[i].id = i+1;
        printf("Ingrese nombre del alumno %d: ", i+1);
        fgets(alum[i].nombre, 50, stdin);
        alum[i].nombre[strcspn(alum[i].nombre, "\n")] = '\0'; // Eliminar salto de linea
    }
    return alum;
}

Tarea* ingresarTareas(int *m) {
    printf("Cuantas tareas desea ingresar:");
    scanf("%d", m);
    getchar(); // Limpiar buffer

    Tarea *tareas = (Tarea*) malloc((*m) * sizeof(Tarea));
    for(int i=0; i<*m; i++) {
        tareas[i].id = i+1;
        printf("Ingrese descripcion de la tarea %d: ", i+1);
        fgets(tareas[i].descripcion, 100, stdin);
        tareas[i].descripcion[strcspn(tareas[i].descripcion, "\n")] = '\0';
    }
    return tareas;
}

Calificacion* asignarCalificaciones(Alumno *alum, int n, Tarea *tareas, int m) {
    Calificacion *calificaciones = (Calificacion*) malloc(n*m * sizeof(Calificacion));
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            calificaciones[i*m + j].idAlumno = alum[i].id;
            calificaciones[i*m + j].idTarea = tareas[j].id;
            printf("Ingrese calificacion de %s en %s: ", alum[i].nombre, tareas[j].descripcion);
            scanf("%f", &calificaciones[i*m + j].calificacion);
        }
    }
    return calificaciones;
}
void mostrarAlumnos(Alumno *alum, int n) {
    printf("\n--- Lista de Alumnos ---\n");
    for(int i=0; i<n; i++) {
        printf("ID: %d - Nombre: %s\n", alum[i].id, alum[i].nombre);
    }
}

void mostrarTareas(Tarea *tareas, int m) {
    printf("\n--- Lista de Tareas ---\n");
    for(int i=0; i<m; i++) {
        printf("ID: %d - Descripcion: %s\n", tareas[i].id, tareas[i].descripcion);
    }
}

void mostrarCalificaciones(Calificacion *calificaciones, Alumno *alum, Tarea *tareas, int n, int m) {
    printf("\n--- Calificaciones ---\n");
    for(int i=0; i<n; i++) {
        printf("\nAlumno: %s\n", alum[i].nombre);
        for(int j=0; j<m; j++) {
            printf("Tarea: %s - Calificacion: %.2f\n",
                   tareas[j].descripcion,
                   calificaciones[i*m + j].calificacion);
        }
    }
}
int main() {
    Alumno *alum = NULL;
    Tarea *tareas = NULL;
    Calificacion *calificaciones = NULL;
    int n=0, m=0;
    int opcion;

  do {
    printf("\n--- Menu----\n");
    printf("1. Ingresar Alumnos\n");
    printf("2. Ingresar Tareas\n");
    printf("3. Asignar Calificaciones\n");
    printf("4. Mostrar Alumnos\n");
    printf("5. Mostrar Tareas\n");
    printf("6. Mostrar Calificaciones\n");
    printf("7. Mostrar Todos los Resultados\n");
    printf("8. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    getchar(); // limpiar buffer

    switch(opcion) {
        case 1: 
            if(alum) free(alum);
            alum = ingresarAlumnos(&n); 
            break;
        case 2: 
            if(tareas) free(tareas);
            tareas = ingresarTareas(&m); 
            break;
        case 3:
            if(calificaciones) free(calificaciones);
            if(alum && tareas)
                calificaciones = asignarCalificaciones(alum, n, tareas, m);
            else
                printf("Primero debe ingresar alumnos y tareas.\n");
            break;
        case 4: mostrarAlumnos(alum, n); break;
        case 5: mostrarTareas(tareas, m); break;
        case 6: 
            if(calificaciones)
                mostrarCalificaciones(calificaciones, alum, tareas, n, m);
            else
                printf("No hay calificaciones asignadas.\n");
            break;
        case 7:
            printf("\n--- TODOS LOS RESULTADOS ---\n");
            mostrarAlumnos(alum, n);
            mostrarTareas(tareas, m);
            if(calificaciones)
                mostrarCalificaciones(calificaciones, alum, tareas, n, m);
            else
                printf("No hay calificaciones asignadas.\n");
            break;
        case 8: 
            printf("Saliendo.\n"); 
            break;
        default: printf("Opcion invalida.\n");
    }
} while(opcion != 8);


    // Liberar memoria
    if(alum) free(alum);
    if(tareas) free(tareas);
    if(calificaciones) free(calificaciones);

    return 0;
}

