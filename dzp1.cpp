//#ifndef _Cvor_h_
//#define _Cvor_h_
#include <vector>
#include <stack>
#include <iostream>
#include <string>
using namespace std;

class Cvor
{
	struct Ocena {
		int id;
		int ocena;
		Ocena(int identifikator, int o = 0) :id(identifikator), ocena(o) {}
	};
	string sadrzaj;
	//pokazivaci na cvorove-potomke
	vector<Cvor*> deca;
	static int posId;
	int id = posId++;

	vector <Ocena> ocene;
	int ocena = 0;
	Cvor* otac = nullptr;
public:
	Cvor() = default;
	Cvor(string tekst) :sadrzaj(tekst) {}
	void ispisSazdrzaja();
	friend Cvor* obidjiStablo(Cvor* koren, int opcija, int id);
	friend class Pitanja;
};

//#endif // !_Cvor_h_

//#include "Pitanja.h"

//#ifndef _Pitanja_h_
//#define _Pitanja_h_
//#include "Cvor.h"

class Pitanja
{
	vector<Cvor*> pitanja;
public:
	Pitanja() = default;
	void dodajPitanje(string tekst);
	void dodajOdgovor(string tekst, int id);
	Cvor* pretragaPitanja(int id);
	Cvor* pretragaOdgovora(int idp, int ido);
	Cvor* pretragaOdgovora(int ido);
	void povecajOcenu(int ido, int vr);
	void urediOdgovore();
	void ispisiPitanja();
	void ispisPiO(int id);
	void brisiOdgovor(int id);
	void brisiPitanje(int id);
	void ispisiPsaO();
	Cvor* pronadjiOdgovor(int id);

};

//#endif // !_Pitanja_h_

//#include "Pitanja.h"
void Pitanja::dodajPitanje(string tekst)
{
	Cvor* novoPitanje = new Cvor(tekst);
	pitanja.push_back(novoPitanje);
}

void Pitanja::dodajOdgovor(string tekst, int id)
{
	Cvor* trazeni = pretragaOdgovora(id);
	if (trazeni && trazeni->deca.size() < 10) {
		Cvor* noviOdgovor = new Cvor(tekst);
		trazeni->deca.push_back(noviOdgovor);
		trazeni->ocene.push_back(Cvor::Ocena(noviOdgovor->id));
		noviOdgovor->otac = trazeni;
	}
	else if (!trazeni) {
		cout << "Ne postoji pitanje/odgovor sa zadatim id" << endl;
	}
}

Cvor* Pitanja::pretragaPitanja(int id)
{
	for (int i = 0; i < pitanja.size(); i++) {
		if (pitanja[i]->id == id) return pitanja[i];
	}
	return nullptr;
}

Cvor* Pitanja::pretragaOdgovora(int idp, int ido)
{
	Cvor* pitanje = pretragaPitanja(idp);
	Cvor* odgovor = obidjiStablo(pitanje, 1, ido);
	if (!odgovor) return nullptr;
	return (odgovor->otac ? odgovor : nullptr);

}

Cvor* Pitanja::pretragaOdgovora(int ido)
{
	Cvor* odgovor = nullptr;
	for (int i = 0; i < pitanja.size(); i++) {
		odgovor = obidjiStablo(pitanja[i], 1, ido);
		if (odgovor) break;
	}
	return odgovor;
}

void Pitanja::povecajOcenu(int ido, int vr)
{
	Cvor* trazeni = nullptr;
	trazeni = pretragaOdgovora(ido);
	if (!trazeni || !trazeni->otac) {
		cout << "Ne postoji odgovor sa zadatim id" << endl; return;
	}
	trazeni->ocena += vr;
	for (int i = 0; i < trazeni->otac->ocene.size(); i++) {
		if (trazeni->otac->ocene[i].id == ido) trazeni->otac->ocene[i].ocena += vr;
	}
}

void Pitanja::urediOdgovore()
{
	if (pitanja.size() == 0) cout << "Ne postoji nijedno pitanje" << endl;
	for (int i = 0; i < pitanja.size(); i++) {
		obidjiStablo(pitanja[i], 3, 0);
	}
}

void Pitanja::ispisiPitanja()
{
	if (pitanja.size() == 0) {
		cout << "Ne postoji nijedno pitanje" << endl; return;
	}
	for (int i = 0; i < pitanja.size(); i++) {
		pitanja[i]->ispisSazdrzaja();
	}
}

