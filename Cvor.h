#ifndef _Cvor_h_
#define _Cvor_h_
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
		Ocena(int identifikator, int o = 0) :id(identifikator), ocena(o){}
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
	Cvor(string tekst):sadrzaj(tekst){}
	void ispisSazdrzaja();
	friend Cvor* obidjiStablo(Cvor* koren, int opcija, int id);
	friend class Pitanja;
};

#endif // !_Cvor_h_