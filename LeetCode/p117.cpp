/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        Node temp(0, 0, 0, root);
        while (Node* p = temp.next) {
            temp.next = nullptr;
            Node* below = &temp;
            for (; p; p = p->next) {
                for (Node* son : {p->left, p->right}) if (son) {
                    below->next = son;
                    below = son;
                }
            }
        }
        return root;
    }
};
