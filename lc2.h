#ifndef LC_2_H_
#define LC_2_H_
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <list>
#include "lc1.h"

using namespace std;
void printTreeLevel(TreeNode* root) {
    TreeNode *node = root;
    TreeNode *next;
    while (node) {
        next = node;
        node = node->left;
        while (next) {
            cout << next->val << ", " ;
            next = next->next;
        }
        cout << endl;
    }
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution993 {
    private:
        int searched;
        queue<TreeNode*> que;
    public:

        bool isCousins(TreeNode* root, int x, int y) {
            int level = 0, clevel = 0;
            int secondVal, val;
            int check = 0;
            TreeNode* parent = NULL;

            if ( NULL == root) {
                return false;
            }
            TreeNode*   node;
            que.push(root); que.push(NULL);
            while ( !que.empty()) {
                node = que.front(); que.pop();
                check = 0;
                if ( node == NULL) {
                    level++;
                    if (que.empty()) break;
                    else que.push(NULL);
                } else {
                    // same level
                    if ( node->left) {
                        if ( node->left->val == x || node->left->val == y) {
                            check = 1;   
                            val = node->left->val;
                        }
                        que.push(node->left);
                    }
                    if ( node->right) {
                        if ( node->right->val == x || node->right->val == y) {
                            check = 1;
                            val = node->right->val;
                        }
                        que.push(node->right);
                    }
                    if ( check && level) {
                        if ( level == clevel) {
                            if ( node != parent && val == secondVal)
                                return true;
                        } else { 
                            clevel = level;
                            parent = node;
                            secondVal = val == x ? y :x;     
                        }
                    } else { check = 0;
                    }
                }

            }
            return false;
        }
};
class SolutionChallenge21 {
    public:
        bool checkStraightLine(vector<vector<int>>& coordinates) {
            int i;
            int dy = coordinates[1][1]-coordinates[0][1];
            int dx = coordinates[0][0]-coordinates[0][0];
            for ( i = 2; i < coordinates.size(); i++) {
                if (coordinates[i][1]-coordinates[i-1][1] != dy) return false;
                if (coordinates[i][0]-coordinates[i-1][0] != dx) return false;
            }
            return true;
        }
};
class SolutionChallenge22 {
    public:
        bool bs(int start, int end, int num) {
            double mid;
            if ( start >= end) {
                if ((start) == (num/start)) return true;
                return false;
            }
            mid = start + double((end-start)/2);
            if ( mid < (num/mid)) {
                return bs(mid+1, end, num);
            } else {
                return bs(start, mid, num);
            }
        }
        bool isPerfectSquare(int num) {
            return bs(1, num, num);
        }
};
class Solution862 {
    public: 
        struct node {
            int sum;
            int index;
            node(int sum, int index):sum(sum), index(index) {}
            node() {}
        };
        //min
        struct comp {
            bool operator()(const node& n1, const node& n2) {
                if ( n2.sum < n1.sum) return true;
                return false;
            }
        };
    public:
        int shortestSubarray(vector<int>& A, int K) {
            int sz = A.size(), i = 0, j;
            int res = INT_MAX;
            int lmax = 0;
            node tmp;
            priority_queue<node, vector<node>, comp> pq;
            vector<int> psum(sz+1, 0);
            pq.push(node(0,0));
            for ( auto n: A) {
                i++;
                psum[i] = psum[i-1]+n;
                pq.push(node(psum[i], i));
                while ( psum[i]-pq.top().sum >= K) {
                    res = min(res, i-pq.top().index);
                    pq.pop();
                }
            } 
            return res==INT_MAX ? -1 : res;
        }
        int shortestSubarraySlidingw(vector<int>& A, int K) {
            int sz = A.size();
            int start = 0, end = 0;
            int res = INT_MAX;
            int tmp = 0;
            if (sz < 1) return -1;
            while ( end < sz) {
                // enlarge the window
                while ( tmp < K && end < sz) {
                    tmp += A[end]; 
                    end++;
                }
                res = min(res, end-start);
                // Shrink the window
                while ( tmp >= K && start < end) {
                    tmp -= A[start];
                    start++;
                    res = min(res, end-start+1);
                }
            }
            return res == INT_MAX ? -1 : res;
        }
};
class SolutionChallenge23 {
    public:
        int findJudge(int N, vector<vector<int>>& trust) {
            vector<int> persons(N+1,0);
            persons[0] = 1;
            for (auto e : trust) {
                persons[e[0]]++;
            }
            int i = 0, res, nop = 0;
            for ( auto v: persons) {
                if (v == 0) {
                    res = i;
                    nop++;
                }
                i++;
            }
            if (nop != 1) return -1;
            persons.clear();
            persons.resize(N+1, 0);
            persons[0]++;
            for (auto e : trust) {
                if ( e[1] == res) {
                    persons[e[0]]++;
                }
            }
            i = 0;
            for ( auto v: persons) {
                if (v == 0) {
                    if (res == i) continue;
                    else return -1;
                }
                i++;
            }
            return res;
        }
};
class SolutionChallenge24 {
    public:
        string helper(string& num, int index, int k) {
            if ( k == 0 ) {
                return num;
            }
            if ( index + k == num.length()) {
                num.erase(index, k);
                return num;
            }
            if ( num[index] > num[index+1]) {
                num.erase(index, 1);
                return helper(num, index, k-1);
            } else {
                return helper(num, index+1, k);
            }

        }
        string removeKdigits(string num, int k) {
            int i = 0;
            int count = 0;
            string res;
            if ( k >= num.length()) {
                return "0";
            }
            res = helper(num, 0, k);
            for (i = 0; i < res.length(); i++) {
                if ( res[i] == '0') count++;
                else break;
            }
            return count == num.length() ? num : num.erase(0, count);
        }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class SolutionChallengeM16 {
    public:
        ListNode* oddEvenList(ListNode* head) {
            ListNode    *olist, *elist, *node = head;
            ListNode    *odd, *even;
            if (node) {
                odd = node;
                node = node->next;
                olist = odd;
            }
            if (node) {
                even = node;
                node = node->next;
                elist = even;
            }
            while ( node && node->next) {
                odd->next = node;
                odd = odd->next;
                node = node->next;
                even->next = node;
                even = even->next;
                node = node->next;
            }
            if ( node) odd->next = node;

            even->next = NULL;
            odd->next = elist;
            return olist;
        }
};
class SolutionChallengeM15 {
    public:
        int maxSubarraySumCircular(vector<int>& A) {
            int res = INT_MIN, sum = 0;
            int f_res = INT_MIN;
            int sz = A.size(), i = 0, j;
            for ( i = 0; i < sz; i++) {
                res = INT_MIN;
                sum = 0;
                for ( j = i; j < sz+i; j++) {
                    sum += A[j%sz];
                    res = max(res, sum);    
                    if ( sum < 0) {
                        sum = 0;
                    } 
                }
                f_res = max(f_res, res);
            }
            return f_res;
        }
};
class SolutionChallengeM17 {
    public:
        // t is sorted string,
        bool lsort(string s, string t, int start, int end) {
            int i, j;
            string tmp;
            map<char, int> hash;
            for ( i = start; i < start+end; i++) {
                hash[s[i]]++;
            }
            i = 0;
            for ( auto h : hash) {
                for ( j = 0; j < h.second; j++) {
                    tmp.push_back( h.first);
                }
            }
            if ( tmp == t) return true; 
            return false;
        }
        vector<int> findAnagrams(string s, string p) {
            int i, j; 
            vector<int> res;
            map<char, int> thash;
            map<char, int> shash;
            for ( auto c: p) {
                thash[c]++;
            }
            int slen = s.length(), tlen = p.length();
            for ( i = 0; i <tlen; i++) {
                shash[s[i]]++;
            }
            for ( ; i <= slen-tlen; i++) {
                if (shash == thash) {
                    res.push_back(i-tlen);
                }
                shash[s[i-tlen]]--;
                shash[s[i]]++;
                if (shash[s[i-tlen]] == 0) {
                    shash.erase(i-tlen);
                }
            }
            return res;
        }
};
class Gsol1 {
    public: 
        bool countDown(vector<int> & inp, int start, int end, int K) {
            int i; 
            for ( i = start; i < end; i++) {
                if (inp[i] != K--) return false;
            }
            return true;
        }
        int countD( vector<int>& inp, int K) {
            int sz = inp.size();
            int i = 0, res = 0;
            if ( sz < K) return 0;
            for (i = 0; i <= sz-K; i++) {
                if ( inp[i] == K && ( inp[i+K-1] == 1)) {
                    if (countDown(inp, i, i+K, K)) res++;
                }
            }
            return res;
        }
};
// TLE
class Gsol2 {
    public: 
        bool bs(int start, int end, int num) {
            double mid;
            if ( start >= end) {
                if ((start) == (num/start)) return true;
                return false;
            }
            mid = start + double((end-start)/2);
            if ( mid < (num/mid)) {
                return bs(mid+1, end, num);
            } else {
                return bs(start, mid, num);
            }
        }
        bool isPerfectSquare(int num) {
            if ( 0 == num) return true;
            return bs(1, num, num);
        }
        int perfect( vector<int>& inp) {
            int sz = inp.size();
            int i, j;
            vector<int> psum(sz+1, 0);
            int res = 0;
            for (i = 0; i < sz; i++) {
                psum[i+1] = psum[i]+inp[i];
                if (isPerfectSquare(psum[i+1])) {
                    res++;
                }
            }
            for ( i = 0; i < sz; i++) {
                for ( j = i+1; j <= sz; j++) {
                    psum[j] -= inp[i];
                    if ( j == i+1) continue;
                    if (isPerfectSquare(psum[j])) {
                        res++;
                    }
                }
            }
            return res;
        }
};
class StockSpanner {
    private: 
        vector<int> prices; // vector of prices along with days
        vector<int> days;
        int index;          // Index at which to insert the price

    public:
        StockSpanner() {
            index = 0;
        }
        int helper(int price, int idx) {
            int d = 0;
            if ( idx < 0) return 0;
            if ( price == prices[idx]) {
                d = days[idx];
            } else if ( price > prices[idx]) {
                d = days[idx];
                d += helper(price, idx-days[idx]);
            }
            return d;
        }
        int next(int price) {
            int res = 1;
            if ( index != 0 ) {
                res = 1+helper(price, index-1);
            } 
            index++;       
            prices.push_back(price);
            days.push_back(res);
            return res;
        }
};
/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */


// Merge sort operation.
// Create a a new array and then merge the intervalsl 

class SolutionChallengeMay23 {
    public:
        vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
            vector<vector<int>> res;
            int i = 0, j = 0; 
            vector<int> tmp(2,0);
            vector<int> vA, vB;
            int sA = A.size(), sB = B.size();
            while ( i < sA && j < sB) {
                vA = A[i];
                vB = B[j];
                if ( vA[0] <= vB[0]) {
                    if (vA[1] < vB[0]) { 
                        // no intersection
                        i++; continue;
                    } else if (vA[1]== vB[0]) {
                        tmp[0] = vA[1];
                        tmp[1] = vA[1];
                        i++;
                        res.push_back(tmp);
                        continue;
                    } 
                    if ( j < sB && vA[1] > vB[1]) {
                        res.push_back(vB);
                        j++; 
                        continue;
                        //if ( j >= sB) break;
                        //vB = B[j];
                    }
                    if (vA[1] <= vB[1]) {
                        tmp[0] = vB[0];
                        tmp[1] = vA[1];
                        res.push_back(tmp);
                    }
                    i++;
                } else {
                 if (vB[1] < vA[0]) { 
                        // no intersection
                        j++; continue;
                    } else if (vB[1]== vA[0]) {
                        tmp[0] = vB[1];
                        tmp[1] = vB[1];
                        j++;
                        res.push_back(tmp);
                        continue;
                    } 
                    if( i < sA && vB[1] > vA[1]) {
                        res.push_back(vA);
                        i++;
                        //if ( i >= sA) break;
                        //vA = A[i];
                        continue;
                    } else if (vB[1] <= vA[1]) {
                        tmp[0] = vA[0];
                        tmp[1] = vB[1];
                        res.push_back(tmp);
                    }
                    j++;
            }
        }
        return res;
    }
};

class Solution973 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        multimap<double, int> hash;
        vector<vector<int>> res;
        vector<int> tmp;
        int i = 0;
        double dist;
        for ( auto e: points) {
            dist = e[0]* e[0]+e[1]*e[1];
            dist = sqrt(dist);
            hash.insert(pair<double, int> (dist,i));
            i++;
        }
        i = 0;
        for ( auto h : hash) {
            if ( i >=K) break;
            res.push_back(points[h.second]);
            i++;
        }
        return res;
    }  
};

