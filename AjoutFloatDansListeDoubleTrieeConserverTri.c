#include <stdio.h>
#include <stdlib.h>

typedef struct elementdouble
{
    float valeur;
    struct elementdouble *suivant;
    struct elementdouble *precedent;
} elementdouble, *listedouble;

void afficherListeDouble(listedouble Ld)
{
    listedouble p = Ld;
    if(p->precedent == NULL){printf("NULL --><-- ");}
    while(p != NULL)
    {
        printf("%.2f --><-- ", p->valeur);
        p = p->suivant;
    }
    if(p == NULL){printf(" NULL");}
    printf("\n");
}


listedouble nettoyerDernierElementListeDouble(listedouble Ld)
{
    if (Ld == NULL)
    {
        return NULL;
    }
    else if (Ld->suivant == NULL)
    {
        free(Ld);
        return NULL;
    }
    listedouble p = Ld;
    while(p->suivant != NULL)
    {   
        listedouble tampon = p;
        p = p->suivant;
        free(p);
        tampon->suivant = NULL;
        return Ld;
    }
    
}

listedouble nettoyerListeDouble(listedouble Ld)
{
    while(Ld != NULL)
    {
        Ld = nettoyerDernierElementListeDouble(Ld);

    }
    printf("La liste double a ete nettoyee\n");
}

// PROGRAMME 3. du TP
listedouble insertionValeurDansListeDoubleTrieeEtConserverLeTrie(listedouble Ld, float valeur)
{
    listedouble nouveauDouble = NULL;
    nouveauDouble = (listedouble)malloc(sizeof(elementdouble));
    if(nouveauDouble == NULL)
    {
        fprintf(stderr, "Erreur d'allocation memoire \n");
        exit(EXIT_FAILURE);
    }
    nouveauDouble->valeur = valeur;
    nouveauDouble->suivant = NULL;
    nouveauDouble->precedent = NULL;
    
    if(Ld == NULL){return nouveauDouble;}
    else if (Ld->valeur >= valeur)
    {
        nouveauDouble->suivant = Ld;
        Ld->precedent = nouveauDouble;
        return nouveauDouble;
    }
    else
    {
        listedouble p = Ld;
        while(p->suivant != NULL && p->suivant->valeur < valeur)
        {
            p = p->suivant;
        }
        nouveauDouble->suivant = p->suivant;
        nouveauDouble->precedent = p;
        if (p->suivant != NULL)
        {
            p->suivant->precedent = nouveauDouble;
        }
        p->suivant = nouveauDouble;
        return Ld;
    }
}
listedouble remplissageListeDoubleTriee(unsigned int nombreElements)
{
    if (nombreElements == 0){return NULL;}
    float valeur;
    listedouble Ld = NULL;
    for(int i = 1; i<=nombreElements; i++ )
    {
        printf("Entrez la valeur du %deme element : ", i);
        scanf("%f", &valeur);
        Ld = insertionValeurDansListeDoubleTrieeEtConserverLeTrie(Ld, valeur);
    }
    return Ld;
}

int main()
{   
    int nombreElement;
    printf("Nombre d'element(s) de la liste chainee double ? \n");
    scanf("%d", &nombreElement);
    if(nombreElement <= 0)
    {
        printf("Fin du programme.\n");
        return 1;
    }
    listedouble ListeDouble = NULL;
    ListeDouble = remplissageListeDoubleTriee(nombreElement);
    printf("Voici la liste double avec vos valeurs : \n");
    afficherListeDouble(ListeDouble);
    printf("Quelle valeur float voulez-vous inserer dans la liste double triee ? \n");
    float valeur;
    scanf("%f", &valeur);
    ListeDouble = insertionValeurDansListeDoubleTrieeEtConserverLeTrie(ListeDouble, valeur);
    printf("Voici la liste double apres insertion de %.2f : \n", valeur);
    afficherListeDouble(ListeDouble);
    printf("Nettoyage de la liste double...\n");
    ListeDouble = nettoyerListeDouble(ListeDouble);
    return 0;
}