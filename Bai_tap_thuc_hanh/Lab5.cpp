#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 100;

struct Book
{
    char tenSach[30];
    int soLuongTacGia;
    char tenTacGia[5][30];
    char nhaXuatBan[30];
    int namXuatBan;
};

Book a[maxn];

struct Node
{
    Book data;
    Node *pNext;
};

struct ThuVien
{
    Node *pHead;
    Node *pTail;
    int size;
};

struct Author
{
    char tenTacGia[30];
    int soLuongSach;
};
struct NodeAuthor
{
    Author data;
    NodeAuthor *pNext;
};

struct ListAuthor
{
    NodeAuthor *Head;
    NodeAuthor *Tail;
};

void InitAuthor(Author &X)
{
    X.soLuongSach = 0;
}

void InitListAuthor(ListAuthor &TG)
{
    TG.Head = TG.Tail = NULL;
}

void add_Author(ListAuthor &TG, char tenTacGia[], int soLuongSach)
{
    NodeAuthor *p = new NodeAuthor;
    if (!p)
        return;
    strcpy(p->data.tenTacGia, tenTacGia);
    p->data.soLuongSach = soLuongSach;
    p->pNext = NULL;
    if (TG.Head == NULL)
        TG.Head = TG.Tail = p;
    else
    {
        TG.Tail->pNext = p;
        TG.Tail = p;
    }
}

void display2(ListAuthor TG)
{
    NodeAuthor *q = TG.Head;
    while (q)
    {
        printf("Ten tac gia : %s\n", q->data.tenTacGia);
        printf("So luong Sach : %d\n", q->data.soLuongSach);
        q = q->pNext;
    }
}

void InitList(ThuVien &L)
{
    L.pHead = NULL;
    L.pTail = NULL;
    L.size = 0;
}

Node *createNode(Book A)
{
    Node *p = new Node;
    p->data = A;
    p->pNext = NULL;
    return p;
}

void Input(Book &A)
{
    fflush(stdin);
    printf("Nhap ten sach : ");
    gets(A.tenSach);
    do
    {
        printf("Nhap so luong tac gia : ");
        scanf("%d", &A.soLuongTacGia);
        if (A.soLuongTacGia > 5)
            printf("So luong tac gia khong hop le !!\n");
    } while (A.soLuongTacGia > 5);
    fflush(stdin);
    for (int i = 0; i < A.soLuongTacGia; ++i)
    {
        printf("Nhap tac gia thu %d : ", i + 1);
        gets(A.tenTacGia[i]);
        fflush(stdin);
    }
    printf("Nhap ten nha xuat ban : ");
    gets(A.nhaXuatBan);
    printf("Nhap nam xuat ban sach : ");
    scanf("%d", &A.namXuatBan);
    fflush(stdin);
}

void Output(Book A)
{
    printf("Ten sach : %s\n", A.tenSach);
    printf("Danh sach tac gia \n");
    for (int i = 0; i < A.soLuongTacGia; ++i)
    {
        printf("Tac gia thu %d : %s\n", i + 1, A.tenTacGia[i]);
    }
    printf("Nha xuat ban : %s\n", A.nhaXuatBan);
    printf("Nam xuat ban : %d\n", A.namXuatBan);
}

int findAuthor(ListAuthor &TG, char name[])
{
    NodeAuthor *p = TG.Head;
    while (p)
    {
        if (strcmp(p->data.tenTacGia, name) == 0)
        {
            p->data.soLuongSach++;
            return 1;
        }
        p = p->pNext;
    }
    return 0;
}

void add_Book(ThuVien &L, Book A)
{
    Node *q = createNode(A);
    if (q == NULL)
        return;
    if (L.pHead == NULL)
        L.pHead = L.pTail = q;
    else
    {
        L.pTail->pNext = q;
        L.pTail = q;
    }
}