//  Graph problem. if no cycles, can finish the courses
// Directed Graph, Use DFS for cycle detection
class Solution207 {
    typedef enum {
        WHITE = 1,
        GREY = 2,
        BLACK = 3
    }color;
    
    private: 
        vector<color> visited;
        vector<int> parent;
        bool cycle; 
    void initUF(int nums) {
        int i;
        parent.resize(nums, 0);
        for (i = 0; i < nums; i++) {
            parent[i] = i;
        }
    }
    int findUF(int num) {
        if( num == parent[num]) return num;
        parent[num] = findUF(parent[num]);
        return parent[num];
    }
    int unionUF(int e1, int e2) {
        if ( findUF(e1) == findUF(e2)) return false;
        parent[parent[e1]] = parent[e2];
        return true;
    }
        
    public:
    void dfs(vector<vector<int>>& graph, int v) {
        visited[v] = GREY;
        for ( auto e: graph[v]) {
            switch(visited[e]) {
                case WHITE:
                    dfs(graph, e); break;
                case GREY:
                    cycle = 1; break;
                case BLACK:
                    ;
            };
        }
        visited[v] = BLACK;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int sz = prerequisites.size();
        cycle = false;
        int i;
        
        // Create the Graph Adjacency List
        vector<vector<int>> graph(numCourses);
        for (auto c: prerequisites) {
            graph[c[0]].push_back(c[1]);
        }
        
        // INitialise the visited color
        visited.resize(numCourses, WHITE);
        
        for ( i = 0; i < numCourses; i++) {
            if ( visited[i] == WHITE) {
                dfs(graph,i);
            }
        }
        return !cycle;
    }
};
class SolutionChallengeJune26 {
//  Pre-order traversal. 
//  pass the value to each node from previous NOdes to determine the value at the node
//  And at each node sum the value returned from children
    public:
    int recurse(TreeNode* root, int inc) {
        int lval = 0, rval = 0;
        int val;
        if ( NULL == root) {
            return inc;
        }   
        val = (inc+root->val);
        if ( root->left) {
            lval = val*10;
            lval = recurse(root->left, lval);
        }
        if (root->right)
        {
            rval = val*10;
            rval = recurse(root->right, rval);
        }    
        if (lval || rval ) return lval + rval;
        return val;
    }
    
