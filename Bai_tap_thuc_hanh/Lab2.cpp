/*
    Author : Trinh Duong Hoan
    Created : 24/09/2023
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>

const int maxn = 50;

struct SinhVien{
    int MSSV;
    char hoTen[maxn];
    char gioiTinh[maxn];
    char diaChi[maxn];
    double diemTB;
} ;
void swap(SinhVien &a, SinhVien &b) {
	SinhVien t = a;
	a = b;
	b = t;
}
void in1(SinhVien &a){
    printf("\nNhap MSSV : "); scanf("%d",&a.MSSV);fflush(stdin);
    printf("\nNhap ho ten : "); gets(a.hoTen);fflush(stdin);
    printf("\nNhap gioi tinh : "); gets(a.gioiTinh);fflush(stdin);
    printf("\nNhap dia chi : "); gets(a.diaChi);
    printf("\nNhap diem trung binh : "); scanf("%lf",&a.diemTB);
}
void out1(SinhVien a){
    printf("\n%-10d %-30s %-10s %-30s %10.2f", a.MSSV, a.hoTen, a.gioiTinh, a.diaChi, a.diemTB);
}
void inputArray(SinhVien a[], int &n){
    do{
        printf("Nhap so luong sinh vien : ");
        scanf("%d",&n);
    } while (n <= 0 || n >= maxn && printf("Khong hop le, nhap lai !!\n"));
    for (int i = 0 ; i < n; ++i) in1(a[i]);
}
void outputArray(SinhVien a[], int n){
    printf("\n%-10s %-30s %-10s %-30s %10s", "MSSV", "Ho Ten", "Gioi Tinh","Dia chi", "Diem TB" );
    for (int i = 0 ; i < n; ++i) out1(a[i]);
}
void sortDiemTB(SinhVien a[], int n){
    for(int i = 0 ; i < n; ++i){
        for(int j = n-1; j > i ; --j){
            if (a[j].diemTB<a[j-1].diemTB) swap(a[j],a[j-1]);
        }
    }
}
void sortName(SinhVien a[], int l, int r){
    if (l >= r) return ;
    int i = l, j = r;
    int mid = (l+r)/2;
    do{
        while(strcmp(a[i].hoTen,a[mid].hoTen) < 0) i++;
        while(strcmp(a[j].hoTen,a[mid].hoTen) > 0) j--;
        if (i <= j){
            swap(a[i],a[j]);
            i++,j--;
        }
    }while(i < j);
    if(l<j) sortName(a,l, j);
	if(i<r) sortName(a, i, r);

}
int searchMSSV(SinhVien a[], int n, int maso){
    for(int i = 0 ; i < n; ++i ){
        if (a[i].MSSV == maso) return i;
    }
    return -1;
}
void writeFile(char filename[], SinhVien a[], int n){
    FILE* f = fopen(filename, "wb");
    if (f == NULL) return;
    for(int i = 0 ; i < n; ++i) {
        fwrite(a+i,sizeof(SinhVien),1,f );
    }
    fclose(f);
}
void readFile(char filename[], SinhVien a[], int &n){
    FILE* f = fopen(filename,"rb");
    FILE* t = fopen("out.txt","w");
    if(f == NULL) return ;
    int i = 0;
    while(fread(a+i, sizeof(SinhVien),1,f) > 0 && i < maxn) {
        fprintf(t,"\n%d %s %s %s %.2f", a[i].MSSV, a[i].hoTen, a[i].gioiTinh, a[i].diaChi, a[i].diemTB);
        ++i;
    }
    n = i;
    fclose(f);
    fclose(t);
}
void updateInfor(char filename[]){
    FILE* f = fopen(filename,"rb+");
    if (f == NULL) return;
    SinhVien sv;
    char choose;
    int maso;
    while(1){
        rewind(f);
        printf("Co muon cap nhat thong tin khong ? (Y/N) : ");fflush(stdin);
        scanf("%c",&choose);
        choose = toupper(choose);
        if (choose == 'N') break;
        printf("MSSV can cap nhat : ");scanf("%d",&maso);
        while(fread(&sv, sizeof(SinhVien),1,f) > 0){
            if(sv.MSSV == maso){
                out1(sv);fflush(stdin);
                in1(sv);
                fseek(f,-sizeof(SinhVien),SEEK_CUR);
                fwrite(&sv,sizeof(SinhVien),1,f);
                fseek(f,sizeof(SinhVien),SEEK_CUR);
            }
        }
    }
    fclose(f);
}
void removeSV(char filename[], int mssv){
    FILE* f = fopen(filename,"rb+");
    if(f == NULL) return;
    SinhVien sv[maxn];
    int size;
    readFile(filename,sv,size);
    if (searchMSSV(sv,size,mssv) == -1) return;
    for(int i = searchMSSV(sv,size,mssv); i < size-1; ++i){
        sv[i] = sv[i+1];
    }
    size--;
    writeFile(filename, sv,size);
}
double findMaxDiemTB(FILE* f){
    double maximum = 0;
    SinhVien sv;
    while(fread(&sv,sizeof(SinhVien), 1,f) > 0){
        if (sv.diemTB > maximum) maximum = sv.diemTB;
    }
    rewind(f);
    return maximum;
}
void outMaxDiemTB(char filename[]){
    FILE* f = fopen(filename,"rb");
    if(f == NULL) return;
    double max_value = findMaxDiemTB(f);
    SinhVien tmp;
    while(fread(&tmp,sizeof(SinhVien),1,f) > 0){
        if (tmp.diemTB == max_value) out1(tmp);
    }
    fclose(f);
}
void menu() {
	printf("---------------------MENU---------------------");
	printf("\n1.Nhap cac sinh vien vao danh sach");
	printf("\n2.In danh sach sinh vien");
	printf("\n3.Xuat thong tin cua sinh vien co ma so X");
	printf("\n4.Sap xep danh sach sinh vien theo thu tu tang dan cua diem trung binh");
	printf("\n5.Sap xep danh sach sinh vien theo thu tu tang dan cua ho va ten");
	printf("\n6.Ghi danh sach sinh vien vao FILE");
	printf("\n7.Doc danh sach sinh vien tu FILE");
	printf("\n8.Sua thong tin cua mot sinh vien co ma X");
	printf("\n9.Xoa sinh vien co ma X");
	printf("\n10.Xuat ra cac sinh vien co diem trung binh cao nhat");
	printf("\n11.Exit");
}
int main(){
    SinhVien Array[maxn];
    char filename[]= "out.bin";
    int run = 1, n,choose, mssv,id;
    menu();
    while (run){
        printf("\nNhap lua chon cua ban : ");scanf("%d",&choose);
        switch (choose){
            case 1:
                inputArray(Array,n);
                break;
            case 2 :
                outputArray(Array,n);
                break;
            case 3:
                printf("\nNhap mssv cua sinh vien can tim : ");
                scanf("%d",&mssv);
                id = searchMSSV(Array,n,mssv);
                if(id == -1) printf("\nKhong tim thay !");
                else out1(Array[id]);
                break;
            case 4:
                sortDiemTB(Array,n);
                printf("Danh sach sau khi sap xep theo diem \n");
                outputArray(Array,n);
                break;
            case 5:
                sortName(Array,0,n-1);
                printf("Danh sach sau khi sap xep theo ten \n");
                outputArray(Array,n);
                break;
            case 6:
                writeFile(filename,Array,n);
                break;
            case 7:
                readFile(filename,Array,n);
                break;
            case 8:
                updateInfor(filename);
                break;
            case 9:
                printf("\nNhap mssv cua sinh vien can xoa : ");
                scanf("%d",&mssv);
                removeSV(filename,mssv);
                printf("Da xoa sinh vien co ma : %d",mssv);
                break;
            case 10:
                outMaxDiemTB(filename);
                break;
            default:
                run = 0;
                break;
        }
    }
    return 0;
}