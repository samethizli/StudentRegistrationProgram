#include<iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include<time.h>

using namespace std;

class Ogrenci
{
	public:
		int yas;//Kisilerin yaslarini tutariz
		int kazanilan_puan;//Kisilerin puanlarini tutariz
		string isim;//Kisilerin isimlerini tutariz
		string soyisim;//Kisilerin soyisimlerini tutariz
		string verilen_cevaplar;//Kisilerin verdigi cevaplari tutariz
		string dogru_yanlis_durumu;//Kisilerin dogru yanlis durumunu tutariz
		
		Ogrenci()//Default constructor - Hic kullanmiyoruz. O sebeple ici bos
		{
		};
		
		~Ogrenci() 
		{
	    	//Destructor fonksiyonu olusturulan tum objeleri program kapaninca siler
	  	}
};

void dosyalariOkuyupOgrencileriOlustur(Ogrenci *ogrenciler)//Elimizde 50 isim ve 50 soyisim bulunmaktadir. Bu fonksiyonla 50x50 = 2500 kisi uretip listeye ekliyoruz
{	
	string isimler[50];//dosyadan 50 isim okumak icin dizi
	string soyisimler[50];//dosyadan 50 soyisim okumak icin dizi
	
	
	ifstream dosya;//Dosya islemleri icin ifstream kullaniyoruz.
	string isim;//Alacagimiz kelimeler icin bir string olusturuyoruz.
	dosya.open("isimler.txt");//Ad dosyasini aciyoruz
	for(int i=0;i<50;i++)//50 tane isim okuyacaz bu sebeple 50 olunca okumayi birakacaz
	{
		dosya>> isim;//Siradaki kelimeyi dosyadan isim stringine aliyoruz. 
		isimler[i] = isim; //IsimListesinde sayac kadar ilerleyip oraya bu ismi koyuyoruz
	}
	dosya.close();//Dosyayi kapatiyoruz
	
	string soyisim;
	dosya.open("soyisimler.txt");//Tek fark dosya adi soyad.txt olarak aliyoruz
	for(int j=0;j<50;j++)
	{
		dosya>> soyisim;
		soyisimler[j] = soyisim;
	}
	dosya.close();
	
	int sira = 0;
	int yas;
	string cevapFormu;
	
	for(int i=0;i<50;i++)//i ile 50 tane ismi sirayla geziyoruz
	{
		for(int j=0;j<50;j++)//j ile 50 tane soyismini sirayla geziyoruz
		{
				
			Ogrenci yeniOgrenci;
			yeniOgrenci.isim = isimler[i];
			yeniOgrenci.soyisim = soyisimler[j];
			
			yas = rand() % 43 +18;
			yeniOgrenci.yas = yas;
			
			cevapFormu = "XXXXXXXXXX";//Basta 10 harfli bir kelime olusturuyoruz
			for(int i=0;i<10;i++)//0 dan 10 a kadar ilerliyoruz ustteki kelimede
			{
				cevapFormu[i]= 'A' + rand()%5;//Her harf icin A,B,C,D,E harflerinden birini rastgele seciyoruz
			}
			yeniOgrenci.verilen_cevaplar = cevapFormu;
			
			*(ogrenciler+sira) = yeniOgrenci;//KisiListemizde sayac kadar ilerleyip oraya bu yeni kisiyi ekliyoruz
			sira++;//Bir sonraki kisi icin sayaci arttiriyoruz
		}
	}	
}