    int sumNumbers(TreeNode* root) {
        return recurse(root, 0);
    }
};

class SolutionChallengeJuly6 {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size()-1;
        vector<int> res(i+2,0);
        for ( ;i >=0; i--) {
            if ( digits[i] == 9) {
                digits[i] = 0;
                if ( i == 0) {
                res[0] = 1;
                return res;
            }
            } else {
                digits[i]++;
                break;
            }
        }
        return digits;
     }
};

class Solution957 {
public:
    vector<int> tmpv;
    void getNextState(vector<int>& cells) {
        int i, tmp, size = cells.size();
        tmpv = cells;
        
        for ( i = 1; i < size-1; i++) {
            tmp = tmpv[i-1] ^ tmpv[i+1];
            cells[i] = tmp ? 0 : 1;
        }
        cells[0] = 0;
        cells[size-1] = 0;
    }
    vector<int> prisonAfterNDays3(vector<int>& cells, int N) 
    {
        vector<int> Ans(8, 0);
        vector<vector<int> > lookup;
        
        while(N--)
        {
            for(int j=1; j<7; ++j)
            {
                if(cells[j-1] ^ cells[j+1]) Ans[j] = 0;     //both are different ie (1,0) or (0,1) using XOR
                else Ans[j] = 1;
            }
            
            if(lookup.size() && lookup.front() == Ans)      //found in the lookup table (ie cycle has begun)
            {
                return lookup[N % lookup.size()];
            }
            else lookup.push_back(Ans);                     //not found in the lookup (ie no cycle yet)
            
            cells = Ans;                                    //update cells
        }
        
        return cells;
    }
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        if ( N == 0 ) return cells;
        int size = cells.size();
        int i = 0;
        vector<vector<int>> cont;
    
        while( N--) {
            getNextState(cells);
            if ( cont.size() == 0 || cont.front() != cells) {
                cont.push_back(cells);
            } else {
                cout << "matched i: " << i << "cont size :" << cont.size() << endl;
                 return cont[N % cont.size()];
            }
        }
        return cont[cont.size()-1];
    }
};

class SolutionChallengeJuly7 {
public:
    int perim;
    vector<vector<bool>> visited;

    int dfs (vector<vector<int>> grid, int x,int y) {
        int rows = grid.size();
        int cols = 0;
        if (rows) cols = grid[0].size();

        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            if (!visited[x][y]) {
            visited[x][y]= true;
            perim += 4;
            if (x-1 >= 0 && grid[x-1][y]) { 
                dfs(grid, x-1, y);
                perim--;
            }
            if (x+1 < rows && grid[x+1][y]) {
                dfs(grid, x+1, y);
                perim--;
            }
            if (y-1 >= 0 && grid[x][y-1]) { 
                dfs(grid, x, y-1);
                perim--;
            }
            if (y+1 < cols && grid[x][y+1]) {
                dfs(grid, x, y+1);
                perim--;
            }
        }
        }
        return 0;
    }
    int islandPerimeter(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = 0;
        bool start = false;
        if (rows) cols = grid[0].size();
        visited.resize(rows, vector<bool>(cols, false));

        perim = 0;
        int i,j;
        for ( i = 0; i < rows;i ++) {
            for (j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    start = true;
                    break;
                }
            } 
            if (start) break;
        }
        if ( i < rows && j < cols) dfs(grid, i, j);
        return perim;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class SolutionChallengeJuly9 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        int res = 0, tmp = 0;
        int sz = 0;
        deque<TreeNode*> que;
        TreeNode    *node = NULL;
        if ( NULL == root) return res;
        que.push_back(root);
        while (!que.empty()) {
            sz = que.size();
            tmp = 0;
            while ( !que.empty() && NULL == que.front()) {
                que.pop_front();tmp++;
            }   
            while ( !que.empty() && NULL == que.back()) {
                que.pop_back();tmp++;
            }    
            sz -= tmp;
            res = max(sz, res);
            while ( sz) {
                node = que.front(); que.pop_front();
                sz--;
                if ( node) {
                    que.push_back(node->left); // push left right without NULL check.
                    que.push_back(node->right);
                } else {
                    que.push_back(NULL);
                    que.push_back(NULL);
                }
            }
        }
        return res;
    }
};
class SolutionChallengeJuly15 {
public:
    string reverseWords(string s) {
        int i = 0, j = s.length()-1;
        int len = s.length();
        int end = 0, start = 0;
        
        for ( ; j >=0 && s[j]== ' '; j--) {
            i++;
        }
        s.erase(j+1,i);

        for ( i = 0; i < j; i++,j--) {
            swap(s[i], s[j]);
        }

        for (i = 0, j = s.length()-1 ; j >=0 && s[j]== ' '; j--) {
            i++;
        }
        s.erase(j+1,i);

        for ( i = 0; i < len; i++) {
            while ( s[i] == ' ' && i < len) i++;
            start = i;
            while ( s[i] != ' ' && i < len) i++;
            end = i-1;
            j = end;
            for (i = start; i < j; i++, j--) {
                swap(s[i], s[j]);
            }
            i = end++;
        }
        return s;
    }
};
/*July 18 Challenge*/
class Solution210 {
private: 
    vector<bool> visited;
     vector<int> schedule;
public:
    vector<vector<int>> createGraph(vector<vector<int>> edges, int v) {
        vector<vector<int>> res(v);
        vector<int> tmp;
        for ( auto e : edges) {
            res[e[0]].push_back(e[1]);
        }
        return res;
    }
    int getZeroIndegreeVertex(vector<vector<int>>& graph) {
        int v = graph.size(), i;
        vector<int> indegree(v,0);
        for ( auto list : graph) {
            for ( auto dest: list) {
                indegree[dest]++;
            } 
        }
        for ( i = 0; i < v; i++) {
            if (indegree[i]==0) return i; 
        }
        return 0;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph;
        graph = createGraph(prerequisites, numCourses);
        int v = getZeroIndegreeVertex(graph);
        visited.resize(graph.size(), false);
        dfs(graph,v);
        if ( schedule.size() == numCourses)
            return schedule;
        schedule.clear();
        return schedule;
    }
    void dfs(vector<vector<int>>& graph, int v) {
        if (! visited[v]) {
            visited[v] = true;
            for ( auto edge : graph[v]) {
                dfs(graph, edge);
            }
            schedule.push_back(v);
        }
    }
};
class Solution67 {
public:
    string addBinary(string a, string b) {
        int alen = a.length(), blen = b.length();
        string res, tstr;
        int i;
        int xlen = max(alen, blen);
        int mlen = min(alen, blen);
        char carry = '0';
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        for (i = 0 ; i < mlen; i++) {
            if ( a[i] == b[i]) {
                res.push_back(carry);
                if ( a[i] == '1') carry = '1';
                else carry = '0';
            } else {
                if ( carry == '1') {
                    res.push_back('0');
                } else {
                    res.push_back('1');
                }
            }
        }
        if ( alen > blen) {
            tstr = a;
        } else tstr = b;

            for ( ; i < xlen; i++) {
                if ( carry == '1') {
                    if ( tstr[i] == '1' ) res.push_back('0');
                    else { res.push_back('1'); carry = '0';}
                } else {
                    res.push_back(tstr[i]);
                }
            }
        if ( carry =='1') res.push_back(carry);
        reverse(res.begin(), res.end());
    return res;
    }
};
class Solution153 {
public:
    int bs(vector<int>& nums, int start, int end) {
        int mid;
        if ( start >= end) return nums[end];
            mid = start + (end-start)/2;
            mid = mid == start ? mid+1 : mid;
            if ( nums[start] >= nums[mid]) {
                return bs(nums, start+1, mid);                
            }
        return min(nums[start],bs(nums, mid, end));
    }
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size()-1;
        if ( nums[start] >= nums[end])
            return bs(nums, start, end);
        return nums[start];
    }
    int findMin2(vector<int>& nums) {
        int res = INT_MAX;
        for ( auto e :nums) {
            res = min(res, e);
        }
        return res;
    }
};

