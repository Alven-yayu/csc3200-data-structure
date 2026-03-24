#include "student_string.h"

namespace student_std {

// 构造一个空字符串
string::string()
{
    strlen = 0;
    c_str[0] = '\0';
}

// 用C风格字符串构造
string::string(const char* str)
{
    strlen = 0;
    if (str != nullptr) {
        while (str[strlen] != '\0' && strlen < MAXLEN - 1) {
            c_str[strlen] = str[strlen];
            strlen++;
        }
    }
    c_str[strlen] = '\0';
}

// 拷贝构造函数
string::string(string const& other)
{
    strlen = other.strlen;
    for (int i = 0; i <= strlen; i++) {
        c_str[i] = other.c_str[i];
    }
}

// 析构函数
string::~string()
{
    // 使用固定数组，无需释放
}

// 获取字符串长度
int string::get_strlen() const
{
    return strlen;
}

// 获取C风格字符串
const char* string::get_c_str() const
{
    return c_str;
}

// 拼接另一个字符串
void string::strcat(string const& other)
{
    int i = 0;
    while (i < other.strlen && strlen + i < MAXLEN - 1) {
        c_str[strlen + i] = other.c_str[i];
        i++;
    }
    strlen += i;
    c_str[strlen] = '\0';
}

// 赋值操作符
string& string::operator=(string const& other)
{
    if (this != &other) {
        strlen = other.strlen;
        for (int i = 0; i <= strlen; i++) {
            c_str[i] = other.c_str[i];
        }
    }
    return *this;
}

// 拼接赋值操作符
string& string::operator+=(string const& other)
{
    strcat(other);
    return *this;
}

// 下标访问（可修改）
char& string::operator[](int i)
{
    return c_str[i];
}

// 下标访问（只读）
const char& string::operator[](int i) const
{
    return c_str[i];
}

// 转大写：a-z -> A-Z
void string::to_upper()
{
    for (int i = 0; i < strlen; i++) {
        if (c_str[i] >= 'a' && c_str[i] <= 'z') {
            c_str[i] = c_str[i] - 'a' + 'A';
        }
    }
}

// 转小写：A-Z -> a-z
void string::to_lower()
{
    for (int i = 0; i < strlen; i++) {
        if (c_str[i] >= 'A' && c_str[i] <= 'Z') {
            c_str[i] = c_str[i] - 'A' + 'a';
        }
    }
}

// 复制另一个字符串的内容
void string::strcopy(string const& other)
{
    strlen = other.strlen;
    for (int i = 0; i <= strlen; i++) {
        c_str[i] = other.c_str[i];
    }
}

// 判断是否相等（区分大小写）
bool string::equals(string const& other) const
{
    if (strlen != other.strlen) return false;
    for (int i = 0; i < strlen; i++) {
        if (c_str[i] != other.c_str[i]) return false;
    }
    return true;
}

// 判断是否相等（忽略大小写）
bool string::equals_ignore_case(string const& other) const
{
    if (strlen != other.strlen) return false;
    for (int i = 0; i < strlen; i++) {
        char a = c_str[i], b = other.c_str[i];
        if (a >= 'a' && a <= 'z') a -= 32;
        if (b >= 'a' && b <= 'z') b -= 32;
        if (a != b) return false;
    }
    return true;
}

// 去除首尾空格
void string::trim()
{
    int start = 0, end = strlen - 1;
    while (start <= end && c_str[start] == ' ') start++;
    while (end >= start && c_str[end] == ' ') end--;

    int new_len = end - start + 1;
    for (int i = 0; i < new_len; i++) {
        c_str[i] = c_str[start + i];
    }
    strlen = new_len;
    c_str[strlen] = '\0';
}

// 判断是否全是字母（a-z, A-Z）
bool string::is_alphabetic() const
{
    if (strlen == 0) return false;
    for (int i = 0; i < strlen; i++) {
        char c = c_str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return false;
        }
    }
    return true;
}

} // namespace student_std