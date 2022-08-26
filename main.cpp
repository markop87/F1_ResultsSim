#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <algorithm>

using namespace std;

struct Circut {
    string gpname;
    int laps;
    int lap_time;
};

struct Team {
    int teamID;
    string name;
    string short3;
    int points;
};

struct Driver {
    int driverID;
    int number;
    string name;
    string short3;
    int teamID;
    int quality;
    int points;
};

struct Result {
    int circut;
    int driverID;
    int laps;
    int time;
    int best_lap;
    int points;
    int order;

    Result(int c, int d, int l, int t, int b, int p, int o) {
        circut = c;
        driverID = d;
        laps = l;
        time = t;
        best_lap = b;
        points = p;
        order = o;
    }

};

struct sortResults //sorting race results by time and laps completed if time is equal
{
    inline bool operator() (const Result& struct1, const Result& struct2)
    {
        if(struct1.time != struct2.time)
            return (struct1.time < struct2.time);
        return (struct1.laps > struct2.laps);
    }
};

vector <Circut> circuts = {
    {" ", 0, 0},
    {"Bahrain GP", 52, 94570},
    {"Saudi Arabian GP", 50, 91634},
    {"Australian GP", 58, 80260},
    {"Emilia Romagna GP", 63, 78446},
    {"Miami GP", 57, 91361},
    {"Spanish GP", 66, 78750},
    {"Monaco GP", 78, 74693},
    {"Azerbaijan GP", 51, 106046},
    {"Canadian GP", 70, 75749},
    {"British GP", 52, 90510},
    {"Austrian GP", 71, 67275},
    {"French GP", 53, 96404},
    {"Hungarian GP", 70, 78394},
    {"Belgian GP", 44, 107483},
    {"Dutch GP", 72, 71097},
    {"Italian GP", 53, 84812},
    {"Singapore GP", 61, 102301},
    {"Japanese GP", 53, 90983},
    {"United States GP", 56, 98485},
    {"Mexico City GP", 71, 77774},
    {"Sao Paulo GP", 71, 71010},
    {"Abu Dhabi GP", 58, 86103},
};

struct sortRanking //sorting drivers championship standings by points
{
    inline bool operator() (const Driver& struct1, const Driver& struct2)
    {
        return (struct1.points > struct2.points);
    }
};

vector <Team> teams = {
    {1, "Ferrari", "FER", 0},
    {2, "Red Bull", "RBL", 0},
    {3, "Mercedes", "MER", 0},
    {4, "Aston Martin", "AST", 0},
    {5, "AlphaTauri", "ATU", 0},
    {6, "Alpine", "ALP", 0},
    {7, "Alfa Romeo", "ALF", 0},
    {8, "McLaren", "MCL", 0},
    {9, "Haas", "HAA", 0},
    {10, "Williams", "WIL", 0}
};

struct sortTeams //sorting constructors championship standings by points
{
    inline bool operator() (const Team& struct1, const Team& struct2)
    {
        return (struct1.points > struct2.points);
    }
};

vector <Driver> drivers = {
    { 1, 24, "Zhou Guanyu", "ZHO", 7, 60, 0},
    { 2, 77, "Valtteri Bottas", "BOT", 7, 65, 0},
    { 3, 10, "Pierre Gasly", "GAS", 5, 65, 0},
    { 4, 22, "Yuki Tsunada", "TSU", 5, 60, 0},
    { 5, 14, "Fernando Alonso", "ALO", 6, 75, 0},
    { 6, 31, "Esteban Ocon", "OCO", 6, 70, 0},
    { 7, 5, "Sebastian Vettel", "VET", 4, 70, 0},
    { 8, 18, "Lance Stroll", "STR", 4, 60, 0},
    { 9, 16, "Charles Leclerc", "LEC", 1, 95, 0},
    { 10, 55, "Carlos Sainz Jr.", "SAI", 1, 85, 0},
    { 11, 20, "Kevin Magnussen", "MAG", 9, 60, 0},
    { 12, 47, "Mick Schumacher", "MSC", 9, 55, 0},
    { 13, 3, "Daniel Ricciardo", "RIC", 8, 65, 0},
    { 14, 4, "Lando Norris", "NOR", 8, 75, 0},
    { 15, 44, "Lewis Hamilton", "HAM", 3, 95, 0},
    { 16, 63, "George Russell", "RUS", 3, 85, 0},
    { 17, 1, "Max Vertappen", "VER", 2, 100, 0},
    { 18, 11, "Sergio Perez", "PER", 2, 85, 0},
    { 19, 6, "Nicholas Latifi", "LAT", 10, 50, 0},
    { 20, 23, "Alexander Albion", "ALB", 10, 55, 0}
};

