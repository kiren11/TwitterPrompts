
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


int main() {

    //multimap, date is key, engagement type and number are a pair of values
    std::multimap <string, pair<string, int> > mmap;

    //date range
    std::string rangeDate1, rangeDate2;

    //engagement data
    std::string date;
    std::string engagement;
    std::string num;

    //possibly to split date?
    //will see if i will use
    int year;
    int month;
    int day;
    char comma = 'y';

    //to read until eof
    std::string line;

    //store range dates as strings, ignore commas
    std::cin>>rangeDate1;
    std::cin.ignore(1, ',');
    std::cin>>rangeDate2;
    std::cin.ignore(1,',');

    // //get 3 pieces of data
    // while(std::getline(std::cin, line)) {
    //     std::cin>>date;
    //     std::cin.ignore(comma);
    //     std::cin>>engagement;
    //     std::cin.ignore(comma);
    //     std::cin>>num;
    // }

    //check syntax for this using c++ reference guide
    // mmap.insert(date, make_pair(engagement, num));

    return 0;
}
