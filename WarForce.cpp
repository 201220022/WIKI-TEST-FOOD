#include "Definition.h"
#include "Core.h"
#include "Tools.h"
#include "WarForce.h"
vector<float> distr[4];
vector<vector<vector<float>>> C397;
float P(int curm, float ming, int a = 0, float pa = 0, int b = 0, float pb = 0, int c = 0, float pc = 0, int d = 0, float pd = 0, int e = 0, float pe = 0) {
    float out = 1;
    float p0, p1, p2, p3, p4, p5;
    p0 = 1 - ming;
    p1 = ming * pa;
    p2 = ming * pb;
    p3 = ming * pc;
    p4 = ming * pd;
    p5 = ming * pe;
    for (int i = 1; i <= (curm - a - b - c - d - e); i++) {
        out *= p0;
        out /= i;
        while (out < 1 && curm != 0) { out *= curm; curm -= 1; }
    }
    for (int i = 1; i <= a; i++) {
        out *= p1;
        out /= i;
        while (out < 1 && curm != 0) { out *= curm; curm -= 1; }
    }
    for (int i = 1; i <= b; i++) {
        out *= p2;
        out /= i;
        while (out < 1 && curm != 0) { out *= curm; curm -= 1; }
    }
    for (int i = 1; i <= c; i++) {
        out *= p3;
        out /= i;
        while (out < 1 && curm != 0) { out *= curm; curm -= 1; }
    }
    for (int i = 1; i <= d; i++) {
        out *= p4;
        out /= i;
        while (out < 1 && curm != 0) { out *= curm; curm -= 1; }
    }
    for (int i = 1; i <= e; i++) {
        out *= p5;
        out /= i;
        while (out < 1 && curm != 0) { out *= curm; curm -= 1; }
    }
    while (curm != 0) { out *= curm; curm -= 1; }
    return out;
}
void Distribution(Entity* src) {
	
}