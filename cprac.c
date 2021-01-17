#include <stdio.h>
#include <iostream> 
#include <thread>
#include <string>
#include <pthread.h>
#include <vector>
#include <queue>
#include <string>
#include "lc1.h"
#include "lc2.h"

using namespace std;

pthread_cond_t  cond1;
pthread_cond_t  cond2;
pthread_cond_t  cond3;
pthread_mutex_t m;

void printV(vector<int> & nums) {
for ( auto a: nums) {
        cout << a << ", ";
    }
    cout << endl;
}

void printV2(vector<vector<int>> & nums) {
for ( auto a: nums) {
    for ( auto b: a) {
            cout << b << ", ";
        }
        cout << endl;
    }
}
void* first(void* )
{
    printf("Entered first \n");
    pthread_mutex_lock(&m);
    pthread_cond_wait(&cond1, &m);
    printf("first \n");
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&m);
}
void* second(void* )
{
    printf("Entered second \n");
    pthread_mutex_lock(&m);
    pthread_cond_wait(&cond2, &m);
    printf("second\n");
    pthread_cond_signal(&cond3);
    pthread_mutex_unlock(&m);
}

void* third(void* )
{
    printf("Entered third \n");
    pthread_mutex_lock(&m);
    pthread_cond_wait(&cond3, &m);
    printf("third\n");
    pthread_mutex_unlock(&m);
}
class parent {
    public: 
        parent() { ; }
        void first() { cout << " First " ; }
        void second () { cout << " second " ; }
        void third() { cout << " Third " ; }
};
void foo(parent& p) 
{
    p.first();
}
int ijump(vector<int>& nums) {
    int cur_index = 0, target_index = 0;
    int last_index = nums.size()-1;
    int i = 0, tmp;
    vector<int> njumps;
    njumps.resize(last_index+1);

    njumps[0] = 0;
    if ( last_index == 0) return njumps[last_index];

    while (target_index < last_index && i <= last_index){
        tmp = cur_index + nums[cur_index];
        if ( tmp > target_index) {
            target_index++;
            for (; (target_index <= tmp && target_index <= last_index);
                    target_index++)
            {
                njumps[target_index] = njumps[cur_index]+1;
                if (target_index == last_index) return njumps[target_index];
            }
        } 
        target_index--;
        if ( target_index > cur_index) cur_index++;
        i++;
    }
    return -1;
}
void testMedianFinder(int argc, char* argv[])
{
    int i;
    medianFinder    fm; 
    for (i = 0; i < argc; i++ ) {
        fm.addNum(atoi(argv[i]));
    }
    cout << "median: " << fm.findMedian() << "\n";
}
void testMedianSliding()
{
    vector<int> in = {5,5,8,1,4,7,1,3,8,4};
    Solution sol;
    sol.medianSlidingWindow(in, 8);
}
void test424(int argc, char* argv[])
{
    Solution424 sol;
    if (2 == argc) {
        cout << sol.characterReplacement(argv[0], atoi(argv[1])) << endl ;
    }
}
void testLc992(int argc, char* argv[])
{
    //vector<int> A = {2,1,2,1,2}; // 2(10)
    vector<int> A = {1,2,1,3,4}; // 3(3)
    //vector<int> A = {1,2,1,2,3}; // 2(7)
    //vector<int> A = {1,2};
    Solution992 sol;
    cout << sol.subarraysWithKDistinct1(A, atoi(argv[0]));
    cout << endl;
}
// Test cases
//WWWEQRQEWWQQQWQQQWEWEEWRRRRRWWQE 5 
// WWEQERQWQWWRWWERQWEQ 4
// WQWRQQQW 3    
void test1234(int argc, char* argv[])
{
    Solution1234    sol; //WWEQERQWQWWRWWERQWEQ
    string          str(argv[0]);
    cout << " Delta is: " << sol.balancedString(str);
    cout << endl;
}
void test315(int argc, char* argv[])
{
    Solution316    sol; //WWEQERQWQWWRWWERQWEQ
    vector<int> res;
    /*vector<int> nums;
      int i = 0;

      for (i = 0; i < argc; i++) {
      nums.push_back(atoi(argv[i]));
      }*/
    // [10,27,10,35,12,22,28,8,19,2,12,2,9,6,12,5,17,9,19,12,14,6,12,5,12,3,0,10,0,7,8,4,0,0,4,3,2,0,1,0]
    //vector<int> nums = {26,78,27,100,33,67,90,23,66,5,38,7,35,23,52,22,83,51,98,69,81,32,78,28,94,13,2,97,3,76,99,51,9,21,84,66,65,36,100,41};
    vector<int> nums = { 6, 5, 4, 6, 1}; 
    res = sol.countSmaller(nums);
    for ( auto j:res) {
        cout << j << "," ;
    }
    cout << endl;

}

void test340(int argc, char* argv[])
{
    Solution340    sol; //WWEQERQWQWWRWWERQWEQ
    string          str(argv[0]);
    cout << " length is: " << sol.maxString(str, atoi(argv[1]));
    cout << endl;
}

void testLc41(int argc, char* argv[])
{
    Solution41 sol;
    vector<int> nums;
    int i = 0;
    for (i = 0; i < argc; i++) {
        nums.push_back(atoi(argv[i]));
    }
    cout << "first missing numer is : " ;
    cout << sol.firstMissingPositive(nums);
    cout << endl;
}
void test273( int argc, char* argv[])
{
    Solution273 sol;
    int i, j ;
    cout <<  sol.numberToWords(atoi(argv[0]));
    cout << endl;
}
void test403( int argc, char* argv[])
{
    Solution403 sol;
    bool i;
    vector<int> stones;
    switch(atoi(argv[0])) {
        case 1:
            stones = {0,1,2,3,4,8,9,11 }; // False
            break;
        case 2: 
            stones = {0,1,3,5,6,8,12,17}; // True
            break;
        case 3:
            stones = {0,1,3,4,5,7,9,10,12}; //True
            break;
        case 4:
            stones = {0,1,3,6,7}; // false 
            break;
        case 5: 
            stones = {0,1,3,6,10,15,16,21}; // true
    };
    i = sol.canCross(stones);
    cout << " cross :" << i << endl;
}

void test815( int argc, char* argv[])
{
    Solution816 sol;
    vector<vector<int>> routes = { { 1,2,7} , {3,6,7}};
    int i, j ;
    i = sol.numBusesToDestination(routes, atoi(argv[0]), atoi(argv[1]));
    cout << " Buses:" << i << endl;
}
void test895(int argc, char* argv[])
{    
    FreqStack fs;
    vector<int> nums;
    int i = 0;

    for (i = 0; i < argc; i++) {
        fs.push(atoi(argv[i]));
    }
    i = fs.pop();
    while (0xFFFFFFF != i) {
        cout << i << "," ;
        i = fs.pop();
    }
    cout << endl;
}
void testtmp(int argc, char* argv[])
{
    int i = 0;
    cout << atoi(argv[0]) << endl;
    for ( i = 1; i < atoi(argv[0]); ) {
        cout << i << "," ;
        i = i+ i & -i;
    }
    cout << endl;
}
void test1280(int argc, char* argv[])
{
    int i = 0;
    vector<vector<int>> cord = { 
       // {1,0},{2,2},{2,0},{0,1},{1,1} // Pending
        {0,2},{2,2},{1,0},{0,0},{1,2},{2,0},{1,1} //A
    };
    Solution1280 sol;
    cout << sol.tictactoe(cord);
    cout << endl;
}
void test1025( int argc, char* argv[])
{
    Solution1025 sol;
    cout << sol.divisorGame(atoi(argv[0]));
    cout << endl;
}

void test772( int argc, char* argv[])
{
    Solution772 sol;
    string str(argv[0]);
    sol.eval(str);
    cout << endl;
}
void test818( int argc, char* argv[])
{
    Solution818 sol;
    int commands = 0 ;
    commands = sol.racecar(atoi(argv[0]));
    cout << commands << endl;
}
void test72( int argc, char* argv[])
{
    Solution72 sol;
    int dis = sol.minDistance(string(argv[0]), string(argv[1]));
    cout << dis << endl;
}
void test188( int argc, char* argv[])
{
    Solution188 sol;
    //vector<int> prices = {2, 4, 1};
    //vector<int> prices = {3,2,6,5,0,3};
    //vector<int> prices = {1, 2, 4};
    vector<int> prices = {1,2,4,2,5,7,2,4,9,0};
    int profit = 0 ;
    profit = sol.maxProfit2(atoi(argv[0]), prices);
    cout << profit << endl;
}
void testKadane(int argc, char* argv[])
{
    SolutionMisc1 sol;
    //vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    vector<int> arr = {1, -3, 2, -5, 7, 6, -1, -4, 11, -23};
    cout << sol.maxSumSubarray(arr) << endl;
}
void test128(int argc, char* argv[])
{
    Solution128 sol;
    vector<int> nums = {400, 4, 1, 200, 3, 2};
    sol.sort(nums);
}
void test801(int argc, char* argv[])
{
    Solution801 sol;
    /*
       vector<int> nums1 = {0, 3, 5, 8, 9}; 
       vector<int> nums2 = {2, 1, 4, 6, 9};
       vector<int> nums1 = {0, 4, 4, 5, 9}; 
       vector<int> nums2 = {0, 1, 6, 8, 10};
       vector<int> nums1 = {3,3,8,9,10}; 
       vector<int> nums2 = {1,7,4,6,8};
     */
    vector<int> nums1 = {0,3, 4, 9, 10};
    vector<int> nums2 = {2,3,7,5,6};
    cout << sol.minSwap(nums1, nums2)<< endl;
}
void test5(int argc, char* argv[])
{
    Solution5 sol;
    cout << sol.longestPalindrome(string(argv[0])) << endl;
}
void test1326(int argc, char* argv[])
{
    Solution1326 sol;
    //vector<int> ranges = {3, 4, 1, 1, 0, 0};
    //vector<int> ranges = {1,2,1,0, 2,1,0,1};
    vector<int> ranges = {4,0,0,0,4,0,0,0,4};
    /*vector<int> ranges = { 0,0,0,1,4,2,2,2,2,4,0,0,0,5,4,0,0,5,3,0,
                            1,1,5,1,1,2,4,1,0,4,3,5,1,0,3,3,4,2,2,4,
                            3,1,1,0,4,0,2,1,4,0,0,3,3,1,1,4,4,2,0,3,
                            4,0,1,5,3,0,1,0,2};
                            */
    int n = ranges.size()-1;
    cout << "Taps: " << sol.minTaps(n, ranges) << endl;
}
void test1(int argc, char* argv[])
{
    //vector<int> nums = {3,2,4};
    vector<int> nums = {3,3};
    vector<int> res;
    Solution1 sol;
    res = sol.twoSum(nums, atoi(argv[0]));
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] <<" ," ;
    }
    cout << endl;
}
void test1011(int argc, char* argv[])
{
    int days = 0;
    Solution1011 sol;
    vector<int> w;
    switch(atoi(argv[0])) {
        case 3:
            days = 3;
            w = {3,2,2,4,1,4};
            break;
        case 4:
            w = {1,2,3,1,1};
            days = 4;
            break;
        case 5:
            w = {1,2,3,4,5,6,7,8,9,10};
            days = 5;
            break;
            case 6:
            w = {10,50,100,100,50,100,100,100};
            days = 5;
        default:
            break;
    };
    cout << sol.shipWithinDays(w, days) << endl;
}
void test846(int argc, char* argv[])
{
    Solution846 sol;
    vector<int> hands ;
    int w;
    switch(atoi(argv[0])) {
        case 3:
            hands = {1,2,3,6,2,3,4,7,8};
            w = 3;
            break;
        case 4:
            hands = {1,2,3,4,5};
            w = 4;
            break;
        case 2:
            hands = {0,0};
            w = 2;
            break;
        default:
            break;
    };
    cout << sol.isNStraightHand(hands, w) << endl;
}
void test774(int argc, char* argv[])
{
    Solution774 sol;
    vector<int> s;
    int k = 0;
    switch(atoi(argv[0])) {
        case 9:
            s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            k = 9;
            break;
        default:
            break;
    };
    cout << sol.minmaxGasDist(s, k) << endl;
}

