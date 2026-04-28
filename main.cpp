#include <iostream>
#include <string>
using namespace std;

/* Inline Function */
inline double childCost(double price)
{
    return price * 0.5;
}

/* Base Class */
class Tour
{
protected:
    int tourID;
    string destination;
    int duration;
    double price;
    int availability;

public:

    Tour()    // Constructor
    {
        tourID = 0;
        destination = "";
        duration = 0;
        price = 0;
        availability = 0;
    }

    void inputTour()
    {
        cout<<"Enter Tour ID: ";
        cin>>tourID;

        cout<<"Enter Destination: ";
        cin>>destination;

        cout<<"Enter Duration: ";
        cin>>duration;

        cout<<"Enter Price: ";
        cin>>price;

        cout<<"Enter Availability: ";
        cin>>availability;
    }

    void displayTour()
    {
        cout<<"\nTour ID: "<<tourID;
        cout<<"\nDestination: "<<destination;
        cout<<"\nDuration: "<<duration;
        cout<<"\nPrice: "<<price;
        cout<<"\nAvailability: "<<availability<<endl;
    }

    double getPrice()
    {
        return price;
    }

    bool checkAvailability(int seats)
    {
        return seats <= availability;
    }

    void updateAvailability(int seats)
    {
        availability -= seats;
    }

    ~Tour()    // Destructor
    {
        cout<<"\nTour object destroyed\n";
    }
};

/* Derived Class */
class BundledTour : public Tour
{
    double discount;

public:

    void inputBundled()
    {
        inputTour();
        cout<<"Enter Discount (%): ";
        cin>>discount;
    }

    double getDiscountPrice()
    {
        return price - (price*discount/100);
    }
};

/* Customer Class */
class Customer
{
private:
    int id;
    string name;
    int age;
    string email;

    static int totalCustomers;

public:

    Customer()   // Constructor
    {
        totalCustomers++;
    }

    void inputCustomer()
    {
        cout<<"Enter Customer ID: ";
        cin>>id;

        cout<<"Enter Name: ";
        cin>>name;

        cout<<"Enter Age: ";
        cin>>age;

        cout<<"Enter Email: ";
        cin>>email;
    }

    void displayCustomer()
    {
        cout<<"\nCustomer ID: "<<id;
        cout<<"\nName: "<<name;
        cout<<"\nAge: "<<age;
        cout<<"\nEmail: "<<email<<endl;
    }

    static void showTotal()
    {
        cout<<"\nTotal Customers: "<<totalCustomers<<endl;
    }

    friend void showCustomerName(Customer c);
};

int Customer::totalCustomers = 0;

/* Friend Function */
void showCustomerName(Customer c)
{
    cout<<"Customer Name: "<<c.name<<endl;
}

/* Booking Class */
class Booking
{
    int bookingID;
    int adults;
    int children;
    double totalCost;

public:

    void createBooking(Customer c, Tour *t)
    {
        cout<<"Enter Booking ID: ";
        cin>>bookingID;

        cout<<"Enter Adults: ";
        cin>>adults;

        cout<<"Enter Children: ";
        cin>>children;

        int total = adults + children;

        if(!t->checkAvailability(total))
        {
            cout<<"Tour Fully Booked!\n";
            return;
        }

        totalCost = adults * t->getPrice() +
                    children * childCost(t->getPrice());

        t->updateAvailability(total);

        cout<<"Booking Successful!\n";
    }

    void displayBooking()
    {
        cout<<"Booking ID: "<<bookingID<<endl;
        cout<<"Total Cost: "<<totalCost<<endl;
    }
};

/* Admin Login */
bool adminLogin()
{
    string user, pass;

    cout<<"\n===== ADMIN LOGIN =====\n";

    cout<<"Username: ";
    cin>>user;

    cout<<"Password: ";
    cin>>pass;

    if(user=="admin" && pass=="1234")
    {
        cout<<"Admin Login Successful\n";
        return true;
    }

    cout<<"Invalid Admin Login\n";
    return false;
}

/* Customer Login */
bool customerLogin()
{
    string user, pass;

    cout<<"\n===== CUSTOMER LOGIN =====\n";

    cout<<"Username: ";
    cin>>user;

    cout<<"Password: ";
    cin>>pass;

    if(user=="customer" && pass=="1111")
    {
        cout<<"Customer Login Successful\n";
        return true;
    }

    cout<<"Invalid Customer Login\n";
    return false;
}

/* Main System */
int main()
{
    int loginChoice;

    cout<<"===== SMART TOUR BOOKING SYSTEM =====\n";
    cout<<"1. Admin Login\n";
    cout<<"2. Customer Login\n";
    cout<<"Enter choice: ";
    cin>>loginChoice;

    if(loginChoice==1)
    {
        if(!adminLogin())
        return 0;
    }
    else if(loginChoice==2)
    {
        if(!customerLogin())
        return 0;
    }
    else
    {
        cout<<"Invalid Choice\n";
        return 0;
    }

    Tour *tour = new Tour();     // Dynamic Memory
    Customer customers[5];       // Array of Objects
    Booking booking;

    int choice;
    int index=0;

    while(true)
    {
        cout<<"\n----- SMART TOUR BOOKING MENU -----\n";
        cout<<"1 Add Tour\n";
        cout<<"2 Add Customer\n";
        cout<<"3 Create Booking\n";
        cout<<"4 Display Tour\n";
        cout<<"5 Display Customers\n";
        cout<<"6 Show Total Customers\n";
        cout<<"7 Exit\n";

        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                tour->inputTour();
                break;

            case 2:
                customers[index].inputCustomer();
                index++;
                break;

            case 3:
                booking.createBooking(customers[0],tour);
                break;

            case 4:
                tour->displayTour();
                break;

            case 5:
                for(int i=0;i<index;i++)
                customers[i].displayCustomer();
                break;

            case 6:
                Customer::showTotal();
                break;

            case 7:
                delete tour;
                return 0;

            default:
                cout<<"Invalid Choice\n";
        }
    }
}
