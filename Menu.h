#ifndef MENU_H
#define MENU_H

void menu(int mode) {
    system("cls"); // Очистка экрана
    switch (mode)
    {
    case 1:
    {
        PrintFlightsList(Flights);
    }
    break;
    case 2:
    {
        ChangeFlightsItem(Flights);
    }
    break;
    case 3:
    {
        AddFlightItemToBegin(Flights);
    }
    break;
    case 4:
    {
        AddFlightItemToEnd(Flights);
    }
    break;
    case 5:
    {
        SaveListOfFlightsToTextFile("Flights.txt", Flights);
    }
    break;
    case 6:
    {
        Flights = ReadListOfFlightsFromTextFile("Flights.txt");
        PrintFlightsList(Flights);
    }
    break;
    case 7:
    {
        DeleteFlightsList(Flights);
    }
    break;
    }
}

#endif
