////////////////////////////////////////////////////////////////////////////////////
// SPIELEDATENBANK UND AUSWAHLRANDOMIZER FUER GESELLSCHAFTSSPIELSAMMLUNGEN        //
////////////////////////////////////////////////////////////////////////////////////
// (C) CHRISTIAN SCHUCH 2014 ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<time.h>
//#include<conio.h> // on android
using namespace std;
const int spielzahl = 500;
string datenbank[spielzahl];	// globales array namen
string spieler[spielzahl];		// ab wievielen Spielern
string spieler_max[spielzahl];	// maximal mit wie vielen Spielern
string alter[spielzahl];		// globales array mindestalter
string laenge[spielzahl];		// globales array spiellaenge
string typ[spielzahl];			// globales array spielart
int position = 0;				// laufende nummer fuers einpflegen
// prototypen fuer die funktionen 
string conv(int);
void lottery();
void einpflegen();
void speichern();
void lesen();
void introlesen();
void anzeigen();
void suche();
void namensuche();
inline void CLS()
{
	system("cls"); // on windoof
	//for (int i=0;i<=20;i++) cout << "\n"; //ueberall
	// clrscr(); //on android
}
inline void pause ()
{
	system("PAUSE");
	//cout << endl << "0 zum zurueckkehren>";int raus;cin >> raus;//ueberall
}
char letter(string such,int pos);
void ausgabe(string);
string zufall(string,int);
void lottosuche();
// hauptprogramm (menue)
int main()
{
	introlesen();
	// menue
	int auswahl;
	do
	{
		cout << "--------------------------------------" << endl;
		cout << "|treffen sie ihre auswahl:           |" << endl;
		cout << "--------------------------------------" << endl;
		cout << "|[99]spiele anzeigen.                |" << endl;
		cout << "|[0]spiele einpflegen.               |" << endl;
		cout << "|[1]txt_file importieren.            |" << endl;
		cout << "|[2]spieldatenbank laden.            |" << endl;
		cout << "|[3]spieldatenbank speichern.        |" << endl;
		cout << "|[4]stichwortsuche.                  |" << endl;
		cout << "|[5]stichwortlotterie.               |" << endl;
		cout << "|[6]lotterie.                        |" << endl;
		cout << "|[7]ende.                            |" << endl;
		cout << "--------------------------------------" << endl;
		cout << "___________/>";
		cin >> auswahl;
		if (auswahl == 0)
			einpflegen();
		if (auswahl == 1)
			lesen();
		if (auswahl == 2)
			lesen();
		if (auswahl == 3)
			speichern();
		if (auswahl == 4)
			suche();
		if (auswahl == 5)
			lottosuche();
		if (auswahl == 6)
			lottery();
		if (auswahl == 99)
			anzeigen();
	}
	while (auswahl != 7);
	return 0;
}

int reconv(string code)
{
	int laenge = code.length();
	if (laenge == 1)
	{
		for (int i = 0; i < 10; i++)
			if (code.at(laenge - 1) == char ('0' + i))
				return i;
	}
	else
	{
		int summe = 0;
		for (int i = 0; i < 10; i++)
			if (code.at(laenge - 1) == char ('0' + i))
				summe = i;
		if (code.at(1) == char ('1'))
			summe += 10;
		if (code.at(1) == char ('2'))
			summe += 20;
		return summe;
	}
}

string conv(int zahl)
{
	switch (zahl)
	{
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	case 11:
		return "11";
	case 12:
		return "12";
	case 13:
		return "13";
	case 14:
		return "14";
	case 15:
		return "15";
	case 16:
		return "16";
	case 17:
		return "17";
	case 18:
		return "18";
	case 19:
		return "19";
	case 20:
		return "20";
	}
}

