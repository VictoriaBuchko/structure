#include <iostream>
using namespace std;

struct Film {
    char title[100];
    char director[100];
    char genre[50];
    float popularityRating;
    float price;
};

//Функция добавления параметров структуры 
int addFilm(Film films[], int MAX_FILMS, int numFilms, const char* title, const char* director, const char* genre, float popularityRating, float price);
void displayAllFilms(const Film films[], int numFilms);                                  //Функция вывода всех фильмов 
void PopularFilm(const Film films[], int numFilms, const char* genre);                   //Функция нахождения самого популярного фильма в определенном жанре 
void searchByField(const Film films[], int numFilms, int fieldChoice, const char* value);//Функция поиска фильма по параметрам(названию фильма, режисеру, жанр)


int main() {
    setlocale(LC_ALL, "Ukrainian");

    const int MAX_FILMS = 20;//максимальное количество возможных фильмов 
    Film films[MAX_FILMS];
    int numFilms = 0;//первоначальное количество фильмов в магазине 


    //Передаем в функцию жобавления параметры которые будут занесены в структуру и numFilms, который будет играть счетчиком количества фильмов 
    numFilms = addFilm(films, MAX_FILMS, numFilms, "Titanic", "James Cameron", "Romance", 8.5, 15.50);
    numFilms = addFilm(films, MAX_FILMS, numFilms, "Mulan", "Nicky Caro", "Drama", 7.8, 10.50);
    numFilms = addFilm(films, MAX_FILMS, numFilms, "Barbie", "Greta Gerwig", "Comedy", 8.2, 12.99);
    numFilms = addFilm(films, MAX_FILMS, numFilms, "Oppenheimer", "Christopher Nolan", "Action", 8.2, 16.50);
    numFilms = addFilm(films, MAX_FILMS, numFilms, "Hatiko", "Kristina Boden", "Drama", 8.2, 12.99);

    while (true) {

        //Запрашиваем у пользователя что он хочет осуществить в нашей программе 

        cout << "\n\nSelect action:\n";
        cout << "1 - Search by field (Title, Director, Genre)\n";
        cout << "2 - Find the most popular movie in the genre\n";
        cout << "3 - Display all records\n";
        cout << "0 - Exit\n";

        int choice;
        cin >> choice;


        cout << endl;

        if (choice == 0) {
            break;
        }

        char value[100];// создаем масив чаров в который запишем поисковой запрос пользователя

        if (choice == 1) {

            cout << "Select a search field (1 - Title, 2 - Director, 3 - Genre): ";

            int fieldChoice;
            cin >> fieldChoice;
            cout << "Enter search value: ";
            cin.ignore();
            cin.getline(value, sizeof(value));//можно было использовать так же fgets(,). Используем такой меттод воода что мы считало 2 слова если таковы имеються

            searchByField(films, numFilms, fieldChoice, value);
        }
        else if (choice == 2) {

            cout << "Enter the genre to search(жанр): ";
            cin.ignore();
            cin.getline(value, sizeof(value));

            PopularFilm(films, numFilms, value);
        }
        else if (choice == 3) {

            displayAllFilms(films, numFilms);
        }
    }
    return 0;
}


//Добавление информации в структуру 
int addFilm(Film films[], int MAX_FILMS, int numFilms, const char* title, const char* director, const char* genre, float popularityRating, float price) {

    if (numFilms < MAX_FILMS) {

        Film newFilm;

        strcpy_s(newFilm.title, title);
        strcpy_s(newFilm.director, director);
        strcpy_s(newFilm.genre, genre);

        newFilm.popularityRating = popularityRating;
        newFilm.price = price;

        films[numFilms] = newFilm;
        return numFilms + 1;
    }
    else {
        cout << "The video store is full\n";
        return numFilms;
    }
}

//Вывод всех фильмов и всей информации про них
void displayAllFilms(const Film films[], int numFilms) {

    if (numFilms == 0) {

        cout << "There are no films in the store\n";
        return;
    }

    cout << "List all movies:\n";

    for (int i = 0; i < numFilms; i++) {
        cout << "Movie " << i + 1 << ":\n";
        cout << "Title: " << films[i].title << endl;
        cout << "Director: " << films[i].director << endl;
        cout << "Genre: " << films[i].genre << endl;
        cout << "Popularity Rating: " << films[i].popularityRating << endl;
        cout << "Price: " << films[i].price << endl;
        cout << "-----------------------\n\n";
    }
}

//Вывод самого поаулярного фильма среди одного жанра 
void PopularFilm(const Film films[], int numFilms, const char* genre) {

    float maxPopularity = 0;//счетчик для отслеживания самого популярного фильма в определенном жанре
    Film mostPopularFilm;//переменная для хранения названия фильма

    for (int i = 0; i < numFilms; i++) {

        if (strcmp(films[i].genre, genre) == 0) {

            if (films[i].popularityRating > maxPopularity) {

                maxPopularity = films[i].popularityRating;
                mostPopularFilm = films[i];
            }
        }
    }

    if (maxPopularity > 0) {

        cout << "The most popular film in the genre '" << genre << "':\n";
        cout << "Title: " << mostPopularFilm.title << endl;
        cout << "Director: " << mostPopularFilm.director << endl;
        cout << "Popularity Rating: " << mostPopularFilm.popularityRating << endl;
        cout << "Price: " << mostPopularFilm.price << endl;
    }
    else {
        cout << "Movies in the genre '" << genre << "' not found\n";
    }
}

//Поиск фильма по ( названию, режисеру или же жанру)
void searchByField(const Film films[], int numFilms, int fieldChoice, const char* value) {

    for (int i = 0; i < numFilms; i++) {

        bool match = false;

        switch (fieldChoice) {
        case 1:
            match = (strcmp(films[i].title, value) == 0);
            break;
        case 2:
            match = (strcmp(films[i].director, value) == 0);
            break;
        case 3:
            match = (strcmp(films[i].genre, value) == 0);
            break;
        default:
            cout << "Invalid field selection\n";
            return;
        }
        if (match) {

            cout << "Title: " << films[i].title << endl;
            cout << "Director: " << films[i].director << endl;
            cout << "Genre: " << films[i].genre << endl;
            cout << "Popularity Rating: " << films[i].popularityRating << endl;
            cout << "Price: " << films[i].price << endl;
            return;
        }
    }
    cout << "Movie with " << value << " was not found in the selected field\n";
}