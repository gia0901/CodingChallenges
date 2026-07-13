#include <bits/stdc++.h>
using namespace std;

class LinkedList {
    struct Node {
        int val;
        Node* next;
        Node() : val(0), next(nullptr) {}
        Node(int v) : val(v), next(nullptr) {}
        Node(int v, Node* next) : val(v), next(next) {}
    };

    Node* head_ = nullptr;
    int len_ = 0;
public:
    LinkedList() = default;
    ~LinkedList() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next;
            delete temp;
        }
    }

    void insert(int idx, int val) {
        if (idx < 0 || idx > len_) return;
        if (idx == 0) return push_front(val);
        if (idx == len_) return push_back(val);

        Node* cur = head_;
        Node* prev = nullptr;
        for (int i = 0; i < idx; i++) {
            prev = cur;
            cur = cur->next;
        }
        
        Node* newNode = new Node(val);
        prev->next = newNode;
        newNode->next = cur;
        len_++;
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (head_ == nullptr) {
            head_ = newNode;
            len_++;
            return;
        }
        
        Node* temp = head_;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        len_++;
    }

    void pop_back() {
        if (head_ == nullptr) return;
        if (head_->next == nullptr) {
            delete head_;
            head_ = nullptr;
        }
        else {
            Node* curr = head_;
            Node* prev = curr;
            while (curr->next) {
                prev = curr;
                curr = curr->next;
            }

            prev->next = nullptr;
            delete curr;
        }
        len_--;
    }

    void push_front(int val) { // O(1)
        Node* newNode = new Node(val);
        newNode->next = head_;
        head_ = newNode;
        len_++;
    }

    void pop_front() { // O(1)
        if (head_ == nullptr) return;
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
        len_--;
    }
    
    void erase(int idx) {
        if (idx < 0 || idx >= len_) return;
        if (idx == 0) return pop_front();
        if (idx == len_-1) return pop_back();

        Node* cur = head_;
        Node* prev = nullptr;
        for (int i = 0; i < idx; i++) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        delete cur;
        len_--;
    }

    bool empty() const {
        return len_ == 0;
    }

    void printList() {
        Node* temp = head_;
        while (temp) {
            cout << temp->val << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    LinkedList l;
    l.push_back(2);
    l.push_back(3);
    l.push_front(1);
    l.printList();
    l.erase(1);
    l.printList();

}