class Solution621 {
    class task {
        public:
        char c;
        int count;  // how many of these tasks need to be scheduled.
        task(char cc, int c): c(cc), count(c) {}
        task() {}
    };
    struct comp {
        // Max PQ.
        bool operator()(const task& t1, const task& t2) {
            return t2.count > t1.count;
        }
    };
    public:
    // Trick: Maintain a map with count and next time
    int leastInterval(vector<char>& tasks, int n) {
        int res = 0, oldres = 0;
        int i;
        int sz = tasks.size();
        map<char, int> count;
        map<char, int> time;
        priority_queue<task, vector<task>, comp> pqMax;
        for ( auto c: tasks) {
            count[c]++ ;
        }
        for ( auto e : count) {
            pqMax.push(task(e.first, count[e.second]));
        }
    
        for ( i = 0; i < sz; ) {
            task t = pqMax.top(); pqMax.pop();
            res++;
            time[t.c] = n;
        oldres = res;    
        for ( auto c: count) {
            if (c.second && time[c.first] <= res) {
                res++;  // time take to do this work
                time[c.first] = res+n;
                count[c.first]--;
                i++;
                }
            }
        if ( oldres == res) {
            // no task could be added
            res++;
        }
        }
        return res;
    }
};
// Connected components problem. 
// As and when new edges are added, different components unite. 
// So start with all the fallen bricks. 
// and add the dropped bricks (edges) to see how many bricks fall
class DSU {
    public: 
    vector<int> parent;
    vector<int> count;
    void initUF(int size) {
        parent.resize(size,0);
        count.resize(size,0);
        int i = 0;
        for ( i = 0; i < parent.size(); i++) {
            parent[i] = i;
            count[i] = 1;
        }
    }
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // optimization
            return parent[x];
        }
        return x;
    }
    int unionF(int x, int y) {
        if ( find(x) != find(y)) {
            count[find(x)] += count[find(y)];
            parent[find(y)] = find(x); // Functionality
        }
        return parent[x];
    }
    
};
class Solution803 {
public:
    vector<vector<int>> visited;
    vector<vector<int>> brickPresent;
    
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int rows = grid.size();
        int cols;
        if (rows) cols = grid[0].size();
        vector<int> res(hits.size(), 0);
        int i, x, y;
        
        vector<vector<int>> copy_visited;

        
        brickPresent.resize(rows,vector<int>(cols,0));
        visited.resize(rows,vector<int>(cols,0));
        copy_visited = visited;
        
        // Remove all the bricks that need to be removed
        for ( auto brickPos : hits) {
            if (grid[brickPos[0]][brickPos[1]]) {
                grid[brickPos[0]][brickPos[1]] = 0;
                brickPresent[brickPos[0]][brickPos[1]] = 1;
            }
        }
        
        // Now get the connected components of the graph for the top row only
        // All the other bricks are acutally fallen
        x = 0;
        for (y = 0; y < cols; y++) {
            if ( grid[x][y] == 1) {
                //check the connections x+1, x-1, j+1, j-1
                dfs(grid, x,y);
            }       
        }
        
        for (i = hits.size()-1; i>=0; i--) {
            x = hits[i][0]; y = hits[i][1];
        //    visited = copy_visited;
            if (brickPresent[x][y]) {
                grid[x][y] = 1;
                if (isTop(grid, x,y)) {
                    res[i] = dfs(grid, x, y)-1;
                }
            }
        }
        return res;
    }
    int dfs(vector<vector<int>>& grid, int x, int y) {
        int count = 0;
        int rows = grid.size(), cols = grid[0].size();

        //if (!visited[x][y]) {
        if (grid[x][y] == 1) {    
            if (isTop(grid, x,y)) grid[x][y] = 2;
            count++;
            if ( x-1 >=0 && grid[x-1][y] == 1) count += dfs(grid, x-1,y);
            if ( x+1 <rows && grid[x+1][y] == 1) count += dfs(grid, x+1,y);
            if ( y-1 >=0 && grid[x][y-1] == 1) count += dfs(grid, x,y-1);
            if ( y+1 <cols && grid[x][y+1] == 1) count += dfs(grid, x,y+1);
        }
        return count;
    }
    bool isTop(vector<vector<int>>& grid, int x, int y) {
        int rows = grid.size(), cols = grid[0].size();
        if ( x == 0) return true;
        if (grid[x][y] == 2) return true;
        if ( x-1 >=0 && grid[x-1][y] == 2) return true;
        if ( x+1 <rows && grid[x+1][y] == 2) return true;
        if ( y-1 >=0 && grid[x][y-1] == 2) return true;
        if ( y+1 <cols && grid[x][y+1] == 2) return true;
        return false;
    }
};
class Solution1103 {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> res(num_people, 0);
        int round = 0, tmp;
        int i = 1;
        int candiesForAll = ((num_people ) * (num_people+1))/2;
        int candies_needed = round * num_people;
        candies_needed += candiesForAll;
        
        while ( candies_needed < candies) {
            round++;
            candies -= candies_needed;
            candies_needed = round * num_people * num_people;
            candies_needed += candiesForAll;
        }
        // if some rounds have been completed, candies each person should have
        // (person_index * round ) + (allRounds * num_people)
        if (round) {
            i = 1;
            while ( i <= num_people) {
                res[i-1] += (((round) * (round-1))/2) *num_people + i*(round);
                i++;
            }
        }
        i = 1;
        while ( candies && i <= num_people) {
            tmp = round*num_people+i;
            if (tmp < candies) {
                res[i-1] += tmp;
                candies -= tmp;
            } else {
                res[i-1] += candies;
                candies = 0;
            }
            i++;
        }
        return res;
    }
};

