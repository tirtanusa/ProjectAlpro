#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cstring>

using namespace std;

struct order{
	int harga;
	string barang;
};

class Marketplace{
	friend ostream &operator << (ostream&, Marketplace&);
	friend istream &operator >> (istream&, Marketplace&);
	public:
		
	string username[10];
	string password;
	string loginUsername;
	string namaBarang[10];
	int hargaBarang[10];
	string tempCart[255];
	string cart[255][3];
	int indeksUserCart;
	int hargaCart[255];
	
	int indeksCart;
	int indeksKolomAkun;
	bool samaUsername;
	fstream in;
	int idUser;
	int saldo[10];
	int jumlahBarang;
	int j;
	int indeksOrder;
	
	int totalHarga;
	
//	public:
	void login();
	void registrasi();
	void import();
	void imporSaldo();
	void importBarang();
	void displayBarang();
	void checkout();
	void displayCart();
};

// import akun yang pernah didaftarkan
void Marketplace::import(){
	indeksKolomAkun = 0;
	in.open("username.txt");
	while(!in.eof()){
		getline(in,username[indeksKolomAkun++]);
	}
	in.close();
}

//mekanisme registrasi
void Marketplace::registrasi(){
	string tempUsername;
	
	if(indeksKolomAkun == 10){ 
		cout << "Anda Tidak Bisa Menambahkan akun baru, silahkan hubungi developer"<<endl;
		login();
	}
	
	bool samaPassword = true;
	string ulangPassword; 
	if(samaUsername == true){ //Username sudah terdaftar
		cout << "Username yang anda daftarkan sudah ada, silahkan masukkan username yang baru\n\n";
	}
	
	samaUsername = false;
	
	do{
		if(samaPassword == false){
			cout << "Inputan Ulang Password salah!"<<endl;
		}
		cout << "Masukkan Username : ";
		getline(cin,username[indeksKolomAkun]);
		tempUsername = username[indeksKolomAkun];
		cout << "Masukkan Password : ";
		getline(cin,password);
		cout << "Ulang Masukkan Password : ";
		getline(cin,ulangPassword);
		if(password != ulangPassword){
			samaPassword=false;
		}
		
		if(tempUsername.length() < 6 or password.length() < 6){ //Ulang input ketika Password/username < 6 character
			cout << "Username atau Password tidak boleh kurang dari 6"<<endl;
			ulangPassword = "";
		}
	}while(password != ulangPassword);
	indeksKolomAkun++;
	
	
	//cek username yang sama yang dibuat lebih dahulu
	for(int i = 0; i < indeksKolomAkun-1; i++){
		if(username[i] == tempUsername){
			samaUsername=true;
			indeksKolomAkun--;
			registrasi();
		}
	}
	
	in.open("username.txt"); //export username yang didaftarkan
	for(int i = 0; i < indeksKolomAkun;i++){
		if(i == indeksKolomAkun-1){
			in << username[i];
		}
		else{
			in << username[i]<<endl;
		}
	}
	in.close();
	
	in.open("password.txt", ios::app);//export password yang didaftarkan
	in << endl << password;
	in.close();

	
}
//algoritma login akun
void Marketplace::login(){
	string loginPassword;
	string passwordLogin[10];
	int indeksPassword;
	bool allow = false;
	
	in.open("password.txt");
	while(!in.eof()){
		getline(in,passwordLogin[indeksPassword++]);
	}
	in.close();
	
//	for(int i = 0;i < indeksPassword;i++){
//		cout << passwordLogin[i]<< " ";
//	}
	
	do{
		cout << "\nMasukkan Username : ";
		getline(cin,loginUsername);
		cout << "Masukkan Password : ";
		getline(cin,loginPassword);
	
		for(int i=0; i < indeksPassword;i++){
			if(username[i] == loginUsername and passwordLogin[i] == loginPassword){
				allow = true;
				idUser = i;
			}
		}
		if(loginUsername.length() < 6 or loginPassword.length() < 6){ //Ulang input ketika Password/username < 6 character
			cout << "Username atau Password tidak boleh kurang dari 6"<<endl;
			allow = false;
		}
		
		if(allow == false){
			cout << "Username atau password yang anda masukkan salah!"<<endl;
		}
	}while(!allow);
	system("cls");
	cout << "Selamat Datang "<< loginUsername<<"!"<<endl;
	
}

