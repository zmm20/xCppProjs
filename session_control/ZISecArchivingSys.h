#pragma once

#include <string>

class ZISecArchivingSys
{
public:
    ZISecArchivingSys();
    ~ZISecArchivingSys();

    std::string login(const std::string& jsonData, cinatra::ContextContainer& ctx);
    std::string workOrdersSelect(const std::string& jsonData);
    std::string fileUploadBefore(const std::string& jsonData);
    std::string fileUploadEnd(const std::string& jsonData);
    std::string workOrderUpdate(const std::string& jsonData);
    
};

