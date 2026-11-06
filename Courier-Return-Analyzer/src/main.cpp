#include <iostream>
#include <string>
using namespace std;

class ReturnParcel
{
private:
    int parcelId;
    string senderName;
    string receiverName;
    string destCity;
    string courierPartner;
    double weightKg;
    int attempts;
    int reasonCode;
    string bookingDate;
    string returnDate;
    char status;

    static int returnCount;
    static int reasonTally[6];

    static void readText(const string& prompt, string& target)
    {
        do
        {
            cout << prompt;
            getline(cin, target);
            if (target.empty())
                cout << "  Field cannot be empty. Try again.\n";
        } while (target.empty());
    }

    static bool isValidDate(const string& d)
    {
        if (d.length() != 10 || d[2] != '-' || d[5] != '-')
            return false;
        for (int i = 0; i < 10; i++)
        {
            if (i == 2 || i == 5)
                continue;
            if (d[i] < '0' || d[i] > '9')
                return false;
        }
        int day = stoi(d.substr(0, 2));
        int month = stoi(d.substr(3, 2));
        int year = stoi(d.substr(6, 4));
        return day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 2000 && year <= 2100;
    }

    static string reasonName(int code)
    {
        switch (code)
        {
        case 1: return "Incorrect Address";
        case 2: return "Receiver Unavailable";
        case 3: return "Delivery Refused";
        case 4: return "Damaged in Transit";
        case 5: return "Other";
        default: return "Unknown";
        }
    }

    static void readDate(const string& prompt, string& target)
    {
        cout << prompt;
        getline(cin, target);
        while (!isValidDate(target))
        {
            cout << "  Invalid date. Use DD-MM-YYYY: ";
            getline(cin, target);
        }
    }

public:
    void setDefaults()
    {
        this->parcelId = 0;
        this->senderName = "";
        this->receiverName = "";
        this->destCity = "";
        this->courierPartner = "";
        this->weightKg = 0;
        this->attempts = 0;
        this->reasonCode = 0;
        this->bookingDate = "";
        this->returnDate = "";
        this->status = 'I';
    }

    inline int getParcelId() const
    {
        return this->parcelId;
    }

    static int getReturnCount()
    {
        return returnCount;
    }

    bool isValid() const
    {
        if (parcelId <= 0)
            return false;
        if (senderName.empty() || receiverName.empty() || destCity.empty() || courierPartner.empty())
            return false;
        if (weightKg <= 0 || weightKg > 100)
            return false;
        if (attempts < 1 || attempts > 3)
            return false;
        if (reasonCode < 1 || reasonCode > 5)
            return false;
        if (!isValidDate(bookingDate) || !isValidDate(returnDate))
            return false;
        if (status != 'R')
            return false;
        return true;
    }

    void inputDetails(int id)
    {
        this->parcelId = id;
        cin.ignore(1000, '\n');

        readText("Enter Sender Name: ", this->senderName);
        readText("Enter Receiver Name: ", this->receiverName);
        readText("Enter Destination City: ", this->destCity);
        readText("Enter Courier Partner: ", this->courierPartner);

        cout << "Enter Parcel Weight (kg, 0-100): ";
        while (!(cin >> this->weightKg) || this->weightKg <= 0 || this->weightKg > 100)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "  Enter a valid weight (0-100 kg): ";
        }

        cout << "Enter Delivery Attempts Made (1-3): ";
        while (!(cin >> this->attempts) || this->attempts < 1 || this->attempts > 3)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "  Enter attempts between 1 and 3: ";
        }

        cout << "Return Reasons:\n"
             << "  1. Incorrect Address\n  2. Receiver Unavailable\n  3. Delivery Refused\n"
             << "  4. Damaged in Transit\n  5. Other\n";
        cout << "Enter Reason Code (1-5): ";
        while (!(cin >> this->reasonCode) || this->reasonCode < 1 || this->reasonCode > 5)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "  Enter a valid reason code (1-5): ";
        }
        cin.ignore(1000, '\n');

        readDate("Enter Booking Date (DD-MM-YYYY): ", this->bookingDate);
        readDate("Enter Return Date (DD-MM-YYYY): ", this->returnDate);

        this->status = 'R';

        if (isValid())
        {
            returnCount++;
            reasonTally[this->reasonCode]++;
            cout << "\nReturn Record Added Successfully!\n";
        }
        else
        {
            cout << "\nInvalid Return Record. Registration Cancelled.\n";
        }
    }

    void displayDetails() const
    {
        if (isValid())
        {
            cout << "\n----------------------------------------";
            cout << "\nParcel ID      : " << parcelId;
            cout << "\nSender         : " << senderName;
            cout << "\nReceiver       : " << receiverName;
            cout << "\nDestination    : " << destCity;
            cout << "\nCourier        : " << courierPartner;
            cout << "\nWeight         : " << weightKg << " kg";
            cout << "\nAttempts Made  : " << attempts;
            cout << "\nReturn Reason  : " << reasonName(reasonCode);
            cout << "\nBooking Date   : " << bookingDate;
            cout << "\nReturn Date    : " << returnDate;
            cout << "\nStatus         : " << status;
            cout << "\n----------------------------------------\n";
        }
    }

    static void showReasonAnalysis()
    {
        if (returnCount == 0)
        {
            cout << "\nNo data to analyze yet.\n";
            return;
        }
        int top = 1;
        cout << "\n========== RETURN REASON ANALYSIS ==========\n";
        for (int c = 1; c <= 5; c++)
        {
            double pct = (reasonTally[c] * 100.0) / returnCount;
            cout << c << ". " << reasonName(c) << " : " << reasonTally[c]
                 << " (" << pct << "%)\n";
            if (reasonTally[c] > reasonTally[top])
                top = c;
        }
        cout << "Most Common Reason: " << reasonName(top) << "\n";
    }

    friend void showParcelSummary(const ReturnParcel& p);
};

