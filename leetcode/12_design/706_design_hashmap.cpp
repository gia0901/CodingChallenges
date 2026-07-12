#include <bits/stdc++.h>
using namespace std;

// Tự cài hash table bằng SEPARATE CHAINING:
//   3 phần: (1) hash function  (2) bucket = mảng linked list  (3) get/put/remove duyệt chain.
// Time trung bình O(1)/op (hash phân tán tốt -> chain ngắn); worst O(n) nếu dồn 1 bucket.
class MyHashMap {
    // mỗi bucket là 1 danh sách liên kết các (key,val) bị đụng độ (cùng hash index)
    struct Node {
        int key, val;
        Node* next;
        Node(int k, int v) : key(k), val(v), next(nullptr) {}   // (!) key(k) không phải key(v)
    };
    static constexpr int SIZE = 19997;          // số bucket, dùng SỐ NGUYÊN TỐ -> giảm clustering
    static constexpr int MULTIPLIER = 12582917; // số nguyên tố lớn -> phân tán key đều hơn

    Node* data[SIZE] = {};   // mảng con trỏ đầu chain, khởi tạo toàn nullptr


public:
    MyHashMap() {}

    // key -> chỉ số bucket. long long tránh tràn (key*MULTIPLIER có thể > int).
    int hash(int key) {
        return (int)((long long)key * MULTIPLIER % SIZE);
    }

    // upsert = XÓA key cũ (nếu có) rồi THÊM mới vào đầu chain -> đảm bảo mỗi key duy nhất 1 node
    void put(int key, int value) {
        remove(key);                          // bỏ node cũ trùng key trước

        int hashIdx = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = data[hashIdx];        // prepend: nối vào đầu chain O(1)
        data[hashIdx] = newNode;
    }

    // duyệt chain của bucket, khớp key thì trả val; hết chain -> -1 (không tồn tại)
    int get(int key) {
        int hashIdx = hash(key);
        Node* temp = data[hashIdx];
        while (temp) {
            if (temp->key == key) return temp->val;
            temp = temp->next;
        }
        return -1;
    }

    // xóa node có key khỏi chain: tách 2 case -> (a) node ở ĐẦU chain, (b) node ở GIỮA/CUỐI
    void remove(int key) {
        int hashIdx = hash(key);
        Node* current = data[hashIdx];

        if (current == nullptr) return;
        if (current->key == key) {               // (a) đầu chain: dời con trỏ đầu bucket
            data[hashIdx] = current->next;
            delete current;                       // nhớ delete -> tránh memory leak
        }
        else {                                    // (b) tìm node mà node->next là mục cần xóa
            while (current->next) {
                if (current->next->key == key) {
                    Node* temp = current->next;
                    current->next = temp->next;   // nối tắt qua node cần xóa
                    delete temp;
                    return;
                }
                current = current->next;
            }
        }
    }
};