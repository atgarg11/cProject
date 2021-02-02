#ifndef LC_1_H_
#define LC_1_H_
#include <set>
#include <map>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <list>

using namespace std;
class medianFinder {
    public: 
        priority_queue<int, vector<int>, greater<int> > pmin;
        priority_queue<int> pmax;
        medianFinder() {}

        void addNum(int n) {
            priority_queue<int> *pq;
            int num = n;
            int maxn, minn;
            if (pmax.empty()) { 
                pmax.push(n);
                return;
            } else {
                maxn = pmax.top();
            }
            if (pmin.empty()) {
                if ( n >= maxn) { 
                    pmin.push(n);
                } else { 
                    pmin.push(pmax.top());
                    pmax.pop();
                    pmax.push(n);
                }
                return;
            } else { 
                minn = pmin.top();
            }
            /*  if the new number is smaller than the max in maxq. 
                it is smaller than the max in the max q and need to go in max q
                else it needs to go in minq followed by a balancing operation  
                can optimiseit further by checking from min number in minq as well*/  
            if (n <= maxn) { 
                pmax.push(n);
                balance();
            } else if ( n>minn) { 
                pmin.push(n);
                balance();
            } else {
                if ( pmin.size() <= pmax.size()) { 
                    pmin.push(n);
                } else pmax.push(n);
            }
        }
        void balance() {
            int diff = pmin.size() - pmax.size() ;
            if ( diff > 1 || diff < -1) {
                if ( pmax.size() > pmin.size()) {
                    pmin.push(pmax.top());
                    pmax.pop();
                } else {
                    pmax.push(pmin.top());
                    pmin.pop();
                }
            }
        }
        double findMedian() {
            if (pmin.empty() && pmax.empty()) { 
                cout << " empty\n" ;
                return 0;
            } else if (pmin.empty()) {
                return pmax.top(); 
            } else if ( pmax.size() == pmin.size()) {
                cout << "equal size\n";
                return double ((pmax.top()+pmin.top()))/2 ;
            } else if (pmax.size() > pmin.size()) {
                return pmax.top(); 
            } else {
                return pmin.top(); 
            }
        }
};

class Solution {
    public: 
        int len;
        vector<double> medianSlidingWindow(vector<int>& nums, int k) {
            multiset<int> s1;
            vector<double> res;
            int i = 0, median = 0, even = 0;
            double med = 0, tmp1, tmp2;
            len = nums.size();
            multiset<int>::iterator t1;

            if ( k > len) return res;
            if (k%2) median = k/2;
            else {
                median = k/2;
                even = 1;
            }
            for ( i = 0; i < k; i++) {
                s1.insert(nums[i]);
            }
            t1 = s1.begin();
            if (even) {
                advance(t1, median);
                tmp1 = *t1--;
                tmp2 = *t1;
                res.push_back((tmp1+tmp2)/2);
            } else {
                advance ( t1, median);
                res.push_back(*t1);
            }

            for ( i = 0; i+k < len; i++) {
                // remove all elements s1.erase(nums[i]);
                t1 = s1.find(nums[i]);
                s1.erase(t1);
                s1.insert(nums[i+k]);

                t1 = s1.begin();
                if (even) {
                    advance(t1, median);
                    tmp1 = *t1--;
                    tmp2 = *t1;
                    res.push_back((tmp1+tmp2)/2);
                } else {
                    advance ( t1, median);
                    res.push_back(*t1);
                }
            }

            for ( auto j : res) cout << j << ", ";
            cout << endl ;
            return res;
        }
};
class Solution424 {
    public:
        void testCases() {
            char* tc[] = { "ABAA", "ABBB", "AAAA"};
            int     k[] = {0, 1, 2};
            return;
        }
        int characterReplacement(string s, int k) {
            int longest = 0, tmp_length = 0, x = 1;
            int length = s.size(), i = 0, j, ii, kk;
            map<char, int> smap;
            char tmpchar = 0;
            for ( i = 0; i < length; i++) {
                tmp_length = 0; x = 1; // x points to next offset
                if (tmpchar == s[i]) { 
                    continue;
                }
                tmpchar = s[i];
                tmp_length++; // new char from previos char. init tmp_length again
                for ( j = 0, x = 1; j < k && (i+j+x) < length; ) {
                    if ( s[i+j+x] == tmpchar)    {
                        x++;
                    } else {
                        j++;
                    }
                    tmp_length++;
                }
                // once J has exhausted check if more chars are same as tmpchar
                if ( j == k ) {
                    while ( (i+j+x) < length) {
                        if (s[i+j+x] != tmpchar) break;
                        tmp_length++;
                        x++;
                    }
                }
                else if ( i+j+x == length) {
                    if ((k-j) <= i)
                        tmp_length += k-j;
                    else tmp_length += i;
                }
                smap[tmpchar] = tmp_length;
                if ( longest < tmp_length) longest = tmp_length;
            }
            return longest;
        }
};

class Solution992 {
    public:
        int subarraysWithKDistinct(vector<int>& A, int k) {
            int n = A.size(), ans = 0;
            //unordered_map<int, int> hash;
            vector<int> hash(n + 1, 0);
            for(int i = 0, j = 0, cnt = 0, istart = 0; j < n; ++j) {
                if(hash[A[j]]++ == 0) cnt++;
                if(cnt < k) continue;
                while(cnt > k) {
                    cnt -= (0 == --hash[A[i++]]);
                    istart = i;
                }
                while(hash[A[i]] > 1) hash[A[i++]]--;
                ans += i - istart + 1;
            }
            return ans;
        }
        int subarraysWithKDistinct1(vector<int>& A, int K) {
            map<int, int> m1;
            int i = 0, len = A.size(), k = K, j = 0;
            int tmp = 0, count = 0;
            int window1=0;
            if ( k <=0 || k > len) return 0;

            while (j < len) {
                if ( m1[A[j]]) m1[A[j++]]++;
                else {
                    m1[A[j++]] = 1;
                    tmp++;
                }

                if (tmp < K) continue;
                if ( tmp > K) {
                    // This is a different element, slide the window
                    while ( m1[A[i]] > 0) {
                        m1[A[i++]]--;
                    }
                    window1 = i;
                } 

                while (m1[A[i]] > 1) { m1[A[i++]]--;}
                count += i-window1+1;
            }
            return count;
        }
};
//
class Solution1234 {
public:
    int balancedString(string s) {
        map<char, int> hash;
        int len = s.length();
        int i = 0, j = 0, delta = 0, req = len/4; 
        int ans = 0xFFFF;
        int sz = 0;
        for ( i = 0; i < len; i++) { 
            hash[s[i]]++;
        }
        sz = hash.size();
        if ( sz > 4) return 1;

        auto itr = hash.begin(), tmp = hash.begin(); 
        while (itr != hash.end() ) { 
            if ( req >= itr->second) {
                tmp = itr;
                itr++;
                hash.erase(tmp);
                if (hash.empty()) ans = 0;
            }
            else { 
                itr->second -= req;
                delta += itr->second;
                itr++;
            }
        }
        // Hash now contains the string that need to be replaced in given string

        for ( i= 0, j = 0; j < len && !hash.empty(); j++) {
            if (hash.count(s[j])) {
                if (hash[s[j]] > 0) delta--;
                hash[s[j]]--;
            }
            while ( delta == 0) {
                if ( ans > (j -i+1)) {
                    ans = j-i+1;
                }
                if (hash.count(s[i])) {
                    if (hash[s[i]] == 0) delta++; 
                    hash[s[i]]++;
                } 
                i++;
            }
        }
        return (ans);
    }
};

class Solution41 {
public:
    void swap(vector<int>& nums, int i, int j) {
        int tmp = 0;
        tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
    int helper(vector<int>& nums, int start, int end) {
        int s = end;
        int p = nums[s-1];
        int i = start, j = s-2, k = 0;
        for ( ; i <= j  && j >= i ; ) {
            if (nums[i] <= p ) i++;
            else { 
                swap(nums, i, j);
                j--;
            }
        }
        swap(nums, i,s-1);
        // 1 will be at index 1, 2 at 2 and so on
        if (i == p) {
            if (i+1 == end) return (p+1);
            return helper(nums, i+1, end);
        } else {
            return (helper(nums, 0, i));
        }
    }
    int firstMissingPositive(vector<int>& nums) {
        vector<int> in;
        map<int, int> hash;
        int i = 0, j = 0, one_found = 0;
        int nsize = 0;
        in.push_back(0); // 0 at 0th index
        for ( i = 0, j = 0; i < nums.size(); i++) {
            if (nums[i] < 1) continue;
            else if (nums[i] > 1) in.push_back(nums[i]);
            else { 
                one_found = 1;
                in.push_back(nums[i]);
            }
        }
        if (! one_found) return 1;
        return (helper(in, 0, in.size()));
    }
};
/*  Rain Water trap */
class Solution42 {
public:
    int getMax(vector<int> & h) {
        int max = 0, i = 0, index = 0;
        while ( i < h.size()) {
            if (h[i] > max) {
                max = h[i];
                index = i;
            }
            i++;
        }
        return index;
    }
    int trap(vector<int>& height) {
        int i = 0, j = height.size()-1, tw = 0, wl = 0;
        int index = getMax(height);
        // Run two loops one from i - index, other from j - index
        for ( ; i < index; i++) {
            if (height[i] > wl) wl = height[i];
            if ( height[i] < wl) tw += wl-height[i];
        }

        for ( wl = 0; j > index; j--) {
            if (height[j] > wl) wl = height[j];
            if ( height[j] < wl) tw += wl-height[j];
        }
        return tw;
    }
};
/*
 ["FreqStack","push","push","push","push","push","push","pop","push","pop","push",
 "pop","push","pop","push","pop","pop","pop","pop","pop","pop"]
[[],[4],[0],[9],[3],[4],[2],[],[6],[],[1],[],[1],[],[4],[],[],[],[],[],[]]
Output:
[null,null,null,null,null,null,null,4,null,6,null,1,null,1,null,4,2,4,3,9,0]
Expected:
[null,null,null,null,null,null,null,4,null,6,null,1,null,1,null,4,2,3,9,0,4]
 */
class FreqStack {
    public:
        map<int, int> hash;
        stack<int> asis, max_freq;
        FreqStack() {
        }

        void push(int x) {
            int px;
            hash[x]++;

            if (max_freq.empty() || (hash[x] >= hash[max_freq.top()])) {
                px = x;
                max_freq.push(px);
            } else {
                asis.push(x);
            }
        }

        int pop() {
            int top1, top2, res=0xFFFFFFF;
            if (!max_freq.empty()) {
                top2 = max_freq.top();
                res = top2;
                max_freq.pop();
                if ( asis.empty());
                else {
                    top1 = asis.top();
                    asis.pop();
                    hash[top1]--;
                    push(top1);
                }

                hash[res]--;
            } 
            return res;
        }
};
class Solution340 {
    public:
        int maxString(string    input, int k) {
            int res = 0, disc = 0;
            map<char, int> hash;
            int i = 0, j;
            for ( j = 0; j < input.length(); j++) {
                hash[input[j]]++;
                if (hash[input[j]] == 1) {
                    disc++; // keep expanding the window as long as the condition is true
                    while (disc > 2) { 
                        if (hash[input[i]] == 1) disc--;
                        hash[input[i]]--;
                        i++;  // shrink the window as soon as conditon breaks;
                    }
                }
                if ( j+1 - i > res) { 
                    res = j+1-i;
                }
            }
            return res;
        }
};

typedef struct Node {
    struct Node* left;
    struct Node* right;
    int val;
    int size;
    int index;
}tNode;

class Solution316 {
    public:

        tNode*  helper(tNode *root, vector<int>& count, tNode* elem) {
            tNode   *tmp = NULL;
            if ( !root) {
                return elem;
            } else if (elem->val < root->val) {
                root->size++;
                if (root->left == NULL) {
                    root->left = elem;
                } else {
                    helper(root->left, count, elem);
                }
            } else if (elem->val == root->val) {
                elem->index += root->size;
                elem->size = root->size;
                root->size++;
            } else {
                elem->index += root->size + 1;
                if (root->right == NULL) {
                    root->right = elem;
                } else {
                    helper(root->right, count, elem);
                }
            }
            return root;
        }
        vector<int> countSmaller(vector<int>& nums) {
            int i, size = nums.size();
            vector<int> count;
            count.resize(size);
            tNode*  root = new tNode() ;
            root->size = 0; root->index = 0;
            tNode*  tmp = NULL;
            root->val = nums[size-1];
            for ( i = size-2 ; i >= 0; i--) {
                tmp = new tNode();
                tmp->val = nums[i]; 
                tmp->index = 0;
                tmp->size = 0;
                helper(root, count, tmp);
                count[i] = tmp->index;
            }
            return count;
        }
};
class Solution815 {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        int i = 0, j = 0;
        int src, dest;
        vector<set<int>> sroutes; // set of stops in a routes
        map<int, vector<int>> busroutes; // hash pointing to buse routes on each stop
        vector < vector<int>> g;        // graph
        vector<int> route;  
        int count, stop;
        vector<int> color;
        queue<int> q;
        
        sroutes.resize(routes.size());
        g.resize(routes.size());
        color.resize(routes.size(), 1);
        
        if ( S == T) return 0;
        
        for ( i = 0; i < routes.size(); i++) {
            route = routes[i];
            for ( j = 0; j < route.size(); j++) {
                stop = route[j];
                sroutes[i].insert(stop); // create set of stop in a route
                busroutes[stop].push_back(i); 
                if (stop == S) src = i;    // Determine the source / destination in terms of routes
                if ( stop == T) dest = i;
            }
            if ( src == dest) return 1;
        }
        for (auto i : busroutes) {
            route = i.second;
            if (route.size() >= 2) {
                g[route[0]].push_back(route[1]);        
            }
        }
        count = 1;
        q.push(src);
        color[src] = 2;
        while ( !q.empty()) {
            i = q.front(); q.pop();
            route = g[i];
            j = 0;
            while ( j < route.size()) {
                if (color[route[j]] == 1) {
                    q.push(route[j]);
                    color[route[j]] = 2;
                    count++;
                }
                if ( route[j] == dest) break;
            }
        }
        return count;
    }
};
class Solution816 {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        int i = 0, j = 0;
        int src, dest;
        vector<set<int>> sroutes; // set of stops in a routes
        map<int, vector<int>> busroutes; // hash pointing to buse routes on each stop
        vector < vector<int>> g;        // graph
        vector<int> route;
        int count, stop;
        vector<int> color;
        queue<int> q;

        sroutes.resize(routes.size());
        g.resize(routes.size());
        color.resize(routes.size(), 1);

        if ( S == T) return 0;

        for ( i = 0; i < routes.size(); i++) {
            route = routes[i];
            for ( j = 0; j < route.size(); j++) {
                stop = route[j];
                sroutes[i].insert(stop); // create set of stop in a route
                busroutes[stop].push_back(i);
                // map the source / destination to routes
                if (stop == S) src = i;
                if ( stop == T) dest = i;
            }
            if ( src == dest) return 1;
        }

