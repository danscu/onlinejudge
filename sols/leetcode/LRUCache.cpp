#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>

using namespace std;

#define DBG 1

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

class LRUCache{
private:
    typedef map<int,int> Cache;
    typedef list<Cache::iterator> LRUList;

    int cap;

    LRUList lruList;
    Cache cache;
    map<int,LRUList::iterator> hash;

public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    void touch(Cache::iterator it) {
        // move to front
        LRUList::iterator old = hash[it->first];
        lruList.erase(old);
        lruList.push_front(it);

        hash[it->first] = lruList.begin();
    }

    int get(int key) {
        // just gets from cache
        Cache::iterator it = cache.find(key);
        if (it == cache.end())
            return -1;
        else {
            touch(it);
            return it->second;
        }
    }

    void set(int key, int value) {
        // if key exists
        Cache::iterator it = cache.find(key);
        if (it != cache.end()) {
            touch(it);
            it->second = value;
            return;
        }

        // if full
        if (cache.size() == cap) {
            // eject LRU
            Cache::iterator it = lruList.back(); lruList.pop_back();
            cache.erase(it);
        }

        // insert
        cache[key] = value;
        lruList.push_front(cache.find(key));
        hash[key] = lruList.begin();
    }
};


int main(){
	LRUCache lc(1);
	lc.set(2,1);
	cout << lc.get(2);
	return 0;
}
