#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <sstream>

using namespace std;

enum gender {unidentified, male, female};

class foititis{
    private:
        char* AM;
        string onoma;
        gender fylo;
        unsigned int semester;
        vector<string> mathimata;
    public:
        foititis(string AM, string onoma){               //κατασκευαστες
            if(AM.length() > 8){
                cout << "ERROR: Ο ΑΜ πρεπει να ειναι μεχρι 8 χαρακτηρες";
                return;
            }
            this->AM = new char[9];
            for(int i=0; i<9; i++){
                this->AM[i] = AM[i];
            }
            this->onoma = onoma;
            this->fylo = unidentified;
            semester = 1;
        }
        foititis(void){
            AM = new char[9];
            AM[0] = '\0';
            onoma = "noName";
            fylo = unidentified;
            semester = 0;
        }
        foititis(const foititis &other){
            this->AM = new char[9];
            for(int i=0; i<9; i++){
                this->AM[i] = other.AM[i];
            }
            this->fylo = other.fylo;
            this->onoma = other.onoma;
            this->semester = other.semester;
            this->mathimata = other.mathimata;
        }
        foititis(string AM, string onoma, gender fylo, unsigned int semester, vector<string>mathimata){
            if(AM.length() > 8){
                cout << "ERROR: Ο ΑΜ πρεπει να ειναι μεχρι 8 χαρακτηρες";
                return;
            }
            this->AM = new char[9];
            for(int i=0; i<9; i++){
                this->AM[i] = AM[i];
            }
            this->onoma = onoma;
            this->fylo = fylo;
            this->semester = semester;
            this->mathimata = mathimata;
        }

        string getAM(void){                     //getters
            return AM;
        }
        string getOnoma(void){
            return onoma;
        }
        string getFylo(void){
            switch(fylo){
                case male: 
                    return "Άνδρας"; break;
                case female: 
                    return "Γυναίκα"; break;
                case unidentified: 
                    return "Μη ορισμένο"; break;
                default: 
                    return "Μη ορισμένο"; 
            }
        }
        unsigned int getSemester(void){
            return semester;
        }
        vector<string> &getMathimata(void){
            return mathimata;
        }

        int setAM(string AM){               //setters
            if(AM.length() != 8){
                cout << "Error, Το μεγεθος του AM δεν ειναι 8 χαρακτηρες";
                return 0;
            }
            delete[] this->AM;
            this->AM = new char[9];
            for(int i=0; i<8; i++){
                this->AM[i] = AM[i];
            }
            this->AM[8] = '\0';
            return 1;
        }
        void setOnoma(string onoma){
            this->onoma = onoma;
        }
        void setFylo(gender fylo){
            this->fylo = fylo;
        }
        void setFylo(string fylo){
            if (fylo == "Άνδρας" || fylo == "Ανδρας" || fylo == "ανδρας" || fylo == "άνδρας") {
                this->fylo = male;
            } else if (fylo == "Γυναίκα" || fylo == "Γυναικα" || fylo == "γυναίκα" || fylo == "γυναικα") {
                this->fylo = female;
            } else {
                this->fylo = unidentified;
            }
        }
        void setSemester(unsigned int semester){
            this->semester = semester;
        }
        void setSemester(string semester){
            if (!semester.empty()) {
                this->semester = stoi(semester);
            }
        }
        void setMathimata(vector<string> math){
            mathimata = math;
        }
        
        void printMathimata(){
            short int i = 0;
            for(string math : mathimata){
                cout << i + 1 << '.' << math << ' ';
                i++;
            }
        }
        void printAll(void){
            cout << AM << "   ";
            cout << onoma << " (" << onoma.length() << ")   ";    //στα ελληνικα εμφαζινει μεγεθος μεγαλυτερο του πληθους των χαρακτηρων, αλλα παραμενει το μεγεθος του πινακα.
            cout << getFylo() << "   ";
            cout << semester << "ο εξάμηνο" << "   \n";
            printMathimata();
        }

