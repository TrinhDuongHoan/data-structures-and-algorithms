#include<bits/stdc++.h>
using namespace std;
#define duonghoan21 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
const int maxn = 1e6;

struct Node{
    int data;
    Node* pNext;
};

struct Linked_List{
    Node* pHead;
    Node* pTail;
    Linked_List () {
        pHead = NULL;
        pTail = NULL;
    }
    Node* createNode(int data){
        Node* p = new Node;
        if(p == NULL) {
            cout << "Error\n";
            return NULL;
        }
        p->data = data;
        p->pNext = NULL;
        return p;
    }
    void push_Head(int data){
        Node* p = createNode(data);
        if (p == NULL) return;
        if(pHead == NULL) pHead = pTail = p;
        else{
            p->pNext = pHead;
            pHead = p;
        }
    }
    void push_Tail(int data){
        Node* p = createNode(data);
        if(p == NULL) return ;
        if(pHead == NULL) pHead = pTail = p;
        else{
            pTail->pNext = p;
            pTail = p;
        }
    }
    Node* findNode(int data){
        Node* p = pHead ;
        while (p != NULL){
            if(p->data == data) return p;
            p = p->pNext;
        }
        return NULL;
    }
    void pushAfterNode(Node*q,int data){
        Node* p = createNode(data);
        if(p == NULL) return;
        if(q != NULL){
            p->pNext = q->pNext;
            q->pNext = p;
            if (q == pTail) pTail = p;
        }
        else push_Head(data);
    }
    void removeHead(){
        if(pHead == NULL) return;
        Node* q = pHead;
        pHead = q->pNext;
        free(q);
    }
    void removeAfterNode(Node* q){
        if (q == NULL || q->pNext == NULL) return;
        Node* p = q->pNext;
        q->pNext = p->pNext;
        if(p == pTail) pTail = q;
        free(p);
    }
    void removeList(){
        Node* p;
        while(pHead != NULL){
            p = pHead;
            pHead = pHead->pNext;
            free(p);
        }
        pTail = NULL;
    }
    int countNode(){
        Node* p = pHead;
        int count = 0;
        while(p != NULL){
            count++;
            p = p->pNext;
        }   
        return count;
    }
    void sortList(){
        for(Node* p = pHead; p != NULL; p = p->pNext){
            for(Node* q = p->pNext; q != NULL; q = q->pNext ){
                if (p->data > q->data){
                    int tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        }
    }
    void display(){
        Node* p = pHead;
        while(p != NULL){
            cout << p->data << " ";
            p = p->pNext;
        }
        cout << "\n";
    }
};

int main(){
    duonghoan21
    freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
    Linked_List L;
    L.push_Head(10);
    L.push_Tail(20);
    L.push_Head(15);
    L.sortList();
    L.display();
    Node* q = L.findNode(10);
    L.pushAfterNode(q,100);
    L.removeHead();
    L.removeAfterNode(L.findNode(100));
    L.display();
    L.removeList();
    L.push_Head(10);
    L.display();
    cout << L.countNode();
    return 0;
}