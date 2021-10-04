#include<iostream>
#include<string>
#include<sstream>
#include<utility>
using namespace std;

string prosiriInfSekv(string i, string g);
pair<string,string> racunanjeOstatka(string i, string g);
string skloniPocetneNule(string str);
string ispisPol(string str);
bool proveriDaLiJeBinarno(string str);
bool proveriDaLiJeNula(string str);


int main() {

	int end = 0;
	string inf, gen, rem,rez, c,e,y;

	do {
		c = y="";

		//unos i(x)
		do {
			cout << "Unesite informacionu sekvencu: ";
			cin >> inf;
		} while (!proveriDaLiJeBinarno(inf));
		
		//unos g(x)
		do{
			cout << "Unesite generisuci polinom u obliku binarne sekvence: ";
			cin >> gen;
		} while (!proveriDaLiJeBinarno(gen));

		inf = skloniPocetneNule(inf);
		gen = skloniPocetneNule(gen);

		//ispis polinoma
		cout << "\nInformaciona sekvenca u polinomijalnom obliku:   i(x)=" << ispisPol(inf) << endl;
		cout << "Generisuci polinom:   g(x)=" << ispisPol(gen) << endl;

		//i* (kada se na sekvencu i doda odgovarajuci broj 0)
		inf = prosiriInfSekv(inf, gen);
		cout << "\ni*= (" << inf << ")\n";

		// i*(x) / g(x)
		pair<string, string> p1;
		p1 = racunanjeOstatka(inf, gen);
		cout << "\nRezultat deljenja i*(x)/g(x): " << (rez = p1.second) << endl;
		cout << "Ostatak deljenja rem{i*(x)/g(x)}: " << (rem = p1.first) << "    ==>    ";
		cout << "r(x)=" << ispisPol(rem) << endl;

		//c = i* XOR rem
		int ri = 0;
		for (size_t i = 0; i < inf.length(); i++) {
			if (i < inf.length() - gen.length() + 1) {
				c += inf[i];
			}
			else {
				int b = (inf[i] - '0') ^ (rem[ri++] - '0');
				c += char(b + '0');
			}
		}
		cout << "\nc = (" << c << ")" << endl;

		//unos greske
		do {
			cout << "\nUnesi sekvencu greske duzine " << c.length() << ":  ";
			cin >> e;
		} while (e.length() != c.length() || !proveriDaLiJeBinarno(e));

		//y = c XOR e
		for (size_t i = 0; i < c.length(); i++) {
			int b = (c[i] - '0') ^ (e[i] - '0');
			y += char(b + '0');
		}
		cout << "\ny = (" << y << ")" << endl;

		// y(x) / g(x)
		p1 = racunanjeOstatka(y, gen);
		cout << "\nRezultat deljenja y(x)/g(x)= " << (rez = p1.second) << endl;
		cout << "Ostatak: rem{y(x)/g(x)}= " << (rem = p1.first) <<"    ==>    ";
		cout << "r(x)=" << ispisPol(rem) << endl;

		//ispis rezultata i zakljucka
		if (proveriDaLiJeNula(rem)==true) {
			cout << "\nPOSLATA KODNA REC c(x) JE ISPRAVNO PRENETA (JER JE DELJIVA GENERISUCIM POLINOMOM g(x))!" << endl;
		}
		else {
			cout << "\nDETEKTOVANA JE GRESKA PRI PRENOSU KODNE RECI c(x)! OSTATAK PRI DELJENJU y(x) SA g(x) JE RAZLICIT OD NULE!" << endl;
		}
		
		//ponovo?
		cout << "\nDa li zelite da uradite jos jedan primer?\n\t0: DA\n\t1: KRAJ\n";
		cin >> end;
	} while (end != 1);

	return 0;
}

string prosiriInfSekv(string i, string g)
{
	string ret = i;
	int br = g.length() - 1;
	for (int i = 0; i < br; i++) {
		ret += '0';
	}
	return ret;
}

pair<string, string> racunanjeOstatka(string i, string g)
{
	string ost;
	string rez = "";
	string pomOst;
	string pomRez;
	size_t sp = g.length();
	size_t duz = g.length();
	ost = i.substr(0, duz);

	while (sp<=i.length()) {
		pomOst = "";
		pomRez = "";
		for (size_t i = 0; i < duz; i++) {
			if (i == 0) {
				rez += ost[i];
				if (ost[i] == '0') {
					for (size_t pi = 0; pi < duz; pi++)
						pomOst += '0';
				}
				else {
					pomOst = g;
				}
			}
			int p = pomOst[i] - '0';
			int s = ost[i] - '0';
			int r = p ^ s;
			pomRez += to_string(r);

		}
		
		if (sp != i.length()) {
			ost = pomRez.substr(1, duz - 1);
			ost += i[sp++];
		}
		else {
			ost = pomRez.substr(1, duz - 1);
			sp++;
		}
			
	}
	
	return make_pair(ost, rez);
}

string skloniPocetneNule(string str)
{
	string ret = "";
	size_t ind = 0;
	int findFirst1 = 0;
	while (ind < str.length()) {
		if (str[ind] == '0' && findFirst1 == 0) {
			ind++;
			continue;
		}
		else if (str[ind] == '1' && findFirst1 == 0) {
			findFirst1 = 1;
			ret += str[ind++];
		}
		else {
			ret += str[ind++];
		}
	}

	return ret;
}

string ispisPol(string str)
{

	string pol = "";
	int duz = str.length();
	int stepen = duz - 1;
	int ind = 0;
	while (ind < duz) {
		if (str[ind] != '0') {
			if (ind == duz - 1) {
				pol += "1";
			}
			else{
				pol += "x^";
				pol += to_string(stepen);
			}
			pol += " + ";
		}

		stepen--;
		ind++;
	}
	duz = pol.length();
	pol = pol.substr(0, duz - 2);
	if (pol == "")
		pol = "0";
	return pol;
}

bool proveriDaLiJeBinarno(string str)
{
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != '0' && str[i] != '1')
			return false;
	}
	return true;
}

bool proveriDaLiJeNula(string str)
{
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != '0') return false;
	}
	return true;
}
