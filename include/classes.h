#include <iostream>
#include <vector>

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
        foititis(string AM, string onoma);
        foititis(void);
        foititis(const foititis &other);
        foititis(string AM, string onoma, gender fylo, unsigned int semester, vector<string>mathimata);

        string getAM(void);
        string getOnoma(void);
        string getFylo(void);
        unsigned int getSemester(void);
        vector<string> &getMathimata(void);

        int setAM(string AM);
        void setOnoma(string onoma);
        void setFylo(gender fylo);
        void setFylo(string fylo);
        void setSemester(unsigned int semester);
        void setSemester(string semester);
        void setMathimata(vector<string> math);
        
        void printMathimata();
        void printAll(void);

        foititis& operator++(void);
        foititis& operator+=(int n);
        foititis& operator-=(int n);
        foititis& operator-(void);
        foititis& operator=(const foititis& other);
        ~foititis();
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
        teacher(int id, string password, string name, gender fylo, string eid, vector<string> &mathimata);
        teacher(void);
        teacher(const teacher& other);

        teacher& operator=(const teacher& other);

        ~teacher();

        string getPassword(void);
        string getOnoma(void);
        string getFylo(void);
        string getSubject(void);
        int getId(void);
        vector<string> &getMathimata(void);

        void setPassword(string ps);
        void setOnoma(string name);
        void setFylo(gender fylo);
        void setFylo(string fylo);
        void setSubject(string eid);
        void setMathimata(vector<string> math);
        void setId(string ids);

        void printMathimata();
        void printAll(void);
};

class mathima{
    private:
        int id;
        string description;
        int semester;
        string YpKath;

    public:
        mathima(int id, string des, int sem, string YpKath);
        mathima(void);
        
        int getId(void);
        string getDescription(void);
        int getSemester(void);
        string getYpkath(void);

        void setDescription(string des);
        void setSemester(int sem);
        void setSemester(string semS);
        void setYpKath(string Yp);
        void setId(string ids);
};

class foititologio{
    public:
        vector<foititis> foitites;
        vector<teacher> kathigites;
        vector<mathima> mathimata_ps;
    
    public:
        void newFoititis(foititis neos);
        void newFoititis(char AM[9], string onoma);
        void newFoititis(string AM, string onoma, gender fylo, unsigned int semester, vector<string>mathimata);
        void newKathigitis(teacher neos);
        void newKathigitis(int id, string password, string onoma, gender fylo, string subject, vector<string> &mathimata);
        void newMathima(int id, string descreprion, int semester, string YpKath);

        //γυρνανε τα αντικειμενα
        foititis getFoititis(string AM);
        teacher getKathigitis(int id);
        mathima getMathima(int id);

        //επιστρεφει vectors με τις θεσεις των αποτελεσαμτων στον πινακα foitites (στο [0] εχει παντα -1)
        vector<int> gfindFoititis(string info);
        //επιστρεφει vectors με τις θεσεις των αποτελεσαμτων στον πινακα kathigites (στο [0] εχει παντα -2)
        vector<int> gfindKathigitis(string info);
        //επιστρεφει vectors με τις θεσεις των αποτελεσαμτων στον πινακα mathimata (στο [0] εχει παντα -3)
        vector<int> gfindMathima(string info);

        //γυρναει την θεση στο vector
        int findFoititis(string AM);
        //γυρναει την θεση στο vector
        int findKathigitis(int id);
        //γυρναει την θεση στο vector
        int findMathima(int id);

        void fixFoitOnoma(string AM, string Onoma);
        int fixFoitAM(string oldAM, string newAM);
        void fixFoitFylo(string AM, gender Fylo);
        void fixFoitSemester(string AM, unsigned int sem);
        void fixFoitMathima(string AM, int mathima_id, string neo_mathima);

        void fixKathOnoma(int id, string Onoma);
        void fixKathFylo(int id, gender Fylo);
        void fixKathEidikotita(int id, string eid);
        int fixKathPassword(int id, string old_pass, string new_pass);
        void fixKathMathima(int id, int mathima_id, string neo_mathima);

        string deleteFoititis(string AM);
        string deleteKathigitis(int id);
        string deleteMathima(int id);

        foititis &giveFoititis(string AM);
        teacher &giveKathigitis(int id);

        void MailAllFoitites(void);
        void MailAllKathigites(void);

        void PrintAllFoitites(void);
        void PrintAllKathigites(void);

        foititologio();


        ~foititologio();
};