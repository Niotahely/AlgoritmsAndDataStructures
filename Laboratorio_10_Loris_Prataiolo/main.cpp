
/* Laboratorio_10    Studente : Loris Prataiolo     Mat : 4632180  */

#include "genogram.cpp"



int menu (){   /* Funzione che implementa la parte grafica del ' menu-di-scelta ' che visualizzara' l' utente all'avvio del programma .
                  Restituisce un valore <int> il quale verra' usato nello switch per l'esecuzione della funzione scelta . */

    int scelta = -1 ;

    while (true)
    {
        cout << "======================================================="<<endl;
        cout << "|                         ~ Menu ~                    |"<<endl;
        cout << "======================================================="<<endl;
        cout << " "<< endl;
        cout << " "<< endl;
        cout << " 1) Leggi un Genogramma da file"       << endl;
        cout << " 2) inserisci una persona nel Genogramma"          << endl;
        cout << " 3) definisci una relazione Genitore - figlio"     << endl;
        cout << " 4) definisci una relazione di coppia     "        << endl;
        cout << " 5) definisci una relazione di coppia  - figlio/a (famiglia)  " << endl;
        cout << " 6) Cancella una persona dal genogramma"           << endl;
        cout << " 7) Controllo la validita' del genogramma"        << endl;
        cout << " 8) Stampa Genogramma"                            << endl;
        cout << " 0) Uscita"                                        << endl;
        cout << " "<< endl;
        cout << " "<< endl;
        cout << " Inserisci la tua scelta e premi Enter ( Invio )"  << endl;
        
        cin >> scelta;
        if (scelta < 0 ||scelta >11)
        {
            cout << " Scelta inesistente " << endl;
            cin.clear();
            cin.ignore();   // queste 4 ultime stringhe servono a ovviare a un bug di glibc
            clearerr(stdin);
            continue;
        }
        return scelta;
    }
}

/**********************************************************************************************************************/


/**********************************************************************************************************************/

int main (){

    int scelta;

    // dati per la definizione di una persona 
    char answr , sesso ; 
    nominative n , c ;
    data data_nascita ;

    // dati per la definizione genitore e figlio
    nominative prnt_n ,prnt_c ,  chld_n , chld_c ;  

    //dati per la definizione di una coppia 
    nominative her_n,her_c, him_n , him_c ;
    
    genog p = createEmptyGenog();
    
    while (true)
    {
        scelta = menu();

        if (scelta == 0)
        {
            cout << " Fine Programma "<< endl ;
        }

        switch (scelta)
        {
        case 1 /*inserimento del Genogramma da file */:
            /* code */
            break;


        case 2 /*inserimento di una persona nel Genogramma"*/:
            
            cout << "===================================" << endl ;
            cout << "| inserisci i dati di una persona |" << endl ;
            cout << "===================================" << endl ;
            cout << "NOME : " ; cin >> n ;
            cout << "COGNOME : "; cin >> c ;
            cout << "NASCITA : \n:" ;

               cout << " giorni : \n";
               cin >> data_nascita.DD  ;
               cout << " mese : \n";
               cin >> data_nascita.MM;
               cout << " anno \n" ;
               cin >> data_nascita.YYYY;

            cout << "SESSO : "; cin >> sesso ;
            
            if (CheckDate(data_nascita))
            {
                addPerson(n,c,sesso ,data_nascita,p);
            }
            
           
            
            break;


        case 3 /*Relazione Madre - Figlio/a*/:
            
            cout << "===================================" << endl ;
            cout << "|    Relazione Genitore - Figlio/a   |" << endl ;
            cout << "===================================" << endl ;
            cout << " Genitore (nome e cognome ) : " ; cin >> prnt_n >> prnt_c ;
            cout << " Figlio   (nome e cognome ) : " ; cin >> chld_n >> chld_c ;
            
            linkParentToChild(prnt_n,prnt_n,chld_n,chld_c,p);
            break;


        case 4 /*inserimento di della relazione coppia*/:
            
             
            cout << "===================================" << endl ;
            cout << "|       formiamo una coppia       |" << endl ;
            cout << "===================================" << endl ;
            cout << " Donna    (nome e cognome ) : " ; cin >> her_n >> her_c ;
            cout << " Uomo     (nome e cognome ) : " ; cin >> him_n >> him_c ;

            They_Like_each_other(her_n,her_c, him_n , him_c,p);
            break;


        case 5 /*inserimento della relazione coppia - figlio/a"*/:
            
            cout << "===================================" << endl ;
            cout << "|  Relazione coppia - figlio /a   |" << endl ;
            cout << "===================================" << endl ;
            cout << " Madre   (nome e cognome ) : " ; cin >> her_n >> her_c ;
            cout << " Padre   (nome e cognome ) : " ; cin >> him_n >> him_c ;
            cout << " Figlio  (nome e cognome ) : " ; cin >> chld_n >> chld_c ;

            AddRelChildToCouple(her_n,her_c, him_n , him_c,chld_n,chld_c,p);


            break;



        case 6 /*Cancella una persona dal genogramma*/ :
            cout << "===================================" << endl ;
            cout << "|  Eliminazione di una Persona    |" << endl ;
            cout << "===================================" << endl ;
            cout << "Nome : " ; cin >> n ;
            cout << "Cognome : "; cin >> c ;

            DeletePerson(n,c,p);
            break;


        case 7 /*Controllo se il genogramma e' totalmente connesso */ :
            /* code */
            break;


        case 8/*Stampa Genogramma*/ :
           printGenog(p);
        

        }
        
    }
    
    return 0;
}