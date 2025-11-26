#include "studentas.h"

void bubbleSort(vector<int> &v)
{
    for (int i = 0; i < (int)v.size() - 1; i++)
        for (int j = 0; j < (int)v.size() - i - 1; j++)
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
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
    int ndKiekis = 5;

    out << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= ndKiekis; i++)
        out << setw(10) << ("ND" + to_string(i));
    out << setw(10) << "Egzaminas" << endl;

    for (int i = 1; i <= kiekis; i++)
    {
        out << left << setw(15) << ("Vardas" + to_string(i))
            << setw(15) << ("Pavarde" + to_string(i));

        for (int j = 0; j < ndKiekis; j++)
            out << setw(10) << randomPazymys(gen);
        out << setw(10) << randomPazymys(gen) << endl;
    }
    out.close();
    cout << "Failas \"" << failoVardas << "\" sukurtas (" << kiekis << " įrašų)." << endl;
}

void generuotiVisusFailus()
{
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    for (int dydis : dydziai)
    {
        string failoVardas = "studentai_" + to_string(dydis) + ".txt";
        auto start = chrono::high_resolution_clock::now();
        generuotiFaila(failoVardas, dydis);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> trukme = end - start;
        cout << "Failo \"" << failoVardas << "\" kūrimas užtruko: "
             << fixed << setprecision(3) << trukme.count() << " s" << endl;
    }
}

