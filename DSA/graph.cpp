#include "graph.h"
#include <iostream>
#include<iomanip>
#include<fstream>
#include <SFML/Graphics.hpp>  // SFML graphics library
#include<math.h>
using namespace std;

node :: node(string dest, string air, string dt, string dep, string arr, double c) 
{
    destination = dest;
    airline = air;
    date = dt;
    departuretime = dep;
    arrivaltime = arr;
    cost = c;
    next = nullptr;
}

adjlist :: adjlist() 
{
    head = nullptr; 
}

void adjlist :: insert(string dest, string airline, string date, string dep, string arr, double cost) 
{
    node *newnode = new node(dest, airline, date, dep, arr, cost);
    newnode->next = head;
    head = newnode;
}

void adjlist::display(const string &src) const 
{
    if (head == nullptr) 
    {
        return;
    }

    node* temp = head;
    while (temp != nullptr) 
    {
        cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << temp->date << setw(20) << temp->departuretime << setw(20) << temp->arrivaltime << setw(20) << temp->cost << setw(20) << temp->airline << endl;
        temp = temp->next;
    }
}

graph :: graph() 
{
    citycount = 0;
}

void graph :: addcity(const string &city) 
{
    for (int i = 0; i < citycount; i++) 
    {
        if (citynames[i] == city) 
        {
            return;
        }
    }
    citynames[citycount++] = city;
}

int graph :: getcityindex(const string &city) const 
{
    for (int i = 0; i < citycount; i++) 
    {
        if (citynames[i] == city)
        {
            return i;
        }
    }
    return -1;
}

void graph :: insertedge(const string &src, const string &dest, const string &airline, const string &date, const string &dep, const string &arr, double cost) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);
    if (srcindex == -1 || destindex == -1) 
    {
        cout << endl << "Invalid City ---> " << src << " OR ---> " << dest << endl;
        return;
    }
    a[srcindex].insert(dest, airline, date, dep, arr, cost);
}

void graph :: displaygraph() const 
{
    for (int i = 0; i < citycount; i++) 
    {
        a[i].display(citynames[i]);
    }
}

void graph :: searchflights(const string &src, const string &dest, const string &date) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);
    if (srcindex == -1 || destindex == -1) 
    {
        cout << "\033[31m";   // red color 
        cout << endl << "\t\t\t\tInvalid City ---> " << src << " OR " << dest << endl;
        cout << "\033[0m"; 
        return;
    }

    node *temp = a[srcindex].head;
    bool found = false;

    cout << "\033[1;33m"; // Set text color to yellow
    cout << endl << "\t\t\t\tPlease Wait... Searching For Flights From " << src << " To " << dest << " On " << date  << endl;
    cout << "\033[0m"; 
    while (temp) 
    {
        if (temp->destination == dest && temp->date == date) 
        {
            found = true;
            cout << "\n\n\t\t\t\tCongratulations! Direct Flight Found. Flight Details Are Loading, Please Wait..." << endl << endl;
            this_thread::sleep_for(chrono::seconds(2));  
            cout << "\033[1;34m"; 
            cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
            cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
            cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
            cout << "\033[0m";  
            cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << temp->date<< setw(20) << temp->departuretime << setw(20) << temp->arrivaltime << setw(20) << temp->cost<< setw(20) << temp->airline << endl;
        }
        temp = temp->next;
    }

    if (!found) 
    {
        cout << "\033[31m";   // red color 
        cout << endl << "\t\t\t\tSorry, No Direct Flights Found. Searching For Connecting Flights...\n" << endl;
        cout << "\033[0m";  
        cout << endl << "\n\t\t\t\tConnecting Flights Are Given Below" << endl;
        cout << "\033[1;34m"; 
        cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
        cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
        cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
        cout << "\033[0m"; 

        temp = a[srcindex].head;
        while (temp) 
        {
            node *mid = a[getcityindex(temp->destination)].head;
            while (mid) {
                if (mid->destination == dest && temp->date == date && mid->date == date) 
                {
                    cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << dest << setw(20) << temp->date << setw(20) << (temp->cost + mid->cost) << setw(20) << temp->airline << setw(20) << mid->airline << endl;
                }
                mid = mid->next;
            }
            temp = temp->next;
        }
    }
}

int convertStringTimeToMinutes(const string &time) 
{
    size_t colon = time.find(':');
    if (colon == string::npos) return -1;
    int hours = stoi(time.substr(0, colon));
    int minutes = stoi(time.substr(colon + 1));
    return hours * 60 + minutes;
}

