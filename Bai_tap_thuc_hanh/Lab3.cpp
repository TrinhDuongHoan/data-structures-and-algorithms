/*
    Author : Trinh Duong Hoan
    Created : 03/10/2023
*/
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* pNext;
};
struct List{
    Node* pHead;
    Node* pTail;
};
void Init(List &L){
    L.pHead = L.pTail = NULL;
}
int isEmpty(List L){
    return L.pHead == NULL;
}
Node* createNode(int data){
    Node* p = new Node;
    if (p == NULL) return p;
    p->data = data;
    p->pNext = NULL;
    return p;
}
void pushTail(List &L, int data){
    Node* p = createNode(data);
    if (p == NULL) return;
    if (isEmpty(L)) L.pHead=L.pTail=p;
    else{
        L.pTail->pNext = p;
        L.pTail = p;
    }
}
void createList(List &L,List &bk ,int &n){
    printf("Nhap so phan tu cua list : ");scanf("%d",&n);
    for(int i = 1,x; i <= n; ++i){
        printf("Nhap phan tu thu %d : ", i); scanf("%d",&x);
        pushTail(L,x);
        pushTail(bk,x);
    }
}

Node* findNode(List L,int data){
    Node* p = L.pHead;
    while(p != NULL){
        if (p->data == data) return p;
        p=p->pNext;
    }
    return NULL;
}
void removeHead(List &L){
        if(isEmpty(L)) return;
        Node* q = L.pHead;
        L.pHead = q->pNext;
        free(q);
    }
