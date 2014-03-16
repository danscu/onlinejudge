#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSumBinSearch(vector<int> &numbers, int target) {
        int i,j;
        vector<int> res;

        for (i=0;i<numbers.size()-1;i++) {
            int rem = target - numbers[i];

            std::pair<std::vector<int>::iterator,std::vector<int>::iterator> bounds;
            bounds = equal_range(numbers.begin() + i + 1, numbers.end(), rem);

            if (bounds.second - bounds.first) {
                    res.push_back(i+1);
                    res.push_back(bounds.first - numbers.begin() + 1);
                    return res;
            }
        }
        return res;
    }

    vector<int> twoSum(vector<int> &numbers, int target) {
            int i,j;
            map<int,int> m;
            vector<int> res(2,0);

            for (i=0;i<numbers.size();i++) {
                m[numbers[i]] = i+1;
            }

            for (i=0;i<numbers.size()-1;i++) {
                int rem = target-numbers[i];
                map<int,int>::iterator it = m.find(rem);
                if (it!=m.end() && it->second != i+1) {
                    res[0]=(i+1);
                    res[1]=(it->second);
                    break;
                }
            }
            return res;
        }
};

int main(){
	vector<int> nn;
	nn.push_back(3);
	nn.push_back(2);
	nn.push_back(4);
	Solution sn;
	vector<int> r = sn.twoSum(nn, 6);
	cout << r[0] << " " << r[1] << endl;
}
