#include <ncurses.h>
#include "../includes/interactmode.h"
#include "../includes/dates.h"
#define DATE_REFERENCE "09/10/2022"

char q8_title[11][100] ={"   /$$$$$$                                                 /$$$$$$ ",
                         "  /$$__  $$                                               /$$__  $$",
                         " | $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$      | $$  | $$",
                         " | $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$      |  $$$$$$/",
                         " | $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$       >$$__  $$",
                         " | $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$      | $$  | $$",
                         " |  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$      |  $$$$$$/",
                         " |____ $$$ |______/  |_______/|__/       |____  $$       |______/  ",
                         "      |__/                               /$$  | $$                 ",
                         "                                        |  $$$$$$/                 ",
                         "                                         |______/                  "};

void q8_output(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, char gender, int n, int x, int y) {
    int id_driver;
    char* id_user;
    char* name_driver;
    char* name_user;
    unsigned int id_ride = 0;
    unsigned short int age_in_days = convert_to_day (DATE_REFERENCE) - (n * 365) - 3; // Calcular o dia a partir do qual a idade é maior à pedida
    unsigned int * array_ids =  check_gender_in_rides (catalog_rides, gender, age_in_days); //recebe o array de ids que correspondem às viagens válidas
    int length = 0;
    
    for (int i = 0; array_ids[i]!=0; i++) {
        int id_ride2 = array_ids [i];
        int id_driver2 = get_ride_driver (catalog_rides, id_ride2); // tem que se subtrair 1 para aceder ao array mas não quando se for imprimir ---> tratar disto
        char* id_user2 = get_ride_user (catalog_rides, id_ride2);
        if (get_driver_acc_Status (catalog_drivers,id_driver2 - 1) && getAccountStatusUser(catalog_users,id_user2))length++;
        free(id_user2);
    }

    int pages;
    if (n % 30 == 0) pages = length / 30;
    else pages = length / 30 + 1;
    int done = 0;
    int page = 0;

    keypad(stdscr, TRUE);

    while (!done) {
        clear();
        
        int start = page * 30;
        int end = start + 30;
        if (end > length) {
            end = length;
        }
        
        mvprintw(45, x/2 - strlen ("Page 1 / 1")/2 , "Page %d / %d", page + 1, pages);
        int a = 0;
        mvprintw(9, x/2 + 12 - strlen("                Driver ID                |                Driver's name                |                User's username                |                User's name                ")/2, "Driver ID                |                Driver's name                |                User's username                |                User's name                ");
        for (int i = start; i < end; i++) {
            if (a % 31 == 0) a *= 0;
            id_ride = array_ids [i];
            id_driver = get_ride_driver (catalog_rides, id_ride); 
            id_user = get_ride_user (catalog_rides, id_ride);
            name_driver = get_driver_name (catalog_drivers, id_driver - 1);
            name_user = getNameUser (catalog_users, id_user);
            if (get_driver_acc_Status (catalog_drivers,id_driver - 1) && getAccountStatusUser(catalog_users,id_user)) {
                mvprintw(a + 11, 23, "%012d", id_driver);
                mvprintw(a + 11, 64, "%s", name_driver);
                mvprintw(a + 11, 111, "%s", id_user);
                mvprintw(a + 11, 157, "%s", name_user);
                a++;
            }
            free (id_user);
            free (name_driver);
            free(name_user);
        }
        
        mvprintw(50, x/2 - strlen("Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial")/2 , "Pressione 'N' para ver a próxima página, 'B' para a página anterior, 'Q' para voltar ao Menu Inicial");
        int ch = getch();
        switch (ch) {
        case 'n':
        case 'N':
            page++;
            if (page >= pages) {
            page = pages - 1;
            }
            break;
        case 'b':
        case 'B':
            page--;
            if (page < 0) {
            page = 0;
            }
            break;
        case 'q':
        case 'Q':
            done = 1;
            clear();
            queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
        }
    }
}

void query8_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q8_title[j])/2, "%s", q8_title[j]);
    }
    mvprintw(16, x/2 - strlen("Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro, representado por <gender> e têm perfis com X ou mais anos, sendo X representado por <X>. O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro")/2, "Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro, representado por <gender> e têm perfis com X ou mais anos, sendo X representado por <X>. O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro"); 
    mvprintw(17, x/2 - strlen("mais especificamente, ordenar por conta mais antiga de condutor e, se necessário, pela conta do utilizador. Se persistirem empates, ordenar por id da viagem (em ordem crescente)")/2, "mais especificamente, ordenar por conta mais antiga de condutor e, se necessário, pela conta do utilizador. Se persistirem empates, ordenar por id da viagem (em ordem crescente)");
    mvprintw(20, x/2 - strlen("Introduza o género pretendido (Masculino) ou (Feminino): ")/2 - 1, "Introduza o género pretendido (Masculino) ou (Feminino): ");
    
    echo();
    char g[10];
    getnstr(g, 19);
    char gender;

    if (strcmp(g, "Masculino") == 0) gender = 'M';
    else gender = 'F';

    noecho();
    cbreak();

    clear();
    for (int j = 0; j < 11; j++) {
        mvprintw(j + 3, x/2 - strlen(q8_title[j])/2, "%s", q8_title[j]);
    }
    mvprintw(16, x/2 - strlen("Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro, representado por <gender> e têm perfis com X ou mais anos, sendo X representado por <X>. O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro")/2, "Listar todas as viagens nas quais o utilizador e o condutor são do género passado como parâmetro, representado por <gender> e têm perfis com X ou mais anos, sendo X representado por <X>. O output deverá ser ordenado de forma que as contas mais antigas apareçam primeiro"); 
    mvprintw(17, x/2 - strlen("mais especificamente, ordenar por conta mais antiga de condutor e, se necessário, pela conta do utilizador. Se persistirem empates, ordenar por id da viagem (em ordem crescente)")/2, "mais especificamente, ordenar por conta mais antiga de condutor e, se necessário, pela conta do utilizador. Se persistirem empates, ordenar por id da viagem (em ordem crescente)");
    mvprintw(20, x/2 - strlen("Introduza o X (em anos): "), "Introduza o X (em anos): ");

    echo();
    char years[5];
    getnstr(years, 5);
    int n = atoi(years);

    noecho();
    cbreak();

    q8_output(catalog_users, catalog_drivers, catalog_rides, catalog_cities, gender, n, x, y);
}   