        foititis& operator++(void){
            semester = semester + 1;
            return *this;
        }
        foititis& operator+=(int n){
            semester = semester + n;
            return *this;
        }
        foititis& operator-=(int n){
            semester = semester - n;
            return *this;
        }
        foititis& operator-(void){
            if(fylo == male){
                fylo = female;
            }else if(fylo == female){
                fylo = male;
            }else{
                cout << "δεν εχει προσδιοριστεί φύλο";
            }
            return *this;
        }
        foititis& operator=(const foititis& other){
            if(this != &other){
                delete[] AM;
        
                AM = new char[9];
                for(int i = 0; i < 9; i++){
                    AM[i] = other.AM[i];
                }
        
                this->onoma = other.onoma;
                this->fylo = other.fylo;
                this->semester = other.semester;
                this->mathimata = other.mathimata;
            }
            return *this;
        }
        ~foititis(){
            delete[] AM;
        }
};

class teacher{
    private:
        int id;
        char* password;
        string name;
        gender fylo;
        string eidikotita;
        vector<string> mathimata;

    public:
        teacher(int id, string password, string name, gender fylo, string eid, vector<string> &mathimata){
            this->password = new char[password.length() + 1];
            for(int i = 0; i <= password.length(); i++){
                this->password[i] = password[i]; 
            }
            this->name = name;
            this->fylo = fylo;
            this->eidikotita = eid;
            this->mathimata = mathimata;
            this->id = id;
        }
        teacher(void){
            password = new char[6];
            password[0] = 'b';
            password[1] = 'l';
            password[2] = 'a';
            password[3] = 'n';
            password[4] = 'k';
            password[5] = '\0';

            name = "blank";
            fylo = unidentified;
            eidikotita = "blank";
        }
        teacher(const teacher& other) {
            int len = 0;
            while(other.password[len] != '\0') len++;
        
            this->password = new char[len + 1];
            for(int i = 0; i <= len; i++){
                this->password[i] = other.password[i];
            }
    
            this->name = other.name;
            this->fylo = other.fylo;
            this->eidikotita = other.eidikotita;
            this->mathimata = other.mathimata;
            this->id = other.id;
        }

        teacher& operator=(const teacher& other) {
            if (this != &other) {
                delete[] password;
        
                int len = 0;
                while(other.password[len] != '\0'){
                    len++;
                }
        
                this->password = new char[len + 1];
                for(int i = 0; i <= len; i++) {
                    this->password[i] = other.password[i];
                }
        
                this->name = other.name;
                this->fylo = other.fylo;
                this->eidikotita = other.eidikotita;
                this->mathimata = other.mathimata;
                this->id = other.id;
            }

            return *this;
        }

        ~teacher(){
            delete[] password;
        }

        string getPassword(void){                      //getters
            string ps;
            ps = password;
            return ps;
        }
        string getOnoma(void){
            return name;
        }
        string getFylo(void){
            switch(fylo){
                case unidentified: return "Μη ορισμένο"; break;
                case male: return "Ανδρας"; break;
                case female: return "Γυναικα"; break;
                default: return "Μη ορισμένο";
            }
        }
        string getSubject(void){
            return eidikotita;
        }
        int getId(void){
            return id;
        }
        vector<string> &getMathimata(void){
            return mathimata;
        }

        void setPassword(string ps){
            delete[] password;
            int l = ps.length();
            password = new char[l+1];
            for(int i = 0; i < l; i++){
                password[i] = ps[i];
            }
            password[l] = '\0';
        }
        void setOnoma(string name){
            this->name = name;
        }
        void setFylo(gender fylo){
            this->fylo = fylo;
        }
        void setFylo(string fylo){
            if (fylo == "Άνδρας" || fylo == "Ανδρας") {
                this->fylo = male;
            } else if (fylo == "Γυναίκα" || fylo == "Γυναικα") {
                this->fylo = female;
            } else {
                this->fylo = unidentified;
            }
        }
        void setSubject(string eid){
            this->eidikotita = eid;
        }
        void setMathimata(vector<string> math){
            mathimata = math;
        }
        void setId(string ids){
            this->id = stoi(ids);
        }