        // create a graph of all connected routes. assuming a stop is served by max two buses.
        for (auto i : busroutes) {
            route = i.second;
            if (route.size() >= 2) {
                g[route[0]].push_back(route[1]);
            }
        }
        count = 1;
        q.push(src);
        color[src] = 2;
        while ( !q.empty()) {
            i = q.front(); q.pop();
            route = g[i];
            j = 0;
            while ( j < route.size()) {
                if (color[route[j]] == 1) {
                    q.push(route[j]);
                    color[route[j]] = 2;
                    count++;
                }
                if ( route[j] == dest) break;
            }
        }
        return count;
    }
};
class Solution273 {
public:
    string numberToWords(int num) {
        string res;
        int nres, mil, thousand;
        int tmp = 0, space = 0;
        map<int, string> hash;
        hash[0] = string("Zero");
        hash[1] = string("One");
        hash[2] = string("Two");
        hash[3] = string("Three");
        hash[4] = string("Four");
        hash[5] = string("Five");
        hash[6] = string("Six");
        hash[7] = string("Seven");
        hash[8] = string("Eight");
        hash[9] = string("Nine");
        hash[10] = string("Ten");
        hash[12] = string("Twelve");
        hash[11] = string("Eleven");
        hash[13] = string("Thirteen");
        hash[14] = string("Fourteen");
        hash[15] = string("Fifteen");
        hash[16] = string("Sixteen");
        hash[17] = string("Seventeen");
        hash[18] = string("Eighteen");
        hash[19] = string("Nineteen");
        hash[20] = string("Twenty");
        hash[30] = string("Thirty");
        hash[40] = string("Forty");
        hash[50] = string("Fifty");
        hash[60] = string("Sixty");
        hash[70] = string("Seventy");
        hash[80] = string("Eighty");
        hash[90] = string("Ninety");
        if ( 0 == num) return hash[0];

        nres = num / 1000000000;
        if ( nres) {
            res = string(hash[nres]);
            res.append(string(" Billion"));
            space = 1;
            num = num%1000000000;
        }
        while (num) {
            mil = false;
            thousand = false;
            nres = num / 1000000;
        if (nres) {
            mil =true;
        } else if (num/1000) {
            nres = num / 1000;
            thousand = true;
        } else {
            nres = num;
        }
        if (nres/100) {
                if (space) res.append(string( " "));
                space = 1;
                res.append(hash[nres/100]);
                res.append(string(" Hundred"));
                nres = nres % 100;
        } if ( nres == 20 || nres == 30 || nres == 40 || nres == 50 ||
              nres == 60 || nres == 70 || nres == 80 || nres == 90) {
            if (space) res.append(string( " "));
            space = 1;
            res.append(hash[nres]);
            nres = nres%10;
        } else if (nres/10 >= 2) {
            tmp = nres/10;
            tmp = tmp*10;
            if (space) res.append(string( " "));
            space = 1;
            res.append(hash[tmp]);
            nres = nres % 10;
        } if (nres) {
            if (space) res.append(string( " "));
            space = 1;
            res.append(hash[nres]);
        }
        if (mil) {
            res.append(string(" Million"));
            num = num % 1000000;
        } else if (thousand) {
            res.append(string(" Thousand"));
            num = num%1000;
        } else num = 0;
    }
        return res;
    }
};
class Solution403 {
public:
    bool validJump(int jump, int reqJump) {
        if (reqJump == jump || reqJump == jump-1 || reqJump == jump+1) 
            return true;
        return false;
    }
    bool helper(vector<int>& stones, int pos, int lastJump) {
        int i = pos, j = i+1;
        int jump = lastJump, reqJump;
        if ( j < stones.size()) {
            reqJump = stones[j]-stones[i];
            while ( reqJump <= jump+1 && j < stones.size()) {
                if (validJump(jump, reqJump) && 
                        helper(stones, j, reqJump)) return true;
                j = j+1;
                if ( j < stones.size()) reqJump = stones[j] - stones[i];
                else return false;
            }
            if ( j < stones.size()) return false;
        }
        return true;
    }
    bool canCross(vector<int>& stones) {
        int i, j, cross = 0;
        int maxJump = 1, reqJump = 0;
        // base condition
        if ( stones.size() < 2 || stones.size() >= 1100) return false;
        if (stones[0] == 0 && stones[1] == 1) 
            return (helper(stones, 0, 1));
        return false;
    }
};
typedef struct {
    int x,y;
}pos;
class Solution1280 {
public:
    int helper(vector<pos>& A) {
        int i = 0, d1_count=0, d2_count=0;
        if (A.size() < 3) return 0;
        map<int, int> rows; 
        map<int, int> cols;

        for ( i = 0; i < A.size(); i++) {
            rows[A[i].x]++;
            cols[A[i].y]++;
            if (A[i].x == A[i].y) {
                if (A[i].x ==1)
                   d2_count++;
                d1_count++;
            }
            if ((A[i].x == 0 && A[i].y == 2) || (A[i].x == 2 && A[i].y==0) )
                d2_count++;
        }
        if ( rows[0] == 3 || rows[1] == 3 || rows[2] == 3 ||
             cols[0] == 3 || cols[1] == 3 || cols[2] == 3||
             d1_count ==3 || d2_count == 3)
            return 1;
        return 0;
    }
    string tictactoe(vector<vector<int>>& moves) {
        int i,j;
    vector<pos> A;
    vector<pos> B;
        pos tmp;
        for ( i = 0, j = 1; j < moves.size(); i+=2, j+=2) {
            tmp.x = moves[i][0];
            tmp.y = moves[i][1];
            A.push_back(tmp);
            tmp.x = moves[j][0];
            tmp.y = moves[j][1];
            B.push_back(tmp);
        }
        if ( i < moves.size()) {
            tmp.x = moves[i][0];
            tmp.y = moves[i][1];
            A.push_back(tmp);
        }
        if (helper(A)) return "A";
        if (helper(B)) return "B";
        if (moves.size() == 9) return "Draw";
        return "Pending";
    }
};
class Solution772 {
    public: 
        int eval(string s) {
            int x;
            int c;
            string tmp;
            stringstream ss (s);
            ss >> x;
            cout << "int is: " << x;
            cout << endl;
            ss >> tmp ; 
            //ss.get(c);
            cout << "char is " << c << endl;
        }
};

class Solution1025 {
public:
    bool divisorGame(int N) {
        // DP solution. Create a recurssion tree to see the overlap
        int i, move, nmove,r,r1;
        int primes[12] = {31, 29, 23, 19, 17, 13, 11, 7, 5, 3, 2, 1};
        vector<int> win;    // status of game for a move at the index
        win.resize(N+1, -1);
        // base case
        switch(N) {
            case 0:
                break;
            case 2:
                win[2] = 1;
                return 1;
            case 1:
                win[1] = 0;
                return 0;
            default:
                win[2] = 1; win[1] = 0;
        }
        move = N;

        for ( i = 0; i < 12; i++) {
            if (move % primes[i] == 0) {
                if (primes[i] != 1) {
                    r = move/primes[i];
                    nmove = move-r;
                }
                else nmove = move-primes[i];

                if ( win[nmove] == -1) {
                    win[nmove] = divisorGame(nmove);
                }
                if (win[nmove] == 1) {
                    win[move] = 0;
                } else if ( win[nmove] == 0) {
                    win[move] = 1;
                    break;  // when ever there is chance to win break.
                }
            }
        }
        return win[N];
    }
};
class Solution818 {
public:
    int max = 0xFFFFFFF;
    vector<int> dp;
    int helper(int start, int dir, int target, int &count) {
        int speed;
        if ( dir == 1) {
            speed = 1;
            while ( target - start >= speed/2 ) {
                count++;
                start += speed;
                speed = speed * 2;
                if (start == target) return count;
            }
            count++;
            return helper(start, -1, target, count);
        } else {
            speed = -1;
            while ( target - start <= speed/2 ) {
                count++;
                start += speed;
                speed = speed * 2;
                if ( start == target) return count;
            }
            count++;
            return helper(start, 1, target, count);
        }
    }
    int racecar(int target) {
        if ( target == 0) return 0;
        dp.resize(target+1, -1); 
        dp[0] = 0;
        return racecar2(target);
    }
    int racecar2(int target) {
        int count = 0;
        int i, m = 1, j = 0;
        int p, q;
        if ( dp[target] > 0) return dp[target];
        dp[target] = max;

        for ( j = 1; j <= target; j = (1<<m) -1) {
            dp[j] = m;
            if ( j == target) return dp[j];
            for ( p =0, q = 0; p < j; p = (1<<q) -1) {
                dp[target] = min(dp[target], m+1+q+1+racecar2(target-(j-p))); 
                q++;
            }
            m++;
        }
        dp[target] = min(dp[target], m+1+racecar2(j-target));
        return dp[target];
    }
};
class Solution188 {
    public:
    int max(int a, int b) {
        return (a > b ? a: b);
    }
    int maxProfit(int k, vector<int>& prices) {
        vector<int> d;
        d.resize(k+1, -1);
        int i, j, tmp, tmpP, start;
        d[0] = 0;   // No transation no profit
        for ( i = 1; i <= k; i++) {
            if (d[i] > 0) return d[i];
            tmp = i-1;
            d[i]= 0;
            start = 0;
            for ( j = 1; j < prices.size(); j++) {
                // Split at this point
                if (prices[j] < prices[j-1] && tmp) {
                    d[i] += maxProfit1(prices, start, j-1);
                    start = j; 
                    if (d[i]) tmp--; 
                }
                if ( !tmp) {
                    d[i] += maxProfit1(prices, start, prices.size()-1);
                    d[i] = max(d[i], d[i-1]);
                    break;
                }
            }
            d[i] = max(d[i], d[i-1]);
        }
        return (d[k]);
    }
    int maxProfit1(vector<int>& prices, int start, int end) {
        int i , j;
        int tmp, res = 0, s = end-start+1; 
        if ( start == end) return 0;
        for ( i = start; i < s-1+start ; i++) {
            for ( j = i+1; j < s+start; j++) {
                tmp = prices[j] - prices[i];
                if ( tmp > res) {
                    res = tmp;
                }
            }
        }
        return res;
    }
    int maxProfit2(int k, vector<int>& p) {
        int i, j , t = 0;
        int s = p.size(), tmp = 0;
        vector<vector<int>> dp;
        if(s < 2) return 0; 

        //dp.resize(k+1);
        dp.resize(2);
        for ( i = 0; i < 2; i++) {
            dp[i].resize(s, 0);
        }
        for ( t = 1; t <= k; t++) {
            for ( i = 1; i < s; i++ ) {
                tmp = 0;
                for ( j = 0; j <= i-1; j++) {
                    tmp = max(tmp, p[i]-p[j]+dp[(t-1)%2][j]);
                }
                dp[t%2][i] = max(dp[t%2][i-1], tmp);
            }
        }
        return (dp[k%2][s-1]);
    }
};
class Solution72 {
    public: 
        int minDistance(string word1, string word2) {
            int n;
            n = lcs2(word1, word2);
            return n;
        }
        int lcs2(string s, string d2) {
            int s1 = s.size(), s2 = d2.size();
            int i, j, x,y, tmp;
            vector<vector<int> > d; 
            d.resize(s1+1);
            d[0].resize(s2+1, 0);
            for ( i = 0; i <= s1; i++) {
                d[i].resize(s2+1, 1);
                for ( j = 0; j <= s2; j++) {
                    if ( i == 0) d[i][j] = j;
                    else if ( j == 0) d[i][j] = i;
                    else if ( d2[j-1] == s[i-1]) {
                        d[i][j] = d[i-1][j-1];
                    } else {
                        tmp = min(d[i-1][j], d[i][j-1]);
                        tmp = min(d[i-1][j-1], tmp); 
                        d[i][j] = 1+tmp;
                    }
                }
            }
            return d[s1][s2];
        }
        int lcs(string s, string d2) {
            int s1 = s.size(), s2 = d2.size();
            int i, j, x,y;
            vector<vector<int> > d; 
            d.resize(s1+1);
            d[0].resize(s2+1, 0);
            for ( i = 1; i <= s1; i++) {
                d[i].resize(s2+1, 0);
                for ( j = 1; j <= s2; j++) {
                    x = i-1; y = j-1;
                    if ( d2[y] == s[x]) {
                        d[i][j] = 1 + d[i-1][j-1];
                    } else {
                        d[i][j] = max(d[i-1][j], d[i][j-1]);
                    }
                }
            }
            return d[s1][s2];
        }
};

class Solution843 {
    public: 
        int max() { 
            return 1;
        }
};
class SolutionMisc1{
    // Kadane's Algorithm
    public: 
        int maxSumSubarray(vector<int> arr) {
            int sum = 0; // Sum to keep track of different sub arrays
            int ans = 0; // max sum
            int i;
            for ( i = 0; i< arr.size(); i++) {
                sum += arr[i];
                if ( sum <=0 ) sum = 0;
                else ans = max(ans, sum);
            }
            return ans;
        }
};
class Solution128 {
public:
    int longestConsecutive(vector<int>& nums) {
        map<int, int> hash;
        int i, j, n;
        int ans = 0, tmp = 0;
        // Put all the elements in the hash
        for ( i = 0; i < nums.size(); i++) {
            hash[nums[i]] = 1;
        }
        for ( i = 0; i < nums.size(); i++) {
            n = nums[i];
            tmp = hash[n];
            if (hash.count(n-1)) continue;
            n++;
            while (hash.count(n)) {
                tmp++;
                n++;
            }
            ans = max(tmp, ans);
        }
        return ans;
    }
    void sort(vector<int>& nums) {
        int i;
        ::sort(nums.begin(), nums.end());
        for ( i = 0;i< nums.size();i++) {
            cout << nums[i] << "," ;
        }
        cout << endl;
    }
};
class Solution801{
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        vector<int> s;
        vector<int> n;
        int size = A.size();
        s.resize(size, INT_MAX);
        n.resize(size, INT_MAX);
        int i = 0;
        n[0] = 0; s[0] = 1;
        for ( i = 1; i < A.size(); i++) {
            if (B[i] > B[i-1] && A[i] > A[i-1]) { 
                n[i] = n[i-1];// choose to keep, get the previous one.
                s[i] = 1 + s[i-1];
            }
            if ( A[i] > B[i-1] && B[i] > A[i-1]) {
                n[i] = min(n[i], s[i-1]);
                s[i] = min(1+n[i-1], s[i]);
            }
        }
        return min(s[size-1], n[size-1]);
    }
};
class Solution5 {
public:
int len; 
string res;
int expand(string s, int l, int r) {
        if ( l < 0  || r >= len) {
            return r-l-1;
        }
        if ( s[l]!= s[r]) {
            return r-l-1;
        }
        return expand (s, l-1, r+1);
    }
    string longestPalindrome(string s) {
        int i, j;
        len = s.length();
        int len1, len2;
        int tmp = 0, start = 0;
        for ( i = 0; i < len; i++) {
            len1 = expand(s, i, i);
            len2 = expand(s, i, i+1);     
            if ( len1 > len2 && len1 > tmp) {
                tmp = len1;            
                res = s.substr(i, tmp);
                start = i-(tmp-1)/2;
            } else if ( len2 > len1 && len2 > tmp) {
                tmp = len2;
                res = s.substr(i, tmp);
                start = i-(tmp-1)/2;
            }
            res = s.substr(start, tmp);
        }
        return res;
    }
    string longestPalindrome1(string s) {
        int length = s.length();
        int i, j, k, x,y, index = 0;
        int tmp = 0, mmax = 0;
        vector<vector<int>> p;
        p.resize(length+1);
        
        if (length < 2 ) return s;

        for ( i = 0; i <= length; i++) {
            p[i].resize(length+1, 0);
            p[i][i] = 1;
        }
        index = 0; mmax = 1;
        // how much length to consider
        for ( int k = 2; k <= length; k++) {
            // From which index to consider k length
            for ( i = 0; i+k <= length; i++) {
                j = i+k-1;
                x = i+1; y = j+1; 
                if (s[i] == s[j] && (k == 2 || p[x+1][y-1])) {
                    p[x][y]++;
                    tmp = k;
                }    
                if (tmp > mmax) {
                    index = i;
                    mmax = k;
                }
            }
        }
        return s.substr(index, mmax);
    }
};