void graph :: bookflight(const string &src, const string &dest, const string &date) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);
    if (srcindex == -1 || destindex == -1) 
    {
        cout << "\033[31m";   // red color 
        cout << endl << "\t\t\t\tInvalid City ---> " << src << " OR ---> " << dest << endl;
        cout << "\033[0m"; 
        return;
    }

    ofstream file1("bookings.txt", ios::app);
    if (!file1) 
    {
        cout << "\033[31m";   // red color 
        cout << endl << "\t\t\t\tError In Open File Please Try Again" << endl;
        cout << "\033[0m"; 
        return;
    }

    node *temp = a[srcindex].head;
    bool found = false;

    cout << endl << "\t\t\t\tSearching For Flights From " << src << " To " << dest << " On " << date << "...\n";
    while (temp) 
    {
        if (temp->destination == dest && temp->date == date) 
        {
            found = true;
            cout << "\n\n\t\t\t\tCongratulations! Direct Flight Found. Flight Details Are Loading, Please Wait..." << endl << endl;
            this_thread::sleep_for(chrono::seconds(2)); 
            cout << "\033[1;34m"; 
            cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
            cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
            cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
            cout << "\033[0m"; 
            cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << temp->date << setw(20) << temp->departuretime << setw(20) << temp->arrivaltime << setw(20) << temp->cost << setw(20) << temp->airline << endl;


            cout << endl << "\t\t\t\tWould You Like To Book This Flight? Press 'Y' For (Yes) Or 'N' For (Not) ---> ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') 
            {
                file1 << "Direct Flight ";
                file1 << src << " -> " << dest << " | Date: " << date << " | Departure: " << temp->departuretime << " | Arrival: " << temp->arrivaltime << " | Cost: " << temp->cost << " | Airline: " << temp->airline << "\n";
                cout << "\033[1;33m"; // yellow color
                cout << endl << "Flight Booked Successfully " << endl;
                cout << "\033[0m";    // reset color 
            } 
            else 
            {
                cout << "\033[31m";   // red color 
                cout << endl << "\t\t\t\tFlight Not Booked" << endl;
                cout << "\033[0m"; 
            }
            file1.close();
            return;
        }
        temp = temp->next;
    }

    if (!found) 
    {
        cout << "\033[31m";   // red color 
        cout << endl << "\t\t\t\tSorry, No Direct Flights Found. Searching For Connecting Flights...\n" << endl;
        cout << "\033[0m";  
        cout << endl << "\n\t\t\t\tConnecting Flights Are Given Below" << endl;
        cout << "\033[1;34m"; 
        cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
        cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
        cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
        cout << "\033[0m"; 

        temp = a[srcindex].head;
        while (temp) 
        {
            node *mid = a[getcityindex(temp->destination)].head;
            while (mid) 
            {
                if (mid->destination == dest && temp->date == date && mid->date == date) 
                {
                    int arrivalTime = convertStringTimeToMinutes(temp->arrivaltime);
                    int departureTime = convertStringTimeToMinutes(mid->departuretime);
                    if (departureTime > arrivalTime) 
                    {
                        cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << dest << setw(20) << temp->date << setw(20) << (temp->cost + mid->cost) << setw(20) << temp->airline << setw(20) << mid->airline << endl;
                        cout << endl << "\t\t\t\tWould You Like To Book This Flight? Press 'Y' For (Yes) Or 'N' For (Not) ---> ";
                        char choice;
                        cin >> choice;
                        if (choice == 'y' || choice == 'Y') 
                        {
                            file1 << "Connecting Flight:\n";
                            file1 << src << " -> " << temp->destination << " -> " << dest << " | Date: " << date << " | Total Cost: " << (temp->cost + mid->cost) << " | Airline 1: " << temp->airline << " | Airline 2: " << mid->airline << endl;
                            cout << endl << "\t\t\t\tFlight Booked Successfully" << endl;
                            file1.close();
                            return;
                        }
                    }
                }
                mid = mid->next;
            }
            temp = temp->next;
        }
    }

    cout << endl << "\t\t\t\tNo Flights Available For Selected Route" << endl;
    file1.close();
}

int timeToMinutes(const string &time) 
{
    size_t colonPos = time.find(':'); 
    int hours = stoi(time.substr(0, colonPos)); 
    int minutes = stoi(time.substr(colonPos + 1)); 
    return hours * 60 + minutes; 
}

int calculateTimeDifference(const string &departureTime, const string &arrivalTime) 
{
    int depMinutes = timeToMinutes(departureTime);
    int arrMinutes = timeToMinutes(arrivalTime);

    if (arrMinutes < depMinutes) 
    {
        arrMinutes += 24 * 60;
    }

    return arrMinutes - depMinutes; 
}

const int infinity = 99999999;

