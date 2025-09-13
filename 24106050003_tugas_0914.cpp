#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

struct isi{
    int banyakData;
    int isiData[100];
    int modus;
    float mean;
    float median;
    float Q1, Q2, Q3;
};

class Statistic{
    public:
        void header();
        void mengisiData(isi*);
        void data(isi*);
        void mengurutkanData(isi*);
        void cetakDataUrut(isi);
        float mencariMean(isi);
        float mencariMedian(isi);
        int mencariModus(isi);
        void mencariKuartil(isi*);   // 🔥 fungsi kuartil
};

void Statistic::header(){
    cout <<"=== Mencari data statistik Mean, Median, Modus & Kuartil ===\n\n";
}

// Mengisi data
void Statistic::mengisiData(isi *x){
    for(int i=0; i<x->banyakData; i++){
        cout << "Masukkan data pada index ke-" << i << ": ";
        cin >> x->isiData[i];
    }
}

// Menampilkan data sebelum diurutkan
void Statistic::data(isi *x){
    cout <<"\n\n=== Data Sebelum Diurutkan ===\n\n";
    for(int i=0; i<x->banyakData; i++){
        cout << x->isiData[i] << " ";
    }
    cout << endl;
}

// Mengurutkan data (bubble sort)
void Statistic::mengurutkanData(isi *x){
    int tmp;
    for (int i=0; i < x->banyakData-1; i++){
        for (int j=0; j < x->banyakData-i-1; j++){
            if(x->isiData[j] > x->isiData[j+1]){
                tmp = x->isiData[j];
                x->isiData[j] = x->isiData[j+1];
                x->isiData[j+1] = tmp;
            }
        }
    }
}

// Cetak data setelah diurutkan
void Statistic::cetakDataUrut(isi x){
    cout << "\n\n=== Data Yang Telah Diurutkan ===\n\n";
    for(int i=0; i<x.banyakData; i++){
        cout << x.isiData[i] << " ";
    }
    cout << endl;
}

// Mean
float Statistic::mencariMean(isi x){
    float jumlahIsiData=0;
    for(int i=0; i<x.banyakData; i++){
        jumlahIsiData+=x.isiData[i];
    }
    x.mean = jumlahIsiData/x.banyakData;
    return x.mean;
}

// Median
float Statistic::mencariMedian(isi x){
    int median1=0, median2=0;
    if(x.banyakData%2 == 0){
        median1 = x.banyakData/2;
        median2 = median1+1;
        median1 = x.isiData[median1-1];
        median2 = x.isiData[median2-1];
        x.median = ((float(median1)+median2)/2);
    } else {
        median1 = x.banyakData/2;
        x.median = x.isiData[median1];
    }
    return x.median;
}

// Modus
int Statistic::mencariModus(isi x){
    int nilaiModus=0, jumlahNilaiModus=0;
    for(int i=0; i<x.banyakData; i++){
        int jumlahSementara=0;
        for(int j=0; j<x.banyakData; j++){
            if(x.isiData[i]==x.isiData[j]){
                jumlahSementara++;
            }
        }
        if(jumlahSementara > jumlahNilaiModus){
            jumlahNilaiModus = jumlahSementara;
            nilaiModus = x.isiData[i];
        }
    }
    if(jumlahNilaiModus == 1){
        nilaiModus = 0;
    }
    return nilaiModus;
}

// Kuartil
void Statistic::mencariKuartil(isi *x){
    int n = x->banyakData;

    // Q2 = median
    x->Q2 = mencariMedian(*x);

    // Q1
    if(n % 2 == 0) {
        // median dari separuh bawah
        isi lower;
        lower.banyakData = n/2;
        for(int i=0;i<lower.banyakData;i++)
            lower.isiData[i] = x->isiData[i];
        x->Q1 = mencariMedian(lower);

        // median dari separuh atas
        isi upper;
        upper.banyakData = n/2;
        for(int i=0;i<upper.banyakData;i++)
            upper.isiData[i] = x->isiData[i + n/2];
        x->Q3 = mencariMedian(upper);
    } else {
        // median dari separuh bawah
        isi lower;
        lower.banyakData = n/2;
        for(int i=0;i<lower.banyakData;i++)
            lower.isiData[i] = x->isiData[i];
        x->Q1 = mencariMedian(lower);

        // median dari separuh atas
        isi upper;
        upper.banyakData = n/2;
        for(int i=0;i<upper.banyakData;i++)
            upper.isiData[i] = x->isiData[i + n/2 + 1];
        x->Q3 = mencariMedian(upper);
    }
}

// Main program
int main(){
    ofstream myfile;
    isi x;
    Statistic s;

    s.header();

    cout << "Masukkan banyaknya data: ";
    cin >> x.banyakData;
    cout << endl;

    s.mengisiData(&x);
    s.data(&x);
    s.mengurutkanData(&x);
    s.cetakDataUrut(x);

    float mean = s.mencariMean(x);
    float median = s.mencariMedian(x);
    int modus = s.mencariModus(x);
    s.mencariKuartil(&x);

    cout << "\n\n=== Hasil Data Statistiknya ===\n";
    cout << "\n1. Mean-nya adalah\t= " << mean;
    cout << "\n2. Median-nya adalah\t= " << median;
    cout << "\n3. Modus-nya adalah\t= " << modus;
    cout << "\n4. Kuartil 1 (Q1)\t= " << x.Q1;
    cout << "\n5. Kuartil 2 (Q2)\t= " << x.Q2;
    cout << "\n6. Kuartil 3 (Q3)\t= " << x.Q3;

    // Simpan ke file
    myfile.open("Simpandata.txt", ios::app);
    if(!myfile.fail()){
        myfile<<"\n===================================================\n";
        myfile<<"\n=== Hasil Data Statistiknya ===\n";
        myfile<<"\n1. Mean-nya adalah\t= " << mean;
        myfile<<"\n2. Median-nya adalah\t= " << median;
        myfile<<"\n3. Modus-nya adalah\t= " << modus;
        myfile<<"\n4. Kuartil 1 (Q1)\t= " << x.Q1;
        myfile<<"\n5. Kuartil 2 (Q2)\t= " << x.Q2;
        myfile<<"\n6. Kuartil 3 (Q3)\t= " << x.Q3;
        myfile.close();
        cout << "\n\nText telah ditulis ke dalam file" << endl;
    } else {
        cout<<"File tidak ditemukan"<<endl;
    }

    _getche();
    return 0;
}
