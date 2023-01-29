#pragma once
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

class UserLogin {
private:

    unordered_map< string, string > table;


public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password

};

UserLogin::UserLogin()
{

}

// COMPLETE THE FOLLOWING FUNCTIONS

void UserLogin::readIn(const string& filename)
{
    fstream myFile;
    myFile.open(filename);
    string username, password;
    while (!(myFile.eof()))
    {
        myFile >> username >> password; //will read the username then the password
        table[username] = password; // make a table in which it has a key, value 
    }
}

size_t UserLogin::numberOfUsers()
{
    return table.size(); //gets the size of the table
}

string UserLogin::passWordCheck(const string& userName)
{
    if (table.find(userName) != table.end()) // if the key is found in the table
    {
        return table[userName]; //then it will return the password pertaining to the userName
    }
    else
    {
        return "Non-existent User"; //else the userName does not exist at all or the password does not match the userName

    }
}

size_t UserLogin::wordBucketIdMethod1(const string& userName)
{
    auto it = 1; //start at first position

    for (auto var = 0; var < table.bucket_count(); var++) //iteration in the number of buckets within the index
    {
        for (auto it = table.begin(var); it != table.end(var); it++) // iteration in the start of the table and the end of the table
        {
            if (it->second != userName) //if the password does not match the username 
            {
                return var; //then it will return the bucket count in which it does not exist
            }
        }
    }
}

size_t UserLogin::wordBucketIdMethod2(const string& userName)
{
    for (auto it = table.begin(); it != table.end(); ++it) // iterating through the table
    {
        if (userName == it->first) //if the userName is == the iterator's userName; meaning it is a match
        {
            return table.bucket(userName); // then it will return the bucket number in which the userName is in
        }
    }

}

bool UserLogin::validateUser(const string& userName)
{
    if (table.find(userName) == table.end()) //if the userName is not found
    {
        return false; //then return false
    }
    else
    {
        return true; //else it has been found and will return true
    }
}

bool UserLogin::authenticateUser(const string& userName, const string& passWord)
{

    if (table.find(userName) == table.end()) // If combination doesn't exist
    {
        return false; //  then it will return false
    }
    else if (table.find(userName)->second != passWord) // If the username exists but does not match password
    {
        return false; //then it will return false
    }
    else 
    {
        return true; // else the combination is correct and will return true
    }
}