        void printMathimata(){
            short int i = 0;
            for(string math : mathimata){
                cout << i +1 << '.' << math << ' ';
                i++;
            }
        }
        void printAll(void){
            cout << id << "   ";
            cout << name << " (" << name.length() << ")   ";    //στα ελληνικα εμφαζινει μεγεθος μεγαλυτερο του πληθους των χαρακτηρων, αλλα παραμενει το μεγεθος του πινακα.
            cout << getFylo() << "   ";
            cout << eidikotita << "ο εξάμηνο" << "   \n";
            printMathimata();
        }

};

class mathima{
    private:
        int id;
        string description;
        int semester;
        string YpKath;

    public:
        mathima(int id, string des, int sem, string YpKath){
            this->id = id;
            description = des;
            semester = sem;
            this->YpKath = YpKath;
        }
        mathima(void){
            id = -1;
            description = "NO DES";
            semester = -1;
            YpKath = "NONE";
        }
        
        int getId(void){
            return id;
        }
        string getDescription(void){
            return description;
        }
        int getSemester(void){
            return semester;
        }
        string getYpkath(void){
            return YpKath;
        }

        void setDescription(string des){
            description = des;
        }
        void setSemester(int sem){
            semester = sem;
        }
        void setSemester(string semS){
            semester = stoi(semS);
        }
        void setYpKath(string Yp){
            YpKath = Yp;
        }
        void setId(string ids){
            this->id = stoi(ids);
        }
};

bool readField(const string& line, int& i, string& el) {
    el.clear();
    if(i >= (int)line.size()) return false;
    while(i < (int)line.size() && line[i] != ',' && line[i] != '\r'){
        el.push_back(line[i]);
        i++;
    }
    if(i < (int)line.size() && line[i] == ',') i++;
    return true;
}

class foititologio{
    public:
        vector<foititis> foitites;
        vector<teacher> kathigites;
        vector<mathima> mathimata_ps;
    
    public:
        void newFoititis(foititis neos){
            foitites.emplace_back(neos);
        }
        void newFoititis(char AM[9], string onoma){

            foitites.emplace_back(AM, onoma);
        }
        void newFoititis(string AM, string onoma, gender fylo, unsigned int semester, vector<string>mathimata){
            foitites.emplace_back(AM, onoma, fylo, semester, mathimata);
        }
        void newKathigitis(teacher neos){
            kathigites.emplace_back(neos);
        }
        void newKathigitis(int id, string password, string onoma, gender fylo, string subject, vector<string> &mathimata){
            kathigites.emplace_back(id, password, onoma, fylo, subject, mathimata);
        }
        void newMathima(int id, string descreprion, int semester, string YpKath){
            mathimata_ps.emplace_back(id, descreprion, semester, YpKath);
        }

        //γυρνανε τα αντικειμενα
        foititis getFoititis(string AM){
            for(foititis& temp : foitites){
                if(temp.getAM() == AM) return temp;
            }
            cout << "Δεν βρεθηκε Φοιτιτης με ΑΜ:" << AM;
        }
        teacher getKathigitis(int id){
            for(teacher& temp : kathigites){
                if(temp.getId() == id) return temp;
            }
            cout << "Δεν βρεθηκε καθηγητης με id:" << id;
        }
        mathima getMathima(int id){
            for(mathima& temp : mathimata_ps){
                if(temp.getId() == id) return temp;
            }
            cout << "Δεν βρεθηκε μαθημα με id:" << id;
        }

