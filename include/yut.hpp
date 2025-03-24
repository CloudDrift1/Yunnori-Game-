#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#ifndef __YUT_H_INCLUDED__
#define __YUT_H_INCLUDED__
using namespace std;


#define BACK_DO 0
#define DO 1
#define GAE 2
#define GEOL 3
#define YUT 4
#define MO 5


class YutName {
  public:
    string name;
    bool operator<(const YutName &other) const {

        static const map<string, int> yutOrder = {
            {"back-do", BACK_DO},
            {"do", DO},
            {"gae", GAE},
            {"geol", GEOL},
            {"yut", YUT},
            {"mo", MO}
        };
        return yutOrder.at(name) < yutOrder.at(other.name);
    }
};

class Yut {

  public:
    Yut(float prob) : prob(prob) {}
    friend class Player;
    friend class AnimalPlayer;

  private:
    float prob;
    int throwOneYut();
    string throwFourYuts();
};

#endif