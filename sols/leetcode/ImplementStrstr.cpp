class Solution {
public:
    char *strStr_(char *haystack, char *needle) {
        char *h, *n;
        for (h = haystack; *h; h++) {
            char *hn = h;
            for (n = needle; *n && *n == *hn; n++, hn++);
            if (!*n)
                return h;
        }
        return NULL;
    }

    char *strStr(char *haystack, char *needle) {
    	if (!*needle)
    		return haystack;
    	char *start1 = haystack;
    	char *start2 = needle+1;
    	while (*start2) {
    		++start1;
    		++start2;
    	}

    	while (*start1) {
    		char *temp1 = needle;
    		char *temp2 = haystack;
    		while (*temp1 && *temp2 && *temp1 == *temp2) {
    			++temp1;
    			++temp2;
    		}
    		if (!*temp1)
    			return haystack;
    		++haystack;
    		++start1;
    	}
    	return NULL;
    }
};
