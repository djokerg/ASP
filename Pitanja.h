#ifndef _Pitanja_h_
#define _Pitanja_h_
#include "Cvor.h"

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

#endif // !_Pitanja_h_