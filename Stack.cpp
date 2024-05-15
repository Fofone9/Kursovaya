//#include "Header.h"
//struct Node {
//    Neterm* val;
//    Node* next;
//    Node(Neterm* v) {
//        val = v;
//        next = nullptr;
//    }
//};
//class AutomatStack
//{
//    Node* root;
//public:
//    AutomatStack() { root = nullptr; }
//    AutomatStack(NetermE* b) {
//        root = new Node(b);
//    }
//    AutomatStack(NetermP* b) {
//        root = new Node(b);
//    }
//    AutomatStack(NetermT* b) {
//        root = new Node(b);
//    }
//    AutomatStack(NetermPlus* b) {
//        root = new Node(b);
//    }
//    void push(NetermE* b) {
//        Node* node = new Node(b);
//        node->next = root;
//        root = node;
//    }
//    void push(NetermP* b) {
//        Node* node = new Node(b);
//        node->next = root;
//        root = node;
//    }
//    void push(NetermT* b) {
//        Node* node = new Node(b);
//        node->next = root;
//        root = node;
//    }
//    void push(NetermPlus* b) {
//        Node* node = new Node(b);
//        node->next = root;
//        root = node;
//    }
//    void push(NetermMult* b) {
//        Node* node = new Node(b);
//        node->next = root;
//        root = node;
//    }
//    Neterm* pop() {
//        Node* node = root;
//        root = root->next;
//        Neterm* answer = static_cast<Neterm*>(node->val);
//        return answer;
//    }
//    bool empty() {
//        return root == nullptr;
//    }
//};