void graph :: findshortestroute(const string& src, const string& dest) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);
    if (srcindex == -1 || destindex == -1) 
    {
        cout << "\033[31m";   // red color 
        cout << endl << "\t\t\t\tInvalid City ---> " << src << " OR " << dest << endl;
        cout << "\033[0m"; 
        return;
    }

    int minvalue[citycount];  
    for (int i = 0; i < citycount; i++) 
    {
        minvalue[i] = infinity;
    }
    minvalue[srcindex] = 0;

    bool visited[citycount] = {false};

    int previous[citycount];
    for (int i = 0; i < citycount; i++) 
    {
        previous[i] = -1;
    }

    int choice;

    cout << endl << endl;
    cout << "\t\t\t\t1. Cost" << endl;
    cout << "\t\t\t\t2. Time" << endl;
    cout << "\t\t\t\tChoose On What Basis YOu Want To Find Shortest Route ---> ";
    cin >> choice;

    for (int i = 0; i < citycount; i++) 
    {
        int mincity = -1;
        int minvalueTemp = infinity;

        for (int j = 0; j < citycount; j++) {
            if (!visited[j] && minvalue[j] < minvalueTemp) 
            {
                mincity = j;
                minvalueTemp = minvalue[j];
            }
        }

        if (mincity == -1) 
        {
            break;
        }

        visited[mincity] = true;

        node* temp = a[mincity].head;
        while (temp) {
            int neighborIndex = getcityindex(temp->destination);
            int newValue;
            if (choice == 1) 
            {
                newValue = minvalue[mincity] + temp->cost;
            } 
            else 
            { 
                newValue = minvalue[mincity] + calculateTimeDifference(temp->departuretime, temp->arrivaltime);
            }

            if (newValue < minvalue[neighborIndex]) 
            {
                minvalue[neighborIndex] = newValue;
                previous[neighborIndex] = mincity;
            }
            temp = temp->next;
        }
    }

    int current = destindex;
    if (minvalue[destindex] == infinity) 
    {
        cout << endl << "\t\t\t\tNo Path Found From " << src << " To " << dest << endl;
        return;
    }

    cout << endl << "\t\t\t\tShortest Route From " << src << " To " << dest << " Is ---> " ;
    string path = "";
    while (current != -1) 
    {
        path = citynames[current] + " -> " + path;
        current = previous[current];
    }
    path = path.substr(0, path.size() - 4);  

    cout << path << endl << endl;
    if (choice == 1) 
    {
        cout << "\033[1;33m"; // yellow color
        cout << "\t\t\t\tTotal Cost ---> " << minvalue[destindex] << endl;
        cout << "\033[0m"; 
    }
    else 
    {
        cout << "\033[1;33m"; // yellow color
        cout << "\t\t\t\tTotal Time (In Minutes) ---> " << minvalue[destindex] << endl;
        cout << "\033[0m"; 
    }

    current = destindex;
    while (current != srcindex) 
    {
        int prevIndex = previous[current];
        node* temp = a[prevIndex].head;
        while (temp)
        {
            if (getcityindex(temp->destination) == current) 
            {
                cout << "\033[1;34m"; 
                cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
                cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
                cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
                cout << "\033[0m"; 
                cout << left << setw(20) << citynames[prevIndex] << setw(20) << temp->destination << setw(20) << temp->date << setw(20) << temp->departuretime << setw(20) << temp->arrivaltime << setw(20) << temp->cost << setw(20) << temp->airline << endl;
                break;
            }
            temp = temp->next;
        }
        current = prevIndex;
    }
}

void graph::searchflightswithpreferences(const string& src, const string& dest, const string& preferredairline, const string& transitcity) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);
    
    if (srcindex == -1 || destindex == -1) 
    {
        cout << "\033[31m";
        cout << endl << "\t\t\t\tInvalid City ---> " << src << " OR " << dest << endl;
        cout << "\033[0m"; 
        return;
    }

    node* temp = a[srcindex].head;
    bool found = false;

    cout << endl << "\t\t\t\tPlease Wait... Searching For Flights From " << src << " To " << dest << " with Preferred Airline: " << preferredairline;

    if (!transitcity.empty()) 
    {
        cout << endl << endl << "\t\t\t\tAnd Transit City ---> " << transitcity;
    }

    cout << endl;

    while (temp) 
    {
        if (temp->destination == dest && temp->airline == preferredairline && (transitcity.empty() || temp->destination == transitcity)) 
        {
            found = true;
            cout << endl << "\t\t\t\tDirect Flight Found" << endl;
            cout << "\033[1;34m";        // blue
            cout << "┌---------------------------------------------------------------------------------------------------------------------------------┐" << endl;
            cout << left << setw(20) << " Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure Time" << setw(20) << "Arrival Time" << setw(20) << "Cost"  << setw(20) << "Airline" << endl; 
            cout << "└---------------------------------------------------------------------------------------------------------------------------------┘" << endl;
            cout << "\033[0m"; 
            cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << temp->departuretime << setw(20) << temp->arrivaltime << setw(20) << temp->cost << setw(20) << temp->airline << endl;
        }
        temp = temp->next;
    }

    if (!found) 
    {
        cout << "\033[31m";
        cout << endl << "\t\t\t\tSorry, No Direct Flights Found with Preferred Airline. Searching For Connecting Flights...\n" << endl;
        cout << "\033[0m"; 
        cout << "\n\t\t\t\tConnecting Flights with Preferred Airline Are Given Below" << endl;

        cout << "\033[1;34m";        // blue
        cout << "┌-------------------------------------------------------------------------------------------------------------------------------------┐" << endl;
        cout << left << setw(20) << "Origin" << setw(20) << "Intermediate" << setw(20) << "Destination" << setw(20) << "Cost" << setw(20) << "Airline 1" << setw(20) << "Airline 2" << endl;
        cout << "└-------------------------------------------------------------------------------------------------------------------------------------┘" << endl;
        cout << "\033[0m"; 

        temp = a[srcindex].head;
        while (temp) 
        {
            node* mid = a[getcityindex(temp->destination)].head;
            while (mid) 
            {
                if (mid->destination == dest && temp->airline == preferredairline && mid->airline == preferredairline) 
                {
                    if (transitcity.empty() || temp->destination == transitcity) 
                    {
                        cout << left << setw(20) << src << setw(20) << temp->destination << setw(20) << dest << setw(20) << (temp->cost + mid->cost) << setw(20) << temp->airline << setw(20) << mid->airline << endl;
                    }
                }
                mid = mid->next;
            }
            temp = temp->next;
        }
    }
}