class Solution1326 {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> t;
        int size = ranges.size(), taps = 0;
        t.resize(ranges.size(), INT_MAX);
        taps = helper(n, ranges, t);
        return taps;
    }
    int helper(int n, vector<int>& ranges, vector<int>& taps) {
        int tap = INT_MAX, i;
        int size = ranges.size();
        // Base condition
        if ( n <=0) return 0;
        
        //  Cache check
        if (taps[n] != INT_MAX) return taps[n];
        
        for ( i = n; i >=0; i--) {
            // for all the taps that can water the nth positison
            if ( ranges[i] && ((i+ranges[i])>=n || (i-ranges[i]<=0)))
                taps[n] = min(taps[n], 1+helper(i- ranges[i], ranges, taps));
        }
        return taps[n];
    }
    int minTapsR(int n, vector<int>& ranges) {
        vector<int> t;
        int size = ranges.size();
        t.resize(ranges.size(), INT_MAX);
        int i, tap;
        t[size-1] = INT_MAX;
        tap = INT_MAX;
        // Base condition
        if ( n <=0) return 0;
        
        for ( i = n; i >=0; i--) {
            // for all the taps that can water the nth positison
            if ( ranges[i] && (i+ranges[i])>=n)
                tap = min(tap, 1+minTaps(i - ranges[i], ranges));
        }
        return tap;
    }
};
class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        map<int, int> hash;
        int i = 0, j = nums.size()-1;
        result.resize(2);
        for ( i = 0; i < nums.size(); i++) {
            hash[nums[i]] = i;
            if (nums[i] + nums[i] == target) {
                for ( j = i+1; j < nums.size(); j++) {
                    if (nums[j] == nums[i]) {
                        result[0] = i;
                        result[1] = j;
                        break;
                    }
                }
            } else if (hash.count(target-nums[i])) {
                result[1] = i;
                result[0] = hash[target-nums[i]];
                break;
            }
        }
        return result;
    }
};
class Solution1011 {
public:
    int helper(vector<int>& weights, int D, int cap)
    {
        int days = 1, wt=0;
        int i = 0, size = weights.size();
        for ( i = 0; i < size; i++) {
            if (wt + weights[i] > cap) {
                days++;
                wt = weights[i];
            }  else {
                wt += weights[i];
            }
        }
        return days;
    }
    int shipWithinDays(vector<int>& weights, int D) {
            int size = weights.size();
            int i, avg = 0, wmax = 0, wmin = 0, tmp;
            int d = D, j, lot = size/D + (size%D ? 1:0);
            for (i = 0; i < size;i++ ) {
                avg += weights[i];
                wmax = max(wmax, weights[i]);
            }
            avg = avg/d;
            wmax = max(avg, wmax);
            wmin = wmax;     // minimum weight ship should carry
            for (i = 0; i < size; i+=lot ) {
                avg = 0;
                for ( j = i; j < i+lot && j < size; j++) {
                    avg += weights[j];
                }
                wmax = max(wmax, avg);  // maximum wt for ship to carry
            }
            while ( wmax > wmin) {
                tmp = (wmax-wmin)/2;
                d = helper(weights, D, wmin+ tmp);
                if ( d < D) wmax = wmin + tmp;
                else if ( d > D) wmin = wmin+(tmp?tmp:1);
                else { wmax = wmin+tmp;}
                return wmin+tmp;
            }
            return wmin;    
            // Now fit more than equal to avg weight and see if it can be done in D days
            /*
            tmp = wmin;
            do {
                i = 0; d = D;
                while ( d && i < size) {
                    avg = weights[i++];
                    while ( i < size && (avg+weights[i]) <= tmp) {
                        avg += weights[i++];
                    }
                    d--;
                }
                if ( i >= size) {
                    return tmp;
                }
                tmp++;
            }while(tmp <= wmax);
            return tmp;
            */
        }
};
class Solution846 {
    public: 
        bool isNStraightHand(vector<int>& hand, int w) {
            int i, size = hand.size(); 
            int first;
            bool res = false;
            map<int, int> hash;
            
            if ( size%w) return false;
            for ( i = 0; i < size; i++) {
                hash[hand[i]]++;           
            }
            auto itr = hash.begin(), tmp = itr;
            while ( !hash.empty()) {
                itr = hash.begin();
                tmp = itr;
                first = itr->first;
                res = false;
                for ( i = 0; i < w && itr != hash.end(); i++) {
                    tmp++;
                    if (first != itr->first) break;;
                    switch (itr->second) {
                        case 1:
                            hash.erase(itr);
                            break;
                        default:
                            itr->second--;
                    };
                    first++;
                    itr = tmp;  
                }
                res = (i == w);
            }
            return res;
        }
};
/*  Locked  */
class Solution774 {
    public:
        double minmaxGasDist(vector<int>& stations, int K) {
            priority_queue<double> dist;
            int i, k = K, tmp = 0;
            int size = stations.size();
            for ( i = 1; i < size; i++) {
                dist.push(stations[i]-stations[i-1]);
            }
            while (k) {
                tmp = dist.top();
                dist.pop();
                dist.push(double(tmp)/2);
                k--;
            }
            return dist.top();
        }
};
class Solution1074 {
    public: 
        int helper(vector<vector<int>>& matrix, vector<vector<int>>& s, int r, int c)
        {
            int i = r, j = c;
            int colsum = 0, rowsum = 0;
            // base condition
            if ( i == 0 && j == 0) {
                s[i][j] = matrix[i][j];
                return 0;
            }
            // Main recursion
            for ( i = 0; i < r; i++) {
                colsum += matrix[i][c];
                s[i][c] = helper(matrix, s, i, c-1) + colsum;
            }
            for ( j = 0; j < c; j++) {
                rowsum += matrix[r][j];
                s[r][j] = helper(matrix, s, r-1,j) + rowsum;
            }
            return s[r][c];
        }
        int numSubmatrixSubTarget(vector<vector<int>>& matrix, int t)
        {
            vector<vector<int>> sum;
            int size = matrix.size();
            int cols = matrix[0].size();
            int i, j = 0, count = 0;
            sum.resize(size);
            for ( i = 0; i < size; i++) {
                sum[i].resize(cols, 0);
            }
            helper(matrix, sum , size-1, cols-1);
            for ( i =  0; i < size; i++ ) {
                for ( j = 0; j < cols; j++) {
                    if (sum[i][j] == t) count++;
                }
            }
            return count;
        }
};
class Solution200 {
public:
    int lands;
    int numIslands(vector<vector<char>>& grid) {
        int rows, cols; // Number of vertices
        int last, i, j;
        rows = grid.size();
        vector<vector<int>> visited;
        visited.resize(rows);
        lands = 0;
        if (rows) cols = grid[0].size();
        else return lands;

        for ( i = 0; i < rows; i++) {
            for ( j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);   
                    lands++;
                }
            }
        }
        return lands;
    }
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (grid[i][j] == '1') {
                grid[i][j] = 0;
            if (i-1 >= 0) dfs(grid, i-1, j);
            if (i+1 < grid.size()) dfs(grid, i+1, j);
            if (j-1 >= 0)  dfs(grid, i, j-1);
            if (j+1 < grid[i].size())  dfs(grid, i, j+1);
        }
    }
};
class SolutionConnectedGraph {
    public:
        vector<int> tmp;
        vector<int> visited;
        void dfs(vector<vector<int>> graph, int v) {
            int i;
            if (!visited[v]) {
                tmp.push_back(v);
                visited[v] = 1;
                for ( i = 0; i < graph[v].size(); i++) {
                    dfs(graph, graph[v][i]);
                }
            }
        }
        vector<vector<int>> connected(vector<vector<int>> graph) {
            int size = graph.size(), i;
            visited.resize(size, 0);
            vector<vector<int>> cc;    
            // for all the vertices 
            for ( i = 0; i < size; i++) {
                dfs(graph, i);
                if (tmp.size()) {
                    cc.push_back(tmp);
                    tmp.clear();
                }
            }
            return cc;
        }
};
class Solution1036 {
    public: 
        int count = 0;
        int sun = 0;
        bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
            int block = blocked.size();
            int i, j, x, y;
            pair<int, int> p;
            map<pair<int, int>, int> vb;    // visited / blocked blocks
            queue<pair<int, int>> que;
            if (source == target || block == 0) return true;
            for ( i = 0; i < block; i++) {
                vb[{blocked[i][0], blocked[i][1]}] = 1;
            }
            que.push({source[0], source[1]});
            while (!que.empty()) {
                p = que.front();
                x = p.first; 
                y = p.second;
                if ( (x == target[0] && y == target[1]) || 
                     ( x > source[0]+block ) ||
                     ( x < source[0]-block) ||
                     (y > source[1]+block) ||
                     (y < source[1]-block))  {
                         if (!sun) { 
                             sun = 1; 
                             return isEscapePossible(blocked, target, source);
                         }
                         else return true;
                     }
                que.pop();
                if (vb.count({x+1,y})) ;
                else {
                    que.push({x+1, y});
                    vb[{x+1, y}] = 1;
                }
                if (x-1 >= 0 && vb.count({x-1,y})) ;
                else if( x-1 >= 0 ) {
                    que.push({x-1, y});
                    vb[{x-1, y}] = 1;
                }
                if (vb.count({x,y-1})) ;
                else if (y-1 >= 0) {
                    que.push({x, y-1});
                    vb[{x, y-1}] = 1;
                }
                if (vb.count({x,y+1})) ;
                else {
                    que.push({x, y+1});
                    vb[{x, y+1}] = 1;
                }
                count++;
            }
            return false;
        }
};

class Trie {
    class TNode {
    public:
        map<char, TNode*> node;
        bool word;
    public: 
        TNode() { 
            word = false;
        } 
    };
public:
     TNode root;
    /** Initialize your data structure here. */
    Trie() {
    }
    TNode*   allocNode(string word) {
        int i = 0, size = word.length();
        TNode    *tmp = new TNode();
        if (word.length() == 1) {
            tmp->node[word[0]] = new TNode();
            tmp->node[word[0]]->word = true;
            return tmp;
        } else {
            tmp->node[word[i]] = allocNode(word.substr(i+1, size));
        }
        return tmp;
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        TNode    *tmp = &root;
        char c = word[0];
        int i = 0, size = word.length();
        c = word[i];
        while (tmp->node.count(c) && i <= size) {
            tmp = tmp->node[c];   
            c = word[++i];
        }
        if ( i < size) {
            if ( (size-i) == 1 ) {
                tmp->node[c] = new TNode();
                tmp->node[c]->word = true;
            } else 
                tmp->node[c] = allocNode(word.substr(i+1, size));
        } else {
            tmp->word = true;
        }
    }
    // delete a node from the TRIE. only delete the last node. 
    void deleteWord(string word) {
        int i, size = word.length();
        TNode    *tmp = &root, *ptmp;
        for ( i = 0; i < size; i++) {
            if ( tmp->node.count(word[i])) {
                ptmp = tmp;
                tmp = tmp->node[word[i]]; 
            } else break;            
        }
        if (i == size && tmp->word) {
            tmp->word = false;
            /*
            if (!tmp->node.empty())
                tmp->word = false;
            else {
                ptmp->node[word[i-1]] = NULL;
                delete(tmp);
            }*/
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        int i, size = word.length();
        TNode    *tmp = &root;
        for ( i = 0; i < size; i++) {
            if ( tmp->node.count(word[i])) {
                tmp = tmp->node[word[i]]; 
            } else break;            
        }
        return (i == size && tmp->word);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        int i, size = word.length();
        TNode    *tmp = &root;
        for ( i = 0; i < size && tmp; i++) {    
            //if (i+1 == size) return true;
            if ( tmp->node.count(word[i])) {
                tmp = tmp->node[word[i]]; 
            } else break;            
        }
        return (i == size);
    }
};
class Solution212 {
public:
    Trie t;
    map<pair<int, int>, int> visited; // making it hash so don't have to resize
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int rows = board.size(), cols;
        string word;
        map< char, vector<vector<int>>> hash;
        map< char, vector<vector<int>>>::iterator itr;

        vector<vector<int>> cordinates;
        int i, j, x, y ;
        char c;
        vector<int> xy;
        vector<string> res;
        string tin = "";
        if (rows) cols = board[0].size();
        // create the coordinate hash map of grid. This is needed to get the starting
        // point for DFS. 
    
        for ( i = 0; i < rows; i++) {
            for ( j = 0; j < cols; j++) {
                c = board[i][j];
                xy.push_back(i); xy.push_back(j);
                if (hash.count(c)) {
                    hash[c].push_back(xy);
                } else {
                    cordinates.push_back(xy);
                    hash[c] = cordinates;
                    cordinates.clear();
                }
                xy.clear();
            }
        }
        // Create the dictionary of the words 
        for ( i = 0; i < words.size(); i++) {
            t.insert(words[i]);
        }
        // Now for all the entries in the co-ordinates hash, see what is present trie
        for ( itr = hash.begin(); itr != hash.end(); itr++) {
            cordinates = itr->second;
            for ( j = 0; j < cordinates.size(); j++) {
                visited.clear();
                dfs2(board, cordinates[j], res, tin);
            }
        }
        /*
        for ( i = 0; i < words.size(); i++) {
            word = words[i];
            cordinates = hash[word[0]];
            for ( j = 0; j < cordinates.size(); j++) {
                visited.clear();
                if (dfs(board, cordinates[j], word)) {
                    res.push_back(word);
                    break;
                }
            }
        }*/
        return res;
    }
    // start for a cordinate and look for the words present in TRie.
    bool dfs2(vector<vector<char>>& grid, vector<int> xy, vector<string>& res, string tin) {
        vector<int> nxy;
        int x, y, count = 0;
        int rows, cols;
        bool dres = false;
        rows = grid.size(); if (rows) cols = grid[0].size();
        x = xy[0]; y = xy[1];
        nxy.resize(2);
        string in = tin+grid[x][y];
        if (!visited.count({x, y}) && t.startsWith(in)) {   
            visited[{x, y}] = 1;
            nxy[0] = x; nxy[1] = y;
            if (t.search(in)) {
                res.push_back(in);
                t.deleteWord(in);
                dres = true; // terminate the dfs
            }
            if ( x+1 < rows ) {
                nxy[0] = x+1; nxy[1] = y;
                dres = dfs2(grid, nxy, res, in);
            }
            if ( x-1 >=0) {
                nxy[0] = x-1; nxy[1] = y;
                dres = dfs2(grid, nxy, res, in);
            }
            if ( y-1 >=0) {
                nxy[1] = y-1;nxy[0] = x;
                dres = dfs2(grid, nxy, res, in);
            }
            if ( y+1 <cols ) {
                nxy[1] = y+1;nxy[0] = x;
                dres = dfs2(grid, nxy, res, in);
            }
            if (!dres) visited.erase({x,y});
        }
        return dres;
    }
    bool dfs(vector<vector<char>>& grid, vector<int> xy, string word) {
        vector<int> nxy;
        int x, y, count = 0;
        int rows, cols;
        rows = grid.size(); if (rows) cols = grid[0].size();
        if (word.length() <= 1) return true;

        x = xy[0]; y = xy[1];
        nxy.resize(2);
        if (!visited.count({x, y}) && grid[x][y] == word[count++]) {   
            visited[{x, y}] = 1;
            nxy[0] = x; nxy[1] = y;
            if ( x+1 < rows && 
                    (!visited.count({x+1, y})) && 
                    grid[x+1][y] == word[count]) {
                    nxy[0] = x+1; nxy[1] = y;
                    if (dfs(grid, nxy, word.substr(count, word.length()))) return true;
                }
                if ( x-1 >=0 && 
                    (!visited.count({x-1, y})) && 
                    grid[x-1][y] == word[count]) {
                    nxy[0] = x-1; nxy[1] = y;
                    if (dfs(grid, nxy, word.substr(count, word.length()))) return true;
                }
                if ( y-1 >=0 && 
                    (!visited.count({x, y-1})) && 
                    grid[x][y-1] == word[count]) {
                    nxy[1] = y-1;nxy[0] = x;
                    if (dfs(grid, nxy, word.substr(count, word.length()))) return true;
                }
                if ( y+1 <cols && 
                    (!visited.count({x, y+1})) && 
                    grid[x][y+1] == word[count]) {
                    nxy[1] = y+1;nxy[0] = x;
                    if (dfs(grid, nxy, word.substr(count, word.length()))) return true;
                }
        }
        visited.erase({x, y}); // back Track;
        return false;
    }
};

