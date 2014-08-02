#include <cstdio>
#include <cstdlib>
#include <algorithm>
//#include <cassert>

static const int kMaxN = 100000;
int mN = 0;
struct Cell
{
    int i, j;
    inline int lastBitSum() const { return (i + j) & 1; }
    inline bool operator < (const Cell& right) const { return j < right.j || j == right.j && i < right.i; }
    inline bool operator >= (const Cell& right) const { return j >= right.j || j == right.j && i >= right.i; }
    inline bool operator == (const Cell& right) const { return i == right.i && j == right.j; }
    inline bool operator != (const Cell& right) const { return i != right.i || j != right.j; }
};
Cell mInputCells[4];
Cell mPath[2 * kMaxN + 2];

enum Direction
{
    kUnknown = -1,
    kVertical1 = 0,
    kVertical2 = 1,
    kLeft1 = 2,
    kLeft2 = 3,
    kRight1 = 4,
    kRight2 = 5,
    kFinish1 = 6,
    kFinish2 = 7,
};

inline bool moveSecond(int cylinder[2][8], int length, const Cell& second)
{
    if (cylinder[second.i][second.j] != kFinish2)
    {
        int& cur = cylinder[second.i][second.j];
        Cell next = second;
        next.i = 1 - second.i;
        int nextState = cylinder[next.i][next.j];
        if (kUnknown == nextState || kFinish2 == nextState)
        {
            cur = kVertical2;
            if (moveSecond(cylinder, length, next))
                return true;
        }
        next.i = second.i;
        next.j = second.j - 1;
        if (next.j < 0)
            next.j = length - 1;
        nextState = cylinder[next.i][next.j];
        if (kUnknown == nextState || kFinish2 == nextState)
        {
            cur = kLeft2;
            if (moveSecond(cylinder, length, next))
                return true;
        }
        next.j = second.j + 1;
        if (next.j >= length)
            next.j = 0;
        nextState = cylinder[next.i][next.j];
        if (kUnknown == nextState || kFinish2 == nextState)
        {
            cur = kRight2;
            if (moveSecond(cylinder, length, next))
                return true;
        }
        cur = kUnknown;
        return false;
    }
    else
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < length; ++j)
                if (kUnknown == cylinder[i][j])
                    return false;
        return true;
    }
}

inline bool moveFirst(int cylinder[2][8], int length, const Cell& first, const Cell& second)
{
    int& cur = cylinder[first.i][first.j];
    if (cur != kFinish2)
    {
        Cell next = first;
        next.i = 1 - first.i;
        int nextState = cylinder[next.i][next.j];
        if ((kUnknown == nextState || kFinish2 == nextState) && next != second)
        {
            cur = kVertical1;
            if (moveFirst(cylinder, length, next, second))
                return true;
        }
        next.i = first.i;
        next.j = first.j - 1;
        if (next.j < 0)
            next.j = length - 1;
        nextState = cylinder[next.i][next.j];
        if ((kUnknown == nextState || kFinish2 == nextState) && next != second)
        {
            cur = kLeft1;
            if (moveFirst(cylinder, length, next, second))
                return true;
        }
        next.j = first.j + 1;
        if (next.j >= length)
            next.j = 0;
        nextState = cylinder[next.i][next.j];
        if ((kUnknown == nextState || kFinish2 == nextState) && next != second)
        {
            cur = kRight1;
            if (moveFirst(cylinder, length, next, second))
                return true;
        }
        cur = kUnknown;
        return false;
    }
    else
    {
        cur = kFinish1;
        if (moveSecond(cylinder, length, second))
            return true;
        cur = kFinish2;
        return false;
    }
}

