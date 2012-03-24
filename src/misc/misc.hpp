#ifndef MISC_H
#define MISC_H

#include <string>

class Misc
{
public:
    Misc();
    virtual ~Misc();

    static int string_to_int(const std::string& value);
    static std::string int_to_string(const int value);
    static bool is_possible_property_name(const std::string& value);
protected:
private:
};

#endif // MISC_H