class Solution208 {
    public: 
        Trie t;
        bool testTrie(vector<string> words, vector<string> swords) {
            int i; 
            for ( i = 0; i < words.size(); i++) {
                if ( words[i] == "insert") {
                    t.insert(swords[i]);
                } else if ( words[i] == "search") {
                    cout << t.search(swords[i]) << ", ";
                } else if ( words[i] == "startsWith") {
                    cout << t.startsWith(swords[i]) << ", ";
                }
            }
            cout << endl;
            return true;
        }
};

class Solution79 {
public:
    vector<vector<bool>> visited, tvis;
    bool exist(vector<vector<char>>& board, string word) {
        int i = 0, j = 0;
        bool res = false;
        int rows = board.size(), cols;
        vector<int> cordinate;
        int index = 0;
        if (rows) {
            visited.resize(rows);
            cols = board[0].size();
            for ( i =0; i < rows; i++)
                visited[i]. resize(cols);
        }
        tvis = visited;
        cordinate.resize(2);
        for ( i = 0; i < rows; i++) {
            for ( j = 0; j < cols && !res ; j++) {
                if (word[0] == board[i][j]) {
                    cordinate[0] = i; 
                    cordinate[1] = j; 
                    if (word.length() == 1) res = true;
                    else 
                        res = dfs(board, cordinate, word, index);
                }
                visited = tvis;
            }
        }
        return res;
    }
    
    bool dfs(vector<vector<char>>& grid, vector<int>& xy, string word, int index) {
        int x = xy[0], y = xy[1];
        int rows = grid.size(), cols = grid[0].size();
        vector<int> nxy = xy; 
        bool res = false;
        if ( index == word.length()) return true;
            
        if (!visited[x][y] && word[index] == grid[x][y]) {
            visited[x][y] = true;
            if ( x+1 < rows) {
                nxy[0] = x+1; nxy[1] = y;
                res=dfs (grid, nxy, word, index+1);
            }
            if ( !res && y+1 < cols) {
                nxy[0] = x; nxy[1] = y+1;
                res=dfs (grid, nxy, word, index+1);
            }
            if ( !res && x-1 >= 0) {
                nxy[0] = x-1; nxy[1] = y;
                res=dfs (grid, nxy, word, index+1);
            }
            if ( ! res && y-1 >= 0) {
                nxy[0] = x; nxy[1] = y-1;
                res=dfs (grid, nxy, word, index+1);
            }
            if (!res) visited[x][y] = false;
        }
        return res;
    }
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
class SolutionSp {
    public:
        int sp(vector<vector<int>>&  grid, vector<int> src, vector<int> dest) {
            int rows = grid.size();
            int cols; 
            if (rows) cols = grid[0].size();
        }
};
class Solution56 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>>::iterator itr = intervals.begin(); 
        vector<vector<int>>::iterator tmp; 
        
        if ( intervals.size() < 2) return intervals;

        qsort1(intervals, 0, intervals.size());
        // intervals are sorted merge them
        for ( itr = intervals.begin()+1 ; itr != intervals.end(); itr++) {
            tmp = itr-1;    
            if (itr[0][0] <= tmp[0][1]) {
                while (itr[0][0] <= tmp[0][0]) {
                    itr = intervals.erase(tmp);
                    if ( itr == intervals.begin()) break;
                    tmp = itr-1;    
                    }
                if (itr != intervals.begin() && itr[0][0] <= tmp[0][1]) {
                    itr[0][0] = tmp[0][0];
                    itr = intervals.erase(tmp);
                }
            }
        }
        return intervals;
    }
    int partition(vector<vector<int>>& inp, int s, int e) {
        int i =s-1, j;
        vector<int> p = inp[e-1];
        for ( j = s; j < e-1; j++) {
            if (inp[j][1] < p[1]) {
                i++;
                swap(inp[i], inp[j]);
            }
        }
        i++;
        swap(inp[i], inp[e-1]);
        return i;
    }
    void qsort1(vector<vector<int>>& inp, int s, int e) {
        int i = s-1, j = s;
        if ( s < e) {
            int p = partition(inp, s, e);
            qsort1(inp, s, p);
            qsort1(inp, p+1, e);
        }
    }
};
class Solution57 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int i, size = intervals.size();
        vector<vector<int>>::iterator itr = intervals.begin(), pitr;
        switch(size) {
            case 0: 
                intervals.push_back(newInterval);
                return intervals;
            case 1:
                if (intervals[0].empty()) {
                    intervals[0] = newInterval;
                    return intervals;
                }
                break;
        };
        while  ( itr!= intervals.end() && 
                (newInterval[0] >= itr[0][0])) {
            itr++;
        }
        // Check the overlap with the previos one. Just one possible
        if (itr != intervals.begin() && newInterval[0] <= (itr-1)[0][1]) {
            itr--;
            itr[0][1] = max(newInterval[1], itr[0][1]);
        } else {
            itr = intervals.insert(itr, newInterval);
        } 
        pitr = itr++;

        while (itr != intervals.end() && pitr[0][1] >= itr[0][1]) {
            itr = intervals.erase(itr);
        }
        if (itr != intervals.end() && pitr[0][1] >= (itr)[0][0]) {
            pitr[0][1] = itr[0][1];
            itr = intervals.erase(itr);
        } else {
            ; // do nothing
        }
        return intervals;
    }
};
class Solution4 {
    public:
        double findMedianSortedArrays(vector<int>& arr1,  vector<int>& arr2) {
            double res=0;
            vector<double> arr;
            int m = arr1.size(), n = arr2.size();
            int tz = 1+(m+n)/2, i, j, k;
            arr.resize(tz);
            for ( k = 0, i = 0, j = 0; k < tz && i < m && j < n; k++) {
                if (arr1[i] <= arr2[j]) {
                    arr[k] = arr1[i++];
                } else {
                    arr[k] = arr2[j++];
                }
            }
            for ( ; i < m && k < tz; k++) {
                arr[k] = arr1[i++];
            }
            for ( ; j < n && k < tz; k++) {
                arr[k] = arr2[j++];
            }
            if ( k == tz) {
                if ((m+n)%2) { res = arr[k-1]; }
                else { res = (arr[k-1]+arr[k-2])/2; }
            } 
            return res;
        }
};
class Solution3 {
    public:
        int lengthOfLongestSubstring(string s) {
            int i=0, j=0;
            int res = 0;
            map<char, int> hash;
            for ( i = 0, j =0; j < s.length(); j++ ) {
                hash[s[j]]++;
                if (hash[s[j]] == 1) {
                    ;
                } else { // Shrink the window
                    while (hash[s[j]] > 1) {
                        hash[s[i++]]--;
                    }
                }
                res = max(res, j-i+1);
            }
            return res;
        }
};

class Solution6 {
    public: 
        string convert(string s, int rows) {
            int k, i, j;
            vector<string> res;
            string tmp;
            if (rows == 1) return s;
            res.resize(rows, "");
            for ( k = 0, i = 0, j = 0; i < rows && k < s.length(); k++, i++) {
                res[i] += s[k];
                if ( i == rows-1) {
                    while (i--) {
                        k++;
                        res[i] += s[k];
                    }
                    i = 0;
                }
            }
            for ( i = 0; i < rows; i++) {
                tmp += res[i];
            }
            return tmp;
        }
};
class Solution10 {
    public:
        bool isMatch(string s, string p) {
            int i, j;
            char prev;
            bool res = true, loop = true;
            for (i = 0, j =0; i < s.length() && j < p.length(); ) {
                if ( p[j] == '*') {
                    // accound for all the same chars in source string
                    while (i < s.length() && 
                            ((s[i] == prev) || prev == '.')) {
                                i++;
                            }
                    // all the previos occurences has been matched with *
                    j++;
                    // acount for same char in pattern string.
                    while ( j < p.length() && loop) {
                        if (p[j] == prev) {
                            j++;
                        } else if ( i == s.length()) {
                            // All the matching is done. check the pattern
                            if (p[j+1] == '*') j += 2;
                            else loop = false;
                        } else loop = false;
                    }
                } else if ( i < s.length() && j < p.length()) {
                    prev = p[j];
                    if (s[i] == p[j] || p[j] == '.') {
                        i++; j++;
                    } else if (p[++j] == '*') {
                        j++; 
                    }
                    else {
                        res = false; 
                        break;
                    }
                }
            }
            return (res && i == s.length() && j == p.length());
        }
};
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
ListNode*   makeList(vector<int>& list) {
    if ( list.size()) {
        ListNode* head = new ListNode(list[0]);
        ListNode*   tmp = head;
        int i;
        for ( i = 1;i < list.size(); i++) {
            tmp->next = new ListNode(list[i]);
            tmp = tmp->next;
        }
        return head;
    }
    return NULL;
}  
void printList(ListNode*    list) {
    while(list) {
        cout << list->val << ", ";
        list = list->next;
    }
    cout << endl;
}

vector<ListNode*> makeLists(vector<vector<int>> & ns) {
        int i;
        vector<ListNode*> lists;
        for ( i = 0; i < ns.size(); i++) {
            lists.push_back(makeList(ns[i]));
        }
        return lists;
    }
class Solution23 {
public:
    ListNode    *last;
     
    ListNode*   insert(ListNode**    head, ListNode* node) {
        ListNode    *tmp = *head;
        if (tmp == NULL)   {
            *head = node;
            last = node;
        } else if ( node == NULL)  ;    
        else {
            last-> next = node;
            last = last->next;
        }
        return last;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int sz = lists.size(), index = 0, i;
        ListNode*   nlist = NULL;
        ListNode*   tmp = NULL;
        vector<ListNode*>::iterator itr;
        if ( sz == 1 ) return lists[0];
        if ( sz == 0 ) return NULL;
        for ( itr = lists.begin(); itr != lists.end();) {
            tmp =  *itr;
            if ( tmp == NULL) lists.erase(itr);
            else itr++;
        }
        sz = lists.size();
        while (sz) {
            index = 0;
            for ( i = 0; i < sz; i++) {
                if (lists[index]->val > lists[i]->val) {
                    index = i;
                };
            }      
            tmp = lists[index];
            insert(&nlist, tmp); tmp = tmp->next;
            lists[index] = tmp;
            if (tmp == NULL) {
                lists.erase(lists.begin()+index);
                sz--;
            }
        }
        return nlist;
    }
};
class Solution264 {
    public: 
        map<int, int> nhash;
        bool ugly2(int n) {
            bool ugly = true; 
            int pn;
            while (n > 1) {
                pn = n;
                if ( n%5 == 0) n = n/5;
                if ( n%2 == 0) n = n/2;
                if ( n%3 == 0) n = n/3;
                if ( pn == n) { ugly = false; break;}
            }
            return ugly;
        }

        int helper(int n) {
            int i = 1, j, t = 1, count = 1; // 1 for 1
            queue<int> factors[3];
            int     primes[3] = {2, 3, 5};
            int     maxs[3] = {INT_MAX/2, INT_MAX/3, INT_MAX/5};    

            if ( n < 7) return n;
            factors[0].push(2);
            factors[1].push(3);
            factors[2].push(5);
        
            while (count < n) {
                t = min(factors[0].front(), 
                        min(factors[1].front(), factors[2].front()));
                for ( i = 0; i < 3; i++) {
                    if ( t == factors[i].front()) {
                        factors[i].pop(); // This will take care of duplicates
                    }
                    if ( count < maxs[i]) 
                        factors[i].push(t*primes[i]); 
                }
                count++;
            }
            return t;
        }
        int nthUglyNumber(int n) {
            int count = 0, tn = n;
            int nugly = 0, i = 0;
            return helper(n);
        }
};
class Solution632 {
    class Node {
        public: 
            int val; 
            int list_index;
            int elem_index;

            Node(int val, int lindex, int eindex):
                val(val), list_index(lindex), elem_index(eindex) {}
            Node() {}
    };
    struct nodeCompare {
        bool operator()(Node& n1, Node& n2) {
            return n1.val > n2.val;
        }
    };
    public: 
        priority_queue<Node, vector<Node>, nodeCompare> que;
        vector<int> smallestRange(vector<vector<int>> nums) {
            vector<int> res;
            Node    tmp(0,0,0), max(INT_MIN, 0, 0);
            int sz = nums.size();
            int i, j = 0;
            int range = INT_MAX;
            if (nums.size() == 0) return res;
            res.resize(2);
            // pick the 0th element from all lists
            for ( i = 0; i < sz; i++) {
                que.push(Node(nums[i][0], i, 0));
                if ( nums[i][0] > max.val) {
                    max.val = nums[i][0];
                    max.list_index = i; 
                    max.elem_index = 0;
                }
            } 
            // Take the list of min element and get the next element
            tmp = que.top();
            if ( max.val-tmp.val < range ) {
                    range = max.val - tmp.val;
                    res[0] = (tmp.val);
                    res[1] = (max.val);               
                }
            i = tmp.list_index;
            j = tmp.elem_index;
            while (++j < nums[i].size()) { // keep doing till there are elements to extract
                que.pop(); 
                if ( nums[i][j] > max.val) {
                    max.val = nums[i][j];
                    max.list_index = i; 
                    max.elem_index = j;
                }
                que.push(Node(nums[i][j], i, j));
                tmp = que.top();
                i = tmp.list_index;
                j = tmp.elem_index;

                if ( max.val-tmp.val < range ) {
                    range = max.val - tmp.val;
                    res[0] = (tmp.val);
                    res[1] = (max.val);               
                }
            }
            return res;
        }
};
class Solution839 {
    public:
        int count = 0;
        map<int, int> hash; // index of string and the set.

        int numSimilarGroups(vector<string>& words) {
            int sz = words.size();
            int wsz = words[0].length();
            vector<vector<int>> dist;
            int i, j, k, index = 0;
            count = sz;
            vector<int> s;
            if ( sz < 2 ) return sz;
            dist.resize(sz);
            s.resize(sz, 0);
            for ( i = 0; i < sz; i++) {
                dist[i].resize(sz);
                s[i] = i;                
            }
            // Find the edit distance from a word to following words
            for ( i = 0, j = 0; i < sz; i ++) {
                for ( j = i+1; j < sz; j++, k = 0) {
                    for ( index = 0; index < wsz; index++) {
                    if (words[i][index] != words[j][index]) k++;
                    }
                    dist[i][j] = k;
                    if ( k == 2 || k == 0) {
                        unify(s, i, j);
                    }
                }
            }
            for ( i = 0; i < sz; i++) {
                if (!hash.count(find(s,i))) hash[find(s,i)]++;
            }
            return hash.size();
        }
        int find(vector<int>& s, int x) {
            if ( x == s[x]) return x;
            return (s[x] = find(s,s[x]));
        }
        void unify(vector<int>& s, int i, int j) {
            int p1, p2;
            p1 = find(s,i); p2 = find(s,j);
            if (find(s,i) != find(s,j)) {
                s[p2] = p1;
            }
        }
};
class Solution1349 {
    public: 
        int rows, cols;
        int count = INT_MIN, ctmp;
        vector<vector<bool>> visited;

