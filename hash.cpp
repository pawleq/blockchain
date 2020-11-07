#include "header.h"

string hashing(string text = "") //mixuojame stringo ascii values su ivairiom operacijomis, apkeitinejam bitus
{
    int hasha = 8;
    for (auto i : text)
    {
        int hashb = int(i);
        hasha += hashb * hashb;
        hasha -= (hashb % hasha);
        hasha +=  hasha << 5;
        hasha -= (hasha & hashb) - (hashb + 14) * (hashb / 4);
    }
    hasha = hasha >> 2;
    stringstream streamas;
    streamas << hex << hasha;
    string hashOut = (streamas.str());
    while (hashOut.length() != 64)
    {
        for (int i : hashOut)
        {
            i = (i*i) * (hasha*hasha);
            streamas.str("");
            streamas << hex << i;
            hashOut += streamas.str();
        }
        if (hashOut.length() > 64)
        {
            hashOut = hashOut.substr(0, 64); //substractina iki 64 ilgio hasho
        }
    }
    return hashOut;
}