        //επιστρεφει vectors με τις θεσεις των αποτελεσαμτων στον πινακα foitites (στο [0] εχει παντα -1)
        vector<int> gfindFoititis(string info){
            vector<int> apot;
            apot.push_back(-1);
            int n = 0;
            for(foititis& temp : foitites){
                stringstream fullonoma(temp.getOnoma());
                string name, surname;
                fullonoma >> name >> surname;
                if(temp.getAM() == info) apot.push_back(n);
                else if(temp.getOnoma() == info) apot.push_back(n);
                else if(name == info) apot.push_back(n);
                else if(surname == info) apot.push_back(n);
                else if(info.length() <=2  && (int)info[0] >= 48 && (int)info[0] <= 57){
                    if(temp.getSemester() == stoi(info)) apot.push_back(n);
                }
                n++;
            }
            return apot;
        }
        //επιστρεφει vectors με τις θεσεις των αποτελεσαμτων στον πινακα kathigites (στο [0] εχει παντα -2)
        vector<int> gfindKathigitis(string info){
            vector<int> apot;
            apot.push_back(-2);
            int n = 0;
            for(teacher& temp : kathigites){
                stringstream fullonoma(temp.getOnoma());
                string name, surname;
                fullonoma >> name >> surname;
                if(info.length() <=3  && (int)info[0] >= 48 && (int)info[0] <= 57){
                    if(temp.getId() == stoi(info)) apot.push_back(n);
                }else if(temp.getOnoma() == info) apot.push_back(n);
                else if(name == info) apot.push_back(n);
                else if(surname == info) apot.push_back(n);
                else if(temp.getSubject() == info) apot.push_back(n);

                n++;
            }
            return apot;
        }
        //επιστρεφει vectors με τις θεσεις των αποτελεσαμτων στον πινακα mathimata (στο [0] εχει παντα -3)
        vector<int> gfindMathima(string info){
            vector<int> apot;
            apot.push_back(-3);
            int n = 0;
            unsigned short int spacesDes = 0;
            unsigned short int spacesOnoma = 0;
            for(mathima& temp : mathimata_ps){
                for(int i = 0; i < temp.getDescription().length(); i++){
                    if(temp.getDescription()[i] == ' ') spacesDes++;
                }
                stringstream fullDes(temp.getDescription());
                string lexeisDes[spacesDes + 1];
                for(int i = 0; i < spacesDes; i++){
                    fullDes >> lexeisDes[i];
                }

                for(int i = 0; i < temp.getYpkath().length(); i++){
                    if(temp.getYpkath()[i] == ' ') spacesOnoma++;
                }
                stringstream fullOnoma(temp.getYpkath());
                string lexeisOnoma[spacesOnoma + 1];
                for(int i = 0; i < spacesOnoma; i++){
                    fullOnoma >> lexeisOnoma[i];
                }

                if(info.length() <=3  && (int)info[0] >= 48 && (int)info[0] <= 57){
                    if(temp.getId() == stoi(info)) apot.push_back(n);
                }else if(temp.getDescription() == info){
                    apot.push_back(n);
                }else for(string lexi: lexeisDes){
                    if(lexi == info){
                        apot.push_back(n);
                        break;
                    }

                }
                for(string lexi: lexeisOnoma){
                    if(lexi == info){
                        apot.push_back(n);
                        break;
                    }
                }
                n++;
                spacesDes = 0;
                spacesOnoma = 0;
            }
            return apot;
        }

        //γυρναει την θεση στο vector
        int findFoititis(string AM){
            int n = 0;
            for(foititis& temp : foitites){
                if(temp.getAM() == AM) return n;
                n++;
            }
            return -1;
        }
        //γυρναει την θεση στο vector
        int findKathigitis(int id){
            int n = 0;
            for(teacher& temp : kathigites){
                if(temp.getId() == id) return n;
                n++;
            }
            return -1;
        }
        //γυρναει την θεση στο vector
        int findMathima(int id){
            int n = 0;
            for(mathima& temp : mathimata_ps){
                if(temp.getId() == id) return n;
                n++;
            }
            return -1;
        }

