#ifndef INC_3DSBUILDTEMPLATE_LOGGER_H
#define INC_3DSBUILDTEMPLATE_LOGGER_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <3ds.h>
#include <string>
#include <malloc.h>

#define SOC_ALIGN       0x1000
#define SOC_BUFFERSIZE  0x100000
//#define DEBUG_SERV_ADDR "192.168.1.108"
//#define DEBUG_SERV_PORT 8090

class Logger {
private:
    std::string green = "\033[92m";
    std::string blue = "\033[94m";
    std::string red = "\033[91m";
    std::string yell = "\033[93m";
    std::string bold = "\033[1m";
    std::string endc = "\033[0m";
    std::string purple = "\033[0m";
    u8 disabled = 0;
    u32 *SOC_buffer;
    s32 debug_sock = -1;
    struct sockaddr_in client;

    void send_string(const std::string& str)
    {
        if (!disabled)
            send(debug_sock, str.c_str(), str.length(), 0); // just shit, todo PImpl
    }
    static std::string module_encase(const std::string& module)
    {
        return "[" + module + "]: ";
    }

public:

    void warning(const std::string& message);
    void warning(const std::string& module, const std::string& message);
    void error(const std::string& message);
    void error(const std::string& module, const std::string& message);
    void log(const std::string& message);
    void log(const std::string& module, const std::string& message);
    void ok(const std::string& message);
    void ok(const std::string& module, const std::string& message);
    void disable();
    void enable();
    Logger(std::string addr, int port);
};

std::string get_timestamp();

#endif //INC_3DSBUILDTEMPLATE_LOGGER_H
