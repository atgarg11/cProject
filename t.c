#ifndef LC_1_H_
#define LC_1_H_
#include<set>
#include<map>
#include <stack>
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
            int i, j;
            for ( j = 0; j < input.length(); j++) {
                hash[input[j]]++;
                if (hash[input[j]] == 1) {
                    // This is the first occurence
                    disc++;
                    if (disc > 2) { 
                        i++; disc--;
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
#endif
