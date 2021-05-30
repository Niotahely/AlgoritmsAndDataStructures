#include "genogram.h"
using namespace genogram;



/*
===================================================
|                     STRUCT                      |
===================================================
*/

// Mezzo arco, non tiene il nodo sorgente
struct halfEdgeNode {

  nominative label;    /* etichetta */ 
  Weight weight;       /* peso dell'arco */
  halfEdgeNode* next;  /* puntatore al mezzo arco successivo */
};

struct data
{
    int DD,MM,YYYY;
};



struct genogram::PersonId /* dati essenziali di una persona all-interno del genogramma */
{      
    
    nominative nome ;
    nominative cognome ;
    char sesso ;
    data data_nascita;
    data data_morte;

    // relazioni 
    nominative mother , father , inCoppia , figlio;

    halfEdgeNode *adjList;      /* puntatore -> liste di adiacenza */
    PersonId *next;
    bool visited ;      /* ci servira' per tener conto se : una persona e' gia presente all-interno del genogramma */
};

halfEdgeNode * const emptyEdge =  NULL;





/********************************************************************************************************************/

/*
===================================================
|                   FUNZIONI                      |
|                       PRINCIPALI                |
===================================================
*/


bool genogram ::addPerson (nominative n /* nome */, nominative c /* cognome */, char s /* sesso */, data dtNA /*data di nascita */, genog& p )
{
    char answr ;

    if (isPersonInGenog(n,c,p))
    {
        return false ; // La persona e' gia presente all' interno del genogramma
    }
    // aggiungi la nuova persona in testa
    
    genog v = new PersonId;

    v->nome = n ;
    v->cognome = c;
    v->sesso = s;
    v->data_nascita.DD = dtNA.DD ;
    v->data_nascita.MM = dtNA.MM ;
    v->data_nascita.YYYY = dtNA.YYYY ;
    
    /* chiediamo in fase di compilazione dell-id della persona se volesse aggiungere anche la data di morte */
    cout << " vuoi aggiungere la data di morte di " << n << " " << c << " ? " <<endl ;
    cout << " [Y / n] " << endl ;
    cin >> answr ;
    if(answr == 'y'|| answr == 'Y' ) {
        
        cout <<" giorni : \n";
        cin >> v->data_morte.DD;
        

        cout << " mese : \n";
        cin >> v->data_morte.MM ;
    
        cout << " anno : \n";
        cin >> v->data_morte.YYYY ;
     
     if (CheckDate(v->data_morte))
     {
         if ( v->data_morte.YYYY < v->data_nascita.YYYY)
        {
            return dataNASCITA_MAGGIORE_dataMORTE ;
        }
     }
     
        
        
    }


    v->adjList = emptyEdge ;
    v->visited = false ;

       if (genogram::isEmpty(p))
       {
           p = v ;
           v->next = emptyGenog;
       }else
       {
          v->next = p ;
          p = v ;
       }
           
 return true ;
 
}

/*************************************************************************************/


 /* Funzione che crea una relazione di coppia tra due persone 
 
    NOTA : n == nome & c == cognome */
bool genogram::They_Like_each_other ( nominative from_n,nominative from_c, nominative to_n ,nominative to_c ,genog& p)
{
    // 1. evito la formazione di una relazione (arco) tra una persona e essa stessa (evito che si formi un cappio)
    if ( from_n == to_n && from_c == to_c)  
        return CAPPIO ;
    
    //2. verifico che le due persone siano presenti nel genogramma
    if (isPersonInGenog(from_n,from_c,p)==PERSONA_CERCATA_INESISTENTE || isPersonInGenog(to_n,to_c,p) == PERSONA_CERCATA_INESISTENTE)
    {
        return PERSONA_CERCATA_INESISTENTE;
    }

    // 3. La relazione tra le due persone non deve gia' esistere
    if(isRelInGenog(from_n,from_c,to_n,to_c,p) == REL_GIA_PRESENTE || isRelInGenog(to_n,to_c,from_n,from_c,p) == REL_GIA_PRESENTE)
    {
        return REL_GIA_PRESENTE;
    }

    /* controllo validita' del genogramma : i genitori devono essere di due sessi diversi*/
    PersonId * herId = getPerson(from_n,p);
    PersonId * himId = getPerson(to_n,p);

    if (herId->sesso == himId->sesso)
    {
        return GENITORI_HANNO_SESSO_UGUALE ;
    }
    
    
    // ora che abbiamo verificato tutto , possiamo formare la coppia
    RelationLink(from_n,from_c,to_n,to_c,p);
    RelationLink(to_n,to_c,from_n,from_c,p);
    return OK;
}



/*************************************************************************************/

/*funzione che in base associa un figlio (chld = child) ad il genitore (prnt = parent) , che in base al sesso di quest' ultimo sara la madre o il padre */

