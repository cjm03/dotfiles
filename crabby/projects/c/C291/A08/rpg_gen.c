/*
A08: rpg_gen.c

Programmer: Charles Moye

Basic Flow: User executes program with ./rpg_gen.c and may provide one optional
argument to seed the RNG. If the user chooses not to, the program will automatically
gather the current UNIX time and use that value as the seed. The program will then
initialize the Crewmember structure array which will hold 10 separate structures,
each representing one of 10 crewmembers, and then pseudo-randomly generate values
representing their skills and abilities. Their race, post, and rank will also be
decided in a similar fashion. All 10 crew members will then be output to stdout as
a table for the user to view, and then the user will also be prompted with a list
of options to make changes to the crew. The program will accept these options and
continue to display them after every command until the user enters 'P' which represents
'Play', and will thus cause the program to terminate.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CREWMEMBERS 10 // amount of crewmembers

typedef enum { Terran, Martian, Venusian, Saturian } Race;  // available races
typedef enum { Crew, Com, Nav, Eng, Sec, Cap } Post;        // available Posts, abbreviated for printing
typedef enum { Spcr, Ens, Lt, Comm } Rank;                  // available ranks, abbreviated for printing

// Structure to hold crewmembers abilities
typedef struct {
    int Charisma;
    int Intelligence;
    int Strength;
    int Psionics;
    int Agility;
} Abilities;
// Structure to hold crewmembers skills
typedef struct {
    int Navigation;
    int Engineering;
    int Tactics;
    int Leadership;
    int Diplomacy;
} Skills;
// Structure to hold all details of each crewmember
typedef struct Crewmember {
    int sernum;                     // unique identifier
    Post post;                      // crewmembers post
    Rank rank;                      // crewmembers rank
    Skills skills;                  // crewmembers skills (Skills)
    Abilities abilities;            // crewmembers abilities (Abilities)
    Race race;                      // crewmembers race
    char* name;                     // crewmembers name
    struct Crewmember* captain;     // captain identifier
} Crewmember;
// roll() : function to return the result of one roll of a die, takes an integer as input representing the amount of desired sides on the die
int roll(int sides)
{
    return (rand() % sides) + 1;
}
// generateAbility() : function to return a value in accordance with project instructions (sum of 3 6sided dice rolls)
int generateAbility()
{
    return roll(6) + roll(6) + roll(6);
}
// generateSkills() : function to generate values for a crewmember's skills, accepts a pointer to an individual crewmember of type Crewmember
void generateSkills(Crewmember* crew)
{
    int avgNavigation = (crew->abilities.Intelligence + crew->abilities.Psionics) / 2;
    int avgEngineering = (crew->abilities.Intelligence + crew->abilities.Agility) / 2;
    int avgTactics = (crew->abilities.Strength + crew->abilities.Agility) / 2;
    int avgLeadership = (crew->abilities.Charisma + crew->abilities.Intelligence) / 2;
    int avgDiplomacy = (crew->abilities.Charisma + crew->abilities.Psionics) / 2;

    crew->skills.Navigation = (avgNavigation >= 10) ? 2 : (avgNavigation >= 15) ? 1 : (avgNavigation >= 7) ? 0 : (avgNavigation >= 4) ? -1 : -2;
    crew->skills.Engineering = (avgEngineering >= 10) ? 2 : (avgEngineering >= 15) ? 1 : (avgEngineering >= 7) ? 0 : (avgEngineering >= 4) ? -1 : -2;
    crew->skills.Tactics = (avgTactics >= 10) ? 2 : (avgTactics >= 15) ? 1 : (avgTactics >= 7) ? 0 : (avgTactics >= 4) ? -1 : -2;
    crew->skills.Leadership = (avgLeadership >= 10) ? 2 : (avgLeadership >= 15) ? 1 : (avgLeadership >= 7) ? 0 : (avgLeadership >= 4) ? -1 : -2;
    crew->skills.Diplomacy = (avgDiplomacy >= 10) ? 2 : (avgDiplomacy >= 15) ? 1 : (avgDiplomacy >= 7) ? 0 : (avgDiplomacy >= 4) ? -1 : -2;
}
// adjustAbilitiesRace() : function to adjust a crewmember's abilities depending on their assigned race, accepts a pointer to an individual crewmember of type Crewmember
void adjustAbilitiesRace(Crewmember* crew)
{
    switch (crew->race) {
        case Martian:
            crew->abilities.Strength -= 2;
            crew->abilities.Psionics += 2;
            crew->abilities.Agility += 1;
            break;
        case Venusian:
            crew->abilities.Charisma += 1;
            crew->abilities.Intelligence -= 1;
            crew->abilities.Strength += 1;
            crew->abilities.Psionics += 1;
            crew->abilities.Agility -= 1;
            break;
        case Saturian:
            crew->abilities.Charisma -= 1;
            crew->abilities.Intelligence += 2;
            crew->abilities.Strength -= 1;
            crew->abilities.Psionics += 1;
            break;
        case Terran:
            break;
    }
}
// generateCrewmember() : the main function for generating crewmembers, accepts a unique identifier for a specific crewmember and a crewnum for name initialization
Crewmember* generateCrewmember(int sernum, int crewnum)
{
    Crewmember* crew = (Crewmember*)malloc(sizeof(Crewmember)); // allocate memory for the crewmember
    crew->sernum = sernum;                                      // assign the crewmember their unique identifier
    crew->name = (char*)malloc(50 * sizeof(char));              // allocate memory for the string representing the crewmember's name
    sprintf(crew->name, "Crewman%d", crewnum);                  // assign the name

    // Race
    crew->race = rand() % 4;                                    // randomly assign the crew member's race as an integer representing a value in the race enumeration

    // Abilities
    crew->abilities.Charisma = generateAbility();               //
    crew->abilities.Intelligence = generateAbility();           // ASSIGNING
    crew->abilities.Strength = generateAbility();               //
    crew->abilities.Psionics = generateAbility();               // ABILITIES
    crew->abilities.Agility = generateAbility();                //

    // Adjust
    adjustAbilitiesRace(crew);                                  // call adjustAbilitiesRace to adjust

    // Skills
    generateSkills(crew);                                       // call generateSkills to assign skills

    int rank_roll = roll(6) + roll(6);
    if (rank_roll <= 7) {
        crew->rank = Spcr;
    } else if (rank_roll <= 10) {
        crew->rank = Ens;                                       // Assigning ranks
    } else if (rank_roll == 11) {
        crew->rank = Lt;
    } else {
        crew->rank = Comm;
    }

    // Post
    crew->post = Crew;                                          // assign default post of Crewman, abbreviated to "Crew"

    // Cap'n pointer
    crew->captain = NULL;                                       // no default captain assignment, assign with NULL

    return crew;
}

// outputTable() : function to print the randomly generated crew, takes in the generated crew and an integer defining the size of the crew
void outputTable(Crewmember** crew, int crewsize)
{
    int captainIndex = -1;
    for (int x = 0; x < CREWMEMBERS; x++) {
        if (crew[x]->captain != NULL) {
            captainIndex = x;
        }
    }
    if (captainIndex != -1) {
        printf("\nCaptain : %s\n", crew[captainIndex]->name);
    } else {
        printf("\nCaptain : %s\n", "NONE");
    }
    printf("\t\t\t%-16s %s\n", "Skills", "Abilities");
    printf("Ser#   Post Rank  | N  E  T  L  D  | C  I  S  P  A  | Race Name\n");
    for (int i = 0; i < 10; i++) {
        //printf("%-6d %-4s %-4s  | %-2d %-2d %-2d %-2d %-2d | %-2d %-2d %-2d %-2d %-2d | %-4s %s\n", 123456, "Crew", "Spcr", 0, -1, 2, -2, 1, 13, 3, 18, 5, 10, "T", "Kerlin");
        printf("%-6d ", crew[i]->sernum);
        switch (crew[i]->post) {
            case Crew: printf("%-4s ", "Crew"); break;
            case Com: printf("%-4s ", "Com"); break;
            case Nav: printf("%-4s ", "Nav"); break;
            case Eng: printf("%-4s ", "Eng"); break;
            case Sec: printf("%-4s ", "Sec"); break;
            case Cap: printf("%-4s ", "Cap"); break;
        }
        switch (crew[i]->rank) {
            case Spcr: printf("%-4s ", "Spcr"); break;
            case Ens: printf("%-4s ", "Ens"); break;
            case Lt: printf("%-4s ", "Lt"); break;
            case Comm: printf("%-4s ", "Comm"); break;
        }
        printf(" | %-2d %-2d %-2d %-2d %-2d | %-2d %-2d %-2d %-2d %-2d | ", //%-4s %s\n", 
               //crew[i]->sernum, crew[i]->post, crew[i]->rank, 
               crew[i]->skills.Navigation, crew[i]->skills.Engineering, crew[i]->skills.Tactics, crew[i]->skills.Leadership, crew[i]->skills.Diplomacy, 
               crew[i]->abilities.Charisma, crew[i]->abilities.Intelligence, crew[i]->abilities.Strength, crew[i]->abilities.Psionics, crew[i]->abilities.Agility);
               //crew[i]->race, crew[i]->name);
        switch (crew[i]->race) {
            case Terran: printf("%-4s", "T"); break;
            case Martian: printf("%-4s", "M"); break;
            case Venusian: printf("%-4s", "V"); break;
            case Saturian: printf("%-4s", "S"); break;
        }
        printf(" %s\n", crew[i]->name);
    }
}
// generateSernum() : function to generate random unique identifiers ranging from 100000-999999
int generateSernum()
{
    int lb = 100000;
    int ub = 999999;
    return (rand() % (ub - lb + 1) + lb );
}
// printMenu() : prints options for user to interact with generated crew
void printMenu()
{
    printf("\n\nMenu options:\n");
    printf("D   - Redisplay the table of crewmembers.\n");
    printf("N # - Provide a name for the specified crewmember.\n");
    printf("C # - Make the specified crewmember the captain for the crew. (No other crewmember should have a higher rank than the captain.)\n");
    printf("B # - Assign the specified crewmember to a bridge position by specifying a menu of bridge crew positions. Use single letter to indicate the bridge post assigned (N C S E).\n");
    printf("S   - Save the crewmember list to a file crewmember_list.txt\n");
    printf("R # - Regenerate the given crewmember.\n");
    printf("P   - Allows the user to play the game which for your program will result in exiting the program.\n");
}
// changeName() : function to change a crewmember's name, accepts the crew itself, and a unique identifier to look for before changing the name
void changeName(Crewmember** crew, int identifier)
{
    int indexPos = 11;
    for (int i = 0; i < CREWMEMBERS; i++) {
        if (crew[i]->sernum == identifier) {
            indexPos = i;
        }
    }
    if (indexPos != 11) {
        printf("Enter new name for crewmember #%d: ", crew[indexPos]->sernum);
        scanf(" %s", crew[indexPos]->name);
        printf("\n%d is now %s\n", crew[indexPos]->sernum, crew[indexPos]->name);
    } else {
        printf("Invalid crewmember\n");
    }
}
// makeCaptain() : function to assign a crewmember as captain. will also modify the new captain's post and rank in accordance with project instructions
void makeCaptain(Crewmember** crew, int identifier)
{
    int indexPos = -1;
    for (int i = 0; i < CREWMEMBERS; i++) {
        if (crew[i]->sernum == identifier) {
            indexPos = i;
            crew[i]->captain = crew[i];
            crew[i]->post = Cap;
            crew[i]->rank = Comm;
            printf("\n%s is now the captain\n", crew[i]->name);

            for (int j = 0; j < CREWMEMBERS; j++) {
                if (i != j) {
                    crew[j]->captain = NULL;
                }
            }
            break;
        }
    }
    if (indexPos != -1) {
        Crewmember* temp = crew[0];
        crew[0] = crew[indexPos];
        crew[indexPos] = temp;
    }
}
// assignBridge() : function to assign crewmembers to bridge posts, accepts the crew and a unique identifier to verify correct assignment
void assignBridge(Crewmember** crew, int identifier)
{
    char bridgePos;
    printf("\nAssigning %d, enter C, N, E, or S: ", identifier);
    for (int i = 0; i < CREWMEMBERS; i++) {
        if (crew[i]->sernum == identifier) {
            scanf(" %c", &bridgePos);
            switch (bridgePos) {
                case 'C': crew[i]->post = Com; break;
                case 'N': crew[i]->post = Nav; break;
                case 'E': crew[i]->post = Eng; break;
                case 'S': crew[i]->post = Sec; break;
                default: printf("\nInvalid option\n"); break;
            }
            printf("\n%d has been reassigned\n", crew[i]->sernum);
        }
    }
}

// writeOutputTableToFile() : same as outputTable(), but uses fprintf to write to a file
void writeOutputTableToFile(Crewmember** crew, int crewsize)
{
    FILE *file = fopen("crewmember_list.txt", "w");
    int captainIndex = -1;
    for (int x = 0; x < CREWMEMBERS; x++) {
        if (crew[x]->captain != NULL) {
            captainIndex = x;
        }
    }
    if (captainIndex != -1) {
        fprintf(file, "Captain : %s\n", crew[captainIndex]->name);
    } else {
        fprintf(file, "Captain : %s\n", "NONE");
    }

    fprintf(file, "\t\t\t%-16s %s\n", "Skills", "Abilities");
    fprintf(file, "Ser#   Post Rank  | N  E  T  L  D  | C  I  S  P  A  | Race Name\n");
    for (int i = 0; i < 10; i++) {
        //printf("%-6d %-4s %-4s  | %-2d %-2d %-2d %-2d %-2d | %-2d %-2d %-2d %-2d %-2d | %-4s %s\n", 123456, "Crew", "Spcr", 0, -1, 2, -2, 1, 13, 3, 18, 5, 10, "T", "Kerlin");
        fprintf(file, "%-6d ", crew[i]->sernum);
        switch (crew[i]->post) {
            case Crew: fprintf(file, "%-4s ", "Crew"); break;
            case Com: fprintf(file, "%-4s ", "Com"); break;
            case Nav: fprintf(file, "%-4s ", "Nav"); break;
            case Eng: fprintf(file, "%-4s ", "Eng"); break;
            case Sec: fprintf(file, "%-4s ", "Sec"); break;
            case Cap: fprintf(file, "%-4s ", "Cap"); break;
        }
        switch (crew[i]->rank) {
            case Spcr: fprintf(file, "%-4s ", "Spcr"); break;
            case Ens: fprintf(file, "%-4s ", "Ens"); break;
            case Lt: fprintf(file, "%-4s ", "Lt"); break;
            case Comm: fprintf(file, "%-4s ", "Comm"); break;
        }
        fprintf(file, " | %-2d %-2d %-2d %-2d %-2d | %-2d %-2d %-2d %-2d %-2d | ", //%-4s %s\n", 
               //crew[i]->sernum, crew[i]->post, crew[i]->rank, 
               crew[i]->skills.Navigation, crew[i]->skills.Engineering, crew[i]->skills.Tactics, crew[i]->skills.Leadership, crew[i]->skills.Diplomacy, 
               crew[i]->abilities.Charisma, crew[i]->abilities.Intelligence, crew[i]->abilities.Strength, crew[i]->abilities.Psionics, crew[i]->abilities.Agility);
               //crew[i]->race, crew[i]->name);
        switch (crew[i]->race) {
            case Terran: fprintf(file, "%-4s", "T"); break;
            case Martian: fprintf(file, "%-4s", "M"); break;
            case Venusian: fprintf(file, "%-4s", "V"); break;
            case Saturian: fprintf(file, "%-4s", "S"); break;
        }
        fprintf(file, " %s\n", crew[i]->name);
    }
    fclose(file);
}


int main(int argc, char* argv[])
{
    int seed = time(NULL);
    if (argc > 1) {
        seed = atoi(argv[1]);
    }
    srand(seed);

    Crewmember* crew[CREWMEMBERS];
    int sernum;

    for (int i = 0; i < CREWMEMBERS; i++) {
        sernum = generateSernum();
        crew[i] = generateCrewmember(sernum, i + 1);
    }

    outputTable(crew, CREWMEMBERS);

    char choice;
    int modify;
    while (1) {
        printMenu();
        printf("Enter your choice: ");
        if (scanf(" %c", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 'D') {
            outputTable(crew, CREWMEMBERS);
        } else if (choice == 'N') {
            if (scanf("%d", &modify) == 1 && modify >= 100000 && modify <= 999999) {
                changeName(crew, modify);
            } else {
                printf("Invalid crew #. Provide 6 digit number\n");
            }
        } else if (choice == 'C') {
            if (scanf("%d", &modify) == 1 && modify >= 100000 && modify <= 999999) {
                makeCaptain(crew, modify);
            } else {
                printf("Invalid crew member #. Provide 6 digit number\n");
            }
        } else if (choice == 'B') {
            if (scanf("%d", &modify) == 1 && modify >= 100000 && modify <= 999999) {
                assignBridge(crew, modify);
            } else {
                printf("Invalid crew member #. Provide 6 digit number\n");
            }
        } else if (choice == 'R') {
            if (scanf("%d", &modify) == 1 && modify >= 100000 && modify <= 999999) {
                for (int i = 0; i < CREWMEMBERS; i++) {
                    if (crew[i]->sernum == modify) {
                        int rSernum = generateSernum();
                        crew[i] = generateCrewmember(rSernum, i);
                        printf("\n%d has been regenerated and is now %d\n", modify, rSernum);
                    }
                }
            } else {
                printf("Invalid crew member #. Provide 6 digit number\n");
            }
        } else if (choice == 'S') {
            writeOutputTableToFile(crew, CREWMEMBERS);
            printf("File saved as crewmember_list.txt\n");
        } else if (choice == 'P') {
            printf("\n");
            break;
        }
    }

    for (int i = 0; i < CREWMEMBERS; i++) {
        free(crew[i]->name);
        free(crew[i]);
    }

    return 0;
}














