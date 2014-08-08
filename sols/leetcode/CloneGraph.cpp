#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
private:
    map<int,UndirectedGraphNode *> newMap;
public:
    UndirectedGraphNode *clone(UndirectedGraphNode *node) {
        if (!node) return node;
        map<int,UndirectedGraphNode *>::iterator it = newMap.find(node->label);
        if (it != newMap.end())
            return it->second;

        UndirectedGraphNode *el = new UndirectedGraphNode(node->label);
        newMap.insert(pair<int,UndirectedGraphNode*>(node->label, el));

        for (vector<UndirectedGraphNode *>::iterator itChild = node->neighbors.begin();
            itChild != node->neighbors.end(); ++itChild)
                el->neighbors.push_back(clone(*itChild));
        return el;
    }

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        newMap.clear();
        return clone(node);
    }
};

int main() {
	Solution sn;
	UndirectedGraphNode *g = new UndirectedGraphNode(-1);

	sn.cloneGraph(g);

	return 0;
}