class Solution967 {
public:
    long int pow(int base, int exp) {
        long int res = 1;
        int i;
        for( i = 0; i < exp; i++) {
            res *= base;
        }
        return res;
    }
    vector<int> numsSameConsecDiff(int N, int K) {
        int i,j;
        int x,y, tmp,n;
        vector<int> res;
        for ( i = 1; i <=9 ; i++) {
            if (i+K <= 9) {
                x = i; 
                y = i+K;
            } else if ( i-K>=0 ) {
                x = i; 
                y = i-K;
            } else {
                continue;
            }
            tmp = 10*x+y;
            if ( N == 2) {
                    res.push_back(tmp);
                    continue;
            }
            for ( j = 2; j < N; j++) {
                n =  j%2 ? y: x;
                tmp = tmp*10+n;   
                res.push_back(tmp);             
            }
        }
        return res;
    }
};
class Solution454 {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        map<int, int> hash1, hash2;
        int i, j;
        int count = 0, key;
        for ( i = 0; i < A.size(); i++) {
            for ( j = 0; j < B.size(); j++) {
                hash1[A[i]+B[j]]++;
            }
        }
        for ( i = 0; i < C.size(); i++) {
            for ( j = 0; j < D.size(); j++) {
                hash2[C[i]+D[j]]++;
            }
        }
        for ( auto e :hash1) {
            key = 0 - e.first;
            if ( hash2[key]) count += e.second*hash2[key];
        }
        return count;
    }
};
class Solution1406 {
public:
    vector<int> dp;
    string stoneGameIII(vector<int>& stoneValue) {
        int sz = stoneValue.size();
        dp.resize(sz,INT_MIN);
        int i, k, pick, n = sz, sv;
        // From which index to pick the stones
        for ( i = n-1; i >=0; i--) {
            // how many stones to pick
            sv = 0;
            for ( k = 0; k < 3 && k+i < n; k++) {
                sv += stoneValue[i+k];
                pick =  sv - (i+k+1 < n ? dp[i+k+1] : 0);
                dp[i] = max(pick, dp[i]);
            }
        }
        if ( dp[0] == 0) return "Tie";
        if ( dp[0] > 0) return "Alice";
        return "Bob";
    }
};

class Solution215 {
    // [3,2,3,1,2,4,5,5,6] 4th val = 4
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq;
        for ( auto e : nums) {
                pq.push(e);
                if ( pq.size() == nums.size()+1-k) return pq.top();
        }
        return pq.top();
    }
};

// Breadth First search from each vertex 
class Solution310 {
public:
    map<int, int> indegree;
    
    void adjustDegree(vector<vector<int>>& graph, int v) {
        for ( auto e: graph[v]) {
            if (indegree.count(e)) indegree[e]--;
        }
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<int> resp;
        vector<int> tmp;
        int i = 0;
        vector<vector<int>> graph(n);
        for ( auto e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
            indegree[e[0]]++;
            indegree[e[1]]++;
        }
        
        while ( indegree.size() > 2) {
            tmp.clear();
            for ( auto d : indegree) {
                if (d.second ==1 ) {
                    tmp.push_back(d.first);
                }
            }
            for (auto i: tmp) {
                // remove this vertex from indegree list
                adjustDegree(graph, i);
                indegree.erase(i);
            }  
            i++;
        }
        for ( auto e : indegree) {
            resp.push_back(e.first);
        }
        return resp;
    }
};

bool compare (vector<int>& one, vector<int> two) {
        return (one[1] < two[1]);
    }
class Solution630 {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), compare);
        // once the courses are sorted in order of increasing finished time
        // it is activity scheduling problem.
        // Greedy approach
        // adjust the start time of the courses
        int sz = courses.size();
        priority_queue<int> pq;
        int i, res = 0;
        // Pick the coueses now
        int curTime = 0;
        for ( auto c: courses) {
            pq.push(c[0]);
            curTime += c[0];
            if (curTime > c[1]) {
                curTime -= pq.top();pq.pop();
            }
        }
        return pq.size();
    }
};

class Solution870 {
public:
    vector<int> advantageCount2(vector<int>& A, vector<int>& B) {
        vector<int> res(A.size());
        vector<int> :: iterator it;
        int i = 0,j;
        sort(A.begin(), A.end());
        
        i = 0;
        for ( auto b: B) {
            it = upper_bound(A.begin(), A.end(), b);
            if ( it != A.end()) {
                res[i] = *it;
                A.erase(it);
            } else {
                res[i] = *A.begin();
                A.erase(A.begin());
            }
            i++;
        }
        return res;
    }
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        vector<int> res(A.size());
        
        int i = 0,j;
        multiset<int> mset;
        multiset<int> :: iterator it;
        for (auto a: A) {
            mset.insert(a);
        }
        
        i = 0;
        for ( auto b: B) {
            it = mset.upper_bound(b);
            if ( it != mset.end()) {
                res[i] = *it;
                mset.erase(it);
            } else {
                res[i] = *mset.begin();
                mset.erase(mset.begin());
            }
            i++;
        }
        return res;
    }
};
class Solution1433 {
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        int dir = 1;
        int i;
        for ( i = 0; i < s1.size(); i++) {
            if ( s1[i]== s2[i]) continue;
            if ( s1[i] > s2[i]) dir = 1;
             else dir = 0;
             break;
        }
        for ( ; i < s1.size(); i++) {
            if ( s1[i] == s2[i]) continue;
            if ((s1[i] > s2[i]) != dir) {
                return false;
            }
        }
        return s1.size() == s2.size();
    }
};


class Solution1497 {
// Simple Hash map solution. 
//Think of how to convert the problem to 2 sum
// 

public:
    bool canArrange(vector<int>& arr, int k) {
        map<int, int> hash;
        int tmp;
        for (auto a : arr) {
            tmp = a%k;
            tmp = tmp < 0 ? tmp+k : tmp;
            hash[tmp]++;
        }
        // for each entry in hash there has to be 
        //equal no of complementary entries
        int c;
        int t1, t2;
        for ( auto h: hash) {
            if ( h.first == 0 && hash[0] % 2 == 0) continue;
            t1 = hash[h.first];
            t2 = hash[k-h.first];
            if ( t1 != t2) return false; 
            hash.erase(k-h.first);  
        }
        return true;
    }
};

class Solution1590 {
public:
    int minSubarray(vector<int>& nums, int p) {
        int i = 1, prev = 0;
        vector<long> psum(1+nums.size(), 0);
        map<int, int> hash;
        int tsum = 0, sz = nums.size();
        for ( auto a: nums) {
            psum[i] = psum[i-1]+a;
            i++;
        }
        tsum = psum[sz]%p;
        if ( tsum == 0 ) return 0;

        int res = sz, tmp;
        i = 0;
        for ( auto a: psum) {
            tmp = psum[i]%p-tsum;    
            tmp = (tmp+p)%p;
            if ( hash.count(tmp)) {
                res = min(res, i-hash[tmp]);
            }
            hash[psum[i]%p] = i; // update the index  
            i++;
        }
        return res == sz ? -1 : res;
    }
};