void test1074(int argc, char* argv[])
{
    Solution1074 sol;
    vector<vector<int>> s;
    int t = 0;
    switch(atoi(argv[0])) {
        case 4:
            s = { {0,1,0},  
                  {1,1,1}, 
                  {0,1,0}};
            t = 0;
            break;
        default:
            break;
    };
    cout << sol.numSubmatrixSubTarget(s, t) << endl;
}
/*  Connected components    */
void test4001(int argc, char* argv[]) {
    int  i, j;
    vector<vector<int>> res;
    vector<vector<int>> graph = {
                                    {1,2}, 
                                    {0,3},
                                    {0,4},
                                    {1,4},
                                    {2,3}};
    SolutionConnectedGraph sol;
    res = sol.connected(graph);
    for ( i = 0;i < res.size(); i++) {
        for ( j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << ", ";
        }
        cout << endl;
    }
}
void test200(int argc, char* argv[]) {
    vector<vector<char>> grid = {
                            {'1','1','1','1','0'},
                            {'1','1','0','1','0'},
                            {'1','1','0','0','0'},
                            {'0','0','0','0','0'},
                            };
    Solution200 sol;
    cout << sol.numIslands(grid) << endl;
}
void test1036(int argc, char* argv[]) {
    vector<int> src;
    vector<int> dest;
    vector<vector<int>> blocked;
    Solution1036 sol;
    switch(atoi(argv[0])) {
        case 0:
            src = { 0,0};
            dest = {0,2};
            blocked = { {1,0}, {0,1}};
            break;
        case 1:
            src = { 0,0};
            dest = {10,10};
            blocked = { {10,9}, {9,10}, {10, 11}, {11, 10}};
            break;
        default:
            break;
    };
    
    cout << sol.isEscapePossible(blocked, src, dest) << endl;
}
void test212(int argc, char* argv[]){
    Solution212 sol;
    vector<vector<char>> grid;
    vector<string> words;
    vector<string> res;
    int i;
    switch(atoi(argv[0])) {
     case 1:
        grid = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}};
        words = {"oath", "pea", "eat", "rain" };
        break;
    case 2:
        grid = {{'a', 'a'}};
        words = {"aaa"};
        break;
    case 3:
        grid = { {'a', 'b'}, {'c', 'd'}};
        words = {"ab","cb","ad","bd","ac",
                "ca","da","bc","db","adcb",
                "dabc","abb","acb"};
        break;
    case 4:
        grid = { {'a', 'b'}, {'a', 'a'}};
        words = {"aba","baa","bab","aaa","aaab",
                "aaaa","aaba"};
        break;
    case 5:
        grid = { {'a', 'b', 'c'}, {'a', 'e', 'd'}, {'a', 'f', 'g'}};
        words = {"eaabcdgfa", "abcdefg","gfedcbaaa","befa","dgc","ade"};
        break;
    case 6:
    grid = { {'a', 'a', 'a', 'a'}, 
            {'a', 'a', 'a', 'a'}, 
            {'a', 'a', 'a', 'a'}};
        words = {"aaaaaaaaaaaaa","aaaaaaaaaaaa","aaaaaaaaaaab"};
        break;
    case 7:     
        grid = {{'a', 'a'}}, 
        words = {"a"};
        break;
      
    default: 
        break;
    };
    res = sol.findWords(grid, words);
    for ( i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }
}
void test208(int argc, char* argv[])
{
    Solution208 sol;
    vector<string> words;
    vector<string> swords;
    switch(atoi(argv[0])) {
        case 1:
            words = {"insert","insert","insert","search","startsWith","search", "startsWith"};
            swords = {"apple","orange","apples","apple","appu","oran", "orang"};
            break;
        case  2:
            words = {"insert","search","search","startsWith","insert","search"};
            swords = {"apple","apple","app","app","app","app"};
            break;
        case  3:
            words = {"insert","search", "search"};
            swords = {"a", "a", "b"};
            break;
        case  4:
            words = {"insert","search", "search"};
            swords = {"ab", "ab", "bb"};
            break;
            case 5:
                words = {"insert","search","search","startsWith",
                        "startsWith","insert","search","startsWith",
                        "insert","search","startsWith"};
                swords = {"ab","abc","ab","abc","ab","ab",
                        "abc","abc","abc","abc","abc"};
                        break;
    };
    cout << sol.testTrie(words, swords) << endl;
}
void test79(int argc, char* argv[]) {
    Solution79 sol;
    vector<vector<char>> grid;
    vector<string> words;
    int i;
    switch(atoi(argv[0])) {
        case 1:
            grid = {
                                {'A','B','C','E'},
                                {'S','F','C','S'},
                                {'A','D','E','E'}};
            words = {"ABCCED", "SEE", "ABCB"};
            break;
        case 2:
            grid = {{'a','a'}};
            words = {"a", "aaa"};
            break;
        default:
            break;
    };
    
    for (i = 0; i < words.size(); i++) {
        cout << sol.exist(grid, words[i]) << ", ";
    } 
    cout << endl;
}
void test56(int argc, char* argv[])
{
    Solution56      sol;
    int i;
    vector<vector<int>> intervals;
    vector<vector<int>> res;

    switch(atoi(argv[0])) {
        case 1:
            intervals = {{2,6},{1,3},{8,10},{15,18}};
            break;
        case 2:
            intervals = {{1,4},{4,5}};
            break;
        case 3: 
            intervals = {{1,4},{2,3}};
            break;
        case 4:
            intervals = {{1,4},{0,2},{3,5}};
            break;
        case 5:
            intervals = {{2,3},{4,5},{6,7},{8,9},{1,10}};
            break;
        case 6:
            intervals = {{1,3},{0,2},{2,3},{4,6},{4,5},{5,5},{0,2},{3,3}};
           break; 
        deafult:
            break;
    };
    res = sol.merge(intervals);
    
    for ( i = 0; i < res.size(); i++) {
        cout << "[ " << res[i][0] << ", " << res[i][1] <<" ]" << " ,";
    }
    cout << endl;
}
void test57(int argc, char* argv[])
{
    Solution57      sol;
    int i;
    vector<vector<int>> intervals;
    vector<int> ni;
    vector<vector<int>> res;

    switch(atoi(argv[0])) {
        case 1:
            intervals = {{1,3},{6,9}};
            ni = {2, 5};
            break;
        case 2:
            intervals = {{1,2},{3,5},{6,7},{8,10},{12,16}};
            ni = {4,8};
            break;
        case 3: 
            intervals = {{}};
            ni = {4,8};
            break;
        case 4:
            intervals = {{1,2}};
            ni = {4,8};
            break;
        case 5:
            intervals = {{1,2}};
            ni = {1,7};
            break;
        case 6:
            intervals = {{1,5}};
            ni = {0,3};
            break;
        deafult:
            break;
    };
    res = sol.insert(intervals, ni);
    
    for ( i = 0; i < res.size(); i++) {
        cout << "[ " << res[i][0] << ", " << res[i][1] <<" ]" << " ,";
    }
    cout << endl;
}
void testLc4(int argc, char* argv[]) {
    Solution4 sol;
    vector<int> arr1; 
    vector<int> arr2;
    switch(atoi(argv[0])) {
        case 1:
            arr1 = {1, 3};
            arr2 = {2};
            break;
        case 2:
            arr1 = {1, 3};
            arr2 = {2, 4};
            break;
    };
    cout << sol.findMedianSortedArrays(arr1, arr2) << endl;
}
void test03(int argc, char* argv[]) {
    Solution3   sol;
    // "dvdf", pwwkew, 
    string s = string(argv[0]);
    cout << sol.lengthOfLongestSubstring(s) << endl;
}
void test6(int argc, char* argv[]) {
    Solution6 sol;
    //"paypalishiring"  int rows = 3;
    cout << sol.convert(argv[0], atoi(argv[1])) << endl;
}
void test632( int argc, char* argv[])
{
    Solution632 sol;
    vector<vector<int>> inp; 
    vector<int> res;
    switch (atoi(argv[0])) {
        case 0://[20, 24]
            inp = { {1, 10, 15, 24,26}, 
                    { 0, 9, 12, 20}, 
                    {4, 18, 22, 30}};
            break;
        default:
            break;
    }
    res = sol.smallestRange(inp);
    
    cout << "[ " << res[0] << ", " << res[1] << "]" << endl;        
    
}
void test10(int argc, char* argv[]) {
    Solution10 sol;
    string s, p;
    if (argc < 2) {
        switch(atoi(argv[0])) {
            case 1: 
                s= "aa"; p = "a*";
                break;
            case 2:
                s= "ab"; p = ".*";
                break;
            case 3:
                s= "ab"; p = ".*c";
                break;
            case 4:
                s = "mississippi";
                p = "mis*is*p*.";
                break;
            case 5:
                s = "aab";
                p = "c*a*b";
                break;
            case 6:
                s = "aaa";
                p = "a*a";
                break;
            case 7:
                s = "aaa";
                p = "ab*a*c*a";
                break;
            case 8:
                s =  "aaca";
                p = "ab*a*c*a";
                break;
            case 9:
                s= "ab"; p = ".*c";
                break;    
        }
    } else {
        s= string(argv[0]);
        p = string(argv[1]);
    }
    cout << s << ", " << p << endl;
    cout << sol.isMatch(s, p) << endl;
}
void test23(int argc, char* argv[]) {
    Solution23 sol;
    vector<vector<int>> nums;
    ListNode*   res;
    vector<ListNode*> tmp;
    switch(atoi(argv[0])) {
        case 1:
            nums = {{1,3,5}, {1,4}, {2}};
            break;
        case 2:
            nums = {{}, {}};
            break;
    };
    tmp = makeLists(nums);
    res = sol.mergeKLists(tmp);
    printList(res);
}
void test264(int argc, char* argv[])
{
    Solution264 sol;
    cout << sol.nthUglyNumber(atoi(argv[0])) << endl ;
}
void test839(int argc, char* argv[])
{
    Solution839 sol;
    vector<string> words;
    switch(atoi(argv[0])) {
        case 0://2
            words = {"tars", "rats", "arts", "star"};
            break;
        case 1:
            words = {"abc", "abc"};
            break;
        case 2://3
            words = {"koqnn","knnqo","noqnk","nqkon"};
            break;
        case 3://2
            words = {"ajdidocuyh","djdyaohuic","ddjyhuicoa","djdhaoyuic","ddjoiuycha","ddhoiuycja","ajdydocuih","ddjiouycha","ajdydohuic","ddjyouicha"};
            break;
    };
    cout << sol.numSimilarGroups(words) << endl;
}
void test1349(int argc, char* argv[]) {
    Solution1349    sol;
    vector<vector<char>> spots;
    switch(atoi(argv[0])) {
        case 0:
            spots = {{ '#','.','#','#','.','#'},
                {'.','#','#','#','#','.'},
                {'#','.','#','#','.','#'}};
                break;
        case 1: 
            spots = {{'.','#'},
                {'#','#'},
                {'#','.'},
                {'#','#'},
                {'.','#'}};
                break;
        case 2:
            spots = {{'#','.','.','.','#'},
                {'.','#','.','#','.'},
                {'.','.','#','.','.'},
                {'.','#','.','#','.'},
                {'#','.','.','.','#'}};
                break;
        case 3:
            spots = {
                {'#','.','#','#','#'},
                {'#','.','.','.','.'},
                {'#','.','.','.','.'},
                {'.','#','.','.','.'}
            };
                break;
    };
    cout << sol.maxStudents(spots) << endl;
}
void test1353(int argc, char* argv[]) {
    Solution1353 sol;
    vector<vector<int>> events;
    switch(atoi(argv[0])) {
        case 1: 
            events = {{1,2},{2,3},{3,4}};
            break;
        case 2:
            events = {{1,2},{2,3},{3,4},{1,2}};
            break;
        case 3://4
            events = {{1,4},{4,4},{2,2},{3,4},{1,1}};
            break;
        case 4://1
            events = {{1,100000}};
            break;
        case 5://7
            events = {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}};
            break;
        case 6: //3
            events = {{1,2},{1,2},{1,6},{1,2},{1,2}};
            break;
        case 7://5
            events = {{1,5},{1,5},{1,5},{2,3},{2,3}};
            break;
        case 8: //2
            events = {{1,1}, {4,4}};
            break;
        case 9: // 18
            events = { {27,27},{8,10},{9,11},{20,21},{25,29},{17,20},
                        {12,12},{12,12},{10,14},{7,7},{6,10},{7,7},{4,8},
                        {30,31},{23,25},{4,6},{17,17},{13,14},{6,9},{13,14}};
            break;
    }
    cout << sol.maxEvents(events) << endl;
}
void test218(int argc, char* argv[]) {
    Solution218_2 sol;
    int i;
    vector<vector<int>> bs;
    vector<vector<int>> res;
    switch(atoi(argv[0])) {
        case 1:
            bs = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, 
            {15, 20, 10}, {19, 24, 8}};
            break;
        case 2:
            bs = {};
            break;
        case 3:
            bs = {{}};
            break;
        case 4:
            bs = {{0,2,3},{2,5,3}};
            break;
        case 5:
            bs = {{1,2,1},{1,2,2}, {1,2,3}};
            break;
        case 6:
            bs = {{0,3,3},{1,5,3}, {2,4,3}, {3,7,3}};
            break;
    };
    res = sol.getSkyline(bs);
    printV2(res);
}
void test685(int argc, char* argv[]) {
    vector<vector<int>> g;
    vector<int> res;
    Solution685 sol;
    switch(atoi(argv[0])) {
        case 1:
            g = {{1,2}, {1,3}, {2,3}};
            break;
        case 2: // 4,1
            g = {{1,2}, {2,3}, {4,1}, {3,4}, {1,5}};
            break;
        case 3://2,1
            g = {{2,1},{3,1},{4,2},{1,4}};
            break;
        case 4: // 4,2
            g = {{4,2},{1,5},{5,2},{5,3},{2,4}};
            break;
    };
    res = sol.findRedundantDirectedConnection(g);
    cout << "[ " << res[0] <<"," << res[1] << " ]" << endl;

}
void test560(int argc, char* argv[])
{
    Solution560 sol;
    vector<int> arr; 
    int k;
    switch(atoi(argv[0])) {
        case 1:
            arr = {1,1,1}; k = 2;
            break;
        case 2: //1
            arr = {-1,-1,1}; k = 0;
            break;
        case 3: //5
            arr = 
            {1,2,3,4,5,6,7,1,23,21,3,1,2,1,1,1,
            1,1,12,2,3,2,3,2,2};
            k = 22;
        break;
    }
    cout << sol.subarraySum(arr, k) << endl;
}
void test1362 (int argc, char* argv[])
{
    Solution1362 sol;
    vector<int> res; 
    // num 9 3,3: 1000 25,40
    res = sol.closestDivisors(atoi(argv[0]));
    cout << "[ " << res[0] << ", " << res[1] << "]" << endl;
}
void test1361 (int argc, char* argv[])
{
    Solution1361 sol;
    vector<int> left, right;
    int num; 
    switch(atoi(argv[0])) {
        case 1: // true
            left = {1,-1,3,-1};right = {2,-1,-1,-1};num = 4;
            break;
        case 2: // false
            left = {1,-1,3,-1};right = {2,3,-1,-1};num = 4;
            break;
        case 3: // false
            left = {1,-1,-1,4,-1,-1}; right = { 2,-1,-1,5,-1,-1};
            num = 6; break;
        case 4:// false
            left = {1,0}; right = {-1,-1}; 
            break;
    }
    cout << sol.validateBinaryTreeNodes(num, left, right) << endl;
    
}
void test1363(int argc, char* argv[])
{
    Solution1363 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case  1:
            nums = {8,1,9};
            break;
        case 2: 
            nums = {8,6,7,1,0};
            break;
        case 3:
            nums = {1};
            break;
        case 4:
            nums = {0,0,0,0,0};
            break;
        case 5:
            nums = {5,8};
            break;
        case 6:
            nums = {1,1,1,2};
            break;
    }
    cout << sol.largestMultipleOfThree(nums)  << endl;
}
void test1358(int argc, char* argv[]) {
    Solution1358 sol;
    string s = string(argv[0]);
    //abcabc: 10, aaabc: 3
    cout << sol.numberOfSubstrings(s) << endl;
}
void test1356(int argc, char* argv[]) {
    Solution1356 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {0,1,2,3,4,5,6,7,8} ;
            //0,1,2,4,8,3,5,6,7
            break;
        case 2:
            nums = {1024,512,256,128,64,32,16,8,4,2,1};
            break; // 1,2,4,8,16,32,64,128,256,512,1024
        case 3:
            nums = {10000, 10000};
            break;
        case 4:
            nums = {2,3,5,7,11,13,17,19};
            break; // 2,3,5,17,7,11,13,19
        case 5:
            nums = {10,100,1000,10000};
            break; // 10,100,10000,1000
    };
    nums = sol.sortByBits(nums);
    for (auto j: nums) {
        cout << j <<", ";
    }
    cout << endl;
}
void test1178(int argc, char* argv[]) {
    Solution1178 sol;
    vector<string> words; 
    vector<string> puzzle;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:
            words = {"aaaa","asas","able","ability","actt","actor","access"};
            puzzle = {"aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"};
            break; //1,1,3,2,4,0
    }
    res = sol.findNumOfValidWords(words, puzzle);
    for (auto i: res) {
        cout << i << ", " ;
    }
    cout << endl;
}
void test1377(int argc, char* argv[])  {
    Solution1377 sol;
    vector<vector<int>> edges;
    int seconds, target, ver;
    switch(atoi(argv[0])) {
        case 1: // .166
            edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
            seconds = 2, target = 4; ver = 7;
            break;
        case 2:
            edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
            seconds = 1, target = 7; ver = 7;
            break;
        case 3:
            edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
            seconds = 20, target = 6; ver = 7;
            break;
        case 4:
            edges = {{2,1},{3,2}};
            ver = 3; seconds = 1; target = 2;
            break;   
        case 5:
            edges = {{2,1},{3,1},{4,2},{5,1},{6,2},{7,5},{8,7},{9,7}};
            ver = 9, seconds = 6; target = 8;
            break; 
    }
    cout << sol.frogPosition(ver, edges, seconds, target) << endl;
}
void test1376(int argc, char* argv[])  {
    Solution1376 sol;
    vector<int> managers;
    vector<int> time;
    int head, n;
    switch(atoi(argv[0])) {
        case 1:
            managers = {2,2,-1,2,2,2}; 
            time = {0,0,1,0,0,0}; 
            head = 2; n = 6;
            break;
        case 2:
            managers = {1,2,3,4,5,6,-1}; 
            time = {0,6,5,4,3,2,1}; 
            head = 6; n = 7;
            break;
         case 3:
            managers = {-1,0,0,1,1,2,2,3,3,4,4,5,5,6,6}; 
            time = {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}; 
            head = 0; n = 15;
            break;
        case 4:
            managers = {3,3,-1,2}; 
            time = {0,0,162,914}; 
            head = 2; n = 4;
            break;
        case 5:
            managers = {-1,5,0,6,7,0,0,0}; 
            time = {89,0,0,0,0,523,241,519}; 
            head = 0; n = 8;
            break;
        case 6:
            managers = {5,9,6,10,-1,8,9,1,9,3,4}; 
            time = {0,213,0,253,686,170,975,0,261,309,337}; 
            head = 4; n = 11;
            break;//2560
        }
    cout << sol.numOfMinutes(n, head, managers, time) << endl;
}
void test25(int argc, char* argv[]) {
    Solution25 sol;
    vector<int> list;
    int m, n;
    ListNode    *head = NULL;
    switch(atoi(argv[0])) {
        case 1:
            list = {1,2,3,4,5};
            m = 2; n = 4;
            break;
        case 2:
            list = {1,2,3,4,5};
            m = 1; n = 5;
            break;
        case 3:
            list = {1,2,3,4,5};
            m = 1; n = 2;
            break;
        case 4:
            list = {1,2,3,4,5};
            m = 3; n = 2;
            break;
        case 5:
            list = {1};
            m = 1; n = 2;
            break;
    }
    head = makeList(list);
    printList(head);
    //head = sol.reverse92(head, m, n);
    head = sol.reverseKGroup(head, m);
    printList(head);
}
void test24(int argc, char* argv[]) {
    Solution24 sol;
    vector<int> list;
    ListNode    *head;
    switch(atoi(argv[0])) {
        case 1:
        list = {1,2,3,4};
        break;
    }
    head = makeList(list);
    printList(head);
    head = sol.swapPairs(head);
    printList(head);
}
void test11(int argc, char* argv[]) {
    Solution11 sol;
    vector<int> list;
    switch(atoi(argv[0])) {
        case 1:
            list = {1,8,6,2,5,4,8,3,7}; break;
    }
    cout << sol.maxArea(list) << endl;
}
void test12(int argc, char* argv[]) {
    Solution12 sol;
    cout << sol.intToRoman(atoi(argv[0])) << endl;
}
void test15(int argc, char* argv[]) {
    Solution15 sol;
    vector<int> nums;
    vector<vector<int>> res;
    switch(atoi(argv[0])) {
        case 1:
            nums = {-4, -1, 0, 1, 2, -1}; break;
        case 2:
            nums = {-1,0,1,0}; break;
        case 3:
            nums = {-2,0,0,2,2}; break;
        case 4:
            nums = {0,0,0,0}; break;
        case 5:
            nums = {0,0,0}; break;
        case 6:
            nums = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};break;
    };
    res = sol.threeSum(nums);
    for (auto v1: res) {
        cout << "[ "<< v1[0] << ", " << v1[1]<<", " <<v1[2] << " ]" << endl;
    }
}
void test16(int argc , char* argv[]) {
    Solution15 sol;
    vector<int> nums;
    int target;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1,1,-1,-1,3}; target = -1;
            break;
    }
    cout << sol.threeSumClosest(nums, target) << endl;
}
void test18(int argc , char* argv[]) {
    Solution18 sol;
    vector<int> nums;
    vector<vector<int>> res;
    int target;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1, 0, -1, 0, -2, 2}; target = 0;break;
        case 2:
            nums = {-1,0,1,0}; break;
        case 3:
            nums = {-2,0,0,2,2}; break;
        case 4:
            nums = {0,0,0,0}; break;
        case 5:
            nums = {0,0,0}; break;
    };
    res = sol.fourSum(nums, target);
    for (auto v1: res) {
        cout << "[ ";
        for (auto i : v1) {
            cout << i << ", ";
        }
        cout << "]" << endl;
    }
}
void test1388(int argc, char* argv[]) {
    Solution1388 sol;
    vector<int> slices;
    switch(atoi(argv[0])) {
        case 1://10
            slices = {1,2,3,4,5,6}; break;
    }
    cout << sol.maxSizeSlices(slices) << endl;
}
void test22(int argc, char* argv[]) {
    Solution22 sol;
    vector<string> res;
    res = sol.generateParenthesis(atoi(argv[0]));
    for (auto s : res) {
        cout << s << endl;
    }
}
void test26(int argc, char* argv[]) {
    Solution26 sol;
    vector<int> nums;
    int res = 0, i;
    switch(atoi(argv[0])) {
        case 1://5
            nums = {0,0,1,1,1,2,2,3,3,4}; break;
    }
    res = sol.removeDuplicates(nums);
    for (i = 0; i < res; i++) {
        cout << nums[i] << ",";
    }
    cout << endl;
}

