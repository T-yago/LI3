#include <ncurses.h>
#include <ctype.h>
#include <string.h>
#include "../includes/interactmode.h"

char q1_title [11][100] = {"  /$$$$$$                                                 /$$$  ",
                           " /$$__  $$                                               /$$$$  ",
                           "| $$  | $$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$      |_  $$  ",
                           "| $$  | $$| $$  | $$ /$$__  $$ /$$__  $$| $$  | $$        | $$  ",
                           "| $$  | $$| $$  | $$| $$$$$$$$| $$  |__/| $$  | $$        | $$  ",
                           "| $$/$$ $$| $$  | $$| $$_____/| $$      | $$  | $$        | $$  ",
                           "|  $$$$$$/|  $$$$$$/|  $$$$$$$| $$      |  $$$$$$$       /$$$$$$",
                           "|_____ $$$|_______/ |________/|__/      |_____  $$      |______/",
                           "     |___/                               /$$ | $$/              ",
                           "                                        | $$$$$$/               ",
                           "                                        |______/                "};

void printbox(int x) {
    mvprintw(35, x/2 - 32, "________________________________________________________________");
    mvprintw(36, x/2 - 32, "|                                                              |");
    mvprintw(37, x/2 - 32, "|                                                              |");
    mvprintw(38, x/2 - 32, "|                                                              |");
    mvprintw(39, x/2 - 32, "|                                                              |");
    mvprintw(40, x/2 - 32, "|                                                              |");
    mvprintw(41, x/2 - 32, "|                                                              |");
    mvprintw(42, x/2 - 32, "|______________________________________________________________|");
}
void query1_menu(Catalog_Users *catalog_users, Catalog_Drivers *catalog_drivers, Catalog_Rides *catalog_rides, Catalog_Cities *catalog_cities, int x, int y) {
    for (int j = 0; j < 11; j++) {
            mvprintw(j + 3, x/2 - strlen(q1_title[j])/2, "%s", q1_title[j]);
    }
    mvprintw(16, x/2 - strlen("Listar o resumo de um perfil registado no serviço através do seu identificador, representado por <ID>. Note que o identificador poderá corresponder a um utilizador (i.e., username no ficheiro")/2, "Listar o resumo de um perfil registado no serviço através do seu identificador, representado por <ID>. Note que o identificador poderá corresponder a um utilizador (i.e., username no ficheiro");
    mvprintw(17, x/2 - strlen("users.csv) ou a um condutor (i.e., id no ficheiro drivers.csv). Em cada caso, o output será diferente, mais especificamente:")/2, "users.csv) ou a um condutor (i.e., id no ficheiro drivers.csv). Em cada caso, o output será diferente, mais especificamente:");
    mvprintw(19, 52, "Utilizador");
    mvprintw(22, 27, "nome;genero;idade;avaliacao_media;numero_viagens;total_gasto");
    mvprintw(19, 127, "Condutor");
    mvprintw(22, 100, "nome;genero;idade;avaliacao_media;numero_viagens;total_auferido");
    mvprintw(25, x/2 - strlen("NOTA: Se introduzir um Id inválido, o programa pedirá para introduzir novo ID")/2, "NOTA: Se introduzir um Id inválido, o programa pedirá para introduzir novo ID");
    mvprintw(29, x/2 - strlen("Introduza o ID desejado: ")/2 - 10, "Introduza o ID desejado: ");

    echo();
    char id[50];
    getnstr(id, 50);

    noecho();
    cbreak();

    if (isdigit(id[0]) == 0) {
        if (!getAccountStatusUser(catalog_users, id)) {
            clear();
            query1_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
        }

        mvprintw(33, x/2 - (strlen("Resumo do Perfil ") + strlen(id))/2, "Resumo do Perfil %s", id);
        printbox(x);

        unsigned short int nviagens = getNviagensUser(catalog_users, id);
        double avaliacao_media = (float) get_aval_media_user(catalog_users, id) / (float) nviagens;
        char* genero;
        if (getGenderUser(catalog_users, id) == 'M') genero = "Masculino";
        else genero = "Feminino";
        mvprintw(36, x/2 - 31, "Nome: %s", getNameUser(catalog_users, id));
        mvprintw(37, x/2 - 31, "Genero: %s", genero);
        mvprintw(38, x/2 - 31, "Idade : %d", get_age_user(catalog_users, id));
        mvprintw(39, x/2 - 31, "Avaliação Média: %.3f", avaliacao_media);
        mvprintw(40, x/2 - 31, "Nº de viagens: %d", nviagens);
        mvprintw(41, x/2 - 31, "Total Gasto: %.3f", getTotalGastoUser(catalog_users, id));

        mvprintw(44, x/2 - strlen("Se pretender continuar nesta query, prima C")/2, "Se pretender continuar nesta query, prima C");
        mvprintw(45, x/2 - strlen("Se pretender voltar ao Menu das Queries prima Q")/2, "Se pretender voltar ao Menu das Queries prima Q");

            int ch;
            while(1) {
                ch = getch();
                if(ch == 'Q' || ch == 'q') {
                    clear();
                    queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
                } else if(ch == 'C' || ch == 'c') {
                    clear();
                    query1_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
                }
            }
    }
    else {
        int index = atoi(id);
        if (!get_driver_acc_Status(catalog_drivers, index - 1)) {
            clear();
            query1_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
        }

        mvprintw(33, x/2 - (strlen("Resumo do Perfil ") + strlen(id))/2, "Resumo do Perfil %d", index);
        printbox(x);

        char* genero;
        if (get_driver_gender(catalog_drivers, index - 1) == 'M') genero = "Masculino";
        else genero = "Feminino";
        mvprintw(36, x/2 - 31, "Nome: %s", get_driver_name(catalog_drivers, index - 1));
        mvprintw(37, x/2 - 31, "Genero: %s", genero);
        mvprintw(38, x/2 - 31, "Idade : %d", get_driver_age(catalog_drivers, index - 1));
        mvprintw(39, x/2 - 31, "Avaliação Média: %.3f", get_driver_avalMedia(catalog_drivers, index - 1));
        mvprintw(40, x/2 - 31, "Nº de viagens: %d", get_driver_Nviagens(catalog_drivers, index - 1));
        mvprintw(41, x/2 - 31, "Total Auferido: %.3f", get_driver_total_auferido(catalog_drivers, index - 1));

        mvprintw(44, x/2 - strlen("Se pretender continuar nesta query, prima C")/2, "Se pretender continuar nesta query, prima C");
        mvprintw(45, x/2 - strlen("Se pretender voltar ao Menu das Queries prima Q")/2, "Se pretender voltar ao Menu das Queries prima Q");

            int ch;
            while(1) {
                ch = getch();
                if(ch == 'Q' || ch == 'q') {
                    clear();
                    queries_menu(x, y, catalog_users, catalog_drivers, catalog_rides, catalog_cities);
                } else if(ch == 'C' || ch == 'c') {
                    clear();
                    query1_menu(catalog_users, catalog_drivers, catalog_rides, catalog_cities, x, y);
                }
            }
    }
}