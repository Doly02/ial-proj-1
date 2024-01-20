/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického výrazu
** do postfixového tvaru. Pro převod využijte zásobník (Stack), který byl
** implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202
** se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix ... konverzní funkce pro převod infixového výrazu
**                      na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**    
**    untilLeftPar ... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"

bool solved;

/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude
 * také odstraněna.
 * Pokud je zásobník prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
 * znaků postfixExpression.
 * Délka převedeného výrazu a též ukazatel na první volné místo, na které se má
 * zapisovat, představuje parametr postfixExpressionLength.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
 * nadeklarovat a používat pomocnou proměnnou typu char.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void untilLeftPar( Stack *stack, char *postfixExpression, unsigned *postfixExpressionLength ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */

	// Kontrola obsahu zasobniku
	if (Stack_IsEmpty(stack))
	{
		return;
	}
	else
	{
		// Neco je na zasobniku
		if ((NULL != stack) && (NULL != postfixExpression) && (NULL != postfixExpressionLength)) // Kontrola zda-li vsechny parametry maji sve hodnoty 
		{
			char CharacterFromTopStack = '\0'; // Pomocna promenna na ukladani znaku ze zasobniku
			while ((0 == Stack_IsEmpty(stack)) && ('(' != CharacterFromTopStack))
			{
				// Vezmi prvek na vrcholu zasobniku
				Stack_Top(stack,&CharacterFromTopStack);
				// Vloz ho do retezce 
				if ('(' != CharacterFromTopStack)
				{
					postfixExpression[(*postfixExpressionLength)] = CharacterFromTopStack;
					(*postfixExpressionLength)++;
				}
				// Uvolni znak ze zasobniku
				Stack_Pop(stack);
			}

		}
	} 
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param c Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void doOperation( Stack *stack, char c, char *postfixExpression, unsigned *postfixExpressionLength ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	if ((NULL != stack) && (NULL != postfixExpression) && (NULL != postfixExpressionLength)) // Kontrola zda-li vsechny parametry maji sve hodnoty 
	{
		char CharacterFromTopStack = '\0'; // Pomocna promenna na ukladani znaku ze zasobniku

		// Pokud je zasobnik prazdny tak vlozit znak na vrchol
		if (1 == Stack_IsEmpty(stack))
		{
			Stack_Push(stack,c);
		}
		// Pokud neni zasobnik prazdny tak si z neho vezmu charakter na vrcholu
		else if (0 == Stack_IsEmpty(stack))
		{
			Stack_Top(stack,&CharacterFromTopStack);
			if ('(' == CharacterFromTopStack)
			{
				Stack_Push(stack,c);
			}
			// Je-li na vrcholu zasobniku operator s mensi prio. tak ho tam tez vloz 
			else if (('+' == CharacterFromTopStack || '-' == CharacterFromTopStack) && ('*' == c || '/' == c))
			{
				Stack_Push(stack,c);
			}
			// Je-li na vrcholu zasobnuku operator s vyssi nebo shodnou prio.
			else 
			{
				// Odstran ho 
				Stack_Pop(stack);
				// Vloz ho na konec vstupniho retezce
				postfixExpression[(*postfixExpressionLength)] = CharacterFromTopStack;
				(*postfixExpressionLength)++;
				// Opakuj cely proces
				doOperation(stack,c,postfixExpression,postfixExpressionLength);

			}
		}
		
	}
}
/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infixExpression a generuje
 * odpovídající postfixový výraz do výstupního řetězce (postup převodu hledejte
 * v přednáškách nebo ve studijní opoře).
 * Paměť pro výstupní řetězec (o velikosti MAX_LEN) je třeba alokovat. Volající
 * funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde
 * alokované paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
 *    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
 *    násobení má stejnou prioritu jako dělení. Priorita násobení je
 *    větší než priorita sčítání. Všechny operátory jsou binární
 *    (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
 *    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
 *    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
 *    chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
 *    ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků Stack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
 * char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
 * nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
 * by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
 * řetězce konstantu NULL.
 *
 * @param infixExpression vstupní znakový řetězec obsahující infixový výraz k převedení
 *
 * @returns znakový řetězec obsahující výsledný postfixový výraz
 */
char *infix2postfix( const char *infixExpression ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	bool IFoundAssign = false;
	// alokace prostoru pro postfixovou notaci vyrazu
	char *postfixExpression = (char *) malloc(MAX_LEN * sizeof(char));
	if (NULL == postfixExpression)
	{
		return NULL;
	}

	// Alokace zasobniku
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	if (!stack)
	{
		free(postfixExpression);
		return NULL;
	}
	Stack_Init(stack); 
	unsigned int CharInInfix = 0u;
	unsigned int LenghtOfPostfix = 0u;

	while(false == IFoundAssign)
	{
		char Character= infixExpression[CharInInfix];
		if ((Character >= '0' && Character <= '9') || (Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z')) // operand
		{
			// Pridat znak na konec Postfixoveho retezce
			postfixExpression[LenghtOfPostfix++] = Character; 
		}
		else if ('(' == Character) 
		{
			// Vloz znak na vrchol zasobniku
			Stack_Push(stack, Character); 
		}
		else if ('+' == Character || '-' == Character || '*' == Character || '/' == Character) 
		{
			// Zpracuj operator
			doOperation(stack, Character, postfixExpression, &LenghtOfPostfix);
		}
		else if (')' == Character) // pravá zavorka
		{
			// Odebirej polozky z vrcholu zasobniku a davej je do postfix. retezce
			untilLeftPar(stack, postfixExpression, &LenghtOfPostfix); 
		}
		else if ('=' == Character) 
		{
			// Postupne vkladej prvky z vrcholu zasobniku do retezce
			while (0 == Stack_IsEmpty(stack))
			{
				Stack_Top(stack, &(postfixExpression[LenghtOfPostfix++]));
				Stack_Pop(stack); 
			}
			// Skonci cyklus
			IFoundAssign = true;
		}
		CharInInfix++;
		
	}
	postfixExpression[LenghtOfPostfix++] = '=';
	postfixExpression[LenghtOfPostfix++] = '\0'; 
	Stack_Dispose(stack);
	free(stack); 

	return postfixExpression; // vrácení výstupního řetězce
	
}


/**
 * Pomocná metoda pro vložení celočíselné hodnoty na zásobník.
 *
 * Použitá implementace zásobníku aktuálně umožňuje vkládání pouze
 * hodnot o velikosti jednoho byte (char). Využijte této metody
 * k rozdělení a postupné vložení celočíselné (čtyřbytové) hodnoty
 * na vrchol poskytnutého zásobníku.
 *
 * @param stack ukazatel na inicializovanou strukturu zásobníku
 * @param value hodnota k vložení na zásobník
 */
void expr_value_push( Stack *stack, int value ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	unsigned int i = 0u;
	char byte = '\0';
	// Rozlozeni 4 Bytove hodnoty na 4 jedno-byte hodnoty 
	for (i = 0u; i < 4; i++)
	{
		// mozna to predelam at se nemusi pouzivat ta maska
		byte = (value >> (i * 8) & 0xFF);
		Stack_Push(stack,byte);
	}
	
}

/**
 * Pomocná metoda pro extrakci celočíselné hodnoty ze zásobníku.
 *
 * Využijte této metody k opětovnému načtení a složení celočíselné
 * hodnoty z aktuálního vrcholu poskytnutého zásobníku. Implementujte
 * tedy algoritmus opačný k algoritmu použitému v metodě
 * `expr_value_push`.
 *
 * @param stack ukazatel na inicializovanou strukturu zásobníku
 * @param value ukazatel na celočíselnou proměnnou pro uložení
 *   výsledné celočíselné hodnoty z vrcholu zásobníku
 */
void expr_value_pop( Stack *stack, int *value ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	*value = 0;

	unsigned int i = 0u;
	char byte = '\0';
	for (i = 3u; i != (unsigned int) -1; i--)
	{
		Stack_Top(stack,&byte);
		Stack_Pop(stack);
		*value = *value | ((byte & 0xFF) << (i*8));
	} 
}

int sum(int a, int b)
{
	return (a+b);
}

int substaction(int a, int b)
{
	return (a-b);
}
 
int division(int a,int b)
{
	return (a/b);
}

int multiplication(int a,int b)
{
	return (a*b);
}

/**
 * Tato metoda provede vyhodnocení výrazu zadaném v `infixExpression`,
 * kde hodnoty proměnných použitých v daném výrazu jsou definovány
 * v poli `variableValues`.
 *
 * K vyhodnocení vstupního výrazu využijte implementaci zásobníku
 * ze cvičení c202. Dále také využijte pomocných funkcí `expr_value_push`,
 * respektive `expr_value_pop`. Při řešení si můžete definovat libovolné
 * množství vlastních pomocných funkcí.
 *
 * Předpokládejte, že hodnoty budou vždy definovány
 * pro všechy proměnné použité ve vstupním výrazu.
 *
 * @param infixExpression vstupní infixový výraz s proměnnými
 * @param variableValues hodnoty proměnných ze vstupního výrazu
 * @param variableValueCount počet hodnot (unikátních proměnných
 *   ve vstupním výrazu)
 * @param value ukazatel na celočíselnou proměnnou pro uložení
 *   výsledné hodnoty vyhodnocení vstupního výrazu
 *
 * @return výsledek vyhodnocení daného výrazu na základě poskytnutých hodnot proměnných
 */
bool eval( const char *infixExpression, VariableValue variableValues[], int variableValueCount, int *value ) {
	//solved = false; /* V případě řešení, smažte tento řádek! */
	
	int AssingInProcess = false;
	char* postfixExpression;
	Stack stack;
	Stack_Init(&stack);
	unsigned int LetterSequence = 0u;
	int TopInStack = 0;
	int UnderTopInStack = 0;
	int Result = 0;

	// Predelat si vyraz z infixove notace do postfixove notace
	postfixExpression = infix2postfix(infixExpression);
	if (NULL == postfixExpression)
	{
		Stack_Dispose(&stack);
		return false;
	}

	while(!AssingInProcess && postfixExpression[LetterSequence] != '\0')
	{
		char Character= postfixExpression[LetterSequence++];
		// 2 Je-li zpracovavanym prvkem operand, vloz ho do zasobniku
		if ((Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z')) // operand
		{

			if((Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z'))
			{
				// Najdi promennou v tabulce 
				for (int i = 0; i < variableValueCount;i++)
				{
					if(variableValues[i].name == Character)
						expr_value_push(&stack,variableValues[i].value);
				}
			}
		}
		// Je-li zpracovavanym prvkem operator, vyjmi ze zasobniku tolik operandu kolika-adicky je operand
		// proved danou akci a vysledek uloz na zasobnik
		else if ('+' == Character)
		{
			// vytahni ze zasobniku prvni hodnoty
			expr_value_pop(&stack,&TopInStack);
			// vytahni ze zasobniku druhou hodnotu 
			expr_value_pop(&stack,&UnderTopInStack);
			// proved oparaci
			Result = sum(UnderTopInStack,TopInStack);
			// vysledek uloz na zasobnik 
			expr_value_push(&stack,Result);
		}
		else if ('-' == Character)
		{
			// vytahni ze zasobniku prvni hodnoty
			expr_value_pop(&stack,&TopInStack);
			// vytahni ze zasobniku druhou hodnotu 
			expr_value_pop(&stack,&UnderTopInStack);
			// proved oparaci
			Result = substaction(UnderTopInStack,TopInStack);
			// vysledek uloz na zasobnik 
			expr_value_push(&stack,Result);
		}
		else if ('*' == Character)
		{
			// vytahni ze zasobniku prvni hodnoty
			expr_value_pop(&stack,&TopInStack);
			// vytahni ze zasobniku druhou hodnotu 
			expr_value_pop(&stack,&UnderTopInStack);
			// proved oparaci
			Result = multiplication(UnderTopInStack,TopInStack);
			// vysledek uloz na zasobnik 
			expr_value_push(&stack,Result);
		}
		else if ('/' == Character)
		{
			// vytahni ze zasobniku prvni hodnoty
			expr_value_pop(&stack,&TopInStack);
			// vytahni ze zasobniku druhou hodnotu 
			expr_value_pop(&stack,&UnderTopInStack);
			// proved oparaci
			Result = division(UnderTopInStack,TopInStack);
			// vysledek uloz na zasobnik 
			expr_value_push(&stack,Result);
		}
		// Je-li zpravovavanym prvkem '='
		else if ('=' == Character)
		{
			AssingInProcess = true;
			expr_value_pop(&stack,value);
			break;
		}
		else{
			return false;
		}
	}
	Stack_Dispose(&stack);
	free(postfixExpression);

	return true;

	
}

/* Konec c204.c */