void removeNode(List &L,int data){
    if(L.pHead->data == data) removeHead(L);
    else{
        Node* q = L.pHead;
        while(q != L.pTail){
            if(q->pNext->data == data){
                Node* p = q->pNext;
                q->pNext = p->pNext;
                if(p == L.pTail) L.pTail = q;
                free(p);
                return;
            }
            q = q->pNext;
        }
    }
}
void List_reqA(List &L, List &A, int x) {
    Init(A);
    Node* p = L.pHead;
    Node* prev = NULL;
    while (p != NULL) {
        if (p->data >= x) {
            pushTail(A, p->data);
            if (prev == NULL) L.pHead = p->pNext;
            else prev->pNext = p->pNext;
            if (p == L.pTail) L.pTail = prev;
            Node* temp = p;
            p = p->pNext;
            free(temp);
        }
        else {
            prev = p;
            p = p->pNext;
        }
    }
}
void List_reqB(List L,List &B,List &C,int x){
    Init(B), Init(C);
    Node* p = L.pHead;
    while(p!=NULL){
        if (p->data<x) pushTail(B,p->data);
        else pushTail(C,p->data);
        p=p->pNext;
    }
}
void display(List L){
    Node*  p = L.pHead;
    while(p != NULL){
        printf("%d ", p->data);
        p=p->pNext;
    }
    printf("\n");
}
void writeFile_reqA(char filename[], List L, List A, int &lenL,int &lenA){
    FILE* f = fopen(filename,"wb+");
    Node* p = L.pHead;
    Node* q = A.pHead;
    int i = 0, j = 0;
    while(p != NULL){
        ++i;
        fwrite(&(p->data), sizeof(int), 1, f);
        p = p->pNext;
    }
    //fwrite("\n", sizeof(char),1,f);
    while(q != NULL){
        ++j;
        fwrite(&(q->data), sizeof(int), 1, f);
        q = q->pNext;
    }
    lenL = i;
    lenA = j;
    fclose(f);
}
void writeFile_reqB(char filename[],List L, List B, List C,int &lenL,int &lenB, int &lenC){
    FILE* f = fopen(filename, "wb+");
    Node* p = L.pHead;
    Node* q = B.pHead;
    Node* w = C.pHead;
    int i = 0, j = 0 , k = 0;
    while(p != NULL){
        ++i;
        fwrite(&(p->data), sizeof(int), 1, f);
        p = p->pNext;
    }
    //fwrite("\n", sizeof(char),1,f);
    while(q != NULL){
        ++j;
        fwrite(&(q->data), sizeof(int), 1, f);
        q = q->pNext;
    }
    //fwrite("\n", sizeof(char),1,f);
    while(w != NULL){
        ++k;
        fwrite(&(w->data), sizeof(int), 1, f);
        w = w->pNext;
    }
    lenL = i,lenB = j, lenC = k;
    fclose(f);
}
void readFile(char filename[],int len1, int len2){
    FILE* f = fopen(filename, "rb+");
    FILE* t = fopen("out.txt","w");
    if(f == NULL) return ;
    int val;
    int a[2] = {len1,len2};
    int cnt = 0, i = 0;
    while(fread(&val, sizeof(int), 1 , f) == 1){
        fprintf(t,"%d ",val);
        ++cnt;
        if (i < 2)
        {
            if(cnt == a[i]) {
                fprintf(t,"\n");
                cnt = 0;
                ++i;
            }
        }
    }
    fclose(f);
    fclose(t);
}
void readFile(char filename[],int len1, int len2, int len3){
    FILE* f = fopen(filename, "rb+");
    FILE* t = fopen("out.txt","w");
    if(f == NULL) return ;
    int a[3]= {len1,len2,len3};
    int cnt = 0, i = 0;
    int val;
    while(fread(&val, sizeof(int), 1 , f) == 1){
        ++cnt;
        fprintf(t,"%d ",val);
        if(i < 3){
            if(cnt == a[i]) {
                fprintf(t,"\n");
                cnt = 0;
                ++i;
            }
        }
    }
    fclose(f);
    fclose(t);
}
void Menu(){
    printf("--------- Moi nhap lua chon -----------\n");
    printf("1. Tao danh sach.\n");
    printf("2. In danh sach.\n");
    printf("3. Tao danh sach theo yeu cau a.\n");
    printf("4. Tao danh sach theo yeu cau b.\n");
    printf("5. Ghi danh sach cua yeu cau a vao file.\n");
    printf("6. Ghi danh sach cua yeu cau b vao file.\n");
    printf("7. Thoat chuon trinh\n");
}
int main(){
    char filename1[] = "linked_list1.bin";
    char filename2[] = "linked_list2.bin";
    List L,A,B,C, back_up;Init(L),Init(A), Init(B), Init(C),Init(back_up);
    int run = 1, choose,n, lenL,lenA,lenB,lenC,lenBK;
    Menu();
    while(run){
        printf("Nhap lua chon : ");
        scanf("%d", &choose);
        switch(choose){
            case 1:{
                createList(L,back_up,n);
                break;
            }
            case 2:{
                printf("List vua khoi tao :\n");
                display(L);
                break;
            }
            case 3:{
                printf("Yeu cau A\n");
                int x;
                printf("Nhap vao gia tri x: "); scanf("%d", &x);
                List_reqA(L, A, x);
                printf("List < x: ");
                display(L);
                printf("List >= x: ");
                display(A);
                break;
            }
            case 4:{
                printf("--Yeu cau B--\n");
                int x;
                printf("Nhap vao gia tri x: "); scanf("%d", &x);
                List_reqB(back_up, B, C, x);
                printf("List Ban Dau : ");
                display(back_up);
                printf("List < x: ");
                display(B);
                printf("List >= x: ");
                display(C);
                break;
            }
            case 5:{
                writeFile_reqA(filename1, L,A, lenL,lenA);
                readFile(filename1, lenL,lenA);
                break;
            }
            case 6:{
                writeFile_reqB(filename2, back_up,B,C,lenBK,lenB,lenC);
                readFile(filename2,lenBK,lenB,lenC);
                break;
            }
            default:{
                run = 0;
                break;
            }
        }
    }
    return 0;
}