void test1138(int argc, char* argv[]) {
    Solution1138 sol;
    string target = string(argv[0]);
    cout << sol.alphabetBoardPath(target) << endl;
}
void test410(int argc, char* argv[]) {
    Solution410 sol;
    vector<int> nums;
    int m;
    switch(atoi(argv[0])) {
        case 1:
            nums = {7,2,5,8,10}; m = 2;
            break;
        case 2:
            nums = {1,4,4}; m = 3;
            break;
        case 3:
            nums = {10,5,13,4,8,4,5,11,14,9,16,10,20,8};
            m = 8; break;
    }
    cout << sol.splitArray(nums, m) <<endl;
}
void test924(int argc, char* argv[]) {
    Solution924 sol;
    vector<vector<int>> graph;
    vector<int> nums;
    
    switch(atoi(argv[0])) {
        case 1://0-2
            graph = {{1,1,0}, {1,1,0}, {0,0,1}};
            nums = {0,1,2};
            break;
        case 2://0
            graph = {{1,0,0}, {0,1,0}, {0,0,1}};
            nums = {0,2};
            break;
        case 3://1
            graph = {{1,1,1}, {1,1,1}, {1,1,1}};
            nums = {1,2};
            break;
        case 4:
            graph = {{1,0,0,0,1,0,0,0},
                    {0,1,1,0,0,1,0,0},
                    {0,1,1,0,1,0,0,0},
                    {0,0,0,1,1,0,0,0},
                    {1,0,1,1,1,0,0,1},
                    {0,1,0,0,0,1,0,0},
                    {0,0,0,0,0,0,1,1},
                    {0,0,0,0,1,0,1,1}};
            nums = {7,2};
            break;
    }
    cout << sol.minMalwareSpread(graph, nums) <<endl;
}
void test1302 ( int argc, char* argv[]) {
    Solution1302 sol;
    TreeNode* root = NULL;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1,2,3,4,5,INT_MIN,6,7,INT_MIN,INT_MIN,
            INT_MIN,INT_MIN,8};
            root = getTree(nums, 0);
            break;
    };
    cout << sol.deepestLeavesSum(root);
}
void test787(int argc, char* argv[]){
    Solution787 sol;
    vector<vector<int>> flights;
    int n, src, dest, k;
    switch(atoi(argv[0])) {
        case 1:
            flights = {{0,1,100},{1,2,100},{0,2,500}};
            n = 3, src = 0, dest = 2, k =1;
            break;
        case 2:
            flights = {{0,1,100},{1,2,100},{0,2,500}};
            n = 3, src = 0, dest = 2, k =0;
            break;
        case 3:
            flights = {{4,1,1},{1,2,3},{0,3,2},
            {0,4,10},{3,1,1},{1,4,3}};
            n = 5; src = 2; dest = 1; k = 1;
            break;
        case 4: 
            flights = {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};
            n = 4; src = 0; dest = 3; k = 1;
            break;
        case 5:
            flights = {{0,1,5},{1,2,5},{0,3,2},{3,1,2},{1,4,1},{4,2,1}};
            n = 5; src = 0; dest = 2; k = 2;
            break;
    }
    cout << sol.findCheapestPrice(n, flights, src, dest, k) << endl;
}
void test7(int argc, char* argv[]) {
    Solution7 sol;
    cout << sol.reverse(atoi(argv[0])) << endl;
}
void test39(int argc, char* argv[]) {
    Solution39 sol;
    vector<int> nums; int target;
    vector<vector<int>> res;
    switch(atoi(argv[0])) {
        case 1:
            nums = {2,3,7}; target = 7;
            break;
        case 2:
            nums = {2,3,5}; target = 8;
            break;
    }
    res = sol.combinationSum(nums, target);
    for (auto i: res) {
        cout << "[ ";
        for (auto j: i) {
            cout << j << ", ";
        }
        cout << "]\n";
    }
}
void testChallenge3( int argc, char* argv[]) {
    SolutionChallenge3 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1: 
            nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};break;
        case 2:
            nums = {-2, -1};break;
        case 3: //19
            nums = {1, -3, 2, -5, 7, 6, -1, -4, 11, -23}; break;
        case 4:
            nums = {1,2};break;
    };
    cout << sol.maxSubArray(nums) << endl;
}
void testChallenge5( int argc, char* argv[]) {
    SolutionChallenge5 sol;
    vector<int> prices;
    switch(atoi(argv[0])) {
        case 1: 
            prices = {7,1,5,3,6,4};break;
        case 2:
            prices = {1,2,3,4,5};break;
        case 3: //19
            prices = {7,6,4,3,1}; break;
        case 4:
            prices = {6,1,3,2,4,7};break;
    };
    cout << sol.maxProfit(prices) << endl;
}
void test123( int argc, char* argv[]) {
    Solution123 sol;
    vector<int> prices;
    switch(atoi(argv[0])) {
        case 1: 
            prices = {7,1,5,3,6,4};break;
        case 2:
            prices = {1,2,3,4,5};break;
        case 3: //19
            prices = {7,6,4,3,1}; break;
        case 4:
            prices = {6,1,3,2,4,7};break;
        case 5:
            prices = {3,3,5,0,0,3,1,4};break;    
    };
    cout << sol.maxProfit(prices) << endl;
}
void testChallenge6(int argc, char* argv[]) {
    SolutionChallege6 sol;
    vector<string> strings;
    vector<vector<string>> res;
    switch(atoi(argv[0])) {
        case 1: 
        strings = {"eat", "tea", "tan", "ate", "nat", "bat"};
        break;
    }
    res = sol.groupAnagrams(strings);
    for (auto i: res) {
        cout << "[ ";
        for (auto s : i) {
            cout << s << ", ";
        }
        cout << " ]\n";
    }
}
void testChallenge7(int argc, char* argv[]) {
    SolutionChallenge7 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1,1,3,3,5,5,7,7}; break;
        case 2:
            nums = {1,3,2,3,5,0}; break;
        case 3:
            nums = {1,1,2,2}; break;
    };
    cout << sol.countElements(nums) << endl;
}
void testChallenge8(int argc, char* argv[]) {
    SolutionChallenge8 sol;
    string S, T;
    switch(atoi(argv[0])) {
        case 1: //1
            S = "ab##"; T="a#b#";
            break;
        case 2://1
            S = "a##c"; T = "#a#c"; break;
        case 3:
            S = "a#c"; T = "b"; break;
        case 4: //1
            S = "bxj##tw"; T="bxo#j##tw" ;
            break;
        case 5:
            S= "bxj##tw";T = "bxj###tw";
            break;
    }
    cout << sol.backspaceCompare(S,T) << endl;
}
void testChallenge9(int argc, char* argv[]) {
    SolutionChallenge9 sol;
    vector<int> nums;
    TreeNode *root;
    switch(atoi(argv[0])) {
        case 1://2
            nums = {3,1,INT_MIN, INT_MIN, 2};
            break;
        case 2://8
            nums = {4,-7,-3,INT_MIN,INT_MIN,-9,-3,9,-7,-4,INT_MIN,6,
            INT_MIN,-6,-6,INT_MIN,INT_MIN,0,6,5,INT_MIN,9,INT_MIN,INT_MIN,-1,-4,
            INT_MIN,INT_MIN,INT_MIN,-2};
            break;
        case 3://3
            nums = {1,2,3,4,5};break;
    }
    root = getTree(nums,0);
    cout << sol.diameterOfBinaryTree(root) << endl;
}
void testChallenge10(int argc, char* argv[]) {
    SolutionChallenge10 sol;
    vector<int> stones;
    switch(atoi(argv[0])) {
        case 1:
            stones = {2,7,4,1,8,1}; break;
        case 2:
            stones = {2,2}; break;
    }
    cout << sol.lastStoneWeight(stones) << endl;
}
void test552(int argc, char* argv[]) {
    Solution552 sol;
    cout << sol.checkRecord(atoi(argv[0])) << endl;
    cout << sol.checkRecord2(atoi(argv[0])) << endl;
}
void testChallenge11(int argc, char* argv[]){
    SolutionChallenge11 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {0,1,1,1,0};break;
        case 2: 
            nums = {0,0,1,0,0,0,1,1};break;
        case 3: //68
            nums = {0,1,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,
                    0,1,1,0,1,1,0,0,0,1,0,1,0,0,1,0,1,
                    1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,0,1,
                    0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,1,
                    1,0,0,0,0,0,0,1,0,1,0,1,1,0,0,1,1,0,
                    1,1,1,1,0,1,1,0,0,0,1,1};break;
    }
    cout << sol.findMaxLength(nums) << endl;
}
void testChallenge12(int argc, char* argv[]) {
    SolutionChallenge12 sol;
    string s;
    vector<vector<int>> shift;
    switch(atoi(argv[0])) {
        case 1:
            s = "abc";
            shift = {{0,1},{1,2}}; break;
        case 2:
            s = "abcdefg";
            shift = {{1,1},{1,1},{0,2},{1,3}};break;
    }
    cout << sol.stringShift(s,shift) << endl;
}
void testChallenge13( int argc, char* argv[]) {
    SolutionChallenge13 sol;
    string s(argv[0]);
    // "(((******))" = true
    // (*()) true
    cout << sol.checkValidString(s) << endl;
}
void test354( int argc, char* argv[]) {
    Solution354 sol;
    vector<vector<int>> envs;
    switch(atoi(argv[0])) {
        case 1:
            envs = {{5,4}, {6,4}, {6,7}, {2,3}};
            break;
        case 2:
            envs = {{5,4}, {6,4}, {6,7}, {2,3},
                    {4,8}, {3,7}, {2,6}, {1,5}};
            break;
    };
    cout << sol.maxEnvelopes(envs) << endl;
}
void testChallenge14(int argc, char* argv[]) {
    SolutionChallenge14 sol;
    vector<vector<int>> grid;
    switch(atoi(argv[0])) {
        case 1: 
        grid = {{1,3,1},
                {1,5,1},
                {4,2,1}};
        break;
    }
    cout << sol.minPathSum(grid) << endl;
}
void testChallenge15(int argc, char* argv[]) {
    SolutionChallenge15 sol;
    vector<int> nums;
    int K;
    switch(atoi(argv[0])) {
        case 1: 
        nums = {4,5,6,7,0,1,2}; K = 0;
        break;
    }
    cout << sol.search(nums,K) << endl;
}
void testChallenge16(int argc, char* argv[]) {
    SolutionChallenge16 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1: 
        nums = {8,5,1,7,10,12}; 
        break;
    }
    cout << sol.bstFromPreorder(nums) << endl;
}

