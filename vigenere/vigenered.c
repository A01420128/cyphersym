// Codigo de decriptacion vigenere.
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


// Metodo que recibe un archivo encryptado y uno de destino para desencriptar.
void dencrypt(FILE *cyphPtr, FILE *decryPtr) {
    // El texto cifrado se guarda en un arreglo de caracteres.
    char cyphertext[MAX_TEXT];

    // Se lee la primera linea del texto que debe incluir el texto completeo.
    if((fgets(cyphertext, MAX_TEXT, cyphPtr)) == NULL) {
        // Terminar si no hay texto en plano para leer.
        printf("Error al leer el texto cifrado.\n");
        exit(EXIT_FAILURE);
    }

    // Imprimir texto cifrado.
    printf("Texto cifrado:\n%s\n", cyphertext);

    // Preguntar por la llave, un string o arreglo de caracteres.
    char key[MAX_TEXT];
    printf("Dame la llave:\n");
    scanf("%s", key);

    // Imprimir la llave.
    printf("Llave %s\n", key);

    // Transformar el texto en plano.
    int i = 0;
    int ik = 0;
    while (cyphertext[i] != '\0' && cyphertext[i] != '\n') {
        // Reiniciar orden de key si ya se acabo.
        if (key[ik] == '\0')
            ik = 0;

        // revision para garantizar funcionamiento con letras.
        char off = key[ik] >= 'a' ? key[ik] - 'a' : key[ik];

        // Tranformar caracter.
        cyphertext[i] = cyphertext[i] - off;
        i++;
        ik++;
    }

    // Copiar el texto en plano desencriptado en archivo decrypted.txt
    fseek(decryPtr, 0, SEEK_SET);
    fprintf(decryPtr, "%s", cyphertext);

    printf("Texto en descifrado:\n%s\n", cyphertext);
    printf("El texto cifrado esta en decrypted.txt\n");
}

int main() {
    // Pedir el nombre del archivo a decifrar.
    char filename[51];
    printf("Escribe el nombre completo del archivo encriptado .txt, nombre de tamano max 50\n");
    scanf("%s", filename);

    // Leer el texto encriptado desde el archivo filename.
    FILE *cyphPtr = fopen(filename, "r");
    if (cyphPtr == NULL) {
        printf("No se pudo abrir el texto encriptado.");
        return EXIT_FAILURE;
    }

    // El texto descifrado se escribe en decrypted.txt
    FILE *decryPtr = fopen("decrypted.txt", "w+");
    if (decryPtr == NULL) {
        printf("No se pudo abrir el texto descifrado.");
        return EXIT_FAILURE;
    }

    // Encryptar plaintext.txt y escribirlo en cyphertext.txt.
    dencrypt(cyphPtr, decryPtr);

    // Cerrar los dos archivos.
    fclose(cyphPtr);
    fclose(decryPtr);

    return EXIT_SUCCESS;
}
