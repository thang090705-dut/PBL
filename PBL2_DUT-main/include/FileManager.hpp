#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "SeatManager.hpp"
#include "TicketManager.hpp"

class FileManager {
public:
    bool loadTicketsData(const std::string& path, TicketManager &tm);
    bool loadSeatMap(const std::string& path, SeatManager &sm, TicketManager &tm);
    bool saveSeatMap(const std::string& path, const SeatManager &sm);
    void printFileContent(const std::string& path);    
};

#endif