void testChallenge17(int argc, char* argv[]) {
    SolutionChallenge17 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1: 
            nums = {2,3,1,1,4}; 
        break;
        case 2:
            nums = {5,9,3,2,1,0,2,3,3,1,0,0}; break;
        case 3:
        nums = {3,2,1,0,4}; break;
    }
    cout << sol.canJump(nums) << endl;
}

void testLRU(int argc, char* argv[]) {
    LRUCache lru(2);
    lru.put(1,1);
    lru.put(2,2);
    cout << lru.get(1) << endl;
    lru.put(3,3);
    cout << lru.get(2) << endl;
    lru.put(4,4);
    cout << lru.get(1) << endl;
    cout << lru.get(3) << endl;
    cout << lru.get(4) << endl;
}
void testChallenge18(int argc, char* argv[]) {
    SolutionChallenge18 sol;
    string s1 = string(argv[0]), s2 = string(argv[1]);
    cout << sol.longestCommonSubsequence(s1,s2) << endl;
}
void testChallenge19(int argc, char* argv[])
{
    vector<int> nums = {2,3,5};
    FirstUnique fu(nums);
    cout << fu.showFirstUnique() << ", ";
    fu.add(5);
    cout << fu.showFirstUnique() << ", ";
    fu.add(2);
    cout << fu.showFirstUnique() << ", ";
    fu.add(3);
    cout << fu.showFirstUnique() << ", ";
}
void testChallenge20(int argc, char* argv[]) {
    SolutionChallenge20 sol;
    vector<int> nums;
    vector<int> tree;
    TreeNode*   root = NULL;
    switch(atoi(argv[0])) {
        case 1:
            nums = {0,1,0,1};break;
        case 2:
            nums = {0,0,1};break;
        case 3:
            nums = {0,1,1}; break;
        case 4:
            nums = {0};break;
    };
    tree = {0,1,0,0,1,0,INT_MIN,INT_MIN,1,0,0};
    root = getTree(tree, 0);
    cout << sol.isValidSequence(root, nums) << endl;
}
void test993(int argc, char* argv[]) {
    Solution993 sol;
    int x,y;
    vector<int> tree;
    TreeNode*   root = NULL;
    switch(atoi(argv[0])) {
        case 1:
            tree = {1,2,4,3,8,6,5,INT_MIN,7};
            x = 5; y = 8;
            break;
        case 2:// true
            tree = {1,2,3, INT_MIN, 4,INT_MIN, 5};
            x = 5; y = 4;
            break;
        case 3:
            break;
        case 4:
            break;
    };
    
    root = getTree(tree, 0);
    cout << sol.isCousins(root, x,y) << endl;
}
void testChallenge21(int argc, char* argv[]) {
    SolutionChallenge21 sol;
    vector<vector<int>> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {{1,2}, {2,3}, {3,4}, {4,5}};
            break;
    };
    cout << sol.checkStraightLine(nums) <<endl;
}
void testChallenge22(int argc, char* argv[]) {
    SolutionChallenge22 sol;
    vector<vector<int>> nums;
    cout << sol.isPerfectSquare(atoi(argv[0])) <<endl;
}
/*  Notes: 
        intuitive approach: Sliding window. 
            but that doesn't work and fail at case 4 below
            because, we can't know till when to shrink the window. 
            */
