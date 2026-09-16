#include <iostream>
#include <string>
#include <thread>
#include <chrono>


class DisplayMulti{
    public:
        virtual ~DisplayMulti() = default;
        virtual void render(std::string) = 0;
};


//________________________________________________________
class DisplayPC : public DisplayMulti{
    public:  //En C++, si une classe ne possède aucun attribut (aucune donnée membre) à initialiser, 
        void render (std::string texte) override{ //le compilateur génère automatiquement un constructeur par défaut implicite (équivalent à ConsoleDisplay() {}).
            std::cout << texte << std::endl;
        }
};


//________________________________________________________
// class Leon3Display : public DisplayInterface {
//     private:
//         // Pointeur volatile : empêche le compilateur d'optimiser/supprimer les accès mémoire
//         volatile uint32_t* gpioDataReg;
//     public:
//         Leon3Display() {
//             gpioDataReg = reinterpret_cast<volatile uint32_t*>(LEON3_GPIO_BASE + GPIO_DATA_OFFSET);
//         }
//         void render(const ClockCalendar& cc) override {
//             // 1. Affichage binaire des secondes sur les 8 LEDs de la carte Atlys
//             uint32_t ledsData = static_cast<uint32_t>(cc.getSec());
//             *gpioDataReg = ledsData; // Écriture directe dans le registre matériel
//             // 2. Si un écran OLED/UART est configuré, on envoie les registres texte
//             // (Exemple : ecrire_oled_chaine(cc.getHour(), cc.getMin(), cc.getSec()));
//         }
// };