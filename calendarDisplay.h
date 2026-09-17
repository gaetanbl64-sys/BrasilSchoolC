#include <iostream>
#include <cstdint>

template <typename T>
class DisplayMulti {
public:
    virtual ~DisplayMulti() = default;
    virtual void render(T data) = 0;
};

class DisplayPC : public DisplayMulti<const char*> {
public:
    void render(const char* texte) override {
        std::cout << texte << std::endl;
    }
};

class DisplayLEON : public DisplayMulti<int> {
private:
    // Adresses physiques des registres GPIO en constexpr
    static constexpr std::uintptr_t ADDR_DATA      = 0x80000a00;
    static constexpr std::uintptr_t ADDR_OUTPUT    = 0x80000a04;
    static constexpr std::uintptr_t ADDR_DIRECTION = 0x80000a08;

    // Conversion en pointeurs MMIO volatiles
    volatile unsigned int* const data      = reinterpret_cast<volatile unsigned int*>(ADDR_DATA);
    volatile unsigned int* const output    = reinterpret_cast<volatile unsigned int*>(ADDR_OUTPUT);
    volatile unsigned int* const direction = reinterpret_cast<volatile unsigned int*>(ADDR_DIRECTION);

public:
    void render(int seconde) override {
        *direction = 0xFFFFFFFF;
        *output = seconde;
        std::cout << "Current value of gpio lines: 0x" 
                  << std::hex << *data << std::dec << std::endl;
    }
};