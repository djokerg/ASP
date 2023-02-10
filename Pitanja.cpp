#include "Pitanja.h"
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