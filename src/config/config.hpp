#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

class Config
{
public:
    std::string host;
    std::string port;

    std::size_t number_of_threads;
    bool is_append_log_enabled;

    std::string dump_file_name;
private:
    Config();
    Config(const Config&);
    void operator =(const Config&);
    virtual ~Config();
public:
    static Config& getInstance();
    void set(const std::string& name, const std::string& value);
};

#endif /* CONFIG_H_ */
