#include<stdio.h>
#include<stdlib.h>

const int maxn = 105;

int Edge[maxn][maxn];
int way[maxn];

struct Node{
    int data;
    Node* pNext;
};

struct Queue{
    Node* front;
    Node* rear;
};

void Init(Queue &Q){
    Q.front = NULL;
    Q.rear = NULL;
}

int isEmpty(Queue Q){
    return Q.front == NULL ? 1:0;
}

void push(Queue &Q, int x){
    Node* p = new Node ;
    if(p == NULL) return;
    p->data = x;
    p->pNext = NULL;
    if(Q.front == NULL ) Q.front = Q.rear = p;
    else {
        Q.rear->pNext =p;
        Q.rear = p;
    }
}

int pop(Queue &Q){
    if (!isEmpty(Q)){
        int x = Q.front->data;
        Node* p = Q.front;
        Q.front = Q.front->pNext;
        if(isEmpty(Q)) Q.rear = NULL;
        delete p;
        return x;
    }
}

void nhap_doThi(int &n, int &m){
    printf("Nhap so dinh : ");scanf("%d",&n);
    printf("Nhap so canh : ");scanf("%d",&m);
    for(int i= 1,x,y; i <= m; ++i){
        printf("Nhap canh %d : ",i);
        scanf("%d%d",&x,&y);
        Edge[x][y] = 1;
//        Edge[y][x] = 1;
    }
}

int bfs(int u, int v,int n){
    Queue Q;
    int visited[maxn] = {0};
    Init(Q);
    push(Q,u);
    way[u] = 0;
    while(!isEmpty(Q)){
        int x = pop(Q);
        if(x == v) return 1;
        visited[x] = 1;
        for(int i = 1; i <=n; ++i ){
            if(!visited[i] && Edge[x][i]){
                way[i] = x;
                push(Q,i);
            }
        }
    }
    return 0;
}

void printfWay(int u){
    if(way[u] == 0) {
        printf("%d", u);
        return;
    }
    printfWay(way[u]);
    printf("->%d",u);
}

void Menu(){
    printf("-- Moi lua chon chuc nang --\n");
    printf("1. Nhap do thi\n");
    printf("2. Kiem tra duong di cua 2 dinh\n");
    printf("3. Thoat chuong trinh\n");
}

int main(){
    int n,m,x,y;
    int running = 1,choose;
    Menu();
    while(running){
        printf("Nhap lua chon : "); scanf("%d",&choose);
        switch(choose){
        case 1 :
            nhap_doThi(n,m);
            break;
        case 2:
            printf("Nhap hai dinh can kiem tra : "); scanf("%d%d", &x,&y);
            if(bfs(x,y,n)){
                printf("Co ton tai duong di\n");
                printfWay(y);
                printf("\n");
            }
            else printf("Khong ton tai duong di\n");
            break;
        case 3 :
            running = 0;
            break;
        }
    }
}
