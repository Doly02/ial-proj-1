/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/*           Daniel Dolejška, září 2022                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,
**      DLL_Dispose ........ zrušení všech prvků seznamu,
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,
**      DLL_InsertLast ..... vložení prvku na konec seznamu,
**      DLL_First .......... nastavení aktivity na první prvek,
**      DLL_Last ........... nastavení aktivity na poslední prvek,
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,
**      DLL_GetLast ........ vrací hodnotu posledního prvku,
**      DLL_DeleteFirst .... zruší první prvek seznamu,
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,
**      DLL_Next ........... posune aktivitu na další prvek seznamu,
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
 * uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c206.h"

bool error_flag;
bool solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error(void) {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = true;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if (NULL == list)
	{
		return;
	}
	else 
	{
		list->activeElement = NULL;
		list->firstElement = NULL;
		list->lastElement = NULL;
	}
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	DLLElementPtr ActualElement = list->firstElement;
	
	while (NULL != list->firstElement)
	{
		ActualElement = list->firstElement;
		// Posunuti ukazatele na novy prvni prvek 
		list->firstElement = ActualElement->nextElement; 

		// Uvolneni aktualniho prvku 
		free(ActualElement);
	}
	//
	list->activeElement = NULL;
	list->firstElement = NULL;
	list->lastElement = NULL;
	
	
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst( DLList *list, int data ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */

	DLLElementPtr NewElement = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (NULL == NewElement)
	{
		DLL_Error();
		return;
	}
	NewElement->data = data;
	NewElement->nextElement = list->firstElement;

	// Aktualizace předchozího prvku původního prvního prvku
    if (list->firstElement != NULL) {
        list->firstElement->previousElement = NewElement;
    }

    list->firstElement = NewElement;

    // Aktualizace posledního prvku, pokud je seznam prázdný
    if (NULL == list->lastElement) {
        list->lastElement = NewElement;
    }
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast( DLList *list, int data ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	DLLElementPtr NewElement = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (NULL == NewElement)
	{
		DLL_Error();
		return;
	}
	NewElement->data = data; 
	NewElement->nextElement = NULL; 
	
	// Pokud se seznam prazdny
	if (NULL == list->lastElement)
	{
		// Prvek se stava prvnim i poslednim
		list->lastElement = NewElement;
		list->firstElement = NewElement;
		// A neexistuje zadny naslednik
		NewElement->previousElement = NULL; 
	}
	else // Pokud vsak prvek neni prvni, je potreba provazat stary posledni
	{	 // s novym poslednim a aktualizovat posledni element v listu

		NewElement->previousElement = list->lastElement; 
		list->lastElement->nextElement = NewElement; 
		list->lastElement = NewElement;
	}
}
/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	list->activeElement = list->firstElement;
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	list->activeElement = list->lastElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst( DLList *list, int *dataPtr ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	if (NULL == list->firstElement)
	{
		DLL_Error();
		return;
	}
	*dataPtr = list->firstElement->data;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast( DLList *list, int *dataPtr ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if (NULL == list->lastElement)
	{
		DLL_Error();
		return;
	}
	*dataPtr = list->lastElement->data;
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */



void DLL_DeleteFirst( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if (NULL == list || NULL == list->firstElement)
	{
		return;
	}
	else
	{
		DLLElementPtr TempElement;
		TempElement = list->firstElement;
		
		// Prvek muze byt zaroven aktivnim prvkem 
		if (TempElement == list->activeElement)
		{
			list->activeElement = NULL;
		}
		// Prvek muze byt zaroven poslednim prvkem (list o jednom prvku)
		if (TempElement == list->lastElement)
		{
			list->firstElement = NULL;
			list->lastElement = NULL;
		}
		else
		{
			list->firstElement = TempElement->nextElement;
			list->firstElement->previousElement = NULL;
				
		}
		free(TempElement);
	}
	
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast( DLList *list ) {
	// solved = false; /* V případě řešení, smažte tento řádek! */

	// Pokud neexistuje ani prvni element tak se rovnou vratim 
	if (NULL == list->firstElement || NULL == list)
	{
		return;
	}
	else 
	{
		DLLElementPtr TempElement;
		TempElement = list->lastElement;
		
		// Prvek muze byt zaroven aktivnim prvkem 
		if (TempElement == list->activeElement)
		{
			list->activeElement = NULL;
		}
		// Pokud je posledni prvek zaroven prvnim prvkem 
		if (TempElement == list->firstElement)
		{
			list->firstElement = NULL;
			list->lastElement = NULL;
		}
		else
		{
			list->lastElement = TempElement->previousElement;
			list->lastElement->nextElement = NULL;
		}
		free(TempElement);
	}

}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if (NULL == list->activeElement || list->lastElement == list->activeElement)
	{
		return;
	}
	else
	{
		// Ulozeni si prvku za aktivnim prvkem
		DLLElementPtr TempElement;
		TempElement = list->activeElement->nextElement;

		// Pokud je TempElement poslednim prvkem v seznamu
		if (TempElement == list->lastElement)
		{
			// Poslednim prvkem se stava aktivni element
			list->lastElement = list->activeElement;
			// A stava se poslednim 
			list->activeElement->nextElement = NULL;
		}
		else 
		{
			list->activeElement->nextElement = TempElement->nextElement;
			TempElement->nextElement->previousElement = list->activeElement;
		}
		free(TempElement);
	}
	
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */

	if (NULL == list->activeElement || list->firstElement == list->activeElement)
	{
		return;
	}
	else
	{
		// Ulozeni si prvku za aktivnim prvkem
		DLLElementPtr TempElement;
		TempElement = list->activeElement->previousElement;

		if (TempElement == list->firstElement)
		{
			list->firstElement = list->activeElement;
			list->activeElement->previousElement = NULL;
		}
		else
		{
			list->activeElement->previousElement = TempElement->previousElement;
			TempElement->previousElement->nextElement = list->activeElement;
		}
		free(TempElement);
	}
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter( DLList *list, int data ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */

	if (NULL == list->activeElement)
	{
		return;
	}
	else
	{
		DLLElementPtr NewElement = (DLLElementPtr)malloc(sizeof(struct DLLElement));
		if (NULL == NewElement)
		{
			DLL_Error();
			return;
		}

		NewElement->previousElement = list->activeElement;
		NewElement->nextElement = list->activeElement->nextElement;
		NewElement->data = data;

		if (NULL != list->activeElement->nextElement)
		{
			list->activeElement->nextElement->previousElement = NewElement;
		}

		if (list->lastElement == list->activeElement)
		{
			// Pokud byl aktivnim prvkem posledni element tak je potreba
			// zmenit ukazatel posledniho prvku 
			list->lastElement = NewElement;
		}
		// A jeste je potreba vlozit novy prvek za posledni prvek 
		list->activeElement->nextElement = NewElement; 


	}
}

/**
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore( DLList *list, int data ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */

	if (NULL == list->activeElement)
	{
		return;
	}
	else 
	{
		DLLElementPtr NewElement = (DLLElementPtr)malloc(sizeof(struct DLLElement));
		if (NULL == NewElement)
		{
			DLL_Error();
			return;
		}
		// nastaveni struktury nove vytvoreneho elementu 
		NewElement->nextElement = list->activeElement;
		// Zde v pripade ze aktivnim elementem bude prvni prvek se ulozi hodnota NULL 
		NewElement->previousElement = list->activeElement->previousElement;
		NewElement->data = data;	

		// Pokud existuje nejaky element pred aktivnim prvkem 
		// je treba nalinkovat na nej nove vytvoreny element
		if (NULL != list->activeElement->previousElement)
		{
			list->activeElement->previousElement->nextElement = NewElement; 
		}	

		// V pripade ze je aktivnim prvkem prvni prvek -> novy prvek bude nyni prvni
		if (list->firstElement == list->activeElement)
		{
			list->firstElement = NewElement;
		}
		// Vlozeni pred aktivni prvek novy prvek 
		list->activeElement->previousElement = NewElement;
	}

}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue( DLList *list, int *dataPtr ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if (NULL == list->activeElement || NULL == list)
	{
		DLL_Error();
		return;
	}
	*dataPtr = list->activeElement->data;

}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue( DLList *list, int data ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */

	if (NULL == list || NULL == list->activeElement)
	{
		return;
	}
	list->activeElement->data = data;

}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Next( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if (NULL == list || NULL == list->activeElement)
	{
		return;
	}
	list->activeElement = list->activeElement->nextElement;
	

}


/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	

	if (NULL == list->activeElement || NULL == list)
	{
		return;
	}
	if (list->activeElement == list->firstElement)
	{
		list->activeElement = NULL;
	}
	else
	{
	list->activeElement = list->activeElement->previousElement;
	}

}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive( DLList *list ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	return (NULL != list->activeElement);
}

/* Konec c206.c */