void create_ThuVien(ThuVien &L)
{
    Book temp;
    printf("Nhap so luong sach : ");
    scanf("%d", &L.size);
    for (int i = 1; i <= L.size; ++i)
    {
        Input(temp);
        add_Book(L, temp);
    }
}
void display(ThuVien L)
{
    Node *p = L.pHead;
    int i = 1;
    while (p != NULL)
    {
        printf("----Thong Tin Sach Thu %d------\n", i++);
        Output(p->data);
        p = p->pNext;
    }
}

void write_Library_to_File(ThuVien L, const char *fileName)
{
    FILE *file = fopen(fileName, "wb");
    if (file == NULL)
    {
        printf("Khong mo duoc file!");
        return;
    }

    Node *p = L.pHead;
    while (p != NULL)
    {
        fwrite(&p->data, sizeof(Book), 1, file);
        p = p->pNext;
    }

    fclose(file);
    printf("\nGhi danh sach sach vao file thanh cong!\n");
}

void read_Library_from_File(ThuVien &L, char fileName[])
{
    FILE *file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("Khong mo duoc file!");
        return;
    }

    Book temp;
    while (fread(&temp, sizeof(Book), 1, file) == 1)
    {
        add_Book(L, temp);
    }
    display(L);
    fclose(file);
    printf("\nDoc danh sach sach tu file thanh cong!\n");
}

int count_SoSach_of_Tacgia(ThuVien TV, char name[])
{
    int cnt = 0;
    Node *p = TV.pHead;
    Book tmp;
    while (p)
    {
        tmp = p->data;
        for (int i = 0; i < tmp.soLuongTacGia; ++i)
        {
            if (!strcmp(name, tmp.tenTacGia[i]))
                cnt++;
        }
        p = p->pNext;
    }
    return cnt;
}

void soSach_xuatBan_trongNam(ThuVien TV, char tenNhaXB[], int namXB)
{
    int check = 0, cnt = 0;
    Node *p = TV.pHead;
    while (p)
    {
        Book temp = p->data;
        if (temp.namXuatBan == namXB && strcmp(temp.nhaXuatBan,tenNhaXB) == 0)
            a[cnt++] = temp, check = 1;
        p = p->pNext;
    }
    if (!check)
        printf("Nha xuat ban %s khong xuat ban sach nao trong nam %d\n", tenNhaXB, namXB);
    else
    {
        printf("---Danh sach nhung cuon sach nha xuat ban %s xuat ban trong nam %d---\n ", tenNhaXB, namXB);
        for (int i = 0; i < cnt; ++i)
        {
            printf("%d. %s\n", i+1,a[i].tenSach);
        }
    }
}
void deleteBooks(ThuVien &TV, char tenTacGia[], char filename[])
{
    Node *p = TV.pHead;
    Node *prev = NULL;
    while (p != NULL)
    {
        int ok = 0;
        for (int i = 0; i < p->data.soLuongTacGia; ++i)
        {
            if (strcmp(tenTacGia, p->data.tenTacGia[i]) == 0)
            {
                if (prev == NULL)
                    TV.pHead = p->pNext;
                else
                    prev->pNext = p->pNext;
                if (p == TV.pTail)
                    TV.pTail = prev;
                Node *temp = p;
                p = p->pNext;
                free(temp);
                ok = 1;
                break;
            }
        }
        if (!ok)
        {
            prev = p;
            p = p->pNext;
        }
    }
    write_Library_to_File(TV, filename);
}

void ThongKeSach(ThuVien TV, ListAuthor &TG, char filename[])
{
    Node *p = TV.pHead;
    while (p)
    {
        for (int i = 0; i < p->data.soLuongTacGia; ++i)
        {
            if (!findAuthor(TG, p->data.tenTacGia[i]))
                add_Author(TG, p->data.tenTacGia[i], 1);
        }
        p = p->pNext;
    }
    FILE *f = fopen(filename, "wb");
    NodeAuthor *q = TG.Head;
    while (q)
    {
        fwrite(&q->data, sizeof(Author), 1, f);
        q = q->pNext;
    }
    fclose(f);
}