void puanHesapla(Ogrenci *ogrenciler, string dogruCevaplar)//Rastgele urettigimiz cevap anahtariyla, kullanicinin ekranda girdigi cevap anahtarini karsilastirip dogru cevaplar icin 10 puan ekliyoruz
{
	int puan;//Puani tutmak icin
	string dogruYanlis;//Karsilastirmanin sonunda dogru yanlis kelimesi uretecez DDYYDY gibi
	int ogrenciSayaci =0;
	int harfSayaci = 0;
	
	while(ogrenciSayaci<2500)//2500 kisinin hepsi icin bu islemi yapiyoruz
	{	
		dogruYanlis = "XXXXXXXXXX";//Basta 10 haneli bir kelime olusturuyoruz. YYYYYYYYYY olsun.
 		puan = 0;//Basta puan 0
		Ogrenci *ogrenci = (ogrenciler+ogrenciSayaci);//Kisi listesinde sirayla i kadar ilerliyoruz
		harfSayaci = 0;//harfleri 0 dan 10 a kadar geziyoruz. X dogru ise D yanlis ise Y yapiyoruz
		while(harfSayaci<10)//cevaptaki 10 harfi sirayla geziyoruz
		{
			if(ogrenci->verilen_cevaplar[harfSayaci] == dogruCevaplar[harfSayaci])//Eger cevap anahtarindaki harf ile kisinin cevabindaki harf ayniysa
			{
				dogruYanlis[harfSayaci] = 'D';//dogruYanlis stringinde X i D ye donusturuyoruz
				puan = puan+10;//10 puan arttiriyoruz
			}//Bunu 10 harf icin de yapiyoruz.5 harf tutarsa 50 puan ...
			else
			{
				dogruYanlis[harfSayaci] = 'Y';//dogruYanlis stringinde X i Y ye donusturuyoruz
			}
			harfSayaci++;
		}
		ogrenci->kazanilan_puan = puan;//En son puan neyse bunu o kisinin puan haznesine yaziyoruz
		ogrenci->dogru_yanlis_durumu = dogruYanlis;//Sonuc stringini de o kisinin sonuc haznesine yaziyoruz. DYDYYYDD bu sekilde
		ogrenciSayaci++;//Bir sonraki ogrenciye geciyoruz
	}	
}

