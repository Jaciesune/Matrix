#include "matrix.h"
#include <fstream>

//konstruktor domyslny
Matrix::Matrix() : n(0), matrix(nullptr){
    this->n = 0;
    this->matrix = new int*[n];
    for(int i = 0; i < n; i++){
        this->matrix[i] = new int[n];
    }
}

//konstruktor z parametrem
Matrix::Matrix(int n){
    this->n = n;
    this->matrix = new int*[n];
    for(int i = 0; i < n; i++){
        this->matrix[i] = new int[n];
    }
}

//konstruktor kopiujacy
Matrix::Matrix(const Matrix& m){
    this->n = m.n;
    this->matrix = new int*[n];
    for(int i = 0; i < n; i++){
        this->matrix[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] = m.matrix[i][j];
        }
    }
}

//konstruktor alokuje pamięc i przepisuje dane z tabeli
Matrix::Matrix(int n, int* tab){
    this->n = n;
    this->matrix = new int*[n];
    for(int i = 0; i < n; i++){
        this->matrix[i] = new int[n];
    }
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] = tab[k];
            k++;
        }
    }
}

// Dekonstruktor
Matrix::~Matrix() {
    if (matrix != nullptr) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

// Operator Wypisywania
ostream& operator<<(ostream& o, const Matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.matrix[i][j] << " ";
        }
        o << endl;
    }
    return o;
}

//metoda alokująca pamięc na macierz
Matrix& Matrix::alokuj(int n) {
    this->n = n;
    this->matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        this->matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            this->matrix[i][j] = 1;
        }
    }
    return *this;
}


//metoda wstawiająca wartość
Matrix& Matrix::wstaw(int x, int y, int value){//wiersz, kolumna, wartosc
    this->matrix[x][y] = value;
    return *this;
}

//zwraca wartość elementu x, y
int Matrix::pokaz(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return 0;
    }

    return this->matrix[x][y];
}

//zamienia wiersze z kolumnami
Matrix& Matrix::odwroc(void){
    int** temp = new int*[n];
    for(int i = 0; i < n; i++){
        temp[i] = new int[n];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp[i][j] = this->matrix[j][i];
        }
    }
    for(int i = 0; i < n; i++){
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
    this->matrix = temp;
    return *this;
}

//wypełnia cyframi od 0 do 9 wszystkie elementy tablicy
Matrix& Matrix::losuj(void){
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] = rand() % 10;
        }
    }
    return *this;
}

//wypełniamy cyframi od 0 do 9 elementy macierzy. Zmienna x określa ile cyfr będziemy losować Następnie algorytm losuje, w które miejsca wstawi wylosowane cyfry
Matrix& Matrix::losuj(int x) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int* tab = new int[x];
        for (int j = 0; j < x; j++) {
            tab[j] = rand() % 10;
        }

        int k = 0;
        for (int j = 0; j < n; j++) {
            this->matrix[i][j] = tab[k];
            k++;
            if (k == x) {
                k = 0;
            }
        }

        delete[] tab;
    }
    return *this;
}

//po przekątnej są wpisane dane z tabeli, a pozostałe elementy są równe 0,
Matrix& Matrix::diagonalna(int* tab) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Jeśli jesteśmy na przekątnej, przypisz wartość z tablicy
                if (k < n) {
                    this->matrix[i][j] = tab[k];
                    k++;
                } else {
                    // Jeśli skończyły się wartości w tablicy, wpisz 0
                    this->matrix[i][j] = 0;
                }
            } else {
                // Jeśli nie jesteśmy na przekątnej, wpisz 0
                this->matrix[i][j] = 0;
            }
        }
    }
    return *this;
}

