#include <stdio.h>
#include <string.h>
#include "stl.h"

#include <iostream>
#include <stack>
#include <string>

using namespace std;

stack<int> s1;
stack<int> mins1;

int minpop() {
    int tmp = s1.top(); s1.pop();
    if ( tmp <= mins1.top()) {
        mins1.pop();
    }
    return tmp;
}

void test_min_stack() {
    int tmp, mintop;
    int ar [] = { 3, 2, 1, 4};
    int i, length = sizeof(ar) / sizeof(int);

    for ( i = 0; i < length; i++) {
        tmp = ar[i];
        s1.push(tmp); 
        tmp = s1.top();

        if (!mins1.empty()) { 
            mintop = mins1.top();
            if (tmp < mintop) {
                mins1.push(tmp);
            }
        } else { 
            mins1.push(tmp);
        }
    }
    cout << "top: " << s1.top() << ", min: " << mins1.top();
    minpop();
    cout << "top: " << s1.top() << ", min: " << mins1.top();

    minpop();
    cout << "top: " << s1.top() << ", min: " << mins1.top();
    cout << "\n";
}

int testCapitalWord(string word)
{
    int i, n = word.length();
    int count = 0;
    for ( i = 0; i < n; i++) { 
        if (word.at(i) <= 'Z') { count++;
        }
    }
    cout << "Capital Letters in the word are " << count << "\n";
    if ( count == 0 || count == n || (count == 1 && word.at(0) <='Z')) { 
        cout << "Capital usage: Success\n";
    } else {
        cout << "Capital usage: Failed \n";
    }
}

void practise_stl(int tc, int argc, char* argv[])
{
    int inar[] = {7,6,5,4,3,2,1}; 
    
    switch (tc) {
        case 1: 
            test_min_stack();
            break;
        case 2: 
            testCapitalWord(argv[0]);
            break;
        case 3: 
            break;
        case 4: 
            break;
        case 5: 
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12: 
        case 13: 
            break;
        case 14: 
        case 15: 
        default :
            break;
    };
    printf("\n");
}
