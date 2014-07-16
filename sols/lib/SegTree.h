/*
 * SegTree.h
 *
 *  Created on: Jun 26, 2014
 *      Author: danke
 */

#ifndef SEGTREE_H_
#define SEGTREE_H_

/* Segment tree */
#define L(u) u<<1
#define R(u) u<<1|1
#define lson u<<1, b, mid
#define rson u<<1|1, mid, e
#define defmid int mid = (b + e) >> 1
const int root = 1;

template<int MAX, int VALS, typename Num>
struct SegTree {
    struct SegNode {
        int cover;  /* the value of the interval, -1 if not fully covered */
        bool coverL, coverR;
    };
    SegNode tree[MAX];
    Num Y[VALS];
    int iY; // next index of Y
    int nY; // total count of Y

    void init(int u, int b, int e) {
        tree[u].cover = 0;
        if (b + 1 == e)
            return;
        defmid;
        init(lson);
        init(rson);
    }

    void clearY() {
        iY = 0;
    }

    void pushY(Num v) {
        Y[iY++] = v;
    }

    /* returns nY - 1 */
    int discreteInit() {
        sort(Y, Y + iY);
        nY = unique(Y, Y + iY) - Y - 1;
        init(root, 0, nY);
        return nY;
    }

    void pushdown(int u, int b, int e) {
        if (tree[u].cover != -1) {
            tree[L(u)].cover = tree[u].cover;
            tree[R(u)].cover = tree[u].cover;
        }
    }

    void pushup(int u, int b, int e) {
        if (tree[L(u)].cover != tree[R(u)].cover)
            tree[u].cover = -1;
        else
            tree[u].cover = tree[L(u)].cover;
    }

    void update(int u, int b, int e, Num l, Num r, int val) {
        if (tree[u].cover != -1 && l == Y[b] && Y[e] == r) {
            // draw line
            if (tree[u].cover == 0 && val == 1 || tree[u].cover == 1 && val == -1)
                len += Y[e] - Y[b];

            tree[u].cover += val;
            return;
        }

        pushdown(u, b, e);

        defmid;
        if (r <= Y[mid])
            update(lson, l, r, val);
        else if (l >= Y[mid])
            update(rson, l, r, val);
        else {
            update(lson, l, Y[mid], val);
            update(rson, Y[mid], r, val);
        }

        pushup(u, b, e);
    }

    // returns uncovered end points
    int query(int u, int b, int e) {
        if (b + 1 == e) {
            tree[u].coverL = tree[u].coverR = tree[u].cover > 0;
            return 0;
        }

        pushdown(u, b, e);

        defmid;
        int vis = query(lson) + query(rson);

        if (tree[L(u)].coverR != tree[R(u)].coverL)
            vis += 1;

        // pushup
        tree[u].coverL = tree[L(u)].coverL;
        tree[u].coverR = tree[R(u)].coverR;

        return vis;
    }
};

#endif /* SEGTREE_H_ */
