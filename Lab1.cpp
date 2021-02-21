#include <math.h>
#include <iostream>
using namespace std;

#define ERR_COUNT_ARGS -1
#define ERR_INCORRECT_INPUT -2

#define M_PI 3.14159265358979323846

class Point {
public:
    Point(float x, float y): x(x), y(y) {;}

    float getX() {return x;}
    float getY() {return y;}

    static Point newPolarPoint(float r, float a) {
        return Point(r * cos(a), r * sin(a));
    }
private:
    float x, y;
};

int checkInput(int argc, const char* argv[], float* numbers) {
    if (argc != 4) {
        cout << "Wrong count of arguments. Using: " << argv[0] << " [x, y] radius" << endl;
        return ERR_COUNT_ARGS;
    }

    for (int i = 1; i < argc; i++) {
        if (!(numbers[i-1] = atof(argv[i]))) {
            cout << "Wrong input. Must be float numbers" << endl;
            return ERR_INCORRECT_INPUT;
        }
    }
    return 0;
}

float getAngle(float x, float y) {
    return atan(y / x);
}

int main (int argc, char* argvs[]) {
    argc = 4;
    const char* argv[] = {"main.exe", "-18", "10", "5"};
    float argvNumbers[3];

    int err = checkInput(argc, argv, argvNumbers);
    if (err != 0)
        return err;

    Point P1(argvNumbers[0], argvNumbers[1]);
    Point P2 = P1.newPolarPoint(argvNumbers[2], getAngle(P1.getX(), P1.getY()));

    cout << "Point on circle: [" << P2.getX() << ", " << P2.getY() << "]" << endl;

    return 0;
}