        void fixFoitOnoma(string AM, string Onoma){
            int n = findFoititis(AM);
            if (n == -1){
                cout << "Error: Φοιτητής με AM " << AM << " δεν βρέθηκε\n";
                return;
            }
            foitites[n].setOnoma(Onoma);
        }
        int fixFoitAM(string oldAM, string newAM){
            if(oldAM.length() != 8){
                cout << "Error, Το μεγεθος του AM δεν ειναι 8 χαρακτηρες";
                return 0;
            }
            int n = findFoititis(oldAM);
            if(n == -1){
                cout << "Error: Φοιτητής με AM " << oldAM << " δεν βρέθηκε\n";
                return 0;
            }
            foitites[n].setAM(newAM);
            return 1;
        }
        void fixFoitFylo(string AM, gender Fylo){
            int n = findFoititis(AM);
            if(n == -1){
                cout << "Error: Φοιτητής με AM " << AM << " δεν βρέθηκε\n";
                return;
            }
            foitites[n].setFylo(Fylo);
        }
        void fixFoitSemester(string AM, unsigned int sem){
            int n = findFoititis(AM);
            if(n == -1){
                cout << "Error: Φοιτητής με AM " << AM << " δεν βρέθηκε\n";
                return;
            }
            foitites[n].setSemester(sem);
        }
        void fixFoitMathima(string AM, int mathima_id, string neo_mathima){
            int n = findFoititis(AM);
            if(n == -1){
                cout << "Error: Φοιτητής με AM " << AM << " δεν βρέθηκε\n";
                return;
            }
            vector<string>& m = foitites[n].getMathimata();
            if(mathima_id >= 0 && mathima_id < m.size()){
                m[mathima_id] = neo_mathima;
            }
        }

        void fixKathOnoma(int id, string Onoma){
            int n = findKathigitis(id);
            if(n == -1){
                cout << "Error: Καθηγητής με id " << id << " δεν βρέθηκε\n";
                return;
            }
            kathigites[n].setOnoma(Onoma);
        }
        void fixKathFylo(int id, gender Fylo){
            int n = findKathigitis(id);
            if(n == -1){
                cout << "Error: Καθηγητής με id " << id << " δεν βρέθηκε\n";
                return;
            }
            kathigites[n].setFylo(Fylo);
        }
        void fixKathEidikotita(int id, string eid){
            int n = findKathigitis(id);
            if(n == -1){ cout << "Error: Καθηγητής με id " << id << " δεν βρέθηκε\n";
                return;
            }
            kathigites[n].setSubject(eid);
        }
        int fixKathPassword(int id, string old_pass, string new_pass){
            int n = findKathigitis(id);
            if(n == -1){
                cout << "Error: Καθηγητής με id " << id << " δεν βρέθηκε\n";
                return 1;
            }
            if(old_pass != kathigites[n].getPassword()){
                cout << "Error: Λαθος κωδικος Καθηγητή";
                return 1;
            }
            kathigites[n].setPassword(new_pass);
            return 0;
        }
        void fixKathMathima(int id, int mathima_id, string neo_mathima){
            int n = findKathigitis(id);
            if(n == -1){
                cout << "Error: Καθηγητής με id " << id << " δεν βρέθηκε\n";
                return;
            }
            vector<string>& m = kathigites[n].getMathimata();
            if(mathima_id >= 0 && mathima_id < (int)m.size()){
                m[mathima_id] = neo_mathima;
            }
        }

        string deleteFoititis(string AM){
            stringstream apot;
            int n = findFoititis(AM);
            if(n == -1){
                apot << "Error: Φοιτητής με AM " << AM << " δεν βρέθηκε";
                return apot.str();
            }
            foitites.erase(foitites.begin() + n);  
            apot << "Ο Φοιτητής με ΑΜ: " << AM << " Διαγράφτηκε επιτυχώς";
            return apot.str();   
        }
        string deleteKathigitis(int id){
            stringstream apot;
            int n = findKathigitis(id);
            if(n == -1){
                apot << "Error: Καθηγητής με id " << id << " δεν βρέθηκε";
                return apot.str();
            }
            kathigites.erase(kathigites.begin() + n);
            apot << "Καθηγητής με id: " << id << " Διαγράφτηκε επιτυχώς";
            return apot.str();
        }
        string deleteMathima(int id){
            stringstream apot;
            int n = findMathima(id);
            if(n == -1){
                apot << "Error: Το μάθημα με id: " << id << " δεν βρέθηκε";
                return apot.str();
            }
            mathimata_ps.erase(mathimata_ps.begin() + n);
            apot << "Το μάθημα με id: " << id << " Διαγράφτηκε επιτυχώς";
            return apot.str();
        }

