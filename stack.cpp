#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <cstdlib>e


struct node
{
    int value;
    node* next;
};

class Stack
{
private:
    node* top;
public:
    Stack() {top = nullptr;}
    void push(int value);
    bool isEmpty();
    int pop();
    int peek();
    ~Stack();
};

void Stack::push(int value)
{
    node *n = new node;
    n->value = value;
    n->next = top;
    top = n;
}

bool Stack::isEmpty()
{
    return top == nullptr;
}

int Stack::pop()
{
    if(isEmpty())
        throw std::runtime_error("The stack is empty!");
    
    int value = top->value;
    node* oldTop = top;
    top = top->next;
    delete oldTop;
    return value;
}

int Stack::peek()
{
    if(isEmpty())
        throw std::runtime_error("The stack is empty!");
    
    return top->value;
}

Stack::~Stack() //destructor called when main returns 0
{
    while (!isEmpty())
        pop();
}
//headers
void print_line();
int get_int(int start, int end);

int main()
{
    Stack stack; 

    std::cout << "Choose what you want to do:" <<std::endl;

    std::cout << "\t1. Push a number into the stack\n\t2. Pop the top number from the stack\n\t3. Peek at the top number of the stack\n\t4. To exit the program\n";
    std::cout << "Enter your option: ";
    int option = get_int(1, 4);
    print_line();

    while(true)
    {
        if(option == 1)
        {
            int n;
            std::cout << "Enter a number to push into the stack: ";
            std::cin >> n;
            stack.push(n);
            print_line();
        }
        else if(option == 2)
        {
            try
            {
                int n = stack.pop();
                std::cout << "Popped number from the stack's top: " << n;
                print_line();
            }
            catch(std::runtime_error& e)
            {
                std::cerr << e.what();
                print_line();
            }
        }
        else if(option == 3)
        {
            try
            {
                int n = stack.peek();
                std::cout << "Current top value is: " << n;
                print_line();
            }
            catch(std::runtime_error& e)
            {
                std::cerr << e.what();
                print_line();
            }
            
        }
        else if(option == 4)
        {
            std::cout << "Exiting program..." << std::endl;
            return 0;
        }
        std::cout << "\t1. Push a number into the stack\n\t2. Pop the top number from the stack\n\t3. Peek at the top number of the stack\n\t4. To exit the program\n";
        std::cout << "Enter your option: ";
        std::cin >> option;
        print_line();
    }
}

void print_line()
{
    std::cout << "\n==========================================\n";
}

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