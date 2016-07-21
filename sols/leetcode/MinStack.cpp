class MinStack {
    vector<pair<int,int>> data;

public:
    void push(int x) {
        if (data.size()) {
            data.push_back(make_pair(x, min(x, data.back().second)));
        } else {
            data.push_back(make_pair(x, x));
        }
    }

    void pop() {
        data.pop_back();
    }

    int top() {
        return data.back().first;
    }

    int getMin() {
        return data.back().second;
    }
};
