#include <stdio.h>
#include <string.h>

#define MAX_SP 100
#define MAX_HD 20

typedef struct
{
    char ma[11];
    char ten[41];
    char dvt[11];
    float dongia;
    int sl;
} SanPham;

typedef struct
{
    char ma[11];
    char ten[41];
    int slmua;
    float dongia;
    float thanhtien;
} DongHoaDon;

SanPham ds[MAX_SP];
int n = 0;
int soHoaDon = 0;
float tongDoanhThu = 0;

int timTheoMa(char ma[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(ds[i].ma, ma) == 0)
            return i;
    }
    return -1;
}

void themSP()
{
    if (n >= MAX_SP)
    {
        printf("Danh sach day!\n");
        return;
    }
    SanPham sp;
    printf("Nhap ma sp: ");
    scanf("%s", sp.ma);
    if (strlen(sp.ma) == 0 || timTheoMa(sp.ma) != -1)
    {
        printf("Ma khong hop le hoac da ton tai!\n");
        return;
    }
    getchar();
    printf("Nhap ten sp: ");
    fgets(sp.ten, 40, stdin);
    sp.ten[strcspn(sp.ten, "\n")] = 0;
    printf("Nhap don vi tinh: ");
    scanf("%s", sp.dvt);
    do
    {
        printf("Nhap don gia: ");
        scanf("%f", &sp.dongia);
    } while (sp.dongia <= 0);
    do
    {
        printf("Nhap so luong: ");
        scanf("%d", &sp.sl);
    } while (sp.sl < 0);
    ds[n++] = sp;
    printf("Them thanh cong!\n");
}

void hienThi()
{
    if (n == 0)
    {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }
    printf("%-5s %-10s %-40s %-10s %-10s %-10s %-12s\n",
           "STT", "Ma", "Ten", "DVT", "Don gia", "SL", "Gia tri ton");
    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-10s %-40s %-10s %-10.2f %-10d %-12.2f\n",
               i + 1, ds[i].ma, ds[i].ten, ds[i].dvt,
               ds[i].dongia, ds[i].sl, ds[i].dongia * ds[i].sl);
    }
}

void capNhat()
{
    char ma[11];
    printf("Nhap ma sp can cap nhat: ");
    scanf("%s", ma);
    int idx = timTheoMa(ma);
    if (idx == -1)
    {
        printf("Khong tim thay!\n");
        return;
    }
    float giaMoi;
    int slThem;
    printf("Nhap don gia moi: ");
    scanf("%f", &giaMoi);
    printf("Nhap so luong nhap them: ");
    scanf("%d", &slThem);
    ds[idx].dongia = giaMoi;
    ds[idx].sl += slThem;
    printf("Cap nhat thanh cong!\n");
}

void xoaSP()
{
    char ma[11];
    printf("Nhap ma sp can xoa: ");
    scanf("%s", ma);
    int idx = timTheoMa(ma);
    if (idx == -1)
    {
        printf("Khong tim thay!\n");
        return;
    }
    for (int i = idx; i < n - 1; i++)
        ds[i] = ds[i + 1];
    n--;
    printf("Xoa thanh cong!\n");
}

void banHang()
{
    if (n == 0)
    {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }
    DongHoaDon hd[MAX_HD];
    int m = 0;
    char ma[11];
    while (1)
    {
        printf("Nhap ma sp (0 de ket thuc): ");
        scanf("%s", ma);
        if (strcmp(ma, "0") == 0)
            break;
        int idx = timTheoMa(ma);
        if (idx == -1)
        {
            printf("Khong tim thay!\n");
            continue;
        }
        if (ds[idx].sl == 0)
        {
            printf("San pham da het hang!\n");
            continue;
        }
        int slmua;
        printf("Nhap so luong mua: ");
        scanf("%d", &slmua);
        if (slmua > ds[idx].sl)
        {
            printf("Khong du hang!\n");
            continue;
        }
        ds[idx].sl -= slmua;
        hd[m].slmua = slmua;
        strcpy(hd[m].ma, ds[idx].ma);
        strcpy(hd[m].ten, ds[idx].ten);
        hd[m].dongia = ds[idx].dongia;
        hd[m].thanhtien = slmua * ds[idx].dongia;
        m++;
    }
    if (m == 0)
        return;
    float tong = 0;
    printf("===== HOA DON =====\n");
    printf("%-10s %-40s %-10s %-10s %-12s\n",
           "Ma", "Ten", "SL", "Don gia", "Thanh tien");
    for (int i = 0; i < m; i++)
    {
        printf("%-10s %-40s %-10d %-10.2f %-12.2f\n",
               hd[i].ma, hd[i].ten, hd[i].slmua,
               hd[i].dongia, hd[i].thanhtien);
        tong += hd[i].thanhtien;
    }
    if (tong >= 500000)
        tong *= 0.9;
    printf("Tong tien phai tra: %.2f\n", tong);
    soHoaDon++;
    tongDoanhThu += tong;
}

void sapHetHang()
{
    for (int i = 0; i < n; i++)
    {
        if (ds[i].sl < 5)
        {
            printf("%s - %s - SL: %d\n", ds[i].ma, ds[i].ten, ds[i].sl);
        }
    }
}

void sapXep()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ds[i].dongia > ds[j].dongia)
            {
                SanPham tmp = ds[i];
                ds[i] = ds[j];
                ds[j] = tmp;
            }
        }
    }
    hienThi();
}

void thongKe()
{
    printf("So mat hang: %d\n", n);
    float tongGiaTri = 0;
    float maxGia = 0;
    int idxMax = -1;
    for (int i = 0; i < n; i++)
    {
        tongGiaTri += ds[i].dongia * ds[i].sl;
        if (ds[i].dongia > maxGia)
        {
            maxGia = ds[i].dongia;
            idxMax = i;
        }
    }
    printf("Tong gia tri ton kho: %.2f\n", tongGiaTri);
    if (idxMax != -1)
    {
        printf("San pham co don gia cao nhat: %s - %.2f\n",
               ds[idxMax].ten, ds[idxMax].dongia);
    }
    printf("So hoa don da ban: %d\n", soHoaDon);
    printf("Tong doanh thu: %.2f\n", tongDoanhThu);
}

int main()
{
    int chon;
    do
    {
        printf("====== QUAN LY CUA HANG ======\n");
        printf("1. Them san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Tim san pham theo ma\n");
        printf("4. Cap nhat gia / nhap them hang\n");
        printf("5. Xoa san pham\n");
        printf("6. Ban hang va in hoa don\n");
        printf("7. Danh sach san pham sap het hang\n");
        printf("8. Sap xep theo don gia tang dan\n");
        printf("9. Thong ke\n");
        printf("0. Thoat\n");
        printf("==============================\n");
        printf("Chon: ");
        scanf("%d", &chon);
        switch (chon)
        {
        case 1:
            themSP();
            break;
        case 2:
            hienThi();
            break;
        case 3:
        {
            char ma[11];
            printf("Nhap ma sp: ");
            scanf("%s", ma);
            int idx = timTheoMa(ma);
            if (idx == -1)
                printf("Khong tim thay!\n");
            else
                printf("%s - %s - %s - %.2f - SL:%d\n",
                       ds[idx].ma, ds[idx].ten, ds[idx].dvt,
                       ds[idx].dongia, ds[idx].sl);
            break;
        }
        case 4:
            capNhat();
            break;
        case 5:
            xoaSP();
            break;
        case 6:
            banHang();
            break;
        case 7:
            sapHetHang();
            break;
        case 8:
            sapXep();
            break;
        case 9:
            thongKe();
            break;
        case 0:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);
    return 0;
}
