# cProject

# Comparator Operator
  Boolean response is in response to b2 being compared to b1
  True means b2 will come after b1 and vice versa
 ```
bool pcomp(vector<int>& b1, vector<int>&b2) {
  if ( b2[0] > b1[0]) {
    return true; // if b2[0] is bigger, it will come after b1
               } else if ( b2[0] == b1[0]) {
                   // if same starting point, smaller bldg will come later
                   if (b2[1] < b1[1]) {
                       return true;
                   } 
               }
               return false;
           }
  ```                                   
 This is the default behavior of internal sort opeation
 ```          
 struct node {
   int x;
   int y;
   node() {}
   node(int x,int y) : x(x), y(y) {}
 };
struct pqcomp {
            // Priority queue created is with respect to n2. 
            // if n2 is bigger, create max pq
            // if n2 is smaller, create min pq
            bool operator()(node& n1, node& n2) {
                return n2.y > n1.y;
            }
        };
 ```    
# SkyLine : lC 218: Sorting / Multisets / PQs
// Idea is to arrange the buildings in asending order.
// At same position, if there are multiple bulding, following holds true
// if buildings are being added, tallesy building should come first. This has been trickly achieved by negating that value.
// if buildings are being removed, tallest building should come last. default sorting will take care of that

// If a building is being removed at some x, there might be another building with same height
```
class Solution {
    public:    
        vector<vector<int>> getSkyline(vector<vector<int>>& bs) {
            vector<vector<int>> res;
            vector<int> tres(2);
            vector<vector<int>> point;
            map<int, int> hhash;    // hash  to tell height is starting / ending
            map<int, int>::reverse_iterator rit;
            map<int, map<int, int>> xhash; // hash to tell what to do at x
            //priority_queue<int> que; // pq doesn't work as we need to remote select heights. use sets instead
            multiset<int> mset; // Will have to use multiset as same height can come multiple times at different positions.
            mset.insert(0);
            int prev = 0;
            if (bs.size() <= 0) return res;
            
            for ( auto i: bs) {
                if ( i.size() <= 0) return res;
                //xhash[i[0]][i[2]] = 1;  # can't use hash. Beacause hash will overwrite the operations on same height.
                //xhash[i[1]][i[2]] = 0; 
                tres[0] = i[0];
                tres[1] = -i[2];
                point.push_back(tres);
                tres[0] = i[1];
                tres[1] = i[2];
                point.push_back(tres);
            }
            sort(point.begin(), point.end());
                for ( auto p: point) {
                    if ( p[1] < 0) {
                        mset.insert(-p[1]);
                    } else {
                        mset.erase(mset.find(p[1]));
                    }
                    int n = *mset.rbegin();
                    if ( n != prev) { 
                        prev = n;
                        tres[1] = prev;
                        tres[0] = p[0];
                        res.push_back(tres);
                    }
            }
            return res;
        }
};
```
