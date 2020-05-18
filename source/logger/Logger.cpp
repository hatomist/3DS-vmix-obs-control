#include "Logger.h"

Logger::Logger(std::string addr, int port) {
    if (!port)
    {
        disable();
        return;
    }

    SOC_buffer = (u32*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);
    if(SOC_buffer == nullptr) {
//        failExit("memalign: failed to allocate\n"); # shit happened
//        std::cout << "failed memalign";
    }
    u8 ret;
    if ((ret = socInit(SOC_buffer, SOC_BUFFERSIZE)) != 0) {
//        std::cout << "socInit: 0x%08X\n" << (unsigned int)ret;
    }

    debug_sock = socket (AF_INET, SOCK_STREAM, IPPROTO_IP);

    client.sin_family = AF_INET;
    inet_aton(addr.c_str(), &client.sin_addr);
    client.sin_port = htons(port);
    errno = 0;
    if (connect(debug_sock, (struct sockaddr *) &client, sizeof(client)) < 0)
//        std::cout << "Error connecting" << std::endl;
        return;
    atexit((void (*)())socExit);
}

void Logger::warning(const std::string& message)
{
    send_string(yell + message + endc);
}

void Logger::error(const std::string& message)
{
    send_string(red + message + endc);
}

void Logger::log(const std::string& message)
{
    send_string(message + endc);
}

void Logger::log(const std::string& module, const std::string& message)
{
    send_string(module_encase(module) + message + endc);
}

void Logger::ok(const std::string& message)
{
    send_string(green + message + endc);
}

void Logger::ok(const std::string& module, const std::string& message)
{
    send_string(module_encase(module) + green + message + endc);
}

void Logger::warning(const std::string &module, const std::string &message) {
    send_string(module_encase(module) + yell + message + endc);
}

void Logger::error(const std::string &module, const std::string &message) {
    send_string(red + module_encase(module) + message + endc);
}

void Logger::disable() {
    disabled = 1;
}
void Logger::enable() {
    disabled = 0;
}

std::string get_timestamp()
{
    time_t t = (osGetTime() / 1000 - 2208988800);  // 3ds time to unix time
    char t_str[10];
    strftime(t_str, 10, "%X", gmtime(&t));
    return std::string(t_str);
}