        bool validSeat(int x, int y) {
            if ( x >= 0 && x < rows) {
                if ( y >= 0 && y < cols) {
                    return true;
                }
            }
            return false;
        }
        void blockSeat(vector<vector<char>>& seats, int x, int y) {
            int i, j;
            if (validSeat(x-1, y-1)) visited[x-1][y-1] = true;
            if (validSeat(x-1, y+1)) visited[x-1][y+1] = true;
            if (validSeat(x+1, y-1)) visited[x+1][y-1] = true;
            if (validSeat(x+1, y+1)) visited[x+1][y+1] = true;
            if (validSeat(x, y-1)) visited[x][y-1] = true;
            if (validSeat(x, y+1)) visited[x][y+1] = true;
        }
        bool dfs(vector<vector<char>>& seats, int x, int y) {
            if ( validSeat(x,y) && !visited[x][y]) {
                visited[x][y] = true;
                if (seats[x][y] == '.') {
                    ctmp++;
                    //Block the other seats now  by marking them visited.
                    blockSeat(seats, x,y);
                    // explore all the other valid possibilities
                    dfs(seats, x-1, y);
                    dfs(seats, x+1, y);
                }
            }
        }
        int maxStudents(vector<vector<char>> seats) {
            int tmax = INT_MIN;
            int i, j, k, l = 0;
            rows = seats.size();
            vector<vector<bool>> vtmp;
            if (rows) cols = seats[0].size();
            else return 0;
            visited.resize(rows);
            vtmp.resize(rows);
            for ( i = 0; i < rows; i++)  {
                visited[i].resize(cols, false);
                vtmp[i].resize(cols, false);
            }
            // we will have to traverse the graph for all coordinates. 
            // there might be disconnected components. 
            for ( k = 0; k < rows; k++) {
                for ( l = 0; l < cols; l++) {
                ctmp = 0;
                if (seats[k][l] == '#') continue;
                    
                for ( i = 0; i < rows; i++) {
                    for ( j = 0; j < cols; j++) {
                        if (!visited[i][j])
                            dfs(seats, i, j);
                    }
                }
                tmax = max(ctmp, tmax);
                visited = vtmp;
                visited[k][l]= true;
                }
            }
            return tmax;
        }
};
class Solution1353 {
public:
    void qsort1(vector<vector<int>>& events, int i, int j, int idx) {
        if ( i >= j) return;
        int p = pivot(events, i, j,idx);
        qsort1(events, i, p-1, idx);
        qsort1(events, p+1, j, idx);
    }
    int pivot(vector<vector<int>>& events, int x, int y, int pindex) {
        int i = x-1, j=x, k;
        float p = events[y][pindex];
        for (k = x; k < y; k++) {
            if (events[k][pindex] < p) {
                swap(events[k], events[++i]);
            }
            else j++;
        }
        swap(events[y], events[++i]);
        return i;
    }
    struct cmp {
        bool operator()(vector<int> n1, vector<int> n2) {
            return (n1[1] > n2[1]);
        }
    };
    bool canAttend(const vector<int>& event, int day) {
        if ( day <= event[1] && day >= event[0])
            return true;
        return false;
    }
    int maxEvents(vector<vector<int>>& events) {
        int emax = 0;
        int start = 0, count = 0, i = 0;
        int day = 1;
        int size = events.size();
        priority_queue<vector<int>, vector<vector<int>>, cmp> que;
        qsort1(events, 0, events.size()-1, 0);
        vector<int> etmp;
        // events are sorted on starting date. 
        // now for all the events possible on day d, attend which is 
        // finishing earliest
        
        do {
            // add all the events, can attend on this day to que.
            while ( i < size ) {
                if (canAttend(events[i], day)) {
                    que.push(events[i++]);
                } else {
                    // check the same event next day (i.e que is !empty())
                    // or the next event
                    if (que.empty())
                        day++;
                    break;
                }
            }
            while (!que.empty()) {
                if (canAttend(que.top(), day)) {
                    count++;
                } else {
                    que.pop();
                    continue; // check the next event for the same day 
                }                 
                que.pop();
                day++;
                break;
            }
        } while ( i < size || !que.empty());  
        return count;
    }
};

class ProductOfNumbers1352 {
public:
    vector<int> list;

    ProductOfNumbers1352() {
        
    }
    
    void add(int num) {
        list.push_back(num);    
    }
    
    int getProduct(int k) {
        // asumptions vector has K size and result doesn't overflow
        int i, res = 1; 
        int sz = list.size();
        sz--;
        for ( i = 0; i < k; i++) {
            res *= list[sz-i];
        }
    }
};
class Solution218 {
    public:
    struct nodeh {
        bool operator()(const vector<int>& b1, 
                        const vector<int> b2)  {
                            return b1[2] < b2[2];
                        }
    };
    struct noder {
        bool operator()(const vector<int>& b1, 
                        const vector<int> b2)  {
                            return b1[1] > b2[1];
                        }
    };
    public:
        // tell if a building is present at x cordinate.
        bool validBldg(vector<int> b, int x) {
            if (b[0] <= x && b[1] > x) return true; // right cordinate is excluded
            return false;
        }
        vector<vector<int>> getSkyline(vector<vector<int>>& bs) {
            vector<vector<int>> res; 
            vector<int> tbldg, tres, ptbldg;
            priority_queue<vector<int>,vector<vector<int>>, nodeh> hque; 
            priority_queue<vector<int>,vector<vector<int>>, noder> rque; 
            int sz = bs.size();
            int mx, mh = 0;
            int i;
            // Sanity
            if (sz == 0) return res;
            if ( sz == 1 && bs[0].size() == 0) return res;
            tres.resize(2); ptbldg.resize(3, 0);
            mx = bs[0][0]; i = 0;
            while (i < sz || !hque.empty()) {
            // for all the buildings at a given x add them to height pq
                while (i < sz && validBldg(bs[i], mx)) {
                    hque.push(bs[i]);
                    rque.push(bs[i]);
                    i++;
                }

                while (!hque.empty()) {
                    tbldg = hque.top();
                    if (validBldg(tbldg, mx)) { // found valid bldg with Max height
                        if (ptbldg == tbldg || mh == tbldg[2]) { break;}
                        else ptbldg = tbldg;
                        tres[0] = mx;
                        tres[1] = tbldg[2];
                        res.push_back(tres);
                        mh = tres[1];
                        break;
                    } else { // not a valid bldg take it out
                        hque.pop();
                    }
                }
                if (hque.empty()) {
                    tres[0] = mx;
                    tres[1] = 0;
                    res.push_back(tres);
                }
                // next position to consider is min of top of rque or next bldg
                //i++;
                if (!rque.empty() && i < sz) {
                    if (bs[i][0] < rque.top()[1]) {
                        mx = bs[i][0];
                    } else {
                        mx = rque.top()[1];
                        rque.pop();
                    }
                } else if (!rque.empty()) {
                    mx = rque.top()[1];
                    rque.pop();
                } else if (i < sz && hque.empty()) mx = bs[i][0];
            }
            return res;
        }
    /*    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> res;
        vector<int> tres(2,0);
        map<int, set<int, greater<int>>> hash;
        map<int, set<int, greater<int>>>::iterator it;
        set<int, greater<int>> tset, t2;
        vector<int> b = buildings[0];
        tres[0] = b[0];
        tres[1] = b[2];
        
        res.push_back(tres);    // insert the first building 
        tset.insert(b[2]);      
        hash[b[1]] = tset;
        hash[b[1]].insert(1);
        for (int i = 1; i < buildings.size(); i++) {
            b = buildings[i];
            it = hash.begin();
            // Multiple cases now
            
            if ( b[0] > it->first) {
                // no over lap in the buildings
                tres[0] = it->first;
                tres[1] = it->second;
                hash.erase(it);
                hash[b[0]].insert(b[2]);
                hash[b[1]].insert(b[2]);
            } else {
                if (b[1] < it->first) { // second building is contained with in first one
                    if ( b[2] <= it->second) ; // nop
                    else {
                        hash[b[0]].insert(b[2]);
                        hash[b[1]].insert(b[2]);
                    }
                } else {
                    if ( b[2] <= it->second) {
                        hash[b[1]] = b[2];   
                    }
                    else {
                        hash[b[0]] = b[2];
                        hash[b[1]] = b[2];
                    }
                }
            }
            res.push_back(tres);
        }
        return res;
    }*/
};
class Solution685 {
public:
    vector<bool> visited;
    vector<int> res;
    vector<int> parent;
    vector<int> ufp; // union find parent
    void initUnionFind() {
        int i;
        for ( i = 0;i < ufp.size(); i++) {
            ufp[i] = i;
        }
    }
    int find(int v) {
        if ( ufp[v] == v) return v;
        ufp[v] = find(ufp[v]); 
    }
    void munion(int x, int y) {
        if ( find(x) != find(y)) {
            ufp[x] = find(y);
        }
    }
    vector<int> ufCycle(vector<vector<int>>& nums) {
        int i;
        vector<int> res = {0,0};
        for ( i = 0; i < nums.size(); i++) {
            if (find(nums[i][0]) == find(nums[i][1])) {
                // cycle is found
                res[0] = nums[i][0];
                res[1] = nums[i][1];
            } else {
                munion(nums[i][0], nums[i][1]);
            }
        }
        return res;
    }

    int dfs(vector<vector<int>>& g, int v) {
        int i;
        if (!visited[v]) {
            visited[v] = true;
            for (i = 0; i < g[v].size(); i++) {
                    return dfs (g, g[v][i]);
            }
        }
        else return v;
        return 0;
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int sz, i, src = 1;
        vector<vector<int>> graph;
        vector<int> tres;
        /// in a directed acyclig graphs number of edges = v-1
        // here one extra edge so number same as vertecies.
        sz = edges.size();
        res.resize(2,0); 
        tres.resize(2,0); 
        parent.resize(sz+1, 0);// parent[x]=y x is parent of y
        ufp.resize(sz+1, 0);// parent[x]=y x is parent of y
        visited.resize(sz+1, false); // dummy 0 entry
        // Create a graph from the given edges
        graph.resize(sz+1);
        initUnionFind();
        for ( i = 0; i < sz; i++) {
            if (parent[edges[i][1]]) {
                res = edges[i];
                tres[1] = edges[i][1];
                tres[0] = parent[edges[i][1]]; 
                src = edges[i][1];
                // tres has gone in graph creation so return tres if cycle.

            } else {
                parent[edges[i][1]] = edges[i][0];
                graph[edges[i][0]].push_back(edges[i][1]);
            } 
        }
        // If we picked the wrong edge we will get cycle in the graph
        if (i = dfs(graph, src)) {
            // if cycle in graphs and two parents for same vertex
            // culprit edge is in tres
            if (res[0] == 0) {
                return ufCycle(edges);
            } else return tres;
        }
        return res;
    }
};
class Solution560 {
    public:
        int subarraySum(vector<int>& arr, int k) {
            int res = 0, psum = 0;
            int sz = arr.size(), i;
            map<int, int> hash;
            hash[0]++;
            for ( i = 0; i < sz; i++) {
                psum += arr[i];
                if (hash.count(psum-k)) res += hash[psum-k];
                hash[psum]++;
            }
            return res;
        }
};
class Solution1362 {
    public:
        vector<int> closestDivisors(int num) {
            vector<int> res, tmp;
            res.resize(2,0); tmp.resize(2,0);
            int max = sqrt(num+2), i, j;
            for (i = max, j = max; i > 0; i--, j--) {
                if ((num+1)%i == 0 && tmp[0] == 0) {
                    tmp[0] = i;
                    tmp[1] = (num+1)/i;
                }
                if ((num+2)%i == 0 && res[0] == 0) {
                    res[0] = i;
                    res[1] = (num+2)/i;
                }
                if ( res[0] != 0 && tmp[0] != 0) {
                    break;
                }
            }

            return abs(res[1]-res[0]) > abs (tmp[1]-tmp[0]) ?  tmp: res;
        }
};
class Solution1361 {

