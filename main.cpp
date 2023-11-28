#include "matrix.h"

//konstruktor domyslny
Matrix::Matrix(void){
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

//destruktor
Matrix::~Matrix(){
    for(int i = 0; i < n; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

//wypisanie macierzy
ostream& operator<<(ostream& o, Matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.matrix[i][j] << " ";
        }
        o << endl;
    }
    return o;
}

//metoda alokująca pamięc na macierz
Matrix& Matrix::alokuj(int n){
    this->n = n;
    this->matrix = new int*[n];
    for(int i = 0; i < n; i++){
        this->matrix[i] = new int[n];
    }
    return *this;
}

//metoda wstawiająca wartość
Matrix& Matrix::wstaw(int x, int y, int value){//wiersz, kolumna, wartosc
    this->matrix[x][y] = value;
    return *this;
}

//zwraca wartość elementu x, y
int Matrix::pokaz(int x, int y){
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
Matrix& Matrix::losuj(int x){
    srand(time(NULL));
    int* tab = new int[x];
    for(int i = 0; i < x; i++){
        tab[i] = rand() % 10;
    }
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] = tab[k];
            k++;
            if(k == x){
                k = 0;
            }
        }
    }
    delete[] tab;
    return *this;
}

//po przekątnej są wpisane dane z tabeli, a pozostałe elementy są równe 0,
Matrix& Matrix::diagonalna(int* tab){
    int k = 0;
    for(int i = 0; i < n; i++){
        this->matrix[i][i] = tab[k];
        k++;
    }
    return *this;
}

//po przekątnej są wpisane dane z tabeli, a pozostałe elementy są równe 0. Parametr k może oznaczać: 0 - przekątna przechodząca przez środek (czyli tak jak metoda diagonalna), cyfra dodatnia przesuwa diagonalną do góry macierzy o podaną cyfrę, cyfra ujemna przesuwa diagonalną w dół o podaną cyfrę
Matrix& Matrix::diagonalna_k(int* tab, int k){
    int l = 0;
    if(k == 0){
        for(int i = 0; i < n; i++){
            this->matrix[i][i] = tab[l];
            l++;
        }
    }
    else if(k > 0){
        for(int i = 0; i < n; i++){
            if(i + k < n){
                this->matrix[i][i + k] = tab[l];
                l++;
            }
        }
    }
    else if(k < 0){
        for(int i = 0; i < n; i++){
            if(i + k >= 0){
                this->matrix[i][i + k] = tab[l];
                l++;
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
Matrix& Matrix::operator*(Matrix& m){
    Matrix* temp = new Matrix(n);
    int suma = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            suma = 0;
            for(int k = 0; k < n; k++){
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
bool Matrix::operator==(const Matrix& m){
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(this->matrix[i][j] != m.matrix[i][j]){
                flag = false;
            }
        }
    }
    return flag;
}

//operator większości sprawdza, czy każdy element macierzy spełnia nierówność 𝐴(𝑛, 𝑚) > 𝐵(𝑛, 𝑚). Jeśli tak, to możemy powiedzieć że macierz jest większa, w przeciwnym wypadku nie możemy stwierdzić, że macierz jest większa.
bool Matrix::operator>(const Matrix& m){
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(this->matrix[i][j] <= m.matrix[i][j]){
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
            if(this->matrix[i][j] >= m.matrix[i][j]){
                flag = false;
            }
        }
    }
    return flag;
}



int main(){

    int tab1[9] = {1,2,3,4,5,6,7,8,9};
    int tab2[9] = {9,8,7,6,5,4,3,2,1};
    Matrix m1(3, tab1);
    Matrix m2(3, tab2);

    //wypisz macierze
    cout << "Macierz m1:" << endl << m1 << endl;
    cout << "Macierz m2:" << endl << m2 << endl;

    //wypisz macierz m1+m2
    cout << "Macierz m1+m2:" << endl << m1 + m2 << endl;


    return 0;
}