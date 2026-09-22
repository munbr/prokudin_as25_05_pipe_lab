#include<iostream>
#include<string>
#include<fstream>
#include<limits>
using namespace std;

template <typename T>
T read_number(const string& prompt, T lo, T hi)
{
    T value;
    cout << prompt << endl;
    while(!(cin>>value) || value < lo || value > hi)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Ошибка. " << prompt << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return value;
}

string read_line(const string& prompt)
{
    string s;
    cout << prompt << endl;
    while (s.empty()) getline(cin, s);
    return s;
}
void print_menu()
{
    cout << "Выберите опцию\n"
         << "1 - Создать трубу\n"
         << "2 - Редактировать трубу\n"
         << "3 - Создать КС\n"
         << "4 - Редактировать КС\n"
         << "5 - Посмотреть все элементы\n"
         << "6 - Сохранить элементы\n"
         << "7 - Загрузить элементы\n"
         << "0 - Выйти из программы";
}

struct CS
{   
    string name;
    int num_workshops = 0;
    int num_on_workshops = 0;
    string station_class;
    bool is_created = false;
};

void settings_cs(CS& cs)
{
    cs.name = read_line("Задайте имя КС:");
    cs.num_workshops = read_number("Задайте кол-во цехов:", 1, INT_MAX);
    cs.num_on_workshops = read_number("Выберите сколько цехов в работе:", 0, cs.num_workshops);
    cs.station_class = read_line("Задайте характеристику КС:");
    cs.is_created = true;
    cout <<  "КС " << cs.name << " задана" << endl;
}
void edit_cs(CS& cs)
{
    if(!(cs.is_created))
    {
        cout << "КС ещё не создана — нечего редактировать." << endl;
        return;
    }
    while (true)
    {
        int check = read_number("1 - Изменить работающие цеха.\n0 - Закончить редактирование.", 0, 1);
        
        if(check == 0) break;

        cs.num_on_workshops = read_number("1 - Изменить работающие цеха.\n0 - Закончить редактирование.", 0, cs.num_workshops);
        
    }

}
void show_cs(const CS& cs)
{
    if(!(cs.is_created))
    {
        cout << "КС ещё не задана" << endl;
        return;
    }
    cout << "Название КС - " << cs.name << endl;
    cout << "Кол-во цехов - " << cs.num_workshops << endl;
    cout << "Кол-во цехов в работе - " << cs.num_on_workshops << endl;
    cout << "Характеристика КС - " << cs.station_class << endl;
}

struct PIPE
{   
    string name;
    double pipe_length = 0;
    double pipe_diam = 0;
    bool pipe_tech = false;
    bool is_created = false;
};

void settings_pipe(PIPE& pipe)
{
    pipe.name = read_line("Задайте имя трубы:");
    pipe.pipe_length = read_number("Задайте длину трубы:", 1, INT_MAX);
    pipe.pipe_diam = read_number("Задайте диаметр трубы:", 1, INT_MAX);
    int isBreak = read_number("В работе ли труба?\nВыберите\n0 - если труба в ремонте\n1 - если труба работоспособна", 0, 1);
    pipe.pipe_tech = (isBreak == 1);
    pipe.is_created = true;
    cout << "Труба " << pipe.name << " задана" << endl;
}
void edit_pipe(PIPE& p)
{
    if (!p.is_created)
    {
        cout << "Труба ещё не создана — нечего редактировать." << endl;
        return;
    }
    while (true)
    {
        int check = read_number("Выберите, что вы хотите отредактировать\n1 - в ремонте ли труба\n0 - закончить редактирование", 0, 1);
        if (check == 0) break;
        int isBreak = read_number("Выберете 0 - если труба в ремонте, 1 - если труба работоспособна", 0, 1);
        p.pipe_tech = (isBreak == 1);
    }
    cout << "Труба " << p.name << " отредактирована" << endl;
}
void show_pipe(const PIPE& pipe)
{
    if(!(pipe.is_created))
    {
        cout << "Труба ещё не задана" << endl;
        return;
    }
    cout << "Название трубы - " << pipe.name << endl;
    cout << "Диаметр трубы - " << pipe.pipe_diam << endl;
    cout << "Длина трубы - " << pipe.pipe_length << endl;
    cout << (pipe.pipe_tech? "Труба в работе" : "Труба не работает") << endl;
}

void save_cs(ofstream& file, const CS& cs)
{
    file << cs.is_created << endl;
    if (cs.is_created)
    {
        file << cs.name << endl;
        file << cs.num_workshops << endl;
        file << cs.station_class << endl;
        file << cs.num_on_workshops << endl;
    }
}
void save_pipe(ofstream& file, const PIPE& pipe)
{
    file << pipe.is_created << endl;
    if (pipe.is_created)
    {
        file << pipe.name << endl;
        file << pipe.pipe_diam << endl;
        file << pipe.pipe_length << endl;
        file << pipe.pipe_tech << endl;
    }
}
void save_all(const CS& cs, const PIPE& pipe)
{
    if (!cs.is_created && !pipe.is_created)
    {
        cout << "Нет данных для сохранения." << endl;
        return;
    }

    ofstream file("save.txt");
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл для записи." << endl;
        return;
    }
    save_cs(file, cs);                     
    save_pipe(file, pipe);
    if(!file)
    {
        file.close();
        cout << "Сохранение не выполнено." << endl;
        return;
    }
    file.close();
    cout << "Сохранение выполнено." << endl;
}   

void load_cs(ifstream& file, CS& cs)
{
    int cs_created = 0;
    file >> cs_created;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!file)
    {
        cout << "Файл повреждён (блок КС)." << endl;
        return;
    }

    if (cs_created)
    {
        getline(file, cs.name);
        file >> cs.num_workshops;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, cs.station_class);
        file >> cs.num_on_workshops;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        cs.is_created = true;
    }
    else
    {
        cs.is_created = false;
    }
}
void load_pipe(ifstream& file, PIPE& pipe)
{
    int pipe_created = 0;
    file >> pipe_created;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!file)
    {
        cout << "Файл повреждён (блок трубы)." << endl;
        return;
    }
    if (pipe_created)
    {
        getline(file, pipe.name);
        file >> pipe.pipe_diam;
        file >> pipe.pipe_length;
        file >> pipe.pipe_tech;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        pipe.is_created = true;
    }
    else
    {
        pipe.is_created = false;
    }
}
void load_all(CS& cs, PIPE& pipe)
{
    ifstream file("save.txt");
    if (!file.is_open())
    {
        cout << "Файл save.txt не найден." << endl;
        return;
    }
    load_cs(file, cs);
    load_pipe(file, pipe);
    if (!file)
        {
            cout << "Файл повреждён (не хватает данных)." << endl;
            return;
        }
    file.close();

    cout << "Данные успешно загружены." << endl;
    cout << "  КС: " << (cs.is_created ? "загружена" : "нет") << endl;
    cout << "  Труба: " << (pipe.is_created ? "загружена" : "нет") << endl;
}
int main()
{
    PIPE pipe;
    CS cs;
    while (true)
    {
        print_menu();
        int option = read_number("", 0, 7);
        switch (option)
        {
        case 1:
            settings_pipe(pipe);          break;
        case 2:
            edit_pipe(pipe);              break;
        case 3:
            settings_cs(cs);              break;
        case 4:
            edit_cs(cs);                  break;
        case 5:
            show_pipe(pipe); show_cs(cs); break;
        case 6:
            save_all(cs,pipe);            break;
        case 7:
            load_all(cs, pipe);           break;
        case 0:
        break;

        default:
            break; 
        }  
    }
    return 0;
}