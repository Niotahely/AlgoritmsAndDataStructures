#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream> 
#include <string>
#include "list-array.h"

using namespace std ;

/* creiamo un namespace : genogram */

namespace genogram {





    typedef int Weight;            /* Peso  */

    typedef string nominative;     /* nome e cognome */

    struct PersonId;               /* stuct che verra poi definita all' interno del file genogram.cpp */

    typedef PersonId* genog;       /* il genogramma e' identificato dal puntatore al primo PersonId */

    const genog emptyGenog = NULL;

    string strEmpty = NULL;




    /*
    =================================================================
    |                     ~ CODICI DI ERRORE ~                      |
    =================================================================
    */


   enum ERROR {
              /* errori che spuntano fuori in caso di :*/

       GENOG_VUOTO , /* genogramma vuoto */
       ERRORE_LETTURA_FILE , /* il file non e' stato letto correttamente */
       CAPPIO , /*  nel caso di un cappio*/
       PERSONA_CERCATA_INESISTENTE , /* la persona cercata non e' presente nel genogramma */
       REL_GIA_PRESENTE , /* la relzaione tra due persone c'e gia' */
       REL_ASSENTE, /* relzione assente */
       GENITORI_HANNO_SESSO_UGUALE , /* i genitori hanno lo stesso sesso */
       DATA_ERRATA_GIORNI ,  /* la data inserita presenta un errore nel giorno*/
       DATA_ERRATA_MESI ,    /* la data inserita presenta un errore nel mese */
       DATA_ERRATA_ANNI,     /* la data inserita presenta un errore nell' anno*/
       dataNASCITA_MAGGIORE_dataMORTE ,   /* la data di nascita non puo' essere maggiore di quella della morte */
       FIGLIO_PIU_VECCHIO_DEL_GENITORE , /* il figlio non puo' essere piu' vecchio del genitore */
       GENOGRAMMA_DISCONNESSO , /* il genogramma e' disconnesso */

       OK, /* Non ci sono stati errori */


   };



    /*
    =================================================================
    |                          ~ FUNZIONI ~                         |
    =================================================================
    */

    bool isEmpty( const genog& );               /* verifica se il genogramma e' vuoto o no */

    genog createEmptyGenog();                   /* restituisce un genogramma vuoto */

    bool addPerson( nominative , nominative , char , data , genog&  );     /* aggiunge una persona nel Genogramma . Fallisce se e' gia presente. */

    bool linkParentToChild( nominative , nominative ,  nominative , nominative , genog& ) ;    /* collega la madre al figlio . Fallisce se il collegamento e' gia presente OPPURE collega il padre al figlio . Fallisce se il collegamento e' gia presente */  
    
    bool They_Like_each_other(  nominative ,nominative , nominative  ,nominative  ,genog& );  /* collega due persone per formare una coppia . Fallisce se sono gia' una coppia */

    ERROR AddRelChildToCouple( nominative , nominative , nominative , nominative ,  nominative , nominative , genog& ) ;  /* collega una coppia a un figlio . fallisce se il collegamento e' gia presente */

    ERROR DeletePerson( nominative , nominative , genog&  );      /* Cancella una persona .
                                                                  Bisogna verificare che sia presente , altrimenti fallisce */
    
    bool GenogIsConnected ();         /* verifica che il genogramma sia connesso */

   
}
    void printGenog( genog& );            /* stampa il genogramma */


