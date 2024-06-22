#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class MemReader
{
  unordered_map<int, vector<int>> userToProperties;
  unordered_map<int, vector<int>> propertyToUsers;

public:
  void addRating(int uid, int pid, int rating)
  {
    userToProperties[uid].push_back((pid << 8) | rating);
    propertyToUsers[pid].push_back((uid << 8) | rating);
  }

  vector<int> recommendProperties(int uid, int minRating)
  {
    unordered_map<int, int> propertyScores;
    unordered_map<int, int> propertyCounts;

    for (int data : userToProperties[uid])
    {
      int pid = data >> 8;
      int rating = data & 0xFF;

      for (int relatedData : propertyToUsers[pid])
      {
        int relatedUid = relatedData >> 8;
        int relatedRating = relatedData & 0xFF;

        if (relatedUid != uid && relatedRating >= minRating)
        {
          propertyScores[pid] += relatedRating;
          propertyCounts[pid]++;
        }
      }
    }

    vector<int> recommendations;
    for (auto &entry : propertyScores)
    {
      if (propertyCounts[entry.first] > 1)
      {
        recommendations.push_back(entry.first);
      }
    }

    return recommendations;
  }
};

int main()
{
  MemReader memReader;
  memReader.addRating(1, 101, 5);
  memReader.addRating(1, 102, 3);
  memReader.addRating(2, 101, 4);
  memReader.addRating(2, 103, 5);

  vector<int> recommendations = memReader.recommendProperties(1, 4);
  for (int pid : recommendations)
  {
    cout << "Recommended property ID: " << pid << endl;
  }

  return 0;
}
