# 14. Implementation from Scratch ★★★☆☆

Dạng phỏng vấn **"implement/design X"**: viết lại data structure hoặc algorithm từ đầu.
Interviewer không cần bạn thuộc lòng code, mà cần bạn nắm **invariant bên trong**, complexity
từng operation, và trade-off. Khác các topic trước (dùng STL để giải bài), ở đây STL chính
là **thứ bị hỏi**.

## A. Data structures cốt lõi (skeleton C++)

> **Vì sao không có stack/queue/linked list/tree/graph "trần" ở đây** — chúng đã nằm đúng chỗ,
> hoặc dạng được hỏi thật là biến thể trong file này:
> - **Stack trần** = dynamic array push/pop ở cuối (A1). Dạng được hỏi thật: Min Stack (B2).
> - **Queue trần** bằng mảng lộ ngay vấn đề "dequeue O(n)?" — câu trả lời chính là circular buffer (D2); biến thể hay hỏi: Queue using Stacks (B3).
> - **Singly linked list** (node, dummy, reverse, fast/slow) → [06_linked_list.md](06_linked_list.md). Doubly → D1.
> - **Graph** chỉ có một nội dung "implement" là cách biểu diễn (adjacency list vs matrix) → [08_graph.md](08_graph.md) mục 0.
> - **Tree**: đề luôn cho sẵn `TreeNode`; cái được hỏi là traversal ([05_tree.md](05_tree.md)) và BST insert/delete (A6).

### A1. Dynamic array (vector)

Invariant: `size ≤ capacity`; khi đầy thì **nhân đôi capacity** rồi copy sang vùng mới.

```cpp
struct DynArray {
    int* data; int size = 0, cap = 1;
    void push_back(int x) {
        if (size == cap) {
            cap *= 2;                       // nhân đôi, KHÔNG cộng hằng số
            int* nd = new int[cap];
            // copy size phần tử cũ sang nd, delete[] data, data = nd
        }
        data[size++] = x;
    }
};
```

Vì sao push_back **amortized O(1)**: để đạt size n, tổng số lần copy qua các đợt grow là
`n/2 + n/4 + ... ≤ n` → n lần push tốn O(n) copy → trung bình O(1)/push. Nếu grow bằng
cách **cộng hằng số** (cap += 100) thì tổng copy là O(n²).

### A2. Hash map (separate chaining)

Mỗi bucket là một danh sách; key được băm rồi mod số bucket. Invariant: **load factor**
`size/buckets` giữ dưới ngưỡng (thường 1.0) — vượt thì rehash gấp đôi số bucket.

```cpp
struct HashMap {
    vector<list<pair<int,int>>> buckets;    // buckets[h] chứa các (key, value) cùng hash
    int sz = 0;
    int idx(int key) const { return (key % (int)buckets.size() + buckets.size()) % buckets.size(); }
    void put(int key, int value) {
        auto& b = buckets[idx(key)];
        // tìm key trong b: có → cập nhật value, return
        b.push_back({key, value}); sz++;
        // if (load factor > 1.0) rehash(): buckets x2, chèn lại TOÀN BỘ phần tử (idx đổi!)
    }
    // get/remove: quét bucket idx(key), O(chiều dài bucket)
};
```

- Trung bình O(1)/op **nếu** hash phân bố đều + load factor bị chặn; worst case O(n) khi mọi key dồn 1 bucket.
- Biến thể **open addressing** (linear probing): không dùng list, đụng độ thì dò ô kế tiếp
  `(h+1) % cap`; xóa phải đặt **tombstone** (đánh dấu "từng có") kẻo chuỗi dò bị đứt.

### A3. Min-heap (array-based) + heapify

Complete binary tree nén vào mảng: node `i` có cha `(i-1)/2`, con `2i+1, 2i+2`.
Invariant: **cha ≤ con** trên mọi cạnh.

```
 mảng  [1, 3, 2, 7, 5]        cây     1
 index  0  1  2  3  4               /   \
                                   3     2
 cha của i=4 là (4-1)/2=1        /  \
                                7    5
```

```cpp
struct MinHeap {
    vector<int> a;
    void sift_up(int i) {       // sau khi push vào cuối
        // while (i > 0 && a[i] < a[(i-1)/2]) swap với cha, i = (i-1)/2
    }
    void sift_down(int i) {     // sau khi pop: đưa a.back() lên đỉnh rồi đẩy xuống
        // chọn con NHỎ HƠN trong 2 con; nếu nhỏ hơn a[i] thì swap, lặp tiếp
    }
    void build(vector<int>& v) { // heapify O(n)
        a = v;
        for (int i = (int)a.size()/2 - 1; i >= 0; i--) sift_down(i);
    }
};
```

