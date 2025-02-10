#include <cstddef>
#include <cstdlib>
#include <string>

#include <utility>
#include <ostream>
#include <iostream>

#include <vector>
#include <cstdlib>

#include "../include/util.h"

class KVManager {
  public:
    KVManager() {
      std::cout << "call to 0 constructor\n";
      _hash = std::rand();
      this->_key = new std::string("");
      this->_value = new std::string("");
    }

    KVManager(const std::string& _key) {
      std::cout << "call to 1 constructor\n";
      _hash = std::rand();
      this->_key = new std::string(_key);
      this->_value = new std::string("");
    }

    KVManager(const std::string& _key, const std::string& _value) {
      std::cout << "call to 2 constructor\n";
      _hash = std::rand();
      this->_key = new std::string(_key);
      this->_value = new std::string(_value);
    }

    KVManager(KVManager&& _kv) {
      std::cout << "call to move constructor\n";
      _hash = std::rand();
      this->_key = _kv._key;
      this->_value = _kv._value;
      _kv._key = nullptr;
      _kv._value = nullptr;
    }

    KVManager& operator=(KVManager&& _kv) {
      std::cout << "call to move assign\n";
      if (this->_key == _kv._key && this->_value == _kv._value) {
        return *this;
      }
      if (this->_key) {
        delete this->_key;
      }
      if (this->_value) {
        delete this->_value;
      }

      this->_key = _kv._key;
      this->_value = _kv._value;

      _kv._key = nullptr;
      _kv._value = nullptr;

      return *this;
    }

    KVManager(const KVManager&) = delete;
    KVManager& operator=(const KVManager&) = delete;

    // __NO_COPY__(KVManager);

    ~KVManager() {
      std::cout << "call to " << _hash << " default destructor\n";
      if (this->_key){
        delete this->_key;
      }
      if (this->_value) {
        delete this->_value;
      }
    }

    friend std::ostream& operator<<(std::ostream& _os,const KVManager& _kv) {
      if (_kv._key && _kv._value) {
        _os << _kv._hash << "-{"<< *_kv._key << ":" << *_kv._value <<"}";
      } else {
        _os << _kv._hash << "-null";
      }
      return _os;
    }
    
    void SetValue(const std::string& _value) {
      *this->_value = _value;
    }
    const std::string& GetValue() const {
      return *this->_value;
    }

  private:
    std::string* _key;
    std::string* _value;
    int _hash;
};

int main() {
    KVManager kv1("Lang", "C++, Go, Java, Schema");
    std::cout << "$kv1 - "<< kv1 << "\n";

    auto kv2(std::move(kv1)); // move constructor
    std::cout << "$kv1 - "<< kv1 << "\n";
    std::cout << "$kv2 - "<< kv2 << "\n";

    auto kv3 = std::move(kv2); // move constructor
    std::cout << "$kv1 - "<< kv1 << "\n";
    std::cout << "$kv2 - "<< kv2 << "\n";
    std::cout << "$kv3 - "<< kv3 << "\n";

    kv1 = std::move(kv3); // move assign
    std::cout << "$kv1 - "<< kv1 << "\n";
    std::cout << "$kv2 - "<< kv2 << "\n";
    std::cout << "$kv3 - "<< kv3 << "\n";
    
    kv1.SetValue("LLVM, JVM, runtime0");
        std::cout << "$kv1 - "<< kv1 << "\n";
    std::cout << "$kv2 - "<< kv2 << "\n";
    std::cout << "$kv3 - "<< kv3 << "\n";

    return 0;
}