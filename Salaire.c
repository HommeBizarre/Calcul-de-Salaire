#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<sys/time.h>

#define SPM 4.33342857 //Semaines de travail par mois || 151.57H / 35H OU 52semaines / 12 mois
#define MPA 10.5953715 //Mois de travail par année || 1607H / 151.57
#define SPA 1607 // 35 = 45.91

//1607HTM / 12 = HPM

#define HTM 151.67 //35×52÷12
#define STA 1607 //1607 / 35 = 45,91
//35 * 52 - 1607 = Heure de non travail par année (213)

#define bonus1 1.25 //20%
#define bonus2 1.50 //50%

// Exemple : 100 € - (100 € * 20 / 100) = 80 € : pour 20% de réduction.
// gcc -Wall -Wextra Salaire.c -o crashtest | ./crashtest

int main()
{
    float CHARGE = 23; //Taxe de merde
    float BRUT = 10.57; //Salaire Brut
    float HEURE = 35;

    char *rep = malloc(10 * sizeof(char));

    printf("Le taux des CHARGES est t'il différent de %.3f%%\nRépondre par OUI ou par NON : ", CHARGE);
    scanf("%s", rep);

    if ((strcmp(rep, "OUI") == 0))
    {
        printf("Quel est le taux des CHARGES ? : ");
        scanf("%f", &CHARGE);
    }
    printf("Le taux des CHARGES est de %.3f%%", CHARGE);

    printf("\n\nQuel est votre salaire BRUT à l'heure? : ");
    scanf("%f", &BRUT);

    float PCT = (BRUT * CHARGE / 100); // Pertes sur le salaire
    float NET = BRUT - PCT; //Salaire Net
    
    printf("On vous retire %f€ pour obtenir votre salaire NET à l'heure", PCT);
    printf("\nVotre salaire BRUT à l'heure est de %.2f€\nEt votre salaire NET à l'heure est de %.2f€", BRUT, NET);
    
    printf("\n\nTravaillez-vous à pleins temps ? (35H Uniquement)\nRépondre par OUI ou par NON : ");
    scanf("%s", rep);

    if ((strcmp(rep, "OUI") != 0))
    {
        printf("\n\nCombien d'heure effectuez-vous par semaine? : ");
        scanf("%f", &HEURE);
    }

    printf("Vous travaillez %.2f heures par semaines", HEURE);

    float HORAIRE[3] = {0, 0, 0};

OVERWORK:
    if (HEURE > 48)
    {
        goto OVERWORK;
    }
    else if (HEURE > 35)
    {
        HORAIRE[0] = 35;
        HORAIRE[1] = HEURE - 35;

        if (HORAIRE[1] > 7)
        {
            HORAIRE[2] = HORAIRE[1] - 7;
            HORAIRE[1] = 7;
        }
    }
    else HORAIRE[0] = HEURE;

    float HEURETEST = HORAIRE[0] + HORAIRE[1] + HORAIRE[2];

    printf("\n\nHEURE1 = %f HEURE2 = %f, HEURE3 = %f DONC %f\n\n", HORAIRE[0], HORAIRE[1], HORAIRE[2], HEURETEST);

    float HPM[3] = {0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        HPM[i] = HORAIRE[i] * SPM;
    }
    float THM = HPM[0] + HPM[1] + HPM[2];
   
    printf("\n\nHPM1 = %f HPM2 = %f, HPM3 = %f DONC %f\n\n", HPM[0], HPM[1], HPM[2], THM);
    
    float HPA[3] = {0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        HPA[i] = HPM[i] * MPA;
    }
    float THA = HPA[0] + HPA[1] + HPA[2];
    printf("\n\nHPA1 = %f HPA2 = %f, HPA3 = %f DONC %f\n\n", HPA[0], HPA[1], HPA[2], THA);
    

    float SS1 = HORAIRE[0] * NET; //Salaire par semaines (35H max)
    float SS2 = HORAIRE[1] * NET * bonus1; //Salaire par semaines (Entre 35H et 43H)
    float SS3 = HORAIRE[2] * NET * bonus2; //Salaire par semaines (Supérieur à 43H)
    float SS = SS1 + SS2 + SS3;

    printf("\n\nSS1 = %f SS2 = %f, SS3 = %f DONC %f\n\n", SS1, SS2, SS3, SS);

    float SM1 = HPM[0] * NET; //Salaire par mois (151.67)
    float SM2 = HPM[1] * NET * bonus1; //Salaire par mois (Entre 151.67 et 186.33 )
    float SM3 = HPM[2] * NET * bonus2; //Salaire par mois
    float SM = SM1 + SM2 + SM3;

    printf("\n\nSM1 = %f SM2 = %f, SM3 = %f DONC %f\n\n", SM1, SM2, SM3, SM);

    float SA1 = HPA[0] * NET;
    float SA2 = HPA[1] * NET * bonus1;
    float SA3 = HPA[2] * NET * bonus2;
    float SA = SA1 + SA2 + SA3;

    printf("\n\nSA1 = %f SA2 = %f, SA3 = %f DONC %f\n\n", SA1, SA2, SA3, SA);

    printf("\n\nPour %.2f heures par semaines vous travaillerez :\n%.2f heures par mois\n%.2f heures par an", HEURE, THM, THA);
    printf("\n\nPour %.2f€ BRUT de l'heure avec un taux de CHARGES à %.3f%%, vous serez payé :\n%.2f€ par heures\n%.2f€ par semaines\n%.2f€ par mois\n%.2f€ par an\n\n", BRUT, CHARGE, NET, SS, SM, SA);

}