//po przekątnej są wpisane dane z tabeli, a pozostałe elementy są równe 0. Parametr k może oznaczać: 0 - przekątna przechodząca przez środek (czyli tak jak metoda diagonalna), cyfra dodatnia przesuwa diagonalną do góry macierzy o podaną cyfrę, cyfra ujemna przesuwa diagonalną w dół o podaną cyfrę
Matrix& Matrix::diagonalna_k(int* tab, int k) {
    int l = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (k == 0 && i == j) {
                this->matrix[i][j] = tab[l];
                l++;
            } else if (k > 0 && i + k < n && j == i + k) {
                this->matrix[i][j] = tab[l];
                l++;
            } else if (k < 0 && i - k >= 0 && j == i - k) {
                this->matrix[i][j] = tab[l];
                l++;
            } else {
                this->matrix[i][j] = 0;
            }
        }
    }
    return *this;
}

//przepisuje dane z tabeli do kolumny, którą wskazuje zmienna x
Matrix& Matrix::kolumna(int x, int* t){
    for(int i = 0; i < n; i++){
        this->matrix[i][x] = t[i];
    }
    return *this;
}

//przepisuje dane z tabeli do wiersza, który wskazuje zmienna y
Matrix& Matrix::wiersz(int y, int* t){
    for(int i = 0; i < n; i++){
        this->matrix[y][i] = t[i];
    }
    return *this;
}

//uzupełnia macierz: 1-na przekątnej, 0-poza przekątną
Matrix& Matrix::przekatna(void){
    for(int i = 0; i < n; i++){
        this->matrix[i][i] = 1;
    }
    return *this;
}

//uzupełnia macierz: 1-pod przekątną, 0-nad przekątną i po przekątnej
Matrix& Matrix::pod_przekatna(void){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i > j){
                this->matrix[i][j] = 1;
            }
            else{
                this->matrix[i][j] = 0;
            }
        }
    }
    return *this;
}

//uzupełnia macierz: 1-nad przekątną, 0-pod przekątną i po przekątnej
Matrix& Matrix::nad_przekatna(void){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i < j){
                this->matrix[i][j] = 1;
            }
            else{
                this->matrix[i][j] = 0;
            }
        }
    }
    return *this;
}

//uzupełnia macierz w ten sposób dla n=4:
//0101
//1010
//0101
//1010
Matrix& Matrix::szachownica(void){
    int k = 0;
    for(int i = 0; i < n; i++){
        if(i % 2 == 0){
            for(int j = 0; j < n; j++){
                if(j % 2 == 0){
                    this->matrix[i][j] = 0;
                }
                else{
                    this->matrix[i][j] = 1;
                }
            }
        }
        else{
            for(int j = 0; j < n; j++){
                if(j % 2 == 0){
                    this->matrix[i][j] = 1;
                }
                else{
                    this->matrix[i][j] = 0;
                }
            }
        }
    }
    return *this;
}

//A+B
Matrix& Matrix::operator+(Matrix& m){
    Matrix* temp = new Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp->matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
        }
    }
    return *temp;
}

//A*B
Matrix& Matrix::operator*(Matrix& m) {
    Matrix* temp = new Matrix(n);
    temp->alokuj(n);  // Zainicjowanie macierzy zerami
    int suma = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            suma = 0;
            for(int k = 0; k < n; k++) {
                suma += this->matrix[i][k] * m.matrix[k][j];
            }
            temp->matrix[i][j] = suma;
        }
    }
    return *temp;
}


//A+int 
Matrix& Matrix::operator+(int a){
    Matrix* temp = new Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp->matrix[i][j] = this->matrix[i][j] + a;
        }
    }
    return *temp;
}


//A*int
Matrix& Matrix::operator*(int a){
    Matrix* temp = new Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp->matrix[i][j] = this->matrix[i][j] * a;
        }
    }
    return *temp;
}

//A-int
Matrix& Matrix::operator-(int a){
    Matrix* temp = new Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp->matrix[i][j] = this->matrix[i][j] - a;
        }
    }
    return *temp;
}

//int+A
Matrix operator+(int a, Matrix& m){
    Matrix* temp = new Matrix(m.n);
    for(int i = 0; i < m.n; i++){
        for(int j = 0; j < m.n; j++){
            temp->matrix[i][j] = m.matrix[i][j] + a;
        }
    }
    return *temp;
}

