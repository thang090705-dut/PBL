#ifndef SEATMANAGER_HPP
#define SEATMANAGER_HPP

#include "Constants.hpp"

class SeatManager {
private:
    int seatNo[MAX];
    int seatStatus[MAX];
    char seatCodes[MAX][10];
    int totalSeats;
public:
    void settotalSeats(int total);
    void setSeats(int index, int no, int status);
    void setSeatCode(int index, const char* code);
    const char* getSeatCode(int index) const;
    int gettotalSeats() const;
    int getseatNo(int index) const;
    int getseatStatus(int index) const;
    void getAllBookedSeat(char (&result)[MAX][10], int &count);
    void displaySeats() const;
    int countEmptySeats();
    void findEmptySeats(int result[], int &count);
    bool assignSeats(int seat);
    void setTicketCodeForSeat(int seat, const char* code);
    void unassignSeat(int seatNum);
};

#endif