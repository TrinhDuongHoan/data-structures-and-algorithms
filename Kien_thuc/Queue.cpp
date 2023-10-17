#include <bits/stdc++.h>
using namespace std;
#define duonghoan21 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
const int maxn = 1e6;

struct Node
{
    int data;
    Node *pNext;
};

struct Queue
{
    Node *front;
    Node *rear;
    void init()
    {
        front = NULL;
        rear = NULL;
    }
    int isEmpty()
    {
        if (rear == NULL)
            return 1;
        return 0;
    }
    void push(int data)
    {
        Node *p = new Node;
        p->pNext = NULL;
        p->data = data;
        if (rear == NULL)
            rear = front = p;
        else
        {
            rear->pNext = p;
            rear = p;
        }
    }
    int pop()
    {
        if (front == NULL)
            return -1;
        else
        {
            int x;
            Node *p = front;
            x = p->data;
            front = p->pNext;
            if (p == rear)
                rear = NULL;
            free(p);
            return x;
        }
    }
    void display()
    {
        Node *p = front;
        while (p != NULL)
        {
            cout << p->data << " ";
            p = p->pNext;
        }
        cout << endl;
    }
};

int main()
{
    duonghoan21
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    Queue q;
    q.init();
    q.push(10);
    q.push(15);
    cout << q.pop();
    q.display();
    return 0;
}