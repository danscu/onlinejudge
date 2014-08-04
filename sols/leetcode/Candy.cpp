#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

class Solution {
public:
    int candy(vector<int> &ratings) {
        multimap<int,int> s;
        vector<int> c(ratings.size(), 0);

        for (int i = 0; i < ratings.size(); i++)
            s.insert(pair<int,int>(ratings[i],i));
            
        for (multimap<int,int>::iterator it = s.begin(); it != s.end(); ++it) {
            int pos = it->second;
            int candies = 1;
            if (pos > 0 && ratings[pos] > ratings[pos-1])
                candies = max(candies, c[pos-1] + 1);
            if (pos < ratings.size() -1 && ratings[pos] > ratings[pos+1])
                candies = max(candies, c[pos+1] + 1);
            c[pos] = candies;
        }
        
        int sum = 0;
        for (int i = 0; i < c.size(); i++)
            sum += c[i];
        return sum;
    }
};

int main() {
  Solution sn;
  vector<int> v;
  int arr[] = {2,2};
  v.insert(v.begin(), arr, arr+2);
  printf("%d\n", sn.candy(v));
  return 0;
}
