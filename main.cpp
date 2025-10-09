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
    cout << "3 - sugeneruoti 5 failus skirtingu dydziu" << endl;
    cin >> pasirinkimas;

    if (pasirinkimas == 3)
    {
        generuotiVisusFailus();
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
}
    int med;
    cout << "Koki norite matyti rezultata" << endl;
    cout << "1 - vidurki" << endl;
    cout << "2 - mediana" << endl;
    cout << "3 - abu" << endl;
    cin >> med;

    cout << "\n" << left << setw(15) << "Pavarde"
         << setw(15) << "Vardas";
    if (med == 1) cout << setw(20) << "Galutinis (Vid.)";
    else if (med == 2) cout << setw(20) << "Galutinis (Med.)";
    else cout << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)";
    cout << endl;
    if (med == 3) cout << string(70, '-') << endl;
    else cout << string(50, '-') << endl;

    for (int i = 0; i < studentaivisi.size(); i++)
    {
        cout << left << setw(15) << studentaivisi[i].pavarde
             << setw(15) << studentaivisi[i].vardas;
        if (med == 1) cout << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasVid;
        else if (med == 2) cout << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasMed;
        else cout << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasVid
                  << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasMed;
        cout << endl;
    }
    padalintiStudentus(studentaivisi);
    return 0;
}