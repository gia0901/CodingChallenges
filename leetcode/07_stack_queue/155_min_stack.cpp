#include <bits/stdc++.h>
using namespace std;

class MinStack {
public:
    MinStack() {}
    
    void push(int value) {
        if (st_.empty()) {
            st_.push({value,value});
        }
        else {
            st_.push({value, min(value, st_.top().second)});
        }
    }
    
    void pop() {
        st_.pop();
    }
    
    int top() {
        return st_.top().first;
    }
    
    int getMin() {
        return st_.top().second;
    }
private:
    stack<pair<int,int>> st_; // pair<val, min_val from the beginning>
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */