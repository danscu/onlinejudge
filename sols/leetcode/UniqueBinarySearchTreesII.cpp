#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	typedef vector<TreeNode *> VT;

	// Generate all subtrees from l to r (inclusive)
	VT genSubTrees(int l, int r) {
		VT res;

		// base
		if (l > r) {
			res.push_back(NULL);
			return res;
		}

		for(int i=l; i<=r; i++) {
			VT lset = genSubTrees(l, i-1);
			VT rset = genSubTrees(i+1, r);

			// combine
			for (VT::iterator il = lset.begin(); il != lset.end(); ++il)
				for (VT::iterator ir = rset.begin(); ir != rset.end(); ++ir) {
					TreeNode *u = new TreeNode(i);
					u->left = *il;
					u->right = *ir;
					res.push_back(u);
				}
		}

		return res;
	}

    vector<TreeNode *> generateTrees(int n) {
        return genSubTrees(1,n);
    }
};

int main() {
	Solution sn;
	vector<TreeNode *> res = sn.generateTrees(4);
	cout << "Total=" << res.size() << endl;
}
