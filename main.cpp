#include "Pitanja.h"

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