int ReturnParcel::returnCount = 0;
int ReturnParcel::reasonTally[6] = {0, 0, 0, 0, 0, 0};

void showParcelSummary(const ReturnParcel& p)
{
    cout << "\nParcel Summary";
    cout << "\nID          : " << p.parcelId;
    cout << "\nReceiver    : " << p.receiverName;
    cout << "\nCity        : " << p.destCity;
    cout << "\nReason      : " << ReturnParcel::reasonName(p.reasonCode) << endl;
}

int main()
{
    const int MAX = 50;
    ReturnParcel arr[MAX];
    ReturnParcel* ptr = arr;

    int total = 0;
    int choice = 0;
    int id = 0;
    int flag = 0;
    int found = 0;

    for (int i = 0; i < MAX; i++)
    {
        arr[i].setDefaults();
    }

    do
    {
        cout << "\n====== COURIER RETURN-TO-SENDER ANALYZER ======\n";
        cout << "1. Register Returned Parcel\n";
        cout << "2. Display All Returns\n";
        cout << "3. Search Parcel by ID\n";
        cout << "4. Show Total Returns\n";
        cout << "5. Return Reason Analysis\n";
        cout << "6. Exit\n";
        cout << "Enter Your Choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter a valid menu choice: ";
        }

        switch (choice)
        {
        case 1:
            if (total >= MAX)
            {
                cout << "\nMaximum capacity of 50 records reached.\n";
                break;
            }
            cout << "\nEnter Parcel ID: ";
            while (!(cin >> id) || id <= 0)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cout << "Enter a valid positive Parcel ID: ";
            }

            flag = 0;
            for (int i = 0; i < total; i++)
            {
                if (ptr[i].getParcelId() == id)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1)
            {
                cout << "\nDuplicate Parcel ID! Registration Rejected.\n";
            }
            else
            {
                arr[total].inputDetails(id);
                if (arr[total].isValid())
                    total++;
                else
                    arr[total].setDefaults();
            }
            break;

        case 2:
            if (total == 0)
            {
                cout << "\nNo Return Records Available.\n";
            }
            else
            {
                cout << "\n========== ALL RETURNED PARCELS ==========\n";
                for (int i = 0; i < total; i++)
                {
                    ptr[i].displayDetails();
                }
            }
            break;

        case 3:
            if (total == 0)
            {
                cout << "\nNo Return Records Available to Search.\n";
                break;
            }
            cout << "\nEnter Parcel ID to Search: ";
            while (!(cin >> id) || id <= 0)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cout << "Enter a valid positive Parcel ID: ";
            }
            found = 0;
            for (int i = 0; i < total; i++)
            {
                if (ptr[i].getParcelId() == id)
                {
                    showParcelSummary(ptr[i]);
                    ptr[i].displayDetails();
                    found = 1;
                    break;
                }
            }
            if (found == 0)
                cout << "\nParcel ID Not Found.\n";
            break;

        case 4:
            cout << "\nTotal Returned Parcels: " << ReturnParcel::getReturnCount() << endl;
            break;

        case 5:
            ReturnParcel::showReasonAnalysis();
            break;

        case 6:
            cout << "\nThank you for using Courier Return-to-Sender Analyzer made by Priyanshu Kumar!\n";
            break;

        default:
            cout << "\nInvalid Choice. Please Select 1 to 6.\n";
        }

    } while (choice != 6);

    return 0;
}
