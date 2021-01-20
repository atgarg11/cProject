# Segment Trees are used for Range query problems
* Update / Creat order is O(n)
* Query Order is O(n)

| HI           | References                                    |   |
|--------------|-----------------------------------------------|---|
| [Tushar Roy] | (https://www.youtube.com/watch?v=ZBHKZF5w4YU) |   |
|              |                                               |   |

```
void buildSegTree(vector<int>& arr, int treeIndex, int lo, int hi)
{
    if (lo == hi) {                 // leaf node. store value in node.
        tree[treeIndex] = arr[lo];
        return;
    }

    int mid = lo + (hi - lo) / 2;   // recurse deeper for children.
    buildSegTree(arr, 2 * treeIndex + 1, lo, mid);
    buildSegTree(arr, 2 * treeIndex + 2, mid + 1, hi);

    // merge build results
    tree[treeIndex] = merge(tree[2 * treeIndex + 1], tree[2 * treeIndex + 2]);
}
```
