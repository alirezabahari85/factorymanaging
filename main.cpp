//توضیح فایل ها
//buyers.txt
//investors.txt
//purchases.txt

#include <iostream>
#include <fstream>
#include <string>
using namespace std;






//  کلاس خرید ========
class Purchase
{
public:
    string buyerUsername;
    int amount;
    string date; // مثال: 1404/11

    void writeToFile()
    {
        ofstream file("purchases.txt", ios::app);
        file << buyerUsername << " "
             << amount << " "
             << date << endl;
        file.close();
    }
};






// ================== کلاس خریدار 
class Buyer
{
public:
    string username;
    string password;
    int totalPurchase;

    Buyer()
    {
        totalPurchase = 0;
    }

    void show()
    {
        cout << "نام خریدار: " << username
             << " | خرید کل: " << totalPurchase << " تن\n";
    }
};





// کلاس سرمایه‌گذار 
class Investor
{
public:
    string name;
    string password;
    int capital;

    void show()
    {
        cout << "سرمایه‌گذار: " << name
             << " | سرمایه: " << capital << endl;
    }
};




// ======================= کلاس کارخانه =
class Factory
{
private:
    Buyer buyers[100];
    Investor investors[50];

    int buyerCount;
    int investorCount;

    int totalProduced;
    int totalSold;

public:
    Factory()
    {
        buyerCount = 0;
        investorCount = 0;
        totalProduced = 0;
        totalSold = 0;

        loadBuyers();
        loadInvestors();
    }






    // خواندن خریدارا----------
    void loadBuyers()
    {
        ifstream file("buyers.txt");
        if (!file) return;

        while (file >> buyers[buyerCount].username
                    >> buyers[buyerCount].password
                    >> buyers[buyerCount].totalPurchase)
        {
            buyerCount++;
        }

        file.close();
    }






    //  ذخیره خریداران -
    void saveBuyers()
    {
        ofstream file("buyers.txt");

        for (int i = 0; i < buyerCount; i++)
        {
            file << buyers[i].username << " "
                 << buyers[i].password << " "
                 << buyers[i].totalPurchase << endl;
        }

        file.close();
    }







    // - خواندن سرمایه‌گذاران *****
    void loadInvestors()
    {
        ifstream file("investors.txt");
        if (!file) return;

        while (file >> investors[investorCount].name
                    >> investors[investorCount].password
                    >> investors[investorCount].capital)
        {
            investorCount++;
        }

        file.close();
    }

    //  ذخیره سرمایه‌گذاران 
    void saveInvestors()
    {
        ofstream file("investors.txt");

        for (int i = 0; i < investorCount; i++)
        {
            file << investors[i].name << " "
                 << investors[i].password << " "
                 << investors[i].capital << endl;
        }

        file.close();
    }

    ///// افزودن خریدار 
    void addBuyer()
    {
        Buyer b;
        cout << "نام کاربری: ";
        cin >> b.username;
        cout << "رمز عبور: ";
        cin >> b.password;
        b.totalPurchase = 0;

        buyers[buyerCount] = b;
        buyerCount++;

        saveBuyers();
    }

    // -------افزودن سرمایه‌گذار 
    void addInvestor()
    {
        if (investorCount >= 50)
        {
            cout << " ظرفیت سرمایه‌گذاران پر است\n";
            return;
        }

        Investor inv;
        cout << "نام سرمایه‌گذار: ";
        cin >> inv.name;
        cout << "رمز عبور: ";
        cin >> inv.password;
        cout << "مقدار سرمایه: ";
        cin >> inv.capital;

        investors[investorCount] = inv;
        investorCount++;

        saveInvestors();
    }

    // -------دسترسی‌-----
    int getBuyerCount() { return buyerCount; }
    int getInvestorCount() { return investorCount; }

    Buyer* getBuyers() { return buyers; }
    Investor* getInvestors() { return investors; }

    void increaseSold(int amount) { totalSold += amount; }
    int getTotalSold() { return totalSold; }

