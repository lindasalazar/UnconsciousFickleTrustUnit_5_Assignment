#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class MenuItem 
{
private:
    string name;
    double itemCost;
    string desc;
    char addLetter;
    char removeLetter;
    int count;

public:
    MenuItem() : name("No Name"), itemCost(0.0), desc("No Description"), addLetter(' '), removeLetter(' '), count(0) {}

    MenuItem(string n, double c, string d, char a, char r) 
        : name(n), itemCost(c), desc(d), addLetter(a), removeLetter(r), count(0) {}

    void setAddLetter(char add) {
        addLetter = add;
    }

    void setRemoveLetter(char remove) {
        removeLetter = remove;
    }

    void setCount(int c) {
        count = c;
    }

    void setName(string n) {
        name = n;
    }

    void setItemCost(double cost) {
        itemCost = cost;
    }

    void setDesc(string d) {
        desc = d;
    }

    char getAddLetter() const {
        return addLetter;
    }

    char getRemoveLetter() const {
        return removeLetter;
    }

    string getName() const {
        return name;
    }

    double getItemCost() const {
        return itemCost;
    }

    string getDesc() const {
        return desc;
    }

    int getCount() const {
        return count;
    }

    void display() const {
        cout << addLetter << ")" << setw(10) << name
             << setw(5) << "$" << itemCost << setw(5) << "(" << removeLetter
             << ")" << setw(7) << count << setw(13) << desc << endl;
    }
};

void populateMenu(vector<MenuItem>& entireMenu) 
{
    vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Hot Dog", "Burger", "Sandwich", "Ice Cream", "Pizza"};
    vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'
};

    for (int i = 0; i < defaultMenuNames.size(); i++) 
    {
        entireMenu.push_back(MenuItem(defaultMenuNames[i], 3.00 + i, "delicious", defaultAddLetters[i], defaultRemoveLetters[i]));
    }
}

void showMenu(const vector<MenuItem>& m) 
{
    cout << fixed << setprecision(2);
    cout << "DrT's Efficient Menu" << endl;
    cout << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC" << endl;
    for (const MenuItem& item : m) {
        item.display();
    }
}

void printReceipt(const vector<MenuItem>& m, double subtotal, double tax, double tipAmount, double totalDue) 
{
    cout << "\n------------ Receipt ------------" << endl;
    cout << "ITEM\t\tPRICE" << endl;
    for (const MenuItem& item : m) {
        if (item.getCount() > 0) {
            cout << item.getName() << "\t\t$" << item.getItemCost() * item.getCount() << endl;
        }
    }
    cout << "------------------------------" << endl;
    cout << "Subtotal:\t$" << subtotal << endl;
    cout << "Tax (10%):\t$" << tax << endl;
    cout << "Tip:\t\t$" << tipAmount << endl;
    cout << "------------------------------" << endl;
    cout << "Total Due:\t$" << totalDue << endl;
    cout << "------------------------------" << endl;
}

void acceptOrder(vector<MenuItem>& m) 
{
    double subtotal = 0.0;

    do 
    {
        cout << "\nPlease choose an item (x to Exit): ";
        char option;
        cin >> option;


        if (option == 'x' || option == 'X') 
        {
            break; 
        }

        bool validOption = false;
        for (MenuItem& item : m) 
        {
            if (option == item.getAddLetter()) 
            {
                cout << "\nMenu Item " << item.getAddLetter() << " selected.";
                item.setCount(item.getCount() + 1);
                subtotal += item.getItemCost();
                validOption = true;
                break;
            } 
            else if (option == item.getRemoveLetter()) 
            {
                cout << "\nRemove Item " << item.getRemoveLetter() << " selected.";
                if (item.getCount() > 0) {
                    item.setCount(item.getCount() - 1);
                    subtotal -= item.getItemCost();
                    validOption = true;
                    break;
                } 
                else 
                {
                    cout << "\nItem count must be > 0 to remove: " << item.getName() << endl;
                    validOption = true;
                    break;
                }
            }
        }

        // Check ivalid input
        if (!validOption) {
            cout << "\nInvalid input (" << option << "). Please try again." << endl;
        }

        // Display updated menu and subtotal
        showMenu(m);
        cout << "\nSubtotal: $" << subtotal << endl;

    } while (true);

    // Receipt generation process
    double tipAmount;
    cout << "\nEnter tip amount (suggest 20% or more): $";
    cin >> tipAmount;

    double tax = subtotal * 0.1; // Assuming 10% tax
    double totalDue = subtotal + tax + tipAmount;

    char paymentType;
    cout << "\nSelect payment type (C for Credit Card, A for Cash): ";
    cin >> paymentType;

    if (paymentType == 'A' || paymentType == 'a') 
    { 
        double tenderAmount;
        cout << "\nEnter tender amount: $";
        cin >> tenderAmount;

        if (tenderAmount >= totalDue) 
        {
            double change = tenderAmount - totalDue;
            cout << "\nChange: $" << change << endl;
        } 
        else 
        {
            cout << "\nInsufficient payment. Transaction cancelled." << endl;
            return;
        }
    } 
    else if (paymentType == 'C' || paymentType == 'c') 
    { 
        cout << "\nProcessing credit card payment..." << endl;
        // Additional payment processing logic can be added here
    }

    printReceipt(m, subtotal, tax, tipAmount, totalDue);
}


int main() 
{
    vector<MenuItem> wholeMenu;
    populateMenu(wholeMenu);
    showMenu(wholeMenu);

    char choice;
    do 
    {
        acceptOrder(wholeMenu);
        cout << "\nWould you like to place another order? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    cout << "\nThank you for visiting!" << endl;
    return 0;
}
