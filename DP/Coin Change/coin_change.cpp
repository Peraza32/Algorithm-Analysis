#include <iostream>
#include <vector>

using namespace std;

int minCoinChangeRecursive(vector<int> coins, int m, int K);
int min(int a, int b);
int minCoinChangeDP_array(vector<int> coins, int K);

int main()
{

    vector<int> coins = {1, 2, 5};
    int K = 11;
    int m = coins.size();
    cout << minCoinChangeRecursive(coins, m, K) << endl;
    cout << minCoinChangeDP_array(coins, K) << endl;

    return 0;
}

int minCoinChangeRecursive(vector<int> coins, int m, int K)
{

    if (K == 0)
        return 0;
    int min = INT_MAX;
    for (size_t i = 0; i < m; i++)
    {
        if (coins[i] <= K)
        {
            int current = minCoinChangeRecursive(coins, m, K - coins[i]);
            if (current != INT_MAX && current + 1 < min)
                min = current + 1;
        }
    }
    if (min == INT_MAX)
        return -1;
    else
        return min;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

// Array implementation
int minCoinChangeDP_array(vector<int> coins, int K)
{
    int solutions[K + 1];

    // Initialize all solutions as INT_MAX
    for (int i = 1; i <= K; i++)
    {
        solutions[i] = INT_MAX;
    }
    solutions[0] = 0; // Initialization on base case

    for (int i = 1; i <= K; i++)
    {
        for (int j = 0; j < coins.size(); j++)
        {
            if (coins[j] <= i)
            {
                solutions[i] = min(solutions[i], 1 + solutions[i - coins[j]]);
            }
        }
    }

    if (solutions[K] == INT_MAX)
        return -1;
    else
        return solutions[K];
}
