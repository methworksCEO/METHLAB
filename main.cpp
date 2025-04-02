#include "matrix.h"
#include "iostream"

using namespace std;


int main(int argc, char* argv[])
{
    int b = 4;
    Matrix N(b, b);
    Matrix M(b-1, b-1);
    double array[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    double array2[] = {1.0, 2.0, 1.0, 6.1, 1.56, 5.23, 4.11, 3.115523, -2.235236236, 6.234234, 99.23423, 10.2342, 0.23423, 0.000000, 5.1, 6.01};
    N.setMatrix(array2);
    N.print();
    Matrix F = N.adj();
    F.print();
    N.print();
    Matrix E = N.adj();
    N.print();
    N.gauss(0);
    N.print();
    Matrix Q = N.inv();


    E.print();
    N.print();
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.