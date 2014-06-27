class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        int lo,hi,m;
        lo=0;hi=n-1;
        if (target>A[hi])
            return hi+1;
        while(lo<hi){
            m=(lo+hi)/2;
            if(target <= A[m])
                hi=m;
            else
                lo=m+1;
        }
        return lo;
    }
};
