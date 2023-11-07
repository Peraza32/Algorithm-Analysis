#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#include "mcc.hpp"

int main(){
    int target = 0, size = 0;
    bool flag = true;
    string input = "";
    while(flag){
        cout << "Enter the target value: ";
        cin >> target;
        cout << "Enter the number of coins: ";
        cin >> size;
        int* coins = new int[size];
        cout << "Enter the coins: ";
        for(int i = 0; i < size; i++){
            cin >> coins[i];
        }
        cin.ignore();
        minimum_coin_change mcc = minimum_coin_change(target, coins, size);
        mcc.mcc();
        cout << "Continue? (y/n): ";
        cin >> input;
        if(input == "n" || input == "N")
            flag = false;
    }
    return 0;
}