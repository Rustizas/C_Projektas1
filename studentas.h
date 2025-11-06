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

// grazinam trukme
void padalintiStudentus(const vector<Studentas>& visi,
                        double& tRusiavimas, double& tWriteVargs, double& tWriteKiet);
void padalintiStudentus(const list<Studentas>& visi,
                        double& tRusiavimas, double& tWriteVargs, double& tWriteKiet);

#endif