void graph::searchflightswithlayovers(const string& src, const string& dest) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);

    if (srcindex == -1 || destindex == -1) 
    {
        cout << "vInvalid City ---> " << src << " OR " << dest << endl;
        return;
    }

    LayoverQueue queue; 
    bool found = false;

    cout << "\n\t\t\t\tSearching For Flights From " << src << " to " << dest << "...\n";
    cout << "\033[1;34m";        // blue
    cout << "┌---------------------------------------------------------------------------------------------------------------------------------------┐" << endl;
    cout << left << setw(20) << "Origin" << setw(20) << "Intermediate" << setw(20) << "Destination" << setw(20) << "Departure" << setw(20) << "Arrival" << setw(20) << "Layover (hrs)" << setw(20) << "Total Cost" << endl;
    cout << "└---------------------------------------------------------------------------------------------------------------------------------------┘" << endl;
    cout << "\033[0m"; 

    node* temp = a[srcindex].head;
    while (temp) 
    {
        if (temp->destination != dest) 
        {
            queue.enqueue(Layover(temp->destination, temp->departuretime, temp->arrivaltime, temp->cost));
        }
        temp = temp->next;
    }

    while (!queue.isEmpty()) 
    {
        Layover layoverFlight = queue.dequeue();
        int layoverCityIndex = getcityindex(layoverFlight.airline);  

        if (layoverCityIndex == -1) 
        {
            continue; 
        }

        node* connection = a[layoverCityIndex].head;  
        while (connection) 
        {
            if (connection->destination == dest) 
            {
                int prevArrival = convertStringTimeToMinutes(layoverFlight.arrivalTime); 
                int nextDeparture = convertStringTimeToMinutes(connection->departuretime);  

                if (nextDeparture > prevArrival) 
                {
                    int layoverTime = (nextDeparture - prevArrival) / 60; 
                    int totalCost = layoverFlight.cost + connection->cost; 

                    cout << left << setw(20) << src << setw(20) << layoverFlight.airline << setw(20) << dest << setw(20) << layoverFlight.departureTime << setw(20) << connection->arrivaltime << setw(20) << layoverTime << setw(20) << totalCost << endl;
                    found = true;
                }
            }
            connection = connection->next;
        }
    }

    if (!found) 
    {
        cout << "\033[31m";
        cout << "\n\t\t\t\tNo Connecting Flights Found." << endl;
        cout << "\033[0m"; 
    }
}



void graph::generateSubgraphByAirline(const string &preferredAirline)
{
    cout << "\t\t\t\tGenerating Subgraph For Airline: " << preferredAirline << endl;
    cout << "\t\t\t\tRelevant Routes " << endl << endl;
    cout << "\033[1;34m"; 
    cout << "┌-----------------------------------------------------------------------------------------------------------------------------------------┐" << endl;
    cout << left << setw(20) << "Origin" << setw(20) << "Destination" << setw(20) << "Date" << setw(20) << "Departure" << setw(20) << "Arrival" << setw(20) << "Cost" << setw(20) << "Airline" << endl;
    cout << "└-----------------------------------------------------------------------------------------------------------------------------------------┘" << endl;
    cout << "\033[0m";  

    for (int i = 0; i < citycount; i++) 
    {
        node* temp = a[i].head;
        while (temp) {
            if (temp->airline == preferredAirline) 
            {
                cout << left << setw(20) << citynames[i] << setw(20) << temp->destination << setw(20) << temp->date << setw(20) << temp->departuretime << setw(20) << temp->arrivaltime << setw(20) << temp->cost << setw(20) << temp->airline << endl;
            }
            temp = temp->next;
        }
    }
}

void graph :: advanceroute(const string& src, const string& dest) 
{
    int srcIndex = getcityindex(src);
    int destIndex = getcityindex(dest);

    if (srcIndex == -1 || destIndex == -1) 
    {
        cout << "\033[31m";
        cout << endl << "\t\t\t\tInvalid source or destination.\n";
        cout << "\033[0m"; 
        return;
    }

    cout << "\033[1;33m"; // yellow color
    cout << endl << "\t\t\t\tSearching for connecting flights from " << src << " to " << dest << "...\n" << endl;
    cout << "\033[0m"; 
    
    node* layoverFlight = a[srcIndex].head; 
    bool foundFlight = false;

    const int maxFlights = 10; 
    string flightPaths[maxFlights];
    double totalCosts[maxFlights];
    int flightCount = 0;

    while (layoverFlight != nullptr) 
    {
        if (layoverFlight->destination != dest) 
        {  
            node* secondLegFlight = a[getcityindex(layoverFlight->destination)].head;  
            while (secondLegFlight != nullptr) 
            {
                if (secondLegFlight->destination != dest) 
                {  
                    node* thirdLegFlight = a[getcityindex(secondLegFlight->destination)].head;
                    while (thirdLegFlight != nullptr) 
                    {
                        if (thirdLegFlight->destination == dest) 
                        {
                            bool isDuplicate = false;
                            for (int i = 0; i < flightCount; ++i) 
                            {
                                if (flightPaths[i].find(layoverFlight->destination + " -> " + secondLegFlight->destination) != string::npos) 
                                {
                                    isDuplicate = true;
                                    break;
                                }
                            }

                            if (!isDuplicate) 
                            {
                                foundFlight = true;
                                double totalCost = layoverFlight->cost + secondLegFlight->cost + thirdLegFlight->cost;
                                if (flightCount < maxFlights) 
                                {
                                    // Save the full path of the flight
                                    flightPaths[flightCount] = src + " -> " + layoverFlight->destination + " -> " + secondLegFlight->destination + " -> " + dest;
                                    totalCosts[flightCount] = totalCost;
                                    flightCount++;
                                }
                                cout << "\t\t\t\tFlight " << flightCount << ": " << src << " -> " << layoverFlight->destination 
                                     << " -> "<< secondLegFlight->destination << " -> " << dest << ", Total Cost: " << totalCost << endl;
                            }
                        }
                        thirdLegFlight = thirdLegFlight->next;
                    }
                }
                secondLegFlight = secondLegFlight->next;
            }
        }
        layoverFlight = layoverFlight->next;
    }

    if (!foundFlight) 
    {
        cout << "\033[31m";
        cout << "\t\t\t\tNo Connecting Flights With More Than One Layover Found From " << src << " To " << dest << ".\n";
        cout << "\033[0m";
        return;
    }

    cout << endl << "\t\t\t\tWould you like to select a specific connecting flight? (1-" << flightCount << ") or -1 to exit ---> ";
    int flightNumber;
    cin >> flightNumber;

    if (flightNumber == -1) 
    {
        cout << "\033[1;32m"; // green color for exit message
        cout << "\t\t\t\tExiting without selecting a flight. Returning to the main menu...\n";
        cout << "\033[0m";
        return;
    }

    if (flightNumber < 1 || flightNumber > flightCount) 
    {
        cout << "\033[0m"; 
        cout << "\t\t\t\tInvalid Selection. Showing All Connecting Flights Instead" << endl;
        cout << "\033[0m"; 
        for (int i = 0; i < flightCount; ++i) 
        {
            cout << "Flight " << (i + 1) << ": " << flightPaths[i] << ", Total Cost: " << totalCosts[i] << endl;
        }
    } 
    else 
    {
        cout << endl  << "\t\t\t\tYou Selected: " << flightPaths[flightNumber - 1] << ", Total Cost: " << totalCosts[flightNumber - 1] << endl;
    }
}


