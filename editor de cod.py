def min_cost(a, b):
    return min(a, b)

def levenshtein_distance(s1, s2):
    m = len(s1)
    n = len(s2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j

    for i in range(m):
        for j in range(n):
            if s1[i] == s2[j]:
                dp[i + 1][j + 1] = dp[i][j]
            else:
                insert_cost = dp[i + 1][j] + 1
                delete_cost = dp[i][j + 1] + 1
                replace_cost = dp[i][j] + 1

                if i > 0 and j > 0 and s1[i - 1] == s2[j] and s1[i] == s2[j - 1]:
                    swap_cost = dp[i - 1][j - 1] + 1
                    replace_cost = min_cost(replace_cost, swap_cost)

                dp[i + 1][j + 1] = min_cost(min_cost(insert_cost, delete_cost), replace_cost)

    return dp[m][n]

if __name__ == "__main__":
    with open("fisier2.in", "r") as fptr1:
        str1 = fptr1.readline().strip()
        str2 = fptr1.readline().strip()

    distance = levenshtein_distance(str1, str2)

    with open("fisier2.out", "w") as fptr2:
        fptr2.write(f"Numărul minim de operații de transformat este {distance}\n")