void test862(int argc, char* argv[]) {
    Solution862 sol;
    vector<int> nums;
    int k;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1};k=1;
            break;
        case 2:
            nums = {1,2};k=4;
            break;
        case 3:
            nums = {2,-1,2}; k = 3;
            break;
        case 4:
            nums = {84,-37,32,40,95, 90}; k = 167;
            break;
        case 5:
            nums = {56,-21,56,35,-9}; k = 61;
            break;
    };
    cout << sol.shortestSubarray(nums, k) <<endl;
}

void testChallenge23(int argc, char* argv[]) {
    SolutionChallenge23 sol;
    vector<vector<int>> nums;
    int N;
    switch(atoi(argv[0])) {
        case 1:
            nums = {{1,2}};
                    N = 2;
            break;
    };
    cout << sol.findJudge(N,nums) <<endl;
}
void testChallenge24(int argc, char* argv[]) {
    SolutionChallenge24 sol;
    string str = string(argv[0]);
    int k = atoi(argv[1]);
    cout << sol.removeKdigits(str,k) <<endl;
}
void testChallengeM16(int argc, char* argv[]) {
    SolutionChallengeM16 sol;
    vector<int> nums = {1,2,3,4,5};
    ListNode    *node, *n;
    switch(atoi(argv[0])) {
        case 1:
            nums={1,2,3,4,5};
            break;
    }
    node = makeList(nums);
    n = sol.oddEvenList(node);
    printList(n);
}
void testChallengeM15(int argc, char* argv[]) {
    SolutionChallengeM15 sol;
    SolutionMisc1 sol2;
    vector<int> nums = {1,2,3,4,5};
    switch(atoi(argv[0])) {
        case 1:
            nums={5,-3,5};
            break;
        case 2:
            nums={3,-1,2,-1};
            break;
        case 3:
            nums={3,-2,2,-3};
            break;
        case 4:
            nums = {-3,-2,-1}; break;
    }
    cout << sol.maxSubarraySumCircular(nums) << endl;
}
void testChallengeM17(int argc, char* argv[]) {
    SolutionChallengeM17 sol;
    string s, p;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:
            s = "cbaebabacd";
            p = "abc";
            break;
        case 2:
            s = "abab";
            p = "ab";
            break;
        }
    res =  sol.findAnagrams(s,p);
    for ( auto e : res) {
        cout << e << ", ";
    }
    cout << endl;
}
void testG (int argc, char* argv[]) {
    int N, nT, K, tmp;
    int i, j;
    cin >> nT; // number of test cases
    vector<int> inp;
    Gsol2 sol;
    for ( j = 1; j <= nT; j++) {
        inp.clear();
        cin >> N;
    for ( i = 0; i < N; i++) {
        cin >> tmp;
        inp.push_back(tmp);
    }
    cout << "Case #" << j << ": " << sol.perfect(inp) << endl;
    }
}
void testChallengeM18(int argc, char* argv[]) {
    StockSpanner sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1: //1, 1, 1, 2, 1, 4, 6
            nums = {100, 80, 60, 70, 60, 75, 85};
            break;
    };
    for ( auto a: nums) {
        cout << sol.next(a) << ", ";
    }
    cout << endl;
}
void testChallengeMay23(int argc, char* argv[]) {
    SolutionChallengeMay23 sol;
    vector<vector<int>> A;
    vector<vector<int>> B;
    vector<vector<int>> res;
    switch(atoi(argv[0])) {
        case 1:
            A = {{0,2},{5,10},{13,23},{24,25}};
            B = {{1,5},{8,12},{15,24},{25,26}};
            break;
        case 2:
            A = {{3,10}};
            B = {{5,10}};break;
        case 3:
            A = {{8,15}};
            B = {{2,6},{8,10},{12,20}}; break;
        case 4:
            A = {{4,6},{7,8},{10,17}};
            B = {{5,10}};break;
        case 5:
            A = {{0,4},{7,8},{12,19}};
            B = {{0,10},{14,15},{18,20}};
            break;
    }
    res = sol.intervalIntersection(A,B);
    printV2(res);
}
void test973(int argc, char* argv[])
{
    Solution973 sol;
    vector<vector<int>> points;
    vector<vector<int>> res;
    int K;
    switch(atoi(argv[0])) {
        case 1:
            points = {{1,0}, {0,1}}; K = 2;
            break;
    }
    res = sol.kClosest(points, K);
    printV2(res);
}
void test207(int argc, char* argv[])
{
    Solution207 sol;
    vector<vector<int>> courses;
    int K;
    bool res = true;
    switch(atoi(argv[0])) {
        case 1:
            courses = {{1,0}, {1,2}, {0,1}}; K = 3;
            break;
        case 2:
           courses = {{2,0}, {1,0}, {3,1}, {3,2}, {1,3}}; K = 4;
            break; 
        case 3:
            courses = {{1,0}}; K = 2;
        case 4: // true
            courses = {{0,1},{0,2},{1,2}}; K = 3;
            break;
    }
    res = sol.canFinish(K, courses);
    cout << res << endl;
}
void testChallengeJune26(int argc, char* argv[]) {
    SolutionChallengeJune26 sol;
    vector<int> tree;
    TreeNode    *root;
    switch(atoi(argv[0])) {
        case 1:
            tree = {1,2,3};
            break;
        case 2:
            tree = {4,9,0,5,1};
            break;
    }

    root = getTree(tree, 0);
    cout << sol.sumNumbers(root) << endl;
}
void testChallengeJuly6(int argc, char* argv[]) {
    SolutionChallengeJuly6 sol;
    vector<int> num;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:
            num = {1,2,3};
            break;
        case 2:
            num = {9};
            break;            
        case 3:
            num = {1,9};
            break;
    }
    res = sol.plusOne(num);
    printV(res);
}
void test957(int argc, char* argv[]) {
    Solution957 sol;
    vector<int> num;
    vector<int> res;
    int N;
    switch(atoi(argv[0])) {
        case 1:
            num = {0,1,0,1,1,0,0,1};
            N = 7;
            break;
        case 2:
            num = {1,0,0,1,0,0,1,0};
            N = 1000000000;
            break;            
        }
    res = sol.prisonAfterNDays(num,N);
    printV(res);
}

