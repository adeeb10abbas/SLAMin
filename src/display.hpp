#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Display{
  Display(){
    sf::RenderWindow window(sf::VideoMode(200, 200), "Display Working here.");   
    }
  void paint(vector<double> array) {};
  void clear() {};
  private:
    vector<double> frame;
};