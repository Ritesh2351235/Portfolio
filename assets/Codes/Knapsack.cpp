#include <iostream>
#include <vector>
using namespace std;

int maxRevenue(vector<vector<int>> &revenue, int n, int m)
{

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); // Intializing with 0

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + revenue[i][j]);
    }
  }

  // Return the maximum revenue
  return dp[n][m];
}

int main()
{

  int n = 3; // Number of ads
  int m = 2; // Number of placements

  vector<vector<int>> revenue = {
      {0, 0, 0},
      {0, 0, 0}, // For sample consider these are the positions like x,y,z
      {0, 1, 2},
      {0, 2, 5}};

  int maxRev = maxRevenue(revenue, n, m);
  cout << "Maximum revenue : " << maxRev << endl;

  return 0;
}