void sirayaGoreYazdir(Ogrenci *ogrenciler, int giris)//Kullanici islemin sonunda 4 secimden birini yapar. Sonuc ona gore siralanir.
{
	Ogrenci temp;//Siralama yaparken iki degerin yeri degisir surekli. Bu iki degerden birini kaybetmemek icin gecici bir Kisi objesinde tutariz.
	int sayac1=0;//ogrenci listesini gezmek icin 1.sayac
	int sayac2=0;//ogrenci listesini gezmek icin 2.sayac
	switch(giris)
	{
		case 1:
			while(sayac1<2500)
			{
				sayac2 = sayac1 +1;//Siralama icin baloncuk siralama algoritmasi esas alinmistir.
				while(sayac2<2500)
				{
					 if((ogrenciler+sayac2)->isim < (ogrenciler+sayac1)->isim) //Eger o elemanin adi diger elemandan alfabetik olarak kucuk ise onune gecer
					  {
				        temp = *(ogrenciler+sayac1);//1. kisi temp nesnesine alinir
				        *(ogrenciler+sayac1) = *(ogrenciler+sayac2);//1.kisi ile 2.kisi yer degisir. 
				        *(ogrenciler+sayac2) = temp;//temp objesi 2. kisiye alinir.
				      }
				      sayac2++;//Sayac2 yi arttiriyoruz
				}
				sayac1++;//sayac1 i arttiriyoruz
			}
			cout<<"Isim";
			cout<<"\t";
			cout<<"Soyisim";
			cout<<"\t";
			cout<<"Yas";
			cout<<"\t";
			cout<<"Cevaplar";
			cout<<"\t";
			cout<<"Dogru-Yanlis";
			cout<<"\t";
			cout<<"Puan";
			cout<<"\t";
			cout<<endl;
			cout<<"---------------------------------------------------------------------------";
			cout<<endl;
			
			
			for(int j=0;j<2500;j++)//Her deger icin ad soyad yas verilen cevaplar sonuc ve puan yazdirilir
			{
				cout<<(ogrenciler+j)->isim;
				cout<<"\t";
				cout<<(ogrenciler+j)->soyisim;
				cout<<"\t";
				cout<<(ogrenciler+j)->yas;
				cout<<"\t";
				cout<<(ogrenciler+j)->verilen_cevaplar;
				cout<<"\t";
				cout<<(ogrenciler+j)->dogru_yanlis_durumu;
				cout<<"\t";
				cout<<(ogrenciler+j)->kazanilan_puan;
				cout<<endl;
				cout<<"---------------------------------------------------------------------------";
				cout<<endl;
			}
			
			break;
			
			case 2:
			while(sayac1<2500)
			{
				sayac2 = sayac1 +1;//Siralama icin baloncuk siralama algoritmasi esas alinmistir.
				while(sayac2<2500)
				{
					 if((ogrenciler+sayac2)->soyisim < (ogrenciler+sayac1)->soyisim) //Eger o elemanin adi diger elemandan alfabetik olarak kucuk ise onune gecer
					  {
				        temp = *(ogrenciler+sayac1);//1. kisi temp nesnesine alinir
				        *(ogrenciler+sayac1) = *(ogrenciler+sayac2);//1.kisi ile 2.kisi yer degisir. 
				        *(ogrenciler+sayac2) = temp;//temp objesi 2. kisiye alinir.
				      }
				      sayac2++;//Sayac2 yi arttiriyoruz
				}
				sayac1++;//sayac1 i arttiriyoruz
			}
			cout<<"Isim";
			cout<<"\t";
			cout<<"Soyisim";
			cout<<"\t";
			cout<<"Yas";
			cout<<"\t";
			cout<<"Cevaplar";
			cout<<"\t";
			cout<<"Dogru-Yanlis";
			cout<<"\t";
			cout<<"Puan";
			cout<<"\t";
			cout<<endl;
			cout<<"---------------------------------------------------------------------------";
			cout<<endl;
			
			for(int j=0;j<2500;j++)//Her deger icin ad soyad yas verilen cevaplar sonuc ve puan yazdirilir
			{
				cout<<(ogrenciler+j)->isim;
				cout<<"\t";
				cout<<(ogrenciler+j)->soyisim;
				cout<<"\t";
				cout<<(ogrenciler+j)->yas;
				cout<<"\t";
				cout<<(ogrenciler+j)->verilen_cevaplar;
				cout<<"\t";
				cout<<(ogrenciler+j)->dogru_yanlis_durumu;
				cout<<"\t";
				cout<<(ogrenciler+j)->kazanilan_puan;
				cout<<endl;
				cout<<"---------------------------------------------------------------------------";
				cout<<endl;
			}
			
			break;
			
			case 3:
			while(sayac1<2500)
			{
				sayac2 = sayac1 +1;//Siralama icin baloncuk siralama algoritmasi esas alinmistir.
				while(sayac2<2500)
				{
					 if((ogrenciler+sayac2)->yas < (ogrenciler+sayac1)->yas) //Eger o elemanin adi diger elemandan alfabetik olarak kucuk ise onune gecer
					  {
				        temp = *(ogrenciler+sayac1);//1. kisi temp nesnesine alinir
				        *(ogrenciler+sayac1) = *(ogrenciler+sayac2);//1.kisi ile 2.kisi yer degisir. 
				        *(ogrenciler+sayac2) = temp;//temp objesi 2. kisiye alinir.
				      }
				      sayac2++;//Sayac2 yi arttiriyoruz
				}
				sayac1++;//sayac1 i arttiriyoruz
			}
			cout<<"Isim";
			cout<<"\t";
			cout<<"Soyisim";
			cout<<"\t";
			cout<<"Yas";
			cout<<"\t";
			cout<<"Cevaplar";
			cout<<"\t";
			cout<<"Dogru-Yanlis";
			cout<<"\t";
			cout<<"Puan";
			cout<<"\t";
			cout<<endl;
			cout<<"---------------------------------------------------------------------------";
			cout<<endl;
			
			for(int j=0;j<2500;j++)//Her deger icin ad soyad yas verilen cevaplar sonuc ve puan yazdirilir
			{
				cout<<(ogrenciler+j)->isim;
				cout<<"\t";
				cout<<(ogrenciler+j)->soyisim;
				cout<<"\t";
				cout<<(ogrenciler+j)->yas;
				cout<<"\t";
				cout<<(ogrenciler+j)->verilen_cevaplar;
				cout<<"\t";
				cout<<(ogrenciler+j)->dogru_yanlis_durumu;
				cout<<"\t";
				cout<<(ogrenciler+j)->kazanilan_puan;
				cout<<endl;
				cout<<"---------------------------------------------------------------------------";
				cout<<endl;
			}
			
			break;
			
			case 4:
			while(sayac1<2500)
			{
				sayac2 = sayac1 +1;//Siralama icin baloncuk siralama algoritmasi esas alinmistir.
				while(sayac2<2500)
				{
					 if((ogrenciler+sayac2)->kazanilan_puan < (ogrenciler+sayac1)->kazanilan_puan) //Eger o elemanin adi diger elemandan alfabetik olarak kucuk ise onune gecer
					  {
				        temp = *(ogrenciler+sayac1);//1. kisi temp nesnesine alinir
				        *(ogrenciler+sayac1) = *(ogrenciler+sayac2);//1.kisi ile 2.kisi yer degisir. 
				        *(ogrenciler+sayac2) = temp;//temp objesi 2. kisiye alinir.
				      }
				      sayac2++;//Sayac2 yi arttiriyoruz
				}
				sayac1++;//sayac1 i arttiriyoruz
			}
			cout<<"Isim";
			cout<<"\t";
			cout<<"Soyisim";
			cout<<"\t";
			cout<<"Yas";
			cout<<"\t";
			cout<<"Cevaplar";
			cout<<"\t";
			cout<<"Dogru-Yanlis";
			cout<<"\t";
			cout<<"Puan";
			cout<<"\t";
			cout<<endl;
			cout<<"---------------------------------------------------------------------------";
			cout<<endl;
			
			for(int j=0;j<2500;j++)//Her deger icin ad soyad yas verilen cevaplar sonuc ve puan yazdirilir
			{
				cout<<(ogrenciler+j)->isim;
				cout<<"\t";
				cout<<(ogrenciler+j)->soyisim;
				cout<<"\t";
				cout<<(ogrenciler+j)->yas;
				cout<<"\t";
				cout<<(ogrenciler+j)->verilen_cevaplar;
				cout<<"\t";
				cout<<(ogrenciler+j)->dogru_yanlis_durumu;
				cout<<"\t";
				cout<<(ogrenciler+j)->kazanilan_puan;
				cout<<endl;
				cout<<"---------------------------------------------------------------------------";
				cout<<endl;
			}
			
			break;	
			
			default:
			cout<<"Yanlis secim yaptiniz ... "<<endl;	
	}
}

