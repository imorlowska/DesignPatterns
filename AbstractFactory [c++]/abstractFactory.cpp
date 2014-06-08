/****************************************************
 * @author: Izabela Orlowska                        *
 *                                                  *
 * Example of an abstract factory design pattern    *
 ****************************************************/
#include <iostream>
#include <fstream>

using namespace std;

//NOTE: Dla demonstracji, prog skladkowy/podatkowy okreslony jest na taka kwote
#define thresholdSP 10000
#define thresholdTax 15000

bool caseInsensitiveStringCompare(const string& str1, const string& str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin();
            c1 != str1.end(); ++c1, ++c2)
        {
            if (tolower(*c1) != tolower(*c2))
            {
                return false;
            }
        }
    return true;
};

/**
 * Klasa odpowiedzialna za obliczanie skladki dodatkowej na podstawie dochodow.
 * NOTE: Zakladam, ze skladki to wartosc procentowa od podanej kwoty.
 **/
class SupplementaryPayment
{
    protected:
        double low, high;
    public:
        double calculate(double amount)
        {
            if (amount > thresholdSP)
            {
                return ((amount * high) / 100);
            }
            return ((amount * low) / 100);
        }
};

/**
 * Poniewaz wszystko jest zawarte w klasie, z ktorej dziedziczymy, to
 * konkretne SupplemenratyPayments roznia sie tylko wartosciamy low i high.
 **/
class SupplementaryPaymentPL:public SupplementaryPayment
{
    public:
        SupplementaryPaymentPL()
        {
            low = 28;
            high = 42;
        }
};

class SupplementaryPaymentDE:public SupplementaryPayment
{
    public:
        SupplementaryPaymentDE()
        {
            low = 25;
            high = 45;
        }
};

class SupplementaryPaymentUS:public SupplementaryPayment
{
    public:
        SupplementaryPaymentUS()
        {
            low = 20;
            high = 40;
        }
};

/**
 * Z braku wiekszej wiedzy dotyczacej opodatkowania, skladek itp. podatki
 * i skladki dzialaja tu niemal tak samo (roznia sie tylko wartosciami). Mysle,
 * ze do prezentacji wzorca nie zrobi to duzej krzywdy.
 **/
class Tax
{
    protected:
        double low, high;
    public:
        double calculate(double amount)
        {
            if (amount > thresholdTax)
            {
                return ((amount * high) / 100);
            }
            return ((amount * low) / 100);
        }
};

class TaxPL:public Tax
{
    public:
        TaxPL()
        {
            low = 18;
            high = 32;
        }
};

class TaxDE:public Tax
{
    public:
        TaxDE()
        {
            low = 15;
            high = 25;
        }
};

class TaxUS:public Tax
{
    public:
        TaxUS()
        {
            low = 10;
            high = 20;
        }
};

class Factory
{
    public:
        static Factory* get();
        virtual SupplementaryPayment* createSP() = 0;
        virtual Tax* createTax() = 0;

};

class FactoryPL:public Factory
{
    public:
        SupplementaryPayment* createSP()
        {
            return new SupplementaryPaymentPL();
        }
        Tax* createTax()
        {
            return new TaxPL();
        }
};

class FactoryUS:public Factory
{
    public:
        SupplementaryPayment* createSP()
        {
            return new SupplementaryPaymentUS();
        }
        Tax* createTax()
        {
            return new TaxUS();
        }
};

class FactoryDE:public Factory
{
    public:
        SupplementaryPayment* createSP()
        {
            return new SupplementaryPaymentDE();
        }
        Tax* createTax()
        {
            return new TaxDE();
        }
};

Factory* Factory::get()
{
    ifstream data;
    data.open ("data.txt");
    if (data.is_open())
    {
        string country;
        getline(data,country);
        data.close();

        cout << country << endl;

        if (caseInsensitiveStringCompare(country, "PL"))
        {
            return new FactoryPL();
        }
        else if (caseInsensitiveStringCompare(country, "DE"))
        {
            return new FactoryDE();
        }
        else if (caseInsensitiveStringCompare(country, "US") ||
                 caseInsensitiveStringCompare(country, "USA"))
         {
             return new FactoryUS();
         }
         else
         {
             cout << "Incorrect data file" << endl;
             return NULL;
         }
    }
    else
    {
        cout << "Data file not found!" << endl;
        return NULL;
    }

};

int main()
{
    double baseAmount = 100000;

    Factory* fact = Factory::get();

    SupplementaryPayment* sp = fact->createSP();
    double amountToTax = sp->calculate(baseAmount);

    Tax* tax = fact->createTax();
    cout << tax->calculate(amountToTax) << endl;

    return 0;
}
