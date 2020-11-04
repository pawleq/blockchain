#include "header.h"
#include "user.cpp"

string alphaNumericStrings(int length)
{
    static const char alphanum[] = "0123456789" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string randomString("", length);
    for (int i = 0; i < length; i++)
    {
        randomString[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return randomString;
}
void generate_user()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<unsigned> rndkey(0, 15);
    uniform_int_distribution<unsigned> rndwallet(1000, 1000000);

    static const char symbols[] = "0123456789" "abcdef";

    for (int i = 0; i < USERAMOUNT; i++)
    {
        users temp;
        temp.UserName = alphaNumericStrings(NAMELENGTH);
        for(int j = 0; j < KEYLENGTH; j++)
        {
            temp.key = temp.key + symbols[rndkey(gen)];
        }
        temp.balance = rndwallet(gen);
        user.push_back(temp);
        cout <<user[i].UserName<<" "<<user[i].key<<" "<<user[i].balance<<endl;
    }
}
