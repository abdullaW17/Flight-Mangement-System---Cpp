#include <iostream>
#include <fstream>
#include "graph.h"
#include <iomanip>
#include <cstdlib>  // using for pause
//#include <conio.h>  // using for pause
#include <chrono>    // for pause 
#include <thread> 
#include <SFML/Graphics.hpp>  // SFML graphics library
#include <SFML/Audio.hpp>


using namespace std;

void playSound(const string& soundFile) {
    // Create a sound buffer
    sf::SoundBuffer buffer;
    
    // Load the sound from the file
    if (!buffer.loadFromFile(soundFile)) {
        cout << "Error loading sound file!" << endl;
        return;
    }
    
    // Create a sound object and set its buffer to the loaded sound
    sf::Sound sound;
    sound.setBuffer(buffer);
    
    // Play the sound
    sound.play();
    
    // Keep the program running until the sound finishes
    while (sound.getStatus() == sf::Sound::Playing) 
    {
        sf::sleep(sf::milliseconds(100)); // Sleep to avoid using too much CPU
    }
}

void display() 
{
    cout << endl << endl;
    cout << "\033[1;34m";        // blue color code
    cout << "\t\t\t ▗▖ ▗▖▗▞▀▚▖█ ▗▞▀▘ ▄▄▄  ▄▄▄▄  ▗▞▀▚▖    ▗▄▄▄▖▄▄▄       ▗▄▄▖▗▖ ▗▖▗▖  ▗▖    ▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖     ▗▄▖ ▗▄▄▄▖    ▗▄▄▄▖▗▖   ▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖    ▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖ ▗▄▖▗▄▄▄▖▗▄▄▄▖ ▗▄▖ ▗▖  ▗▖" << endl;
    cout << "\t\t\t▐▌ ▐▌▐▛▀▀▘█ ▝▚▄▖█   █ █ █ █ ▐▛▀▀▘      █ █   █     ▐▌   ▐▌▗▞▘ ▝▚▞▘     ▐▛▚▖▐▌▐▌ ▐▌▐▌  ▐▌    ▐▌ ▐▌  █      ▐▌   ▐▌     █  ▐▌   ▐▌ ▐▌  █      ▐▛▚▖▐▌▐▌ ▐▌▐▌  ▐▌  █  ▐▌   ▐▌ ▐▌ █    █  ▐▌ ▐▌▐▛▚▖▐▌" << endl;
    cout << "\t\t\t▐▌ ▐▌▝▚▄▄▖█     ▀▄▄▄▀ █   █ ▝▚▄▄▖      █ ▀▄▄▄▀      ▝▀▚▖▐▛▚▖   ▐▌      ▐▌ ▝▜▌▐▛▀▜▌▐▌  ▐▌    ▐▛▀▜▌  █      ▐▛▀▀▘▐▌     █  ▐▌▝▜▌▐▛▀▜▌  █      ▐▌ ▝▜▌▐▛▀▜▌▐▌  ▐▌  █  ▐▌▝▜▌▐▛▀▜▌ █    █  ▐▌ ▐▌▐▌ ▝▜▌" << endl;
    cout << "\t\t\t▐▙█▟▌     █                            █           ▗▄▄▞▘▐▌ ▐▌  ▐▌      ▐▌  ▐▌▐▌ ▐▌ ▝▚▞▘     ▐▌ ▐▌▗▄█▄▖    ▐▌   ▐▙▄▄▖▗▄█▄▖▝▚▄▞▘▐▌ ▐▌  █      ▐▌  ▐▌▐▌ ▐▌ ▝▚▞▘ ▗▄█▄▖▝▚▄▞▘▐▌ ▐▌ █  ▗▄█▄▖▝▚▄▞▘▐▌  ▐▌" << endl;
    cout << "\033[0m";
    cout << endl << endl;


}





