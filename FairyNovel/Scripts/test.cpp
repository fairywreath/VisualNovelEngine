#include <iostream>
#include <vector>


#include <algorithm>

#include <string>

using namespace std;

int main()
{
    vector<int> vect;
    vect.reserve(20);
    vect.push_back(12);
       auto itr1 =  prev(vect.end());

    vect.push_back(24);
    vect.push_back(17);
    auto itr2 = prev(vect.end());

    vect.push_back(11);
    vect.push_back(921);
    vect[10] = 32;
    cout << *itr1 << endl;
    cout << *itr2 << endl;
    cout << vect[10] << endl;
    cout << vect.size();

    cout << stof("HITAGI") <<endl;
}