        foititis &giveFoititis(string AM){
            int i = findFoititis(AM);
            if(i == -1){
                exit;
            }
            return foitites[i];
        }
        teacher &giveKathigitis(int id){
            int i = findKathigitis(id);
            if(i == -1){
                exit;
            }
            return kathigites[i];
        }

        void MailAllFoitites(void){
            for(foititis temp : foitites){
                if(temp.getFylo() == "Άνδρας")
                    cout << "Αποστάλθηκε email στον " << temp.getOnoma() << " με ΑΜ: " << temp.getAM() << "\n";
                else if(temp.getFylo() == "Γυναίκα")
                    cout << "Αποστάλθηκε email στην " << temp.getOnoma() << " με ΑΜ: " << temp.getAM() << "\n";
                else
                    cout << "Φοιτητής " << temp.getOnoma() << ": Μη ορισμένο φύλο\n";
            }
        }
        void MailAllKathigites(void){
            for(teacher temp : kathigites){
                if(temp.getFylo() == "Ανδρας")
                    cout << "Αποστάλθηκε email στον Κυριο " << temp.getOnoma() << "\n";
                else if(temp.getFylo() == "Γυναικα")
                    cout << "Αποστάλθηκε email στην Κυρια " << temp.getOnoma() << "\n";
                else
                    cout << "Καθηγητής " << temp.getOnoma() << ": Μη ορισμένο φύλο\n";
            }
        }

        void PrintAllFoitites(void){
            if(foitites.size() != 0){
                cout << "Oι φοιτητες ειναι οι: " << endl;
                for(foititis &temp: foitites){
                    cout << "                      " << temp.getOnoma() << endl;
                }
            }
        }
        void PrintAllKathigites(void){
            if(kathigites.size() != 0){
                cout << "Oι φοιτητες ειναι οι: " << endl;
                for(teacher &temp: kathigites){
                    cout << "                      " << temp.getOnoma() << endl;
                }
            }
        }

