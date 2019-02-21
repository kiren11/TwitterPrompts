

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

struct node {
  std::string date;
  std::string engagement;
  int num;
  node *next;
};	

class linkedlist {
private:
  node *head, *tail;
  public:
  linkedlist() {
    head=NULL;
    tail=NULL;
}

void createnode(string x, string y, int z) {
  node *temp = new node;

  temp->date = x;
  temp->engagement = y;
  temp->num = z;

  temp->next = NULL;

  if(head == NULL) {
    head = temp;
    tail = temp;
    temp = NULL;
  } else {	
    tail->next=temp;
    tail = temp;
  }
}

void display() {
  node *temp=new node;
  temp=head;
  while(temp!=NULL) {
    cout<<temp->date<<"\t";
    cout<<temp->engagement<<"\t";
    cout<<temp->num<<"\t";
    temp=temp->next;
  }
} 

};
int main() {
    //std::string rangeDate1, rangeDate2;

    std::string date;
    std::string engagement;
    int num;

    std::string line;

    
    //used to ignored in range values, data
    char comma = ',';

        //get 3 pieces of data
        while(std::getline(std::cin, line)) {
            std::cin>>date;
            std::cin.ignore(comma);
            std::cin>>engagement;
            std::cin.ignore(comma);
            std::cin>>num;
        }

    //store range dates as strings, ignore commas
    // std::cin>>rangeDate1;
    // std::cin.ignore(1, ',');
    // std::cin>>rangeDate2;

    return 0;
}