int main() 
{

    display();

    cout << endl << "\t\t\t\tPress Any Key (And Then Enter Or Directly Press Enter) To Continue..."; 

    // Play the sound file "output.ogg"
    playSound("output.ogg"); 

    cin.get();

    cout << endl << "\t\t\t\tPlease Wait Main Menu Is Loading..." << endl;
    this_thread::sleep_for(chrono::seconds(3));  



    graph flightgraph;
    string filename = "Flights.txt";
    ifstream file(filename);
    if (!file) 
    {
        cout << endl << "Error In Opening File Please Try Again" << endl;
        return 1;
    }

    string source;
    string destination;
    string date;
    string departuretime;
    string arrivaltime;
    string airline;
    double cost;

    while (file >> source >> destination >> date >> departuretime >> arrivaltime >> cost >> airline) 
    {
        flightgraph.addcity(source);
        flightgraph.addcity(destination);
        flightgraph.insertedge(source, destination, airline, date, departuretime, arrivaltime, cost);
    }
    file.close();

    int choice;
    do 
    {

    cout << endl;
    cout << "\033[1;34m"; 
    cout << "\t\t\t\t┌─────────────────────────────────────────────────────┐" << endl;  
    cout << "\t\t\t\t|  ▗▖  ▗▖ ▗▄▖ ▗▄▄▄▖▗▖  ▗▖    ▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▖ ▗▖   |" << endl;
    cout << "\t\t\t\t|  ▐▛▚▞▜▌▐▌ ▐▌  █  ▐▛▚▖▐▌    ▐▛▚▞▜▌▐▌   ▐▛▚▖▐▌▐▌ ▐▌   |" << endl;
    cout << "\t\t\t\t|  ▐▌  ▐▌▐▛▀▜▌  █  ▐▌ ▝▜▌    ▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌▐▌ ▐▌   |" << endl;
    cout << "\t\t\t\t|  ▐▌  ▐▌▐▌ ▐▌▗▄█▄▖▐▌  ▐▌    ▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌▝▚▄▞▘   |" << endl;
    cout << "\t\t\t\t|                                                     |" << endl;       
    cout << "\t\t\t\t│ 1. View All Flights                                 │" << endl;
    cout << "\t\t\t\t│ 2. Search Flights                                   │" << endl;
    cout << "\t\t\t\t│ 3. Book Flight                                      │" << endl;
    cout << "\t\t\t\t│ 4. Find Shortest Route                              │" << endl;
    cout << "\t\t\t\t│ 5. Search Flights with Preferences                  │" << endl;
    cout << "\t\t\t\t│ 6. Search Flights with Layovers                     │" << endl;
    cout << "\t\t\t\t│ 7. Advanced Route Generation                        │" << endl;
    cout << "\t\t\t\t│ 8. Subgraphs                                        │" << endl;
    cout << "\t\t\t\t│ 9. Exit                                             │" << endl;
    cout << "\t\t\t\t└─────────────────────────────────────────────────────┘" << endl;
    cout << "\033[0m";  

    cout << endl << "\t\t\t\tEnter Your Choice Between 1-9 ---> ";

        while (!(cin >> choice) || choice < 0 || choice > 9) 
        {
            cout << "\033[31m" << endl << "\t\t\t\tInvalid choice! Please enter a number between 1 and 9, or 0 to exit." << endl;
            cin.clear();
            cin.ignore();
            cout << "\033[0m"; 
            cout << endl << "\t\t\t\tEnter Valid Choice ---> ";
        }
        switch (choice) 
        {
            case 1:
            {
                int choice;
                cout << endl << endl << "\t\t\t\t1. Terminal Based Output "<< endl;
                cout << "\t\t\t\t2. Graphical Based Output "<< endl;
                cout << "\t\t\t\tEnter Your Choice ---> ";
                cin >> choice;
                if(choice == 1)
                {
                cout << "\033[1;34m"; 
                cout << endl;
                cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
                cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
                cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
                
                flightgraph.displaygraph();
                }
                else if(choice == 2)
                {
                 flightgraph.displaygraphSFML();   
                }
                else
                {
                cout << "\t\t\t\tInput Validation "<<endl;
                }
                break;
            }

            case 2: 
            {  
                int choice;
                cout << endl << endl << "\t\t\t\t1. Terminal Based Output "<< endl;
                cout << "\t\t\t\t2. Graphical Based Output "<< endl;
                cout << "\t\t\t\tEnter Your Choice ---> ";
                cin >> choice;

                if(choice==1)
                {
                string sourcececity;
                string destinationity; 
                string traveldate;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> sourcececity;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destinationity;

                cout << endl << "\t\t\t\tEnter travel date ---> ";
                cin >> traveldate;

                flightgraph.searchflights(sourcececity, destinationity, traveldate);
                }
                else if(choice==2)
                {
                sf::RenderWindow window(sf::VideoMode(800, 600), "Search Flight");
                string sourcececity;
                string destinationity; 
                string traveldate;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> sourcececity;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destinationity;

                cout << endl << "\t\t\t\tEnter travel date ---> ";
                cin >> traveldate;

                flightgraph.searchflightss(sourcececity, destinationity, traveldate,window);
                }
                else
                {
                cout << "\t\t\t\tInput Validation "<<endl;
                }
                break;
            }

            case 3: 
            {
                string sourcececity1;
                string destinationity1; 
                string traveldate1;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> sourcececity1;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destinationity1;

                cout << endl << "\t\t\t\tEnter travel date ---> ";
                cin >> traveldate1;

                flightgraph.bookflight(sourcececity1, destinationity1, traveldate1);
                break;
            }

            case 4: 
            {
                
                int choice;

                cout << endl << endl << "\t\t\t\t1. Terminal Based Output "<< endl;
                cout << "\t\t\t\t2. Graphical Based Output "<< endl;
                cout << "\t\t\t\tEnter Your Choice ---> ";
                cin >> choice;

                if(choice==1)
                {
                string sourcececity2, destinationity2;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> sourcececity2;
                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destinationity2;

                flightgraph.findshortestroute(sourcececity2, destinationity2);
                }
                else if(choice==2)
                {
                    
                sf::RenderWindow window(sf::VideoMode(800, 600), "Shortest Route");
                string sourcececity2, destinationity2;
                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> sourcececity2;
                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destinationity2;

                flightgraph.findshortestroutes(sourcececity2, destinationity2,window);
                }
                else
                {
                cout << "\t\t\t\tInput Validation "<<endl;
                }
                break;
            }

            case 5: 
            {                
                int choice;
                cout << endl << endl << "\t\t\t\t1. Terminal Based Output "<< endl;
                cout << "\t\t\t\t2. Graphical Based Output "<< endl;
                cout << "\t\t\t\tEnter Your Choice ---> ";
                cin >> choice;

                if(choice==1)
                {
                string source3;
                string destination3;
                string preferredairline;
                string layovercity;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> source3;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destination3;

                cout << endl << "\t\t\t\tEnter preferred airline ---> ";
                cin >> preferredairline;

                cout << endl << "\t\t\t\tEnter preferred layover city ---> ";
                cin >> layovercity;

                flightgraph.searchflightswithpreferences(source3, destination3, preferredairline, layovercity);
                }
                else if(choice==2)
                {
                    
                sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Preference");
                 string source3;
                string destination3;
                string preferredairline;
                string layovercity;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> source3;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destination3;

                cout << endl << "\t\t\t\tEnter preferred airline ---> ";
                cin >> preferredairline;

                cout << endl << "\t\t\t\tEnter preferred layover city ---> ";
                cin >> layovercity;

                flightgraph.searchflightswithpreferencess(source3, destination3, preferredairline, layovercity,window);
                }
                
                else
                {
                cout << "\t\t\t\tInput Validation "<<endl;
                }
                break;
            }

            case 6: 
            {
                int choice;
                cout << endl << endl << "\t\t\t\t1. Terminal Based Output "<< endl;
                cout << "\t\t\t\t2. Graphical Based Output "<< endl;
                cout << "\t\t\t\tEnter Your Choice ---> ";

                cin >> choice;
                
                if(choice==1)
                {
                string source4;
                string destination4;
                string date4;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> source4;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destination4;

                flightgraph.searchflightswithlayovers(source4, destination4);  
            

                }
                else if(choice==2)
                {
                sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Layover");
                string source4;
                string destination4;
                string date4;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> source4;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destination4;

                flightgraph.searchflightswithlayoverss(source4, destination4,window);  
             
            }
            
                else
                {
                cout << endl << "\t\t\t\tInput Validation "<<endl;
                }
                break;
            }

            case 7:
            {
                string source5;
                string destination5;
                //string date5;

                cout << endl << "\t\t\t\tEnter source city ---> ";
                cin >> source5;

                cout << endl << "\t\t\t\tEnter destination city ---> ";
                cin >> destination5;

                //cout << "Enter Date ---> ";
                //cin >> date5;

                flightgraph.advanceroute(source5, destination5);
                break;

            }
            
            case 8:
            {
                string preferredAirline;
                cout << endl << "\t\t\t\tEnter Your Preferred Airline  ---> ";
                cin >> preferredAirline;
                flightgraph.generateSubgraphByAirline(preferredAirline);
                break;
            }

            case 9:
            {
                cout << endl << "\t\t\t\tExiting The Program Please Wait..." << endl;
                this_thread::sleep_for(chrono::seconds(2)); 
                break;
            }
            default:
            {
                cout << "\033[31m";
                cout << endl << "\t\t\t\tInvalid Choice, Please Try Again" << endl;
                cout << "\033[0m"; 
                break;
            }
        }

    } 
    while (choice != 9);  

}
