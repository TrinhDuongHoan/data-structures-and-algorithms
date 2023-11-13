#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct item{
    char maSV[20];
    char name[20];
    double diem;
};

struct Node{
    item data;
    Node* pLeft;
    Node* pRight;
};
typedef Node* Tree;

void InitTree(Tree &T){
    T = NULL;
}

void NhapSV(item &SV){
    fflush(stdin);
    printf("Nhap ma sinh vien : ");scanf("%s", &SV.maSV); fflush(stdin);
    printf("Nhap ten sinh vien : "); gets(SV.name);
    printf("Nhap diem cua sinh vien : "); scanf("%lf", &SV.diem);
}

void XuatSV(item SV){
    printf("|%20s|%20s|%10.1lf|\n", SV.maSV, SV.name, SV.diem);
}

Node* TaoNode(item SV){
    Node* p = new Node;
    if(p == NULL) return p;
    p->data = SV;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}

int SoSanh(char sv1[], char sv2[]){
    if (strlen(sv1) == strlen(sv2)){
        return strcmp(sv1,sv2);
    }
    else if (strlen(sv1) < strlen(sv2)){
        return -1;
    }
    else return 1;

}

int ThemNode(Tree &T, Node* p ){
    if(p == NULL) return 0;
    if (T == NULL) T = p;
    else {
        if (SoSanh(T->data.maSV,p->data.maSV) > 0){
            ThemNode(T->pLeft, p);
        }
        else if (SoSanh(T->data.maSV,p->data.maSV) < 0){
            ThemNode(T->pRight, p);
        }
        else return 0;
    }
    return 1;
}

void TaoCay(Tree &T, int &n){
    item tmp;
    printf("Nhap so luong sinh vien : "); scanf("%d",&n);
    for(int i = 1; i <= n; ++i){
        NhapSV(tmp);
        if(ThemNode(T,TaoNode(tmp))){
            printf("Da them node vao cay !!\n");
        }
        else {
            printf("Node da ton tai hoac khong du bo nho !!\n");
            i--;
        }
    }
}

void XuatCay(Tree T){
    if (T != NULL){
        if (T->pLeft != NULL){
            XuatCay(T->pLeft);
        }
        XuatSV(T->data);
        if (T->pRight != NULL){
            XuatCay(T->pRight);
        }
    }
}

void Menu(){
    printf("-- Moi lua chon chuc nang --\n");
    printf("1. Tao cay\n");
    printf("2. Xuat cay\n");
    printf("3. Tinh chieu cao cua cay\n");
    printf("4. Dem so nut la cua cay\n");
    printf("5. Chen mot node vao cay\n");
    printf("6. Tim kiem node\n");
    printf("7. Xoa mot node\n");
    printf("8. Thoat chuong trinh\n");
}

int max( int a, int b){
    if (a > b) return a;
    return b;
}

int ChieuCaoCay(Tree T){
    if (T == NULL){
        return 0;
    }
    return max(ChieuCaoCay(T->pLeft), ChieuCaoCay(T->pRight)) + 1;
}

int SoNutLa(Tree T){
    if (T == NULL) return 0;
    else {
        if (T->pLeft == NULL && T->pRight == NULL) return 1;
        return SoNutLa(T->pLeft)+SoNutLa(T->pRight);
    }
}

void TimKiem(Tree T, char maSV[]){
    if (T == NULL) {
        printf("Khong tim thay thong tin sinh vien co ma %s ! \n", maSV);
        return;
    }
    if (strcmp(T->data.maSV, maSV) == 0){
        printf("Thong tin sinh vien : \n");
        printf("|%20s|%20s|%10s|\n","MaSV","Ho ten", "Diem");
        XuatSV(T->data);
        return ;
    }
    else if (strcmp(T->data.maSV,maSV) < 0) TimKiem(T->pRight, maSV);
    else TimKiem(T->pLeft, maSV);
}

void TimThayThe(Tree &p, Tree &q){
    if(q->pLeft) TimThayThe(p,q->pLeft);
    else{
        p->data = q->data;
        p = q;
        q = q->pRight;
    }
}


void XoaNode(Tree &T, char maSv[]){
    if(T != NULL){
        if (SoSanh(T->data.maSV, maSv) > 0) XoaNode(T->pLeft, maSv);
        else if (SoSanh(T->data.maSV,maSv) < 0) XoaNode(T->pRight,maSv);
        else{
            Node* p = T;
            if(T->pLeft == NULL) T = T->pRight;
            else if (T->pRight == NULL) T = T->pLeft;
            else {
                Node* q = T->pRight;
                TimThayThe(p,q);
            }
            delete p;
        }
    }
}


int main(){
    int run = 1,choose;
    Tree T;
    InitTree(T);
    int n;
    item SV;
    char ma[20];
    Menu();
    while(run){
        fflush(stdin);
        printf("Nhap lua chon : "); scanf("%d",&choose);
        switch(choose){
        case 1 :
            TaoCay(T,n);
            break;
        case 2 :
            printf("Danh Sach Sinh Vien \n");
            printf("|%20s|%20s|%10s|\n","MaSV","Ho ten", "Diem");
            XuatCay(T);
            break;
        case 3 :
            printf("Chieu cao cua cay la : %d\n" , ChieuCaoCay(T));
            break;
        case 4:
            printf("So nut la cua cay : %d\n", SoNutLa(T));
            break;
        case 5:
            printf("Nhap thong tin cua node can chen\n");
            NhapSV(SV);
            ThemNode(T,TaoNode(SV));
            break;
        case 6:
            printf ("Nhap ma sinh vien can tim kiem : ");
            fflush(stdin);
            scanf("%s",&ma );
            TimKiem(T,ma);
            break;
        case 7 :
            printf("Nhap ma sinh vien can xoa : ");
            fflush(stdin);
            scanf("%s", &ma);
            XoaNode(T,ma);
            break;
        case 8 :
            run = 0;
            break;
        }
    }
    return 0;
}
