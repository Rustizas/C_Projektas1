#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iterator>
using namespace std;
#include "studentas.h"

template<typename Container>
const void* last_address(const Container& c) {
    auto it = c.end();
    if (it == c.begin()) return nullptr;
    --it;
    return static_cast<const void*>(&(*it));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);

    cout << "Pasirinkite veiksmą:\n"
         << "1 - ivedimas ranka\n"
         << "2 - nuskaitymas is failo (vienkartinis)\n"
         << "3 - sugeneruoti 5 failus (tik kurimas)\n"
         << "4 - benchmarkai su esamais failais (Vector arba List, keli kartojimai)\n";
    int pasirinkimas; cin >> pasirinkimas;

    if (pasirinkimas == 3) {
        generuotiVisusFailus();
        return 0;
    }

    int kont = 1;
    if (pasirinkimas == 1 || pasirinkimas == 4) {
        cout << "Pasirinkite konteinerį: 1 - vector<Studentas>, 2 - list<Studentas>: ";
        cin >> kont;
    }

    if (pasirinkimas == 1) {
        int skaiciusstud;
        cout << "Iveskite studentu skaiciu: ";
        cin >> skaiciusstud;

        if (kont == 1) {
            vector<Studentas> studentaivisi;
            studentaivisi.reserve(skaiciusstud);

            for (int j = 0; j < skaiciusstud; j++) {
                Studentas stud;
                int ndSk;
                int ivestis;
                cout << "Iveskite studento varda ir pavarde: ";
                cin >> stud.vardas >> stud.pavarde;
                cout << "Ar norite ivesti pazymius pats (1), ar generuoti atsitiktinai (2)? ";
                cin >> ivestis;
                if (ivestis == 1) {
                    cout << "Iveskite namu darbu skaiciu (0 jei nezinote): ";
                    cin >> ndSk;
                    cout << "Iveskite namu darbu rezultatus (0 jei baigete): ";
                    for (;;) {
                        int n; cin >> n;
                        if (n == 0) break;
                        stud.namudarbai.push_back(n);
                        if (ndSk != 0 && (int)stud.namudarbai.size() >= ndSk) break;
                    }
                    cout << "Iveskite egzamino rezultata: ";
                    cin >> stud.egzaminas;
                } else {
                    cout << "Kiek namu darbu generuoti? ";
                    cin >> ndSk;
                    for (int i = 0; i < ndSk; i++) stud.namudarbai.push_back(dist(gen));
                    stud.egzaminas = dist(gen);
                    cout << "Sugeneruoti ND: ";
                    for (int x : stud.namudarbai) cout << x << " ";
                    cout << " Egzaminas: " << stud.egzaminas << "\n";
                }

                double sum = 0;
                for (int x : stud.namudarbai) sum += x;
                double vid = stud.namudarbai.empty() ? 0.0 : sum / (double)stud.namudarbai.size();
                stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;

                bubbleSort(stud.namudarbai);
                double mediana = 0.0;
                int n = (int)stud.namudarbai.size();
                if (n > 0) {
                    if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
                    else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
                }
                stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;

                studentaivisi.push_back(stud);

                cout << "Objekto adresas atmintyje: " << last_address(studentaivisi) << "\n";
            }
        } else {
            list<Studentas> studentaivisi;

            for (int j = 0; j < skaiciusstud; j++) {
                Studentas stud;
                int ndSk;
                int ivestis;
                cout << "Iveskite studento varda ir pavarde: ";
                cin >> stud.vardas >> stud.pavarde;
                cout << "Ar norite ivesti pazymius pats (1), ar generuoti atsitiktinai (2)? ";
                cin >> ivestis;
                if (ivestis == 1) {
                    cout << "Iveskite namu darbu skaiciu (0 jei nezinote): ";
                    cin >> ndSk;
                    cout << "Iveskite namu darbu rezultatus (0 jei baigete): ";
                    for (;;) {
                        int n; cin >> n;
                        if (n == 0) break;
                        stud.namudarbai.push_back(n);
                        if (ndSk != 0 && (int)stud.namudarbai.size() >= ndSk) break;
                    }
                    cout << "Iveskite egzamino rezultata: ";
                    cin >> stud.egzaminas;
                } else {
                    cout << "Kiek namu darbu generuoti? ";
                    cin >> ndSk;
                    for (int i = 0; i < ndSk; i++) stud.namudarbai.push_back(dist(gen));
                    stud.egzaminas = dist(gen);
                    cout << "Sugeneruoti ND: ";
                    for (int x : stud.namudarbai) cout << x << " ";
                    cout << " Egzaminas: " << stud.egzaminas << "\n";
                }

                double sum = 0;
                for (int x : stud.namudarbai) sum += x;
                double vid = stud.namudarbai.empty() ? 0.0 : sum / (double)stud.namudarbai.size();
                stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;

                bubbleSort(stud.namudarbai);
                double mediana = 0.0;
                int n = (int)stud.namudarbai.size();
                if (n > 0) {
                    if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
                    else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
                }
                stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;

                studentaivisi.push_back(stud);

                cout << "Objekto adresas atmintyje: " << last_address(studentaivisi) << "\n";
            }
        }
        return 0;
    }

    if (pasirinkimas == 2) {
        string Pav;
        cout << "Iveskite failo pavadinima: ";
        cin >> Pav;

        // Vienkartinis skaitymas į vector (kaip v0.2) ir matavimai
        auto startViso = chrono::high_resolution_clock::now();
        auto startNuskaitymas = chrono::high_resolution_clock::now();

        ifstream in(Pav);
        string eilute; getline(in, eilute);
        int stulpeliai = 0; { string z; stringstream p(eilute); while (p >> z) stulpeliai++; }
        int ndSk = stulpeliai - 3;

        vector<Studentas> studentaivisi;
        Studentas stud;
        while (in >> stud.vardas >> stud.pavarde) {
            stud.namudarbai.clear();
            for (int i = 0; i < ndSk; i++) { int paz; in >> paz; stud.namudarbai.push_back(paz); }
            in >> stud.egzaminas;

            double sum = 0;
            for (int x : stud.namudarbai) sum += x;
            double vid = stud.namudarbai.empty() ? 0.0 : sum / (double)stud.namudarbai.size();
            stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;

            bubbleSort(stud.namudarbai);
            double mediana = 0.0;
            int n = (int)stud.namudarbai.size();
            if (n > 0) {
                if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
                else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
            }
            stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;

            studentaivisi.push_back(stud);
        }
        in.close();

        auto endNuskaitymas = chrono::high_resolution_clock::now();
        chrono::duration<double> tRead = endNuskaitymas - startNuskaitymas;
        cout << "Failo is " << studentaivisi.size()
             << " irasu nuskaitymo laikas: " << fixed << setprecision(6) << tRead.count() << " s\n";

        double tR, tWV, tWK;
        padalintiStudentus(studentaivisi, tR, tWV, tWK);

        auto endViso = chrono::high_resolution_clock::now();
        chrono::duration<double> tTotal = endViso - startViso;
        cout << studentaivisi.size() << " irasu testo laikas: " << fixed << setprecision(6)
             << tTotal.count() << " s\n";
        return 0;
    }

    if (pasirinkimas == 4) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        int repeats = 3;

        ofstream csv("rezultatai.csv", ios::trunc);
        csv << "container,size,run,read_s,split_s,write_vargs_s,write_kiet_s,total_s\n";

        string contName = (kont == 1 ? "vector" : "list");
        cout << "\n=== BENCHMARK: " << contName << " ===\n";

        for (int dydis : dydziai) {
            string failoVardas = "studentai_" + to_string(dydis) + ".txt";

            vector<double> rRead, rSplit, rWV, rWK, rTotal;

            for (int r = 1; r <= repeats; r++) {
                auto startViso = chrono::high_resolution_clock::now();
                auto startNuskaitymas = chrono::high_resolution_clock::now();

                // Nuskaitymas į pasirinktą konteinerį
                string eilute;
                ifstream in(failoVardas);
                if (!in) { cerr << "Nepavyko atidaryti: " << failoVardas << "\n"; break; }
                getline(in, eilute);
                int stulpeliai = 0; { string z; stringstream p(eilute); while (p >> z) stulpeliai++; }
                int ndSk = stulpeliai - 3;

                double tRead = 0.0, tSplit = 0.0, tWV_s = 0.0, tWK_s = 0.0;

                if (kont == 1) {
                    vector<Studentas> visi;
                    visi.reserve(dydis);
                    Studentas stud;
                    while (in >> stud.vardas >> stud.pavarde) {
                        stud.namudarbai.clear();
                        for (int i = 0; i < ndSk; i++) { int paz; in >> paz; stud.namudarbai.push_back(paz); }
                        in >> stud.egzaminas;

                        double sum = 0;
                        for (int x : stud.namudarbai) sum += x;
                        double vid = stud.namudarbai.empty() ? 0.0 : sum / (double)stud.namudarbai.size();
                        stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;

                        bubbleSort(stud.namudarbai);
                        double mediana = 0.0;
                        int n = (int)stud.namudarbai.size();
                        if (n > 0) {
                            if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
                            else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
                        }
                        stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;

                        visi.push_back(stud);
                    }
                    auto endN = chrono::high_resolution_clock::now();
                    tRead = chrono::duration<double>(endN - startNuskaitymas).count();

                    padalintiStudentus(visi, tSplit, tWV_s, tWK_s);
                } else {
                    list<Studentas> visi;
                    Studentas stud;
                    while (in >> stud.vardas >> stud.pavarde) {
                        stud.namudarbai.clear();
                        for (int i = 0; i < ndSk; i++) { int paz; in >> paz; stud.namudarbai.push_back(paz); }
                        in >> stud.egzaminas;

                        double sum = 0;
                        for (int x : stud.namudarbai) sum += x;
                        double vid = stud.namudarbai.empty() ? 0.0 : sum / (double)stud.namudarbai.size();
                        stud.balasVid = 0.4 * vid + 0.6 * stud.egzaminas;

                        bubbleSort(stud.namudarbai);
                        double mediana = 0.0;
                        int n = (int)stud.namudarbai.size();
                        if (n > 0) {
                            if (n % 2 == 1) mediana = stud.namudarbai[n / 2];
                            else mediana = (stud.namudarbai[n / 2 - 1] + stud.namudarbai[n / 2]) / 2.0;
                        }
                        stud.balasMed = 0.4 * mediana + 0.6 * stud.egzaminas;

                        visi.push_back(stud);
                    }
                    auto endN = chrono::high_resolution_clock::now();
                    tRead = chrono::duration<double>(endN - startNuskaitymas).count();

                    padalintiStudentus(visi, tSplit, tWV_s, tWK_s);
                }

                auto endViso = chrono::high_resolution_clock::now();
                double tTotal = chrono::duration<double>(endViso - startViso).count();

                rRead.push_back(tRead);
                rSplit.push_back(tSplit);
                rWV.push_back(tWV_s);
                rWK.push_back(tWK_s);
                rTotal.push_back(tTotal);

                cout << contName << " | " << dydis << " | run " << r
                     << " | read=" << fixed << setprecision(6) << tRead
                     << " s | split=" << tSplit
                     << " s | write(v)=" << tWV_s
                     << " s | write(k)=" << tWK_s
                     << " s | total=" << tTotal << " s\n";

                csv << contName << "," << dydis << "," << r << ","
                    << tRead << "," << tSplit << "," << tWV_s << "," << tWK_s << "," << tTotal << "\n";
            }

            auto avg = [](const vector<double>& v){
                if (v.empty()) return 0.0;
                double s=0; for (double x : v) s += x; return s / v.size();
            };
            double aRead = avg(rRead), aSplit = avg(rSplit), aWV = avg(rWV), aWK = avg(rWK), aTotal = avg(rTotal);
            cout << "AVG -> " << contName << " | " << dydis
                 << " | read=" << aRead << " s | split=" << aSplit
                 << " s | write(v)=" << aWV << " s | write(k)=" << aWK
                 << " s | total=" << aTotal << " s\n\n";

            csv << contName << "," << dydis << ",avg,"
                << aRead << "," << aSplit << "," << aWV << "," << aWK << "," << aTotal << "\n";
        }

        cout << "Visi rezultatai įrašyti į rezultatai.csv\n";
        return 0;
    }

    cout << "Nesuprastas pasirinkimas.\n";
    return 0;
}