    public: 
        vector<int> parent;
        bool validateBinaryTreeNodes(int num, vector<int>& left, vector<int>& right) {
            bool res = true;
            int  count = 0, i;
            parent.resize(num, -1);
            for ( i = 0; i < num; i++) {
                if (left[i] != -1) {
                    if (parent[left[i]] == -1) {
                        parent[left[i]] = i;
                    } else { // duplicate parents
                        res = false; break;
                    }
                }
                if (right[i] != -1) {
                    if (parent[right[i]] == -1) {
                        parent[right[i]] = i;
                    } else { // duplicate parents
                        res = false; break;
                    }
                }
            }
            for ( i = 0; i < num; i++) {
                if (parent[i] == -1) {
                    count++;
                }
            }
            return (count == 1 ? res: false);      
        }
};
class Solution1363 {
    public: 
        string largestMultipleOfThree(vector<int>& nums) {
            string res = "", suffix = "";
            int sz = nums.size(), tmp, maxn = 0;
            int i, si, ei, resi, rei;// indexes to keep track of digits to use
            vector<int> pre;
            char buf[2];

            pre.resize(sz,  0);
            sort(nums.begin(), nums.end(), greater<int>());
            pre[0] = nums[0];
            
            for (i = 1; i < sz; i++) {
                pre[i] += pre[i-1]+nums[i]; 
            }
            si = 0; resi = 0; rei = 0; ei = 0;
            
            if (( sz == 1 && nums[0]%3 == 0) || pre[0] == 0){
                sprintf(buf, "%d", nums[si]);
                res += buf;
                return res;
            } else if ( sz ==1) {
                return res;
            }
             
            // Determine what all numbers can be used for  / by 3, 
            // largest sum that is divisibe by 3
            i = sz-1;
            while ( i > 0 ) {
                if (pre[i] == pre[i-1]) {
                    i--;
                    suffix += "0";
                } else break;
            }
            for ( ; i>=0 ; i--) {
                if  (pre[i] % 3 == 0) {
                    ei = i; resi = 0;
                    maxn = pre[i]; break;
                } 
            }   
          /*  
            sort(nums.begin(), nums.end())
            for (i = sz-1; i >=0 ; i--) {
                while ( maxn && (pre[i] - pre[si]) > maxn) {
                    if ( pre[i] - pre[si] % 3 == 0) {
                        maxn = pre[i]-pre[si];
                        resi = si;
                    }
                    si++;
                }
            }*/
            // use the si and ei to make string
            for (;si <= ei && maxn; si++) {
                sprintf(buf, "%d", nums[si]);
                res += buf;
            }
            return res+suffix;
        }
};
class Solution1358 {
public:
    int numberOfSubstrings(string s) {
        int res = 0; 
        map<char, int> hash;
        int count = 0, i, j, tmp;
        int len = s.length();

        for ( i=0, j = 0; j < len; j++) {
            // enlarge the window
            tmp = ++hash[s[j]];
            if ( tmp == 1) count++; 

            // window created. Now shrink maintaining condition
            while ( count == 3) { 
                res += len-j;
                tmp = --hash[s[i++]];
                if (tmp == 0) count--;
            }
        }
        return res;
    }
};
class Solution1356 {
    public: 
    class node {
        public:
            int ones, num;
            node(int o, int n) : ones(o), num(n) {}
    };
    struct nodeCompare {
        bool operator()(node n1, node n2) {
            if ( n1.ones == n2.ones) return n1.num > n2.num;
            return n1.ones > n2.ones ;
        }
    };
    public:
        int getBits(int num) {
            int i, count = 0;
            while (num) {
                num = num & num-1;
                count++;
            }
            return count;
        }
        vector<int> sortByBits(vector<int>& nums) {
            vector<int> res;
            int i, sz = nums.size();
            int tmp;
            priority_queue<node, vector<node>, nodeCompare> que;
            for (i = 0; i < sz; i++) {
                tmp = getBits(nums[i]);
                que.push(node(tmp, nums[i]));
            }
            while ( !que.empty()) {
                res.push_back(que.top().num);
                que.pop();
            }
            return res;
        }
};
class Solution1178u {
private: 
    int validWord(string& w, string& p, map<char, int>& ph, map<char, int>& wh) {
        int i, matchFound = 0;
        if (wh.count(p[0]) == 0) return matchFound;
        for (auto i: wh ) {
            if ( 0 == ph.count(i.first)) return 0;
        }
        return 1;
    }
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        vector<int> res;
        map<char, int> phash, tmp;
        vector<map<char, int>> whash;
        int j, tres = 0;
        // check for each words validity wrt to puzzle
        for (auto w: words) {
            for (j = 0; j < w.length(); j++) {
                tmp[w[j]]++;
            }   
            whash.push_back(tmp);
            tmp.clear();
        }
        for ( auto i: puzzles) {    
            // For each puzzle string make a hash
            for (j = 0; j < i.length(); j++) {
                phash[i[j]]++;
            }  
            // Check each work against this puzzle
            for ( j = 0; j < words.size(); j++) {
                tres += (validWord(words[j], i, phash, whash[j]));
            }
            res.push_back(tres);
            tres = 0;
            phash.clear();
        }   
        return res;
    }
};
class Solution1178 {
private: 
    
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        vector<int> res;
        map<int, int> wmap;
        int i, j, tres = 0;
        int wkey =0, pkey=0;
        // Convert each word to a key. 
        // Number of chars and their position doesn't matter
        for (auto w: words) {
            wkey = 0;
            for (j = 0; j < w.length(); j++) {
                wkey |= 1<< (w[j]-'a');
            }   
            wmap[wkey]++;
        }
        for ( auto p: puzzles) {    
            // For each puzzle, get the possible valid subsets
            // for all the possible subsets check if that subset exists in words
            for (j = 0; j < (1 << (p.length()-1)); j++) {
                pkey = 1 << (p[0]-'a'); // first char should be present
                // Make a key for each subset
                for (i = 0; i < p.length()-1; i++) {
                    if (j & 1<<i) {
                        pkey |= 1 << (p[i+1]-'a');
                    }
                }
                tres += wmap.count(pkey) ? wmap[pkey]: 0;
            }  
            res.push_back(tres);
            tres = 0;
        }   
        return res;
    }
};
class Solution1377 {
    public: 
        vector<bool> visited;
        vector<int> parent;
        double  result(vector<vector<int>>& graphs, int j) {
            double res = 1;
            int p = parent[j];
            if ( j == 0 || j == 1) return 1;
            res = res/graphs[p].size();
            res = res*result(graphs,p);
            return res;
        }
        double bfs(vector<vector<int>>& graphs, int t, int target) {
            double res = 1;
            int sz = graphs.size();
            visited[0] = true;
            queue<int> que;
            int i = 1, length;
            que.push(i); //
            while ( !que.empty() && t) {
                length = que.size();                
                t--;
                while (length) {                    
                    i = que.front(); que.pop();
                    length--;
                    if ( !visited[i]) {
                        visited[i] = true;
                        for (auto j:graphs[i]) {
                            que.push(j);
                            parent[j] = i;
                            if ( j == target) {
                                if (t && graphs[j].size()) { return 0;}
                                res = result(graphs, target);
                                return res;
                            }
                        }
                    }
                }
            }
            return 0;
        }
        double frogPosition(int ver, vector<vector<int>>& edges, int t, int target) {
            double res  = 0;
            int sz = edges.size(), i;
            vector<vector<int>> graph;
            graph.resize(ver+1); // dummy 0 vertex
            if (sz == 0) return (target == 1);
            visited.resize(ver+1, false); 
            parent.resize(ver+1, 0);
            for (auto e :edges) {
                if ( e[0] < e[1] ) graph[e[0]].push_back(e[1]);
                else graph[e[1]].push_back(e[0]);
            }
            res = bfs(graph, t, target);
            return res;
        }
};
class Solution1376 {
public:
    
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        int res = 0, tmp = 0;
        int i=0, j,length;
        pair<int, int> p;

        vector<vector<int>> org;
        queue<pair<int, int>> que; // pair of vertex and time to reach it
        org.resize(n);
        for ( auto e: manager) {
            if ( e != -1) org[e].push_back(i);
            i++;
        }
        que.push({headID, 0});
        while ( !que.empty()) {
            length = que.size();
            p = que.front(); que.pop();
            res = max(res, p.second + informTime[p.first]);
                for ( j = 0; j < org[p.first].size(); j++) {
                    que.push({org[p.first][j], p.second + informTime[p.first]});
                }
        }
        return res;
    }
};
class Solution25 {
    public:
        ListNode* reverse206(ListNode* head) {
            if (NULL == head || head->next == NULL) return head;
            ListNode    *ctmp, *ptmp, *cur, *inp = NULL;
            cur = head;
            while (cur && cur->next) {
                ptmp = cur->next;
                ctmp = cur->next->next;
                cur->next->next = cur;
                cur->next = inp;
                inp = ptmp;
                cur = ctmp;
            }
            if (cur) {
                cur->next = inp;
                return cur;
            }
            return inp;
        }
        ListNode* reverse92(ListNode* head, int m, int n) {
            int i = 1, tmp;
            ListNode    *ctmp, *ptmp, *cur, *inp, *pcur = NULL;
            ListNode    *pinp, *prev;
            if (NULL == head || head->next == NULL) return head;
            cur = head;
            while ( i++ < m) {
                pcur = cur;
                cur = cur->next;
            }
            i--; inp = cur;
            while ( i++ <= n) {
                pinp = inp;   
                inp = inp->next;
            }   
            if ( n == m+1) {
                tmp = pinp->val;
                pinp->val = cur->val;
                cur->val = tmp;
                return head;
            }
            prev = cur;
            cur = cur->next;
            prev->next = inp;
            while (cur && cur != inp) {
                ptmp = cur->next;
                cur->next = prev;
                prev = cur;
                cur = ptmp;
            }
            if (pcur) {
                pcur->next = prev;
                return head;
            } else return prev;
        }
        ListNode* reverseKGroup(ListNode* head, int k) {
            int i = 0, j, sz;
            ListNode    *prev, *cur, *next;
            prev = head; 
            i = 0;
            while (prev) {
                prev = prev->next;
                i++;
            }
            sz = i; i = 1;
            head = reverse92(head, i, i+k-1);
            
            while (i < sz) {
                j = i;
                for (; i < j+k && i < sz; i++) {
                    ;
                }
                if ( i+k-1 <= sz)
                    reverse92(head, i, i+k-1);
            }
            return head;
        }
};
class Solution24 {
public:
    ListNode* swapPairs(ListNode* head) {
        if ( NULL == head || head->next == NULL) return head;
        ListNode    *cur, *prev, *next, *tmp = NULL;
        prev = head;
        head = prev->next;
        while ( prev && prev->next) {
            cur = prev->next;
            if (tmp) tmp->next = cur;            
            next = cur->next;
            cur->next = prev;
            prev->next = next;
            tmp = prev;
            prev = prev->next;
        }
        return head;
    }
};
class Solution11 {
public:
    int maxArea(vector<int>& height) {
        int res = 0, tmp;
        int i, xi, j, xj;
        // Two POinter problem. RUn two pointers. One from start 
        // one from last.
        i = 0; j = height.size()-1;
        while ( i < j) {
            xi = height[i];
            xj = height[j];
            tmp = (j-i) * min(xi, xj);
            res = max (res,tmp);
            if ( xi < xj) {
                i++;
            } else j--;
        }
        return res;
    }
};
class Solution12 {
public:
    string helper(int& num, int  div) {
        char c;
        string res = "";
        bool sp = false;
        int n = num/div, rem = n%div;
        
        switch(div) {
            case 1000: c= 'M';break;
            case 500: 
                c= 'D'; 
                if ( num >= 900) {
                    res = "CM"; num -= 900;
                    sp = true;
                }break;
            case 100: 
                c= 'C';
                if ( n == 4) {
                    res = "CD";
                    sp = true; num -= 400;
                }break;
            case 50: 
                c= 'L';
                if ( num >= 90) {
                    res = "XC";
                    sp = true;
                    num = num-90;
                }break;
            case 10: 
                c = 'X';
                if ( n == 4) {
                    res = "XL";
                    sp = true;
                    num = num%10;
                } break;
            case 5: 
                c = 'V';
                if ( num == 9) {
                    res = "IX";
                    sp = true;
                    num = 0;
                }
                break;
            case 1: c = 'I';
                if ( num == 4) {
                    res = "IV"; num = 0;
                    sp = true;
                }
                break;
        };
        if ( !sp) {
            num %= div;
            res += string(n, c);
        }
        return res;
    }
    string intToRoman(int num) {
        int out = 0;
        string res = "";
        int arr[] = {1000, 500, 100, 50, 10, 5, 1};
        int i = 0, div;
        while (num) {
            div = arr[i];
            res += helper(num, div);     
            i++;
        }
        return res;
    }
};

class Solution15 {
public:
    vector<vector<int>> twoSum(vector<int>& nums, int start, int K) {
        vector<vector<int>> res;
        vector<int> tres(2,0);
        int previ = INT_MAX, prevj = INT_MAX;
        int i = start, j = nums.size()-1;
        while ( j > i) {
            if (previ == nums[i] && prevj == nums[j]) {
                if ((previ+ prevj) == K ) {i++; j--;
                } else if ((previ+ prevj) > K ) j--;
                else i++;
                continue;
            }
            previ = nums[i];
            prevj = nums[j];
            if ( nums[i]+nums[j] == K) {
                tres[0] = nums[i];
                tres[1] = nums[j];
                res.push_back(tres);
                i++;j--;
            } else if (nums[i]+nums[j] > K) j--;
            else i++;
        }
        return res;
    }
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        int K = 0;
        vector<vector<int>> res;
        vector<vector<int>> res2;
        vector<int> tres;
        int i= 0, j, desiredSum = 0;
        sort(nums.begin(), nums.end());
        int sz = nums.size();
        if ( sz < 3) return res;
        int prev = INT_MAX;
        for ( i = 0;i <= sz-3; i++) {
            if (nums[i] == prev) continue;
            else prev = nums[i];
            desiredSum = K - nums[i];
            res2 = twoSum(nums, i+1, desiredSum);
            for ( j = 0; j < res2.size();j++) {
                res2[j].push_back(nums[i]);
                res.push_back(res2[j]);
            }
            res2.clear();
        }
        return res;
    }
    
    vector<vector<int>> threeSum2(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tres;   // tmprary result
        tres.resize(3);
        sort(nums.begin(), nums.end());
        int i, j, k, sz = nums.size();
        int tsum = 0, tmp, pnum, pnum2;
        for ( i = 0; i < sz-2; i++) {
            pnum = nums[i];
            j = i+1; k = sz-1; 
            while ( j < k) {
                tmp = nums[i]+nums[j]+nums[k];
                if ( tsum == tmp) {
                    tres[0] = nums[i];
                    tres[1] = nums[j];
                    tres[2] = nums[k];
                    res.push_back(tres);
                    pnum2 = nums[j];
                    while ( nums[j] == pnum2 && j < sz-1) j++;
                } else if ( tmp > tsum) k--;
                else j++;
            }
            while (pnum == nums[i+1] && i < sz-2 ) i++;
        }
        return res;
    }
    int threeSumClosest(vector<int>& nums, int tsum) {
        vector<int> tres;   // tmprary result
        tres.resize(3);
        sort(nums.begin(), nums.end());
        int i, j, k, sz = nums.size();
        int msum = INT_MAX, tmp, pnum, pnum2;
        for ( i = 0; i < sz-2; i++) {
            pnum = nums[i];
            j = i+1; k = sz-1; 
            while ( j < k) {
                tmp = nums[i]+nums[j]+nums[k];
                if (abs(tsum-tmp) < msum) {
                    msum = abs(tsum-tmp);
                    tres[0] = nums[i];
                    tres[1] = nums[j];
                    tres[2] = nums[k];
                    pnum2 = nums[j];
                    //while ( nums[j] == pnum2 && j < sz-1) j++;
                } else if ( tmp > tsum) k--;
                else j++;
            }
           // while (pnum == nums[i+1] && i < sz-2 ) i++;
        }
        return (tres[0]+tres[1]+tres[2]);
    }
    vector<vector<int>> threeSum3(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tres;   // tmprary result
        vector<pair<int, int>> nums2;
        map<int, int> hash, chash;
        int k = 0, i, j, tsum;
        tres.resize(3);
        // for each element in the nums, we need a two sum to make target sum
        // get the target two sum array
        for ( i = 0; i < nums.size(); i++) {
            if (hash.count(nums[i]) == 0) {
                nums2.push_back({i, k-nums[i]}); // we need these 2sums.
            }
            hash[nums[i]]++;
        }
        chash = hash;
        for (i = 0; i < nums2.size(); i++) {
            // for each 2sum in nums2, see if we have ints in nums
            tres[0] = nums[nums2[i].first];
            tsum = nums2[i].second;
            if (hash[tres[0]] > 0) hash[tres[0]]--; // remove this element from hash
            for (j = 0; j < nums.size(); j++) {
                // don't consider the ith element from nums
                if ( nums2[i].first == j) continue;
                if (hash[tsum-nums[j]] && hash[nums[j]]) {
                    tres[1] = nums[j];
                    tres[2] = tsum-nums[j];
                    if (tres[1] == tres[2] && hash[tres[1]] == 1) continue;
                    hash[tres[1]] = 0; 
                    hash[tres[2]] = 0; 
                    res.push_back(tres);
                }
            }
            chash[tres[0]] = 0;  // All the possibilities with this number are exhausted.
            hash = chash;
        }
        return res;
    }
};

class Solution18 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int i, j, k, l;
        int pi, pj, pk;
        int sz = nums.size(), tmp;
        vector<int> tres;
        vector<vector<int>> res;
        tres.resize(4);
        sort(nums.begin(), nums.end());
        for ( i = 0; i < sz-3; i++) {
            pi = nums[i];
            j = i+1;
            for ( ; j < sz-2; j++) {
                pj = nums[j];
                k = j+1;
                l = sz-1;
                while ( k < l) {
                    pk = nums[k];
                    tmp = pi+pj+nums[k]+nums[l];
                    if ( tmp == target) {
                        tres[0] = pi; tres[1] = pj;
                        tres[2] = nums[k]; tres[3] = nums[l];
                        res.push_back(tres);
                        while ( pk == nums[k] && k<l) k++;
                    } else if (tmp > target) l--;
                    else k++;
                }
                while ( pj == nums[j+1] && j < sz-2) j++;
            }
            while ( pi == nums[i+1] && i < sz-3) i++;
        }
        return res;
    }
};
    struct node {
        int index;
        int slice;
        int used;
        node (int s, int index):slice(s), index(index) {} 
    };
    bool sortBySlice(const node& n1, const node& n2) {
        return n1.slice > n2.slice;
    }

class Solution1388 {
public:
    
