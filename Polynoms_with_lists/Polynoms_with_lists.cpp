#include <iostream>
#include <fstream>
using namespace std;

struct elem
{
    int coef;
    int st;
    elem* next;
};
typedef elem* Polinom;

Polinom create(string file_name)
{
    ifstream in(file_name);

    Polinom top = new elem;
    top->coef = -1;
    top->st = -1;

    Polinom p = top;
    int c;
    int i = 0;
    int deg;
    in >> deg;
    while (in >> c)
    {
        p->next = new elem;
        p = p->next;
        p->coef = c;
        p->st = deg - i;
        i++;
    }
    p->next = NULL;

    in.close();

    return top;
}

void show_polinom(Polinom top)
{
    Polinom p = top;
    if (p == NULL) cout << "Empty" << endl;
    if (p->next != NULL)
    {
        cout << p->next->coef << "x^" << p->next->st;
        p = p->next;
    }

    while (p->next != NULL)
    {
        cout << " + " << p->next->coef << "x^" << p->next->st;
        p = p->next;
    }
    cout << endl;
}

void delete_polinom(Polinom &top)
{
    Polinom p = top->next;
    Polinom q;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        delete q;
    }
}

int calc(Polinom top, int c)
{
    int res = 0;
    Polinom p = top;
    while (p->next != 0)
    {
        res = res * c + p->next->coef;
        p = p->next;
    }
    return res;
}

void diff(Polinom top)
{
    Polinom p = top;
    while (p->next->next != NULL)
    {
        p->next->coef *= p->next->st;
        p->next->st--;
        p = p->next;
    }
    p->next->coef = 0;
}

Polinom summ(Polinom p1, Polinom p2)
{
    Polinom top3 = new elem;
    top3->coef = -1;
    top3->st = -1;
    Polinom p3 = top3;

    while (p1->next != NULL && p2->next != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        if (p1->next->st == p2->next->st)
        {
            p3->coef = p1->next->coef + p2->next->coef;
            p3->st = p1->next->st;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->next->st > p2->next->st)
        {
            p3->coef = p1->next->coef;
            p3->st = p1->next->st;
            p1 = p1->next;
        }
        else
        {
            p3->coef = p2->next->coef;
            p3->st = p2->next->st;
            p2 = p2->next;
        }
    }

    while (p1->next != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        p3->coef = p1->next->coef;
        p3->st = p1->next->st;
        p1 = p1->next;
    }
    while (p2->next != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        p3->coef = p2->next->coef;
        p3->st = p2->next->st;
        p2 = p2->next;
    }
    p3->next = NULL;
    return top3;
}

bool is_equal(Polinom p1, Polinom p2)
{
    bool res = true;

    while (p1->next != NULL && p2->next != NULL && res)
    {
        if (p1->next->coef != p2->next->coef || p1->next->st != p2->next->st)
        {
            res = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    if (p1->next != NULL || p2->next != NULL) res = false;

    return res;
}

void print(Polinom top)
{
    Polinom p = top;
    if (p == NULL) cout << "Empty" << endl;
    if (p->next != NULL)
    {
        if (p->next->coef != 0)
        {
            if (p->next->coef != 1) cout << p->next->coef;
            if (p->next->st > 1)
            {
                if (p->next->coef != 1)
                {
                    cout << "*x^" << p->next->st;
                }
                else
                {
                    cout << "x^" << p->next->st;
                }
            }
            else if (p->next->st == 1)
            {
                if (p->next->coef != 1)
                {
                    cout << "*x";
                }
                else
                {
                    cout << "x";
                }
            }
        }
        p = p->next;
    }

    while (p->next != NULL)
    {
        if (p->next->coef != 0)
        {
            cout << " + ";
            if (p->next->coef != 1) cout << p->next->coef;
            if (p->next->st > 1)
            {
                if (p->next->coef != 1)
                {
                    cout << "*x^" << p->next->st;
                }
                else
                {
                    cout << "x^" << p->next->st;
                }
            }
            else if (p->next->st == 1)
            {
                if (p->next->coef != 1)
                {
                    cout << "*x";
                }
                else
                {
                    cout << "x";
                }
            }
        }
        p = p->next;
    }

    cout << endl;
}

int main()
{
    Polinom p1 = create("polinom.txt");
    //show_polinom(p1);
    Polinom p2 = create("polinom1.txt");
    //show_polinom(p2);

    //cout << calc(p1, 0) << endl;

    //diff(p1);
    //show_polinom(p1);

    //Polinom p3 = summ(p1, p2);
    //show_polinom(p3);

    //cout << is_equal(p1, p2) << endl;

    print(p1);
    print(p2);

    //delete_polinom(p1);
    
}

