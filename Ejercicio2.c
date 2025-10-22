#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


char* const_output( char* ruta) {
    size_t n = strlen(ruta);
    char sufi[] = ".out.txt";
    char* out = (char*)malloc(n + sizeof(sufi));
    if (!out) return NULL;
    memcpy(out, ruta, n);
    memcpy(out + n, sufi, sizeof(sufi));
    return out;
}


int busqueda(FILE* in, FILE* out, char* p_buscar, const char* repl) {
    int c;
    size_t cap = 32, len = 0;
    char* palabra = (char*)malloc(cap);
    if (!palabra) return -1;

    while ((c = fgetc(in)) != EOF) {
        if (isalnum((unsigned char)c)) {
            if (len + 1 >= cap) {
                size_t ncap = cap * 2;
                char* temp = (char*)realloc(palabra, ncap);
                if (!temp) { free(palabra); return -1; }
                palabra = temp; cap = ncap;
            }
            palabra[len++] = (char)c;
        } else {
            if (len > 0) {
                palabra[len] = '\0';
                if (strcmp(palabra, p_buscar) == 0) {
                    fputs(repl, out);
                } else {
                    fputs(palabra, out);
                }
                len = 0;
            }
            fputc(c, out);
        }
    }

    if (len > 0) {
        palabra[len] = '\0';
        if (strcmp(palabra, p_buscar) == 0) {
            fputs(repl, out);
        } else {
            fputs(palabra, out);
        }
    }

    free(palabra);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr,
            "Uso: %s <archivo_entrada> <palabra_buscar> <reemplazo>\n", argv[0]);
        return 1;
    }

    char* ruta = argv[1];
    char* p_buscar  = argv[2];
    char* repl    = argv[3];

    if (p_buscar[0] == '\0') {
        fprintf(stderr, "Error: la palabra a buscar no puede ser vacia.\n");
        return 1;
    }

    FILE* in = fopen(ruta, "r");
    if (!in) {
        perror("No se pudo abrir archivo de entrada");
        return 1;
    }

    char* out_ruta = const_output(ruta);
    if (!out_ruta) {
        fprintf(stderr, "Error: sin memoria para nombre de salida.\n");
        fclose(in);
        return 1;
    }

    FILE* out = fopen(out_ruta, "w");
    if (!out) {
        perror("No se pudo abrir archivo de salida");
        fclose(in);
        free(out_ruta);
        return 1;
    }

    int rc = busqueda(in, out, p_buscar, repl);
    if (rc != 0) {
        fprintf(stderr, "Error: sin memoria durante el reemplazo.\n");
        fclose(in);
        fclose(out);
        free(out_ruta);
        return 1;
    }

    fclose(in);
    fclose(out);
    printf("Listo. Archivo de salida: %s\n", out_ruta);
    free(out_ruta);
    return 0;
}