void lottery()
{
	srand(time(NULL));
	int x = rand() % 5 + 1;
	int y = rand() % 5 + 1;
	cout << "-------------------------------------------------" << endl;
	cout << "wieviele spiele gibt es in Spalte" << x << " und Reihe "
		<< y << ">";
	int spiele;
	cin >> spiele;
	cout << "Nehmen Sie Spiel nr." << rand() % spiele + 1 << endl;
	cout << "-------------------------------------------------" << endl;
	pause();
	CLS();
	return;
}

void einpflegen()
{
	cout << "------------------------------------------" << endl;
	cout << "name des spieles:";
	string name_ein;
	cin >> name_ein;
	//schon da?
	int sicherheit;
	bool flag=false;
	for (int i=0;i<position;i++)
	{
		if (datenbank[i]==name_ein)
		{
			cout << "schon vorhanden !"<<endl
				 << "ueberschreiben ?[0-ja][1-nein]";
			int check;
			cin >> check;
			if (check !=0)
				goto raus;
			else
			{
				sicherheit=position;
				position=i;
				flag=true;
			}
		}
	}
	datenbank[position]=name_ein;
	cout << "minimale Spielerzahl:";
	cin >> spieler[position];
	cout << "maximale Spielerzahl:";
	cin >> spieler_max[position];
	cout << "mindestalter:";
	cin >> alter[position];
	cout << "laenge [0(sehr kurz) bis 4(sehr lang)]:";
	cin >> laenge[position];
	cout << "spielart:" << endl;
	cout << "   (1)strategie" << endl;
	cout << "   (2)aufbau" << endl;
	cout << "   (3)fantasy sf escapistisch" << endl;
	cout << "   (4)karten" << endl;
	cout << "   (5)glueck" << endl;
	cout << "   (6)party" << endl;
	cout << "   (7)geschicklichkeit" << endl;
	cout << "   (8)kommunikation" << endl;
	cout << "(>";
	cin >> typ[position];
	if (flag!=true)
		position++;
	else
		position=sicherheit;
raus:
	cout << "------------------------------------------" << endl;
	return;
}

void speichern()
{
	ifstream test;
	// test.open("/sdcard/gamesbase.txt", ios::out | ios::binary); //
	// auf PAD
	test.open("gamesbase.txt", ios::out | ios::binary);	// nur auf PC
	// nicht im 
	// rest vergessen !!!
	if (!test)
	{
		test.close();
		goto allok;
	}
	else
	{
		cout << "datenbank schon vorhanden!\nersetzen[0-ja][1-nein]?";
		int check;
		cin >> check;
		if (check == 0)
			goto allok;
		else
			goto ende;
	}
  allok:						// Hier dann das normale Schreiben
	{
		ofstream schreiben;
		schreiben.open("gamesbase.txt", ios::out);
		for (int i = 0; i < position; i++)
		{
			schreiben << datenbank[i];
			schreiben << "\n";	// trenner
			schreiben << spieler[i];
			schreiben << "\n";	// trenner
			schreiben << spieler_max[i];
			schreiben << "\n";	// trenner
			schreiben << alter[i];
			schreiben << "\n";	// trenner
			schreiben << laenge[i];
			schreiben << "\n";	// trenner
			schreiben << typ[i];
			schreiben << "\n";	// trenner
		}
		schreiben << "*";		// endsignal
	} goto ende;
  ende:						// Ausstiegspunkt 
	return;
}
void introlesen()
{
	
	int i = 0;
	ifstream lesen;
	lesen.open("gamesbase.txt", ios::in);
	if(!lesen)
		return;
	string gelesen;
	bool flag = false;
	do
	{
		lesen >> gelesen;
		if (gelesen == "*")
		{
			break;
			flag = true;
		}
		datenbank[i] = gelesen;
		lesen >> gelesen;
		spieler[i] = gelesen;
		lesen >> gelesen;
		spieler_max[i] = gelesen;
		lesen >> gelesen;
		alter[i] = gelesen;
		lesen >> gelesen;
		laenge[i] = gelesen;
		lesen >> gelesen;
		typ[i] = gelesen;
		i++;
	}
	while (flag != true);
	position = i;
	cout <<">-------------DATENSTAND-------------<"<<endl;
	cout <<">----------------|"<<position<<"|---------------<"<<endl;
	cout <<">------------------------------------<"<<endl;
	return;
}


