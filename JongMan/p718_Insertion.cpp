#include<set>
#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
 
int n, shifted[50000];
int A[50000];
 
typedef int KeyType;
 
struct Node {
    KeyType key;
    int priority, size;
    Node *left, *right;
 
    Node(const KeyType& _key) : key(_key), priority(rand()),
        size(1), left(NULL), right(NULL) {
    }
    void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
    void setRight(Node* newRight) { right = newRight; calcSize(); }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};
 
Node* lowerBound(Node* root, KeyType key) {
    if (root == NULL) return NULL;
    if (root->key < key) return lowerBound(root->right, key);
    Node* ret = lowerBound(root->left, key);
    if (!ret) ret = root;
    return ret;
}
 
bool exists(Node* root, KeyType key) {
    Node* node = lowerBound(root, key);
    return node != NULL && node->key == key;
}
 
Node* kth(Node* root, int k) {
    int ls = (root->left ? root->left->size : 0);
    int rs = (root->right ? root->right->size : 0);
    if (k <= ls) return kth(root->left, k);
    if (k == ls + 1) return root;
    return kth(root->right, k - ls - 1);
}
 
int countLessThan(Node* root, KeyType key) {
    if (root == NULL) return 0;
    if (root->key >= key)
        return countLessThan(root->left, key);
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
}
 
typedef pair<Node*, Node*> NodePair;
 
NodePair split(Node* root, KeyType key) {
    if (root == NULL) return NodePair(NULL, NULL);
    // 루트가 key 미만이면 오른쪽의 일부를 잘라낸다
    if (root->key < key) {
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    // 루트가 key 이상이면 왼쪽의 일부를 잘라낸다
    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}
 
Node* insert(Node* root, Node* node) {
    if (root == NULL) return node;
    if (root->priority < node->priority) {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if (node->key < root->key)
        root->setLeft(insert(root->left, node));
    else
        root->setRight(insert(root->right, node));
    return root;
}
 
Node* merge(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
 
    if (a->priority < b->priority) {
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}
 
Node* erase(Node* root, KeyType key) {
    if (root == NULL) return root;
    // root 를 지우고 양 서브트립을 합친 뒤 반환한다
    if (root->key == key) {
        Node* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if (key < root->key)
        root->setLeft(erase(root->left, key));
    else
        root->setRight(erase(root->right, key));
    return root;
}
void solve() {
    Node* candidates = NULL;
    for (int i = 0; i < n; i++)
        candidates = insert(candidates, new Node(i + 1));
    //뒤에서부터 A[]를 채워나간다.
    for (int i = n - 1; i >= 0; --i) {
        //후보 중 이 수보다 큰 수가 larger개 있다.
        int larger = shifted[i];
        Node*k = kth(candidates, i + 1- larger);
        A[i] = k->key;
        candidates = erase(candidates, k->key);
    }
}
 
int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int cases;
    cin >> cases;
    while (cases--) {
 
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> shifted[i];
        solve();
        for (int i = 0; i < n; i++)
            cout << A[i] << " ";
        cout << "\n";
 
    }
    return 0;
}
