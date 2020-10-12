#include "matrix.h"

using namespace task;


double& Row::operator[](size_t col) {
    return this->data[col];
}

const double& Row::operator[](size_t col) const {
    return this->data[col];
}

size_t Row::size() const {
    return this->size_;
}

Row::Row(const Row &copy) {
    this->data = new double[copy.size()];
    this->size_ = copy.size();
    for (size_t i = 0; i < this->size_; ++i) {
        this->data[i] = copy.data[i];
    }
}

Row::~Row() {
    delete[] this->data;
}

Row::Row() : size_(1) {
    this->data = new double[1];
    this->data[0] = 0.0;
}

Row::Row(size_t size) : size_(size) {
    this->data = new double[size];
    for (size_t i = 0; i < size; ++i) {
        this->data[i] = 0.;
    }
}

Row& Row::operator=(const Row &copy) {
    if (&copy == this) {return *this;}
    delete[] this->data;
    this->size_ = copy.size();
    this->data = new double[copy.size()];
    for (size_t i = 0; i < size_; ++ i) {
        this->data[i] = copy.data[i];
    }
    return *this;
}

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(new Row[rows]) {
    for (size_t i = 0; i < rows; ++ i) {
        this->data[i] = Row(cols);
    }
    size_t min = rows;
    if (rows > cols) {
        min = cols;
    }
    for (size_t i = 0; i < min; ++i) {
        data[i][i] = 1.;
    }
}

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(const Matrix &copy) : rows(copy.rows), cols(copy.cols), data(new Row[rows]) {
    for (size_t i = 0; i < rows; ++i) {
        data[i] = copy.data[i];
    }
}

Matrix& Matrix::operator=(const Matrix &a) {
    if (&a == this) { return *this; }
    this->rows = a.rows;
    this->cols = a.cols;
    delete[] this->data;
    this->data = new Row[a.rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = a.data[i];
    }
    return *this;
}

double& Matrix::get(size_t row, size_t col) {
    if (row >= this->rows || col >= this->cols) {
        throw OutOfBoundsException();
    }
    return this->data[row][col];
}

const double &Matrix::get(size_t row, size_t col) const {
    if (row >= this->rows || col >= this->cols) {
        throw OutOfBoundsException();
    }
    return this->data[row][col];
}

void Matrix::set(size_t row, size_t col, const double &value) {
    if (row >= this->rows || col >= this->cols) {
        throw OutOfBoundsException();
    }
    this->data[row][col] = value;
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
    Row *temp = new Row[new_rows];
    for (size_t i = 0; i < new_rows; ++i) {
        temp[i] = Row(new_cols);
    }
    size_t min_rows = new_rows;
    size_t min_cols = new_cols;
    if (min_rows > this->rows) { min_rows = this->rows; }
    if (min_cols > this->cols) { min_cols = this->cols; }
    for (size_t i = 0; i < min_rows; ++i) {
        for (size_t j = 0; j < min_cols; ++j) {
            temp[i][j] = this->data[i][j];
        }
    }
    delete[] this->data;
    this->data = temp;
    this->rows = new_rows;
    this->cols = new_cols;
}

Row& Matrix::operator[](size_t row) {
    if (row >= this->rows) {
        throw OutOfBoundsException();
    }
    return this->data[row];
}

const Row &Matrix::operator[](size_t row) const {
    if (row >= this->rows) {
        throw OutOfBoundsException();
    }
    return this->data[row];
}

Matrix& Matrix::operator+=(const Matrix &a) {
    if (this->rows != a.rows || this->cols != a.cols) {
        throw SizeMismatchException();
    }
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            this->data[i][j] += a[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix &a) {
    if (this->rows != a.rows || this->cols != a.cols) {
        throw SizeMismatchException();
    }
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            this->data[i][j] -= a[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix &a) {
    if (this->cols != a.rows) {
        throw SizeMismatchException();
    }
    Matrix answer(this->rows, a.cols);
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            answer[i][j] = 0.;
            for (size_t m = 0; m < this->cols; ++m) {
                answer[i][j] += this->data[i][m] * a[m][j];
            }
        }
    }
    *this = answer;
    return *this;
}

Matrix& Matrix::operator*=(const double &number) {
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            this->data[i][j] *= number;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &a) const {
    Matrix temp = *this;
    return temp += a;
}