int main()
{
	srand(time(NULL));//Program her calistiginda srand fonksiyonu yeni degerler  uretsin diye tine(NULL) yapilir
	Ogrenci ogrenciler[2500];//Kisi nesnelerini tutmak icin olusturdugumuz Kisi dizisi
	string dogruCevaplar;//Kullanicidan alinan dogru cevap anahtari
	int giris;//Kullanicinin yapmis oldugu siralama secimi
	
	dosyalariOkuyupOgrencileriOlustur(ogrenciler);
	
	cout<<"10 haneli cevap anahtari giriniz(orn: ABCDEEDCBA) :  ";
	cin>>dogruCevaplar;//Kullanicidan 10 haneli cevap anahtari alinir
	
	puanHesapla(ogrenciler, dogruCevaplar);//Cevaplari kontrol etme fonksiyonu yazilir
	
	cout<<"Sonuclar degerlendirildi. Nasil siralanmasini istersiniz ? "<<endl;
	cout<<"1. Isme gore"<<endl;
	cout<<"2. Soyisme gore"<<endl;	
	cout<<"3. Yasa gore"<<endl;
	cout<<"4. Puana gore"<<endl;
	cin>>giris;
	
	sirayaGoreYazdir(ogrenciler,giris);//Kisi listesi secime gore siralanir
}
