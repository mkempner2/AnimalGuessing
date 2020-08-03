// myDebugging-Mini.h
//
// changelog:
//	6/1/20 - pruned down to essentials for class work
// notes:
//  Change ckDbgCnt to always spit out message.
//  Add rest of debugger commands at some point.
//

#ifndef MYDEBUGGING_H
#define MYDEBUGGING_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int dbgCnt=-1; //debug counter
bool debugPrinting = false; //maybe set to true in main code
bool showflowControl = true; //maybe set to false in main code


void showflow (string msg) {
    if (showflowControl)
		cout << "--- at: " << msg << endl;
} // showflow

void showflow (string msg, int num) {
    if (showflowControl)
		cout << "--- at: " << msg << " with " << num << endl;
} // showflow

void showflow (string msg, int num1, int num2) {
    if (showflowControl)
		cout << "--- at: " << msg << " with " << num1
            << " " << num2 << endl;
} // showflow

void showflow (string msg,string msg2) {
    if (showflowControl)
		cout << "--- at: " << msg << ' ' << msg2 << endl;
} // showflow


void setDbgCnt (int cnt) {dbgCnt = cnt;}

void ckDbgCnt (string msg) {
    int n;
    if (debugPrinting && (dbgCnt-- <= 1)) {
        cout << "--->> " << msg << endl;
        cin >> n;
        if (n > 0) dbgCnt = n;
    }
} //ckDbgCnt

void dprint (string msg) {
    ckDbgCnt(msg);
} // dprint

void dprint (string msg, int val) {
    ckDbgCnt(msg+to_string(val));
} // dprint

void dprint (string msg, string val) {
    ckDbgCnt(msg+val);
} // dprint


#endif //MYDEBUGGING_H