     int maxSizeSlices(vector<int>& slices) {
        int sz = slices.size(), i, j, ssz;
        int smax = 0, tmax = 0, tmp = 0;
        vector<int> tslices = slices;
        vector<node> sslices;
        for ( i = 0; i < sz-1; i++) {
            sslices.push_back(node(slices[i], i));
        }
        //sort(sslices.begin(), sslices.end());
        for ( i = 0, j = sz-1; i < sz/3; i++, j--) {
            tmax += sslices[j].slice;
        }
        while (smax < tmax) {
               ssz = sz; 
            while ( ssz) { 
                i = sslices[ssz-1].index;
                tmp += sslices[ssz-1].slice;
                tslices[i] = true;
                
            }
            //sort(sslices.begin(), sslices.end());
            if ( tmp > smax && tmp <=tmax)
                smax = tmp;
        }
        return smax;
    }
};
class Solution22 {
public:
    void helper(int l, int r, string tmp, vector<string>& ans) {
        if ( l ==0 && r == 0) {
            ans.push_back(tmp);
            return ;
        }
        if (l) helper(l-1, r, tmp+"(", ans);
        if (r && r > l) helper(l, r-1, tmp+")", ans);
    }
    
    vector<string> generateParenthesis(int n) {
        string tmp;
        vector<string> res;
        int l = n, r = n;
        tmp = "("; l--;
        helper(l,r,tmp, res);
        return res;
    }
};
class Solution26 {
public:
    int removeDuplicates(vector<int>& nums) {
        int i, j;
        int sz = nums.size();
        int count = 1;
        if ( sz < 2) return sz;
        for ( i = 0, j = i+1; j < sz; j++) {
            if ( nums[i] == nums[j]) {
                ;
            } else {
                nums[i+1] = nums[j];
                count++;
                i++;
            }
        }
        return count;
    }
};
class Solution1138 {
    public: 
    struct pathNode {
        int x, y;       // cordinates of parent:
        char parent;
        char direction; // from parent to this node
        pathNode(int x, int y, char p, char d): x(x), y(y), direction(d), parent(p) {}
        pathNode() {}
    };
    public: 
        string res;
        vector<string> board = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};
        vector<vector<pathNode>> path, path_copy;  // Store parent of each node along with the direction from parent to this node

        void getPath(int x, int y, char src, string& res) {
            int lx, ly;
            if (path[x][y].parent == 0) return;
            if (path[x][y].parent == src) {
                res += path[x][y].direction;
                return;
            }           
            getPath(path[x][y].x, path[x][y].y, src, res);
            res += path[x][y].direction;
        }
        
        pair<int, int>  
            bfs(int x, int y, char dest) {
            vector<vector<bool>> visited;
            int i;
            int bsz = board.size();
            int csz = board[0].length();
            visited.resize(bsz);
            pair<int, int> p;
            for ( i = 0; i < bsz;i ++) {
                visited[i].resize(csz, false);
            }
            for ( i = 1; i < csz; i++ ) {
                visited[bsz-1][i] = true;
            }
            queue<pair<int, int>>     que;
            que.push({x,y});
            visited[x][y] = true;
            while (!que.empty()) {
                p = que.front();que.pop();
                x = p.first; y = p.second;            
                    if ( board[x][y] == dest) { 
                        return {x,y};
                    }
                    if (x-1 >= 0 && !visited[x-1][y]) {
                        path[x-1][y] = pathNode(x,y,board[x][y], 'U');
                        if ( board[x-1][y]==dest) return {x-1,y};
                        que.push({x-1, y});
                        visited[x-1][y] = true;
                    }
                    if (x+1 < bsz && !visited[x+1][y]) {
                        path[x+1][y] = pathNode(x,y,board[x][y], 'D');
                        if ( board[x+1][y]==dest) return {x+1,y};
                        que.push({x+1, y});
                        visited[x+1][y] = true;
                    }
                    if (y-1 >= 0 && !visited[x][y-1]) {
                        path[x][y-1] = pathNode(x,y,board[x][y], 'L');
                        if ( board[x][y-1]==dest) return {x, y-1};
                        que.push({x, y-1});
                        visited[x][y-1] = true;
                    }
                    if (y+1 < csz && !visited[x][y+1]) {
                        path[x][y+1] = pathNode(x,y,board[x][y], 'R');
                        if ( board[x][y+1]==dest) return {x, y+1};
                        que.push({x, y+1});
                        visited[x][y+1] = true;
                    }
            }
            return {0,0};
        }
        string alphabetBoardPath(string& target) {
            int bsz = board.size(), csz = board[0].length();
            int x, y, i;
            char parent = 'a';            
            path.resize(bsz);
            pair<int, int> p = {0,0};
            for (i = 0; i < bsz; i++)  {
                path[i].resize(csz, pathNode(0,0,'0','0'));
            }
            path_copy = path;
            x = 0; y = 0;
            for ( i = 0; i < target.length(); i++) {
                p = bfs(x,y,target[i]);
                getPath(p.first, p.second, parent, res );
                res += "!";
                parent = target[i]; // new source
                x = p.first; y = p.second;
                path = path_copy;
            }
            return res;
        }
};
class Solution410 {
public:
    // Determine if a target sim is valid or not.
    // if valid, return the max sum, 
    // if cuts are more than given return 0
    // if not enough cuts, return -1
    int validCut(vector<int> & nums, int m, int target) {
        int ncuts = 1, i;
        long long maxSum = INT_MIN, tsum = 0;

        for ( i = 0; i < nums.size(); i++) {
            if ((tsum + long(nums[i])) <= target) { 
                tsum += long(nums[i]);
            } else {
                ncuts++;
                maxSum = max(maxSum, tsum);
                tsum = long(nums[i]);
            }
        }
        maxSum = max(maxSum, tsum);
        if (ncuts == m) {
            return maxSum;
        } else if ( ncuts < m) return -1;
        return 0;
    }
    int splitArray(vector<int>& nums, int m) {
        int start, end;
        int sz = nums.size();
        int res = INT_MAX;        
        long long tsum = 0;
        int target ; 
        vector<int> tnums = nums;
        for ( auto i: nums) {
            tsum += long(i);
        }
        sort(tnums.begin(), tnums.end());
        start = tnums[0]; end = tsum;
        while (start <= end) {
            // Find some target number using Binary search
            target = (end - start)/2 + start;
    
            // check the validity of this target
            tsum = validCut(nums, m, target);
            switch(tsum) {
                case 0: // more than desired cuts. in crease the target sum
                    start = target+1;
                    break;
                case -1: // less than desired cuts.
                    end = target-1;
                    break;
                default:        
                // we were able to cut the array in m subs with target sum. 
                // see if we can improve. 
                end = target-1;
                if (tsum < res) res = tsum;
            } 
        }
        return res;
    }
};
class Solution924 {
public:
    vector<int> parent; // Parent array to maintain the disjoint sets of uF
    void initialiseUF() {
        int i; 
        // each node belongs to its own set
        for ( i = 0; i < parent.size(); i++) 
            parent[i] = i;
    }
    int findUF(int x) {
        if (parent[x] == x) return x;
        return parent[x] = findUF(parent[x]); // path compresion
    }
    void unionUF (int x, int y) {
        if (findUF(x) != findUF(y)) {
            parent[findUF(x)] = findUF(y);
        }
    }
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int row = graph.size(), col;
        int isz = initial.size();
        if (row) col = graph[0].size();
        int i, j, x;
        int count2, count = INT_MIN;
        int res = 0, res2 = -1;
        map<int, int> hash;
        map<int, int> infected;
        parent.resize(row, 0);  // no of vertices is same as rows / cols
        initialiseUF();
        for ( i = 0; i < row; i++) {
            for ( j = 0; j < col; j++) {
                if ( graph[i][j]) {
                    unionUF(i,j);
                }
            }
        }
        // Find component sizes.
        for ( i = 0; i < parent.size(); i++) {
            hash[findUF(i)]++;
        }
        for ( i = 0; i < initial.size(); i++) {
            x = findUF(initial[i]);
            infected[x]++;
        }
        count2 = INT_MIN;
        count = INT_MIN;
        for ( i = 0; i < initial.size(); i++) {
            x = findUF(initial[i]);
            // consider only the components with one infected node
            if (infected[x] == 1) {
                if (hash[x] > count2) {
                    count2 = hash[x];
                    res2 = initial[i];
                } else if (hash[x] == count2) {
                    res2 = min(res2, initial[i]);
                }
            } else {
                if (hash[x] > count) {
                    count = hash[x];
                    res = initial[i];
                } else if (hash[x] == count) {
                    res = min(res, initial[i]);
                }
            }
        }
        return (res2 == -1) ? res : res2;
    }
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode    *next;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode*   getTree(vector<int>& nums, int start) {
    int i = start, sz = nums.size();
    int left, right;
    if (i >= nums.size()) return NULL;
    TreeNode*   root = new TreeNode(nums[i]);
    i++;
    left = 2*i -1; right = 2*i ;
    if ( nums[left] != INT_MIN) {
        root->left = getTree(nums, 2*i-1);
    }
    if ( nums[right] != INT_MIN) {
        root->right = getTree(nums, 2*i);
    }
    return root;
}
class Solution1302 {
    // mainatin a hash for all nodes at a depth. 
    // sum all the nodes at the max depth.
public:
    map<int, vector<int>> hash;
    int helper(TreeNode* root, int depth) {
        int ldepth = 0, rdepth = 0;
        if ( NULL == root) return depth;
        depth++;
        hash[depth].push_back(root->val);
        
        if ( root->left == NULL && root->right == NULL) return depth;
        
        if ( root->left) {
            ldepth = helper(root->left, depth);
        }
        if ( root->right) {
            rdepth = helper(root->right, depth);
        }
        return max(ldepth, rdepth);
    }
    int deepestLeavesSum(TreeNode* root) {
        if ( NULL == root) return 0;
        int depth = 0, res = 0;
        depth = helper(root, depth);
        vector<int> nums = hash[depth];
        for ( auto i: nums) {
            res += i; 
        }
        return res;
    }
};

class Solution7 {
public:
    int reverse(int x) {
        long long res = 0;
        while (x) {
            res += long(x%10);
            x /= 10;
            if (x) res *= 10;
        }
        if ( res > (1<<31)-1) return 0;
        return res;
    }
};

class Solution787 {
    public: 
    struct edge {
        int src, dest; 
        int cost, hop;
        edge(int s, int d, int wt, int hop) : src(s), dest(d), cost(wt), hop(hop) {}
        edge() {}
    };
    class comp {
        public:
        bool operator()(edge& s, edge& d) {
            return s.cost > d.cost; // for min que incoming ( dest) should be small
        }
    };
    
public:
    vector<int> cost; // cost to this node from source
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        priority_queue<edge, vector<edge>, comp> pq;
        vector<vector<pair<int, int>>> graph; // graph needed to detemine the adjacency
        vector<pair<int, int>> list;        // List in the graph
        int count = 0, x;
        
        // initialisation 
        cost.resize(n, INT_MAX);            // maintain initial infinity cost
        cost[src] = 0;
        graph.resize(n);
        // create the graph
        for ( auto e : flights) {
            graph[e[0]].push_back({e[1], e[2]});
        }

        edge tedge(src, src, 0, 0);
        pq.push(tedge);
        while (!pq.empty()) {
            tedge = pq.top(); pq.pop();
            if ( tedge.hop > K+1) continue;
            x = tedge.dest;
            if ( x == dst) return tedge.cost;
            // relax all the edges from new src
            list = graph[x];
            for ( auto e: list) {
                //cost[e.first] = min(eg.cost+e.second, cost[e.first]); 
                cost[e.first] = tedge.cost+e.second;
                pq.push(edge(x, e.first, cost[e.first], tedge.hop+1));
            }
        }
        return -1; 
    }
};
class Solution39 {
    void helper(vector<int>& cand, int index, int target, vector<vector<int>>& res, vector<int>& tres) {
        if ( target <= 0) {
            if (target == 0)  res.push_back(tres);
            return;
        }
        int i;
        for ( i = index; i < cand.size(); i++) {
            tres.push_back(cand[i]); 
            // consider all the possibilities with ith number including number itse
            helper(cand, i, target-cand[i], res, tres);
            tres.pop_back(); 
        }
    }
    public:
    vector<vector<int>> combinationSum(vector<int>& cand, int target) {
        vector<int> tres;
        vector<vector<int>> res;
        helper(cand, 0, target, res, tres);
        return res;        
    }
};
class SolutionChallenge3 {
public:
    int maxSubArray(vector<int>& nums) {
        int start, end;
        int i;
        int res = INT_MIN;
        int ppsum, cpsum, psum = 0;
        int pnsum, cnsum;
        for ( i = 0; i < nums.size(); i++) {
            if ( nums[i] > 0) {
                if (psum  >= 0) psum += nums[i]; 
                if ( psum < 0 ) psum = nums[i];
            } else {
                if (psum >= 0) psum += nums[i];
                else psum = max(psum, nums[i]);
            }
            res = max(res, psum);
        }
        return res;
    }
};
class SolutionChallenge5 {
public:
    int maxProfit(vector<int>& prices) {
        int canSell = 0, buyPrice = 0; 
        int res = 0, i;
        
        for ( i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i-1]) {
                if ( canSell == 0) {
                    buyPrice = prices[i-1];
                    canSell = 1;
                }
            } else if ( prices[i] < prices[i-1]) {
                if (canSell) {
                    res += prices[i-1] - buyPrice;
                    canSell = 0;
                }
            }
        }
        if ( canSell) {
            res += prices[i-1]-buyPrice;
        }
        return res;
    }
};

class SolutionChallege6 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<int> keys(strs.size(), 0);
        int i, j;
        vector<string> tmp = strs;
        map<string, vector<string>> hash;
        map<string, vector<string>>::iterator itr;
        vector<vector<string>> res;
        tmp = strs;
        for ( i = 0; i < strs.size(); i++) {
            sort(tmp[i].begin(), tmp[i].end());
            hash[tmp[i]].push_back(strs[i]);
        }
        res.resize(hash.size());
        for ( i = 0, itr = hash.begin(); itr != hash.end();  itr++, i++) {
            res[i] = itr->second;
        }
        return res;
    }
};
class SolutionChallenge7 {
public:
    int countElements(vector<int>& arr) {
        map<int, int> hash;
        int i, count = 0;
        for ( i = 0; i < arr.size(); i++) {
            hash[arr[i]]++;
        }
        for ( auto j: arr) {
            if (hash[j+1]) {
                count++;
            }
        }
        return count;
    }
};
class Solution123 {
    public: 

