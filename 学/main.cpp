#include <iostream> // 包含输入输出库

int main() {
    const char*string = "Hello";
    for(int i = 0;i < 5;i++){
        const char c = string[i];
        std::cout<<c<<std::endl;
    }
}