void printSolution()
{
    int occupied = 0;
    Cell inputCells[4];
    int transform[4];
    for (int i = 0; i < 4; ++i)
        inputCells[i] = mInputCells[i];
    std::sort(inputCells, inputCells + 4);
    for (int i = 0; i < 4; ++i)
    {
        Cell& curCell = inputCells[i];
        int x = (curCell.j - 1) >> 1;
        if (0 != occupied && transform[occupied - 1] == x)
            continue;
        transform[occupied++] = x;
    }
    for (int i = 0; i < 4; ++i)
    {
        inputCells[i].i = mInputCells[i].i - 1;
        for (int j = 0; j < occupied; ++j)
            if (transform[j] == ((mInputCells[i].j - 1) >> 1))
            {
                inputCells[i].j = 2 * j + ((mInputCells[i].j - 1) & 1);
                break;
            }
    }

    int cylinder[2][8];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 8; ++j)
            cylinder[i][j] = kUnknown;
    cylinder[inputCells[2].i][inputCells[2].j] = kFinish2;
    cylinder[inputCells[3].i][inputCells[3].j] = kFinish2;

    // solution
    bool res = moveFirst(cylinder, 2 * occupied, inputCells[0], inputCells[1]);
    //assert(res);
    if (res)
    for (int spider = 0; spider < 2; ++spider)
    {
        Cell move = inputCells[spider];
        Cell* path = mPath;
        path->i = move.i + 1;
        path->j = transform[move.j >> 1] * 2 + (move.j & 1) + 1;
        ++path;
        int dist = 1;
        while ((cylinder[move.i][move.j] & (~1)) != kFinish1)
        {
            int destination = 0;
            switch (cylinder[move.i][move.j] & (~1))
            {
            case kVertical1:
                {
                    if (move.j & 1) // may have come from left
                    {
                        int right = move.j + 1;
                        if (right >= 2 * occupied)
                            right = 0;
                        if ((cylinder[0][move.j] & (~1)) != kRight1 && (cylinder[1][move.j] & (~1)) != kRight1
                            && (cylinder[0][right] & (~1)) != kLeft1 && (cylinder[1][right] & (~1)) != kLeft1
                            && (cylinder[0][right] & (~1)) != kVertical1 && (cylinder[1][right] & (~1)) != kVertical1)
                        {
                            int start = transform[move.j >> 1] * 2 + 2, end = transform[right >> 1] * 2;
                            if (start >= mN)
                                start = 0;
                            if (start != end)
                            {
                                ++start;
                                if (end <= 0)
                                    end = mN;
                                if (start > end)
                                {
                                    dist += 2 * (end + mN + 1 - start);
                                    for (int c = start; c <= mN; ++c, ++path)
                                    {
                                        path->i = move.i + 1;
                                        path->j = c;
                                    }
                                    for (int c = 1; c <= end; ++c, ++path)
                                    {
                                        path->i = move.i + 1;
                                        path->j = c;
                                    }
                                    for (int c = end; c >= 1; --c, ++path)
                                    {
                                        path->i = 2 - move.i;
                                        path->j = c;
                                    }
                                    for (int c = mN; c >= start; --c, ++path)
                                    {
                                        path->i = 2 - move.i;
                                        path->j = c;
                                    }
                                }
                                else
                                {
                                    dist += 2 * (end + 1 - start);
                                    for (int c = start; c <= end; ++c, ++path)
                                    {
                                        path->i = move.i + 1;
                                        path->j = c;
                                    }
                                    for (int c = end; c >= start; --c, ++path)
                                    {
                                        path->i = 2 - move.i;
                                        path->j = c;
                                    }
                                }
                            }
                        }
                    }
                    else // may have come from right
                    {
                        int left = move.j - 1;
                        if (left < 0)
                            left = 2 * occupied - 1;
                        if ((cylinder[0][move.j] & (~1)) != kLeft1 && (cylinder[1][move.j] & (~1)) != kLeft1
                            && (cylinder[0][left] & (~1)) != kRight1 && (cylinder[1][left] & (~1)) != kRight1)
                        {
                            int start = transform[move.j >> 1] * 2, end = transform[left >> 1] * 2 + 2;
                            if (end >= mN)
                                end = 0;
                            if (start != end)
                            {
                                ++end;
                                if (start <= 0)
                                    start = mN;
                                if (start < end)
                                {
                                    dist += 2 * (start + mN + 1 - end);
                                    for (int c = start; c >= 1; --c, ++path)
                                    {
                                        path->i = move.i + 1;
                                        path->j = c;
                                    }
                                    for (int c = mN; c >= end; --c, ++path)
                                    {
                                        path->i = move.i + 1;
                                        path->j = c;
                                    }
                                    for (int c = end; c <= mN; ++c, ++path)
                                    {
                                        path->i = 2 - move.i;
                                        path->j = c;
                                    }
                                    for (int c = 1; c <= start; ++c, ++path)
                                    {
                                        path->i = 2 - move.i;
                                        path->j = c;
                                    }
                                }
                                else
                                {
                                    dist += 2 * (start + 1 - end);
                                    for (int c = start; c >= end; --c, ++path)
                                    {
                                        path->i = move.i + 1;
                                        path->j = c;
                                    }
                                    for (int c = end; c <= start; ++c, ++path)
                                    {
                                        path->i = 2 - move.i;
                                        path->j = c;
                                    }
                                }
                            }
                        }
                    }
                    move.i = 1 - move.i;
                }
                break;
            case kLeft1:
                destination = move.j - 1;
                if (destination < 0)
                    destination = 2 * occupied - 1;
                if (0 == (move.j & 1))
                {
                    int start = transform[move.j >> 1] * 2, end = transform[destination >> 1] * 2 + 2;
                    int absent = start - end;
                    if (absent < 0)
                        absent += mN;
                    if (absent > 0)
                    {
                        if ((cylinder[1 - move.i][move.j] & (~1)) == kLeft1 || (cylinder[1 - move.i][destination] & (~1)) == kRight1)
                        {
                            dist += absent;
                            if (end > start)
                            {
                                for (int c = start; c > 0; --c, ++path)
                                {
                                    path->i = move.i + 1;
                                    path->j = c;
                                }
                                for (int c = mN; c > end; --c, ++path)
                                {
                                    path->i = move.i + 1;
                                    path->j = c;
                                }
                            }
                            else
                            {
                                for (int c = start; c > end; --c, ++path)
                                {
                                    path->i = move.i + 1;
                                    path->j = c;
                                }
                            }
                        }
                        else
                        {
                            dist += absent * 2;
                            int h = move.i + 1;
                            if (end > start)
                            {
                                for (int c = start; c > 0; --c, ++path)
                                {
                                    path->i = h;
                                    path->j = c;
                                    ++path;
                                    h = 3 - h;
                                    path->i = h;
                                    path->j = c;
                                }
                                for (int c = mN; c > end; --c, ++path)
                                {
                                    path->i = h;
                                    path->j = c;
                                    ++path;
                                    h = 3 - h;
                                    path->i = h;
                                    path->j = c;
                                }
                            }
                            else
                            {
                                for (int c = start; c > end; --c, ++path)
                                {
                                    path->i = h;
                                    path->j = c;
                                    ++path;
                                    h = 3 - h;
                                    path->i = h;
                                    path->j = c;
                                }
                            }
                            //assert(h == move.i + 1);
                        }
                    }
                }
                move.j = destination;
                break;
            case kRight1:
                destination = move.j + 1;
                if (destination >= 2 * occupied)
                    destination = 0;
                if (0 != (move.j & 1))
                {
                    int start = transform[move.j >> 1] * 2 + 3, end = transform[destination >> 1] * 2 + 1;
                    int absent = end - start;
                    if (absent < 0)
                        absent += mN;
                    if (absent > 0)
                    {
                        if ((cylinder[1 - move.i][move.j] & (~1)) == kRight1 || (cylinder[1 - move.i][destination] & (~1)) == kLeft1)
                        {
                            dist += absent;
                            if (end < start)
                            {
                                for (int c = start; c <= mN; ++c, ++path)
                                {
                                    path->i = move.i + 1;
                                    path->j = c;
                                }
                                for (int c = 1; c < end; ++c, ++path)
                                {
                                    path->i = move.i + 1;
                                    path->j = c;
                                }
                            }
                            else
                            {
                                for (int c = start; c < end; ++c, ++path)
                                {
                                    path->i = move.i + 1;
                                    path->j = c;
                                }
                            }
                        }
                        else
                        {
                            dist += absent * 2;
                            int h = move.i + 1;
                            if (end < start)
                            {
                                for (int c = start; c <= mN; ++c, ++path)
                                {
                                    path->i = h;
                                    path->j = c;
                                    ++path;
                                    h = 3 - h;
                                    path->i = h;
                                    path->j = c;
                                }
                                for (int c = 1; c < end; ++c, ++path)
                                {
                                    path->i = h;
                                    path->j = c;
                                    ++path;
                                    h = 3 - h;
                                    path->i = h;
                                    path->j = c;
                                }
                            }
                            else
                            {
                                for (int c = start; c < end; ++c, ++path)
                                {
                                    path->i = h;
                                    path->j = c;
                                    ++path;
                                    h = 3 - h;
                                    path->i = h;
                                    path->j = c;
                                }
                            }
                            //assert(h == move.i + 1);
                        }
                    }
                }
                move.j = destination;
                break;
            case kUnknown:
            case kFinish1:
            default:
                ;//assert(false);
            }
            path->i = move.i + 1;
            path->j = transform[move.j >> 1] * 2 + (move.j & 1) + 1;
            ++path;
            ++dist;
        }

        printf("%d\n", dist);
        //assert(int(path - mPath) == dist);
        for (const Cell* curCell = mPath; curCell != path; ++curCell)
            printf("%d %d\n", curCell->i, curCell->j);
    }
    else
        printf("-1\n");
}