        foititologio(){
            fstream lista_foititwn;
            lista_foititwn.open("lista_foititwn.csv", ios::in);
            if(!lista_foititwn.is_open()){
                cout << "ERROR: Κατι πηγε λαθως στην φoρτωση των αρχειων.\n";
            }else{
                string line;
                int i;
                string element;
                while(getline(lista_foititwn, line)){
                    if(line.empty()) continue;
                    i = 0;
                    foititis tempFoit;
                    vector<string> tempVec;

                    readField(line, i, element);
                    tempFoit.setAM(element);

                    readField(line, i, element);
                    tempFoit.setFylo(element);

                    readField(line, i, element);
                    tempFoit.setOnoma(element);

                    readField(line, i, element);
                    tempFoit.setSemester(element);

                    readField(line, i, element);
                    string tempMathima;
                    for(char c : element){
                        if(c == '-'){
                            if(!tempMathima.empty()){
                                tempVec.push_back(tempMathima);
                                tempMathima.clear();
                            }
                        }else{
                            tempMathima.push_back(c);
                        }
                    }
                    tempFoit.setMathimata(tempVec);
                    foitites.push_back(tempFoit);
                }
                lista_foititwn.close();
            }

            fstream lista_kathigitwn;
            lista_kathigitwn.open("lista_kathigitwn.csv", ios::in);
            if(!lista_kathigitwn.is_open()){
                cout << "ERROR: Κατι πηγε λαθως στην φoρτωση των αρχειων.\n";
            }else{
                string line;
                int i;
                string element;
                while(getline(lista_kathigitwn, line)){
                    if(line.empty()) continue;
                    i = 0;
                    teacher tempKath;
                    vector<string> tempVec;

                    readField(line, i, element);
                    tempKath.setId(element);

                    readField(line, i, element);
                    tempKath.setFylo(element);

                    readField(line, i, element);
                    tempKath.setOnoma(element);

                    readField(line, i, element);
                    tempKath.setSubject(element);

                    readField(line, i, element);
                    tempKath.setPassword(element);

                    readField(line, i, element);
                    string tempMathima;
                    for(char c : element){
                        if(c == '-'){
                            if(!tempMathima.empty()){
                                tempVec.push_back(tempMathima);
                                tempMathima.clear();
                            }
                        }else{
                            tempMathima.push_back(c);
                        }
                    }
                    tempKath.setMathimata(tempVec);
                    kathigites.push_back(tempKath);
                }
                lista_kathigitwn.close();
            }

            fstream mathimataPS;
            mathimataPS.open("lista_mathimatwn.csv", ios::in);
            if(!mathimataPS.is_open()){
                cout << "ERROR: Κατι πηγε λαθως στην φoρτωση των αρχειων.\n";
            }else{
                string line;
                int i = 0;
                string element;
                while(getline(mathimataPS, line)){
                    if(line.empty()) continue;
                    i = 0;
                    mathima tempMath;

                    readField(line, i, element);
                    tempMath.setId(element);

                    readField(line, i, element);
                    tempMath.setDescription(element);

                    readField(line, i, element);
                    tempMath.setSemester(element);

                    readField(line, i, element);
                    tempMath.setYpKath(element);

                    mathimata_ps.push_back(tempMath);
                }
                mathimataPS.close();
            }
        }


        ~foititologio(){                     //κανει save σε αρχεια csv τις πληροφοριες
            fstream lista_foititwn;
            lista_foititwn.open("lista_foititwn.csv", ios::out);
            if(!lista_foititwn.is_open()){
                cout << "ERROR: Κατι πηγε λαθως στην αποθηκευση στα αρχεια. Οι αλλαγες στους φοιτητες ΔΕΝ αποθηκεύτηκαν";
            }else{
                for(foititis temp : foitites){
                    lista_foititwn << temp.getAM() << ',' << temp.getFylo() << ',' << temp.getOnoma() << ',' << temp.getSemester() << ',';
                    for(string tempMath : temp.getMathimata()){
                        lista_foititwn << tempMath << '-';
                    }
                    lista_foititwn << "\n";
                }
                lista_foititwn.close();
            }

            fstream lista_kathigitwn;
            lista_kathigitwn.open("lista_kathigitwn.csv", ios::out);
            if(!lista_kathigitwn.is_open()){
                cout << "ERROR: Κατι πηγε λαθως στην αποθηκευση στα αρχεια. Οι αλλαγες στους καθηγητές ΔΕΝ αποθηκεύτηκαν";
            }else{
                for(teacher temp : kathigites){
                    lista_kathigitwn << temp.getId() << ',' << temp.getFylo() << ',' << temp.getOnoma() << ',' << temp.getSubject() << ',' << temp.getPassword() << ',';
                    for(string tempMath : temp.getMathimata()){
                        lista_kathigitwn << tempMath << '-';
                    }
                    lista_kathigitwn << "\n";
                }
                lista_kathigitwn.close();
            }
            
            fstream mathimataPS;
            mathimataPS.open("lista_mathimatwn.csv", ios::out);
            if(!mathimataPS.is_open()){
                cout << "ERROR: Κατι πηγε λαθως στην αποθηκευση στα αρχεια. Οι αλλαγες στα μαθήματα του προγραμματος σπουδών ΔΕΝ αποθηκεύτηκαν";
            }else{
                for(mathima temp : mathimata_ps){
                    mathimataPS << temp.getId() << ',' << temp.getDescription() << ',' << temp.getSemester() << ',' << temp.getYpkath();
                    mathimataPS << "\n";
                }
                mathimataPS.close();
            }
            
        }
};

#endif