void lesen()
{
	cout << "-----------------------------------------" << endl;
	cout << "wirklich datenbank im speicher durch" << endl;
	cout << "datei-datenbank ersetzen ?[0-ja][1-nein]";
	int check;
	cin >> check;
	if (check == 0)
	{
		int i = 0;
		ifstream lesen;
		lesen.open("gamesbase.txt", ios::in);
		string gelesen;
		bool flag = false;
		do
		{
			lesen >> gelesen;
			if (gelesen == "*")
			{
				break;
				flag = true;
			}
			datenbank[i] = gelesen;
			lesen >> gelesen;
			spieler[i] = gelesen;
			lesen >> gelesen;
			spieler_max[i] = gelesen;
			lesen >> gelesen;
			alter[i] = gelesen;
			lesen >> gelesen;
			laenge[i] = gelesen;
			lesen >> gelesen;
			typ[i] = gelesen;
			i++;
		}
		while (flag != true);
		position = i;
	}
	cout << position << " datensätze eingelesen........"<<endl;
	cout << "-----------------------------------------" << endl;
	pause();
	CLS();
	return;
}

void ausgabe(int i)
{
	cout << "--------------------------------------" << endl;
	cout << "gefunden:" << datenbank[i] << endl
		<< "--------------------------------------" << endl
		<< "mindestspielerzahl:" << spieler[i] << endl
		<< "maximale spielerzahl:" << spieler_max[i] << endl
		<< "mindestalter(angabe):" << alter[i] << endl << "Spieldauer:";
	if (laenge[i] == "0")		// spieldauer in text umrechnen
		cout << "sehr kurz" << endl;
	if (laenge[i] == "1")
		cout << "kurz" << endl;
	if (laenge[i] == "2")
		cout << "mittel" << endl;
	if (laenge[i] == "3")
		cout << "lang" << endl;
	if (laenge[i] == "4")
		cout << "sehr lang" << endl;
	cout << "Spieltyp:";
	if (typ[i] == "1")			// spieltyp in text umrechnen
		cout << "strategie/denkspiel" << endl;
	if (typ[i] == "2")
		cout << "aufbauspiel" << endl;
	if (typ[i] == "3")
		cout << "eskapistisch(z.b.fantasy/\n         sf/spion etc)" << endl;
	if (typ[i] == "4")
		cout << "kartenspiel" << endl;
	if (typ[i] == "5")
		cout << "gluecks/wuerfelspiel" << endl;
	if (typ[i] == "6")
		cout << "partyspiel" << endl;
	if (typ[i] == "7")
		cout << "geschicklichkeitsspiel" << endl;
	if (typ[i] == "8")
		cout << "kommunikations/sprach/soziales spiel" << endl;
	cout << "--------------------------------------" << endl;

}