Vì sao build-heap **O(n)** chứ không O(n log n): sift_down từ node ở độ cao h tốn O(h);
một nửa số node là lá (h=0), 1/4 có h=1... tổng `Σ n/2^(h+1) · h = O(n)`.

### A4. Trie (prefix tree)

Mỗi node là một mảng 26 con trỏ con + cờ kết thúc từ. Đi từ root theo từng ký tự.

```cpp
struct TrieNode {
    TrieNode* child[26] = {};
    bool isEnd = false;
};
// insert(word): đi theo từng c, thiếu node thì new; cuối đường đặt isEnd = true
// search(word): đi theo từng c, đứt đường → false; cuối đường trả về isEnd
// startsWith(prefix): như search nhưng cuối đường trả true luôn
```

Time O(L)/op với L là độ dài từ — **không phụ thuộc số từ đã lưu** (khác hash map ở điểm
tra được theo prefix).

### A5. Union-Find (Disjoint Set Union)

Mỗi phần tử trỏ lên cha; root đại diện cho tập. Hai tối ưu bắt buộc: **path compression**
(find xong trỏ thẳng lên root) + **union by size/rank** (cây nhỏ gắn vào cây lớn).

```cpp
struct DSU {
    vector<int> parent, sz;
    DSU(int n) : parent(n), sz(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]); // path compression
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;           // đã cùng tập → phát hiện cycle
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a; sz[a] += sz[b];
        return true;
    }
};
```

Với cả hai tối ưu, mỗi op gần như O(1) (chính xác: O(α(n)), α là inverse Ackermann).

### A6. BST insert / delete

Invariant: trái < node < phải. Insert: đi xuống như search, gắn lá mới. **Delete có 3 case**:

```
 case 1: lá             → xóa thẳng
 case 2: 1 con          → nối con lên thay chỗ mình
 case 3: 2 con          → tìm SUCCESSOR (nhỏ nhất của cây phải),
                          chép giá trị successor lên node, rồi xóa successor
                          (successor có ≤ 1 con → quy về case 1/2)
```

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val)      root->left  = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        // case 1+2: if (!root->left) return root->right; đối xứng cho right
        // case 3: succ = node trái nhất của root->right;
        //         root->val = succ->val; root->right = deleteNode(root->right, succ->val);
    }
    return root;
}
```

Mọi op O(h); BST thường không tự cân bằng nên worst case h = n (chèn dãy đã sort).
Phỏng vấn hiếm khi bắt code red-black/AVL — chỉ cần **nói được** vì sao cần cân bằng.

## B. Bài cốt lõi — Design-style LeetCode (7 bài)

| # | Bài | Cấu trúc bên trong | Complexity mục tiêu |
|---|-----|--------------------|---------------------|
| 1 | LRU Cache (146) | hash map + doubly linked list | O(1) mọi op |
| 2 | Min Stack (155) | 2 stack song song | O(1) mọi op |
| 3 | Implement Queue using Stacks (232) | 2 stack in/out | amortized O(1) |
| 4 | Insert Delete GetRandom O(1) (380) | vector + hash map index | O(1) mọi op |
| 5 | Time Based KV Store (981) | map key → vector (time, value) | set O(1), get O(log n) |
| 6 | Implement Trie (208) | A4 nguyên bản | O(L)/op |
| 7 | Design HashMap (706) | A2 nguyên bản | trung bình O(1) |

### 1. LRU Cache — bài "design" hay hỏi nhất
> Hash map cho O(1) lookup + doubly linked list cho O(1) move-to-front / evict đuôi.

```
 map: key → con trỏ node          list (mới → cũ):
                                  head ⇄ [k3] ⇄ [k1] ⇄ [k7] ⇄ tail
 get(k1)  : tháo k1, gắn lại sát head        (dummy)² tránh xử lý biên
 put mới khi đầy: xóa node sát tail + XÓA CẢ ENTRY TRONG MAP
