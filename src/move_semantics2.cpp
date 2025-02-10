#include <utility>
#include <vector>


void rref_vector(std::vector<int> && v){
    v.emplace_back(10);
}

void value_vector(std::vector<int> v) {
    v.emplace_back(10);
}

int main() {
    std::vector<int> v = {1,2,3};
    value_vector(v); // 值拷贝(深拷贝)
    value_vector(std::move(v)); // 移动赋值,函数结束后v没了(v移动到value_vector栈空间然后被析构)

    std::vector<int> v2 = {1,2,3};
    // rref_vector(v2); // 编译错误,把左值绑定到右值上
    rref_vector(std::move(v2)); // 传递引用,函数结束后v2仍然存在

    return 0;
}