bool genogram ::linkParentToChild( nominative prnt_n , nominative prnt_c ,  nominative chld_n , nominative chld_c , genog& p)
{
    // verifico che il genitore e il figlio siano presenti all'interno del genogramma
    if (isPersonInGenog(prnt_n,prnt_c,p) == PERSONA_CERCATA_INESISTENTE || isPersonInGenog(chld_n,chld_c,p) == PERSONA_CERCATA_INESISTENTE)
    {
        return PERSONA_CERCATA_INESISTENTE;
    }

    // La relazione tra le due persone non deve gia' esistere
    if(isRelInGenog(prnt_n,prnt_c,chld_n,chld_c,p) == REL_GIA_PRESENTE || isRelInGenog(chld_n,chld_c,prnt_n,prnt_c,p) == REL_GIA_PRESENTE)
    {
        return REL_GIA_PRESENTE;
    }
    
    
    PersonId * IdPrnt = getPerson (prnt_n,p);
    PersonId * IdChld = getPerson (chld_n,p);
    
    // verifico che i genitore siano piu' grandi del figlio
    // Cosi sono sicuro che la coppia di genitori , sia effettivamente la piu grande rispetto ai figli che verranno
    if (IdPrnt->data_nascita.YYYY > IdChld->data_nascita.YYYY)
    {
        return FIGLIO_PIU_VECCHIO_DEL_GENITORE ;
    }
 
     /* creo la relazione tra il genitore e il figlio */
    RelationLink(prnt_n,prnt_c,chld_n,chld_c,p);
    RelationLink(chld_n,chld_c,prnt_n,prnt_c,p);
    
    
    /* Definiamo se la relazione tra genitore - figlio , e' con la madre o con il padre*/
    if (IdPrnt->sesso == 'M'||IdPrnt->sesso == 'm'  ) IdChld->mother = IdPrnt->nome;
    else if (IdPrnt->sesso == 'F'||IdPrnt->sesso == 'f')IdChld->father = IdPrnt->nome;

    /* Definiamo chi e' il figlio */
    IdPrnt->figlio = IdChld->nome ;

    return OK;
}


/*************************************************************************************/

/* Funzione che collega a una coppia ( mothr = mother e fathr = father) a un figlio (chld = child)*/
ERROR genogram ::AddRelChildToCouple(nominative mothr_n , nominative mothr_c , nominative fathr_n , nominative fathr_c ,  nominative chld_n , nominative chld_c , genog& p)
{
    /* 1. verifichiamo che la relazione tra madre e padre esista gia' */
    if(isRelInGenog(mothr_n,mothr_c,fathr_n,fathr_c,p) == REL_ASSENTE && isRelInGenog(fathr_n,fathr_c,mothr_n,mothr_c,p)==REL_ASSENTE)

        return REL_ASSENTE;
    

    /* 2. Verifichiamo che il figlio esista */
    if (isPersonInGenog(chld_n,chld_c,p) == PERSONA_CERCATA_INESISTENTE) return PERSONA_CERCATA_INESISTENTE;

    /*3. ora che abbiamo verificato che non ci siano errori, possiamo procedere con l'unione*/
    linkParentToChild(mothr_n,mothr_c,chld_n,chld_c,p);
    linkParentToChild(fathr_n,fathr_c,chld_n,chld_c,p);
    return OK ;
    
}



/*************************************************************************************/

/* funzione che elimina una persona dal genogramma e nel caso quest-ultima avesse dei figli gli elimina*/
ERROR genogram::DeletePerson(nominative n , nominative c , genog& p)
{

    /* verifichiamo che sia presente all'interno del genogramma */
    if( isPersonInGenog(n,c,p) == PERSONA_CERCATA_INESISTENTE) return PERSONA_CERCATA_INESISTENTE;

    
       PersonId * nPerson = getPerson (n,p);
       
       /*se la persona che vogliamo eliminare ha un figlio o piu , gli elimineremo*/
       while (nPerson->figlio != strEmpty)
       {
           PersonId * ChildToDelete = getPerson(n,p);
           DeletePerson(ChildToDelete->nome, ChildToDelete->cognome,p);
       }

       /* eliminiamo la persona scelta */
       delete nPerson;
        
        return OK ;


}


/********************************************************************************************************************/

 /* funzione che verifica se tutto il genogramma e' connesso */
bool genogram ::GenogIsConnected ( genog& p)
{

    
}





/********************************************************************************************************************/

/*
===================================================
|                   FUNZIONI                      |
|                       AUSILIARIE                |
===================================================
*/


/*************************************************************************************/


/* Verifica se il genogram e' vuoto oppure no */
bool genogram::isEmpty( const genog &p)
{
    return ( p == emptyGenog);
}

/*************************************************************************************/

