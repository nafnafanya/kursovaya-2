#ifndef MENU_H
#define MENU_H

void menu(int mode) {
    system("cls"); // Очистка экрана
    FlightItem flight1;
    switch (mode)
    {
    case 1:
    {
        flight1.PrintFlightsList(Flights);
    }
    break;
    case 2:
    {
       flight1.ChangeFlightsItem(Flights);
    }
    break;
    case 3:
    {
        flight1.AddFlightItemToBegin(Flights);
    }
    break;
    case 4:
    {
        flight1.AddFlightItemToEnd(Flights);
    }
    break;
    case 5:
    {
        flight1.SaveListOfFlightsToTextFile("Flights.txt", Flights);
    }
    break;
    case 6:
    {
        Flights = flight1.ReadListOfFlightsFromTextFile("Flights.txt");
        flight1.PrintFlightsList(Flights);
    }
    break; 
    case 7:
    {
        flight1.DeleteFlightsList(Flights);
    }
    break;
    }
}

#endif
