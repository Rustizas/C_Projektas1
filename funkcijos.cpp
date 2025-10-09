#include "studentas.h"

void bubbleSort(vector<int> &v) //sortas
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
int randomPazymys(mt19937 &gen)
{
    uniform_int_distribution<> dist(1, 10);
    return dist(gen);
}

void generuotiFaila(const string &failoVardas, int kiekis)
{
    ofstream out(failoVardas);
    random_device rd;
    mt19937 gen(rd());
    int ndKiekis = 5; // namu darbu skaicius
    out << left << setw(15) << "Vardas"
        << setw(15) << "Pavarde";
    for (int i = 1; i <= ndKiekis; i++) // sugeneruojam namu darbu stulpelius
        out << setw(10) << ("ND" + to_string(i));
    out << setw(10) << "Egzaminas" << endl;

    for (int i = 1; i <= kiekis; i++)
    {
        out << left << setw(15) << ("Vardas" + to_string(i))
            << setw(15) << ("Pavarde" + to_string(i));

        for (int j = 0; j < ndKiekis; j++) // sugeneruojam random studentu pazymius
        {
            int paz = randomPazymys(gen);
            out << setw(10) << paz;
        }

        int egz = randomPazymys(gen);
        out << setw(10) << egz << endl; // surasom pazymio duomenis i faila
    }
    out.close();
    cout << "Failas \"" << failoVardas << "\" sukurtas (" << kiekis << " įrašų)." << endl;
}

void generuotiVisusFailus()
{
    cout << "." << endl;
    vector<int> dydziai;
    dydziai.push_back(1000);
    dydziai.push_back(10000);
    dydziai.push_back(100000);
    dydziai.push_back(1000000);
    dydziai.push_back(10000000); // pridedam elementus i vektoriu
   for (int i = 0; i < dydziai.size(); i++)
    {
        int dydis = dydziai[i];
        string failoVardas = "studentai_" + to_string(dydis) + ".txt";
        generuotiFaila(failoVardas, dydis);
    }
}

void padalintiStudentus(const vector<Studentas>& visi)
{
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai; // sukuriam vektorius

    // Padalinam studentus i dvi grupes
     for (int i = 0; i < visi.size(); i++)
    {
        double galutinis = visi[i].balasVid; 
        if (galutinis < 5.0)
            vargsiukai.push_back(visi[i]);
        else
            kietiakiai.push_back(visi[i]);
    }

    // Isvedame vargsiukus
    ofstream os("vargsiukai.txt");
    os << left << setw(15) << "Pavarde"
       << setw(15) << "Vardas"
       << setw(20) << "Galutinis (Vid.)" << endl;
    os << string(50, '-') << endl;

   for (int i = 0; i < vargsiukai.size(); i++)
    {
        os << left << setw(15) << vargsiukai[i].pavarde
           << setw(15) << vargsiukai[i].vardas
           << setw(20) << fixed << setprecision(2) << vargsiukai[i].balasVid << endl;
    }
    os.close(); // uzdarom faila
    os.open("kietiakiai.txt"); 
    os << left << setw(15) << "Pavarde"
       << setw(15) << "Vardas"
       << setw(20) << "Galutinis (Vid.)" << endl;
    os << string(50, '-') << endl;

     for (int i = 0; i < kietiakiai.size(); i++)
    {
        os << left << setw(15) << kietiakiai[i].pavarde
           << setw(15) << kietiakiai[i].vardas
           << setw(20) << fixed << setprecision(2) << kietiakiai[i].balasVid << endl;
    }
    os.close();
    cout << "Failai sukurti" << endl;
}