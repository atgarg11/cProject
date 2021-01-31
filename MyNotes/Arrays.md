__Squares of Sorted Array__:
* Think of it as merge Sort of two sorted arrays. Pick the bigger element from each array.
```
vector<int> sortedSquares(vector<int>& nums) {
        int i = 0, j = nums.size()-1;
        int k=j;
        vector<int> res(j+1);
        while ( i <= j) {
            if ( abs(nums[i]) > abs(nums[j])) {
                res[k--] = nums[i]*nums[i];
                i++;
            } else {
                res[k--] = nums[j]*nums[j];
                j--;
            }
        }
        return res;
    }
```