class Solution785 {
    // simply keep a set as a color array with white and Black colors
    // 1 is white and 2 is black
    
public:
    vector<int> visited;
    bool bfs(vector<vector<int>>& graph, int s, vector<int>& color) {
        int u, col;
        queue<int> que;
        que.push(s);
        visited[s] = true;
        while ( !que.empty()) {
            u = que.front(); que.pop();
            if ( color[u] == 1) col = 2;
            else col = 1;
            for ( auto v: graph[u]) {
                if ( color[v] == color[u]) {
                    return false;
                } 
                if ( !visited[v]) {
                    visited[v] = 1;
                    color[v] = col;
                    que.push(v);
                }
            }
        }
        return true;
    }
    
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> color(graph.size(), 0);
        visited.resize(graph.size(), 0);
        int i;
        for ( i = 0; i < graph.size(); i++) {
            if ( !visited[i]) {
                color[i] = 1;
                visited[i] = 1;
                if (!bfs(graph, i, color)) return 0;
            }
        }
        return true;
    }
};

class Solution978 {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int start = 0, end = 0;
        int sz = arr.size();
        int tmp, res, k;
        if ( sz <= 2) return sz;
        res = 2;
        end = 1;
        
        while ( end < arr.size()) {
            k = end-1;
            if (( arr[k] > arr[k+1]) && arr[k+2] > arr[k+1]) {
                end += 1;
            } else if (( arr[k] < arr[k+1]) && arr[k+2] < arr[k+1]) {
                end += 1;
            } else {
                end++;
                start++;
            }
            res = max(res, end+1-start);
        }
        return res;
    }
};

class Solution213 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> tp(n, 0);
        vector<int> tp1(n, 0);
        int i;
        if ( n == 0 ) return 0;
        if ( n == 1) return nums[0];
        if ( n == 2) return max(nums[0], nums[1]);
        
        tp[0] = nums[0];
        tp[1] = max(nums[0], nums[1]);
        // Don't consider the last element
        for ( i = 2; i < n-1; i ++) {
            tp[i]  = max(nums[i]+tp[i-2], tp[i-1]);
        }
        
        tp1[0] = 0;
        tp1[1] = nums[1];
        // don't consider the first element
        for ( i = 2; i < n; i ++) {
            tp1[i]  = max(nums[i]+tp1[i-2], tp1[i-1]);
        }
        
        return max(tp[n-2], tp1[n-1]);
    }
};
class Solutiont {
    // Sliding window with Frequency Map
public:
    bool allK(unordered_map<char, int>& hash, int k) {
        for ( auto entry: hash) {
            if (entry.second < k && entry.second != 0) return false;
        }
        return true;
    
    }
    int longestSubstring(string s, int k) {
        return 1;
    }
    /*
    int longestSubstring(string s, int k) {
        unordered_map<char, int> hash;
        int res = 0, tmp;
        char c;
        int start = 0, end = 0, t;
        for (auto c : s) {
            hash[c]++;
            if (hash[c]) == 1 { 
                count++;
            }
        }
        for (int i = 1; i <= count; i++) {
            while ( end < s.size()) {
                hash[c]++;
                if (hash[c] == 1) {
                    tcount++;
                    if (tcount > i) {

                    }
                }                
            end++;
            res = max(res, tmp);
            }
        }
            if (hash[c]) {
                // probably a hit. Check
                if (allK(hash, k)) {
                    res = max(res, end+1-start);
                } else {
                    // try squeezing the window
                    do {
                        t = start;
                        hash[t++]--;
                        if (allK(hash, k)) {
                            res = max(res, end+1-start);
                        }
                    } while( hash[c] >= k);
                }
            end++;
        }
        return res;
    }*/
};
class Solution416 {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(); 
        int subsetSum = 0;
        int i, j;
        
        for (auto e: nums) {
            subsetSum += e;
        }
        if ( subsetSum%2 == 0) {
            subsetSum /= 2;
        } else {
            return false;
        }
        
        vector<vector<bool>> dp(n+1, vector<bool>(subsetSum+1,false));
        // base case
        dp[0][0] = true;
        // for all the values in the given array
        for ( i = 1; i <= n; i++) {
            //check if subset sum is achievable using this value AND not using this value
            for ( int j = 0; j <= subsetSum; j++) {
                dp[i][j] = dp[i-1][j] ; // This element is not included   
                if ( j-nums[i-1]>=0) {
                    dp[i][j] = dp[i][j] || (dp[i-1][j-nums[i-1]]) ; 
                }
            }
        }
        return dp[n][subsetSum];
    }
};

class Solution239 {
public:
    int getMax(unordered_map<int, int>& hash) {
        int tmax = INT_MIN;
        for (auto h: hash) {
            if (h.second) tmax = max(h.first, tmax);
        }
        return tmax;
    }
    vector<int> maxSlidingWindow_B(vector<int>& nums, int k) {
        vector<int> res;
        unordered_map<int, int> hash;
        int i, tmax = INT_MIN;
        for (i = 0; i < k; i++) {
            tmax = max(nums[i], tmax);
            hash[nums[i]]++;
        }
        res.push_back(tmax);
        for ( i = 0; i+k < nums.size(); i++) {
            hash[nums[i]]--;
            hash[nums[i+k]]++;
            // if the number going out is the max number itself
            if (hash[nums[i]] == 0) {
                tmax = getMax(hash);
            } else {
                tmax = max(tmax, nums[i+k]);
            }
            res.push_back(tmax);
        }
        return res;
    }
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> ms;
        multiset<int>::iterator it;
        multiset<int>::reverse_iterator rit;
        vector<int> res;
        int tmax = INT_MIN, i, j = 0;
        for (i = 0; i < k; i++) {
            ms.insert(nums[i]);    
        }
        rit = ms.rbegin();
        res.push_back(*rit);
        for ( ; i < nums.size(); j++, i++) {
            it = ms.find(nums[j]);
            ms.erase(it);
            ms.insert(nums[i]);
            rit = ms.rbegin();
            res.push_back(*rit);
        }
        return res;
    }
};
class Solution644 {
public:
    double max(double x, double y) {
        return (x>=y ? x : y);
    }
    double findMaxAverage(vector<int>& nums, int k) {
        vector<int> psum;
        int prev = 0;
        double res = INT_MIN;
        int tmax = INT_MIN;
        psum.push_back(0);
        for (auto n : nums) {
            prev += n;
            psum.push_back(prev);
        }
        for ( int i = k; i <= nums.size(); i++) {
            for ( int j = i; j <= nums.size(); j++) {
                tmax = max(tmax, psum[j]-psum[j-i]);
            }
            res = max(res, (double(tmax)/double(i)));
        }
        return res;
    }
};

class Solution605 {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        vector<int> f = flowerbed;
        int i = 0;
        if (f.size() == 1 && f[0] == 0 && n == 1) {
            return true;
        }
        if ( f[0] == 0 && f[1] == 0) {
            f[0] = 1;
            n--;
            i = 2;
        }
        
        for (; i+1 < f.size(); i++) {
            if ( 0 == n) return true;
            if (f[i] == 0 && f[i-1] == 0 && f[i+1] == 0) {
                f[i] = 1;
                n--;
                i++;
            }
        }
        if ( f[f.size()-1] == 0 && f[f.size()-2] == 0) {
            f[f.size()-1] = 1;
            n--;
        }
        if ( n <= 0) return true;
        return false;
    }
};

