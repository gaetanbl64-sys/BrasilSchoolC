//Implementação de calendário com data e hora, usando como base os exemplos de herança múltipla discutidos na aula. O programa deverá 
//ficar em laço infinito, atualizando a data e hora.
//Implémentation d'un calendrier avec date et heure, en s'appuyant sur les exemples d'héritage multiple abordés en cours. Le programme doit 
//rester dans une boucle infinie, en mettant à jour la date et l'heure.

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "calendarDisplay.h"

static constexpr int NBR_DAY_PER_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //constexpr : Indique au compilateur de stocker cette valeur directement à la compilation

class Clock{ //namespace serait utile pour creer une fonction bissextile et override l'operateur == potentiellement meme 2 fois si on créait 2 namespaces
    private:  
        int h; int m; int s; //ou? struct ClockTime { int hr; int min; int sec;};
    public:
        Clock(int _hour, int _min, int _sec): h(_hour), m(_min), s(_sec) {}; //pas de void devant le constructeur   //pas self.hour = _hour mais hour(_hour)
        int hour() const{ return h;}
        int min() const{ return m;}
        int sec() const{ return s;}
        bool advanceH(); //void advance(){}; est faux
        std::string getTime() const{
            return ((h < 10 ? "0" : "") + std::to_string(h) + ":" + 
                    (m < 10 ? "0" : "") + std::to_string(m) + ":" + 
                    (s < 10 ? "0" : "") + std::to_string(s) ); 
            //ou? ostream& operator<<(ostream& os, ClockTime t) { os << t.hr << ":" << t.min << ":" << t.sec; return os;} 
            //qui permet d utiliser std::cout << "Heure actuelle : " << now;
        }
};

bool Clock::advanceH(){
    s += 1;
    if (s==60){ m += 1, s = 0;}
    if (m==60){ h += 1, m = 0;}
    if (h==24){ h = 0; return false;}
    return true;
}


//________________________________________________________
class Calendar{
    private:
        int d; int m; int y;
    public:
        Calendar(int _day, int _month, int _year): d(_day), m(_month), y(_year) {};
        int day() const{ return d;}
        int month() const{ return m;}
        int year() const{ return y;}
        void advanceD();
        std::string getDay() const{
            return((d < 10 ? "0" : "") + std::to_string(d) + "/" + 
                   (m < 10 ? "0" : "") + std::to_string(m) + "/" + 
                   (y < 10 ? "0" : "") + std::to_string(y) );
        };
};

void Calendar::advanceD(){
    d += 1;
    if (d==(NBR_DAY_PER_MONTH[m-1]+1)){ m += 1, d = 1;}
    if (m==13){ y += 1, m = 1;}
}


//________________________________________________________
class ClockCalendar: public Clock, public Calendar{ //sans "public" getTime et getDay sont inacessibles
    public:
        //Calendar(Hour& _hour, Day& _day);
        ClockCalendar(int h, int m, int s, int d, int mo, int y): Clock(h, m, s), Calendar(d, mo, y) {}
        std::string getCalendar() const{
            return(getTime() + " " + getDay());
        }
        bool advance() {
            if (!advanceH()) {
                advanceD();
                return true; // Le jour vient de changer !
            }
            return false;
        }
        bool operator==(Calendar& theDay) const{
            return(day()==theDay.day() && 
                   month()==theDay.month() && 
                   year()==theDay.year()); //ici d==theDay.day() est impossible, il faudrait passer d en protected
        }
};


//________________________________________________________
int main(){
    //Hour heureJ(18, 4, 5); //Day jourJ(8, 9, 2026); //Calendar now(heureJ, jourJ); // Le '&' ici est l'opérateur "Adresse-de". // '&heureJ' produit un POINTEUR (Hour*), pas une référence."""
    ClockCalendar now(23, 59, 56, 31, 1, 2026);
    DisplayPC display;
    while (1){
        if (now.advance()) {
            display.render(now.getDay());
        }
        display.render(now.getTime());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
};