void Pitanja::ispisPiO(int id)
{
	Cvor* pitanje = pretragaPitanja(id);
	if (!pitanje) {
		cout << "Ne postoji ptanje sa zadatim id" << endl;
		return;
	}
	obidjiStablo(pitanje, 0, 0);
}

void Pitanja::brisiOdgovor(int id)
{
	Cvor* odgovor = nullptr;
	odgovor = pretragaOdgovora(id);
	if (!odgovor) { cout << "Ne postoji odgovor sa zadatim id" << endl; return; }
	if (!odgovor->otac) { cout << "Ovo je pitanje!" << endl; return; }
	obidjiStablo(odgovor, 2, 0);
}

void Pitanja::brisiPitanje(int id)
{
	Cvor* pitanje = nullptr;
	pitanje = pretragaPitanja(id);
	if (!pitanje) {
		cout << "Ne postoji ptanje sa zadatim id" << endl;
		return;
	}
	for (int i = 0; i < pitanja.size(); i++) {
		if (pitanja[i]->id == id) pitanja.erase(pitanja.begin() + i);
	}
	obidjiStablo(pitanje, 2, 0);//ova funkcija izbrise sve potomke od pitanja
}
void Pitanja::ispisiPsaO()//ova funkcija je uvedena po potrebi, radi lakse interakcije sa korisnikom
{
	if (pitanja.size() == 0) {
		cout << "Ne postoji nijedno pitanje" << endl;
		return;
	}
	for (int i = 0; i < pitanja.size(); i++) {
		obidjiStablo(pitanja[i], 0, 0);
	}
}

Cvor* Pitanja::pronadjiOdgovor(int id)//ovo je id pitanja
{
	Cvor* pitanje = nullptr;
	Cvor* odgovor = nullptr;
	pitanje = pretragaPitanja(id);
	odgovor = obidjiStablo(pitanje, 4, 0);
	return odgovor;
}

//#include "Cvor.h"
int Cvor::posId = 0;

void Cvor::ispisSazdrzaja()
{
	if (!this) cout << "Ne postoji!" << endl;
	if (this) {
		cout << sadrzaj << "[" << id << "]";
		if (otac) cout << "(ocena: " << ocena << ")";
		cout << "(" << (otac ? otac->sadrzaj : "pitanje") << ")" << endl;
	}

}

Cvor* obidjiStablo(Cvor* koren, int opcija, int id)//u zavisnosti od vrednosti "opcija" ulazim u neki od switch case-ova
{
	if (!koren) return nullptr;
	stack<Cvor*> Stek;
	vector<Cvor*> Preorder;
	Stek.push(koren);
	Cvor* pom = nullptr;
	int maks = -1;

	while (!Stek.empty()) {
		Cvor* tek = Stek.top();
		Stek.pop();
		//obrada cvora
		switch (opcija) {
		case 0: tek->ispisSazdrzaja(); break;
		case 1: if (tek->id == id) return tek; else break;
		case 2: {
			Preorder.push_back(tek);
			break;
		}
		case 3: {//ove dve petlje swapuju i u vektoru ocene i u vektoru deca mesta
			for (int i = 0; i < tek->ocene.size(); i++) {
				for (int j = i + 1; j < tek->ocene.size(); j++) {
					if (tek->ocene[i].ocena < tek->ocene[j].ocena) {
						Cvor::Ocena pom(0, 0);
						pom = tek->ocene[i];
						tek->ocene[i] = tek->ocene[j];
						tek->ocene[j] = pom;
						Cvor* pom1;
						pom1 = tek->deca[i];
						tek->deca[i] = tek->deca[j];
						tek->deca[j] = pom1;
					}
				}
			}
			break;
		}
		case 4: {
			if (tek->ocena > maks) {
				if (tek->otac) {
					maks = tek->ocena;
					pom = tek;
				}
			}
			break;
		}
		}
		//stavljanje dece na stek u obrnutom poretku
		for (int i = tek->deca.size() - 1; i >= 0; i--) {
			Stek.push(tek->deca[i]);
		}
	}
	//ne ulazi se u ovaj for ako se ne ulazi u case 2
	for (int i = Preorder.size() - 1; i >= 0; i--) {
		if (Preorder[i]->otac) {
			for (int j = 0; j < Preorder[i]->otac->deca.size(); j++) {
				if (Preorder[i]->otac->deca[j]->id == Preorder[i]->id) {
					Preorder[i]->otac->deca.erase(Preorder[i]->otac->deca.begin() + j);
					Preorder[i]->otac->ocene.erase(Preorder[i]->otac->ocene.begin() + j);
				}
			}
			delete Preorder[i];//brise ceo cvor koji je prethodno izbacen iz liste dece njegovog oca
		}
		else {
			delete Preorder[i];
		}
	}
	return pom;
}

