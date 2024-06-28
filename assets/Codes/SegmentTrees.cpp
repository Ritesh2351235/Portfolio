#include <iostream>
#include <vector>
using namespace std;

class SegmentTree
{
  vector<int> tree, lazy;
  int size;

public:
  SegmentTree(int n)
  {
    size = n;
    tree.resize(4 * n);
    lazy.resize(4 * n);
  }

  void build(vector<int> &values, int node, int start, int end)
  {
    if (start == end)
    {
      tree[node] = values[start];
    }
    else
    {
      int mid = (start + end) / 2;
      build(values, 2 * node, start, mid);
      build(values, 2 * node + 1, mid + 1, end);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  void updateRange(int node, int start, int end, int l, int r, int val)
  {
    if (lazy[node] != 0)
    {
      tree[node] += (end - start + 1) * lazy[node];
      if (start != end)
      {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
      }
      lazy[node] = 0;
    }

    if (start > end || start > r || end < l)
      return;

    if (start >= l && end <= r)
    {
      tree[node] += (end - start + 1) * val;
      if (start != end)
      {
        lazy[2 * node] += val;
        lazy[2 * node + 1] += val;
      }
      return;
    }

    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, l, r, val);
    updateRange(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }

  int queryRange(int node, int start, int end, int l, int r)
  {
    if (lazy[node] != 0)
    {
      tree[node] += (end - start + 1) * lazy[node];
      if (start != end)
      {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
      }
      lazy[node] = 0;
    }

    if (start > end || start > r || end < l)
      return 0;

    if (start >= l && end <= r)
      return tree[node];

    int mid = (start + end) / 2;
    int leftQuery = queryRange(2 * node, start, mid, l, r);
    int rightQuery = queryRange(2 * node + 1, mid + 1, end, l, r);
    return leftQuery + rightQuery;
  }
};

int main()
{
  int n = 5;
  vector<int> propertyValues = {10, 20, 30, 40, 50};
  SegmentTree segTree(n);
  segTree.build(propertyValues, 1, 0, n - 1);

  segTree.updateRange(1, 0, n - 1, 1, 3, 5);
  cout << "Updated Property Value Range (1-3): " << segTree.queryRange(1, 0, n - 1, 1, 3) << endl;

  return 0;
}