    // =======================ثبت خرید خریدار ======
void buyerPurchase()
{
    string user, pass;
    cout << "نام کاربری: ";
    cin >> user;
    cout << "رمز عبور: ";
    cin >> pass;

    for (int i = 0; i < buyerCount; i++)
    {
        if (buyers[i].username == user && buyers[i].password == pass)
        {
            Purchase p;
            p.buyerUsername = user;

            cout << "مقدار خرید: ";
            cin >> p.amount;

            cout << "تاریخ (مثال 1404/11): ";
            cin >> p.date;

            buyers[i].totalPurchase += p.amount;
            totalSold += p.amount;

            p.writeToFile();
            saveBuyers();

            cout << " خرید ثبت شد\n";
            return;
        }
    }

    cout << " خریدار یافت نشد\n";
}

// ======================= گزارش ماهانه 
void monthlyReport()
{
    string targetDate;
    cout << "ماه/سال گزارش (مثال 1404/11): ";
    cin >> targetDate;

    ifstream file("purchases.txt");
    if (!file)
    {
        cout << " فایل خرید وجود ندارد\n";
        return;
    }

    string user, date;
    int amount;
    int sum = 0;

    while (file >> user >> amount >> date)
    {
        if (date == targetDate)
        {
            sum += amount;
        }
    }

    file.close();

    cout << " مجموع فروش در " << targetDate
         << " = " << sum << " تن\n";
}

//  منوی سرمایه‌گذار =======================
void investorMenu()
{
    string name, pass;
    cout << "نام سرمایه‌گذار: ";
    cin >> name;
    cout << "رمز عبور: ";
    cin >> pass;

    for (int i = 0; i < investorCount; i++)
    {
        if (investors[i].name == name &&
            investors[i].password == pass)
        {
            int choice;
            cout << "\n1. مشاهده سرمایه\n";
            cout << "2. فروش کل سرمایه\n";
            cout << "انتخاب: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << " سرمایه شما: "
                     << investors[i].capital << endl;
            }
            else if (choice == 2)
            {
                cout << " سرمایه فروخته شد\n";

                // حذف سرمایه‌گذار
                for (int j = i; j < investorCount - 1; j++)
                {
                    investors[j] = investors[j + 1];
                }

                investorCount--;
                saveInvestors();
            }
            return;
        }
    }

    cout << " سرمایه‌گذار یافت نشد\n";
}

//  نمایش سرمایه‌گذاران 
void showAllInvestors()
{
    cout << "\n لیست سرمایه‌گذاران:\n";
    for (int i = 0; i < investorCount; i++)
    {
        investors[i].show();
    }
}

void showAllBuyers() {
    if (buyerCount == 0) {
        cout << "No buyers registered.\n";
        return;
    }

    for (int i = 0; i < buyerCount; i++) {
        buyers[i].show();
        cout << "------------------\n";
    }
}

};


// =====1====== منوی خریدار ===
void buyerMenu(Factory &factory)
{
    int choice;
    do
    {
        cout << "\n--- منوی خریدار ---\n";
        cout << "1. ثبت خرید\n";
        cout << "0. بازگشت\n";
        cout << "انتخاب: ";
        cin >> choice;

        if (choice == 1)
            factory.buyerPurchase();

    } while (choice != 0);
}

// === منوی کارمند ===
void employeeMenu(Factory &factory)
{
    int choice , password = 1597 , inputPassword ;
    do
    {
        cout << "\nرمز ورود : \n";
        cin>> inputPassword ;
        if (inputPassword == password){
            cout << "\n--- منوی کارمند ---\n";
        cout << "\n1.افزودن حریدار\n";
        cout << "2. گزارش فروش ماهانه\n";
        cout << "3. نشان دادن خریداران\n";
        cout << "0. بازگشت\n";
        cout << "انتخاب: ";
        cin >> choice;

        if (choice == 2)
            factory.monthlyReport();
        else if (choice == 1)
            factory.addBuyer(); 
        else if (choice == 3)
            factory.showAllBuyers();
            
        }
        else{
            cout<<"password denied";
        }
         

    } while (choice != 0);
}

// ==== منوی رییس کارخانه 
void bossMenu(Factory &factory)
{
    int choice , bossPassword = 9874 , inputBossPassword ;
    do
    {
        cout << "\nرمز ورود : \n";
        cin>> inputBossPassword ;
        if (inputBossPassword == bossPassword){cout << "\n=== منوی رییس کارخانه ===\n";
        cout << "1. افزودن خریدار\n";
        cout << "2. افزودن سرمایه‌گذار\n";
        cout << "3. مشاهده سرمایه‌گذاران\n";
        cout << "4. گزارش فروش ماهانه\n";
        cout << "0. خروج\n";
        cout << "انتخاب: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            factory.addBuyer();
            break;
        case 2:
            factory.addInvestor();
            break;
        case 3:
            factory.showAllInvestors();
            break;
        case 4:
            factory.monthlyReport();
            break;
        }}
        else{
            cout<<"wrong pass .....";
        }
        

    } while (choice != 0);
}

// =======================main 
int main()
{
    Factory factory;
    int role;

    do
    {
        cout << "\n==============================\n";
        cout << "  سیستم مدیریت کارخانه فولاد\n";
        cout << "==============================\n";
        cout << "1. خریدار\n";
        cout << "2. کارمند\n";
        cout << "3. سرمایه‌گذار\n";
        cout << "4. رییس کارخانه\n";
        cout << "0. خروج\n";
        cout << "انتخاب نقش: ";
        cin >> role;

        switch (role)
        {
        case 1:
            buyerMenu(factory);
            break;
        case 2:
            employeeMenu(factory);
            break;
        case 3:
            factory.investorMenu();
            break;
        case 4:
            bossMenu(factory);
            break;
        }

    } while (role != 0);

    cout << "خروج از برنامه\n";
    return 0;
}