void testChallengeJuly7(int argc, char* argv[]) {
    SolutionChallengeJuly7 sol;
    vector<vector<int>> grid;
    switch(atoi(argv[0])) {
        case 1:
            grid = {
                            {0,1,0,0},
                            {1,1,1,0},
                            {0,1,0,0},
                            {1,1,0,0},
                            };
            break;
        case 2:
            grid = {
                            {0},
                            {1}
                            };
            break;
        case 3:
            grid = {{1}};
            break;
    }
    cout << sol.islandPerimeter(grid) << endl;
}

void testChallengeJuly15(int argc, char* argv[]) {
    SolutionChallengeJuly15 sol;
    string s;
    switch(atoi(argv[0])) {
        case 1:
            s="the sky is blue";
            break;
        case 2:
        s="  the sky is   blue  ";
            break;
    }
    cout << sol.reverseWords(s) << endl;
}
void testChallengeJuly9 ( int argc, char* argv[]) {
    SolutionChallengeJuly9 sol;
    TreeNode* root = NULL;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1,2,3,4,5,INT_MIN,6};
            break;
    };
    root = getTree(nums, 0);
    cout << sol.widthOfBinaryTree(root) << endl;
}
void test210 ( int argc, char* argv[]) {
    Solution210 sol;
    vector<vector<int>> nums;
    vector<int> res;
    int C = 0;
    switch(atoi(argv[0])) {
        case 1:
            nums = {{1,0}, {2,0}, {3,1}, {3,2}};
            C = 4;
            break;
    };

    res = sol.findOrder(C, nums);
    printV(res);
}
void test67 ( int argc, char* argv[]) {
    Solution67 sol;
    string a, b;
    string res;
    switch(atoi(argv[0])) {
        case 1:
            a = "11"; b = "1";
            break;
        case 2:
            a = "0"; b = "0";
            break;
        case 3:
            a = "1010"; b = "1011";
            break;
    };

    res = sol.addBinary(a,b);
    cout << res << endl;
}
void test153 ( int argc, char* argv[]) {
    Solution153 sol;
    //Solution153 sol;
    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {3,4,5,1,2};
            break;
        case 2:
            nums = {4,5,6,0,1,2};
            break;
        case 3:
            nums = {2,1}; break;
        case 4:
            nums = {5,1,2,3,4}; break;
        case 5:
            nums = {2,2,2,0,1}; break;
        case 6:
            nums = {3,1,3}; break;
    };

    cout <<  sol.findMin(nums) << endl;
}
void test621 ( int argc, char* argv[]) {
    Solution621 sol;
    vector<char> nums;
    int n;
    switch(atoi(argv[0])) {
        case 1:
            nums = {'A','A','A','B','B','B'};
            n = 2;
            break;
        case 2:
            nums = {'A','A','A','B','B','B'};
            n = 0;break;
        case 3:
            nums = {'A','A','A','A','A','A','B','C','D','E','F','G'};
            n = 2; break;
    };

    cout <<  sol.leastInterval(nums,n) << endl;
}
void test803 ( int argc, char* argv[]) {
    Solution803 sol;
    vector<vector<int>> bricks;
    vector<vector<int>> hits;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:
            bricks = {{1,0,0,0}, {1,1,1,0}};
            hits = {{1,0}};
            break;
        case 2:
            bricks = {{1,0,0,0}, {1,1,0,0}};
            hits = {{1,1},{0,0}};
            break;
        case 3:
            bricks = {{1},{1},{1},{1},{1}};
            hits = {{3,0},{4,0},{1,0},{2,0},{0,0}};
            break;
        case 4:
            bricks = {{1,0,1},{1,1,1}};
            hits = {{0,0},{0,2},{1,1}};
            break;
    };

    res =  sol.hitBricks(bricks,hits);
    printV(res);
}

void test1103 ( int argc, char* argv[]) {
    Solution1103 sol;
    int candies = atoi(argv[0]); 
    int ppl = atoi(argv[1]);
    vector<int> res;

    res =  sol.distributeCandies(candies, ppl);
    printV(res);
}
void test967 ( int argc, char* argv[]) {
    Solution967 sol;
    int N = atoi(argv[0]); 
    int K = atoi(argv[1]);
    vector<int> res;

    res =  sol.numsSameConsecDiff(N, K);
    printV(res);
}

void test454 ( int argc, char* argv[]) {
    Solution454 sol;
    vector<int> A;
    vector<int> B;
    vector<int> C;
    vector<int> D;
    int res;
    switch(atoi(argv[0])) {
        case 1:
            A = {1,2}; B = {-2,-1};
            C = {-1,2}; D = {0,2};
            break;
        case 2:
            A = {-1,-1}; B = {-1,1};
            C = {-1,1}; D = {1,-1};
            break;
        case 3:
            A = {1,2}; B = {-2,-1};
            C = {-1,2}; D = {0,2};
            break;
        case 4:
            A = {1,2}; B = {-2,-1};
            C = {-1,2}; D = {0,2};
            break;
    };

    res =  sol.fourSumCount(A,B,C,D);
    cout << res << endl;
}
void test206(int argc, char* argv[]) {
    Solution206 sol;
    vector<int> list;
    ListNode    *head = NULL;
    switch(atoi(argv[0])) {
        case 1:
            list = {1,2,3,4,5};
            break;
        case 2:
            list = {1,2,3,4,5};
            break;
        case 3:
            list = {1,2,3,4,5};
            break;
        case 4:
            list = {1,2,3,4,5};
            break;
        case 5:
            list = {1};
            break;
    }
    head = makeList(list);
    printList(head);
    head = sol.reverseList(head);
    printList(head);
}
void test215(int argc, char* argv[]) {
    Solution215 sol;
    vector<int> list;
    int k; 
    switch(atoi(argv[0])) {
        case 1: // 5
            list = {3,2,1,5,6,4}; k = 2;
            break;
        case 2: // 4
            list = {3,2,3,1,2,4,5,5,6}; k = 4;
            break;
    }
    cout <<  sol.findKthLargest(list, 4) << endl;
}

void test1406(int argc, char* argv[]) {
    Solution1406 sol;
    vector<int> list;
    switch(atoi(argv[0])) {
        case 1:
            list = {1,2,3,7};
            break;
        case 2:
            list = {1,2,3,-9};
            break;
        case 3:
            list = {1,2,3,6};
            break;
    }
    cout << sol.stoneGameIII(list) << endl;
}
void test115(int argc, char* argv[]) {
    Solution115 sol;
    string s, t;
    switch(atoi(argv[0])) {
        case 1:
            s = "rabbbit"; t = "rabbit";
            break;
        case 2:
            s = "babgbag"; t = "bag";
            break;
    }
    cout << sol.numDistinct(s,t) << endl;
}

