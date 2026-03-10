#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <cstdlib>

//headers
void print_line();
int get_int(int start, int end);
int get_int(int start, int end)
{
    std::string input;
    int temp;

     while(true) //check if input is for grade count is int
        {
            bool is_number = true;
            std::cin >> input;
            if(input == ";") return -1;
            for(auto i : input)
            {
                if(!std::isdigit(static_cast<unsigned char>(i)))
                {
                    std::cout << "Enter a number from " << start << " to " << end << "! ";
                    is_number = false;
                    break;
                }
            }
            
            if(is_number)
                temp = stoi(input);
            if(temp < start  && is_number)
            {
                std::cout << "Enter a number bigger than " << start - 1  << " ! " ;
            }
            else if(temp > end && is_number) 
            {
                std::cout << "Enter a number smaller than " << end + 1 << " ! ";
            }
            else if(temp <= end && temp >= start && is_number) break; //if conditions correct

        }
    return temp;
}

void print_line()
{
    std::cout << "\n==========================================\n";
}