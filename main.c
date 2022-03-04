// Import library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define OS_Windows
#else
#include <unistd.h>
#endif

// Deklarasi ukuran untuk banyak produk
#define ukuran 7

// Deklarasi inc untuk looping, dan addrs untuk temp address
int inc;
int addrs=0;

// Deklarasi Struct data
struct data{
	char kode[10];
	char nama[30];
	int  stok;
	long harga;
};

// Deklarasi produk dari tipe data struct "data"
struct data Produk[ukuran];

// Deklarasi Function
void clear_screen(); // Fungsi : Bersihkan konsol
void tampilNmToko(); // Fungsi : Tampilkan nama toko
void inisialisasi(); // Fungsi : Inisialsisasi data produk
void tampilProduk(); // Fungsi : Tampilkan tabel produk
void mnuProgramKu(); // Fungsi : Menu
void buatProdukSl(); // Fungsi : Jual
void tambahkanStk(); // Fungsi : Tambah Stok

void cekKodeProdk(char kode[]); // Fungsi cek kode produk
void format_angka(long angka); // Fungsi konversi 1000 -> 1.000

// Main Program
int main(){
	#ifdef OS_Windows
	system("title HEALTHY YOGHURT SHOP CASHIER");
	#endif
	
	// Panggil Fungsi inisialisasi data produk
	inisialisasi();
	// Panggil Fungsi menu
	mnuProgramKu();

	// Return value 0
	return 0;
}

// Bersihkan Konsol
void clear_screen(){
	// Panggil system() dengan parameter cls || clear : cls -> windows, clear -> linux
	system("cls||clear");
}

// Tampilkan nama toko
void tampilNmToko(){
	// Tampilkan nama
	printf("HEALTHY YOGHURT SHOP CASHIER\n");
	printf("===============================\n\n");
}

// Inisialisasi Struct data produk
void inisialisasi(){
	// Deklarasi kode produk mengunakan array 2 dimensi
	char kode[ukuran][10] = {
		"HE002", "HE003", "HE006",
		"HE007", "HE011", "HE018", "HE022"
	};
	
	// Deklarasi nama produk menggunakan array 2 dimensi
	char nama[ukuran][30] = {
		"Plain Yoghurt",
		"Blueberry Yoghurt",
		"Manggo Peach Yoghurt",
		"Banana Strawberry Yoghurt",
		"Choco Granola Yoghurt",
		"Berry Smooth Yoghurt",
		"Pomegranate Yoghurt"
	};
	
	// Deklarasi stok menggunakan 1 dimensi array
	int stok[ukuran] = {
		18, 23, 19, 22, 14, 17, 12
	};
	
	// Deklarsi harga menggunakan 1 dimensi array
	long hrga[ukuran] = {
		15000, 15000, 18000,
		18000, 20000, 20000, 20000
	};
	
	// Proses inisialisasi struct data produk
	for(inc=0; inc<ukuran; inc++){
		strcpy(Produk[inc].kode, kode[inc]);
		strcpy(Produk[inc].nama, nama[inc]);
		
		Produk[inc].stok  = stok[inc];
		Produk[inc].harga = hrga[inc];
	}
}

// Tampilkan tabel produk
void tampilProduk(){
	printf("No. | Code  | Yoghurt Name              | Available | Price\n");
	printf("-------------------------------------------------------------------\n");
	
	// Menampilkan produk dengan perulangan yang di ambil dari sturct data produk
	for(inc=0; inc<ukuran; inc++){
		printf("0%d. | %s | %-25s | %9d | Rp. ", inc+1, Produk[inc].kode, Produk[inc].nama, Produk[inc].stok);
		format_angka(Produk[inc].harga);
		printf(",-\n");
	}
	
	printf("-------------------------------------------------------------------\n\n");
}

// Menu program
void mnuProgramKu(){
	// Deklarasi input_choice untuk menerima input menu
	int input_choice;
	
	// Panggil function
	// clear_screen(); // Bersihkan konsol
	tampilNmToko(); // Tampilkan nama toko
	tampilProduk(); // Tampilkan tabel produk
	
	// Tampilkan menu
	printf("Menu : \n");
	printf("1. Sell\n");
	printf("2. Add Stock\n");
	printf("3. Exit\n");
	
	// Proses input pemilihan menu
	printf("Input choice : ");
	scanf("%d", &input_choice);
	
	// switch case menu
	switch(input_choice){
		case 1:
			buatProdukSl();
		case 2:
			tambahkanStk();
		case 3:
			exit(0);
		default:
			exit(1);
	}
}

// Jual produk
void buatProdukSl(){
	// Deklarasi kode untuk menerima input kode produk
	char kode[10];
	// Deklarasi jumlah untuk menerima berpa jumlah yang di jual
	int jumlah;
	
	// Poses Input kode produk
	printf("\nInput Yoghurt Code [5 Chars]: ");
	scanf("%s", kode);
	
	// Cek kode produk
	cekKodeProdk(kode);
	
	// Proses input jumlah yang terjual
	printf("Input Quantitiy [0..%d]: ", Produk[addrs].stok);
	scanf("%d", &jumlah);

	// Cek jumlah
	if(jumlah < 0 || jumlah > Produk[addrs].stok){
		printf("\n\n...The quantity of yoghurt is not enough...");
		
		sleep(3);
		mnuProgramKu();
	} else if(jumlah == 0){
		printf("\n--- Thank You ---");
		
		sleep(3);
		mnuProgramKu();
	}
	
	// Tampilkan hasil
	printf("\nTotal Price: Rp ");
	format_angka(Produk[addrs].harga);
	printf(",- x %d = Rp ", jumlah);
	format_angka(Produk[addrs].harga * jumlah);
	printf(",-");
	
	// Proses pengurangan jumlah stok produk yang ada dilist
	Produk[addrs].stok = Produk[addrs].stok - jumlah;
	
	printf("\n\n--- Thank You ---");
	
	sleep(3);
	mnuProgramKu();
}

void tambahkanStk(){
	char kode[10];
	int stok;
	
	printf("\nInput Yoghurt Code [5 Chars]: ");
	scanf("%s", kode);
	
	cekKodeProdk(kode);
	
	printf("Input Quantitiy [1..100]: ");
	scanf("%d", &stok);

	if(stok < 0 || stok > 100){
		exit(1);
	} else if(stok == 0){
		mnuProgramKu();
	}
	
	Produk[addrs].stok = Produk[addrs].stok + stok;
	
	printf("\n\n--- Adding Stock Success ---");
	
	sleep(3);
	mnuProgramKu();
}

void cekKodeProdk(char kode[]){
	int found=0;
	
	if(strlen(kode) != 5){
		printf("\n\n---The yoghurt code doesn't exist---");
		
		sleep(3);
		mnuProgramKu();
	}
	
	for(inc=0; inc<ukuran; inc++){
		if(strcmp(Produk[inc].kode, kode) == 0){
			found = 1;
			addrs = inc;
		}
	}
	
	if(found == 0){
		printf("\n\n---The yoghurt code doesn't exist---");
		
		sleep(3);
		mnuProgramKu();
	}
}

// Konverter angka
void format_angka(long angka){
	if(angka < 0){
		printf("-");
		format_angka(-angka);
		return;
	} else if(angka < 1000){
		printf("%ld", angka);
		return;
	}
	format_angka(angka / 1000);
	printf(".%03ld", angka % 1000);
}