int main(int argc, char** argv)
{
#if BENCH
    freopen("files/r13_2_test.txt","r",stdin);
#endif
    int T = 0;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d", &mN);
        scanf("%d%d", &mInputCells[0].i, &mInputCells[0].j);
        scanf("%d%d", &mInputCells[1].i, &mInputCells[1].j);
        scanf("%d%d", &mInputCells[2].i, &mInputCells[2].j);
        scanf("%d%d", &mInputCells[3].i, &mInputCells[3].j);

        printf("Case #%d\n", t);
        bool noSolution = false;
        if (mInputCells[0].lastBitSum())
        {
            if (mInputCells[1].lastBitSum())
                noSolution = (0 != (mInputCells[2].lastBitSum() || mInputCells[3].lastBitSum())); // 11 -> 00
            else
                noSolution = (0 == (mInputCells[2].lastBitSum() ^ mInputCells[3].lastBitSum())); // 10 -> 10
        }
        else
        {
            if (mInputCells[1].lastBitSum())
                noSolution = (0 == (mInputCells[2].lastBitSum() ^ mInputCells[3].lastBitSum())); // 10 -> 10
            else
                noSolution = (0 == (mInputCells[2].lastBitSum() && mInputCells[3].lastBitSum())); // 00 -> 11
        }
        if (noSolution)
            printf("-1\n");
        else
            printSolution();
    }

    return 0;
}
