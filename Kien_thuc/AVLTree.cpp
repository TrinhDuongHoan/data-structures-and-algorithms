#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int val) : data(val), height(1),left(NULL), right(NULL) {};
};

struct AVLTree{
public :
    AVLTree() : root(NULL){};

    int getHeight(Node* node){
        return (node ==  NULL ? 0 : node->height);
    }

    void InsertNode(int val){
        this->root = InsertNode(this->root,val);
    }

    void display(){
        display(this->root);
    }
    void deleteNode(int val){
        this->root = deleteNode(this->root,val);
    }

private:
    Node* root;
    Node* InsertNode(Node* node, int val){
        if(node == NULL){
            return new Node(val);
        }
        if(val == node->data) return node;
        else if(val > node->data) node->right = InsertNode(node->right,val);
        else node->left = InsertNode(node->left,val);

        node->height = 1+ max(getHeight(node->left),getHeight(node->right));

        int balance = getBalance(node);

        if(balance > 1){
            if(getBalance(node->left) < 0) node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (balance < -1){
            if(getBalance(node->right) > 0) node->right = rightRotate(node->right);
            return rightRotate(node);
        }

        return node;
    }

    Node* deleteNode(Node* node,int val){
        if(node == NULL) return NULL;

        if(val < node->data) node->left = deleteNode(node->left,val);
        else if (val > node->data) node->right = deleteNode(node->right,val);
        else{
            if(node->left == NULL || node->right == NULL){
                Node* temp = (node->left == NULL ? node->right : node->left);
                delete(node);
                node = temp;
            }
            else{
                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right,node->data);
            }
        }
        if(node == NULL) return NULL;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);

        if(balance > 1) {
            if(getBalance(node->left) < 0) node->left = leftRotate(node->left);
            return rightRotate(node);
        } else if (balance < -1) {
            if(getBalance(node->right) > 0) node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* leftRotate(Node* node){
        if(node == NULL) return NULL;
        Node* TNode = node->right;
        node->right = TNode->left;
        TNode->left = node;

        node->height = 1+max(getHeight(node->left),getHeight(node->right));
        TNode->height = 1+max(getHeight(TNode->left),getHeight(TNode->right));

        return TNode;
    }

    Node* rightRotate(Node* node){
        if(node == NULL) return NULL;
        Node* TNode = node->left;
        node->left = TNode->right;
        TNode->right = node;

        node->height = 1+max(getHeight(node->left),getHeight(node->right));
        TNode->height = 1+ max(getHeight(TNode->left),getHeight(TNode->right));

        return TNode;
    }

    Node* minValueNode(Node* node){
        if(node->left == NULL) return node;
        return minValueNode(node->left);
    }

    Node* maxValueNode(Node* node){
        if(node->right == NULL) return node;
        return maxValueNode(node->right);
    }

    int getBalance(Node* node){
        if(node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void display(Node* node){
        if(node == NULL) return ;
        display(node->left);
        display(node->right);
        cout <<"Node : " << node->data <<',' << "height : "<<node->height << '\n';
    }

};

int main(){
    AVLTree tree;
    tree.InsertNode(3);
    tree.InsertNode(2);
    tree.InsertNode(4);
    tree.InsertNode(1);
    tree.display();
    tree.deleteNode(3);
    tree.display();
}
