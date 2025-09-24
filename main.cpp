#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
using namespace std;

struct Studentas
{
    string vardas;
    string pavarde;
    vector<int> namudarbai;
    int egzaminas;
    double balasVid;
    double balasMed;
};

void bubbleSort(vector<int> &v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    int skaiciusstud;
    cout << "Iveskite studentu skaiciu: ";
    cin >> skaiciusstud;
    vector<Studentas> studentaivisi;
    for (int j = 0; j < skaiciusstud; j++)
    {
        Studentas stud;
        int ndSk;
        int pasirinkimas;
        cout << "\nIveskite studento varda ir pavarde: ";
        cin >> stud.vardas >> stud.pavarde;
        cout << "Ar norite ivesti pazymius pats (1), ar generuoti atsitiktinai (2)? ";
        cin >> pasirinkimas;
        if (pasirinkimas == 1)
        {
            cout << "Iveskite namu darbu skaiciu: (jei tikslaus skaiciaus nezinote iveskite 0) ";
            cin >> ndSk;
            cout << "Iveskite namu darbu rezultatus (iveskite 0 jei baigete): ";
            for (int i = 0; ; i++)
            {
                int n;
                cin >> n;
                if (n == 0) break;
                stud.namudarbai.push_back(n);
                if (ndSk != 0 && i + 1 >= ndSk) break;
            }
            cout << "Iveskite egzamino rezultata: ";
            cin >> stud.egzaminas;
        }
        else
        {
            cout << "Kiek namu darbu generuoti? ";
            cin >> ndSk;
            for (int i = 0; i < ndSk; i++)
            {
                stud.namudarbai.push_back(dist(gen));
            }
            stud.egzaminas = dist(gen);
            cout << "Sugeneruoti namu darbu pazymiai: ";
            for (int i = 0; i < stud.namudarbai.size(); i++) cout << stud.namudarbai[i] << " ";
            cout << " Egzaminas: " << stud.egzaminas << endl;
        }
        double sum = 0;
        for (int i = 0; i < stud.namudarbai.size(); i++)
        {
            sum += stud.namudarbai[i];
        }
        double vid = sum / stud.namudarbai.size();
        stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;
        bubbleSort(stud.namudarbai);
        double mediana;
        int n = stud.namudarbai.size();
        if (n % 2 == 1)
        {
            mediana = stud.namudarbai[n / 2];
        }
        else
        {
            mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
        }
        stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;
        studentaivisi.push_back(stud);
    }
    int med;
    cout << "Koki norite matyti rezultata" << endl;
    cout << "1 - vidurki" << endl;
    cout << "2 - mediana" << endl;
    cout << "3 - abu" << endl;
    cin >> med;
    cout << "\n"
         << left << setw(15) << "Pavarde"
         << setw(15) << "Vardas";
    if (med == 1)
        cout << setw(20) << "Galutinis (Vid.)";
    else if (med == 2)
        cout << setw(20) << "Galutinis (Med.)";
    else
        cout << setw(20) << "Galutinis (Vid.)"
             << setw(20) << "Galutinis (Med.)";
    cout << endl;
    if (med == 1)
        cout << string(50, '-') << endl;
    else if (med == 2)
        cout << string(50, '-') << endl;
    else
        cout << string(70, '-') << endl;
    for (int i = 0; i < studentaivisi.size(); i++)
    {
        cout << left << setw(15) << studentaivisi[i].pavarde
             << setw(15) << studentaivisi[i].vardas;
        if (med == 1)
            cout << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasVid;
        else if (med == 2)
            cout << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasMed;
        else
            cout << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasVid
                 << setw(20) << fixed << setprecision(2) << studentaivisi[i].balasMed;
        cout << endl;
    }
    for (int i = 0; i < studentaivisi.size(); i++) {
        if (studentaivisi[i].balasVid > 10 || studentaivisi[i].balasMed > 10) {
            cout << "Ar tikrai gerai ivedete duomenis studentui?????????? " << endl;
        }
    }
    return 0;
}
