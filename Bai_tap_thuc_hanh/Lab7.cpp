#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct MatHang{
    int maMH;
    char tenMH[12];
};

struct Node{
    MatHang data;
    Node* pNext;
};

struct Queue{
    int soluong;
    Node* front;
    Node* rear;
};

void Init(Queue &Q){
    Q.front = NULL;
    Q.rear = NULL;
    Q.soluong = 0;
}

int isEmpty(Queue Q){
    return Q.front == NULL ? 1 : 0;
}

void them_matHang(Queue &Q, MatHang x){
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

MatHang pop(Queue &Q){
    if (!isEmpty(Q)){
        MatHang x = Q.front->data;
        Node* p = Q.front;
        Q.front = Q.front->pNext;
        if(isEmpty(Q)) Q.rear = NULL;
        free(p);
        return x;
    }
}

void nhap1_MatHang(MatHang &mh){
    fflush(stdin);
    printf("Nhap ma mat hang : "); scanf("%d", &mh.maMH);
    fflush(stdin);
    printf("Nhap ten mat hang : "); gets(mh.tenMH);
}

void xuat1_MatHang(MatHang mh){
    printf("%d %s\n",mh.maMH, mh.tenMH);
}

void taoKhoHang(Queue &Q){
    MatHang x;
    printf("Nhap so luong mat hang : "); scanf("%d",&Q.soluong);
    for(int i= 1; i <= Q.soluong; ++i){
        printf("Mat hang thu %d\n", i);
        nhap1_MatHang(x);
        them_matHang(Q,x);
    }
}
void check_moiNhap(Queue Q){
    if (Q.rear == NULL){
        printf("Khong co mat hang nao trong kho\n");
        return;
    }
    xuat1_MatHang(Q.rear->data);
}

void check_chuanBiXuat(Queue Q){
    if(Q.front == NULL){
        printf("Khong co mat hang nao trong kho\n");
        return;
    }
    xuat1_MatHang(Q.front->data);
}


void check_HangTrongKho(Queue Q){
    Node* p = Q.front;
    while(p){
        xuat1_MatHang(p->data);
        p=p->pNext;
    }
}

void xuat_ToanBoKho(Queue &Q){
    MatHang x;
    Node* p = Q.front;
    while(!isEmpty(Q)){
        x = pop(Q);
        xuat1_MatHang(x);
    }
    printf("Da xuat het mat hang trong kho\n");
}

void Menu(){
    printf("-- Moi lua chon chuc nang --\n");
    printf("1. Nhap kho hang\n");
    printf("2. Xuat mot mat hang\n");
    printf("3. Xem mat hang chuan bi xuat\n");
    printf("4. Xem mat hang moi nhap\n");
    printf("5. Xem cac mat hang co trong kho\n");
    printf("6. Xuat toan bo kho hang\n");
    printf("7. Ket thuc chuong trinh\n");
}

int main(){
    Queue Q;
    Init(Q);
    int runnning =1, choose = 0;
    while(running){
        printf("Nhap lua chon : ");
        scanf("%d",&choose);
        switch(choose){
            case 1 :
                taoKhoHang(Q);
                break;
            case 2:
                printf("Nhap ma mat hang can xuat \n");
                break;
        }
    }
    return 0;
}
