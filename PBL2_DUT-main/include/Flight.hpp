#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>
#include "Constants.hpp"

class Flight {
private:
    std::string FlightCode;
    std::string Departure;
    std::string Destination;
    std::string FlightTime;
    
public:
    void inputFlight();
    void displayFlightInfo() const;
    std::string getFlightCode() const;
    std::string getDeparture() const;
    std::string getDestination() const;
    std::string getFlightTime() const;
};

#endif