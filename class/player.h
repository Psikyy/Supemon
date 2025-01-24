#ifndef CGI_TPILE_H
#define CGI_TPILE_H
 
#define ITEM_ALLOC_ERROR  1
#define PILE_EMPTY       -1
 
#ifdef __cplusplus
  extern "C" {
#endif
 
/*  Structure représentant un élément de la pile. */
typedef struct Titem
        {
                int Value;
                struct Titem *prec;
        } Titem ;
 
/*  Structure représentant l'objet pile. */
typedef struct TPile
        {
            /*  Les pointeurs sur fonctions (membres) :                       */
            /*  Push empile une valeur sur la pile.
                retourne ITEM_ALLOC_ERROR si l'allocation a échoué sinon 0
                int Push(TPile, int)                                          */
                int(*Push)(struct TPile*, int);
 
            /*  Pop retire la dernière valeur empilée sur la pile.
                retourne PILE_EMPTY si la pile est vide.
                int Pop(TPile)                                                */
                int(*Pop)(struct TPile*);
 
            /*  Clear vide la pile.
                void Clear(TPile)                                             */
                void(*Clear)(struct TPile*);
 
            /*  Free détruit la pile.
                void Free(TPile)                                              */
                void(*Free)(struct TPile*);
 
            /*  Lenght retourne le nombre d'éléments de la pile.
                int Length(TPile)                                             */
                int(*Length)(struct TPile*);
 
            /*  View affiche la totalité de la pile en commençant par le sommet.
                void View(TPile)                                              */
                void(*View)(struct TPile*);
 
            /*  Les données membres :                                         */
                int Nombre;
                struct Titem *Top;
 
        } TPile ;
 
 
/*  Pile_Create crée une pile. */
TPile TPile_Create(void);
 
TPile* New_TPile(void);
 
int TPile_Push(TPile*, int);
 
int TPile_Pop(TPile*);
 
void TPile_Clear(TPile*);
 
int TPile_Length(TPile*);
 
void TPile_View(TPile*);
 
void TPile_Free(TPile*);
 
void TPile_New_Free(TPile*);
 
#ifdef __cplusplus
}
#endif
 
#endif