Matrix Matrix::operator-(const Matrix &a) const {
    Matrix temp = *this;
    return temp -= a;
}

Matrix Matrix::operator*(const Matrix &a) const {
    Matrix temp = *this;
    return temp *= a;
}

Matrix Matrix::operator*(const double &a) const {
    Matrix temp = *this;
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            temp.data[i][j] *= a;
        }
    }
    return temp;
}

Matrix Matrix::operator-() const {
    Matrix temp = *this;
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            temp.data[i][j] *= -1;
        }
    }
    return temp;
}

Matrix Matrix::operator+() const {
    return *this;
}

double Matrix::det() const {
    if (this->rows != this->cols) {
        throw SizeMismatchException();
    }
    Matrix temp = *this;
    size_t size = this->rows;

    double result = 1.0;
    for (size_t i = 0; i < size; ++i) {
        size_t k = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (fabs(temp[j][i]) > fabs(temp[k][i])) {
                k = j;
            }
        }
        if (fabs(temp[k][i]) < EPS) {
            result = 0;
            break;
        }
        std::swap_ranges(temp[i].data, temp[i].data + size, temp[k].data);
        if (i != k) {
            result = -result;
        }
        result *= temp[i][i];
        for (size_t j = i + 1; j < size; ++j) {
            temp[i][j] /= temp[i][i];
        }
        for (size_t j = 0; j < size; ++j) {
            if (j != i && fabs(temp[j][i]) > EPS) {
                for (size_t p = i + 1; p < size; ++p) {
                    temp[j][p] -= temp[i][p] * temp[j][i];
                }
            }
        }
    }

    return result;
}

void Matrix::transpose() {
    Row *temp = new Row[this->cols];
    for (size_t i = 0; i < this->cols; ++i) {
        temp[i] = Row(this->rows);
    }
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            temp[j][i] = this->data[i][j];
        }
    }
    delete[] this->data;
    this->data = temp;
    size_t temp_row = this->rows;
    this->rows = this->cols;
    this->cols = temp_row;
}

Matrix Matrix::transposed() const {
    Matrix temp = *this;
    temp.transpose();
    return temp;
}

double Matrix::trace() const {
    if (this->rows != this->cols) {
        throw SizeMismatchException();
    }
    double temp = 0.;
    for (size_t i = 0; i < this->rows; ++i) {
        temp += this->data[i][i];
    }
    return temp;
}

std::vector<double> Matrix::getRow(size_t row) {
    if (row >= this->rows) {
        throw SizeMismatchException();
    }
    std::vector<double> temp;
    for (size_t i = 0; i < this->cols; ++i) {
        temp.push_back(this->data[row][i]);
    }
    return temp;
}

std::vector<double> Matrix::getColumn(size_t column) {
    if (column >= this->cols) {
        throw SizeMismatchException();
    }
    std::vector<double> temp;
    for (size_t i = 0; i < this->rows; ++i) {
        temp.push_back(this->data[i][column]);
    }
    return temp;
}

bool Matrix::operator==(const Matrix &a) const {
    if (this->rows == a.rows && this->cols == a.cols) {
        for (size_t i = 0; i < this->rows; ++i) {
            for (size_t j = 0; j < this->cols; ++j) {
                if (fabs(this->data[i][j] - a.data[i][j]) >= EPS) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

size_t Matrix::sizeRows() const {
    return this->rows;
}

size_t Matrix::sizeCols() const {
    return this->cols;
}

bool Matrix::operator!=(const Matrix &a) const {
    return !(*this == a);
}

Matrix task::operator*(const double &a, const Matrix &b) {
    Matrix temp = b;
    temp *= a;
    return temp;
}

std::ostream& task::operator<<(std::ostream &output, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.sizeRows(); ++i) {
        for (size_t j = 0; j < matrix.sizeCols(); ++j) {
            output << matrix[i][j] << " ";
        }
        output << "\n";
    }
    return output;
}

std::istream& task::operator>>(std::istream &input, Matrix &matrix) {
    size_t rows, cols;
    input >> rows >> cols;
    matrix = Matrix(rows, cols);
    for (size_t i = 0; i < matrix.sizeRows(); ++i) {
        for (size_t j = 0; j < matrix.sizeCols(); ++j) {
            input >> matrix[i][j];
        }
    }
    return input;
}
