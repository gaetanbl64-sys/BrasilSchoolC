#include <iostream>
#include <string>

//________________________________________________________
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
class Leon3Display : public DisplayInterface {
    private:
        // Pointeur volatile : empêche le compilateur d'optimiser/supprimer les accès mémoire
        volatile unsigned int *output = (volatile unsigned int *)0x80000a04; //vrb qui va changer cst pour envoyer des consignes aux diff output (aux diff led)
        volatile unsigned int *data = (volatile unsigned int *)0x80000a00; //dans quel endroit de la memoire envoyer les data recus
        volatile unsigned int *direction = (volatile unsigned int *)0x80000a08; //Définir le mode des broches
    public:
        void render(int seconde) override{
            // Enable all Outputs
            *direction = 0xffffffff;

            // Assign value to output registers escreve os secondes sur les LEDs
            *output = seconde;

            // Realiza a leitura dos valores indicados nos pinos de entrada (Switches e Buttons)
            std::cout << "Current value of gpio lines: 0x" << *data << std::endl;
        }
};