#ifndef TICKETMANAGER_HPP
#define TICKETMANAGER_HPP

#include "Constants.hpp"
#include <string>

class TicketManager {
private:
    char ticketCode[MAX][10];
    int seatAssigned[MAX];
    std::string passengerNames[MAX];
    std::string passengerPhones[MAX];
    int bookingCount;
public:
    void reset();
    bool isTicketExist(const char* newTicketCode);
    void addTicket(const char *newTicketCode, int seat, const std::string& name = "", const std::string& phone = "");
    void exportTicket(const char* code, const std::string& name, const std::string& phone,
                      const std::string& fCode, const std::string& dep, const std::string& dest,
                      const std::string& time, const std::string& seatStr, const std::string& seatClass);
    void printTicketInfo(const char* searchCode);
    void exportAllTickets(const std::string& filename);
    int getSeatByTicketCode(const char* code);
    bool removeTicket(const char* code);
};

#endif