//int*A
Matrix operator*(int a, Matrix& m){
    Matrix* temp = new Matrix(m.n);
    for(int i = 0; i < m.n; i++){
        for(int j = 0; j < m.n; j++){
            temp->matrix[i][j] = m.matrix[i][j] * a;
        }
    }
    return *temp;
}

//int-A
Matrix operator-(int a, Matrix& m){
    Matrix* temp = new Matrix(m.n);
    for(int i = 0; i < m.n; i++){
        for(int j = 0; j < m.n; j++){
            temp->matrix[i][j] = m.matrix[i][j] - a;
        }
    }
    return *temp;
}

//A++
Matrix& Matrix::operator++(int){
    Matrix* temp = new Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp->matrix[i][j] = this->matrix[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j]++;
        }
    }
    return *temp;
}

//A--
Matrix& Matrix::operator--(int){
    Matrix* temp = new Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp->matrix[i][j] = this->matrix[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j]--;
        }
    }
    return *temp;
}

//++A
Matrix& Matrix::operator++(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j]++;
        }
    }
    return *this;
}

//--A
Matrix& Matrix::operator--(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j]--;
        }
    }
    return *this;
}

//każdy element w macierzy powiększamy o „a”
Matrix& Matrix::operator+=(int a){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] += a;
        }
    }
    return *this;
}

//każdy element w macierzy pomniejszamy o „a”
Matrix& Matrix::operator-=(int a){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] -= a;
        }
    }
    return *this;
}

//każdy element w macierzy mnożymy przez „a”
Matrix& Matrix::operator*=(int a){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] *= a;
        }
    }
    return *this;
}

//wszystkie cyfry są powiększone o część całkowitą z wpisanej cyfry
Matrix& Matrix::operator+(double a){
    int b = (int)a;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] += b;
        }
    }
    return *this;
}

//sprawdza, czy każdy element macierzy spełnia równość 𝐴(𝑛, 𝑚) = 𝐵(𝑛, 𝑚)
//jeśli nie, to nie możemy mówić że macierze są równe, jeśli tak, to możemy
bool Matrix::operator==(const Matrix& m) const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (this->matrix[i][j] != m.matrix[i][j]) {
                return false; // Jeśli znaleziono różnicę, zwróć false
            }
        }
    }
    return true; // Jeśli nie znaleziono różnic, zwróć true
}


//operator większości sprawdza, czy każdy element macierzy spełnia nierówność 𝐴(𝑛, 𝑚) > 𝐵(𝑛, 𝑚). Jeśli tak, to możemy powiedzieć że macierz jest większa, w przeciwnym wypadku nie możemy stwierdzić, że macierz jest większa.
bool Matrix::operator>(const Matrix& m){
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(this->matrix[i][j] < m.matrix[i][j]){
                flag = false;
            }
        }
    }
    return flag;
}

//operator mniejszości
bool Matrix::operator<(const Matrix& m){
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(this->matrix[i][j] > m.matrix[i][j]){
                flag = false;
            }
        }
    }
    return flag;
}


