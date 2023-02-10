#include "Cvor.h"
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
				for (int i = 0; i < tek->ocene.size();i++) {
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