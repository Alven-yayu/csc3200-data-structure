#ifndef STUDENT_STRING_H
#define STUDENT_STRING_H

#define MAXLEN 256

namespace student_std {

class string
{
public:
    string();
    string(const char* str);
    string(string const&);
    ~string();

    int get_strlen() const;
    const char* get_c_str() const;
    void strcat(string const&);
    string& operator=(string const&);
    string& operator+=(string const&);
    char& operator[](int);
    const char& operator[](int) const;

    void to_upper();
    void to_lower();
    void strcopy(string const&);           
    bool equals(string const&) const;
    bool equals_ignore_case(string const&) const;
    void trim();
    bool is_alphabetic() const;

private:
    char c_str[MAXLEN];
    int strlen;
};

} // namespace student_std

#endif