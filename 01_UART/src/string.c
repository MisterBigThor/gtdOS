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