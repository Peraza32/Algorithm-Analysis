#ifndef MCC_HPP
#define MCC_HPP

#include <iostream>
#include <iomanip>

class minimum_coin_change{
    private:
        //Parameters
        int target;
        int* coins;
        int size;
        string** strTable;
        int** table;

        // Functions
        void init_arrays(){
            // Table initialization
            this->strTable = new string*[this->size + 1];
            this->table = new int*[this->size + 1];
            
            for(int i = 0; i <= this->size; i++){
                this->table[i] = new int[this->target + 1];
                this->strTable[i] = new string[this->target + 1];
            }
            
            for(int i = 0; i <= this->size; i++){
                this->table[i][0] = 0;
                this->strTable[i][0] = "";
            }
            
            for(int i = 1; i <= this->target; i++){
                this->table[0][i] = __INT32_MAX__;
                this->strTable[0][i] = "";
            }
        }
    
    public:
        // Minimum coin change algorithm
        void mcc(){
            // Local variables
            int add = 0, i_winner = 0, j_winner = 0;
            string str = "";
            
            // Algorithm
            for(int i = 1; i <= size; i++){
                for(int j = 1; j <= target; j++){
                    if(j < coins[i - 1] || table[i - 1][j] < (table[i][j - coins[i - 1]] + 1)){
                        add = 0;
                        str = "";
                        i_winner = i - 1;
                        j_winner = j;
                    }
                    else{
                        add = 1;
                        str = to_string(coins[i - 1]);
                        i_winner = i;
                        j_winner = j - coins[i - 1];
                    }
                    table[i][j] = table[i_winner][j_winner] + add;
                    strTable[i][j] = strTable[i_winner][j_winner] + str;
                    print_coin_amt();
                    cout << "Press enter to continue...";
                    cin.get();
                    print_coin_str();
                    cout << "Press enter to continue...";
                    cin.get();
                }
            }

            cout << "The minimum number of coins is: " << table[size][target] << endl;
            cout << "The coins are: " << strTable[size][target] << endl;
        }

        // Print functions
        void print_coin_amt(){
            if(!size || !target)
                return;
            
            const char separator = ' ';
            const int width = 13;
            cout << "Amount of coins needed:\n";
            for(int i = 0; i <= target; i++){
                cout << left << setw(width) << setfill(separator) << i << "|" ;
            }
            cout << "\n";
            for(int i = 0; i <= size; i++){
                for(int j = 0; j <= target; j++){
                    cout << left << setw(width) << setfill(separator) << table[i][j] << "|" ;
                }
                cout << "\n";
            }
        }

        void print_coin_str(){
            if(!size || !target)
                return;
            
            const char separator = ' ';
            const int width = 13;
            cout << "Coins:\n";
            for(int i = 0; i <= target; i++){
                cout << left << setw(width) << setfill(separator) << i << "|";
            }
            cout << "\n";
            for(int i = 0; i <= size; i++){
                for(int j = 0; j <= target; j++){
                    cout << left << setw(width) << setfill(separator)  << strTable[i][j] << "|";
                }
                cout << "\n";
            }
        }

        // Constructors
        minimum_coin_change(int target, int* coins, int size){
            this->target = target;
            this->coins = coins;
            this->size = size;
            this->init_arrays();
        }
        

        // Destructor
        ~minimum_coin_change(){
            free(table);
            free(strTable);
            free(coins);
        }
};
#endif