void padalintiStudentus_strategija1(const vector<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet)
{
    auto startRusiavimas = chrono::high_resolution_clock::now();
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakiai;

    vargsiukai.reserve(visi.size());
    kietiakiai.reserve(visi.size());

    for (const auto &s : visi)
        (s.balasVid < 5.0 ? vargsiukai : kietiakiai).push_back(s);

    auto endRusiavimas = chrono::high_resolution_clock::now();
    tRusiavimas = chrono::duration<double>(endRusiavimas - startRusiavimas).count();

    auto startVargsiukai = chrono::high_resolution_clock::now();
    {
        ofstream os("vargsiukai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : vargsiukai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endVargsiukai = chrono::high_resolution_clock::now();
    tWriteVargs = chrono::duration<double>(endVargsiukai - startVargsiukai).count();

    auto startKietiakiai = chrono::high_resolution_clock::now();
    {
        ofstream os("kietiakiai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : kietiakiai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endKietiakiai = chrono::high_resolution_clock::now();
    tWriteKiet = chrono::duration<double>(endKietiakiai - startKietiakiai).count();

    cout << visi.size() << " įrašų: rūšiavimas = " << fixed << setprecision(6) << tRusiavimas
         << " s, vargsiukai->failas = " << tWriteVargs
         << " s, kietiakiai->failas = " << tWriteKiet << " s" << endl;
}

void padalintiStudentus_strategija1(const list<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet)
{
    auto startRusiavimas = chrono::high_resolution_clock::now();
    list<Studentas> vargsiukai;
    list<Studentas> kietiakiai;

    for (const auto &s : visi)
        (s.balasVid < 5.0 ? vargsiukai : kietiakiai).push_back(s);

    auto endRusiavimas = chrono::high_resolution_clock::now();
    tRusiavimas = chrono::duration<double>(endRusiavimas - startRusiavimas).count();

    auto startVargsiukai = chrono::high_resolution_clock::now();
    {
        ofstream os("vargsiukai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : vargsiukai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endVargsiukai = chrono::high_resolution_clock::now();
    tWriteVargs = chrono::duration<double>(endVargsiukai - startVargsiukai).count();

    auto startKietiakiai = chrono::high_resolution_clock::now();
    {
        ofstream os("kietiakiai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : kietiakiai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endKietiakiai = chrono::high_resolution_clock::now();
    tWriteKiet = chrono::duration<double>(endKietiakiai - startKietiakiai).count();

    cout << visi.size() << " įrašų: rūšiavimas = " << fixed << setprecision(6) << tRusiavimas
         << " s, vargsiukai->failas = " << tWriteVargs
         << " s, kietiakiai->failas = " << tWriteKiet << " s" << endl;
}

void padalintiStudentus_strategija2(vector<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet)
{
    auto startRusiavimas = chrono::high_resolution_clock::now();
    vector<Studentas> vargsiukai;
    vargsiukai.reserve(visi.size());

    for (auto it = visi.begin(); it != visi.end();)
    {
        if (it->balasVid < 5.0)
        {
            vargsiukai.push_back(*it);
            it = visi.erase(it);
        }
        else
        {
            ++it;
        }
    }

    auto endRusiavimas = chrono::high_resolution_clock::now();
    tRusiavimas = chrono::duration<double>(endRusiavimas - startRusiavimas).count();

    auto startVargsiukai = chrono::high_resolution_clock::now();
    {
        ofstream os("vargsiukai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : vargsiukai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endVargsiukai = chrono::high_resolution_clock::now();
    tWriteVargs = chrono::duration<double>(endVargsiukai - startVargsiukai).count();

    auto startKietiakiai = chrono::high_resolution_clock::now();
    {
        ofstream os("kietiakiai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : visi)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endKietiakiai = chrono::high_resolution_clock::now();
    tWriteKiet = chrono::duration<double>(endKietiakiai - startKietiakiai).count();

    cout << (vargsiukai.size() + visi.size()) << " įrašų: rūšiavimas = " << fixed << setprecision(6) << tRusiavimas
         << " s, vargsiukai->failas = " << tWriteVargs
         << " s, kietiakiai->failas = " << tWriteKiet << " s" << endl;
}

void padalintiStudentus_strategija2(list<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet)
{
    auto startRusiavimas = chrono::high_resolution_clock::now();
    list<Studentas> vargsiukai;

    for (auto it = visi.begin(); it != visi.end();)
    {
        if (it->balasVid < 5.0)
        {
            vargsiukai.push_back(*it);
            it = visi.erase(it);
        }
        else
        {
            ++it;
        }
    }

    auto endRusiavimas = chrono::high_resolution_clock::now();
    tRusiavimas = chrono::duration<double>(endRusiavimas - startRusiavimas).count();

    auto startVargsiukai = chrono::high_resolution_clock::now();
    {
        ofstream os("vargsiukai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : vargsiukai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endVargsiukai = chrono::high_resolution_clock::now();
    tWriteVargs = chrono::duration<double>(endVargsiukai - startVargsiukai).count();

    auto startKietiakiai = chrono::high_resolution_clock::now();
    {
        ofstream os("kietiakiai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : visi)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endKietiakiai = chrono::high_resolution_clock::now();
    tWriteKiet = chrono::duration<double>(endKietiakiai - startKietiakiai).count();

    cout << (vargsiukai.size() + visi.size()) << " įrašų: rūšiavimas = " << fixed << setprecision(6) << tRusiavimas
         << " s, vargsiukai->failas = " << tWriteVargs
         << " s, kietiakiai->failas = " << tWriteKiet << " s" << endl;
}

void padalintiStudentus_strategija3(vector<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet)
{
    auto startRusiavimas = chrono::high_resolution_clock::now();

    auto partition_point = stable_partition(visi.begin(), visi.end(),
                                            [](const Studentas &s)
                                            { return s.balasVid >= 5.0; });

    vector<Studentas> vargsiukai(partition_point, visi.end());
    visi.erase(partition_point, visi.end());

    auto endRusiavimas = chrono::high_resolution_clock::now();
    tRusiavimas = chrono::duration<double>(endRusiavimas - startRusiavimas).count();

    auto startVargsiukai = chrono::high_resolution_clock::now();
    {
        ofstream os("vargsiukai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : vargsiukai)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endVargsiukai = chrono::high_resolution_clock::now();
    tWriteVargs = chrono::duration<double>(endVargsiukai - startVargsiukai).count();

    auto startKietiakiai = chrono::high_resolution_clock::now();
    {
        ofstream os("kietiakiai.txt");
        os << left << setw(15) << "Pavarde" << setw(15) << "Vardas"
           << setw(20) << "Galutinis (Vid.)" << endl
           << string(50, '-') << endl;
        for (const auto &s : visi)
            os << left << setw(15) << s.pavarde << setw(15) << s.vardas
               << setw(20) << fixed << setprecision(2) << s.balasVid << endl;
    }
    auto endKietiakiai = chrono::high_resolution_clock::now();
    tWriteKiet = chrono::duration<double>(endKietiakiai - startKietiakiai).count();

    cout << (vargsiukai.size() + visi.size()) << " įrašų: rūšiavimas = " << fixed << setprecision(6) << tRusiavimas
         << " s, vargsiukai->failas = " << tWriteVargs
         << " s, kietiakiai->failas = " << tWriteKiet << " s" << endl;
}