void test310(int argc, char* argv[]) {
    Solution310 sol;
    vector<vector<int>> edges;
    vector<int> res;
    int n;
    switch(atoi(argv[0])) {
        case 1: //1
            n = 4;
            edges = {{1,0},{1,2},{1,3}};break;
        case 2:
            n = 6;
            edges = {{0,1},{0,2},{0,3},{3,4},{4,5}};
            break;
    }
    res = sol.findMinHeightTrees(n, edges);
    printV(res);
}

void test630(int argc, char* argv[]) {
    Solution630 sol;
    vector<vector<int>> courses;
    switch(atoi(argv[0])) {
        case 1: //1
            courses = {{100, 200},{200, 1300},{1000,1250}, {2000,3200}};
            break;
        case 2:
            courses = {{1, 2},{2, 3}};
            break;
        case 3:
            courses = {{5,5},{4,6},{2,6}};break;
    }
    int res = sol.scheduleCourse(courses);
    cout << res << endl;
}

void test870(int argc, char* argv[]) {
    Solution870 sol;
    vector<int> A, B; 
    
    switch(atoi(argv[0])) {
        case 1:
            A = {2,7,11,15};
            B = {1,10,4,11};
            break;
        case 2: //1
            A = {12,24,8,32};
            B = {13,25,32,11};
            break;
        case 3:
            A = {2,0,4,1,2};
            B = {1,3,0,0,2};
            break;
    }
    vector<int> res = sol.advantageCount(A,B);
    printV(res);
}
void test1433(int argc, char* argv[]) {
    Solution1433 sol;
    cout << sol.checkIfCanBreak(string(argv[0]),string(argv[1])) << endl;
   
}

void test1497(int argc, char* argv[]) {
    Solution1497 sol;
    vector<int> A; 
    int k;
    switch(atoi(argv[0])) {
        case 1:// true
            A = {1,2,3,4,5,10,6,7,8,9};
            k = 5;            break;
        case 2: //true
            A = {-1,1,-2,2,-3,3,-4,4};
            k = 3;break;
        case 3:// false;
            A = {1,2,3,4,5,6};
            k = 10;break;
        case 4:// false;
            A = {-1,-1,-1,-1,2,2,-2,-2};
            k = 3;break;
    }
    cout << sol.canArrange(A,k) << endl;
}
void test1590(int argc, char* argv[]) {
    Solution1590 sol;
    vector<int> A; 
    int k;
    switch(atoi(argv[0])) {
        case 1:// 1
            A = {3,1,4,2};
            k = 6;            break;
        case 2: //2
            A = {6,3,5,2};
            k = 9;break;
        case 3:// 0;
            A = {1,2,3};
            k = 3;break;
        case 4:// -1;
            A = {1,2,3};
            k = 7;break;
        case 5://3
            A = {26,19,11,14,18,4,7,1,30,23,19,8,10,6,26,3};
            k = 26;
            break;
    }
    cout << sol.minSubarray(A,k) << endl;
}

void test785(int argc, char* argv[]) {
    Solution785 sol;
    vector<vector<int>> A; 
    switch(atoi(argv[0])) {
        case 1:// 1
            A = {{1,3}, {0,2}, {1,3}, {0,2}};
            break;
    }
    cout << sol.isBipartite(A) << endl;
}

void test978(int argc, char* argv[]) {
    Solution978 sol;
    vector<int> A; 
    switch(atoi(argv[0])) {
        case 1:// 5
            A = {9,4,2,10,7,8,8,1,9};
            break;
    }
    cout << sol.maxTurbulenceSize(A) << endl;
}

void test213(int argc, char* argv[]) {
    Solution213 sol;
    vector<int> A; 
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {2,3,2};break;
        case 2:// 4
            A = {1,2,3,1};break;
    }
    cout << sol.rob(A) << endl;
}
void testt(int argc, char* argv[]) {
    Solutiont sol;
    int k;
    string s; //aaabc, aba, bbaaacbd
    if ( argc >= 2) {
        s = string(argv[0]);
        k = atoi(argv[1]);
        cout << sol.longestSubstring(s,k) << endl;
    }
}
void test416(int argc, char* argv[]) {
    Solution416 sol;
    vector<int> A; 
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {1,5,11,5}; break;
        case 2:// 4
            A = {1,2,3,5};break;
    }
    cout << sol.canPartition(A) << endl;
}
void test239(int argc, char* argv[]) {
    Solution239 sol;
    vector<int> A; 
    int k;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {1,3,-1,-3,5,3,6,7}; k = 3;break;
        case 2:// 4
            A = {1,-1}; k = 1;break;
        case 3:
            A = {1}; k = 1;break;
    }
    res =  sol.maxSlidingWindow(A, k);
    printV(res);
}

void test644(int argc, char* argv[]) {
    Solution644 sol;
    vector<int> A; 
    int k;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {1,12,-5,-6,50,3}; k = 4;break;
        case 2:// 4
            A = {5}; k = 1;break;
        case 3:
            A = {1}; k = 1;break;
    }
    cout <<  sol.findMaxAverage(A, k) << endl;
    
}

void test605(int argc, char* argv[]) {
    Solution605 sol;
    vector<int> A; 
    int n;
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {1,0,0,0,1}; n = 1;break;
        case 2:// 4
            A = {1,0,0,0,1}; n = 2;break;
        case 3:
            A = {0,1,0}; n = 1;break;
    }
    cout <<  sol.canPlaceFlowers(A, n) << endl;
    
}

void test163(int argc, char* argv[]) {
    Solution163 sol;
    vector<int> A; 
    int lower, upper;
    vector<string> res;
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {0,1,3,50,75}; lower = 0; upper = 99;break;
        case 2:// 4
            A = {}; lower = 1; upper = 1;break;
        case 3:
            A = {-1}; lower = -1; upper = -1;break;
        case 4:
            A = {-1}; lower = -2; upper = -1;break;
    }
    res =  sol.findMissingRanges(A, lower, upper);
    for (auto s: res) {
        cout << s << endl;
    }
    
}

void test1010(int argc, char* argv[]) {
    Solution1010 sol;
    vector<int> A; 
    int res;
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {30,20,150,100,40}; break;
        case 2:// 4
            A = {60,60,60}; break;
        case 3:
            A = {418,204,77,278,239,457,284,263,372,279,476,416,360,18}; break;
        case 4:
            A = {30,20,150,100,40}; break;

    }
    res =  sol.numPairsDivisibleBy60(A);
    cout << res << endl;
    
}
void test116 ( int argc, char* argv[]) {
    Solution116 sol;
    TreeNode* root = NULL;
    TreeNode* res = NULL;

    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1:
            nums = {1,2,3,4,5,INT_MIN,6};
            break;
        case 2:
            nums = {1,2,3,4,5,6,7};
            break;
    };
    root = getTree(nums, 0);
    res = sol.connect(root);
    printTreeLevel(res);
}
void test563 ( int argc, char* argv[]) {
    Solution563 sol;
    TreeNode* root = NULL;
    int res;

    vector<int> nums;
    switch(atoi(argv[0])) {
        case 1://15
            nums = {4,2,9,3,5,INT_MIN,7};
            break;
        case 2:
            nums = {1,2,3,4,5,6,7};
            break;
    };
    root = getTree(nums, 0);
    res = sol.findTilt(root);
    cout << res << endl;
}
void test80(int argc, char* argv[]) {
    Solution80 sol;
    vector<int> A; 
    int res;
    switch(atoi(argv[0])) {
        case 1:// 3
            A = {1,1,1,2,2,3}; break;
        case 2:// 4
            A = {0,0,1,1,1,1,2,3,3}; break;
        case 3:
            A = {418,204,77,278,239,457,284,263,372,279,476,416,360,18}; break;
        case 4:
            A = {30,20,150,100,40}; break;

    }
    res =  sol.removeDuplicates(A);
    cout << res << endl;
    printV(A);
}
void test334(int argc, char* argv[]) {
    Solution334 sol;
    vector<int> A; 
    int res;
    switch(atoi(argv[0])) {
        case 1:// false
            A = {5,4,3,2,1}; break;
        case 2:// true
            A = {2,1,5,0,4,6}; break;
        case 3: // true
            A = {5,1,5,5,2,5,4}; break;
        case 4: // true
            A = {0,10,0,20}; break;
        case 5: // true
            A = {0,10,1,2,3}; break;
    }
    res =  sol.increasingTriplet(A);
    cout << res << endl;
    
}
void test912(int argc, char* argv[]) {
    Solution912 sol;
    vector<int> A; 
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:// false
            A = {5,4,3,2,1}; break;
        case 2:// true
            A = {2,1,5,0,4,6}; break;
        case 3: // true
            A = {5,1,5,5,2,5,4}; break;
        case 4: // true
            A = {0,10,0,20}; break;
        case 5: // true
            A = {0,10,1,2,3}; break;
        case 6: 
            A = {5,1,1,2,0,0}; break;
    }
    res =  sol.sortArray(A);
    printV(res);   
}

void test240(int argc, char* argv[]) {
    Solution240 sol;
    vector<vector<int>> A; 
    int target = atoi(argv[1]);
    bool res;
    switch(atoi(argv[0])) {
        case 1:// false
            A = {
                {1,4,7,11,15},
                {2,5,8,12,19},
                {3,6,9,16,22},
                {10,13,14,17,24},
                {18,21,23,26,30}}; 
             break;
        case 2:// true
            A = {{1,2,3,4,5,},
                {6,7,8,9,10},
                {11,12,13,14,15},
                {16,17,18,19,20},
                {21,22,23,24,25}}; 
        case 3: // true
            A = {
                {5,1,5,5,2,5,4}}; break;
        case 4: // true
            A = {
                    {0,10,0,20}
                }; break;
        case 5: // true
            A = {
                    {0,10,1,2,3}
                }; break;
    }
    res =  sol.searchMatrix(A, target);
    cout << res << endl;
    
}

