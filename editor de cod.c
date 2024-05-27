#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcție pentru calcularea valorii minime
int Min(int a, int b)
{
    return (a < b) ? a : b;
}

// Funcție care calculează distanța de editare (Levenshtein) dintre două șiruri de caractere
int distanta(const char *s1, const char *s2)
{
    int m = strlen(s1);                                 // Lungimea primului șir
    int n = strlen(s2);                                 // Lungimea celui de-al doilea șir
    int **dp = (int **)malloc((m + 1) * sizeof(int *)); // Alocare dinamică pentru matricea dp
    for (int i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int)); // Alocare dinamică pentru fiecare rând din matricea dp
    }

    // Inițializarea primei coloane a matricei dp
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }
    // Inițializarea primei linii a matricei dp
    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    // Calcularea valorilor din matricea dp
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s1[i] == s2[j])
            {
                dp[i + 1][j + 1] = dp[i][j]; // Dacă caracterele sunt egale, costul este același
            }
            else
            {
                int insert_cost = dp[i + 1][j] + 1; // Costul pentru inserare
                int delete_cost = dp[i][j + 1] + 1; // Costul pentru ștergere
                int replace_cost = dp[i][j] + 1;    // Costul pentru înlocuire

                // Verificare pentru costul de swap (transpunere)
                if (i > 0 && j > 0 && s1[i - 1] == s2[j] && s1[i] == s2[j - 1])
                {
                    int swap_cost = dp[i - 1][j - 1] + 1;
                    replace_cost = Min(replace_cost, swap_cost); // Alegerea costului minim dintre înlocuire și swap
                }
                // Alegerea costului minim dintre inserare, ștergere și înlocuire
                dp[i + 1][j + 1] = Min(Min(insert_cost, delete_cost), replace_cost);
            }
        }
    }

    int result = dp[m][n]; // Rezultatul final este în dp[m][n]

    for (int i = 0; i <= m; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main()
{
    char str1[1001]; // Declarația primului șir
    char str2[1001]; // Declarația celui de-al doilea șir
    FILE *fptr1;
    FILE *fptr2;
    fptr1 = fopen("fisier2.in", "r");
    fptr2 = fopen("fisier2.out", "w");
    if (fptr1 == NULL || fptr2 == NULL)
    {
        printf("Error!");
        exit(1);
    }

    // Citirea primului șir din fișier
    if (fgets(str1, sizeof(str1), fptr1) != NULL)
    {
        str1[strcspn(str1, "\n")] = '\0'; // Eliminarea caracterului de linie nouă
    }

    // Citirea celui de-al doilea șir din fișier
    if (fgets(str2, sizeof(str2), fptr1) != NULL)
    {
        str2[strcspn(str2, "\n")] = '\0'; // Eliminarea caracterului de linie nouă
    }

    int distance = distanta(str1, str2); // Calcularea distanței de editare

    // Scrierea rezultatului în fișierul de ieșire
    fprintf(fptr2, "Numărul minim de operații de transformat este %d\n", str1, str2, distance);

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
