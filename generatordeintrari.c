#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definirea funcției generateRandomText
void generateRandomText(char *text, int length)
{
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int charsetSize = sizeof(charset) - 1;

    srand(time(0)); // Inițializare generator de numere aleatorii

    for (int i = 0; i < length; i++)
    {
        int key = rand() % charsetSize;
        text[i] = charset[key];
    }
    text[length] = '\0'; // Adaugă caracterul de terminare a șirului
}

// Definirea funcției shuffleText
void shuffleText(char *text, int length)
{
    srand(time(0)); // Reinițializare generator de numere aleatorii

    for (int i = length - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        // Schimbă caracterele text[i] și text[j]
        char temp = text[i];
        text[i] = text[j];
        text[j] = temp;
    }
}

int main()
{
    FILE *fptr1, *fptr2;
    int length;

    // Deschidere fișier de intrare pentru citire
    fptr1 = fopen("fisier1.in", "r");
    if (fptr1 == NULL)
    {
        printf("Error! Could not open file fisier1.in for reading\n");
        return 1;
    }

    // Citire lungime text din fișier
    fscanf(fptr1, "%d", &length);
    fclose(fptr1);

    // Verificare lungime validă
    if (length <= 0)
    {
        printf("Error! Invalid length\n");
        return 1;
    }

    char text[length + 1]; // Creează un array pentru text, cu un spațiu suplimentar pentru '\0'

    // Generare text aleator
    generateRandomText(text, length);

    // Deschidere fișier de ieșire pentru scriere
    fptr2 = fopen("fisier1.out", "w");
    if (fptr2 == NULL)
    {
        printf("Error! Could not open file fisier1.out for writing\n");
        return 1;
    }

    // Scriere text generat în fișier
    fprintf(fptr2, " %s\n", text);

    // Amestecare litere în text
    shuffleText(text, length);

    // Scriere text amestecat în fișier
    fprintf(fptr2, " %s\n", text);

    fclose(fptr2);

    return 0;
}