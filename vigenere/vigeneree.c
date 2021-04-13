// Codigo de encriptacion vigenere.
// Para Seguridad Informatica
// Profesor Pedro Alberto Lascurain López
// Tarea 5
// Por:
// Jose Javier Tlacuilo Fuentes
// A01420128

#include <stdio.h>
#include <stdlib.h>

// Tamano maximo del texto son 100 caracteres.
// Si el archivo tiene mas de 100 caracteres no los va a leer
// Mas un espacio para el caracter '\0' que termina un string.
#define MAX_TEXT 101


// Metodo que recibe un archivo para leer y uno de destino para encriptar.
void encrypt(FILE *plainPtr, FILE *cyphPtr) {
    // El texto en plano se guarda en un arreglo de caracteres.
    char plaintext[MAX_TEXT];

    // Se lee la primera linea del texto que debe incluir el texto completeo.
    if((fgets(plaintext, MAX_TEXT, plainPtr)) == NULL) {
        // Terminar si no hay texto en plano para leer.
        printf("Error al leer el texto en plano.\n");
        exit(EXIT_FAILURE);
    }

    // Imprimir texto a cifrar.
    printf("Texto en plano:\n%s\n", plaintext);

    // Preguntar por la llave, un string o arreglo de caracteres.
    char key[MAX_TEXT];
    printf("Dame la llave:\n");
    scanf("%s", key);

    // Imprimir la llave.
    printf("Llave %s\n", key);

    // Transformar el texto en plano.
    int i = 0;
    int ik = 0;
    while (plaintext[i] != '\0' && plaintext[i] != '\n') {
        // Reiniciar orden de key si ya se acabo.
        if (key[ik] == '\0')
            ik = 0;

        // printf("%c corrimiento con:%c\n", plaintext[i], key[ik]);

        // revision para garantizar funcionamiento con letras.
        char off = key[ik] >= 'a' ? key[ik] - 'a' : key[ik];

        // Tranformar caracter.
        plaintext[i] = plaintext[i] + off;
        i++;
        ik++;
    }

    // Copiar el texto en plano encriptado en archivo ciphertext
    fseek(cyphPtr, 0, SEEK_SET);
    fprintf(cyphPtr, "%s", plaintext);

    printf("Texto cifrado:\n%s\n", plaintext);
    printf("El texto cifrado esta en cyphertext.txt\n");
}

int main() {
    // Pedir el nombre del archivo a decifrar.
    char filename[51];
    printf("Escribe el nombre completo de tu .txt, nombre de tamano max 50\n");
    scanf("%s", filename);

    // Leer el texto en plano desde el archivo filename.
    FILE *plainPtr = fopen(filename, "r");
    if (plainPtr == NULL) {
        printf("No se pudo abrir el texto en plano.");
        return EXIT_FAILURE;
    }

    // El texto cifrado se escribe en cyphertext.txt
    FILE *cyphPtr = fopen("cyphertext.txt", "w+");
    if (cyphPtr == NULL) {
        printf("No se pudo abrir el texto cifrado.");
        return EXIT_FAILURE;
    }

    // Encryptar plaintext.txt y escribirlo en cyphertext.txt.
    encrypt(plainPtr, cyphPtr);

    // Cerrar los dos archivos.
    fclose(plainPtr);
    fclose(cyphPtr);

    return EXIT_SUCCESS;
}