class Solution163 {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        int j = 0;
        vector<string>resp;
        string tresp;
        int start, end;
        bool done = false;
        start = lower; end = upper;
        for ( auto e: nums) {
            if ( e == start) {
                start++; 
            } else if ( e > start) {
                end = e-1;
                if ( start < end) tresp = string(to_string(start))+"->"+string(to_string(end));
                else if ( start == end) tresp = string(to_string(start));
                resp.push_back(tresp);
                start = e+1;
                end = upper;
                if ( e == upper) done = true;
            }
        }
        if ( !done) {
            if ( start < end) tresp = string(to_string(start))+"->"+string(to_string(end));
            else if ( start == end) tresp = string(to_string(start));
                resp.push_back(tresp);
        }
        return resp;
    }
};

class Solution1010 {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int res = 0;
        int tmp = 0;
        unordered_map<int, int> hash;
        for ( auto e : time) {
            if (0 == e%60) {
                res += hash[0];
            } else {
                res += hash[60-e%60];
            }
            hash[e%60]++;
        }
        return res;
    }
};

class Solution116 {
public:
    TreeNode* helper(TreeNode* root, TreeNode* rNext) {
        TreeNode* next = NULL;
        if ( NULL == root) return root;
        root->next = rNext;
        if ( rNext ) {
                if (rNext->left) {
                    next = rNext->left;
                } else if ( rNext->right) {
                    next = rNext->right;
                }
        }
        if ( root->left) {
            root->left->next = root->right ? root->right : next;
            helper(root->left,root->left->next);
        }
        if (root->right) {
            root->right->next = next;
            helper(root->right, next);
        }
        return root;
    }
    
    TreeNode* connect(TreeNode* root) {
        return helper(root, NULL);
    }
};

class Solution80 {
public:
    
    int removeDuplicates(vector<int>& nums) {
        int rindex, windex = 0;
        int prev = INT_MIN;
        int count = 0;
        if ( nums.size() < 3) return nums.size();
        for (int i = 0; i < nums.size(); i++) {
                    if ( prev != nums[i]) {
                        count = 1;
                        prev = nums[i];
                    } else {
                        count++;
                    }
                    if (count <= 2) {
                        nums[windex] = nums[i];
                        windex++;
                    }
                
        }
        return windex;
    }
};

class Solution563 {
public:
    int helper(TreeNode* root, int& tilt) {
        int sum = 0;
        int lsum = 0, rsum = 0;
        if ( NULL == root) return 0;
        if ( root->left == NULL && root->right == NULL) {
            sum = root->val; 
            tilt    += 0;
            return sum;
        } 
        if ( root->left) {
            lsum= helper(root->left, tilt);
        }
        if ( root->right) {
            rsum= helper(root->right, tilt);
        }
        tilt += lsum > rsum ? lsum-rsum : rsum-lsum;
        return lsum+rsum+root->val;
    }
    int findTilt(TreeNode* root) {
        int tilt = 0;
        helper(root, tilt);
        return tilt;
    }
};
class Solution334 {
public:
    bool increasingTriplet(vector<int>& nums) {
        int start = 0, end = start+1;
        int first, second;
        if ( nums.size() < 3) return false;
        first = nums[0]; 
        second = INT_MAX;
        for ( end = 1; end < nums.size(); ) {
            if ( nums[end] > second) {
                return true;
            } else if ( nums[end] > first) {
                second = nums[end];
            } else {
                first = nums[end];
            }
            end++;
        }
        return false;
    }
};
class Solution912 {
public:
    void merge(vector<int>& num, vector<int>& res, int start, int size) {
        int second = size + start;
        int end2 = start+2*size;
        int end1 = start+size;
        int i = start, j = second;
        while ( i < end1 && j < end2) {
            if ( num[i] < num[j]) {
                res[start++] = num[i++];
            } else {
                res[start++] = num[j++];
            }
        }
        while ( i < end1) {
            res[start++] = num[i++];
        }
        while ( j < end2) {
            res[start++] = num[j++];
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        int i = 0; 
        vector<int> res(nums.size(), 0);
        int start = 0;
        for ( int s = 1; s < nums.size(); s = s*2) {
            for ( start = 0; start < nums.size(); start += 2*s) {
                merge(nums, res, start, s);
            }
            nums = res;
        }
        return res;
    }
};

class Solution240 {
public:
    int rows, cols;
    // r1, c1 is the starting corrdinate of the matrix in. which to serach for the target
    // l is the lenght of the matrix and w being the width
    bool helper2(vector<vector<int>> matrix, int target, int r1, int c1, int l, int w)  {
        bool res = false;
        if ( l < 0 || w < 0) {
            return false;
        }
        if ( l ==  0 && w == 0) {
            return target == matrix[r1][c1];
        }
        int midl = l/2, midw = w/2;
        
        if ( target == matrix[r1+midl][c1+midw]) {
            return true;
        } else if (target > matrix[r1+midl][c1+midw]) {
            res |= helper(matrix, target, r1+midl+1, c1+midw+1, rows-1-( r1+midl+1), cols-1-(c1+midw+1));
            res |= helper(matrix, target, r1, c1+midw+1, midl, cols-1-(c1+midw+1));
            res |= helper(matrix, target, r1+midl+1, c1, rows-1-(r1+midl+1), midw);
            return res;
        } else {
            return helper(matrix, target, r1, c1, midl, midw);
        }
        return false;
    }
    bool helper(vector<vector<int>> matrix, int target, int r1, int c1, int l, int w)  {
        bool res = false;
        int x = r1;
        if ( l < 0 || w < 0) {
            return false;
        }
        if ( l ==  0 && w == 0) {
            return target == matrix[r1][c1];
        }
        if ( target < matrix[r1][c1] || target > matrix[r1+l][c1+w]) {
            return false;
        }
        int midw = w/2;
        while ( x < rows && matrix[x][c1+midw] < target) {
            x++;
        }
        if ( x >= rows) {
            res = helper(matrix, target, r1, c1+midw+1, l, w-midw-1);
        } else if ( matrix[x][c1+midw] == target) {
            return true;
        } else {
            res = helper(matrix, target, r1, c1+midw+1, x-r1, w-midw-1);
            if (!res) res |= helper(matrix, target, x, c1, l+r1-x, midw-1);
        }
        return res;
        
        /*if ( target == matrix[r1+midl][c1+midw]) {
            return true;
        } else if (target > matrix[r1+midl][c1+midw]) {
            res |= helper(matrix, target, r1+midl+1, c1+midw+1, rows-1-( r1+midl+1), cols-1-(c1+midw+1));
            if (!res) res |= helper(matrix, target, r1, c1+midw+1, midl, cols-1-(c1+midw+1));
            if (!res) res |= helper(matrix, target, r1+midl+1, c1, rows-1-(r1+midl+1), midw);
            return res;
        } else {
            return helper(matrix, target, r1, c1, midl, midw);
        }*/
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        rows = matrix.size();
        if (rows) cols = matrix[0].size();
        else return false;
        return helper(matrix, target, 0,0, rows-1, cols-1) ;
    }
};
class Solution37 {
public:
    bool complete;
    // if the given number present at row, col, it is not valid
    // if the given number is present in 3X3 square it can't be placed at row, col
    bool isValid(int num, int row, int col, vector<vector<set<char>>>& cellTracker, vector<vector<set<char>>>& sqTracker) {       
        if (cellTracker[row][col].count(num) != 0) {
            return false;
        } 
        row = row/3;
        col = col/3;
        if (sqTracker[row][col].count(num) != 0) {
            return false;
        }
        return true;
    }
    void place(vector<vector<char>>& board, char num, int row, int col, vector<vector<set<char>>>& cellT, vector<vector<set<char>>>& sqT ) {
        int i, j;
        board[row][col] = num;
        int rows = cellT.size();

        for ( i = 0; i < rows; i++) {
            cellT[row][i].insert(num);
            cellT[i][col].insert(num);
        }
        row = row/3;
        col = col/3;
        sqT[row][col].insert(num);
    }
    
void remove(vector<vector<char>>& board, int row, int col, vector<vector<set<char>>>& cellT, vector<vector<set<char>>>& sqT ) {
        int i, j;
        int rows = cellT.size();
        char num = board[row][col];
        board[row][col] = '.';
        for ( i = 0; i < rows; i++) {
            cellT[row][i].erase(num);
            cellT[i][col].erase(num);
        }
        row = row/3;
        col = col/3;
        sqT[row][col].erase(num);
    }
        