int main() {
	Pitanja p;
	bool nastavi = true;
	int izbor;
	while (nastavi) {
		cout << "Izaberite neku stavku iz datog menija: " << endl;
		cout << "1. Dodavanje novog pitanja" << endl;
		cout << "2. Dodavanje odgovora na pitanje ili odgovor" << endl;
		cout << "3. Pretraga pitanja(prema zadatom id)" << endl;
		cout << "4. Pretraga odgovora(prema zadatom id)" << endl;
		cout << "5. Povecavanje ocene nekog odgovora" << endl;
		cout << "6. Uredjivanje odgovora prema njihovoj oceni za sva pitanja" << endl;
		cout << "7. Ispis svih pitanja" << endl;
		cout << "8. Ispis pojedinacnog pitanja i njemu pridruzenih odgovora i komentara" << endl;
		cout << "9. Brisanje odgovora/komentara" << endl;
		cout << "10. Brisanje pojedinacnog pitanja i svih povezanih odgovora" << endl;
		cout << "11. Pronadji odgovor/komentar na zadato pitanje sa najvisom ocenom" << endl;
		cout << "12. Ispisi sva pitanja sa svim odgovorima" << endl;
		cout << "13. Zavrsi program" << endl;
		cin >> izbor;
		switch (izbor) {
		case 1: {
			string tekst;
			cout << "Unesite tekst pitanja:" << endl;
			cin.ignore();
			getline(cin, tekst);
			p.dodajPitanje(tekst);
			break;
		}
		case 2: {
			string tekst;
			int ident;
			cout << "Unesite id pitanja/odgovora na koje se odnosi odgovor, kao i sam tekst odgovora" << endl;
			cin >> ident;
			cin.ignore();
			getline(cin, tekst);
			p.dodajOdgovor(tekst, ident);
			break;
		}
		case 3: {
			int ident;
			cout << "Unesite id pitanja" << endl;
			cin >> ident;
			p.pretragaPitanja(ident)->ispisSazdrzaja();
			break;
		}
		case 4: {
			int idp, ido;
			cout << "Unesite id pitanja, zatim id odgovora" << endl;
			cin >> idp >> ido;
			p.pretragaOdgovora(idp, ido)->ispisSazdrzaja();
			break;
		}
		case 5: {
			cout << "Unesite id odgovora kome zelite povecati ocenu i za koliko" << endl;
			int ido, vr;
			cin >> ido >> vr;
			p.povecajOcenu(ido, vr);
			break;
		}
		case 6: {
			p.urediOdgovore();
			break;
		}
		case 7: {
			p.ispisiPitanja();
			break;
		}
		case 8: {
			int id;
			cout << "Unesite pitanje(id) ciji sadrzaj i odgovore zelite da ispisete" << endl;
			cin >> id;
			p.ispisPiO(id);
			break;
		}
		case 9: {
			int id;
			cout << "Unesite id odgovora koji zelite da obrisete" << endl;
			cin >> id;
			p.brisiOdgovor(id);
			break;
		}
		case 10: {
			int id;
			cout << "Unesite id pitanja koje zelite da obrisete" << endl;
			cin >> id;
			p.brisiPitanje(id);
			break;
		}
		case 11: {
			int id;
			cout << "Unesite id pitanja" << endl;
			cin >> id;
			p.pronadjiOdgovor(id)->ispisSazdrzaja();
			break;
		}
		case 12: {
			p.ispisiPsaO();
			break;
		}
		case 13: 
			nastavi = false;
			break;
		default:
			cout << "Uneli ste pogresan izbor, unesite ponovo." << endl;
		}
	}
	return 0;
}