#include "Flight.hpp"
#include <iostream>
#include <limits>
#include <iomanip> 
#include <sstream>  
#include <ctime>

using namespace std;

void Flight::inputFlight(){
    FlightCode = "PFIEV";
    Departure = "Da Nang";
    Destination = "Ho Chi Minh City";
    // time_t now = time(nullptr);
    // struct tm timeInfo = *localtime(&now);
    // ostringstream oss;
    // oss << put_time(&timeInfo, "%H:%M %d/%m/%Y");
    // FlightTime = oss.str();
    FlightTime = "19:00 09/07/2025";
}
void Flight::displayFlightInfo() const{
    cout << "Chuyến bay mang số hiệu: " << FlightCode << endl;
    cout << "Hành trình: " << Departure << " -> " << Destination << endl;
    cout << "Thời gian khởi hành: " << FlightTime << endl;
}
string Flight::getFlightCode() const { return FlightCode; }
string Flight::getDeparture() const { return Departure; }
string Flight::getDestination() const { return Destination; }
string Flight::getFlightTime() const { return FlightTime; }