vector <Result> results;

//generate random number
int getNumber(int x, int y) {
    static mt19937 gen(time(nullptr));; // seed the generator
    uniform_int_distribution<> distr(x, y); //range
    return distr(gen);
}

//function to print saved time in ms in format minutes:seconds.miliseconds
string timeFormat (int z)
{
    int minutes=0;

    while (z > 59999) {
     z = z - 60000;
     minutes++;
    }

    int seconds = z / 1000;

    int miliseconds = z % 1000;

    stringstream ss;

        if(seconds < 10 && miliseconds < 10)
            ss << minutes << ":0" << seconds << ".00" << miliseconds;
        else if(seconds < 10 && miliseconds > 100)
            ss << minutes << ":0" << seconds << "." << miliseconds;
        else if(seconds < 10 && miliseconds > 9 && miliseconds < 100)
            ss << minutes << ":0" << seconds << ".0" << miliseconds;
        else if(seconds > 10 && miliseconds < 10)
            ss << minutes << ":" << seconds << ".00" << miliseconds;
        else if(seconds > 10 && miliseconds > 9 && miliseconds < 100)
            ss << minutes << ":" << seconds << ".0" << miliseconds;
        else ss << minutes << ":" << seconds << "." << miliseconds;

    return ss.str();
}

int main()
{
system("title Simple F1 Results Sim");

char again;
int order = 1;
int circut = 0, choice = -1;

do
{
    system("CLS");

    //menu
    if(choice != 0)
    {
        for (int c = 1; c < 23; c++)
        {
            cout << c << ". " << circuts[c].gpname << endl;
        }
        cout << "0. " << "Simulate full season" << endl;

        cout << "Choose a circut: ";
        cin >> choice;

        //reseting drivers and team points to 0 before full season
        if(choice == 0)
        {
            circut = 0;

            for(int a = 0; a < 20; a++)
            {
                drivers[a].points = 0;
            }

            for(int b = 0; b < 10; b++)
            {
                teams[b].points = 0;
            }
        }
    }

    system("CLS");

    //incrementing through circuts if simulating full season
    if(choice == 0)
    {
        circut++;
    }
    else circut = choice;

    if(choice == 0) //printing name of a race in two version: full season or single race
    {
        cout << "Results of " << circuts[circut].gpname << " - " << circut << "/22 - (" << circuts[circut].laps << " laps):" << endl;
    } else cout << "Results of " << circuts[circut].gpname << " (" << circuts[circut].laps << " laps):" << endl;

    //simulating driver time based on his quality parameter
    for(int d = 0; d < 20; d++)
    {
        int lap_time = 0, full_time = 0, last_lap = 0, best_lap = 9999999, points = 0, lap_counter;

        for(int l = 1; l <= circuts[circut].laps; l++)
        {
            if(l == 1)
            {
                lap_time = circuts[circut].lap_time + getNumber(-drivers[d].quality, 450 - drivers[d].quality*2) + 450;
            } else lap_time = last_lap + getNumber(- drivers[d].quality*2, 200 - drivers[d].quality);

            //saving driver's best lap time
            if (lap_time < best_lap)
            {
                best_lap = lap_time;
            }

            last_lap = lap_time;
            full_time += lap_time;
            lap_counter = l;

            //drawing number from 1 to 300, 69 means driver had an accident and didn't finish the race
            int accident = getNumber(0, 300);

            if(accident == 69)
            {
                full_time = 99999999;
                break;
            }
        }
        //adding result to vector "results"
        Result finish(circut, drivers[d].driverID, lap_counter, full_time, best_lap, points, order);
        results.push_back(finish);
    }

    //sorting results
    sort(results.begin(), results.end(), sortResults());

    int pl = 1;

    for(int r = 0; r < results.size(); r++)
    {
        if(results[r].circut == circut && results[r].order == order)
        {
            //adding points for places
            if (pl == 1) { results[r].points = 25; }
            if (pl == 2) { results[r].points = 18; }
            if (pl == 3) { results[r].points = 15; }
            if (pl == 4) { results[r].points = 12; }
            if (pl == 5) { results[r].points = 10; }
            if (pl == 6) { results[r].points = 8; }
            if (pl == 7) { results[r].points = 6; }
            if (pl == 8) { results[r].points = 4; }
            if (pl == 9) { results[r].points = 2; }
            if (pl == 10) { results[r].points = 1; }

            for(int d = 0; d < 20; d++)
            {
                //printing results
                if(results[r].driverID == drivers[d].driverID)
                {
                    cout << setw(2) << pl << ". ";
                    cout << setw(25) << left << drivers[d].name;

                    for(int t = 0; t < 10; t++)
                    {
                        if(drivers[d].teamID == teams[t].teamID)
                        {
                            cout << teams[t].short3 << "\t";
                        }
                    }

                    if(results[r].time == 99999999)
                    {
                        cout << "DNF(L:" << setw(2) << right << results[r].laps << ")";
                    }
                    else cout << setw(9) << timeFormat(results[r].time);

                    cout << " (" << timeFormat(results[r].best_lap) << ")\t";
                    cout << setw(2) << right << results[r].points << endl;
                    pl++;

                }
            }

            for(int x = 0; x < 20; x++) //adding points to drivers championship after the race
            {
                if(drivers[x].driverID == results[r].driverID)
                {
                    drivers[x].points += results[r].points;


                    for(int y = 0; y < 10; y++) //adding points to constructors championship after the race
                    {
                        if(teams[y].teamID == drivers[x].teamID)
                        {
                            teams[y].points += results[r].points;
                        }
                    }
                }
            }
        }
    }

    //printing championship standings in full season mode
    if(choice == 0)
    {
        cout << "\n\n";
        system("pause");
        system("CLS");

        cout << "Championship ranking after " << circut << " of 22 rounds:\n";

        sort(drivers.begin(), drivers.end(), sortRanking());

        for(int c = 0; c < 20; c++)
        {
            cout << setw(2) << c+1 << ". ";
            cout << setw(25) << left << drivers[c].name;

            for(int t = 0; t < 10; t++)
                {
                    if(drivers[c].teamID == teams[t].teamID)
                    {
                            cout << teams[t].short3 << "\t";
                    }
                }

            cout << setw(4) << right << drivers[c].points << endl;
        }

        cout << "\n\nConstructors ranking after " << circut << " of 22 rounds:\n";

        sort(teams.begin(), teams.end(), sortTeams());

        for(int x = 0; x < 10; x++)
        {
            cout << setw(2) << x+1 << ". ";
            cout << setw(25) << left << teams[x].name;
            cout << setw(4) << right << teams[x].points << endl;
        }
        cout << "\n\n";
    }

    if(choice != 0)
    {
        cout << "\n\nAnother race (Y)? ";
        cin >> again;
    }
    else if (choice == 0 && circut != 22)
    {
        system("pause");
    }

    else if(choice == 0 && circut == 22)
    {
        cout << "\n\nThis is the end of a season!" << endl;
        break;
    }

    order++;

} while((choice == 0 && circut < 23) || again == 'y' || again == 'Y');

return 0;
}