//fitur saldo
void Marketplace::imporSaldo(){
	int i = 0;
	in.open("saldo.txt");
	while(!in.eof()){
		in >> saldo[i];
		i++;
	}
	in.close();
	cout << "\nSaldo anda : " <<saldo[idUser]<<endl;
}

void Marketplace::importBarang(){
	int i = 0;
	jumlahBarang = 0;
	in.open("nama_barang.txt");
	while(!in.eof()){
		getline(in,namaBarang[i]);
		i++;
		jumlahBarang++;
	}
	in.close();
	i = 0;
	in.open("harga_barang.txt");
	while(!in.eof()){
		in >> hargaBarang[i];
		i++;
	}
	in.close();	
}

void Marketplace::displayCart(){
	indeksCart = 0;
	int i = 0;
	in.open("cart_barang.txt");
	while(!in.eof()){
		getline(in,tempCart[i]);
		i++;
		indeksCart++;
	}
	in.close();
	int l = 0;
	int m = 0;
	int stop = indeksCart/3;
	for(int j = 0; j < stop ; j++){
		for(int k = 0; k < 3;k++){
			cart[j][k] = tempCart[l];
			l++;
		}
	}
	
	indeksUserCart = 0;
	//sorting cart berdasarkan username
	for(int j = 0; j < stop ; j++){
		if(loginUsername == cart[j][0]){
			stringstream ss;
			ss << cart[j][2];
			ss >> hargaCart[indeksUserCart++];
			for(int k = 1;k < 3; k++){
				cout << cart[j][k] << " ";
			}
			cout << endl;
		}
	}
	cout << endl;
	totalHarga = 0;
//	cout << indeksUserCart<<endl<<endl;
	for(int i = 0 ;i < indeksUserCart; i++){
//		cout << hargaCart[i]<<endl;
		totalHarga += hargaCart[i];
	}
//	cout << totalHarga;
//	bool berhasilBayar = false;
//	fstream out;
//	char check;
//	cout << "Apakah anda ingin Checkout sekarang? (y/n) : ";
//	cin >> check;
//	string kodePromo = "PROMO01EMANTAP";
//		if(check == 'y'){
//			cout << "Total : \t" << totalHarga <<endl;
//			cout << "==========================="<<endl;
//			cout << "Pembayaran akan dilakukan dengan mengurangi saldomu "<<endl;
//			system("pause");
//			if(totalHarga > saldo[idUser]){
//				cout << "Mohon maaf saldo anda tidak cukup";
//				return;
//			}
//			berhasilBayar = true;
//			cout << "Pembayaran : "<< saldo[idUser]<<" - " <<  totalHarga;
//			cout << "\nSisa saldo anda adalah : " << saldo[idUser] - totalHarga;
//			saldo[idUser] -= totalHarga;
//			cout << endl;
//			out.open("saldo.txt");
//			for(int i = 0; i < indeksKolomAkun; i++){
//				if(i == indeksKolomAkun-1){
//					out << saldo[i];
//				}
//				else{
//					out << saldo[i] << endl;
//				}	
//			}
//			out.close();
//			
//			ofstream keluar;
//			if(berhasilBayar == true){
//				keluar.open("cart_barang.txt", ios::trunc);
//				int j = 0;
//				while(j < m){
//					keluar << user[j] << endl << brg[j] <<endl<< hrg[j]<<endl;
//				}
//				keluar.close();
//			}
//			
//				
//		}		
}

void display_menu(){
	cout << "Silahkan pilih menu dibawah ini!"<<endl;
	cout << "1. Tampilkan menu dengan urutan waktu ditambahkan\n2. Tampilkan menu dengan sorting harga\n3. Tampilkan menu Cart\n4. Searching"<<endl;
}



