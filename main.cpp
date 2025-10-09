#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono> 
using namespace std;
#include "studentas.h"


int main()
{
    random_device rd; // generuojam random seed gauti atsitiktinius ir skirtingus duomenis
    mt19937 gen(rd()); // aprasom generatoriu
    uniform_int_distribution<> dist(1, 10); // nustatom intervala
    vector<Studentas> studentaivisi;
    int pasirinkimas;
    cout << "Pasirinkite duomenu ivedimo buda:" << endl;
    cout << "1 - ivedimas ranka" << endl;
    cout << "2 - nuskaitymas is failo" << endl;
    cout << "3 - sugeneruoti 5 failus skirtingu dydziu ir atlikti testavima" << endl;
    cin >> pasirinkimas;

    if (pasirinkimas == 3)
    {
        vector<int> dydziai;
        dydziai.push_back(1000);
        dydziai.push_back(10000);
        dydziai.push_back(100000);
        dydziai.push_back(1000000);
        dydziai.push_back(10000000);

        for (int i = 0; i < dydziai.size(); i++)
        {
            int dydis = dydziai[i];
            string failoVardas = "studentai_" + to_string(dydis) + ".txt";
            cout << endl;
            cout << "Failas uzdarytas" << endl;
            generuotiFaila(failoVardas, dydis);

            chrono::high_resolution_clock::time_point startViso = chrono::high_resolution_clock::now();
            chrono::high_resolution_clock::time_point startNuskaitymas = chrono::high_resolution_clock::now(); // pradedam matuoti laika  

            ifstream in(failoVardas);
            string eilute;
            getline(in, eilute); 
            int stulpeliai = 0;
            string zodis;
            stringstream p(eilute);
            while (p >> zodis) stulpeliai++;
            int ndSk = stulpeliai - 3;

            vector<Studentas> studentaivisi;
            while (true)
            {
                Studentas stud;
                if (!(in >> stud.vardas >> stud.pavarde)) break; // tikrinam ar pavyko nuskaityti faila
                stud.namudarbai.clear();
                for (int j = 0; j < ndSk; j++)
                {
                    int paz;
                    in >> paz;
                    stud.namudarbai.push_back(paz);
                }
                in >> stud.egzaminas;
                double sum = 0;
                for (int j = 0; j < stud.namudarbai.size(); j++) sum += stud.namudarbai[j]; // sudedam namu darbu pazymius 
                double vid = sum / stud.namudarbai.size(); //suskaiciuojam vidurki
                stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;
                bubbleSort(stud.namudarbai);
                double mediana;
                int n = stud.namudarbai.size();
                if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
                else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
                stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;
                studentaivisi.push_back(stud);
            }
            in.close();

            chrono::high_resolution_clock::time_point endNuskaitymas = chrono::high_resolution_clock::now();
            chrono::duration<double> trukmeNuskaitymas = endNuskaitymas - startNuskaitymas; // nustojam skaiciuot laika ir suskaiciuojam skirtuma

            cout << "Failo is " << dydis << " irasu nuskaitymo laikas: " << fixed << setprecision(6) << trukmeNuskaitymas.count() << " s" << endl;

            chrono::high_resolution_clock::time_point startDalijimas = chrono::high_resolution_clock::now();
            padalintiStudentus(studentaivisi);
            chrono::high_resolution_clock::time_point endDalijimas = chrono::high_resolution_clock::now();
            chrono::duration<double> trukmeDalijimas = endDalijimas - startDalijimas;

            chrono::high_resolution_clock::time_point endViso = chrono::high_resolution_clock::now();
            chrono::duration<double> trukmeViso = endViso - startViso;

            cout << dydis << " studentu padalijimo is viso laikas: " << fixed << setprecision(6) << trukmeViso.count() << " s" << endl;
            cout << endl;
        }
        return 0;
    }

    if (pasirinkimas == 1)
    {
        int skaiciusstud;
        cout << "Iveskite studentu skaiciu: " << endl;
        cin >> skaiciusstud;
        for (int j = 0; j < skaiciusstud; j++)
        {
            Studentas stud;
            int ndSk;
            int ivestis;
            cout << "Iveskite studento varda ir pavarde: " << endl;
            cin >> stud.vardas >> stud.pavarde;
            cout << "Ar norite ivesti pazymius pats (1), ar generuoti atsitiktinai (2)? " << endl;
            cin >> ivestis;
            if (ivestis == 1)
            {
                cout << "Iveskite namu darbu skaiciu (0 jei nezinote): " << endl;
                cin >> ndSk;
                cout << "Iveskite namu darbu rezultatus (0 jei baigete): " << endl;
                for (int i = 0;; i++)
                {
                    int n;
                    cin >> n;
                    if (n == 0) break;
                    stud.namudarbai.push_back(n);
                    if (ndSk != 0 && i + 1 >= ndSk) break;
                }
                cout << "Iveskite egzamino rezultata: " << endl;
                cin >> stud.egzaminas;
            }
            else
            {
                cout << "Kiek namu darbu generuoti? " << endl;
                cin >> ndSk;
                for (int i = 0; i < ndSk; i++)
                {
                    stud.namudarbai.push_back(dist(gen));
                }
                stud.egzaminas = dist(gen);
                cout << "Sugeneruoti ND: ";
                for (int i = 0; i < stud.namudarbai.size(); i++) cout << stud.namudarbai[i] << " ";
                cout << " Egzaminas: " << stud.egzaminas << endl;
            }

            double sum = 0;
            for (int i = 0; i < stud.namudarbai.size(); i++) sum += stud.namudarbai[i];
            double vid = sum / stud.namudarbai.size();
            stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;

            bubbleSort(stud.namudarbai);
            double mediana;
            int n = stud.namudarbai.size();
            if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
            else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
            stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;

            studentaivisi.push_back(stud);
        }
    }
    else if (pasirinkimas == 2)
    {
        string Pav;
        cout << "Iveskite failo pavadinima: " << endl;
        cin >> Pav;
        chrono::high_resolution_clock::time_point startViso = chrono::high_resolution_clock::now();
        chrono::high_resolution_clock::time_point startNuskaitymas = chrono::high_resolution_clock::now(); // pradedam matuoti laika  
        ifstream in(Pav);
        string eilute;
        getline(in, eilute); 
        int stulpeliai = 0;
        string zodis;
        stringstream p(eilute);
        while (p >> zodis) stulpeliai++;
        int ndSk = stulpeliai - 3;
        while (true)
        {
            Studentas stud;
            if (!(in >> stud.vardas >> stud.pavarde)) break; // tikrinam ar pavyko nuskaityti faila
            stud.namudarbai.clear();
            for (int i = 0; i < ndSk; i++)
            {
                int paz;
                in >> paz;
                stud.namudarbai.push_back(paz);
            }
            in >> stud.egzaminas;
            double sum = 0;
            for (int i = 0; i < stud.namudarbai.size(); i++) sum += stud.namudarbai[i]; // sudedam namu darbu pazymius 
            double vid = sum / stud.namudarbai.size(); //suskaiciuojam vidurki
            stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;
            bubbleSort(stud.namudarbai);
            double mediana;
            int n = stud.namudarbai.size();
            if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
            else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
            stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;
            studentaivisi.push_back(stud);
        }
        in.close();
        chrono::high_resolution_clock::time_point endNuskaitymas = chrono::high_resolution_clock::now();
        chrono::duration<double> trukmeNuskaitymas = endNuskaitymas - startNuskaitymas; // nustojam skaiciuot laika ir suskaiciuojam skirtuma

        cout << "Failo is " << studentaivisi.size() << " irasu nuskaitymo laikas: " << fixed << setprecision(6) << trukmeNuskaitymas.count() << " s" << endl;

        padalintiStudentus(studentaivisi);
        chrono::high_resolution_clock::time_point endViso = chrono::high_resolution_clock::now();
        chrono::duration<double> trukmeViso = endViso - startViso;
        cout << studentaivisi.size() << " irasu testo laikas: " << fixed << setprecision(6) << trukmeViso.count() << " s" << endl;
    }
    return 0;
}