int main() {

    int tab[900] = {
6,7,9,4,3,4,6,7,4,2,2,3,5,7,6,2,0,4,5,7,7,1,5,3,6,7,1,0,2,7,
5,8,6,3,9,1,9,9,1,5,0,9,9,8,3,7,6,5,1,3,8,3,5,7,8,3,7,5,2,6,
0,0,2,7,6,4,2,1,6,3,1,0,6,4,0,7,0,6,4,4,5,7,1,4,9,4,8,3,2,4,
9,5,0,8,6,5,3,2,6,1,8,9,7,3,8,9,9,9,6,4,0,8,5,0,5,1,3,0,2,2,
5,8,7,8,2,9,9,1,9,3,7,3,3,0,4,2,2,2,2,7,1,4,2,9,5,7,8,4,4,0,
1,1,5,0,0,4,4,9,6,6,0,4,1,7,5,3,2,5,9,4,5,1,8,6,0,8,3,1,6,6,
0,6,7,0,4,7,9,5,5,1,3,1,1,3,1,8,9,0,4,2,0,1,9,6,9,6,5,7,5,3,
7,2,9,9,2,4,3,7,3,8,9,3,2,9,2,7,7,0,9,1,8,6,5,4,8,3,8,1,1,6,
8,8,9,9,9,5,4,9,9,6,0,7,1,0,0,8,6,7,6,2,4,7,3,4,8,0,6,1,9,1,
6,5,9,1,5,5,0,5,8,3,1,7,2,8,5,1,8,9,6,7,2,3,6,7,6,6,0,4,2,6,
5,7,7,0,2,7,1,6,6,0,5,4,3,8,2,7,0,1,5,0,4,9,4,9,0,6,4,9,1,9,
7,5,9,0,9,7,4,6,5,3,0,2,6,4,6,2,3,2,8,2,7,7,4,4,3,2,0,6,9,6,
6,5,2,6,1,2,0,2,7,0,9,3,2,0,3,3,7,6,8,3,4,3,9,7,3,9,6,8,6,9,
9,0,4,5,5,9,2,1,4,9,1,1,7,7,1,1,6,3,9,2,1,5,6,1,2,9,0,7,8,9,
0,2,8,3,6,2,3,1,4,0,6,3,9,9,4,8,0,2,9,8,4,2,8,9,1,3,2,9,0,3,
8,5,0,2,3,9,8,2,9,4,5,8,8,7,6,9,4,8,7,2,3,3,2,5,4,8,7,1,3,3,
0,5,5,2,8,2,9,7,9,8,5,5,5,2,1,8,6,1,2,7,4,4,4,4,6,3,2,8,5,0,
0,8,4,0,1,7,8,9,7,7,9,4,1,1,3,4,8,5,8,3,3,5,2,9,5,5,1,0,4,0,
6,9,1,0,1,6,6,5,0,2,4,7,1,1,6,4,1,7,2,7,3,2,5,5,4,3,8,6,9,4,
1,6,3,1,0,8,7,6,2,0,4,8,1,6,4,5,5,4,7,8,4,9,4,8,9,3,3,4,3,7,
6,1,5,2,8,3,4,5,5,6,4,0,1,4,6,0,6,5,2,6,5,0,1,3,9,1,9,3,6,9,
3,7,4,3,7,3,1,7,9,9,2,6,7,6,4,9,6,2,9,6,1,8,9,3,1,4,8,5,2,0,
6,6,9,8,1,3,1,7,7,4,3,7,3,1,0,3,8,2,6,1,4,3,0,1,4,7,9,7,1,4,
3,7,4,3,7,4,0,7,9,6,7,0,0,1,7,3,7,7,7,2,8,1,4,7,4,7,3,1,7,6,
0,6,9,9,6,2,5,2,3,2,3,1,9,2,6,7,2,0,7,5,4,6,2,0,7,0,8,2,2,6,
9,0,4,5,5,9,2,1,4,9,1,1,7,7,1,1,6,3,9,2,1,5,6,1,2,9,0,7,8,9,
7,2,9,9,2,4,3,7,3,8,9,3,2,9,2,7,7,0,9,1,8,6,5,4,8,3,8,1,1,6,
5,8,7,8,2,9,9,1,9,3,7,3,3,0,4,2,2,2,2,7,1,4,2,9,5,7,8,4,4,0,
8,5,0,2,3,9,8,2,9,4,5,8,8,7,6,9,4,8,7,2,3,3,2,5,4,8,7,1,3,3,
5,8,7,8,2,9,9,1,9,3,7,3,3,0,4,2,2,2,2,7,1,4,2,9,5,7,8,4,4,0
};

    Matrix m1;
    m1.alokuj(30);
    cout << m1;

    cout << endl;

    Matrix m2;
    m2.alokuj(30);
    
    cout << (m1 == m2);
    

    return 0;
}