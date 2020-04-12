#include "string.h"
#include "bool.h"

int size(string s){
    int i=0;
    while(s[i] != '\0') i++;
    return i;
}
bool cmp(string a, string b){
    int i = 0;
    while((a[i] != '\0') & (b[i] != '\0'))
        if(a[i] != b[i]) return false;
        else i++;
    return true;
}

bool isNumeric(string a){
    for(int i = 0; i < size(a); ++i){
        if(((a[i] <= '0')| (a[i] >= '9')) & (a[i] != '-')) return false;
    }
    return true;
}

int atoi(const string a){
    return 0;
//ToDo: atoi implementation.
}