void graph::findshortestroutes(const string &src, const string &dest, sf::RenderWindow &window) {
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);
    
    if (srcindex == -1 || destindex == -1) {
        cout << endl << "Invalid City " << src << " OR " << dest << endl;
        return;
    }

    int mincost[citycount];
    for (int i = 0; i < citycount; i++) {
        mincost[i] = infinity;
    }
    mincost[srcindex] = 0;

    bool visited[citycount] = {false};
    int previous[citycount];
    for (int i = 0; i < citycount; i++) {
        previous[i] = -1;
    }

    // Store the positions of the cities for rendering
    vector<sf::Vector2f> cityPositions(citycount);

    // Set up the font for city names
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }

    // Main window event loop to keep the window open
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Manually close the window when requested
            }
        }

        // Clear the screen at the start of every frame
        window.clear(sf::Color::Black);

        // Draw cities and their initial state
        for (int i = 0; i < citycount; i++) {
            float angle = i * (2 * 3.14159f / citycount);
            float x = 400 + 250 * cos(angle);
            float y = 300 + 250 * sin(angle);
            cityPositions[i] = sf::Vector2f(x, y);

            // Highlight the source and destination cities in yellow
            sf::CircleShape cityNode(10);
            if (citynames[i] == src || citynames[i] == dest) {
                cityNode.setFillColor(sf::Color::Yellow); // Yellow for source and destination
            } else {
                cityNode.setFillColor(sf::Color::Green);  // Non-highlighted cities are green
            }
            cityNode.setPosition(x - 10, y - 10);
            window.draw(cityNode);

            // Draw city name
            sf::Text cityName;
            cityName.setFont(font);
            cityName.setString(citynames[i]);
            cityName.setCharacterSize(14);
            cityName.setFillColor(sf::Color::White);
            cityName.setPosition(x + 15, y - 10);
            window.draw(cityName);
        }

        // Dijkstra's Algorithm for finding the shortest path
        for (int i = 0; i < citycount; i++) {
            int mincity = -1;
            int mincostvalue = infinity;

            // Find the unvisited city with the smallest cost
            for (int j = 0; j < citycount; j++) {
                if (!visited[j] && mincost[j] < mincostvalue) {
                    mincity = j;
                    mincostvalue = mincost[j];
                }
            }

            if (mincity == -1) {
                break;  // No more cities to visit
            }

            visited[mincity] = true;

            // Change the node color to blue (evaluated)
            sf::CircleShape cityNode(10);
            cityNode.setFillColor(sf::Color::Blue);  // Set evaluated nodes to blue
            cityNode.setPosition(cityPositions[mincity].x - 10, cityPositions[mincity].y - 10);
            window.draw(cityNode);

            // Check the neighbors of the current city
            node* temp = a[mincity].head;
            while (temp) {
                int neighborIndex = getcityindex(temp->destination);
                int newCost = mincost[mincity] + temp->cost;
                if (newCost < mincost[neighborIndex]) {
                    mincost[neighborIndex] = newCost;
                    previous[neighborIndex] = mincity;
                }
                temp = temp->next;
            }

            // Display the intermediate result for this iteration
            window.display();
            sf::sleep(sf::milliseconds(100));  // Add delay to visualize step by step
        }

        // Retrieve and highlight the shortest path
        int current = destindex;
        if (mincost[destindex] == infinity) {
            cout << endl << "No Path Found From " << src << " To " << dest << endl;
            return;
        }

        // Output the shortest route and cost
        cout << endl << "Shortest Route From " << src << " To " << dest << " Is" << endl;
        string path = "";
        vector<int> pathNodes;
        while (current != -1) {
            pathNodes.push_back(current);  // Store the path in reverse order
            path = citynames[current] + " -> " + path;
            current = previous[current];
        }

        path = path.substr(0, path.size() - 4);  // Remove the trailing " -> "
        cout << path << endl;
        cout << "Total Cost: " << mincost[destindex] << endl;

        // Highlight the optimal path in yellow (use yellow color)
        for (int i = 0; i < pathNodes.size() - 1; i++) {
            int fromIndex = pathNodes[i];
            int toIndex = pathNodes[i + 1];

            sf::Vertex line[] = {
                sf::Vertex(cityPositions[fromIndex], sf::Color::Red),  // Use yellow for the optimal path
                sf::Vertex(cityPositions[toIndex], sf::Color::Red)     // Continue in yellow
            };
            window.draw(line, 2, sf::Lines);
        }

        // Display everything on the window
        window.display();

        // Optional sleep to slow down the final rendering
        sf::sleep(sf::milliseconds(1000));  // Pause before closing
    }
}

