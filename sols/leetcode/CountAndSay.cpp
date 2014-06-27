class Solution {
public:
    string countAndSay(int n) {
        string cur = "1";
        string last;
        for (int i=0;i<n-1;i++){
            last.swap(cur);
            cur.clear();

            char lc = -1;
            int c = 0;
            for (int j=0;j<last.size();j++) {
                if (last[j]!=lc) {
                    if (lc!=-1) {
                        cur.append(1, (char)('0'+c));
                        cur.append(1, lc);
                    }
                    lc=last[j],c=1;
                } else
                    c++;
            }
            if (lc!=-1) {
                cur.append(1, (char)('0'+c));
                cur.append(1, lc);
            }
        }
        return cur;
    }
};