void anzeigen()
{
	cout << ">>>>>spiele:>>>>>" << endl << endl;
	int check;
	cout << "lang[0] oder kurz[1]form----?--->";
	cin >> check;
	if (check==1)
	{
		for (int i = 0; i < position; i+=2){
			cout << "(" << datenbank[i]<<")"<<endl;
			if (i+1<=position)
				cout <<"\t   ("<<datenbank[i+1]<<")"<<endl;}
		cout << endl << endl << "<<----------->>" << endl;
		pause();
		CLS();
		return;
	}
	else
	{
		for (int i = 0; i < position; i++)
			ausgabe(i);
		cout << endl << endl << "<<----------->>" << endl;
		pause();
		CLS();
		return;
	}

}
char letter(string such,int pos)
{
	return (such.at(pos));
}
int lstring(string such)
{
	return such.length();
}
void namensuche_by_call (string gesucht)
{
		string spielname;
		for (int eintrag=0;eintrag<position;eintrag++)	// AB 0 DA ARRAYS AB [0]
		{
			spielname=datenbank[eintrag];
			//FALLS DER KOMPLETTE SPIELENAME GEFUNDEN WIRD:
			if (spielname==gesucht)
			{
				ausgabe(eintrag);
				return;
			}
		}
}
void namensuche ()
{
		string gesucht;
		string sicherung;
		string spielname;
		string sammlung;								//FUER DIE BUCHSTABENSUCHE ALS ZIELGEFAESS
		char d;											//BUCHSTABE IN DATENBANK
		char g;											//BUCHSTABE IN SUCHSTRING
		int LSp=0;
		int endposition=0;								//WIE WEIT SUCHEN
		int buchstabe_ges=0;							//ZAEHLEN IM SUCHSTRING
		cout << "---->namen eingeben:";
		cin >> gesucht;									//EINGABE DES SUCHSTRINGS
		int LGes=lstring(gesucht);						//TATSAECHLICHE LAENGE DES SUCHSTRINGS
		for (int eintrag=0;eintrag<position;eintrag++)	// AB 0 DA ARRAYS AB [0]
		{
			spielname=datenbank[eintrag];			//AKTUELLER EINTRAG IN VARIABLE UEBERTRAGEN
			LSp=lstring(spielname);					//LAENGE DES ARRAYEINTRAGS IN DER SPIELEDATENBANK
			//FALLS DER KOMPLETTE SPIELENAME GEFUNDEN WIRD:
			if (spielname==gesucht)
			{
				ausgabe(eintrag);
				continue;
			}
			//FALLS NICHT, SUCHE IM STRING NACH AUFEINANDERFOLGENDER KOMBI
			endposition=LSp;				//DA DANACH NUR NOCH TEILWEISE SEIN KANN
			if (LSp<LGes)							//FALLS EINTRAG KUERZER ALS GESUCHT
				continue;
			//DIE EIGENTLICHE SUCHE:
			buchstabe_ges=0;
			for (int buchstabe=0;buchstabe<endposition;buchstabe++)
			{
				d=letter(spielname,buchstabe);
				g=letter(gesucht,buchstabe_ges);
				if (d==g)
				{
					sammlung+=d;
					buchstabe_ges++;
				}
				if (d!=g)
				{
					sammlung="";
					buchstabe_ges=0;
				}
				if (sammlung==gesucht)
				{
					ausgabe(eintrag);
					sammlung="";
					buchstabe_ges=0;
					break;
				}
			}


		}
}