void graph::searchflightswithpreferencess(const string& src, const string& dest, const string& preferredairline, const string& transitcity, sf::RenderWindow &window) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);

    // Validate city indices
    if (srcindex == -1 || destindex == -1) 
    {
        cout << "Invalid City ---> " << src << " OR " << dest << endl;
        return;
    }

    node* temp = a[srcindex].head;
    bool found = false;

    // Display searching message
    cout << "Searching for flights from " << src << " to " << dest  
         << " with preferred airline: " << preferredairline;
    if (!transitcity.empty()) 
    {
        cout << " and transit city: " << transitcity;
    }
    cout << endl;

    // Store positions of cities for rendering
    vector<sf::Vector2f> cityPositions(citycount);
    
    // Setup font for city names
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error: Failed to load font!" << endl;
        return;
    }

    // Event loop for window persistence
    sf::Event event;
    bool windowOpen = true;
    while (windowOpen) 
    {
        // Handle events
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                windowOpen = false;  // Close the window when the user presses the close button
            }
        }

        // Clear the window and prepare for drawing
        window.clear(sf::Color::Black);

        // Draw all cities and their paths
        for (int i = 0; i < citycount; i++) {
            float angle = i * (2 * 3.14159f / citycount); // Calculate positions in a circular layout
            float x = 400 + 250 * cos(angle);
            float y = 300 + 250 * sin(angle);
            cityPositions[i] = sf::Vector2f(x, y);

            // Create a city circle shape
            sf::CircleShape cityNode(10);
            if (citynames[i] == src || citynames[i] == dest || citynames[i] == transitcity) {
                cityNode.setFillColor(sf::Color::Yellow); // Highlight selected cities
            } else {
                cityNode.setFillColor(sf::Color::Green);  // Other cities in green
            }
            cityNode.setPosition(x - 10, y - 10);  // Adjust position for center alignment
            window.draw(cityNode);

            // Create text label for the city
            sf::Text cityName;
            cityName.setFont(font);
            cityName.setString(citynames[i]);
            cityName.setCharacterSize(14);
            cityName.setFillColor(sf::Color::White);
            cityName.setPosition(x + 15, y - 10); // Position the text near the city
            window.draw(cityName);
        }

        // Search for direct flights with preferences
        temp = a[srcindex].head;
        while (temp) 
        {
            if (temp->destination == dest  && temp->airline == preferredairline && (transitcity.empty() || temp->destination == transitcity)) 
            {
                found = true;
                cout << "\nDirect Flight Found:" << endl;
                cout << "---------------------------------------\n";
                cout << left << setw(15) << "Origin" << setw(15) << "Destination" << setw(15) << "Date" << setw(15) << "Departure" 
                     << setw(15) << "Arrival" << setw(15) << "Cost" << setw(15) << "Airline" << endl;
                cout << "---------------------------------------\n";
                cout << left << setw(15) << src << setw(15) << temp->destination << setw(15) << temp->date << setw(15) 
                     << temp->departuretime << setw(15) << temp->arrivaltime << setw(15) << temp->cost << setw(15) 
                     << temp->airline << endl;

                // Highlight the direct path between cities
                int srcPos = getcityindex(src);
                int destPos = getcityindex(dest);
                sf::Vertex line[] = {
                    sf::Vertex(cityPositions[srcPos], sf::Color::Red),
                    sf::Vertex(cityPositions[destPos], sf::Color::Red)
                };
                window.draw(line, 2, sf::Lines);
            }
            temp = temp->next;
        }

        // If no direct flights are found, search for connecting flights
        if (!found) 
        {
            cout << "\nNo Direct Flights Found with Preferred Airline. Searching for Connecting Flights...\n";
            cout << "\nConnecting Flights are given below:" << endl;
            cout << "------------------------------------------------------------\n";
            cout << left << setw(15) << "Origin" << setw(15) << "Intermediate" << setw(15) << "Destination" << setw(15) 
                 << "Date" << setw(15) << "Cost" << setw(15) << "Airline 1" << setw(15) << "Airline 2" << endl;
            cout << "------------------------------------------------------------\n";

            // Search for connecting flights: source -> transit -> destination
            temp = a[srcindex].head;
            while (temp) 
            {
                node* mid = a[getcityindex(temp->destination)].head;
                while (mid) 
                {
                    if (mid->destination == dest && 
                        temp->airline == preferredairline && mid->airline == preferredairline) 
                    {
                        if (transitcity.empty() || temp->destination == transitcity) 
                        {
                            cout << left << setw(15) << src << setw(15) << temp->destination << setw(15) << dest << setw(15) 
                                 << temp->date << setw(15) << (temp->cost + mid->cost) << setw(15) << temp->airline << setw(15) 
                                 << mid->airline << endl;

                            // Draw connecting paths (source -> transit -> destination)
                            int srcPos = getcityindex(src);
                            int transitPos = getcityindex(temp->destination);
                            int destPos = getcityindex(dest);

                            // First leg of the journey (source -> transit)
                            sf::Vertex line1[] = {
                                sf::Vertex(cityPositions[srcPos], sf::Color::Red),
                                sf::Vertex(cityPositions[transitPos], sf::Color::Red)
                            };
                            window.draw(line1, 2, sf::Lines);

                            // Second leg of the journey (transit -> destination)
                            sf::Vertex line2[] = {
                                sf::Vertex(cityPositions[transitPos], sf::Color::Red),
                                sf::Vertex(cityPositions[destPos], sf::Color::Red)
                            };
                            window.draw(line2, 2, sf::Lines);
                        }
                    }
                    mid = mid->next;
                }
                temp = temp->next;
            }
        }

        // Display everything on the window after drawing all cities and paths
        window.display();
    }
}

