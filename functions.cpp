#include "header.h"
#include "user.cpp"
#include "hash.cpp"
#include "block.cpp"

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
vector<users> generate_user()
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
        //cout <<user[i].UserName<<" "<<user[i].key<<" "<<user[i].balance<<endl;m
    }
    return user;
}
vector<transactions> generate_transactions(vector<users> user)
{
    transactions transaction;
    for(int i = 0; i < TRANSAMOUNT; i++)
    {
        transaction.sId = user.at(rand()%(USERAMOUNT)).key;
        do
        {
            transaction.rId = user.at(rand()%(USERAMOUNT)).key;
        }
        while (transaction.sId == transaction.rId);
        transaction.amount = rand()%(USERAMOUNT);
        transaction.id = hashing(transaction.sId + transaction.rId + to_string(transaction.amount));
        trans.push_back(transaction);
        //cout <<trans[i].sId<<" "<<trans[i].rId<<" "<<trans[i].amount<<" "<<trans[i].id<<endl;
    }
    return trans;
}
vector<transactions> generate_100trans(vector<transactions>& trans) //to place 100 different trans to a block
{
    vector<transactions> returnTransactions;
    for(int i = 0; i < 100; i++)
    {
        returnTransactions.push_back(trans.at(0));
        trans.erase(trans.begin());
    }
    return returnTransactions;
}
string merkle(vector<transactions> trans) //merkle function for both versions
{
    int size = trans.size();
    vector<string> hashes;
    for(int i = 0; i < size; i++)
    {
        if(i + 1 < size)
        {
            hashes.push_back(hashing(trans.at(i).id + trans.at(i+1).id));
            i++;
        }
        else
        {
            hashes.push_back(hashing(trans.at(i).id));
        }
        //cout <<hashes[i];m
    }

    while(hashes.size() != 1)
    {
        vector<string> newHashes;
        size = hashes.size();

        for(int i = 0; i < size; i++)
        {
            if(i + 1 < size)
            {
                newHashes.push_back(hashing(hashes.at(i) + hashes.at(i+1)));
                i++;
            }
            else
            {
                newHashes.push_back(hashing(hashes.at(i)));
            }
        }
        hashes = newHashes;
    }
    return hashes.at(0);
}
string generate_hash(const string& prevBlockHash, vector<transactions> trans)
{
    string newBlockHash;
    time_t timestamp = std::time(nullptr);
    string version = "version1";
    string merkleHash = merkle(move(trans));
    string difficultyTarget = "0"; //how much zeros
    long long int nonce = 0;
    do
    {
        newBlockHash = hashing(prevBlockHash + to_string(timestamp) + version + merkleHash + to_string(nonce) + difficultyTarget); //block hash generate
        nonce++;
    }
    while (newBlockHash.substr(0, difficultyTarget.size()) != difficultyTarget);
    return newBlockHash;
}

void mining(vector<transactions> trans, vector<users> user)
{
    user = generate_user();
    trans = generate_transactions(user);
    while(!trans.empty())
    {
        vector<transactions> transactions100 = generate_100trans(trans);
        Block block;
        string hash;
        if(blocks.empty())
        {
            hash = generate_hash("0", transactions100);
        }
        else
        {
            hash = generate_hash(blocks.back().hash, transactions100);
        }

        for(int i = 0; i < transactions100.size(); i++)
        {
            transactions trans = transactions100.at(i);
            int sId = find_if(user.begin(), user.end(), [trans, i](const users& user)
            {
                return user.key == trans.sId;
            }) - user.begin();
            int rId = find_if(user.begin(), user.end(), [trans, i](const users& user)
            {
                return user.key == trans.rId;
            }) - user.begin();
            if(user.at(sId).balance >= trans.amount)
            {
                user.at(sId).balance -= trans.amount;
                user.at(rId).balance += trans.amount;
            }
            else
            {
                transactions100.at(i).bad = true;
            }
        }
        cout << "Mined block hash : " << hash << endl;
        block.hash = hash;
        block.trans = transactions100;
        blocks.push_back(block);
    }
}
