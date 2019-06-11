#include <iostream> 
using namespace std; 
  
// function to convert 
// Hexadecimal to Binary Number 
string HexToBin(string hexdec) 
{ 
    long int i = 2; 
    string re;
  
    while (hexdec[i]) { 
  
        switch (hexdec[i]) { 
        case '0': 
            re.append("0000"); 
            break; 
        case '1': 
            re.append("0001"); 
            break; 
        case '2': 
            re.append("0010"); 
            break; 
        case '3': 
            re.append("0011"); 
            break; 
        case '4': 
            re.append("0100"); 
            break; 
        case '5': 
            re.append("0101"); 
            break; 
        case '6': 
            re.append("0110"); 
            break; 
        case '7': 
            re.append("0111"); 
            break; 
        case '8': 
            re.append("1000"); 
            break; 
        case '9': 
            re.append("1001"); 
            break; 
        case 'A': 
        case 'a': 
            re.append("1010"); 
            break; 
        case 'B': 
        case 'b': 
            re.append("1011"); 
            break; 
        case 'C': 
        case 'c': 
            re.append("1100"); 
            break; 
        case 'D': 
        case 'd': 
            re.append("1101"); 
            break; 
        case 'E': 
        case 'e': 
            re.append("1110"); 
            break; 
        case 'F': 
        case 'f': 
            re.append("1111"); 
            break; 
        default: 
            return re;
        } 
        i++; 
    } 
    return re;
} 