istream &operator >> (istream& in, Marketplace& mp){
	mp.import();
	mp.importBarang();
	char cartTampil = false;
	int j;
	int pilih_menu;
	fstream out;
	char lagi;
	mp.indeksOrder = 0;
	order ord[mp.jumlahBarang];
	cout << "Selamat Datang Marketplace"<<endl; 
	cout << "Silahkan login!";
	mp.login();
	mp.imporSaldo();
	int totalHargaSekarang = 0;
	
	mulai :
	display_menu();
	cout << "Masukkan pilihan anda : ";
	cin >> pilih_menu;
	
	switch(pilih_menu){
			case 1:{
				cout << "Berikut daftar barang yang dapat anda beli di marketplace ini."<<endl;
				do{
					for(int i = 0 ; i < mp.jumlahBarang; i++){
						cout << i+1<<". "<< mp.namaBarang[i] << "\t\t" << mp.hargaBarang[i]<<endl;
					}
					cout << "Masukkan pilihan : ";
					in >> j;
					int l;
					l = j-1;
					ord[mp.indeksOrder].barang =  mp.namaBarang[l];
					ord[mp.indeksOrder].harga =  mp.hargaBarang[l];
					mp.indeksOrder++;
					cout << "Apakah ingin memesan lagi? (y/n) : ";
					in >> lagi;
				}while(lagi == 'y');
				break;
			}
			case 2:{
				for(int i = 0; i < mp.jumlahBarang;i++){
					for(int j = 0; j < mp.jumlahBarang; j++){
						if(mp.hargaBarang[i] < mp.hargaBarang[j]){
							swap(mp.hargaBarang[i],mp.hargaBarang[j]);
							swap(mp.namaBarang[i],mp.namaBarang[j]);
						}
					}
				}
				do{
					for(int i = 0 ; i < mp.jumlahBarang; i++){
						cout << i+1<<". "<< mp.namaBarang[i] << "\t\t" << mp.hargaBarang[i]<<endl;
					}
					cout << "Masukkan pilihan : ";
					in >> j;
					int l;
					l = j-1;
					ord[mp.indeksOrder].barang =  mp.namaBarang[l];
					ord[mp.indeksOrder].harga =  mp.hargaBarang[l];
					mp.indeksOrder++;
					cout << "Apakah ingin memesan lagi? (y/n) : ";
					in >> lagi;
				}while(lagi == 'y');
				break;
			}
			case 3:{
				cartTampil = true;
				mp.displayCart();
				break;
			}
			case 4:{
				int pilihMetodePencarian;
				cout << "Pilih Metode Pencarian\n1. Pencarian berdasarkan nama barang\n2. Pencarian berdasarkan Range harga barang\nPilih : ";
				cin >> pilihMetodePencarian;
				if(pilihMetodePencarian == 1){
					system("cls");
					string cari;
					bool ketemu =  false;
					cout << "Masukkan kata kunci pencarian : ";
					cin.ignore();
					getline(cin,cari);
					do{
						for(int i = 0; i < mp.jumlahBarang; i++ ){
							if(mp.namaBarang[i].find(cari) != string::npos){
								ketemu = true;
								cout <<i+1<<". "<< mp.namaBarang[i] <<" "<< mp.hargaBarang[i]<<endl;
								
							}
						}
						if(ketemu == false){
							cout << "Kata kunci yang anda cari tidak ditemukan";
							return in;
						}
					
						cout << "Masukkan pilihan : ";
						in >> j;
						int l;
						l = j-1;
						ord[mp.indeksOrder].barang =  mp.namaBarang[l];
						ord[mp.indeksOrder].harga =  mp.hargaBarang[l];
						mp.indeksOrder++;
						cout << "Apakah ingin memesan lagi? (y/n) : ";
						in >> lagi;
					}while(lagi == 'y');
				}
				else if(pilihMetodePencarian == 2){
					system("cls");
					int hargaMaksimum,hargaMinimum;
					bool found = false;
					cout << "Masukkan harga minimum : ";
					cin >> hargaMinimum;
					cout << "Masukkan harga maksimum : ";
					cin >> hargaMaksimum;
					
					
					do{
						for(int i = 0; i < mp.jumlahBarang;i++ ){
							if(mp.hargaBarang[i] < hargaMaksimum and mp.hargaBarang[i] > hargaMinimum){
								cout << mp.namaBarang[i] << "\t" << mp.hargaBarang[i]<<endl;
								
							}
						} 
						cout << "Masukkan pilihan : ";
						in >> j;
						int l;
						l = j-1;
						ord[mp.indeksOrder].barang =  mp.namaBarang[l];
						ord[mp.indeksOrder].harga =  mp.hargaBarang[l];
						mp.indeksOrder++;
						cout << "Apakah ingin memesan lagi? (y/n) : ";
						in >> lagi;
					}while(lagi == 'y');
					if(found == false){
						cout << "Barang dengan Range harga tersebut tidak ditemukan ";
					}
				}
				else{
					cout << "Pilihan anda tidak terdeteksi";
					return in;
				}
				
				break;
			}
			default:{
				cout << "Pilihan tidak ditemukan";
				return in;
				break;
				}
		}
	
	char check;
	if(cartTampil == false){
		bool punya;
		cout << "Apakah anda ingin Checkout sekarang? (y/n) : ";
		cin >> check;
		string kodePromo = "PROMO01EMANTAP";
		string masukkanKodePromo;
		if(check == 'y'){
			cout << "Nama Barang   Harga Barang"<<endl;
			for(int k = 0; k < mp.indeksOrder;k++){
				cout << ord[k].barang << " "<< ord[k].harga<<endl; 
				totalHargaSekarang += ord[k].harga;
			}
			cout << "Total : \tRp." << totalHargaSekarang<<endl;
			cout << "Apakah anda mempunyai kode promo? (0/1)";
			cin >> punya;
			bool promoBenar;
			if(punya == 1){
				do{
					cout << "Masukkan Kode Promo : ";
					getline(cin,masukkanKodePromo);
					if(masukkanKodePromo == kodePromo){
						promoBenar == true;
					}
					cout << "Coba lagi? (0/1) : "
				}while(punya == 1)
				
			}
			cout << "==========================="<<endl;
			cout << "Pembayaran akan dilakukan dengan mengurangi saldomu "<<endl;
			system("pause");
			if(totalHargaSekarang > mp.saldo[mp.idUser]){
				cout << "Mohon maaf saldo anda tidak cukup";
				return in;
			}
			cout << "Pembayaran : Rp."<< mp.saldo[mp.idUser]<<" - Rp." <<  totalHargaSekarang;
			if(promoBenar == true){
				cout << "Karena anda mempunyai kode promo ,maka tagihan akan dikurangi sebesar Rp. 20000"<<endl;
				"\nPembayaran : Rp."<< mp.saldo[mp.idUser]<<" - (Rp." <<  totalHargaSekarang << "-  Rp. 20000)"<<;
				cout << "\nSisa saldo anda adalah : Rp." << mp.saldo[mp.idUser] - (totalHargaSekarang - 20000);
				mp.saldo[mp.idUser] -= totalHargaSekarang-20000;
				cout << endl;
			}
			else{
				cout << "\nSisa saldo anda adalah : Rp." << mp.saldo[mp.idUser] - totalHargaSekarang;
				mp.saldo[mp.idUser] -= totalHargaSekarang;
				cout << endl;
			}
			
			out.open("saldo.txt");
			for(int i = 0; i < mp.indeksKolomAkun; i++){
				if(i == mp.indeksKolomAkun-1){
					out << mp.saldo[i];
				}
				else{
					out << mp.saldo[i] << endl;
				}	
			}
			out.close();	
		}	
	}
	if(mp.indeksOrder >= 1){
		out.open("cart_barang.txt", ios::app); //export cart
		out << endl;
		for(int i = 0; i < mp.indeksOrder;i++){
			if(i == mp.indeksOrder-1){
				out << mp.loginUsername<<endl;
				out << ord[i].barang<<endl;
				out << ord[i].harga;
			}
			else{
				out << mp.loginUsername<<endl;
				out << ord[i].barang<<endl;
				out << ord[i].harga<<endl;
			}
		}
		out.close();
	}
	return in;
	
}
//ostream &operator << (ostream& out, Marketplace& mp){
//	out << 
//}
int main(){
	Marketplace mp;
	cin >> mp;
	return 0;
}