void readThongKe1(ListAuthor &tmp, char filename[])
{
    FILE *f = fopen(filename, "rb");
    Author temp;
    while (fread(&temp, sizeof(Author), 1, f))
    {
        add_Author(tmp, temp.tenTacGia, temp.soLuongSach);
    }
    fclose(f);
}

void readThongKe2(ListAuthor &tmp, char filename[])
{
    FILE *f = fopen(filename, "rb+");
    Author temp;
    while (fread(&temp, sizeof(Author), 1, f))
    {
        add_Author(tmp, temp.tenTacGia, temp.soLuongSach);
    }
    fclose(f);
    display2(tmp);
}

void Menu()
{
    printf("----- MOI LUA CHON CHUC NANG -----\n");
    printf("1. Tao ThuVien Sach va ghi vao File\n");
    printf("2. Cho biet so luong sach cua mot tac gia bat ki\n");
    printf("3. Cho biet thong tin nhung quyen sach ma tac gia X xuat ban trong nam YYYY\n");
    printf("4. Xoa tat ca cac quyen sach cua tac gia X va ghi vao tep moi\n");
    printf("5. Thong ke so luong sach cua moi tac gia va ghi vao tep\n");
    printf("6. Doc du lieu thong ke tu cau 5 va xuat len man hinh\n");
    printf("7. Doc du lieu tu tep trong cau 1 va dua vao danh sach lien ket don\n");
    printf("8. Doc du lieu thong ke tu cau 5 va dua vao mot danh sach moi\n");
    printf("9. Doc du lieu tu tep trong cau 4\n");
    printf("10. Thoat chuong trinh\n");
}

int main()
{
    ThuVien library1, library2, library3;
    ListAuthor TG, temp1, temp2;
    char filename1[] = "library1.bin"; // file luu yeu cau 1
    char filename2[] = "library2.bin"; // file luu yeu cau 4
    char filename3[] = "Author.bin"; // file luu yeu cau 5

    InitListAuthor(TG), InitListAuthor(temp1), InitListAuthor(temp2);
    InitList(library1), InitList(library2), InitList(library3);
    
    int running = 1, choose;
    Menu();
    while (running)
    {
        printf("Moi nhap lua chon : ");
        scanf("%d", &choose);
        switch (choose)
        {
            case 1:
            {
                create_ThuVien(library1);
                write_Library_to_File(library1, filename1);
                break;
            }
            case 2:
            {
                char authorName[50];
                printf("Nhap ten tac gia can kiem tra : ");
                fflush(stdin);
                gets(authorName);
                int count1 = count_SoSach_of_Tacgia(library1, authorName);
                printf("So luong sach cua tac gia %s : %d\n", authorName, count1);
                break;
            }
            case 3:
            {
                char nhaXuatBan[50];
                int year;
                printf("Nhap ten nha xuat ban can kiem tra : ");
                fflush(stdin);
                gets(nhaXuatBan);
                printf("Nhap nam xuat ban : ");
                scanf("%d", &year);
                soSach_xuatBan_trongNam(library1, nhaXuatBan, year);
                break;
            }
            case 4:
            {
                char authorName3[50];
                printf("Nhap ten tac gia cua sach can xoa : ");
                fflush(stdin);
                gets(authorName3);
                deleteBooks(library1, authorName3, filename2);
                break;
            }
            case 5:
            {
                ThongKeSach(library1, TG, filename3);
                break;
            }
            case 6:
            {
                readThongKe2(temp1, filename3);
                break;
            }
            case 7:
            {
                read_Library_from_File(library2, "library1.bin");
                break;
            }
            case 8:
            {
                readThongKe1(temp2, filename3);
                break;
            }
            case 9:{
                read_Library_from_File(library3,filename2);
                break;
            }
            default:
            {
                running = 0;
                break;
            }
        }
    }
    return 0;
}