    /*  The idea is this    
        On any day, you can have two states. 
        1: You have stocks in hand and can sell. 
        0: you don't have any stocks and can buy
        Let Profit on any day with k transations is defined as below
                    P(i,k,0)
                (NOPE)/   \Sell on ith day [ Transaction is counted on buy] 
        max[P(i-1,k, 0)), P(i-1,k,1 )
                    P(i,k,1)
                (NOPE)/   \Buy on ith day [ Transaction is counted on buy] 
        max[P(i-1,k, 1)), P(i-1,k-1,0 )
        */
    int maxProfit(vector<int>& prices) {
        int K = 2;
        int res = 0, sz = prices.size();
        int i, j, k;
        if ( sz < 2) return 0;
        vector<vector<int>> P(sz+1, vector<int>(K+1, 0));
        vector<vector<int>> C(sz+1, vector<int>(K+1, 0));
        // base conditions initialised above. 
        for ( j = 1; j <= K; j++) { // start from 1st transaction
            // P[1][j] = 0; Profit on first day is 0
            C[1][j] = -prices[0];
        }
        //  for each day starting from day 2.
        for ( i = 2; i <= sz; i++) {
            // what is the max profit for K transactions
            k = i-1;
            for ( j = 1; j <= K; j++) {
                P[i][j] = max(P[i-1][j],C[i-1][j] + prices[k]);
                C[i][j] = max(C[i-1][j], P[i-1][j-1]-prices[k]); // Transactions counted at buy
            }
        }
        return P[sz][K];
    }
};
class SolutionChallenge8 {
public:
    bool backspaceCompare(string S, string T) {
        stack<char> s, t;
        int i, j;
        for ( i =0; i < S.length(); i++) {
            if (S[i] == '#') {
                if (!s.empty()) s.pop();
            }
            else s.push(S[i]);
        }
        for ( i =0; i < T.length(); i++) {
            if (T[i] == '#') {
                if (!t.empty()) t.pop();
            }
            else t.push(T[i]);
        }
        if (s.size() == t.size()) {
            while (!s.empty()) {
                if (s.top() != t.top() ) return false;
                s.pop(); t.pop();
            }
            return true;
        }
        return false;
    }
    bool backspaceCompare2(string S, string T) {
        int i = S.length(), j = T.length(); 
        int ic = 0, jc = 0;
        i--; j--;
    
        while (!(i<0 && j <0)) {
            while ( i >= 0 && S[i] == '#') {
                i--;
                ic++;
            }
            while ( j >= 0 && T[j] == '#') {
                j--;
                jc++;
            }
            if ( ic || jc) {
                if (ic && i>=0) {
                    ic--;
                    i--;
                } 
                if (jc && j >=0) {
                    j--;
                    jc--;
                }
                continue;
            }
            if ( i>=0 && j >=0) {
                if (S[i] != T[j])
                    return false;
                i--;j--;
            } else return false;  

        }
        return i==j;
    }
};

class SolutionChallenge9 {
public:
    int height(TreeNode* root, int ht, int& maxPath) {
        /*  At each node
            Get the height of left and right subtrees
            Determine the maxPath length between the left and right subtress
            send the height and maxPath to root for root to make a decision
            */
        if (NULL == root) return ht;
        int lheight = 0, rheight = 0;
        
        if (root->left) {
            lheight = height(root->left, ht, maxPath);
        }
        if (root->right) {
            rheight = height(root->right, ht, maxPath);
        }        
        maxPath = max(maxPath, lheight+rheight);// Local maxPath at the Node
        return 1+max(lheight, rheight);   // return the height to root
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int r = 0,l = 0;
        int maxPath = INT_MIN;
        if ( NULL == root) return 0;
        l = height(root->left, 0, maxPath);
        r = height(root->right, 0, maxPath);
        
        return max(l+r,maxPath);
    }
};
class SolutionChallenge10 {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> q;
        //priority_queue<int, vector<int>, greater<int> > pmin;

        int x,y;
        for ( auto i: stones) {
            q.push(i);
        }
        while ( q.size() > 1) {
            y = q.top();
                q.pop();
            x = q.top();
                q.pop();
            y -= x;
            if (y) q.push(y);
        }
        if (q.empty()) return 0;
        return q.top();
    }
};
class Solution552 {
public:

    int count(int n, int a, int l) {
        int res = 0;
        if (n == 0) return 0;
        if ( n == 1) {
            if (a && l) res = 3;
            else if (a || l) res = 2;
            else res = 1;
            return res;
        }
        res += count(n-1,a,2); // Using p n current pos, reset l
        if (a) {
            res += count(n-1, a-1, 2);
        }
        if (l) {
            res += count(n-1, a, l-1);
        }
        return res;
    }
    int checkRecord2(int n) {
        return count(n,1,2);
    }

    int checkRecord(int n) {
        int i, j, k;
        long long n12 = 3, n02 = 2, n11 = 3, n01 = 2, n10 = 2, n00 = 1;
        long long tmp02, tmp12;
        if ( n== 0) return 0;
        for ( i = 2; i <= n; i++) {
            tmp12 = n12;
            n12 = n12+n02+n11;
            tmp02 = n02;
            n02 = n02+n01;
            n11 = tmp12+n10+tmp02;
            n01 = tmp02+n00;
            n10 = tmp12+tmp02;
            n00 = tmp02;
        }
        return n12;
    }
};
class SolutionChallenge11{
public:
    int findMaxLength(vector<int>& nums) {
        int res = 0, count = 0;
        int i;
        unordered_map<int, int> hash;
        hash[0] = -1; // base case
        for ( i = 0; i < nums.size(); i++) {
            if ( nums[i] == 0) count--;
            else count++;
            if ( !hash.count(count)) {
                hash[count] = i; // count is seen first time. Store the index.
            } else {
                res = max(i - hash[count], res);
            }
        }
        return res;
    }
};

class SolutionChallenge12 {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int len = s.length();
        int pos;
        for (auto v : shift) {
            pos = v[1]%len;
            if (pos) {
                if (v[0]) {
                    // right shift
                    s = s.substr(len-pos)+s.substr(0,len-pos);
                } else {
                    s = s.substr(pos) + s.substr(0,pos);
                }
            }
        }
        return s;
    }
};

class SolutionChallenge13 {
public:
    bool checkValidString(string s) {
        stack<int> open, wild;
        int i = 0;
        for (auto c : s) {
            if ( c == '(') {
                open.push(i);
            } else if ( c==')') {
                if (!open.empty()) open.pop();
                else if (!wild.empty()) wild.pop();
                else return false;
            } else if (c=='*') {
                wild.push(i);
            }
            i++;
        }
        while ( !open.empty() && !wild.empty()) {
            if (open.top() > wild.top()) {
                return false;
            }
            open.pop(); wild.pop();
        }
        return open.empty();
    }
};
class SolutionChallenge14 {
    struct node {
        int x,y;
        int wt;
        node (int x, int y, int wt) :x(x), y(y), wt(wt) {}
        node () {}
    };
    struct compare {
        bool operator()(const node& n1, const node& n2) {
            if (n1.wt > n2.wt) return true;
            return false;
        }
    };
public:
    int minPathSum(vector<vector<int>>& grid) {
        priority_queue<node, vector<node>, compare> pq;
        int rows = grid.size(), cols;
        if (rows) cols = grid[0].size();
        node source, dest(rows-1, cols-1, 0);
        node tnode;
        int x,y;
        pq.push(node(0,0, grid[0][0]));
        while (!pq.empty()) {
            tnode = pq.top(); pq.pop();
            x = tnode.x ; y = tnode.y;
            if ( x == dest.x && y == dest.y) {
                return tnode.wt;
            }
            if ( y+1 < cols) {
                pq.push(node(x,y+1,grid[x][y+1]+tnode.wt));
            }
            if ( x+1 < rows) {
                pq.push(node(x+1,y,grid[x+1][y]+tnode.wt));
            }
        }
        return 0;      
    }
};

class Solution354 {
public:
    struct env {
        int x,y;
        env(int x, int y):x(x), y(y) {}
        env() {}
    };
    struct compareL{
      bool operator()(const env& e1, const env& e2) {
          if ( e2.x > e1.x) return true;
          if ( e2.x == e1.x) return e2.y > e1.y;
          return false;
      }  
    };

    public:
    int helper(priority_queue<env, vector<env>, compareL> pq, int l, int w) {
        env tEnv;
        int withlen = 0, len = 0;
        int il = l, iw = w;
        if (pq.empty()) return 0;
        tEnv = pq.top(); pq.pop();
        if ( tEnv.x < l && tEnv.y < w) {
            l = tEnv.x ;
            w = tEnv.y ;
            withlen = 1+helper(pq, l, w);        
        } 
        len = helper(pq, il, iw);
        
        return max(withlen, len);
    }
    
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int len = 0;
        priority_queue<env, vector<env>, compareL> pq;
        for ( auto e: envelopes) {
            pq.push(env(e[0], e[1]));
        }
        
        len = helper(pq, INT_MAX, INT_MAX);
        return len;
    }
};
class SolutionChallenge15 {
public:
    int helper(vector<int>& nums, int target, int start, int end) {
        int index = -1, mid = 0;
        if ( end < start) return -1; // Nothing found here
        if ( end == start ) {
            if(nums[start] == target ) return start;
        }
        int size = end-start+1;
        mid = start+size/2; 
        if ( size%2) {
            if (nums[mid] == target) return mid;
             index = helper(nums, target, mid+1, end);
        } else {
             index = helper(nums, target, mid, end);
        }
        if ( index != -1) return index;
        index = helper(nums, target, start, mid-1);      
        return index;
        
    }
    int search(vector<int>& nums, int target) {
        return helper(nums, target, 0, nums.size()-1);    
    }
};
class SolutionChallenge16 {
public:
    TreeNode*   createTree(vector<int> & nums, int start, int end) {
        if ( start > end) return NULL;

        TreeNode* root = new TreeNode(nums[start]);
        start++;
        int i = start;
        while ( i <= end && nums[i] < root->val ) {
                i++;
            } 
        if ( i <= end) {
            root->right = createTree(nums, i, end);
        }
        root->left = createTree(nums, start, i-1);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& nums) {
        int size = nums.size();
        if (size < 1) return NULL;
        int start = 0, end;
        TreeNode    *root = new TreeNode(nums[0]);
        if ( nums.size() == 1) return root;
        start++;
        int i = start;
        while ( i < nums.size() && nums[i] < root->val ) {
            i++;
        } 
        root->left = createTree(nums, start, i-1);
        
        if ( i < nums.size()) {
            root->right = createTree(nums, i, nums.size()-1);
        }
            
        return root;
    }
};
class LRUCache {
    private: 
        list<pair<int,int>> l;
        map<int, list<pair<int, int>>::iterator> hash;
        int cap;
    
    public:   
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        // get the position in list from hash for the key
        map<int, list<pair<int, int>>::iterator>::iterator itr = hash.find(key);
        int res;
        if (  itr != hash.end()) {
            list<pair<int, int>>::iterator litr = itr->second;
            res = litr->first;
            l.erase(litr);
            hash.erase(itr);
            l.push_front({key,res});
            hash[key] = l.begin();
            return res;
        }
        return -1;
    }
    
    void put(int key, int value) {    
        map<int, list<pair<int, int>>::iterator>::iterator itr = hash.find(key);
        list<pair<int,int>>::iterator litr;
        if (  itr != hash.end()) {
            litr = itr->second;
            l.erase(litr);
            hash.erase(itr);
        } else if (l.size() >= cap) {
                hash.erase(l.back().first);
                l.pop_back();
                
        }
        l.push_front({key,value});
        litr = l.begin();
        hash[key] = litr;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
class SolutionChallenge17 {
public:
    vector<int> visited;
    bool dfs(int curpos, vector<int>& nums) {
        int i ;
        visited[curpos] = 1;
        // Base condition
        if ( curpos+nums[curpos] >= nums.size()-1) return true;

        // Evaluate choices: In this case all the edges from current pos
        for ( i = 1; i <= nums[curpos] && curpos+i < nums.size() ; i++ ) {
            if ( !visited[curpos+i])
                if ( true == dfs(curpos+i, nums)) return true;
        }
        return false;
    }
    bool canJump(vector<int> nums) {
        visited.resize(nums.size(),0);
        int cur_index = 0, last_index = nums.size()-1;
        int i = cur_index;
        while (cur_index < last_index && i < nums.size()) {
            cur_index = max(cur_index, i+nums[i]);
            i++;
        }
        return (cur_index >= last_index); 
        /*
        if ( nums.size() > 0)
            return dfs(0, nums);
            return false;
            */
        
    }
    bool previous_canJump2(vector<int>& nums) {
        // when target_index >= last_index we got the answer
        int cur_index = 0, target_index = 0;
        int last_index = nums.size()-1;
        int tmp = 0;
        int i = 0;
        if (last_index == 0) return true;
        while (target_index < last_index && i < nums.size())
        {
            tmp = cur_index + nums[cur_index];
            target_index = target_index > tmp ? target_index : tmp;
            i++;
            if ( target_index > cur_index)
                cur_index++;
        }
        if (target_index >= last_index) return true;
        return false;
    }
};
class SolutionChallenge18 {
public:
    int dfs(string s1, string s2, int m, int n) {
        int i = m,j = n;
        while ( i < s1.length()) {
        while ( j < s2.length()) {
            if ( s1[i] == s2[j]) {
                return 1+dfs(s1,s2,m+1,j+1);
                }
                j++;
            }
            i++;
        }
            return 0;
    }
    int longestCommonSubsequence(string text1, string text2) {
        int i, j;
        int n = text1.length(), m = text2.length();
        return dfs(text1,text2,0,0);
    }
    int longestCommonSubsequence2(string text1, string text2) {
        int i, j;
        int n = text1.length(), m = text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for ( i = 1; i <= m; i++) {
            for ( j = 1; j <= n; j++) {
                if ( text1[j-1] == text2[i-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        return dp[m][n];
    }
};
class FirstUnique {
private:
    map<int, int> hash;
    queue<int> que;
    
public:
    FirstUnique(vector<int>& nums) {
        for ( auto n : nums) {
            add(n);
        }    
    }
    
    int showFirstUnique() {
        int res;
        while (!que.empty()) {
            res = que.front();
            if ( 1 == hash[res]) {
                return res;
            }
            que.pop();
        }
        return -1;
    }
    
    void add(int n) {
        if (hash.count(n)) {
                if ( n == que.front()) {
                    que.pop();
                }
        } else {
            que.push(n);    
        }
        hash[n]++;
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
class SolutionChallenge20 {
    // In order traversal
public:
    bool leafNode(TreeNode* root) {
        return (root->left == NULL && root->right==NULL);
    }
    bool helper(TreeNode* root, vector<int>& arr, int index) {
        int size = arr.size();
        bool lt = false, rt = false;
        // Base/exit condition
        if (index >= size || root->val != arr[index]) return false;
        else {
            if (leafNode(root)) {
               return (index+1 == size ); 
            }
        }
        index++;
        if ( root->left) {
            lt = helper(root->left, arr, index);
        }
        if ( lt == false && root->right) {
            rt = helper(root->right, arr, index);
        }
        return (lt || rt);
    }
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        int size = arr.size();
        if ( NULL == root || size == 0) return false;
        
        return helper(root, arr, 0);
    }
};

class Solution206 {
public:
    ListNode*   helper(ListNode** inp, ListNode** h) {
        ListNode* head = *inp;
    //  Base condition of the recursive solution
        if ( head == NULL || head->next == NULL) {
                    *h = head;
                  return head;
        }
        auto tmp = helper(&head->next,h);
        tmp->next = head;
        head->next = NULL;
        return head;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* h;
        helper(&head, &h);    
        return h;
    }
    ListNode* reverseListI(ListNode* head) {
            if (NULL == head || head->next == NULL) return head;
            ListNode    *ctmp, *ptmp, *cur, *inp = NULL;
            cur = head;
            while (cur && cur->next) {
                ptmp = cur->next;
                ctmp = cur->next->next;
                cur->next->next = cur;
                cur->next = inp;
                inp = ptmp;
                cur = ctmp;
            }
            if (cur) {
                cur->next = inp;
                return cur;
            }
            return inp;
        }
};

class Solution115 {
public:
    int helper(string s, string t, int i, int j) {
    if (j >= t.size()) {
        return 1;
    }
    if (i >= s.size()) {
        return 0;
    } 
    int res = 0;
    // Choices
    if (s[i] == t[j]) {
        res += helper(s, t, i+1, j+1);
    } 
    res += helper(s, t, i+1, j);
    
    return res;
    }
    int numDistinct(string s, string t) {
        return helper(s, t, 0, 0);
    }
};
#endif
