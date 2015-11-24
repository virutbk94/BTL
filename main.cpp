#include <NTL/ZZ.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include <openssl/sha.h>
using namespace std;
using namespace NTL;

static ZZ p,q,n,phiN,e,d,chuKy;
void RSA();
void TaoKhoa();
void Ky();
void XacThuc();

bool LuuKhoaCongKhai(char *tenfile);
bool LuuKhoaBiMat(char *tenfile);
bool LuuChuKy(char *tenfile);

bool LoadKhoaBiMat(char *tenfile);
bool LoadKhoaCongKhai(char *tenfile);
bool LoadChuKy(char *tenfile);

bool sha_256(char *path,char outputBuffer[65]);

char convToHex(int a);
void convToHex2048(ZZ a,char c[513]);
int convToInt(char c);
ZZ convToZZ(char *dulieubam);

void padding(char in[65],char out[513]);


int main()
{
    RSA();

}


bool LuuKhoaCongKhai(char *tenfile)
{
    ofstream out;
    out.open(tenfile,ios::out|ios::trunc);
    if(!out.is_open())
    {
        cout<<"Error"<<endl;
        return false;
    }
    else
    {
        out<<e;
        out<<endl;
        out<<n;
    }
    out.close();
    return true;
}

bool LuuKhoaBiMat(char *tenfile)
{
    ofstream out;
    out.open(tenfile,ios::out|ios::trunc);
    if(!out.is_open())
    {
        cout<<"Error"<<endl;
        return false;
    }
    else
    {
        out<<d;
        out<<endl;
        out<<n;
    }
    out.close();
    return true;
}

bool LuuChuKy(char *tenfile)
{
    ofstream out;
    out.open(tenfile,ios::out|ios::trunc);
    if(!out.is_open())
    {
        cout<<"Error"<<endl;
        return false;
    }
    else
    {
        out<<chuKy;
    }
    out.close();
    return true;
}

bool LoadKhoaBiMat(char *tenfile)
{
    ifstream in;
    in.open(tenfile);
    if(!in.is_open())
    {
        cout<<"Error"<<endl;
        return false;
    }
    else
    {
        in>>d;
        in.ignore();
        in>>n;
    }
    in.close();
    return true;
}

bool LoadKhoaCongKhai(char *tenfile)
{
    ifstream in;
    in.open(tenfile);
    if(!in.is_open())
    {
        cout<<"Error"<<endl;
        return false;
    }
    else
    {
        in>>e;
        in.ignore();
        in>>n;
    }
    in.close();
    return true;
}

bool LoadChuKy(char *tenfile)
{
    ifstream in;
    in.open(tenfile);
    if(!in.is_open())
    {
        cout<<"Error"<<endl;
        return false;
    }
    else
    {
        in>>chuKy;
    }
    in.close();
    return true;
}


bool sha_256(char *path,char outputBuffer[65])
{
    FILE *file = fopen(path, "rb");
    if(!file) return false;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    const int bufSize = 32768;
    unsigned char *buffer = (unsigned char *)malloc(bufSize);
    int bytesRead = 0;
    if(!buffer) return false;
    while((bytesRead = fread(buffer, 1, bufSize, file)))
    {
        SHA256_Update(&sha256, buffer, bytesRead);
    }
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[65] = 0;
    fclose(file);
    free(buffer);
    return true;
}

ZZ convToZZ(char *dulieubam)
{
    ZZ a = conv<ZZ>(0);
    for(int i=0; i<strlen(dulieubam); i++)
    {
        a = a*16 + convToInt(dulieubam[i]);
    }
    return a;
}

void convToHex2048(ZZ a,char c[513])
{
    ZZ t=a;
    for(int i=0;i<512;i++){
        c[511-i]=convToHex(t%16);
        t=t/16;
    }
    c[512]='\0';
}

char convToHex(int a)
{
    switch(toupper(a)){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'a';
        case 11: return 'b';
        case 12: return 'c';
        case 13: return 'd';
        case 14: return 'e';
        case 15: return 'f';
        default: return '0';
    }
}

int convToInt(char c){
    switch(toupper(c)){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default: return 0;
    }
}

void padding(char in[65],char out[513]){
    out[0]='0';
    out[1]='0';
    out[2]='0';
    out[3]='1';
    for(int i=4;i<446;i++){
        out[i]='f';
    }
    out[446]='0';
    out[447]='0';
    for(int i=0;i<65;i++){
        out[i+448]=in[i];
    }
}


void RSA()
{
    char* chon;
    bool check = true;
    while(check)
    {

        check = false;
        cout<<"Chon chuc nang"<<endl<<"1.Tao Khoa"<<endl<<"2.Ky len ban tin"<<endl<<"3.Xac thuc chu ky"
            <<endl<<"4.Ket thuc"<<endl;
        cin>>chon;
        cin.ignore();
        if(strcmp(chon,"1")==0)
        {
            TaoKhoa();
            check=true;
        }
        else if(strcmp(chon,"2")==0)
        {
            Ky();
            check=true;
        }
        else if(strcmp(chon,"3")==0)
        {
            XacThuc();
            check=true;
        }
        else if(strcmp(chon,"4")==0)
        {
            system("exit");
        }
        else
        {
            check = true;
        }
    }
}


