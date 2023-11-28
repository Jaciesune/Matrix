#pragma once
#include <ostream>
#include <iostream>

using namespace std;

//klasa matrix jest kwadratowa, posiada rozmiar n x n
//macierz jest pzrechowywana w zmiennej dynamicznej na stercie
//klasa wczytuje macierz z pliku


class Matrix {
private:
    int n;
    int** matrix;
public:
    //konstruktor domyslny
    Matrix(void);
    //konstruktor z parametrem
    Matrix(int n);
    //konstruktor kopiujacy
    Matrix(const Matrix& m);
    //konstruktor alokuje pamięc i przepisuje dane z tabeli
    Matrix(int n, int* tab);
    //destruktor
    ~Matrix();

    //METODY//
    //metoda alokująca pamięc na macierz
    Matrix& alokuj(int n);
    //metoda wstawiająca wartość
    Matrix& wstaw(int x, int y, int value);//wiersz, kolumna, wartosc
    //zwraca wartość elementu x, y
    int pokaz(int x, int y);
    //zamienia wiersze z kolumnami
    Matrix& odwroc(void);
    //wypełnia cyframi od 0 do 9 wszystkie elementy tablicy
    Matrix& losuj(void);
    //wypełniamy cyframi od 0 do 9 elementy macierzy. Zmienna x określa ile cyfr będziemy losować Następnie algorytm losuje, w które miejsca wstawi wylosowane cyfry
    Matrix& losuj(int x);
    //po przekątnej są wpisane dane z tabeli, a pozostałe elementy są równe 0,
    Matrix& diagonalna(int* tab);
    //po przekątnej są wpisane dane z tabeli, a pozostałe elementy są równe 0. Parametr k może oznaczać: 0 - przekątna przechodząca przez środek (czyli tak jak metoda diagonalna), cyfra dodatnia przesuwa diagonalną do góry macierzy o podaną cyfrę, cyfra ujemna przesuwa diagonalną w dół o podaną cyfrę
    Matrix& diagonalna_k(int* tab, int k);
    //przepisuje dane z tabeli do kolumny, którą wskazuje zmienna x
    Matrix& kolumna(int x, int* t);
    //przepisuje dane z tabeli do wiersza, który wskazuje zmienna y
    Matrix& wiersz(int y, int* t);
    //uzupełnia macierz: 1-na przekątnej, 0-poza przekątną
    Matrix& przekatna(void);
    //uzupełnia macierz: 1-pod przekątną, 0-nad przekątną i po przekątnej
    Matrix& pod_przekatna(void);
    //uzupełnia macierz: 1-nad przekątną, 0-pod przekątną i po przekątnej
    Matrix& nad_przekatna(void);
    //uzupełnia macierz w ten sposób dla n=4:
    //0101
    //1010
    //0101
    //1010
    Matrix& szachownica(void);
    //A+B
    Matrix& operator+(Matrix& m);
    //A*B
    Matrix& operator*(Matrix& m);
    //A+int
    Matrix& operator+(int a);
    //A*int
    Matrix& operator*(int a);
    //A-int
    Matrix& operator-(int a);
    //int+A
    friend Matrix operator+(int a, Matrix& m);
    //int*A
    friend Matrix operator*(int a, Matrix& m);
    //int-A
    friend Matrix operator-(int a, Matrix& m);
    //A++
    Matrix& operator++(int);
    //A-- 
    Matrix& operator--(int);
    //++A
    Matrix& operator++();
    //--A
    Matrix& operator--();
    //każdy element w macierzy powiększamy o „a”
    Matrix& operator+=(int a);
    //każdy element w macierzy pomniejszamy o „a”
    Matrix& operator-=(int a);
    //każdy element w macierzy mnożymy przez „a”
    Matrix& operator*=(int a);
    //wszystkie cyfry są powiększone o część całkowitą z wpisanej cyfry
    Matrix& operator+(double a);
    //wypisanie macierzy
    friend std::ostream& operator<<(std::ostream& o, Matrix& m);
    //sprawdza, czy każdy element macierzy spełnia równość 𝐴(𝑛, 𝑚) = 𝐵(𝑛, 𝑚)
    //jeśli nie, to nie możemy mówić że macierze są równe, jeśli tak, to możemy
    bool operator==(const Matrix& m);
    //operator większości sprawdza, czy każdy element macierzy spełnia nierówność 𝐴(𝑛, 𝑚) > 𝐵(𝑛, 𝑚). Jeśli tak, to możemy powiedzieć że macierz jest większa, w przeciwnym wypadku nie możemy stwierdzić, że macierz jest większa.
    bool operator>(const Matrix& m);
    //operator mniejszości 
    bool operator<(const Matrix& m);

};