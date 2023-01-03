#include <iostream>
using namespace std;

struct Dugum
{
    int veri; //düðümün sayýsal deðeri
    Dugum* sonraki; //sonraki düðüme iþaretçi
};


struct Kuyruk {
    Dugum* bas; //kuyruðun baþýndaki elemanýn adresini tutar
    Dugum* son; //kuyruðun sonundaki elemanýn adresini tutar
    void olustur(); //baþlangýç için gereken tanýmlarý içerir
    void kapat(); //program bitiminde bellek iadesi yapar
    void ekle(int); //kuyruða yeni veri ekler
    int cikar(); //kuyruktan sýradaki elemaný çýkarýr
    bool bosMu(); //kuyruk boþ mu kontrol eder
    void yazdir();
};

struct Yigin {
    Kuyruk k1, k2; //yýðýn için kullanýlacak kuyruk deðiþkenleri
    void olustur(); //baþlangýç için gereken tanýmlarý içerir
    void kapat(); //program bitiminde bellek iadesi yapar
    void ekle(int); //kuyruða yeni veri ekler
    int cikar(); //kuyruktan sýradaki elemaný çýkarýr
    bool bosMu(); //kuyruk boþ mu kontrol eder
    int tepe(); //yýðýnýn tepesindeki elemaný okur
    void yazdir(); //yýðýn elemanlarýný sýrayla ekrana yazar  
};

void yiginCikar(Yigin *s);

void siraliEkle(Yigin *s, int x);

void siraliYazdir(Yigin* s);

int main()
{
    Yigin* y = new Yigin();

    y->olustur();

    y->ekle(3);
    y->ekle(1);
    y->ekle(7);
    y->ekle(4);
    y->ekle(8);
   
    cout << "Orjinal yigin:"<< endl;
    cout << "\n";

    y->yazdir();

    cout << "\n";
    cout << "\n";
    
    cout << " --- yiginCikar fonksiyon cagirisi --- "<< endl ;
  
    cout << "\n";
    cout << "\n";

    cout << "Sirali yigin:" << endl;
    cout << "\n";

    yiginCikar(y);
    siraliYazdir(y);

}

void Kuyruk::olustur()
{
    bas = NULL;
    son = NULL;
}

void Kuyruk::ekle(int Yeni)
{
    Dugum* YeniDugum = new Dugum();
    YeniDugum->veri = Yeni;
    YeniDugum->sonraki = NULL;

    if (bas == NULL)
    {
        bas = YeniDugum;
        son = bas;
    }
    else
    {
        son->sonraki = YeniDugum;

        son = YeniDugum;
    }
}

void Kuyruk::kapat()
{
    Dugum* p;
    while (bas)
    {
        p = bas;
        bas = bas->sonraki;
        delete p;
    }
}

int Kuyruk::cikar()
{
    Dugum* UstDugum;
    int Gecici;
    UstDugum = bas;
    bas = bas->sonraki;
    Gecici = UstDugum->veri;
    delete UstDugum;

    return Gecici;
}

bool Kuyruk::bosMu()
{
    return bas == NULL;
}

void Kuyruk::yazdir()
{
    Dugum* yenidugum = bas;
    while (yenidugum)
    {
        cout << yenidugum->veri << " ";
        yenidugum = yenidugum->sonraki;
    }
}


void Yigin::olustur()
{
    k1.olustur();

    k2.olustur();
}

void Yigin::kapat()
{
    Dugum* p;

    while (k1.bas)
    {
        p =k1.bas;

        k1.bas = k1.bas->sonraki;

        delete p;
    }
}
   
void Yigin::ekle(int x)
{

    k2.ekle(x);
    
    while (!k1.bosMu()) 
    {
        k2.ekle(k1.bas->veri);
        k1.cikar();
    }

    Kuyruk temp = k1;
    k1 = k2;
    k2 = temp;
}

int Yigin::cikar()
{

    if (k1.bosMu())
    {
        cout << "BOÞ!!";
        return -1;
    }

    return k1.cikar();

}

bool Yigin::bosMu()
{
    return k1.bosMu();
}

int Yigin::tepe()
{
    if (k1.bosMu()) 
    {
        return -1;
    }
       
    return k1.bas->veri;

}

void Yigin::yazdir()
{
    k1.yazdir();
}

void siraliYazdir(Yigin*  s)
{
    while (!s->bosMu())
    {
        cout << s->tepe() << " ";
        s->cikar();
    }
    cout << endl;
}

void yiginCikar(Yigin *s)
{
    if (!s->bosMu())
    {
        int x = s->cikar();

        yiginCikar(s);

        siraliEkle(s, x);
    }
    
}

void siraliEkle(Yigin *s, int x )
{
    if (s->bosMu() || x > s->tepe())
    {
        s->ekle(x);
    }
    else
    {
        int temp = s->cikar();

        siraliEkle(s, x);

        s->ekle(temp);
    } 
}



