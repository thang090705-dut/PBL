#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP
#include <string>


#include "Flight.hpp"
#include "SeatManager.hpp"
#include "TicketManager.hpp"
#include "FileManager.hpp"

class SystemManager {
private:
    Flight flight;
    SeatManager seatManager;
    TicketManager ticketManager;
    FileManager fileManager;
public:
    void openFlight();
    void displaySeatMap();
    void bookingProcess();
    void checkTicket();
    void exportBookedTickets();
    void cancelTicketProcess();
    void closeFlight();
    void cancelAllTickets();
};

#endif