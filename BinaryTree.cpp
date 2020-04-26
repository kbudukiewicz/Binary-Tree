#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;

struct wezel
{
    int value;
    wezel *right;
    wezel *left;
};

void BST_insert(wezel *&r, int x) //funkcja do tworzenia drzewa binarnego
{
    if(r == NULL)
    {
        wezel *nowy = new wezel;
        nowy->value = x;
        nowy->right = NULL;
        nowy->left = NULL;
        r = nowy;
    }
    else if(x >= r->value)
        BST_insert(r->right, x);
    else
        BST_insert(r->left, x);
}

wezel* BST_search(wezel *r, int x) //funkcja do szukania zadanego elementu
{
    if((r==NULL) or (r->value == x))
        return r;
    else
        if(x < r->value)
            return BST_search(r->left, x);
        else
            return BST_search(r->right, x);
}

void BST_remove(wezel *nowy) //funkcja do usuwania drzewa
{
    if(nowy)
    {
        BST_remove(nowy->left);
        BST_remove(nowy->right);
        delete nowy;
    }
}

void print_BST(wezel *wezel, int level) // funkcja do rysowania drzewa w konsoli`
{
    if(wezel)
    {
        print_BST(wezel->right, level+1);
        for(int i = level; i > 0; i--)
            cout << "    ";
        cout << wezel->value << endl;
        print_BST(wezel->left, level+1);
    }
}

wezel *BST_max(wezel *r) // funkcja do szukania maksymalnej wartosci
{
    if((r !=NULL) && (r->right != NULL))
        return BST_max(r->right);
    else
        return r;
}

wezel *delete_wezel(wezel *r, int value) // funkcja do usuwania zadanego wezla
{
    if(r == NULL) return r;
    else if(value < r->value)
        r->left = delete_wezel(r->left, value);
    else if(value > r->value)
        r->right = delete_wezel(r->right, value);
    else
    {
        if(r->right == NULL && r->left == NULL)
        {
            delete r;
            r == NULL;
        }
        else if(r->right == NULL)
        {
            wezel *temp = r;
            r = r->right;
            delete temp;
        }
        else if(r->left == NULL)
        {
            wezel *temp = r;
            r = r->left;
            delete temp;
        }
        else
        {
            wezel *temp = BST_max(r->left);
            r->value = temp->value;
            r->left = delete_wezel(r->left, temp->value);
        }
    }
    return r;
}

int main()
{
    bool runFlag = true;
    wezel *root = NULL;
    srand( time( NULL ) );
    int choice;
    int wstawiany;
    int wart_usun;

    while(runFlag)
    {
        system("cls"); // œrednik na koñcu dodany
        cout << " Menu do obslugi programu do drzewa binarnego. " << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "        Wybor zadania do zrealizowania:        " << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "[1] - Dodanie wartosci do drzewa               " << endl;
        cout << "[2] - Rysowanie drzewa                         " << endl;
        cout << "[3] - Usuwanie podanej wartosci                " << endl;
        cout << "[4] - Wyjœcie z programu                       " << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Twoj wybor to:                                 " << endl;
        /*cin >> choice << endl;*/
        cin >> choice;
        system("cls"); // œrednik na koñcu dodany

        switch(choice)
        {
        case 1 :
                cout << "Podaj wartosc do wstawienia: ";
                cin >> wstawiany;
                BST_insert(root, wstawiany);
                break;
        case 2 :
                print_BST(root, 0);
                system("pause");
                break; break;
        case 3 :
                cout << "Podaj wartosc do usuniecia: ";
                cin >> wart_usun;
                delete_wezel(root, wart_usun);
                break;
        case 4 :
                cout << "Opuszczanie programu." << endl;
                runFlag = false;
                break;
        }
    }
    BST_remove(root);
    return 0;
}
