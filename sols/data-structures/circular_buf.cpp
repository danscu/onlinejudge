#include <iostream>

using namespace std;

#define size 20

class WorkQueue {
public:
    struct WorkItem {
        int uid;
        bool block;
        WorkItem(int uid = -1, bool block = false)
        : uid(uid),
          block(block)
        {
        }
    };

private:
    WorkItem mQueue[size + 1]; // add an empty element to denote full queue
    int mHead; // mTail == mHead --> empty
    int mTail; // (mTail + 1) mod (size + 1) == mHead --> full
    int mPending; // number of pending requests

    int findUid(int uid) const {
        int cur = mHead;
        while (cur != mTail) {
            if (mQueue[cur].uid == uid)
                return cur;
            if (++cur == size + 1)
                cur = 0;
        }
        return -1; // not found
    }

    bool emptyLocked() const {
        return mHead == mTail;
    }

    // Returns false if queue is full
    bool addLocked(int uid, bool block) {
        int uidIdx = findUid(uid);
        if (uidIdx >= 0)
            mQueue[uidIdx].block = block;
        else {
            mQueue[mTail] = WorkItem(uid, block);
            int nextTail = mTail;
            if (++nextTail == size + 1)
                nextTail = 0;
            if (nextTail == mHead)
                return false; // full
            mTail = nextTail;
            mPending++;
        }
        return true;
    }

public:
    WorkQueue() :
      mHead(0),
      mTail(0),
      mPending(0)
    {
    }

    // Reinitializes the work queue after terminating all waiting threads
    void reinit() {
        mHead = mTail = mPending = 0;
    }

    bool add(int uid, bool block) {
        bool ret = addLocked(uid, block);
        return ret;
    }

    // Returns {uid: -1} if queue is empty
    WorkItem getNext() {
        if (mHead == mTail)
            return WorkItem(-1, false); // empty
        WorkItem &ret = mQueue[mHead];
        if (++mHead == size + 1)
            mHead = 0;
        return ret;
    }

    int dump() const {
        int cur = mHead;
        while (cur != mTail) {
            cout << mQueue[cur].uid << " " << mQueue[cur].block << endl;
            if (++cur == size + 1)
                cur = 0;
        }
        cout << endl;
    }
};

int main() {
    int i, j;
    WorkQueue wq;

    for (i = 0; i < 9; i++) {
        cout << "Round " << i + 1 << endl;
        for (j = 0; j < 10; j++)
            cout << (wq.add(i*10+j, 1) ? "ok" : "fail") << " ";
        cout << endl;
        cout << "dump" << endl; wq.dump();
        for (j = 0; j < 9; j++)
            cout << wq.getNext().uid << " " << endl;
        cout << "dump " << endl; wq.dump();
    }

    cout << "final dump " << endl;
    wq.dump();

    return 0;
}
