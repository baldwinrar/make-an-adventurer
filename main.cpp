#include <iostream>
#include <random> 
#include <string>
#include <chrono>
#include <vector>

struct Character {

    std::string name = "Unknown";
    std::string advclass = "Adventurer";
    int stats[7] = {0};
    int hp = 0;
} adventurer;

std::vector<std::string> statnames = {"Strength", "Intelligence", "Wisdom", "Constitution", "Dexterity", "Charisma", "Gold"};
std::vector<std::string> advclassnames = {"Fighter", "Magic-user", "Cleric", "Barbarian", "Thief", "Bard"};

std::random_device rd{};    
std::mt19937 tower{rd()};
std::uniform_real_distribution<float> d4{1, 5};
std::uniform_real_distribution<float> d6{1, 7};

int roll_nd4 (int n) {

    int sum = 0;

    for (int i=0; i<n; i++) {

        int roll = d4(tower);

        if (roll > 4) {

            std::cout << "lol" << std::endl;
            i--;

        } else {

            sum += roll;
        }
    }

    return sum;
}

int roll_nd6 (int n) {

    int sum = 0;

    for (int i=0; i<n; i++) {

        int roll = d6(tower);

        if (roll > 6) {
            std::cout << "lol" << std::endl;
            i--;

        } else {

            // std::cout << " " << roll << " ";
            sum += roll;
        }
    }

    return sum;
}

std::string StatQuality(int statnum) {

    std::string bonus = "(- 3)";

    if (statnum > 17) {
        bonus = "(+ 3)";
    }

    else if (statnum > 15) {
        bonus = "(+ 2)";
    }

    else if (statnum > 12) {
        bonus = "(+ 1)";
    }

    else if (statnum > 8) {
        bonus = "(+ 0)";
    }

    else if (statnum > 5) {
        bonus = "(- 1)";
    }

    else if (statnum > 3) {
        bonus = "(- 2)";
    }

    std::string result = std::to_string(statnum) + " " + bonus;
    return result;
}

std::string sorbGap(int statval) {

    std::string result = "\t\t";

    if (statval > 9) {

        result = "\t";
    }

    return result;
}

void showStats(int *statarr, bool showbonus = false, bool shownum = false) {

    std::cout << std::endl;

    if (showbonus) {

        std::cout << "Strength: " << StatQuality(statarr[0]) << "\t" << "Intelligence: " << StatQuality(statarr[1]) << "\t" << "Wisdom: " << StatQuality(statarr[2])<< std::endl;
        std::cout << "Constitution: " << StatQuality(statarr[3]) << "\t" << "Dexterity: " << StatQuality(statarr[4]) << "\t" << "Charisma: " << StatQuality(statarr[5]) << std::endl;

    } else if (shownum) {

        std::cout << "1. Strength: " << statarr[0] << "\t\t" << "2. Intelligence: " << statarr[1] << "\t" << "3. Wisdom: " << statarr[2]<< std::endl;
        std::cout << "4. Constitution: " << statarr[3] << "\t" << "5. Dexterity: " << statarr[4] << sorbGap(statarr[4]) << "6. Charisma: " << statarr[5] << std::endl;

    } else {

        std::cout << "Strength: " << statarr[0] << "\t\t" << "Intelligence: " << statarr[1] << sorbGap(statarr[1])  << "Wisdom: " << statarr[2] << std::endl;
        std::cout << "Constitution: " << statarr[3] << sorbGap(statarr[3]) << "Dexterity: " << statarr[4] << "\t\t"  << "Charisma: " << statarr[5] << std::endl;
    }
}

void showSheet() {

    std::cout << std::endl;
    std::cout << "\t\t" << adventurer.name << ", the " << adventurer.advclass << std::endl;
    showStats(adventurer.stats);
    std::cout << "Gold: " << adventurer.stats[6] << std::endl;
    std::cout << std::endl;
}

int main() {

    int choice;
    bool run = true;
    
    /* Main menu loop */
    while (run) {

        showSheet();
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1. Set adventurer's name \n2. Set adventurer's class \n3. Roll or modify adventurer's stats \n4. Buy adventurer's equipment \n5. Save or load adventurer \n6. Exit" << std::endl;
        std::cin >> choice;
        std::cin.clear();

        /* Name entry */
        if (choice == 1) {

            std::cout << "Please enter your adventurer's name:" << std::endl;
            std::string new_name;
            std::cin.ignore();
            std::getline(std::cin, new_name);

            if (!new_name.empty()) {

                adventurer.name = new_name;
            }

        /* Class selection */
        } else if (choice == 2) {

            bool select = true;

            while (select) {

                int numclasses = advclassnames.size();
                std::cout << "Choose a new adventuring class:" << std::endl;

                for (int i=0; i<numclasses; i++) {

                    std::cout << i+1 << ". " << advclassnames.at(i) << std::endl;
                }

                std::cout << numclasses+1 << ". Cancel" << std::endl;

                int advclasschoice;
                std::cin >> advclasschoice;
                std::cin.clear();

                if (advclasschoice > 0 && advclasschoice <= numclasses) {

                    adventurer.advclass = advclassnames.at(advclasschoice-1);
                    select = false;

                } else if (advclasschoice == numclasses+1) {

                    select = false;
                }
            }

        /* Stat rollup and modification */
        } else if (choice == 3) {

            bool rolling = true;
            int newstats[7];

            for (int i=0; i<7; i++) {
                
                newstats[i] = adventurer.stats[i];
            }

            bool bonuses = false;
            bool modified = false;
            while (rolling) {

                /* Submenu */

                if (modified) {

                    std::cout << "\nYour (modified) stat sheet" << std::endl;

                } else {

                    std::cout << "\nYour stat sheet" << std::endl;
                }
                
                showStats(newstats, bonuses);
                bonuses = false;
                std::cout << "Gold: " << newstats[6] << std::endl << std::endl;
                std::cout << "Select an option: \n1. (Re)Roll \n2. Edit \n3. Save \n4. Cancel" << std::endl;
                int rollchoice;
                std::cin >> rollchoice;
                std::cin.clear();

                /* Rollup adventurer's stats */
                if (rollchoice == 1) {

                    for (int i=0; i<7; i++) {

                        newstats[i] = roll_nd6(3);
                    }

                    /* Multiply adventurer's gold */
                    newstats[6] *= 10;

                    bonuses = true;
                    modified = true;

                /* Edit stats */
                } else if (rollchoice == 2) {

                    bool edit = true;

                    while (edit) {

                        // Show user options and get input
                        std::cout << "\nEdit which stat?: " << std::endl;
                        showStats(newstats, false, true);
                        std::cout << "7. Gold: " << newstats[6] << "\n\n8. Done!" << std::endl;
                        int editchoice;
                        std::cin >> editchoice;
                        std::cin.clear();

                        // Edit stats 1-7
                        if (editchoice > 0 && editchoice < 8) {

                            std::cout << "\nEnter a new value for your " << statnames[editchoice-1] << ":" << std::endl;
                            int newvalue;
                            std::cin >> newvalue;
                            std::cin.clear();

                            // Set new stat value
                            newstats[editchoice-1] = newvalue;
                            modified = true;
                        }

                        // Done editing
                        if (editchoice == 8) {
                            edit = false;
                        }
                    }

                /* Save stats */
                } else if (rollchoice == 3) {

                    for (int i=0; i<7; i++) {
                        adventurer.stats[i] = newstats[i];
                    }

                    rolling = false;

                } else if (rollchoice == 4) {

                    rolling = false;
                }
            }

        /* Exit program */
        } else if (choice == 6) {

            run = false;
        }
    }

    return 0;
}