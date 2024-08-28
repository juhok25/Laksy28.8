#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <string>


template <typename T>
class Log_Ptr {
private:
    T* ptr;  
    std::string logFile;

    void log(const std::string& message) const 
    {
        std::ofstream logStream(logFile, std::ios_base::app); 
        if (logStream.is_open()) {
            std::time_t now = std::time(nullptr);
            struct tm timeinfo;

            
            localtime_s(&timeinfo, &now);

            char buf[100];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
            logStream << "[" << buf << "] " << message << " " << ptr << std::endl;
        }
        else {
            std::cerr << "Unable to open log file!" << std::endl;
        }
    }

public:
    // konstruiktori
    Log_Ptr(T* p, const std::string& logFileName = "log_ptr.txt") : ptr(p), logFile(logFileName) 
    {
        log("Omistajuus siirretty");
    }

    // destruktori
    ~Log_Ptr() 
    {
        if (ptr) {
            log("Olio tuhottu");
            delete ptr;
        }
    }


    // poistetaan kopiointioperaattori
    Log_Ptr(const Log_Ptr&) = delete;
    Log_Ptr& operator=(const Log_Ptr&) = delete;

    // siirto operaattori
    Log_Ptr(Log_Ptr&& other) noexcept : ptr(other.ptr), logFile(std::move(other.logFile)) {
        other.ptr = nullptr;
        log("Omistajuus siirretty (siirto)");
    }

    Log_Ptr& operator=(Log_Ptr&& other) noexcept 
    {
        if (this != &other) 
        {
            if (ptr) {
                log("Olio tuhottu (siirto)");
                delete ptr;
            }
            ptr = other.ptr;
            logFile = std::move(other.logFile);
            other.ptr = nullptr;
            log("Omistajuus siirretty (siirto)");
        }
        return *this;
    }

    // p‰‰sy hallittun olioon

    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }
};


int main() {
    {
        Log_Ptr<int> logPtr1(new int(42)); // omistajuus siirretty
        *logPtr1 = 100; // k‰ytet‰‰n logptr1:ss‰ hallitua olioa

    } // logptr1 menee pois scopesta ja tuhoutuu

    return 0;
}