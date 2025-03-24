#include "yut.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;


int Yut::throwOneYut() {
    int res = rand() % 100;
    if (res < prob * 100) {
        return 1; // front
    } else {
        return 0; // back
    }
}

/*
- Using the throwOneYut function to get a yut result
- Yut result is obtained based on the results from the front and back
result of each yut stick.
- One of the yut sticks is marked, so we need to consider the back-do.

- Output
    - yut result (back-do, do, gae, geol, yut, and mo)
*/
string Yut::throwFourYuts() {

    vector<string> yutSticks = {"y1", "y2", "y3", "y4"};
    vector<int> yutRes(yutSticks.size(), -1);

    for(int i=0; i<yutSticks.size(); i++){
        int res = throwOneYut();
        yutRes.at(i) = res;
    }

    //assume the fourth stick is marked

    int sum = 0;

    for(auto& elem:yutRes){
        sum += elem;
    }

    if(sum == 0){
        return "yut";
    }
    else if(sum == 1){
        return "geol";
    }
    else if(sum == 2){
        return "gae";
    }
    else if((sum == 3) && (yutRes.at(3) == 0)){
        return "back-do";
    }
    else if((sum == 3) && (yutRes.at(3) == 1)){
        return "do";
    }
    else if(sum == 4){
        return "mo";
    }
    else{
        return "None";
    }
}