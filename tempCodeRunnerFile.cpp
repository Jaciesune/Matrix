Matrix operator+(int a, Matrix& m){
    Matrix* temp = new Matrix(m.n);
    for(int i = 0; i < m.n; i++){
        for(int j = 0; j < m.n; j++){
            temp->matrix[i][j] = m.matrix[i][j] + a;
        }
    }
    return *temp;
}