void test37(int argc, char* argv[]) {
    Solution37 sol;
    vector<vector<char>> board; 
    switch(atoi(argv[0])) {
        case 1:// false
            board = {
                {'5','3','.','.','7','.','.','.','.'},
                {'6','.','.','1','9','5','.','.','.'},
                {'.','9','8','.','.','.','.','6','.'},
                {'8','.','.','.','6','.','.','.','3'},
                {'4','.','.','8','.','3','.','.','1'},
                {'7','.','.','.','2','.','.','.','6'},
                {'.','6','.','.','.','.','2','8','.'},
                {'.','.','.','4','1','9','.','.','5'},
                {'.','.','.','.','8','.','.','7','9'}}; 
             break;
    }
    sol.solveSudoku(board);
    cout << "solved" << endl;
}
void test77(int argc, char* argv[]) {
    Solution77 sol;
    vector<vector<int>> res; 
    res = sol.combine(atoi(argv[0]), atoi(argv[1]));
    printV2(res);
}

void test100 ( int argc, char* argv[]) {
    Solution100 sol;
    TreeNode* root1 = NULL;
    TreeNode* root2 = NULL;
    int res;

    vector<int> nums1;
    vector<int> nums2;
    switch(atoi(argv[0])) {
        case 1://15
            nums1 = {10,5,15};
            nums2 = {10,5, INT_MIN, 10, 15};
            break;
        case 2:
            nums1 = {1,2,3,4,5,6,7};
            break;
    };
    root1 = getTree(nums1, 0);
    root2 = getTree(nums2, 0);

    res = sol.isSameTree(root1, root2);
    cout << res << endl;
}
void testSet(int argc, char* argv[]) {
    set<pair<int, int>> pset;
    pset.insert({1,2});
    cout << "set.count(present) " << pset.count({1,2}) << endl;
    cout << "set.count(!present) " << pset.count({2,2}) << endl;
    cout << "set.find(present) " << (pset.end() != pset.find({1,2}));
    cout << "set.find(!present) " << (pset.end() != pset.find({2,2}));
}

void test31(int argc, char* argv[]) {
    Solution31 sol;
    vector<int> A; 
    vector<int> res;
    switch(atoi(argv[0])) {
        case 1:// false
            A = {1,2,3}; break;
        case 2:// true
            A = {1,3,2 }; break;
        case 3: // true
            A = {3,2,1}; break;
        case 4: // true
            A = {1,2}; break;
        case 5: // true
            A = {0,10,1,2,3}; break;
        case 6: 
            A = {5,1,1,2,0,0}; break;
    }
    printV(A);  
    sol.nextPermutation(A);
    printV(A);   
}
void practise_cprac(int tc, int argc, char * argv[])
{
    vector<int> nums;
    int i;
    switch(tc) {
        case -1:
            testSet(argc, argv);
            break;
        case 3001: 
            pthread_t   t1, t2, t3; 
            pthread_cond_init(&cond1, NULL);
            pthread_cond_init(&cond2, NULL);
            pthread_cond_init(&cond3, NULL);
            pthread_mutex_init(&m, NULL);
            pthread_create(&t1, NULL, first, (void*) &t1);
            pthread_create(&t2, NULL, second, (void*) NULL );
            pthread_create(&t3, NULL, third, (void*) NULL );

            printf(" Main Thread\n");
            pthread_mutex_lock(&m);
            pthread_cond_signal(&cond1);
            pthread_mutex_unlock(&m);

            pthread_exit(NULL);
            break;
        case 3004:
            testMedianFinder(argc, argv);
            break;    
        case 3003:
            nums.push_back(1);
            nums.push_back(2);
            nums.push_back(3);
            cout << ijump(nums);
            break;
        case 0:
            testMedianSliding();
            break;
        case 1:
            test1(argc, argv);
            break;
        case 3:
            test03(argc, argv);
            break;
        case 4:
            testLc4(argc, argv);
            break;    
        case 5:
            test5(argc, argv);
            break;
        case 6:
            test6(argc, argv);
            break;
        case 7:
            test7(argc, argv);
            break;
        case 10:
            test10(argc, argv);
            break;
        case 11:
            test11(argc, argv);
            break; 
        case 12:
            test12(argc, argv);
            break;    
        case 15:
            test15(argc, argv);
            break;    
        case 16:
            test16(argc, argv);
            break; 
        case 18:
            test18(argc, argv);
            break; 
        case 22:
            test22(argc, argv);
            break; 
        case 23:
            test23(argc, argv);
            break;
        case 24:
            test24(argc, argv);
            break;
        case 25:
            test25(argc, argv);
            break;
        case 26:
            test26(argc, argv);
            break;
        case 31:
            test31(argc, argv);
            break;
        case 37:
            test37(argc, argv);
            break;  
        case 39:
            test39(argc, argv);
            break;
        case 40:
            testtmp(argc, argv);
            break;
        case 41:
            testLc41(argc, argv);
            break;
        case 56:
            test56(argc, argv);
            break;
        case 57:
            test57(argc, argv);
            break;
        case 67:
            test67(argc, argv);
            break;
        case 72:
            test72(argc, argv);
            break;
        case 77:
            test77(argc, argv);
            break;
        case 79:
            test79(argc, argv);
            break;
        case 80:
            test80(argc, argv);
            break;
        case 100:
            test100(argc, argv);
            break;       
        case 115:
            test115(argc, argv);
            break;
        case 116:
            test116(argc, argv);
            break;
        case 123:
            test123(argc, argv);
            break;
        case 128:
            test128(argc, argv);
            break;
        case 129:
            testChallengeJune26(argc, argv);
            break;
        case 153:
            test153(argc, argv);
            break;
        case 163:
            test163(argc, argv);
            break;
        case 188:
            test188(argc, argv);
            break;
        case 200:
            test200(argc, argv);
            break;
        case 206:
            test206(argc, argv);
            break;
        case 207:
            test207(argc, argv);
            break;
        case 208:
            test208(argc, argv);
            break;
        case 210:
            test210(argc, argv);
            break;
        case 212:
            test212(argc, argv);
            break;
        case 213:
            test213(argc, argv);
            break;
        case 215:
            test215(argc, argv);
            break;
        case 218:
            test218(argc, argv);
            break;
        case 239:
            test239(argc, argv);
            break;
        case 240:
            test240(argc, argv);
            break;
        case 264:
            test264(argc, argv);
            break;
        case 273:
            test273(argc, argv);
            break;
        case 310:
            test310(argc, argv);
            break;  
        case 315:
            test315(argc, argv);
            break;
        case 334:
            test334(argc, argv);
            break;    
        case 340:
            test340(argc, argv);
            break;
        case 354:
            test354(argc, argv);
            break;
        case 403:
            test403(argc, argv);
            break;
        case 410:
            test410(argc, argv);
            break;
        case 416:
            test416(argc, argv);
            break;
        case 424: 
            test424(argc, argv);
            break;  
        case 454: 
            test454(argc, argv);
            break;      
        case 552: 
            test552(argc, argv);
            break;  
        case 560: 
            test560(argc, argv);
            break;   
        case 563: 
            test563(argc, argv);
            break;   
        case 605: 
            test621(argc, argv);
            break;   
        case 621: 
            test621(argc, argv);
            break;   
        case 630: 
            test630(argc, argv);
            break;     
        case 632: 
            test632(argc, argv);
            break; 
        case 662: 
            testChallengeJuly9(argc, argv);
            break; 
        case 685: 
            test685(argc, argv);
            break;   
        case 772:
            test772(argc, argv);
            break;
        case 774:
            test774(argc, argv);
            break;
        case 787:
            test787(argc, argv);
            break;    
        case 785:
            test785(argc, argv);
            break;    
        case 801:
            test801(argc, argv);
            break;
        case 803:
            test803(argc, argv);
            break;    
        case 815:
            test815(argc,argv);
            break;
        case 818:
            test818(argc, argv);
            break;
        case 839:
            test839(argc, argv);
            break;
        case 846:
            test846(argc, argv);
            break;
        case 862:
            test862(argc, argv);
            break;
        case 870:
            test870(argc, argv);
            break;
        case 895:
            test895(argc,argv);
            break;
        case 924:
            test924(argc,argv);
            break;
        case 912:
            test912(argc,argv);
            break;
        case 957:
            test957(argc,argv);
            break;
        case 967:
            test967(argc,argv);
            break;
        case 973:
            test973(argc,argv);
            break;
        case 978:
            test978(argc,argv);
            break;    
        case 992:
            testLc992(argc, argv);
            break;
        case 993:
            test993(argc, argv);
            break;    
        case 1011:
            test1011(argc, argv);
            break;
        case 1010:
            test1010(argc, argv);
            break;
        case 1036:
            test1036(argc, argv);
            break;
        case 1074:
            test1074(argc, argv);
            break;
        case 1103:
            test1103(argc, argv);
            break;
        case 1138:
            test1138(argc, argv);
            break;
        case 1178:
            test1178(argc, argv);
            break;
        case 1234:
            test1234(argc, argv);
            break;
        case 1280:
            test1280(argc, argv);
            break;
        case 1302:
            test1302(argc, argv);
            break;
        case 1326:
            test1326(argc, argv);
            break;
        case 1349:
            test1349(argc, argv);
            break;
        case 1353:
            test1353(argc, argv);
            break;
        case 1356:
            test1356(argc, argv);
            break;    
        case 1358:
            test1358(argc, argv);
            break;
        case 1361:
            test1361(argc, argv);
            break;    
        case 1362:
            test1362(argc, argv);
            break;
        case 1363:
            test1363(argc, argv);
            break;
        case 1376:
            test1376(argc, argv);
            break;
        case 1377:
            test1377(argc, argv);
            break;
        case 1388:
            test1388(argc, argv);
            break; 
        case 1406:
            test1406(argc, argv);
            break;       
        case 1433:
            test1433(argc, argv);
            break;   
        case 1497:
            test1497(argc, argv);
            break;              
        case 1590:
            test1590(argc, argv);
            break;              
        case 2020:
            //testKadane(argc, argv);
            //testChallenge3(argc, argv);
            //testChallenge5(argc, argv);
            //testLRU(argc, argv);
            //testChallengeMay23(argc, argv);
            //testChallengeJune26(argc, argv);
            //testChallengeJuly7(argc, argv);
            testChallengeJuly15(argc, argv);
            break;
        case 4001:
            test4001(argc, argv);
            break;
        case 5000:
            testG(argc, argv);
            break;
        default: 
            cout << " CPP \n";
            break;
    };
}