void TaoKhoa()
{
    cout<<"Tao ngau nhien 2 so nguyen to lon p,q co chieu dai 1024 bits"<<endl;
    p = RandomPrime_ZZ(1024);
    cout<<"p = "<<p<<endl;
    q = RandomPrime_ZZ(1024);
    cout<<"q = "<<q<<endl;
    n = p*q;
    cout<<"n = "<<n<<endl;
    phiN = (p-1)*(q-1);
    cout<<"phiN = "<<phiN<<endl;
    cout<<"Chon khoa cong khai e"<<endl;
    cin>>e;
    cin.ignore();
    while(GCD(e,phiN)>1||e==0)
    {
        cout<<"e va phiN khong nguyen to cung nhau.Chon lai e"<<endl;
        cin>>e;
        cin.ignore();
    }
    cout<<"Chon e thanh cong!"<<endl;
    cout<<"e = "<<e<<endl;
    cout<<"Tinh d"<<endl;
    d = InvMod(e,phiN);
    cout<<"d = "<<d<<endl;
    cout<<"Luu khoa cong khai"<<endl;
    cout<<"Nhap ten file luu khoa cong khai \n";
    char tenfile[25];
    cin>>tenfile;
    cin.ignore();
    bool e;
    e = LuuKhoaCongKhai(tenfile);
    if(e==false) return;
    cout<<"Luu khoa bi mat"<<endl;
    cout<<"Nhap ten file luu khoa bi mat \n";
    cin>>tenfile;
    cin.ignore();
    e = LuuKhoaBiMat(tenfile);
    if(e==false) return;
    std::cout<<"Hoan thanh \n";
}

void Ky()
{
    cout<<"Chon file khoa bi mat: \n";
    char keyFile[30];
    cin>>keyFile;
    cin.ignore();

    cout<<"Load khoa bi mat \n";
    bool er = LoadKhoaBiMat(keyFile);
    if(er==false) return;
    cout<<"d = "<<d<<endl;
    cout<<"n = "<<n<<endl;
    cout<<"Load khoa thanh cong \n";

    cout<<"Chon ten du lieu can ky: \n";
    char dataFile[30];
    cin>>dataFile;
    cin.ignore();

    cout<<"Bam du lieu \n";
    char dulieubam[65];
    sha_256(dataFile,dulieubam);
    char dulieumahoa[512];
    padding(dulieubam,dulieumahoa);

    ZZ dl;
    dl = convToZZ(dulieumahoa);
    cout<<dulieumahoa<<endl;
    cout<<"Tao chu ky \n";
    chuKy = PowerMod(dl,d,n);
    char chuKyHex[513];
    convToHex2048(chuKy,chuKyHex);
    cout<<chuKyHex<<endl;
    cout<<"Tao chu ky thanh cong \n";

    cout<<"Luu chu ky \n";
    char tenfile[30];
    cout<<"Nhap ten file luu chu ky \n";
    cin>>tenfile;
    cin.ignore();
    LuuChuKy(tenfile);
}




void XacThuc()
{
    cout<<"Chon file chu ky: \n";
    char signedFile[30];
    cin>>signedFile;
    cin.ignore();

    cout<<"Load chu ky \n";
    bool er = LoadChuKy(signedFile);
    if(er==false) return;
    char chuKyHex[513];
    convToHex2048(chuKy,chuKyHex);
    cout<<"chu ky = "<<chuKyHex<<endl;
    cout<<"Load chu ky thanh cong \n";

    cout<<"Chon file cong khai: \n";
    char keyFile[30];
    cin>>keyFile;
    cin.ignore();

    cout<<"Load khoa cong khai \n";
    er = LoadKhoaCongKhai(keyFile);
    if(er==false) return;
    cout<<"e = "<<e<<endl;
    cout<<"n = "<<n<<endl;
    cout<<"Load khoa thanh cong \n";

    cout<<"Chon ten du lieu can xac thuc: \n";
    char dataFile[30];
    cin>>dataFile;
    cin.ignore();

    cout<<"Du lieu da duoc bam \n";
    char dulieubam[65];
    sha_256(dataFile,dulieubam);
    char dulieumahoa[512];
    padding(dulieubam,dulieumahoa);
    cout<<dulieumahoa<<endl;


    ZZ dl = convToZZ(dulieumahoa);

    cout<<"Giai ma chu ky: \n";
    ZZ dlGiaiMa = PowerMod(chuKy,e,n);
    cout<<"Giai ma chu ky thanh cong \n";
    char dlGiaiMaHex[513];
    convToHex2048(dlGiaiMa,dlGiaiMaHex);
    cout<<dlGiaiMaHex<<endl;


    if(dlGiaiMa==dl)
    {
        cout<<"Chu ky duoc xac thuc \n";
    }
    else
    {
        cout<<"Chu ky hoac du lieu bi thay doi \n";
    }
}

