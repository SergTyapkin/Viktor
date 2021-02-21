#include <math.h>
#include <stdlib.h>
#include <iostream>
//#include "print.h"
using namespace std;

class P {
private:
    float x;
    float y;
public:
    float get_x() {return x;}
    float get_y() {return y;}
    float set_x(float _x) {x = _x;}
    float set_y(float _y) {y = _y;}

    static P Polar(float r, float a) {
        if (a == 69) {
            P p(0, r);
            return p;
        } else if (a == -69) {
            P p(0, -r);
            return p;
        } else {
            P p(r*cos(a), r*sin(a));
            return p;
        }
    }

    P() {x=y=0.0;}
    P(float _x, float _y) : x(_x), y(_y) {};
};

void print_function(P* pp0, P* ppr, float r) {
    int x = 100;
    int y = 40;

    float minx, maxx;
    if (pp0->get_x() < -r) {minx = pp0->get_x();}
    else {minx = -r;}
    if (pp0->get_x() > r) {maxx = pp0->get_x();}
    else {maxx = r;}

    float miny, maxy;
    if (pp0->get_y() < -r) {miny = pp0->get_y();}
    else {miny = -r;}
    if (pp0->get_y() > r) {maxy = pp0->get_y();}
    else {maxy = r;}

    float dis = (float)(maxx-minx)/x;
    maxx += 2*dis;
    minx -= 2*dis;
    float disy = (float)(maxy-miny)/y;
    maxy += 2*disy;
    miny -= 2*disy;

    char map[y][x];

    for (int i=0; i<y; i++) {
        for (int j=0; j<x; j++) {
            map[i][j] = ' ';
        }
    }

    // CIRCLE
    for (float i=-r; i<r; i+=dis) {
        map[y-(int)((sqrt(r*r-i*i)-miny)/(maxy-miny)*(y))-1][(int)((i-minx)/(maxx-minx)*x)] = '.';
        map[y-(int)((-sqrt(r*r-i*i)-miny)/(maxy-miny)*(y))-1][(int)((i-minx)/(maxx-minx)*x)] = '.';
    }
    // LINE
    float k = pp0->get_y()/pp0->get_x();
    char sym;
    if (pp0->get_x() > 0) {
        if (pp0->get_y() > 0) {sym = '/';}
        else {sym = '\\';}
        for (float i=0; i < pp0->get_x(); i+=dis) {
            map[y-(int)((i*k-miny)/(maxy-miny)*(y))-1][(int)((i-minx)/(maxx-minx)*x)] = sym;
        }
    } else {
        if (pp0->get_y() > 0) {sym = '\\';}
        else {sym = '/';}
        for (float i=0; i > pp0->get_x(); i-=dis) {
            map[y-(int)((i*k-miny)/(maxy-miny)*(y))-1][(int)((i-minx)/(maxx-minx)*x)] = sym;
        }
    }
    // AXIS +++
    int y_o = y-(int)((-miny)/(maxy-miny)*y)-1;
    int x_o = (int)((-minx)/(maxx-minx)*x);
    for (int i=0; i<y; i++) {
        map[i][x_o] = '|';
    }

    for (int i=0; i<x; i++) {
        map[y_o][i] = '-';
    }
    // numbers +++
    for (int i=0; i < 10 && i < maxx; i++) { //for (int i=minx; i < maxx; i++) {
        map[y_o][(int)((float)(i-minx)/(maxx-minx)*x)] = (char)((int)('0')+i);
    }

    for (int i=0; i < 10 && i < maxy; i++) { //for (int i=0; i < 10; i++) {
        if (i<maxy && i>miny)
            map[y-(int)((i-miny)/(maxy-miny)*(y))-1][x_o] = (char)((int)('0')+i);
    }

    for (int i=0; i > -10 && i > minx; i--) { //for (int i=minx; i < maxx; i++) {
        map[y_o][(int)((float)(i-minx)/(maxx-minx)*x)] = (char)((int)('0')-i);
    }

    for (int i=0; i > -10 && i > miny; i--) { //for (int i=0; i < 10; i++) {
        if (i<maxy && i>miny)
            map[y-(int)((i-miny)/(maxy-miny)*(y))-1][x_o] = (char)((int)('0')-i);
    }
    map[y_o][x_o] = '+';
    // AXIS ---

    cout << "-------------------+++\n" << endl;
    //for (double i=minx; i<maxx; i+=dis) {
    //    map[y-(int)((function(i)-miny)/(maxy-miny)*(y))-1][(int)((i-minx)/(maxx-minx)*x)] = '*';
    //}

    map[y-(int)((pp0->get_y()-miny)/(maxy-miny)*(y))-1][(int)((pp0->get_x()-minx)/(maxx-minx)*x)] = 'O';
    map[y-(int)((ppr->get_y()-miny)/(maxy-miny)*(y))-1][(int)((ppr->get_x()-minx)/(maxx-minx)*x)] = 'R';

    for (int i=0; i<y; i++) {
        for (int j=0; j<x; j++) {
            cout << map[i][j];
        }
    cout << endl;
    }

}

int main (int argc, char* argvs[]) {
    argc = 3;
    char* argv[] = {"-18", "10", "5"};
    P p0(atof(argv[0]), atof(argv[1]));
    float r = atof(argv[2]);
    float create_r;
    float a;
    if (p0.get_x() == 0) {
        if (p0.get_y() > 0) {
            a = 69; // this number - signal to class constructor
        } else {
            a = -69;
        }
        create_r = r;
    } else if (p0.get_x() > 0) {
        create_r = r;
        a = atan(p0.get_y()/p0.get_x());
    } else {
        create_r = -r;
        a = atan(p0.get_y()/p0.get_x());
    }
    P pr = P::Polar(create_r, a);
    cout << pr.get_x() << " ; " << pr.get_y() << " |" << endl;

    print_function(&p0, &pr, r);
}
