#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

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

void bubbleSort(vector<int> &v);
int randomPazymys(mt19937 &gen);
void generuotiFaila(const string &failoVardas, int kiekis);
void generuotiVisusFailus();

void padalintiStudentus_strategija1(const vector<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet);
void padalintiStudentus_strategija1(const list<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet);

void padalintiStudentus_strategija2(vector<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet);
void padalintiStudentus_strategija2(list<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet);

void padalintiStudentus_strategija3(vector<Studentas> &visi,
                                    double &tRusiavimas, double &tWriteVargs, double &tWriteKiet);

#endif