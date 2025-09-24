#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Studentas
{
    string vardas;
    string pavarde;
    vector<int> namudarbai;
    int egzaminas;
    double balas;
};

int main()
{
    int skaiciusstud;
    cout << "Iveskite studentu skaiciu" << endl;
    cin >> skaiciusstud;
    vector<Studentas> studentaivisi;
    Studentas stud;
    for (int j = 0; j < skaiciusstud; j++)
    {
        int ndSk;
        cout << "Iveskite studento varda ir pavarde";
        cin >> stud.vardas >> stud.pavarde;
        cout << "Iveskite namu darbu skaiciu";
        cin >> ndSk;
        cout << "Iveskite namu darbu rezultatus";
        for (int i = 0; i < ndSk; i++)
        {
            int n;
            cin >> n;
            stud.namudarbai.push_back(n);
        }
        cout << "Iveskite egzamino rezultata" << endl;
        cin >> stud.egzaminas;

        double sum = 0;
        for (int i = 0; i < stud.namudarbai.size(); i++) {
            sum += stud.namudarbai[i];
        }  
        double vid = sum/stud.namudarbai.size();

        stud.balas = 0.4 * vid + 0.6 * stud.egzaminas;
        studentaivisi.push_back(stud);
    }
        cout << left << setw(15) << "Pavarde"
         << setw(15) << "Vardas"
         << setw(15) << "Galutinis (Vid.)" << endl;

    cout << string(45, '-') << endl;

    for (int i = 0; i < studentaivisi.size(); i++)
    {
        cout << left << setw(15) << studentaivisi[i].pavarde
             << setw(15) << studentaivisi[i].vardas
             << setw(15) << fixed << setprecision(2) << studentaivisi[i].balas
             << endl;
    }

    return 0;
}
