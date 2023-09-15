/*
    Author : Trinh Duong Hoan
    Created : 12/09/2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 100

// -------------------------------- Declare (Phần khai báo) ----------------------------

typedef struct
{
    char Name[256];
    char Meaning[512];
} WORD;

// -------------------------------- Function (Các hàm xử lí) ---------------------------

// Hàm khởi tạo một từ
void init(WORD &a, char w[], char m[])
{
    strcpy(a.Name, w);
    strcpy(a.Meaning, m);
}
// 1. Hàm ghi một từ
void inWORD(WORD &x)
{
    printf("Nhap ten cua tu : ");
    scanf("%s", x.Name);
    fflush(stdin);
    printf("NHap nghia cua tu : ");
    scanf("%s", x.Meaning);fflush(stdin);
}
// Hàm xuất một từ
void outWORD(WORD x)
{
    printf("%s : %s \n", x.Name, x.Meaning);
}
// Hàm xuất mảng
void outArray(WORD Array[], int lenArray)
{
    for (int i = 0; i < lenArray; ++i)
    {
        outWORD(Array[i]);
    }
}
// Hàm đổi vị trí
void swap(WORD &a, WORD &b)
{
    WORD tmp = a;
    a = b;
    b = tmp;
}
// Hàm sắp xếp theo tên
void sortName(WORD Array[], int lenArray)
{
    for (int i = 0; i < lenArray; ++i)
    {
        for (int j = lenArray - 1; j > i; j--)
        {
            if (strcmp(Array[j].Name, Array[j - 1].Name) < 0)
            {
                swap(Array[j], Array[j - 1]);
            }
        }
    }
}
// Hàm tìm kiếm theo tên
int searchName(WORD Array[], int lenArray, char x[])
{
    int left = 0, right = lenArray - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        int check = strcmp(Array[mid].Name, x);
        if (check == 0)
            return mid;
        else if (check < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
// Hàm ghi một từ vào tệp
void writeWord(char FileName[], WORD x)
{
    FILE *f = fopen(FileName, "ab");
    if (f == NULL)
    {
        printf("Open file is falied !!");
        return;
    }
    fwrite(&x, sizeof(WORD), 1, f);
    fclose(f);
}
// Hàm ghi một mảng vào tệp
void writeFile(char Filename[], WORD Array[], int lenArray)
{
    FILE *f = fopen(Filename, "ab");
    for (int i = 0; i < lenArray; ++i)
    {
        fwrite(&Array[i], sizeof(WORD), 1, f);
        // fwrite("\n",sizeof(char),1,f);
    }
    fclose(f);
}
// Hàm đọc một WORD trong file
void readWord(char fileName[])
{
    FILE *f = fopen(fileName, "rb");
    FILE *t = fopen("test.txt", "a");
    int cnt = 0;
    WORD tmp;
    while (fread(&tmp, sizeof(WORD), 1, f) == 1 && cnt < 1)
    {
        fprintf(t, "%s : %s\n", tmp.Name, tmp.Meaning);
        ++cnt;
    }
    fclose(f);
    fclose(t);
}
// Ham doc file
void readFile(char fileName[])
{
    FILE *f = fopen(fileName, "rb");
    FILE *t = fopen("test.txt", "w");
    WORD a;
    while (fread(&a, sizeof(WORD), 1, f) == 1)
    {
        fprintf(t, "%s : %s\n", a.Name, a.Meaning);
    }
    fclose(f);
    fclose(t);
}
// Hàm cập nhật meaning của 1 word
void updateWord(char fileName[], char name[], char newMean[])
{
    FILE *f = fopen(fileName, "rb+");
    char tmp[] = "cc.bin";
    WORD a;
    while (fread(&a, sizeof(WORD), 1, f) == 1)
    {
        if (strcmp(a.Name, name) == 0)
            strcpy(a.Meaning, newMean);
        writeWord(tmp, a);
    }
    fclose(f);
    remove(fileName);
    rename(tmp, fileName);
}
// Hàm xóa một word trong tệp
void removeWord(char fileName[], char name[])
{
    FILE *f = fopen(fileName, "rb+");
    char tmp[] = "cc.bin";
    WORD a;
    while (fread(&a, sizeof(WORD), 1, f) == 1)
    {
        if (strcmp(a.Name, name) == 0)
            continue;
        writeWord(tmp, a);
    }
    fclose(f);
    remove(fileName);
    rename(tmp, fileName);
}
void Menu()
{
    printf("\n-------------------- Lua chon chuc nang -------------------- \n");
    printf("1. Nhap thong tin tu mot Word\n");
    printf("2. Xuat thong tin tu mot Word\n");
    printf("3. Sap xep theo Name tang dan\n");
    printf("4. Tim kiem theo Name\n");
    printf("5. Ghi 1 word vao tep\n");
    printf("6. Ghi mot mang ten File\n");
    printf("7. Doc file\n");
    printf("8. Doc 1 word tu tep\n");
    printf("9. Cap nhap meaning cua mot word\n");
    printf("10 .Xoa mot tu khoi tep\n");
    printf("11. Thoat chuong trinh\n");
}
int main()
{
    int test;
    WORD Array[maxn];
    char s[maxn], m[maxn];
    char out[] = "output.bin";
    int lenArray = 0;
    int running = 1;
    Menu();
    while (running)
    {
        scanf("%d", &test);
        switch (test){
            case 1:{
                inWORD(Array[lenArray++]);
                break;
            }
            case 2:{
                int ans;
                do{
                    printf("Nhap vao vi tri can in : ");
                    scanf("%d", &ans);
                }while(ans < 0 || ans >= lenArray);

                outWORD(Array[ans]);
                break;
            }
            case 3:{
                sortName(Array,lenArray);
                printf("Mang sau khi duoc sap xep :\n ");
                outArray(Array, lenArray);
                break;
            }
            case 4:{
                char name[256];
                printf("Nhap vao Name can tim: ");
                scanf("%s", name);
                int pos = searchName(Array, lenArray, name);
                if(pos == -1) printf("Khong tim thay !!\n");
                else printf("Vi tri : %d\n", pos);
                break;
            }
            case 5:{
                WORD word;
                inWORD(word);
                writeWord(out, word);
                break;
            }
            case 6:{
                writeFile(out, Array, lenArray);
                break;
            }
            case 7:{
                readFile(out);
                break;
            }
            case 8:{
                readWord(out);
                break;
            }
            case 9:{
                char name[256], newMean[512];
                printf("Nhap NAME can doi nghia: ");
                scanf("%s", name);
                printf("Nhap nghia moi cho NAME: ");
                scanf("%s", newMean);
                updateWord(out, name, newMean);
                break;
            }
            case 10:{
                char del[256];
                printf("Nhap NAME can xoa: ");
                scanf("%s", del);
                removeWord(out, del);
                break;
            }
            default:{
                running = 0;
                break;
            }

        }
    }
    return 0;
}