void suche()
{
	CLS();
	cout << "--------------------------------------" << endl;
	cout << "was soll gesucht werden ?" << endl;
	cout << "--------------------------------------" << endl;
	cout << "[0]namen suchen (eintrag anzeigen)" << endl;
	cout << "[1]nach einzelkriterien suchen" << endl;
	cout << "[2]nach kombination suchen" << endl;
	cout << "[alles andere]<zurueck<" << endl;
	cout << "--------------------------------------" << endl;
	cout << "--->";
	int eingabe;
	cin >> eingabe;
	if (eingabe == 0)
		namensuche();
	if (eingabe == 1)
	{
		CLS();
		cout << "--------------------------------------" << endl;
		cout << "nach welchem kriterium suchen?" << endl;
		cout << "--------------------------------------" << endl;
		cout << "[1]spielerzahl" << endl;
		cout << "[2]mindestalter" << endl;
		cout << "[3]laenge" << endl;
		cout << "[4]spielart" << endl;
		cout << "-------------------------------------" << endl;
		cout << ">>" << endl;
		int krit;
		cin >> krit;
		int wert;
		if (krit==4)
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,7-geschick,\n8-kommunikation]-?->";
		else
			cout << "-----wert--->";
		cin >> wert;
		string wertc = conv(wert);
		cout << wertc << endl;
		for (int i = 0; i < position; i++)
		{
			if ((krit == 1) && (reconv(spieler_max[i]) >= wert) && (reconv(spieler[i]) <= wert))
				ausgabe(i);
			if ((krit == 2) && (reconv(alter[i]) <= wert))
				ausgabe(i);
			if ((krit == 3) && (reconv(laenge[i]) == wert))
				ausgabe(i);
			if ((krit == 4) && (reconv(typ[i]) == wert))
				ausgabe(i);
		}

	}
	if (eingabe == 2)
	{
		CLS();
		cout << "-------------------------------------" << endl;
		cout << "nach welcher kombination suchen?" << endl;
		cout << "-------------------------------------" << endl;
		cout << "[0]alter&spielerzahl" << endl;
		cout << "[1]alter&typ" << endl;
		cout << "[2]alter&laenge" << endl;
		cout << "[3]spielerzahl&laenge" << endl;
		cout << "[4]spielerzahl&typ" << endl;
		cout << "[5]laenge&typ" << endl;
		cout << "-------------------------------------" << endl;
		cout << "-------->";
		int eingabe2;
		cin >> eingabe2;
		if (eingabe2 == 0)
		{
			cout << "alter:";
			int alt;
			cin >>alt;
			cout << "spielerzahl:";
			int szahl;
			cin >>szahl;
			int decision;
			cout << "kurzausgabe reicht ?[0-ja][1-nein]";
			cin >> decision;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < position; i++)
			{
				if ((reconv(alter[i]) <= alt) && (reconv(spieler_max[i]) >= szahl) && (reconv(spieler[i]) <= szahl))
				{
					if (decision==1) 
						ausgabe(i);
					else
						cout <<"   <>"<<datenbank[i];
				}
			}
			cout << endl<<"-------------------------------------" << endl;
		}
		if (eingabe2 == 1)
		{
			cout << "alter:";
			int alt;
			cin >>alt;
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,\n7-geschick,8-kom.]:";
			int szahl;
			cin >>szahl;
			int decision;
			cout << "kurzausgabe reicht ?[0-ja][1-nein]";
			cin >> decision;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < position; i++)
			{
				if ((reconv(alter[i]) <= alt) && (reconv(typ[i]) == szahl))
				{
					if (decision==1) 
						ausgabe(i);
					else
						cout <<"   <>"<<datenbank[i];
				}
			}
			cout << endl<<"-------------------------------------" << endl;
		}
		if (eingabe2 == 2)
		{
			cout << "alter:";
			int alt;
			cin >>alt;
			cout << "laenge:";
			int szahl;
			cin >>szahl;
			int decision;
			cout << "kurzausgabe reicht ?[0-ja][1-nein]";
			cin >> decision;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < position; i++)
			{
				if ((reconv(alter[i]) <= alt) && (reconv(laenge[i]) == szahl))
				{
					if (decision==1) 
						ausgabe(i);
					else
						cout <<"   <>"<<datenbank[i];
				}
			}
			cout << endl<<"-------------------------------------" << endl;
		}
		if (eingabe2 == 3)
		{
			cout << "spielerzahl:";
			int alt;
			cin >>alt;
			cout << "laenge:";
			int szahl;
			cin >>szahl;
			int decision;
			cout << "kurzausgabe reicht ?[0-ja][1-nein]";
			cin >> decision;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < position; i++)
			{
				if ((reconv(spieler_max[i]) >= alt) && (reconv(spieler[i]) <= alt) && (reconv(laenge[i]) == szahl))
				{
					if (decision==1) 
						ausgabe(i);
					else
						cout <<"   <>"<<datenbank[i];
				}
			}
			cout << endl<<"-------------------------------------" << endl;
		}
		if (eingabe2 == 4)
		{
			cout << "spielerzahl:";
			int alt;
			cin >>alt;
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,\n7-geschick,8-kom.]:";
			int szahl;
			cin >>szahl;
			int decision;
			cout << "kurzausgabe reicht ?[0-ja][1-nein]";
			cin >> decision;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < position; i++)
			{
				if ((reconv(spieler_max[i]) >= alt) && (reconv(spieler[i]) <= alt) && (reconv(typ[i]) == szahl))
				{
					if (decision==1) 
						ausgabe(i);
					else
						cout <<"   <>"<<datenbank[i];
				}
			}
			cout << endl<<"-------------------------------------" << endl;
		}
		if (eingabe2 == 5)
		{
			cout << "laenge:";
			int alt;
			cin >>alt;
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,\n7-geschick,8-kom.]:";
			int szahl;
			cin >>szahl;
			int decision;
			cout << "kurzausgabe reicht ?[0-ja][1-nein]";
			cin >> decision;
			cout << "-------------------------------------" << endl;
			for (int i = 0; i < position; i++)
			{
				if ((reconv(laenge[i]) == alt) && (reconv(typ[i]) == szahl))
				{
					if (decision==1) 
						ausgabe(i);
					else
						cout <<"   <>"<<datenbank[i];
				}
			}
			cout << endl<<"-------------------------------------" << endl;
		}
		cout << endl << endl << "<<----------->>" << endl;
		
	}
	pause();
	CLS();
	return;
}
string zufall(string daten[],int anzahl)
{
	int auswahl=0;
		srand(time(NULL));
		auswahl = rand() % anzahl + 1;
	if (daten[auswahl]=="")
		return "leider kein spiel, da nichts\n gefunden wurde";
	return daten[auswahl];
}
void lottosuche()
{
	CLS();
	cout << "--------------------------------------" << endl;
	cout << "wonach soll die lotterie suchen ?" << endl;
	cout << "--------------------------------------" << endl;
	cout << "[0]nach einzelkriterien suchen" << endl;
	cout << "[1]nach kombination suchen" << endl;
	cout << "[alles andere]<zurueck<" << endl;
	cout << "--------------------------------------" << endl;
	cout << "--->";
	int eingabe;
	cin >> eingabe;
	if (eingabe == 0)//nach einzelkriterien wuerfeln
	{
		CLS();
		cout << "--------------------------------------" << endl;
		cout << "nach welchem kriterium suchen?" << endl;
		cout << "--------------------------------------" << endl;
		cout << "[1]spielerzahl"<<endl;
		cout << "[2]mindestalter" << endl;
		cout << "[3]laenge" << endl;
		cout << "[4]spielart" << endl;
		cout << "-------------------------------------" << endl;
		cout << ">>" << endl;
		int krit;
		cin >> krit;
		int wert;
		if (krit == 4)
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,7-geschick,\n8-kommunikation]-?->";
		else
			cout << "-----wert--?->";
		cin >> wert;
		string wertc = conv(wert);
		cout << wertc << endl;
		int count=0;
		for (int i = 0; i < position; i++)//zaehldurchlauf
		{
			if ((krit == 1) && (reconv(spieler_max[i]) >= wert) && (reconv(spieler[i])<= wert))
				count++;
			if ((krit == 2) && (reconv(alter[i]) <= wert))
				count++;
			if ((krit == 3) && (reconv(laenge[i]) == wert))
				count++;
			if ((krit == 4) && (reconv(typ[i]) == wert))
				count++;
		}
		string *wuerfel=new string[count+1];//dynamisches array fuers wuerfeln (visual studio zeigt fehler)
		int k=0;
		for (int i = 0; i < position; i++)//der tatsaechliche suchlauf
		{
			if ((krit == 1) && (reconv(spieler_max[i]) >= wert) && (reconv(spieler[i]) <= wert))
			{wuerfel[k]=datenbank[i];k++;}
			if ((krit == 2) && (reconv(alter[i]) <= wert))
			{wuerfel[k]=datenbank[i];k++;}
			if ((krit == 3) && (reconv(laenge[i]) == wert))
			{wuerfel[k]=datenbank[i];k++;}
			if ((krit == 4) && (reconv(typ[i]) == wert))
			{wuerfel[k]=datenbank[i];k++;}
		}
		string erwuerfelt=zufall(wuerfel,count);
		cout	<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<erwuerfelt<<endl
				<<"--------------------------------------"<<endl;
				namensuche_by_call(erwuerfelt);
		delete[]wuerfel;
		k=0;
	}
	if (eingabe == 1)
	{
		CLS();
		cout << "-------------------------------------" << endl;
		cout << "nach welcher kombination suchen?" << endl;
		cout << "-------------------------------------" << endl;
		cout << "[0]alter&spielerzahl" << endl;
		cout << "[1]alter&typ" << endl;
		cout << "[2]alter&laenge" << endl;
		cout << "[3]spielerzahl&laenge" << endl;
		cout << "[4]spielerzahl&typ" << endl;
		cout << "[5]laenge&typ" << endl;
		cout << "-------------------------------------" << endl;
		cout << "-------->";
		int eingabe2;
		cin >> eingabe2;
		if (eingabe2 == 0)//ALTER UND SPIELERZAHL
		{
			cout << "alter:";
			int alt;
			cin >>alt;
			cout << "spielerzahl:";
			int szahl;
			cin >>szahl;
			cout << "-------------------------------------" << endl;
			int count=0;
			for (int i = 0; i < position; i++)//zaehlschleife
			{
				if ((reconv(alter[i]) <= alt) && (reconv(spieler_max[i]) >= szahl) && (reconv(spieler[i]) <= szahl))
				{
					count++;
				}
			}
			string *wuerfel=new string[count+1];
			int k=0;//zaehlvariable fuer wuerfel
			for (int i = 0; i < position; i++)
			{
				if ((reconv(alter[i]) <= alt) && (reconv(spieler_max[i]) >= szahl) && (reconv(spieler[i]) <= szahl))
				{
					wuerfel[k]=datenbank[i];
					k++;
				}
			}
			string erwuerfelt=zufall(wuerfel,count);
		cout	<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<erwuerfelt<<endl
				<<"--------------------------------------"<<endl;
				namensuche_by_call(erwuerfelt);
		delete[]wuerfel;
		k=0;
		}
		if (eingabe2 == 1)
		{
			cout << "alter:";
			int alt;
			cin >>alt;
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,\n7-geschick,8-kom.]:";
			int szahl;
			cin >>szahl;
			cout << "-------------------------------------" << endl;
			int count=0;
			for (int i = 0; i < position; i++)//zaehlschleife
			{
				if ((reconv(alter[i]) <= alt) && (reconv(typ[i]) == szahl))
				{
					count++;
				}
			}
			string *wuerfel=new string[count+1];
			int k=0;//zaehlvariable fuer wuerfel
			for (int i = 0; i < position; i++)
			{
				if ((reconv(alter[i]) <= alt) && (reconv(typ[i]) == szahl))
				{
					wuerfel[k]=datenbank[i];
					k++;
				}
			}
			cout<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<zufall(wuerfel,count)<<endl
				<<"--------------------------------------"<<endl;
		delete[]wuerfel;
		k=0;
		}
		if (eingabe2 == 2)
		{
			cout << "alter:";
			int alt;
			cin >>alt;
			cout << "laenge:";
			int szahl;
			cin >>szahl;
			cout << "-------------------------------------" << endl;
			int count=0;
			for (int i = 0; i < position; i++)//zaehlschleife
			{
				if ((reconv(alter[i]) <= alt) && (reconv(laenge[i]) == szahl))
				{
					count++;
				}
			}
			string *wuerfel=new string[count+1];
			int k=0;//zaehlvariable fuer wuerfel
			for (int i = 0; i < position; i++)
			{
				if ((reconv(alter[i]) <= alt) && (reconv(laenge[i]) == szahl))
				{
					wuerfel[k]=datenbank[i];
					k++;
				}
			}
			string erwuerfelt=zufall(wuerfel,count);
		cout	<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<erwuerfelt<<endl
				<<"--------------------------------------"<<endl;
				namensuche_by_call(erwuerfelt);
		delete[]wuerfel;
		k=0;
		}
		if (eingabe2 == 3)
		{
			cout << "spielerzahl:";
			int alt;
			cin >>alt;
			cout << "laenge:";
			int szahl;
			cin >>szahl;
			int count=0;
			for (int i = 0; i < position; i++)//zaehlschleife
			{
				if ((reconv(spieler_max[i]) >= alt) && (reconv(spieler[i]) <= alt) && (reconv(laenge[i]) == szahl))
				{
					count++;
				}
			}
			string *wuerfel=new string[count+1];
			int k=0;//zaehlvariable fuer wuerfel
			for (int i = 0; i < position; i++)
			{
				if ((reconv(spieler_max[i]) >= alt) && (reconv(spieler[i]) <= alt) && (reconv(laenge[i]) == szahl))
				{
					wuerfel[k]=datenbank[i];
					k++;
				}
			}
			string erwuerfelt=zufall(wuerfel,count);
		cout	<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<erwuerfelt<<endl
				<<"--------------------------------------"<<endl;
				namensuche_by_call(erwuerfelt);
		delete[]wuerfel;
		k=0;
		}
		if (eingabe2 == 4)
		{
			cout << "spielerzahl:";
			int alt;
			cin >>alt;
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,\n7-geschick,8-kom.]:";
			int szahl;
			cin >>szahl;
			cout << "-------------------------------------" << endl;
			int count=0;
			for (int i = 0; i < position; i++)//zaehlschleife
			{
				if ((reconv(spieler_max[i]) >= alt) && (reconv(spieler[i]) <= alt) && (reconv(typ[i]) == szahl))
				{
					count++;
				}
			}
			string *wuerfel=new string[count+1];
			int k=0;//zaehlvariable fuer wuerfel
			for (int i = 0; i < position; i++)
			{
				if ((reconv(spieler_max[i]) >= alt) && (reconv(spieler[i]) <= alt) && (reconv(typ[i]) == szahl))
				{
					wuerfel[k]=datenbank[i];
					k++;
				}
			}
			string erwuerfelt=zufall(wuerfel,count);
		cout	<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<erwuerfelt<<endl
				<<"--------------------------------------"<<endl;
				namensuche_by_call(erwuerfelt);
		delete[]wuerfel;
		k=0;
		}
		if (eingabe2 == 5)
		{
			cout << "laenge:";
			int alt;
			cin >>alt;
			cout << "typ[1-strategie,2-aufbau,3-escap.,\n4-karten,5-glueck,6-party,\n7-geschick,8-kom.]:";
			int szahl;
			cin >>szahl;
			cout << "-------------------------------------" << endl;
			int count=0;
			for (int i = 0; i < position; i++)//zaehlschleife
			{
				if ((reconv(laenge[i]) == alt) && (reconv(typ[i]) == szahl))
				{
					count++;
				}
			}
			string *wuerfel=new string[count+1];
			int k=0;//zaehlvariable fuer wuerfel
			for (int i = 0; i < position; i++)
			{
				if ((reconv(laenge[i]) == alt) && (reconv(typ[i]) == szahl))
				{
					wuerfel[k]=datenbank[i];
					k++;
				}
			}
			string erwuerfelt=zufall(wuerfel,count);
		cout	<<"--------------------------------------"<<endl
				<<"nehmen sie:"<<erwuerfelt<<endl
				<<"--------------------------------------"<<endl;
				namensuche_by_call(erwuerfelt);
		delete[]wuerfel;
		k=0;
		}
		cout << endl << endl << "<<----------->>" << endl;

	}
	pause();
	CLS();
	return;
}