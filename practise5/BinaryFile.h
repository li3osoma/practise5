#ifndef _BINARYFILE_H
#define _BINARYFILE_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int recordsNum = 10;

struct film {
	int id;
	char theatre[20];
	char title[20];
	int freeplaces;
    film() {
        id = -1;
        freeplaces = -1;
    }
};

//creating binary from text
int fromTextToBin(string textfile, string binfile) {

    ifstream fin(textfile, ios::in);
    fstream foutb(binfile, ios::binary | ios::out | ios::trunc);

    if (!fin || !foutb) return 1;

    int i = 0;
    char help[10];
    film F;
    while (!fin.eof()) {

        fin.getline(help, sizeof(int), '\n');
        F.id = stoi(help);

        fin.getline(F.theatre, 21, '\n');
        fin.getline(F.title, 21, '\n');

        fin.getline(help, sizeof(int), '\n');
        F.freeplaces = stoi(help);

        foutb.write((char*)&F, sizeof(film));
    }

    fin.close();
    foutb.close();
    return 0;
}

//read record by index
int searchFilmInBinByNumber(string binfile, int filmNum, film* F, int rn = recordsNum)
{
    ifstream finb(binfile, ios::binary);
    if (!finb) return 1;

    int skip = (filmNum - 1) * sizeof(film);
    finb.seekg(skip, ios::beg);
    if (!finb.bad())
    {
        finb.read((char*)F, sizeof(film));
    }
    else return 2;

    finb.close();
    return 0;
}

//delete record by id
int deleteFilmById(string binfile, int deleteId, int rnum = recordsNum)
{
    fstream finb(binfile, ios::binary | ios::in | ios::out);

    if (!finb.is_open()) return 1;

    film lastF, deleteF, previousF;
    int i = 1, i_del = -1;;
    int pos = sizeof(film);

    while (!finb.eof()) {
        searchFilmInBinByNumber(binfile, i, &lastF);

        if (i > 1 && previousF.id == lastF.id) break;

        if (lastF.id == deleteId) {
            deleteF = lastF;
            i_del = i;
        }
        i++;
        previousF = lastF;
    }
    if (i_del == -1) return 2;

    finb.seekg((i_del - 1) * sizeof(film), ios::beg);
    finb.write((char*)&lastF, sizeof(film));

    recordsNum--;

    finb.close();
    return 0;
}

#endif
