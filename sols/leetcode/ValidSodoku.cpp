class Solution {
public:
    bool isVal(vector<vector<char> > &board, vector<pair<int,int> > &ind) {
        vector<char> mask(10);
        int i;
        for(i=0;i<9;i++) {
            char d = board[ind[i].first][ind[i].second];
            if (d == '.')
                continue;
            d -= '0';
            if (mask[d])
                return false;
            else
                mask[d] = 1;
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char> > &board) {
        vector<pair<int,int> > ind(9);
        int i,j,x,y;

        // vert
        for (i=0;i<9;i++)
            ind[i].first=i;
        for (i=0;i<9;i++) {
            for (j=0;j<9;j++)
                ind[j].second=i;
            if (!isVal(board,ind))
                return false;
        }

        // hori
        for (i=0;i<9;i++)
            ind[i].second=i;
        for (i=0;i<9;i++) {
            for (j=0;j<9;j++)
                ind[j].first=i;
            if (!isVal(board,ind))
                return false;
        }

        // square
        for (i=0;i<3;i++)
            for (j=0;j<3;j++) {
                for (x=0;x<3;x++)
                    for (y=0;y<3;y++)
                        ind[x*3+y] = make_pair(i*3+x,j*3+y);
                if (!isVal(board,ind))
                    return false;
            }
        return true;
    }
};