void graph::searchflightswithlayoverss(const string &src, const string &dest, sf::RenderWindow &window) {
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);

    if (srcindex == -1 || destindex == -1) {
        cout << "Invalid City ---> " << src << " OR " << dest << endl;
        return;
    }

    LayoverQueue queue;
    bool found = false;

    // SFML setup
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }

    vector<sf::Vector2f> cityPositions(citycount);
    vector<sf::Text> cityLabels;
    vector<sf::VertexArray> flightLines;

    // Calculate positions for cities dynamically in a circular layout
    for (int i = 0; i < citycount; i++) {
        float angle = i * (2 * 3.14159f / citycount);
        float x = 400 + 250 * cos(angle);
        float y = 300 + 250 * sin(angle);
        cityPositions[i] = sf::Vector2f(x, y);

        // City name labels
        sf::Text label;
        label.setFont(font);
        label.setString(citynames[i]);
        label.setCharacterSize(14);
        label.setFillColor(sf::Color::White);
        label.setPosition(x + 15, y - 10);
        cityLabels.push_back(label);
    }

    // Enqueue initial flights
    node *temp = a[srcindex].head;
    while (temp) {
        if (temp->destination != dest) {
            queue.enqueue(Layover(temp->destination, temp->departuretime, temp->arrivaltime, temp->cost));
        }
        temp = temp->next;
    }

    // Process flights and find layovers
    while (!queue.isEmpty()) {
        Layover layoverFlight = queue.dequeue();
        int layoverCityIndex = getcityindex(layoverFlight.airline);

        if (layoverCityIndex == -1) continue;

        node *connection = a[layoverCityIndex].head;
        while (connection) {
            if (connection->destination == dest) {
                int prevArrival = convertStringTimeToMinutes(layoverFlight.arrivalTime);
                int nextDeparture = convertStringTimeToMinutes(connection->departuretime);

                if (nextDeparture > prevArrival) {
                    found = true;

                    // Add a visual connection (line) between source and layover
                    sf::VertexArray line1(sf::Lines, 2);
                    line1[0].position = cityPositions[srcindex];
                    line1[0].color = sf::Color::Red;
                    line1[1].position = cityPositions[layoverCityIndex];
                    line1[1].color = sf::Color::Red;
                    flightLines.push_back(line1);

                    // Add a visual connection (line) between layover and destination
                    sf::VertexArray line2(sf::Lines, 2);
                    line2[0].position = cityPositions[layoverCityIndex];
                    line2[0].color = sf::Color::Red;
                    line2[1].position = cityPositions[destindex];
                    line2[1].color = sf::Color::Red;
                    flightLines.push_back(line2);

                    cout << left << setw(15) << src
                         << setw(15) << layoverFlight.airline
                         << setw(15) << dest
                         << setw(15) << layoverFlight.departureTime
                         << setw(15) << connection->arrivaltime
                         << setw(15) << (nextDeparture - prevArrival) / 60
                         << setw(15) << layoverFlight.cost + connection->cost << endl;
                }
            }
            connection = connection->next;
        }
    }

    if (!found) {
        cout << "No connecting flights found." << endl;
    }

    // SFML main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Draw cities as nodes
        for (int i = 0; i < citycount; i++) {
            sf::CircleShape cityNode(10);
            cityNode.setFillColor((citynames[i] == src || citynames[i] == dest ) ? sf::Color::Yellow : sf::Color::Green);
            cityNode.setPosition(cityPositions[i].x - 10, cityPositions[i].y - 10);
            window.draw(cityNode);
        }

        // Draw city labels
        for (const auto &label : cityLabels) {
            window.draw(label);
        }

        // Draw flight lines
        for (const auto &line : flightLines) {
            window.draw(line);
        }

        window.display();
    }
}

