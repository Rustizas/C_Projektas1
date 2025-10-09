#ifndef STUDENTAS_H
#define STUDENTAS_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
using namespace std;

struct Studentas // studento strukturos aprasymas
{
    string vardas;
    string pavarde;
    vector<int> namudarbai;
    int egzaminas;
    double balasVid;
    double balasMed;
};

//Funkcijos
void bubbleSort(vector<int> &v);
int randomPazymys(mt19937 &gen);
void generuotiFaila(const string &failoVardas, int kiekis);
void generuotiVisusFailus();
void padalintiStudentus(const vector<Studentas>& visi);

#endif
