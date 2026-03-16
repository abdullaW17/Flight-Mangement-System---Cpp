void graph::searchflightswithlayovers(const string& src, const string& dest, const string& date) 
{
    int srcindex = getcityindex(src);
    int destindex = getcityindex(dest);

    if (srcindex == -1 || destindex == -1) 
    {
        cout << "Invalid City ---> " << src << " OR " << dest << endl;
        return;
    }

    LayoverQueue queue;  // Queue for layover management
    bool found = false;

    cout << "\nSearching for flights from " << src << " to " << dest << " on " << date << "...\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(15) << "Origin" << setw(15) << "Intermediate" << setw(15) << "Destination" 
         << setw(15) << "Departure" << setw(15) << "Arrival" << setw(15) << "Layover (hrs)" 
         << setw(15) << "Total Cost" << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n";

    // Enqueue all flights from the source city
    node* temp = a[srcindex].head;
    while (temp) 
    {
        if (temp->date == date && temp->destination != dest) 
        {
            queue.enqueue(Layover(temp->destination, temp->departuretime, temp->arrivaltime, temp->cost));
        }
        temp = temp->next;
    }

    // Process flights in the queue
    while (!queue.isEmpty()) 
    {
        Layover layoverFlight = queue.dequeue();
        int layoverCityIndex = getcityindex(layoverFlight.airline);

        if (layoverCityIndex == -1) 
        {
            continue;  // Skip if invalid city
        }

        node* connection = a[layoverCityIndex].head;
        while (connection) 
        {
            if (connection->destination == dest && connection->date == date) 
            {
                // Check valid layover (departure after previous arrival)
                int prevArrival = convertStringTimeToMinutes(layoverFlight.arrivalTime);
                int nextDeparture = convertStringTimeToMinutes(connection->departuretime);

                if (nextDeparture > prevArrival) 
                {
                    int layoverTime = (nextDeparture - prevArrival) / 60;  // Calculate layover in hours
                    int totalCost = layoverFlight.cost + connection->cost;

                    cout << left << setw(15) << src 
                         << setw(15) << layoverFlight.airline 
                         << setw(15) << dest 
                         << setw(15) << layoverFlight.departureTime 
                         << setw(15) << connection->arrivaltime 
                         << setw(15) << layoverTime 
                         << setw(15) << totalCost << endl;

                    found = true;
                }
            }
            connection = connection->next;
        }
    }

    if (!found) 
    {
        cout << "\nNo connecting flights found." << endl;
    }
}
