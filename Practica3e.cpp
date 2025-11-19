#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char *buffer;
    size_t size;
    size_t length;
} TextEditor;
void init_editor(TextEditor *editor);
void free_editor(TextEditor *editor);
void insert_text(TextEditor *editor, const char *text);
void mostrarTexto(const TextEditor *editor);
void buscarYReemplazar(TextEditor *editor, const char *buscar, const char *reemplazar);
void mostrarBusqueda(const TextEditor *editor, const char *buscar);
void mostrarReemplazo(const char *reemplazar);
void mostrarEstadisticas(const TextEditor *editor);
void copiarCadena(char *destino, const char *origen);
void concatenarCadenas(char *destino, const char *origen);
int longitudCadena(const char *cadena);
int main() {
    TextEditor editor;
    char buscar[100];
    char reemplazar[100];
    char input[256];
    int opcion;
    int i;
    init_editor(&editor); 
    do {
        printf("\nMenu principal\n");	
        printf("1. Insertar texto\n");
        printf("2. Mostrar texto actual\n");
        printf("3. Buscar texto\n");
        printf("4. Reemplazar texto\n");
        printf("5. Mostrar estadisticas de memoria\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();      

        switch(opcion) {
            case 1:
                printf("Ingrese el texto a insertar:\n");
                fgets(input, sizeof(input), stdin);
                // Eliminar salto de linea
                for(i = 0; input[i] != '\0'; i++) {
                    if(input[i] == '\n') {
                        input[i] = '\0';
                        break;
                    }
                }
                insert_text(&editor, input);
                break;
                
            case 2:
                mostrarTexto(&editor);
                break;
                
            case 3:
                if (editor.length == 0) {
                    printf("El texto esta vacio.\n");
                    break;
                }
                printf("Ingrese el texto para buscar: ");
                fgets(buscar, sizeof(buscar), stdin);
                for(i = 0; buscar[i] != '\0'; i++) {
                    if(buscar[i] == '\n') {
                        buscar[i] = '\0';
                        break;
                    }
                }

                printf("\n--- Busqueda de texto----\n");
                mostrarTexto(&editor);
                mostrarBusqueda(&editor, buscar);
                break;

            case 4:
                if (editor.length == 0) {
                    printf("El texto esta vacio.\n");
                    break;
                }

                printf("Ingrese el texto a buscar: ");
                fgets(buscar, sizeof(buscar), stdin);
                for(i = 0; buscar[i] != '\0'; i++) {
                    if(buscar[i] == '\n') {
                        buscar[i] = '\0';
                        break;
                    }
                }

                printf("Ingrese el texto de reemplazo: ");
                fgets(reemplazar, sizeof(reemplazar), stdin);
                for(i = 0; reemplazar[i] != '\0'; i++) {
                    if(reemplazar[i] == '\n') {
                        reemplazar[i] = '\0';
                        break;
                    }
                }

                printf("\n--- Remplazo del texto ---\n");
                mostrarTexto(&editor);
                mostrarReemplazo(reemplazar);
                buscarYReemplazar(&editor, buscar, reemplazar);
                
                printf("\n--- Texto final ---\n");
                mostrarTexto(&editor);
                break;

            case 5:
                mostrarEstadisticas(&editor);
                break;

            case 6:
                printf("Saliendo del programa\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
        
    } while(opcion != 6);
    
    // Liberar memoria al salir
    free_editor(&editor);
    printf("Memoria liberada correctamente.\n");
    
    return 0;
}

// Inicializar editor con memoria dinamica 
void init_editor(TextEditor *editor) {
    editor->buffer = (char *)malloc(100 * sizeof(char));
    if (editor->buffer == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria inicial\n");
        exit(1);
    }
    editor->buffer[0] = '\0';
    editor->size = 100;
    editor->length = 0;
    printf("Editor inicializado con %zu bytes de memoria\n", editor->size);
}

// Liberar memoria del editor
void free_editor(TextEditor *editor) {
    free(editor->buffer);
    editor->buffer = NULL;
    editor->size = 0;
    editor->length = 0;
}

// Funcion para calcular longitud de cadena
int longitudCadena(const char *cadena) {
    int longitud = 0;
    while(*cadena != '\0') {
        longitud++;
        cadena++;
    }
    return longitud;
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

void insert_text(TextEditor *editor, const char *text) {
    int text_len = longitudCadena(text);
    
    // Verificar si se necesita mas memoria
    if (editor->length + text_len + 1 >= editor->size) {
        size_t new_size = editor->size;
        while (editor->length + text_len + 1 >= new_size) {
            new_size *= 2;
        }
        
        char *new_buffer = (char *)realloc(editor->buffer, new_size);
        if (new_buffer == NULL) {
            fprintf(stderr, "Error: No se pudo redimensionar la memoria\n");
            return;
        }
        
        editor->buffer = new_buffer;
        editor->size = new_size;
        printf("Memoria redimensionada: %zu bytes\n", editor->size);
    }
    

    concatenarCadenas(editor->buffer, text);
    editor->length += text_len;
    
    printf("Texto insertado. Longitud actual: %zu caracteres\n", editor->length);
}

// Funcion para mostrar el texto completo
void mostrarTexto(const TextEditor *editor) {
    printf("\n--- Texto actual ---\n");
    if (editor->length == 0) {
        printf("El texto esta vacio.\n");
    } else {
        printf("%s\n", editor->buffer);
    }
    printf("Longitud: %zu caracteres\n", editor->length);
}

// Funcion para buscar una subcadena
int buscarSubcadena(const char *texto, const char *subcadena) {
    int len_texto = longitudCadena(texto);
    int len_sub = longitudCadena(subcadena);
    int i, j;
    
    if(len_sub == 0) return 0;
    
    for(i = 0; i <= len_texto - len_sub; i++) {
        int encontrado = 1;
        for(j = 0; j < len_sub; j++) {
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
void buscarYReemplazar(TextEditor *editor, const char *buscar, const char *reemplazar) {
    int len_buscar = longitudCadena(buscar);
    int len_reemplazar = longitudCadena(reemplazar);
    int contador = 0;
    int j;
    
    if (len_buscar == 0) {
        printf("Error: El texto a buscar no puede estar vacio.\n");
        return;
    }
    
    if (buscarSubcadena(editor->buffer, buscar) == -1) {
        printf("El texto '%s' no fue encontrado.\n", buscar);
        return;
    }
    
    // Calcular tam maximo necesario para el resultado
    size_t max_needed = editor->length + (len_reemplazar - len_buscar) * (editor->length / len_buscar) + 1;
    
    if (max_needed > editor->size) {
        char *new_buffer = (char *)realloc(editor->buffer, max_needed);
        if (new_buffer == NULL) {
            fprintf(stderr, "Error: No se pudo redimensionar la memoria para el reemplazo\n");
            return;
        }
        editor->buffer = new_buffer;
        editor->size = max_needed;
        printf("Memoria redimensionada para reemplazo: %zu bytes\n", editor->size);
    }
    
    char *temp_buffer = (char *)malloc(editor->size);
    if (temp_buffer == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria temporal\n");
        return;
    }
    
    temp_buffer[0] = '\0';
    char *current = editor->buffer;
    
    while(*current != '\0') {
        int coincide = 1;
        for(j = 0; j < len_buscar; j++) {
            if(current[j] != buscar[j] || current[j] == '\0') {
                coincide = 0;
                break;
            }
        }
        
        if(coincide) {
            
            concatenarCadenas(temp_buffer, reemplazar);
            current += len_buscar;
            contador++;
        } else {
            char temp[2] = {*current, '\0'};
            concatenarCadenas(temp_buffer, temp);
            current++;
        }
    }
    copiarCadena(editor->buffer, temp_buffer);
    editor->length = longitudCadena(editor->buffer);
    
    free(temp_buffer);
    printf("Reemplazo completado. Se reemplazaron %d ocurrencias.\n", contador);
}

// Funcion para mostrar el texto a buscar
void mostrarBusqueda(const TextEditor *editor, const char *buscar) {
    printf("\n--- Texto al buscar  ---\n");
    printf("'%s'\n", buscar);
    
    int len_buscar = longitudCadena(buscar);
    int len_texto = editor->length;
    int contador = 0;
    int i, j;
    
    printf("Posiciones encontradas: ");
    
    for(i = 0; i <= len_texto - len_buscar; i++) {
        int encontrado = 1;
        for(j = 0; j < len_buscar; j++) {
            if(editor->buffer[i + j] != buscar[j]) {
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
    printf("\n--- Texto reemplazado ---\n");
    printf("'%s'\n", reemplazar);
    printf("Longitud: %d caracteres\n", longitudCadena(reemplazar));
}
void mostrarEstadisticas(const TextEditor *editor) {
    printf("\n--Estadistica de memoira\n");
    printf("Tama total del buffer: %zu bytes\n", editor->size);
    printf("Memoria utilizada: %zu bytes\n", editor->length + 1);
    printf("Memoria disponible: %zu bytes\n", editor->size - (editor->length + 1));
    printf("Eficiencia de memoria: %.2f%%\n", 
           ((double)(editor->length + 1) / editor->size) * 100);
    printf("Longitud del texto: %zu caracteres\n", editor->length);
    
    if (editor->size > 100) {
        printf("Redimensionamientos: Si \n");
    } else {
        printf("Redimensionamientos: No (tama inicial)\n");
    }
}

