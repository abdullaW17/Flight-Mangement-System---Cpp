#ifndef GRAPH_H
#define GRAPH_H
#include <SFML/Graphics.hpp>  // SFML graphics library
#include <string>
#include<iomanip>
#include "layoverqueue.h"
#include <chrono>    // for pause 
#include <thread>  
using namespace std;

class node 
{
    public:
    string destination;
    string airline ;
    string date;
    string departuretime;
    string arrivaltime;
    double cost;

    node *next;

    node(string dest, string air, string dt, string dep, string arr, double c);
};

class adjlist                            
{
    public:
    node *head;

    adjlist();
    void insert(string dest, string airline, string date, string dep, string arr, double cost);
    void display(const string &src) const;
};

class graph 
{
    private:
    string citynames[12];
    int citycount;

    adjlist a[12];
        sf::RenderWindow window;  // SFML window
    
    sf::Font font;            // SFML font for text
    sf::Text text;            // SFML text for displaying city names or other info

    void drawCity(int x, int y, const string &cityName);  // Helper function to draw a city
    void drawFlightRoute(int x1, int y1, int x2, int y2, const string &airline);  // Helper function to draw a flight route

    public:
    graph();
    void addcity(const string &city);
    int getcityindex(const string &city) const;
    void insertedge(const string &src, const string &dest, const string &airline, const string &date, const string &dep, const string &arr, double cost);
    void displaygraph() const;
    void searchflights(const string &src, const string &dest, const string &date);
    void bookflight(const string &src, const string &dest, const string &date);
    void findshortestroute(const string &src, const string &dest);
    void searchflightswithpreferences(const string& src, const string& dest, const string& preferredairline, const string& transitcity);
    void searchflightswithlayovers(const string& src, const string& dest);
    void generateSubgraphByAirline(const string &preferredAirline);
    void advanceroute(const string& src, const string& dest);
    void findshortestroutes(const string &src, const string &dest,sf::RenderWindow &window);
    void searchflightswithpreferencess(const string& src, const string& dest, const string& preferredairline, const string& transitcity, sf::RenderWindow &window);
    void searchflightswithlayoverss(const string& src, const string& dest,sf::RenderWindow &window);
    void displaygraphSFML() const;  // SFML-specific method to display the graph
    void searchflightss(const string &src, const string &dest, const string &date, sf::RenderWindow &window);
   


};

#endif
