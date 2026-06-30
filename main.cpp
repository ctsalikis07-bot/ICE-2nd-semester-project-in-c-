#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <random>
#include <ncurses.h>
#include <locale.h>
#include "classes.h"
using namespace std;
enum type {foit, kath, math, none};
enum oper {Epej, del, noOp};


//kane move ekei poy thes prin to kaleseis
string gettext(WINDOW * &win, int cap){
    curs_set(1);
    int y, x;
    getbegyx(win, y, x);
    WINDOW * getit = newwin(1, cap, getcury(win)+ y, getcurx(win)+ x);
    keypad(getit, true);
    int ch;
    string search;
    int width = 0;
    while((ch = wgetch(getit)) != '\n'){
        width = 0;
        for(int i = 0; i < search.length(); i++){
            unsigned char c = search[i];
            if(c == 206 || c == 207) i++;
            width++;
        }
        if(ch == KEY_BACKSPACE || ch == 127 || ch == 8){
            if(!search.empty() && ((search[search.length() - 2] == (char)206) || (search[search.length() - 2] == (char)207))){
                search.erase(search.length() - 2);
            }else if(!search.empty()){
                search.pop_back();
            }
        }
        else if(ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT){}
        else if((ch == 206 || ch == 207) && search.length() < cap*2){
            search.push_back(char(ch));
            search.push_back(wgetch(getit));
        }
        else if(ch > 31 && search.length()<cap){
            search.push_back(char(ch));
        }
        
        for(int i = 0; i <= width; i++){
            mvwprintw(getit, 0, i, " ");
        }
        mvwprintw(getit, 0, 0, search.c_str());
        wrefresh(getit);
    }
    curs_set(0);
    wclear(getit);
    delwin(getit);
    return search;
}
void apotelesma(string text){
    WINDOW * apot = newwin(3, 70, LINES - 6, COLS/2 - 35);
    box(apot, 0, 0);
    mvwprintw(apot, 1, 3, text.c_str());
    mvwprintw(apot, 2, 13, "Πιέστε οποιοδήποτε πλήκτρο για να συνεχίσετε");
    wrefresh(apot);
    wgetch(apot);
    wclear(apot);
    wrefresh(apot);
    delwin(apot);
}
bool yes_no(unsigned short int start_y, unsigned short int start_x){
    WINDOW * yn = newwin(5, 17, start_y, start_x);
    keypad(yn, true);
    box(yn, 0, 0);
    mvwin(yn, start_y, start_x);
    wrefresh(yn);
    string elements[2] = {"OXI", "NAI"};
    int highlight = 0;
    bool run = true;
    int epilogi;
    mvwprintw(yn, 1, 1, "Είστε σίγουροι;");
    while(run){
        if(highlight<0) highlight++;
        if(highlight>1) highlight--;
        wmove(yn, 2, 1);
        wrefresh(yn);
        for(int i = 0; i < 2; i++)
        {
            if(i == highlight) wattron(yn, A_REVERSE);  
            wprintw(yn, elements[i].c_str());
            wattroff(yn, A_REVERSE);
            if(i!=1) wmove(yn, getcury(yn) +1, 1);
        }
        wrefresh(yn);
        epilogi = wgetch(yn);
        switch(epilogi){
            case KEY_UP: highlight--; break;
            case KEY_DOWN: highlight++; break;
            case (int)' ': run = false; wclear(yn); break;
            default: break;
        }
        if(epilogi == 10){
            switch(highlight){
                case 0: wclear(yn); wrefresh(yn); delwin(yn); return false; break;
                case 1: wclear(yn); wrefresh(yn); delwin(yn); return true; break;
                default: break;
            }
        }
    }
    
    wrefresh(yn);
    delwin(yn);
    return false;
}
oper epilogesAnaz(type eidos, string AM, int id, const int &highlight, WINDOW * &resaults, WINDOW * &searchBar, foititologio &catalog){
    oper whatDo = noOp;
    bool run = true;
    int highlightC = 0;
    int epilogi;
    bool yn = false;
    int y = 5;
    if(eidos == math){
        y = 4;
    }
    WINDOW *choises = newwin(y, 16, 0, 0);
    keypad(choises, true);
    box(choises, 0, 0);
    string choices_txt[3] = {"Επεξεργασία", "Αποστολή eMail", "Διαγραφή"};
    mvwin(choises, 13 + highlight, COLS/28 + 3);
    while(run){
        if(eidos == math){
            if((highlightC == 1) && epilogi == KEY_UP) highlightC = 0;
            if((highlightC == 1) && epilogi == KEY_DOWN) highlightC = 2;
        }
        if(highlightC<0) highlightC++;
        if(highlightC >= 3) highlightC--;
        wrefresh(choises);
        wmove(choises, 1, 1);
        for(int i = 0; i < 3; i++){
            if((eidos != math) || (i != 1)){
                if(i == highlightC) wattron(choises, A_REVERSE);  
                wprintw(choises, choices_txt[i].c_str());
                wattroff(choises, A_REVERSE);
                if(i!=2) wmove(choises, getcury(choises)+1, 1);
            }
        }
        wrefresh(choises);

        epilogi = wgetch(choises);
        switch(epilogi){
            case KEY_UP: highlightC--; break;
            case KEY_DOWN: highlightC++; break;
            case (int)' ': run = false; wclear(choises); break;
            default: break;
        }
        if(epilogi == 10 && highlightC == 0){
            whatDo = Epej;
            run = false;
        }else if(epilogi == 10 && highlightC == 1){
            yn = yes_no(13 + highlight, COLS/28 + 19);
            touchwin(resaults);
            wrefresh(resaults);
            touchwin(choises);
            wrefresh(choises);
            touchwin(searchBar);
            wrefresh(searchBar);
            if(yn){
                apotelesma("Το e-Mail στάλθηκε επιτυχώς!");
            }
            touchwin(resaults);
            wrefresh(resaults);
            touchwin(choises);
            wrefresh(choises);
            touchwin(searchBar);
            wrefresh(searchBar);
            
        }else if(epilogi == 10 && highlightC == 2){
            yn = yes_no(13 + highlight, COLS/28 + 19);
            touchwin(resaults);
            wrefresh(resaults);
            touchwin(choises);
            wrefresh(choises);
            touchwin(searchBar);
            wrefresh(searchBar);
            if(yn){
                string apot;
                switch(eidos){
                    case foit: apot = catalog.deleteFoititis(AM); break;
                    case kath: apot = catalog.deleteKathigitis(id); break;
                    case math: apot = catalog.deleteMathima(id); break;
                    case none: break;
                    default: break;
                }
                apotelesma(apot);
                whatDo = del;
                run = false;
            }
            touchwin(resaults);
            wrefresh(resaults);
            touchwin(choises);
            wrefresh(choises);
            touchwin(searchBar);
            wrefresh(searchBar);
        }
        wrefresh(choises);
    }
    wclear(choises);
    wrefresh(choises);
    delwin(choises);
    return whatDo;
}
type epiloges(int &highlight, bool enikos){
    WINDOW * epiloges = newwin(5, 12, 0, 0);
    int first_highlight = highlight;
    int epilogi;
    bool addRun = true;
    string * epilogesAdd_elements;
    int x = 0;
    int n = 0;
    switch(highlight){
        case 1: x = COLS/2 - 26; break;
        case 2: x = COLS/2 - 14; break;
        case 3: x = COLS/2 + 11; break;
        default: break;
    }
    if(enikos){
        mvwin(epiloges, 5, x);
        mvwprintw(epiloges, 1, 1, "Φοιτητή");
        mvwprintw(epiloges, 2, 1, "Καθηγητή");
        mvwprintw(epiloges, 3, 1, "Μάθημα");
        box(epiloges, 0, 0);
        wrefresh(epiloges);
        n = 3;
        epilogesAdd_elements = new string[3]{"Φοιτητή   ", "Καθηγητή  ", "Μάθημα    "};
    }else if(!enikos && highlight == 3){
        mvwin(epiloges, 5, x);
        mvwprintw(epiloges, 1, 1, "Φοιτητές");
        mvwprintw(epiloges, 2, 1, "Καθηγητές");
        mvwprintw(epiloges, 3, 1, "Μαθήματα");
        box(epiloges, 0, 0);
        wrefresh(epiloges);
        n = 3;
        epilogesAdd_elements = new string[3]{"Φοιτητές  ", "Καθηγητές ", "Μαθήματα  "};
    }else if(!enikos && highlight == 2){
        mvwin(epiloges, 5, x);
        mvwprintw(epiloges, 1, 1, "Φοιτητές");
        mvwprintw(epiloges, 2, 1, "Καθηγητές");
        box(epiloges, 0, 0);
        wrefresh(epiloges);
        n = 2;
        epilogesAdd_elements = new string[2]{"Φοιτητές  ", "Καθηγητές "};
    }
    
    highlight = 0;
    while(addRun){
        if(highlight<0) highlight++;
        if(highlight>n-1) highlight--;
        wmove(epiloges, 1, 1);
        for(int i = 0; i < n; i++)
        {
            if(i == highlight) wattron(epiloges, A_REVERSE);  
            wprintw(epiloges, epilogesAdd_elements[i].c_str());
            wattroff(epiloges, A_REVERSE);
            wmove(epiloges, getcury(epiloges) + 1, 1);
        }
        wrefresh(epiloges);
        epilogi = getch();
        switch(epilogi){
            case KEY_UP: if(highlight > 0) highlight--; break;
            case KEY_DOWN: highlight++; break;
            case KEY_LEFT: highlight = first_highlight -1; addRun = false; wclear(epiloges); break;
            case KEY_RIGHT: highlight = first_highlight +1; addRun = false; wclear(epiloges); break;
            default: break;
        }
        if(epilogi == 10){
            switch(highlight){
                case 0: delwin(epiloges); return foit; break;
                case 1: delwin(epiloges); return kath; break;
                case 2: delwin(epiloges); return math; break;
                default: break;
            }
        }
        wrefresh(epiloges);
    }

    wclear(epiloges);
    touchwin(epiloges);
    wrefresh(epiloges);
    delwin(epiloges);
    return none;
}
bool edit(type whatEdit, string AM, int id, const int &highlight, WINDOW * &resaults, foititologio &catalog){
    bool isEdit = false;
    WINDOW * editor = newwin(3, 50, LINES/28 + 13 + highlight, COLS/28 + 3);
    box(editor, 0, 0);
    bool run = true;
    int epilogi;
    int highlightC = 1;
    if((whatEdit == foit) && (!AM.empty())){
        foititis editFoit(catalog.getFoititis(AM));
        int foitVecPos = catalog.findFoititis(AM);
        string Sedit[4] = {editFoit.getAM(), editFoit.getOnoma(), editFoit.getFylo(), to_string(editFoit.getSemester())};
        while(run){
            if(highlightC<1) highlightC++;
            if(highlightC >= 4) highlightC--;

            wmove(resaults, 11 + highlight, 3);
            wrefresh(resaults);
            for(int i = 0; i < 4; i++){
                if(i == highlightC) wattron(resaults, A_REVERSE);  
                wprintw(resaults, "%s", Sedit[i].c_str()); 
                wattroff(resaults, A_REVERSE);
                if(i!= 3) wprintw(resaults, " | ");
            }
            wrefresh(resaults);
            epilogi = wgetch(resaults);
            switch(epilogi){
                case KEY_LEFT: highlightC--; break;
                case KEY_RIGHT: highlightC++; break;
                case (int)' ': run = false; isEdit = false; mvwchgat(resaults, 11 + highlightC, 3, 70, A_NORMAL, 0, NULL); break;
                default: break;
            }          
            if(epilogi == 10 && highlightC == 1){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.foitites[foitVecPos].setOnoma(gettext(editor, 48));
                apotelesma("Το όνοματεπώνυμο άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }else if(epilogi == 10 && highlightC == 2){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.foitites[foitVecPos].setFylo(gettext(editor, 48));
                apotelesma("Το Φύλο άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }else if(epilogi == 10 && highlightC == 3){
                wrefresh(editor);
                wmove(editor, 1, 1);
                
                catalog.foitites[foitVecPos].setSemester(gettext(editor, 48));
                apotelesma("Το Τρέχων εξάμηνο άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }
        }
    }else if((whatEdit == kath) && (id != -1)){
        teacher editKath(catalog.getKathigitis(id));
        int KathVecPos = catalog.findKathigitis(id);
        string Sedit[4] = {to_string(editKath.getId()), editKath.getOnoma(), editKath.getFylo(), editKath.getSubject()};
        while(run){
            if(highlightC<1) highlightC++;
            if(highlightC >= 4) highlightC--;

            wmove(resaults, 11 + highlight, 3);
            wrefresh(resaults);
            for(int i = 0; i < 4; i++){
                if(i == highlightC) wattron(resaults, A_REVERSE);  
                wprintw(resaults, "%s", Sedit[i].c_str()); 
                wattroff(resaults, A_REVERSE);
                if(i!= 3) wprintw(resaults, " | ");
            }
            wrefresh(resaults);
            epilogi = wgetch(resaults);
            switch(epilogi){
                case KEY_LEFT: highlightC--; break;
                case KEY_RIGHT: highlightC++; break;
                case (int)' ': run = false; isEdit = false; mvwchgat(resaults, 11 + highlightC, 3, 70, A_NORMAL, 0, NULL); break;
                default: break;
            }          
            if(epilogi == 10 && highlightC == 1){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.kathigites[KathVecPos].setOnoma(gettext(editor, 48));
                apotelesma("Το όνοματεπώνυμο άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }else if(epilogi == 10 && highlightC == 2){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.kathigites[KathVecPos].setFylo(gettext(editor, 48));
                apotelesma("Το Φύλο άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }else if(epilogi == 10 && highlightC == 3){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.kathigites[KathVecPos].setSubject(gettext(editor, 48));
                apotelesma("Η Ειδικότητα άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }
        }
    }else if((whatEdit == math) && (id != -1)){
        mathima editMath(catalog.getMathima(id));
        int mathVecPos = catalog.findMathima(id);
        string Sedit[4] = {to_string(editMath.getId()), editMath.getDescription(), editMath.getYpkath(), to_string(editMath.getSemester())};
        while(run){
            if(highlightC<1) highlightC++;
            if(highlightC >= 4) highlightC--;

            wmove(resaults, 11 + highlight, 3);
            wrefresh(resaults);
            for(int i = 0; i < 4; i++){
                if(i == highlightC) wattron(resaults, A_REVERSE);  
                wprintw(resaults, "%s", Sedit[i].c_str()); 
                wattroff(resaults, A_REVERSE);
                if(i!= 3) wprintw(resaults, " | ");
            }
            wrefresh(resaults);
            epilogi = wgetch(resaults);
            switch(epilogi){
                case KEY_LEFT: highlightC--; break;
                case KEY_RIGHT: highlightC++; break;
                case (int)' ': run = false; isEdit = false; mvwchgat(resaults, 11 + highlightC, 3, 70, A_NORMAL, 0, NULL); break;
                default: break;
            }          
            if(epilogi == 10 && highlightC == 1){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.mathimata_ps[mathVecPos].setDescription(gettext(editor, 48));
                apotelesma("Η περιγραφή άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }else if(epilogi == 10 && highlightC == 2){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.mathimata_ps[mathVecPos].setYpKath(gettext(editor, 48));
                apotelesma("Ο Υπέυθυνος Καθηγητής άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }else if(epilogi == 10 && highlightC == 3){
                wrefresh(editor);
                wmove(editor, 1, 1);
                catalog.mathimata_ps[mathVecPos].setSemester(gettext(editor, 48));
                apotelesma("Το Τρέχων εξάμηνο άλλαξε επιτυχώς!");
                isEdit = true;
                run = false;
            }
        }
    }
    wclear(editor);
    wrefresh(editor);
    delwin(editor);
    return isEdit;
}
vector<string> addMathimata(type ti){
    bool run = true;
    int start_x, start_y;
    switch(ti){
        case foit: start_y = LINES/28 + 8; start_x = COLS/28 + 14; break;
        case kath: start_y = LINES/28 + 9; start_x = COLS/28 + 14; break;
        case math: run = false; break;
        default: run = false; break;
    }
    curs_set(1);
    WINDOW * addm = newwin(3, 70, start_y, start_x);
    box(addm, 0, 0);
    wrefresh(addm);
    keypad(addm, true);

    int highlight = 0;
    int n = 0;
    vector<string> inputv;
    string inputs;
    int epilogi;
    wmove(addm, 1, 1);
    if(run) inputs = gettext(addm, 68);
    while(run){
        if(!inputs.empty()){
            inputv.push_back(inputs);
            n++;
        }
        if(highlight < 0) highlight ++;
        if(highlight >= n) highlight --;

        mvwprintw(addm, 1, 1, "                                                                    ");
        mvwprintw(addm, 1, 1, inputv.at(highlight).c_str());

        mvwprintw(addm, 1, 60, "%d από %d", highlight + 1, n);
        epilogi = wgetch(addm);
        switch(epilogi){
            case KEY_UP: highlight--; break;
            case KEY_DOWN: highlight++; break;
            case (int)' ': run = false; break;
            default: break;
        }
        wmove(addm, 1, 1);
        if(epilogi == 10){
            inputs = gettext(addm, 68);
            inputv.at(highlight) = inputs;
        }
        if(epilogi == KEY_DOWN && (highlight == n)){
            inputs = gettext(addm, 68);
            if(!inputs.empty()){
                inputv.push_back(inputs);
                n++;
            }
        }
        inputs.clear();
    }

    curs_set(0);
    wclear(addm);
    wrefresh(addm);
    delwin(addm);
    return inputv;
}
void seeMathimata(vector<string> math, type whatAdd){
    int y;
    if(whatAdd == foit) y = 6 + LINES/28;
    else if(whatAdd == kath) y = 7 + LINES/28;
    WINDOW * seem = newwin(15, 52, y, 37 + COLS/28);
    box(seem, 0, 0);
    wmove(seem, 1, 1);
    for(int i = 0; i < math.size(); i++){
        if(i != math.size() - 1){
            if(math.at(i).length() >= getmaxx(seem)-getcurx(seem)){
                wmove(seem, getcury(seem) + 1, 1);
            }
        }
        wprintw(seem, "%s, ", math.at(i).c_str());
    }
    
    wgetch(seem);
    wclear(seem);
    delwin(seem);
}
void anazitisi(string search, WINDOW * &searchBar, foititologio &catalog){
    mvwin(searchBar, 2, COLS/2 - 30);
    wclear(searchBar);
    mvwprintw(searchBar, 1, 5, search.c_str());
    box(searchBar, 0, 0);
    WINDOW *resaults = newwin(26*LINES/28, 26*COLS/28, LINES/28, COLS/28);
    box(resaults, 0, 0);
    keypad(resaults, true);
    clear();
    refresh();
    wrefresh(resaults);
    noecho();
    curs_set(0);
    vector<int> foitApot = catalog.gfindFoititis(search);
    vector<int> kathApot = catalog.gfindKathigitis(search);
    vector<int> mathApot = catalog.gfindMathima(search);
    vector<int> apot;
    bool noel;
    if((foitApot.size() == kathApot.size() == mathApot.size())&& foitApot.size() == 1){
        noel = true;
    }

    vector<foititis> foitites;
    vector<teacher> kathigites;
    vector<mathima> mathimata;
    bool run = true;
    bool listaRun = true;
    int highlight = 0;
    int epilogi;
    type epilegmeno = none;
    string elements[3]= {"Φοιτητες", "Καθηγητές", "Μαθηματα"};

    if(foitApot.size() != 1){
        for(int i : foitApot){
            if(i!=-1){
                foitites.push_back(catalog.foitites[i]);
            }
        }
    }
    if(kathApot.size() != 1){
        for(int i: kathApot){
            if(i!= -2){
                kathigites.push_back(catalog.kathigites[i]);
            }
        }
    }
    if(mathApot.size() != 1){
        for(int i: mathApot){
            if(i!= -3){
                mathimata.push_back(catalog.mathimata_ps[i]);
            }
        }
    }

    if(noel){
        wattron(resaults, A_BOLD);
        mvwprintw(resaults, 6, 3, "ΔΕΝ ΒΡΕΘΗΚΑΝ ΑΠΟΤΕΛΕΣΜΑΤΑ");
        mvwprintw(resaults, 7, 3, "πιέστε οποιοδήποτε κουμπί στο πληκτρολόγιο για επιστροφή στην αρχικη οθόνη");
        wattron(resaults, A_BOLD);
        wrefresh(resaults);
        wrefresh(searchBar);
        wgetch(resaults);
        run = false;
    
    }else{
        wattron(resaults, A_BOLD);
        wmove(resaults, 6, 4);
        wprintw(resaults, "Βρέθηκαν: ");
        if(foitApot.size() > 1){
            wprintw(resaults, "%d αποτελέσματα στους Φοιτητές", foitApot.size() - 1);
            wmove(resaults, 7, 14);
        }
        if(kathApot.size() > 1){
            wprintw(resaults, "%d αποτελέσματα στους Καθηγητές", kathApot.size() - 1);
            wmove(resaults, getcury(resaults) +1, 14);
        }
        if(mathApot.size() > 1) wprintw(resaults, "%d αποτελέσματα στα Μαθήματα", mathApot.size() - 1);
        wattroff(resaults, A_BOLD);
        wrefresh(resaults);
    }
    wrefresh(resaults);
    wrefresh(searchBar);
    while(run){
        listaRun = true;
        epilegmeno = none;
        if(highlight<0) highlight++;
        if(highlight>2) highlight--;
        wmove(resaults, 6, getmaxx(resaults)-30);
        wrefresh(resaults);
        for(int i = 0; i < 3; i++)
        {
            if(i == highlight) wattron(resaults, A_REVERSE);  
            wprintw(resaults, elements[i].c_str());
            wattroff(resaults, A_REVERSE);
            if(i!=2) wprintw(resaults, "|");
        }
        wrefresh(resaults);
        epilogi = wgetch(resaults);
        switch(epilogi){
            case KEY_LEFT: highlight--; break;
            case KEY_RIGHT: highlight++; break;
            case (int)' ': run = false; break;
            default: break;
        }
        
        if((epilogi == 10) && highlight == 0){
            if(foitites.size() > 0) epilegmeno = foit;
        }else if((epilogi == 10) && highlight == 1){
            if(kathigites.size() > 0) epilegmeno = kath;
        }else if((epilogi == 10) && highlight == 2){
            if(mathimata.size() > 0) epilegmeno = math;
        }
        
        if(epilegmeno == foit){
            highlight = 0;
            mvwchgat(resaults, 6, getmaxx(resaults)-30, 27, A_NORMAL, 0, NULL);
            for(int i = 0; i < 10; i++){
                wmove(resaults, 9 + i, 3);
                wprintw(resaults, "                                                                                           ");
            }

            wattron(resaults, A_BOLD);
            mvwprintw(resaults, 10, 5, " ΑΜ | Ονοματεπώνυμο | Φύλο | Εξάμηνο ");
            wattroff(resaults, A_BOLD);

            while(listaRun){
                if(highlight<0) highlight++;
                if(highlight >= foitites.size()) highlight--;
                wmove(resaults, 11, 3);
                wrefresh(resaults);
                for(int i = 0; i < foitites.size(); i++)
                {
                    if(i == highlight) wattron(resaults, A_REVERSE);  
                    wprintw(resaults, "%s | ", foitites[i].getAM().c_str());
                    wprintw(resaults, "%s | ", foitites[i].getOnoma().c_str());
                    wprintw(resaults, "%s | ", foitites[i].getFylo().c_str());
                    wprintw(resaults, "%d", foitites[i].getSemester());
                    wattroff(resaults, A_REVERSE);
                    if(i!=foitites.size()-1) wmove(resaults, getcury(resaults)+1, 3);
                }
                wrefresh(resaults);
                epilogi = wgetch(resaults);
                switch(epilogi){
                    case KEY_UP: highlight--; break;
                    case KEY_DOWN: highlight++; break;
                    case (int)' ': listaRun = false; mvwchgat(resaults, 11 + highlight, 3, 70, A_NORMAL, 0, NULL); break;
                    default: break;
                }
                if(epilogi == 10){
                    oper w = epilogesAnaz(foit, foitites[highlight].getAM(), -1, highlight, resaults, searchBar, catalog);
                    if(w == Epej){
                        if(edit(foit, foitites[highlight].getAM(), -1, highlight, resaults, catalog)){
                            run = false;
                            listaRun = false;
                        }
                    }else if(w == del){
                        run = false;
                        listaRun = false;
                    }
                }
            }
            highlight = 0;
        }else if(epilegmeno == kath){
            highlight = 0;
            mvwchgat(resaults, 6, getmaxx(resaults)-30, 27, A_NORMAL, 0, NULL);
            for(int i = 0; i < 10; i++){
                wmove(resaults, 9 + i, 3);
                wprintw(resaults, "                                                                                           ");
            }

            wattron(resaults, A_BOLD);
            mvwprintw(resaults, 10, 5, " Id | Ονοματεπώνυμο | Φύλο | Ειδικότητα ");
            wattroff(resaults, A_BOLD);

            while(listaRun){
                if(highlight<0) highlight++;
                if(highlight >= kathigites.size()) highlight--;
                wmove(resaults, 11, 3);
                wrefresh(resaults);
                for(int i = 0; i < kathigites.size(); i++)
                {
                    if(i == highlight) wattron(resaults, A_REVERSE);  
                    wprintw(resaults, "%d | ", kathigites[i].getId());
                    wprintw(resaults, "%s | ", kathigites[i].getOnoma().c_str());
                    wprintw(resaults, "%s | ", kathigites[i].getFylo().c_str());
                    wprintw(resaults, "%s", kathigites[i].getSubject().c_str());
                    wattroff(resaults, A_REVERSE);
                    if(i!=kathigites.size()-1) wmove(resaults, getcury(resaults)+1, 3);
                }
                wrefresh(resaults);
                epilogi = wgetch(resaults);
                switch(epilogi){
                    case KEY_UP: highlight--; break;
                    case KEY_DOWN: highlight++; break;
                    case (int)' ': listaRun = false; mvwchgat(resaults, 11 + highlight, 3, 70, A_NORMAL, 0, NULL); break;
                    default: break;
                }
                if(epilogi == 10){
                    oper w = epilogesAnaz(kath, "", kathigites[highlight].getId(), highlight, resaults, searchBar, catalog);
                    if(w == Epej){
                        if(edit(kath, "", kathigites[highlight].getId(), highlight, resaults, catalog)){
                            run = false;
                            listaRun = false;
                        }
                    }else if(w == del){
                        run = false;
                        listaRun = false;
                    }
                }
            }
            highlight = 0;
        }else if(epilegmeno == math){
            highlight = 0;
            mvwchgat(resaults, 6, getmaxx(resaults)-30, 27, A_NORMAL, 0, NULL);
            for(int i = 0; i < 10; i++){
                wmove(resaults, 9 + i, 3);
                wprintw(resaults, "                                                                                           ");
            }

            wattron(resaults, A_BOLD);
            mvwprintw(resaults, 10, 5, " Id | Περιγραφή | Υπέυθυνος Καθηγητής | Εξάμηνο ");
            wattroff(resaults, A_BOLD);

            while(listaRun){
                if(highlight<0) highlight++;
                if(highlight >= mathimata.size()) highlight--;
                wmove(resaults, 11, 3);
                wrefresh(resaults);
                for(int i = 0; i < mathimata.size(); i++)
                {
                    if(i == highlight) wattron(resaults, A_REVERSE);  
                    wprintw(resaults, "%d | ", mathimata[i].getId());
                    wprintw(resaults, "%s | ", mathimata[i].getDescription().c_str());
                    wprintw(resaults, "%s | ", mathimata[i].getYpkath().c_str());
                    wprintw(resaults, "%d", mathimata[i].getSemester());
                    wattroff(resaults, A_REVERSE);
                    if(i!=mathimata.size()-1) wmove(resaults, getcury(resaults)+1, 3);
                }
                wrefresh(resaults);
                epilogi = wgetch(resaults);
                switch(epilogi){
                    case KEY_UP: highlight--; break;
                    case KEY_DOWN: highlight++; break;
                    case (int)' ': listaRun = false; mvwchgat(resaults, 11 + highlight, 3, 70, A_NORMAL, 0, NULL); break;
                    default: break;
                }
                if(epilogi == 10){
                    oper w = epilogesAnaz(math, "", mathimata[highlight].getId(), highlight, resaults, searchBar, catalog);
                    if(w == Epej){
                        if(edit(math, "", mathimata[highlight].getId(), highlight, resaults, catalog)){
                            run = false;
                            listaRun = false;
                        }
                    }else if(w == del){
                        run = false;
                        listaRun = false;
                    }
                }
            }
            highlight = 0;
        }
        wrefresh(resaults);
        wrefresh(searchBar);
    }

    //telos anazitisis
    wclear(resaults);
    wrefresh(resaults);
    delwin(resaults);
    wclear(searchBar);
    wrefresh(searchBar);
    clear();
    refresh();
}
void newAddition(type whatAdd, foititologio &catalog){
    if(whatAdd == none) return;
    WINDOW * newAdd = newwin(26*LINES/28, 26*COLS/28, LINES/28, COLS/28);
    box(newAdd, 0, 0);
    keypad(newAdd, true);
    string * stoixia;
    string * newInfo;
    gender newFylo = unidentified;
    int highlight = 0;
    int epilogi;
    int n; //θα χρησιμοποιθει για highlight max εκτος των if (εννιαιο block για ολες τις WhatAdd)
    bool run = true;
    vector<string> mathimata;
    if(whatAdd == foit){
        wattron(newAdd, A_BOLD);
        mvwprintw(newAdd, 3, 3, "Παρακαλώ πληκτρολογίστε τα στοιχεία του Φοιτητή που θέλετε να προσθέσετε");
        wattroff(newAdd, A_BOLD);
        wrefresh(newAdd);
        stoixia = new string[5];
        newInfo = new string[3];
        stoixia[0] = "Ονοματεπώνυμο:";
        stoixia[1] = "Φύλο:";
        stoixia[2] = "Εξάμηνο:";
        stoixia[3] = "Μαθήματα:";
        stoixia[4] = "ΑΠΟΘΗΚΕΥΣΗ";
        n = 5; 
    }else if(whatAdd == kath){
        wattron(newAdd, A_BOLD);
        mvwprintw(newAdd, 3, 3, "Παρακαλώ πληκτρολογίστε τα στοιχεία του Καθηγητή που θέλετε να προσθέσετε");
        wattroff(newAdd, A_BOLD);
        wrefresh(newAdd);
        stoixia = new string[6];
        newInfo = new string[4];
        stoixia[0] = "Ονοματεπώνυμο:";
        stoixia[1] = "Κωδικός Πρόσβασης:";
        stoixia[2] = "Φύλο:";
        stoixia[3] = "Ειδικότητα:";
        stoixia[4] = "Μαθήματα:";
        stoixia[5] = "ΑΠΟΘΗΚΕΥΣΗ";
        n = 6;
    }else if(whatAdd == math){
        wattron(newAdd, A_BOLD);
        mvwprintw(newAdd, 3, 3, "Παρακαλώ πληκτρολογίστε τα στοιχεία του Μαθήματος που θέλετε να προσθέσετε");
        wattroff(newAdd, A_BOLD);
        wrefresh(newAdd);
        stoixia = new string[4];
        newInfo = new string[3];
        stoixia[0] = "Περιγραφή:";
        stoixia[1] = "Ύπευθυνος Καθηγητής:";
        stoixia[2] = "Εξάμηνο:";
        stoixia[3] = "ΑΠΟΘΗΚΕΥΣΗ";
        n = 4;
    }
    
    while(run){
        touchwin(newAdd);
        wrefresh(newAdd);
        if(highlight < 0) highlight ++;
        if(highlight >= n) highlight --;
        wmove(newAdd, 6, 3);
        for(int i = 0; i < n; i++){
            if(i == n-1) wmove(newAdd, getcury(newAdd) + 3, 3);
            if(highlight == i) wattron(newAdd, A_REVERSE);
            wprintw(newAdd, stoixia[i].c_str());
            wattroff(newAdd, A_REVERSE);
            if((i == n-2) && ((whatAdd == foit) || (whatAdd == kath)) && (!mathimata.empty())){
                wprintw(newAdd, "Δείτε %d Μαθήματα", mathimata.size());
            }
            if(i != n-1){
                wprintw(newAdd, " ");
                wprintw(newAdd, newInfo[i].c_str());
            }
            if(i != n-1) wmove(newAdd, getcury(newAdd) +1, 3);
        }
        wrefresh(newAdd);
        epilogi = wgetch(newAdd);
        switch(epilogi){
            case KEY_UP: highlight--; break;
            case KEY_DOWN: highlight++; break;
            case (int)' ': run = false; break;
            default: break;
        }
    
        if((epilogi == KEY_RIGHT && highlight == 3) && whatAdd == foit){
            seeMathimata(mathimata, foit);
        }else if((epilogi == KEY_RIGHT && highlight == 4) && whatAdd == kath){
            seeMathimata(mathimata, kath);
        } else if(epilogi == 10 && highlight == n-1){
            //diadikasia apoyhikeusus me if gia whatAdd
            bool err = false;
            if(whatAdd == foit || whatAdd == kath){
                for(int i = 0; i < n-2; i++){
                    if(newInfo[i].empty()){
                        err = true;
                        break;
                    }
                }
                if(mathimata.empty()){
                    err = true;
                }
            }else if(whatAdd == math){
                for(int i = 0; i < n; i++){
                    if(newInfo[i].empty()){
                        err = true;
                        break;
                    }
                }
            }
            
            if(err){
                apotelesma("Όλα τα στοιχεία πρέπει να είναι συμπληρωμένα!");
                wrefresh(newAdd);
            }else if(!err){
                switch(whatAdd){
                    case foit: catalog.newFoititis(to_string(stoi(catalog.foitites.back().getAM()) + 1), newInfo[0], newFylo, stoi(newInfo[2]), mathimata); break;
                    case kath: catalog.newKathigitis(catalog.kathigites.back().getId() +1, newInfo[1], newInfo[0], newFylo, newInfo[3], mathimata); break;
                    case math: catalog.newMathima(catalog.mathimata_ps.back().getId() + 1, newInfo[0], stoi(newInfo[2]), newInfo[1]); break;
                    default: break;
                }
                run = false;
            }
            

        }else if(whatAdd == foit && epilogi == 10){
            if(highlight == 0){
                mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6, 18);
                string neo = gettext(newAdd, 70);
                if(yes_no(LINES/28 + 7, COLS/28 + 3))newInfo[0] = neo;
                else mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
            }else if(highlight == 1){
                mvwprintw(newAdd, 6+ highlight, 9, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 18);
                string neo = gettext(newAdd, 70);
                if(neo == "Ανδρας" || neo == "Άνδρας"){
                    if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3)){
                        newInfo[highlight] = neo;
                        newFylo = male;
                    }else mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
                }else if(neo == "Γυναίκα" || neo == "Γυναικα"){
                    if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3)){
                        newInfo[highlight]= neo;
                        newFylo = female;
                    }else mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
                }else{
                    apotelesma("Λάθος! Εισαγεται Γυναίκα ή Άνδρας");
                }
            }else if(highlight == 2){
                mvwprintw(newAdd, 6+ highlight, 12, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 18);
                string neo = gettext(newAdd, 70);
                bool err = false;
                for (char ch : neo) {
                    if (!isdigit(ch)) err = true;
                }
                if(!err){
                    if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3)){
                        newInfo[highlight] = neo;
                    }else mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
                }else{
                    mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
                    apotelesma("Λάθος! Εισαγεται Αριθμό");
                }
            }else if(highlight == 3){
                mvwprintw(newAdd, 6+ highlight, 13, "                                                                      ");
                wrefresh(newAdd);
                mathimata = addMathimata(foit);
            }
        }else if(whatAdd == kath && epilogi == 10){
            if(highlight == 0){
                mvwprintw(newAdd, 6+ highlight, 18, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6, 22);
                string neo = gettext(newAdd, 70);
                if(yes_no(LINES/28 + 7, COLS/28 + 3))newInfo[0] = neo;
                else mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
            }else if(highlight == 1){
                mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 22);
                string neo = gettext(newAdd, 70);
                if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3))newInfo[highlight] = neo;
                else mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
            }else if(highlight == 2){
                mvwprintw(newAdd, 6+ highlight, 9, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 22);
                string neo = gettext(newAdd, 70);
                if(neo == "Ανδρας" || neo == "Άνδρας"){
                    if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3)){
                        newInfo[highlight] = neo;
                        newFylo = male;
                    }else mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
                }else if(neo == "Γυναίκα" || neo == "Γυναικα"){
                    if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3)){
                        newInfo[highlight] = neo;
                        newFylo = female;
                    }else mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
                }else{
                    mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
                    apotelesma("Λάθος! Εισαγεται Γυναίκα ή Άνδρας");
                }
            }else if(highlight == 3){
                mvwprintw(newAdd, 6+ highlight, 15, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 22);
                string neo = gettext(newAdd, 70);
                if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3))newInfo[highlight] = neo;
                else mvwprintw(newAdd, 6+ highlight, 22, "                                                                      ");
            }else if(highlight == 4){
                mvwprintw(newAdd, 6+ highlight, 13, "                                                                      ");
                mathimata = addMathimata(kath);
            }
        }else if(whatAdd == math && epilogi == 10){
            if(highlight == 0){
                mvwprintw(newAdd, 6+ highlight, 14, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6, 24);
                string neo = gettext(newAdd, 70);
                if(yes_no(LINES/28 + 7, COLS/28 + 3))newInfo[0] = neo;
                else mvwprintw(newAdd, 6+ highlight, 24, "                                                                      ");
            }else if(highlight == 1){
                mvwprintw(newAdd, 6+ highlight, 24, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 24);
                string neo = gettext(newAdd, 70);
                if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3))newInfo[highlight] = neo;
                else mvwprintw(newAdd, 6+ highlight, 24, "                                                                      ");
            }else if(highlight == 2){
                mvwprintw(newAdd, 6+ highlight, 12, "                                                                      ");
                wrefresh(newAdd);
                wmove(newAdd, 6 + highlight, 24);
                string neo = gettext(newAdd, 70);
                bool err = false;
                for (char ch : neo) {
                    if (!isdigit(ch)) err = true;
                }
                if(!err){
                    if(yes_no(LINES/28 + 7 + highlight, COLS/28 + 3)){
                        newInfo[highlight] = neo;
                    }else mvwprintw(newAdd, 6+ highlight, 24, "                                                                      ");
                }else{
                    apotelesma("Λάθος! Εισαγεται Αριθμό");
                }
            }
        }
    
    }

    delete[] stoixia;
    wclear(newAdd);
    wrefresh(newAdd);
    delwin(newAdd);
}