    void initBoard(vector<vector<char>>& board, vector<vector<set<char>>>& cellTracker, vector<vector<set<char>>>& sqTracker ) {
        int rows = board.size();
        int i, j;
        for ( i = 0; i < rows; i++) {
            for ( j = 0; j < rows; j++) {
                if ( board[i][j] != '.') 
                place(board, board[i][j], i, j, cellTracker, sqTracker);
            }
        }
    }
    
    void helper(vector<vector<char>>& board, int row, int col, vector<vector<set<char>>>& cellTracker, vector<vector<set<char>>>& sqTracker ) {
        int rows = board.size();
        int i, j;
        char c[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        int cindex = 0;
        i = row + col/9;
        j = col%9;
        if ( i >= 9 || j >= 9) return;
            if ( board[i][j] == '.') {
                    for ( cindex = 0; cindex < 9; cindex++) { 
                        if (isValid(c[cindex], i, j, cellTracker, sqTracker)) {
                            if ( i == rows-1 && j == rows-1) {
                                complete = true;
                                return;
                            }
                            place(board, c[cindex], i, j, cellTracker, sqTracker);
                            helper(board, i, j+1, cellTracker, sqTracker);
                            if ( complete) {
                                return;
                            }
                            remove(board, i, j, cellTracker, sqTracker);
                        }
                    }
                } else {
                    helper(board, i, j+1, cellTracker, sqTracker);
                    if ( complete) {
                                return;
                            }
                }
    }
    
    
    void solveSudoku(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        complete = false;
        vector<vector<set<char>>> cellTracker(rows, vector<set<char>>(cols)); 
        vector<vector<set<char>>> sqTracker(rows, vector<set<char>>(cols));; 
        initBoard(board, cellTracker, sqTracker);
    
        helper(board, 0, 0, cellTracker, sqTracker);
    }
};

class Solution77 {
public:
    vector<vector<int>> res;
    void helper(vector<int>& tres, int n, int k) {
        if ( k == 0) {
            res.push_back(tres);
            //tres.clear();
            return;
        }
        for (int i = 0; i < n ; i++){
            tres.push_back(n-i);
            helper(tres, n-i-1, k-1);
            tres.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<int> tmp;
        helper(tmp, n, k);
        return res;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution100 {
public:
    bool recurse(TreeNode* p, TreeNode* q) {
        bool ltree = false, rtree = false;
        if ( NULL == p && NULL == q) return true;
        if ( p && q) {
        if ( p->val != q->val ) return false;
        
            ltree = isSameTree(p->left, q->left);
            rtree = isSameTree(p->right, q->right);
            return ltree && rtree;
    }
        return false;
    }
    
    bool iterate(TreeNode* p, TreeNode* q) {
        
        queue<TreeNode*> q1, q2;
        q1.push(p);
        q2.push(q);
        TreeNode    *p1, *p2;
        while ( !q1.empty() && !q2.empty()) {
            p1 = q1.front(); q1.pop();
            p2 = q2.front(); q2.pop();
            
            if (p1 == NULL && p2 == NULL) continue;
            else if ( p1 == NULL || p2 == NULL ) return false;
            if ( p1->val != p2->val) return false;
            q1.push(p1->left); q1.push(p1->right);
            q2.push(p2->left); q2.push(p2->right);
        }
        return q1.empty() && q2.empty();
    }
    bool isSameTree(TreeNode* root1, TreeNode* root2) {
        //return recurse(root1, root2);
        return iterate(root1, root2);
    }
};
class Solution31 {
public:
    void swap(vector<int>& nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    void reverse(vector<int>& nums, int  i) {
        int j = nums.size()-1;
        for (;i < j; i++, j--) {
            swap(nums, i,j);
        }
    }
    void nextPermutation(vector<int>& nums) {
        bool done = false;
        int i,j;
        if ( nums.size() < 2) return;
        for(  i = nums.size()-1; i > 0; i--) {
            if (nums[i] > nums[i-1]) {
                    int j = i;
                    while ( nums[j] > nums[i-1] && j < nums.size()) {
                        j++;
                    }
                    swap(nums, j-1, i-1);
                    reverse(nums, i);
                    done = true;
                    break;
                }
        }
        if ( !done) {
            for( i = 0, j = nums.size()-1; i<j; i++, j--) {
                swap(nums, i,j);
            }
        }
    }
};
// Boolean response is in response to b2 being compared to b1
// True means b2 will come after b1 and vice versa
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
bool scomp(vector<int>& b1, vector<int>&b2) {
               if ( b2[0] > b1[0]) {
                   return true; // if b2[0] is bigger, it will come after b1
               } else if ( b2[0] == b1[0]) {
                   // if same starting point, smaller bldg will come later
                   if (b2[2] < b1[2]) {
                       return true;
                   } else if ( b2[2] == b1[2]) {
                       if (b2[1] > b1[1]) {
                           return true;
                       }
                   }
                   return false;
               }
               return false;
           }
class Solution218_2 {
    public:
        struct node {
            int x;
            int y;
            node() {}
            node(int x,int y) : x(x), y(y) {}
        };
        struct pqcomp {
            // if n2 is bigger, it will come first. create a max priority que
            bool operator()(node& n1, node& n2) {
                return n2.y > n1.y;
            }
        };

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
            //sort(bs.begin(), bs.end(), scomp);
            // 
            for ( auto i: bs) {
                if ( i.size() <= 0) return res;
                xhash[i[0]][i[2]] = 1;
                xhash[i[1]][i[2]] = 0; 
                tres[0] = i[0];
                tres[1] = -i[2];
                point.push_back(tres);
                tres[0] = i[1];
                tres[1] = i[2];
                point.push_back(tres);
            }
            sort(point.begin(), point.end());
            /*for ( auto eachx : xhash) {
                for ( rit = eachx.second.rbegin(); rit != eachx.second.rend(); rit++) {
                    if (rit->second == 1) {
                        // que.push(rit->first);
                        mset.insert(rit->first);
                    } else { 
                        mset.erase(mset.find(rit->first));
                    }
                }*/
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

class Solution699 {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        
    }
};
#endif