void graph::searchflightss(const string &src, const string &dest, const string &date, sf::RenderWindow &window) {
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);

    if (srcindex == -1 || destindex == -1) {
        cout << "Invalid City: " << src << " or " << dest << endl;
        return;
    }

    node *temp = a[srcindex].head;
    bool foundDirect = false;
    bool foundConnecting = false;

    cout << "\nSearching for flights from " << src << " to " << dest << " on " << date << "...\n";

    // Load font once for city labels
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Failed to load font!" << endl;
        return;
    }

    // Main SFML rendering loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear(sf::Color::Black);  // Set background color to black

        // Draw all cities as nodes
        vector<sf::Vector2f> cityPositions(citycount); // Store positions for all cities
        for (int i = 0; i < citycount; i++) {
            float angle = i * (2 * 3.14159f / citycount);
            float x = 400 + 250 * cos(angle);
            float y = 300 + 250 * sin(angle);

            cityPositions[i] = sf::Vector2f(x, y); // Save position for lines

            sf::CircleShape cityNode(10);
            // Highlight source and destination cities in yellow
            if (citynames[i] == src || citynames[i] == dest) {
                cityNode.setFillColor(sf::Color::Yellow);  // Set highlighted city color to yellow
            } else {
                cityNode.setFillColor(sf::Color::Green);  // Set other cities to green
            }
            cityNode.setPosition(x - 10, y - 10);
            window.draw(cityNode);

            // Draw city name
            sf::Text cityName;
            cityName.setFont(font);
            cityName.setString(citynames[i]); // Assuming citynames[] holds city names
            cityName.setCharacterSize(14);
            cityName.setFillColor(sf::Color::White);  // Set text color to white
            cityName.setPosition(x + 15, y - 10);
            window.draw(cityName);
        }

        // Check for direct flights
        temp = a[srcindex].head; // Reset temp
        while (temp) {
            if (temp->destination == dest && temp->date == date) {
                foundDirect = true;

                // Draw line for direct flight (red)
                sf::Vertex line[] = {
                    sf::Vertex(cityPositions[srcindex], sf::Color::Red),  // Start point in red
                    sf::Vertex(cityPositions[destindex], sf::Color::Red) // End point in red
                };
                window.draw(line, 2, sf::Lines);

                cout << "Direct Flight Found: " << src << " to " << dest << " on " << date << endl;
                cout << "Departure: " << temp->departuretime << ", Arrival: " << temp->arrivaltime
                     << ", Cost: " << temp->cost << ", Airline: " << temp->airline << endl;
            }
            temp = temp->next;
        }

        // Check for connecting flights if no direct flight is found
        if (!foundDirect) {
            temp = a[srcindex].head; // Reset temp for connecting flights
            while (temp) {
                int midIndex = getcityindex(temp->destination);
                node *mid = a[midIndex].head;

                while (mid) {
                    if (mid->destination == dest && temp->date == date && mid->date == date) {
                        foundConnecting = true;

                        // Draw lines for connecting flights (red)
                        sf::Vertex line1[] = {
                            sf::Vertex(cityPositions[srcindex], sf::Color::Red),    // Start point in red
                            sf::Vertex(cityPositions[midIndex], sf::Color::Red)     // Midpoint in red
                        };
                        sf::Vertex line2[] = {
                            sf::Vertex(cityPositions[midIndex], sf::Color::Red),    // Midpoint in red
                            sf::Vertex(cityPositions[destindex], sf::Color::Red)    // End point in red
                        };
                        window.draw(line1, 2, sf::Lines);
                        window.draw(line2, 2, sf::Lines);

                        cout << "Connecting Flight Found: " << src << " to " << temp->destination
                             << " to " << dest << " on " << date << endl;
                        cout << "Total Cost: " << temp->cost + mid->cost << endl;
                        cout << "Airlines: " << temp->airline << ", " << mid->airline << endl;
                    }
                    mid = mid->next;
                }
                temp = temp->next;
            }
        }

        // Display "No Flights Found" if neither direct nor connecting flights are available
        if (!foundDirect && !foundConnecting) {
            cout << "No flights found for the given route and date.\n";
        }

        window.display();  // Display the window content
    }
}

void graph::displaygraphSFML() const 
{
    // Initialize window outside the loop
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Routes");

    // Load font once before the loop
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font!" << endl;
        return;
    }

    // Example of source and destination city names (you can pass these or set them as needed)
    string src = "New York";  // Example source city
    string dest = "Los Angeles";  // Example destination city

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // For each city, draw a circle with more dynamic positioning
        for (int i = 0; i < citycount; i++) {
            // Dynamically adjust city position (circular layout)
            float angle = i * (2 * 3.14159f / citycount);  // Equal angular distance
            float x = 400 + 250 * cos(angle);  // 400 is the center, 250 is the radius
            float y = 300 + 250 * sin(angle);

            // Check if the current city is the source or destination
            sf::Color cityColor = sf::Color::Yellow;  // Default city color
            if (citynames[i] == src || citynames[i] == dest) {
                cityColor = sf::Color::Yellow;  // Highlight source and destination cities in yellow
            }

            // Debug output to check position of cities
            cout << "City " << citynames[i] << " Position: (" << x << ", " << y << ")" << endl;

            sf::CircleShape cityShape(12);  // radius of 12
            cityShape.setFillColor(cityColor);  // Use dynamic color based on condition
            cityShape.setPosition(x - 10, y - 10);  // Position based on center
            window.draw(cityShape);

            // Render city name
            sf::Text cityText(citynames[i], font, 14);
            cityText.setFillColor(sf::Color::White);
            cityText.setPosition(x - 10, y + 10);  // Position below the circle
            window.draw(cityText);
        }

        // Draw connections between cities (edges in the graph)
        for (int i = 0; i < citycount; i++) {
            node* temp = a[i].head;
            while (temp != nullptr) {
                int destIndex = getcityindex(temp->destination);
                if (destIndex != -1) {
                    // Draw line between cities (dynamically using calculated positions)
                    float x1 = 400 + 250 * cos(i * (2 * 3.14159f / citycount));
                    float y1 = 300 + 250 * sin(i * (2 * 3.14159f / citycount));
                    float x2 = 400 + 250 * cos(destIndex * (2 * 3.14159f / citycount));
                    float y2 = 300 + 250 * sin(destIndex * (2 * 3.14159f / citycount));

                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Red)
                    };
                    window.draw(line, 2, sf::Lines);
                }
                temp = temp->next;
            }
        }

        window.display();
    }
}