int main(void) {
    setlocale(LC_ALL, "");
    foititologio catalog;
    /*
    if(catalog.foitites.empty()){
        vector<string> mathFoit = {"Σχεδίαση και Ανάλυση Αλγορίθμων", "Πιθανότητες και Στατιστική", "Μαθηματική ανάλυση ΙΙ", "Αντικειμενοστρεφής Προγραμματισμός", "Ψηφιακή Σχεδίαση", "Θεωρία Κυκλωμάτων"};
        vector<string> mathKath = {"Γραμμική Άλγεβρα", "Διακριτά Μαθηματικά", "Πιθανότητες και Στατιστική"};
        catalog.newFoititis("2539007", "Χρήστος Τσαλικης", male, 2, mathFoit);
        catalog.newKathigitis(catalog.kathigites.back().getId() + 1, "mparlasUniwa12345!", "Κωνσταντινος Μπαρλας", male, "Μαθηματικά", mathKath);
        catalog.newFoititis("25390001", "Νικολετα Παπαδημητριου", female, 4, mathFoit);
        vector<string> MathMel = {"Προγραμματισμός Υπολογιστών", "Αντικειμενοστρεφής Προγραμματισμός"};
        catalog.newKathigitis(123456, "meletiou1234@", "Γεωργιος Μελετιου", male, "Προγραμματισμος", MathMel);
    }
    */
    initscr();
    bool run = true;
    bool scrrun = true;
    
    WINDOW * searchBar = newwin(3, 60, 7, COLS/2 - 30);
    string epiloges_elements[5] = {" Αναζήτηση ", " Προσθήκη ", " Μαζική αποστολή e-mail "," Μαζική διαγραφή ", "ΕΞΟΔΟΣ"};
    int epilogi;
    int highlight = 0;
    int epilegmeno = -10;
    char c_search[100];
    string search;
    while(run){
        mvwin(searchBar, 7, COLS/2 - 30);
        scrrun = true;
        attron(A_BOLD);
        mvprintw(2, COLS/2 - 35, "Γεια σας, Αναζητήστε Φοιτητές, Καθηγητές και Μαθήματα στο φοιτιτολόγιο!");
        attroff(A_BOLD);
        keypad(stdscr, true);
        refresh();
        box(searchBar, 0, 0);
        wrefresh(searchBar);
        curs_set(0);
        noecho();
        wattrset(searchBar, A_DIM);

        while(scrrun){
            attron(A_BOLD);
            mvprintw(2, COLS/2 - 35, "Γεια σας, Αναζητήστε Φοιτητές, Καθηγητές και Μαθήματα στο φοιτιτολόγιο!");
            attroff(A_BOLD);
            epilegmeno = -10;
            search.clear();
            mvwprintw(searchBar, 1, 2, "Πληκτρολογίστε ΑΜ/Id, Ονοματεπώνυμο, ειδικότητα η εξάμηνο");
            if(highlight<0) highlight++;
            if(highlight>4) highlight--;
            move(4, COLS/2 - 37);
            for(int i = 0; i < 5; i++)
            {
                if(i == highlight) attron(A_REVERSE);  
                printw(epiloges_elements[i].c_str());
                attroff(A_REVERSE);
                if(i!=4) printw("|");
            }
            refresh();
            touchwin(searchBar);
            wrefresh(searchBar);
            epilogi = getch();
            switch(epilogi){
                case KEY_LEFT: if(highlight > 0) highlight--; break;
                case KEY_RIGHT: highlight++; break;
                case KEY_DOWN: highlight = -1; break;
                default: break;
            }
            
            if(epilogi == 10){
                epilegmeno = highlight;
            }
            if(highlight == -1 || epilegmeno == 0){
                wattrset(searchBar, A_NORMAL);
                wrefresh(searchBar);
                scrrun = false;
                wmove(searchBar, 1, 2);
                curs_set(1);
                keypad(stdscr, true);
                keypad(searchBar, true);
                wrefresh(searchBar);

                int i = wgetch(searchBar);
                wmove(searchBar, 1, 1);
                noecho();
                ungetch(i);
                wprintw(searchBar, "                                                          ");
                wmove(searchBar, 1, 2);
                refresh();
                wrefresh(searchBar);

                search = gettext(searchBar, 56);
                
                anazitisi(search, searchBar, catalog);
            }else if(epilegmeno == 1){
                type whatAdd = epiloges(highlight, true);
                if(whatAdd != none) newAddition(whatAdd, catalog);
                clear();
                touchwin(stdscr);
                refresh();
            }else if(epilegmeno == 2){
                apotelesma("Προσοχή, αυτο θα στείλει e-mail σε όλους!!!");
                refresh();
                wrefresh(searchBar);
                type whatSend = epiloges(highlight, false);
                if(whatSend != none){
                    if(yes_no(5 ,COLS/2 - 2)){
                        switch(whatSend){
                            case foit: touchwin(stdscr); refresh(); touchwin(searchBar); wrefresh(searchBar); apotelesma("Αποστάλθηκε Mail σε όλους τους φοιτητές"); break;
                            case kath: touchwin(stdscr); refresh(); touchwin(searchBar); wrefresh(searchBar); apotelesma("Αποστάλθηκε Mail σε όλους τους καθηγητές"); break;
                            case math: break;
                            case none: break;
                            default:break;
                        }
                    }
                    clear();
                }
                
            }else if(epilegmeno == 3){
                apotelesma("Προσοχή, αυτο θα σβήσει ολες τις καταχωρήσεις!!!");
                refresh();
                wrefresh(searchBar);
                type whatDel = epiloges(highlight, false);
                if(whatDel != none){
                    if(yes_no(5 ,COLS/2 + 23)){
                        switch(whatDel){
                            case foit: touchwin(stdscr); refresh(); touchwin(searchBar); wrefresh(searchBar); catalog.foitites.clear(); apotelesma("ΔΙΑΓΡΑΦΤΗΚΑΝ ΟΛΟΙ ΟΙ ΦΟΙΤΗΤΤΕΣ!"); break;
                            case kath: touchwin(stdscr); refresh(); touchwin(searchBar); wrefresh(searchBar); catalog.kathigites.clear(); apotelesma("ΔΙΑΓΡΑΦΤΗΚΑΝ ΟΛΟΙ ΟΙ ΚΑΘΗΓΗΤΕΣ"); break;
                            case math: touchwin(stdscr); refresh(); touchwin(searchBar); wrefresh(searchBar); catalog.mathimata_ps.clear(); apotelesma("ΔΙΑΓΡΑΦΤΗΚΑΝ ΟΛΑ ΤΑ ΜΑΘΗΜΑΤΑ!"); break;
                            case none: break;
                            default: break;
                        }
                    }
                    clear();
                }
                
            }else if(epilegmeno == 4){
                run = false;
                scrrun = false;
            } 
            wrefresh(searchBar);
        }
    }
    
    cout << "====== ΛΗΞΗ ΠΡΟΓΡΑΜΜΑΤΟΣ ΚΑΙ ΑΠΟΘΗΚΕΥΣΗ ΤΟΥ ΚΑΤΑΛΟΓΟΥ ======" << search;
    delwin(searchBar);
    endwin();
    return 0;
}   