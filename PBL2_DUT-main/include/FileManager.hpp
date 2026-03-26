#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "SeatManager.hpp"
#include "TicketManager.hpp"

class FileManager {
public:
    bool loadSeatMap(const std::string& path, SeatManager &sm, TicketManager &tm);
    bool saveSeatMap(const std::string& path, const SeatManager &sm);
    void printFileContent(const std::string& path);    
};

#endif

// file output : file khach hang (username), file ve, file cho ngoi
