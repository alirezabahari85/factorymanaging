//توضیح فایل ها
//buyers.txt
//investors.txt
//purchases.txt






#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ======================= کلاس خرید =======================
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

// ======================= کلاس خریدار =======================
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

// ======================= کلاس سرمایه‌گذار =======================
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

// ======================= کلاس کارخانه =======================
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

    // ---------- خواندن خریداران ----------
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

    // ---------- ذخیره خریداران ----------
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

    // ---------- خواندن سرمایه‌گذاران ----------
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

    // ---------- ذخیره سرمایه‌گذاران ----------
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

    // ---------- افزودن خریدار ----------
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

    // ---------- افزودن سرمایه‌گذار ----------
    void addInvestor()
    {
        if (investorCount >= 50)
        {
            cout << "❌ ظرفیت سرمایه‌گذاران پر است\n";
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

    // ---------- دسترسی‌ها برای مراحل بعد ----------
    int getBuyerCount() { return buyerCount; }
    int getInvestorCount() { return investorCount; }

    Buyer* getBuyers() { return buyers; }
    Investor* getInvestors() { return investors; }

    void increaseSold(int amount) { totalSold += amount; }
    int getTotalSold() { return totalSold; }
};