/*  restituisce , se esiste , il nominativo di una persona */
PersonId* getPerson(nominative n , const genog& p) 
{
    for ( genogram::genog i = p; p != emptyGenog; i = i->next)
    {
        if( i->nome == n) return i; // esiste
    }
    return emptyGenog; // non esiste
    
}

/*************************************************************************************/

/* verifica se la persona (n + c ) e' gia presente all' interno del genogramma */
ERROR isPersonInGenog( nominative n , nominative c , const genog& p) 
{
    PersonId * nPerson = getPerson (n,p);
    if (getPerson(n,p) == emptyGenog)       /* verifico che getPerson non riturni emptyGenog */
    {
        return GENOG_VUOTO;
    }
    else  nPerson->visited; return OK;
}


/*************************************************************************************/

/* crea un genogram vuoto */
genog genogram::createEmptyGenog()
{
    return emptyGenog;
}

/*************************************************************************************/

/* aggiunge una "relzione a meta' " . questo ci aiutera' per la realizzazione delle funzioni :
 - addRelMother();
 - addRelFather();
 - They_Like_each_other()
 
  NOTA : n == nome & c == cognome */

void RelationLink( nominative from_n,nominative from_c, nominative to_n ,nominative to_c , genog& p)
{
    halfEdgeNode *e = new halfEdgeNode;
    e->label = to_n;    /* per comodita' settiamo l'etichetta con il nome della persona . Dato che il nome e' unico e non ci possono essere omonimi nel genogramma */
    

    PersonId * nPerson = getPerson(from_n,p);

    if (nPerson->adjList == emptyEdge)
    {
        nPerson->adjList = e ;
        e->next = emptyEdge;
    }
    else
    {
        e->next = nPerson->adjList;
        nPerson->adjList = e ;
    }
    nPerson->inCoppia = to_n +" "+ to_c ; /* qui diciamo che la persona indicata con from _n+c e' in coppia con la persona to_n+c*/

}




/*************************************************************************************/

/* Funzione che verifica se la relazione tra due persone esista gia' , oppure no */
bool isRelInGenog(nominative from_n,nominative from_c, nominative to_n ,nominative to_c , genog& p)
{
    PersonId * nPerson = getPerson(from_n,p) ;
    if (nPerson == emptyGenog)  /* verifichiamo se nPerson non sia vuoto */
    {
        return GENOG_VUOTO ;
    }

    /*      Verifichiamo se nella lista di nPerson e' presente il nome di 'to'    */
    for (halfEdgeNode* n = nPerson->adjList; n != emptyEdge; n = n->next) {
    if (n->label == to_n ) return REL_GIA_PRESENTE;    /* la persona che ha l-etichetta == nome dei 'to' e' stata trovata */
  }
 return REL_ASSENTE;
    
}

/*************************************************************************************/
ERROR CheckDate(data& d)
{
    if (d.YYYY < 0) // l-anno non puo' essere minore di 0
    {
        return DATA_ERRATA_ANNI ;
    }

    if (d.MM < 1|| d.MM > 12) // verifico che il mese sia compreso tra 1 e 12
    {
        return DATA_ERRATA_MESI ;
    }

    if (d.MM == 2) 
    {
        if (d.YYYY % 4 == 0)
       {
        
        
        if (d.DD > 29 || d.DD < 0)
        {
            return DATA_ERRATA_GIORNI;
        }
        else if (d.DD > 28 || d.DD < 0 )
        {
            return DATA_ERRATA_GIORNI ;
            
        }
        }
        
    }

    else if (d.MM == 1 || d.MM == 5 || d.MM ==1 || d.MM == 7 || d.MM == 8 || d.MM ==10  )
    {
        if (d.DD > 31 || d.DD < 0)
        {
            return DATA_ERRATA_GIORNI;
        }
        
    }

    else if (d.DD > 30 || d.DD < 0)
    {
        return DATA_ERRATA_GIORNI ;
    }
    
    
    
    return OK ;
    
    
}


/*************************************************************************************/

/* funzione che stampa il genogramma */
  void printGenog( genog& p)
  {
      for (genogram::genog i = p; i != emptyGenog; i = i->next)
    {
        cout << "===================================="<< endl;
        cout << "NOME : "    << i->nome <<endl;
        cout << "COGNOME : " << i->cognome << endl;
        cout << "NASCITA : " << i->data_nascita.DD << "-"<<i->data_nascita.MM << "-"<< i->data_nascita.YYYY << endl;
        cout << "MORTE : "   << i->data_morte.DD << "-" << i->data_morte.MM << "-" << i->data_morte.YYYY << endl;
        cout << "SESSO : "   << i->sesso <<endl ;
        cout << "PADRE : "   << i->father << endl ;
        cout << "MADRE : "   << i->mother << endl ;
        cout << "IN COPPIA CON : " << i->inCoppia << endl ;
        cout << "FIGLI : "   << i->figlio << endl ;
        cout <<"====================================="<< endl;
    }
  }