```

```cpp
struct LRUCache {
    int cap;
    list<pair<int,int>> items;                        // (key, value), front = mới nhất
    unordered_map<int, list<pair<int,int>>::iterator> pos;
    // get: không có → -1; có → splice node lên front, trả value
    //      items.splice(items.begin(), items, pos[key]);
    // put: key đã có → cập nhật + splice lên front
    //      chưa có: nếu full → xóa items.back() VÀ pos.erase(key cũ); push_front + ghi pos
};
```

- Vì sao doubly (không phải singly): tháo một node ở giữa cần con trỏ prev — singly phải quét O(n).
- Bẫy: `get` cũng phải move-to-front (get là một lần "use"); evict phải xóa **cả hai** cấu trúc.

### 2. Min Stack
> Stack phụ lưu min-so-far: push `min(x, minStack.top())`, pop cả hai cùng lúc.
- Vì sao đúng: đỉnh stack phụ luôn là min của đúng tập phần tử đang còn trong stack chính.

### 3. Queue using Stacks
> Stack `in` nhận push; `out` phục vụ pop/peek. `out` cạn thì trút toàn bộ `in` sang (đảo chiều).
- Amortized O(1): mỗi phần tử bị di chuyển tối đa 2 lần trong cả vòng đời.

### 4. Insert Delete GetRandom O(1)
> Vector chứa giá trị + map giá trị→index. Xóa: **swap phần tử cần xóa với phần tử cuối**, pop_back.
- Bẫy: sau swap phải **cập nhật index trong map của phần tử vừa bị swap xuống**.
- getRandom cần vector (truy cập theo index ngẫu nhiên) — map/set không làm được O(1).

### 5. Time Based KV Store
> Mỗi key giữ vector (timestamp, value) — timestamp set vào luôn tăng → vector đã sort sẵn.
> `get` = binary search (`upper_bound` rồi lùi 1) tìm timestamp lớn nhất ≤ t.

## C. Sorting from scratch

| Thuật toán | Time avg | Time worst | Space | Stable |
|-----------|:--------:|:----------:|:-----:|:------:|
| Bubble    | O(n²) | O(n²), best **O(n)** với cờ swapped | O(1) | ✓ |
| Selection | O(n²) | O(n²) (kể cả input đã sort) | O(1) | ✗ |
| Insertion | O(n²) | O(n²), best **O(n)** (gần sorted) | O(1) | ✓ |
| Quicksort | O(n log n) | **O(n²)** | O(log n) stack | ✗ |
| Mergesort | O(n log n) | O(n log n) | O(n) | ✓ |
| Heapsort  | O(n log n) | O(n log n) | O(1) | ✗ |

### C0. Basic sorts — bubble / selection / insertion

Ở mức mid+ hiếm khi là coding task, nhưng phỏng vấn **fresher/junior hỏi trực tiếp khá thường**,
và cả ba là nguyên liệu cho câu follow-up ở mọi level.

```cpp
// Insertion: bên trái i luôn sorted; rút a[i] ra, dịch phần tử lớn hơn sang phải, chèn vào lỗ
for (int i = 1; i < n; i++) {
    int key = a[i], j = i - 1;
    while (j >= 0 && a[j] > key) { a[j+1] = a[j]; j--; }
    a[j+1] = key;
}
// Selection: mỗi vòng tìm min của phần chưa sort, swap về vị trí i
//   for i: minIdx = argmin(a[i..n-1]); swap(a[i], a[minIdx]);
// Bubble: quét cạnh nhau, swap nếu ngược thứ tự; CỜ swapped — một lượt không swap → dừng sớm
//   for i: swapped = false; for j < n-1-i: if (a[j] > a[j+1]) swap, swapped = true;
//          if (!swapped) break;   // best case O(n) trên mảng đã sort
```

Giá trị thật của từng cái khi bị hỏi sâu (đây mới là phần ăn điểm):

- **Insertion sort**: O(n) trên mảng **gần sorted** → là base case của sort thực tế
  (`std::sort` = introsort, chuyển sang insertion cho đoạn nhỏ; Timsort của Python/Java cũng vậy).
  Bài LC liên quan: Insertion Sort List (147).
- **Selection sort**: tiền thân tư duy của heapsort — "selection sort nhưng tìm min bằng heap
  thay vì quét O(n)". Điểm trừ riêng: không stable và không nhanh lên khi input đã sort.
- **Bubble sort**: chủ yếu để giải thích vì sao O(n²) (mỗi swap chỉ sửa được 1 cặp nghịch thế —
  inversion — mà mảng có thể có tới n(n-1)/2 cặp) và kỹ thuật early exit bằng cờ swapped.

### Quicksort — partition là phần bị hỏi kỹ nhất

```cpp
// Lomuto partition: a[lo..i] < pivot, pivot đứng đúng chỗ, trả về vị trí pivot
int partition(vector<int>& a, int lo, int hi) {
    swap(a[lo + rand() % (hi - lo + 1)], a[hi]);  // pivot ngẫu nhiên, đưa về cuối
    int pivot = a[hi], i = lo;
    for (int j = lo; j < hi; j++)
        if (a[j] < pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]);
    return i;
}
// quicksort(lo, hi): p = partition; đệ quy [lo, p-1] và [p+1, hi]
```

- Vì sao phải **random pivot**: pivot cố định (đầu/cuối) gặp mảng đã sort → mỗi lần chia
  chỉ tách được 1 phần tử → O(n²). Đây là câu hỏi follow-up kinh điển.
- **Quickselect** (tìm phần tử thứ k, O(n) trung bình): sau partition chỉ đệ quy **một phía**
  chứa vị trí k — dùng cho Kth Largest thay heap.

### Mergesort
```cpp
// merge 2 nửa đã sort: hai con trỏ i, j, lấy phần tử nhỏ hơn bỏ vào mảng tạm
// dùng <= khi bằng nhau (lấy bên trái trước) → STABLE
```
- Chia đôi đến khi ≤ 1 phần tử, merge ngược lên. Là nền của "merge two sorted arrays/lists".
- Trên **linked list** mergesort là lựa chọn tự nhiên (Sort List 148): merge không cần mảng phụ.

### Heapsort
> Build max-heap O(n) (A3), rồi n lần: swap đỉnh với phần tử cuối, thu hẹp heap, sift_down đỉnh.
- In-place O(1) extra — điểm bán duy nhất so với mergesort; thực tế chậm hơn quicksort vì cache-unfriendly.

## D. Linked list & circular buffer từ đầu

Singly list (node, dummy, reverse, fast/slow) đã có ở [06_linked_list.md](06_linked_list.md).
Phần này bổ sung hai thứ hay bị hỏi ở dạng "implement":

### D1. Doubly linked list (nền của LRU)
```cpp
struct Node { int key, val; Node *prev, *next; };
// Dùng 2 dummy head/tail nối sẵn với nhau → insert/remove KHÔNG có case biên:
// remove(n):        n->prev->next = n->next; n->next->prev = n->prev;
// insertAfter(h,n): n->prev = h; n->next = h->next; h->next->prev = n; h->next = n;
```
Vì sao dummy cả 2 đầu: mọi node thật luôn có prev và next ≠ null → 2 dòng remove không cần if.

### D2. Circular buffer / Design Circular Queue (622)
```cpp
struct CircularQueue {
    vector<int> a; int head = 0, count = 0;   // tail suy ra: (head + count) % a.size()
    // enqueue: full? false : a[(head + count) % a.size()] = x, count++
    // dequeue: empty? false : head = (head + 1) % a.size(), count--
};
```
- Lưu `count` thay vì (head, tail) trần: phân biệt được **đầy vs rỗng** (cả hai đều head == tail).
- Mọi op O(1), bộ nhớ cố định — nói được ứng dụng thật (ring buffer trong producer/consumer) là điểm cộng.

## Pitfall C++ hay gặp

- **Rehash phải tính lại bucket của mọi phần tử** — index cũ `h % oldSize` vô nghĩa với size mới; và rehash làm **iterator/reference vào bucket cũ chết hết**.
- Hash âm: `key % n` ra **âm** với key âm trong C++ → chuẩn hóa `((key % n) + n) % n`.
- Heap: nhầm công thức index (con `2i+1, 2i+2` cho 0-based; `2i` chỉ đúng khi 1-based); sift_down quên chọn con **nhỏ hơn** trước khi so với cha.
- LRU: quên move-to-front trong `get`; evict xóa list mà quên xóa map (hoặc ngược lại) → map giữ iterator dangling.
- RandomizedSet: xóa xong quên sửa index của phần tử bị swap; hoặc xóa chính phần tử cuối → swap với chính nó, phải xử lý được.
- Quicksort: pivot cố định + input đã sort → O(n²); đệ quy cả hai phía trong quickselect làm mất O(n).
- BST delete case 2 con: chép giá trị successor xong phải **xóa successor trong cây phải**, không phải xóa key gốc lần nữa.
- `new` không đi kèm `delete` trong phỏng vấn thường được bỏ qua, nhưng **chủ động nói ra** ("production tôi sẽ dùng `unique_ptr`") là điểm cộng.

## Liên hệ

- Min-heap A3 là phần "bên trong" của `priority_queue` ở [10_heap.md](10_heap.md); heapsort và quickselect thay thế nhau trong bài Top-K.
- Union-Find A5 dùng trực tiếp cho connected components / cycle detection ở [08_graph.md](08_graph.md).
- Trie A4 phục vụ các bài prefix/word search ở [03_string.md](03_string.md).
- Partition & quickselect nối với [04_binary_search.md](04_binary_search.md) (sorting là prerequisite của binary search).
- Doubly linked list D1 là mảnh ghép của LRU; kỹ thuật dummy node gốc ở [06_linked_list.md](06_linked_list.md).
