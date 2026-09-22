#include<iostream>
#include<string>
#include<fstream>
#include<limits>
using namespace std;

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
    cout << "Задайте имя КС:" << endl;
    while(cs.name.empty()) getline(cin,cs.name);
    cout << "Задайте кол-во цехов:" << endl;
    while((!(cin>>cs.num_workshops) || cs.num_workshops <= 0))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Ошибка. Задайте осмысленное кол-во цехов:" << endl;
    }
    cout << "Выберите сколько цехов в работе:" << endl;
    while(!(cin>>cs.num_on_workshops) || cs.num_on_workshops < 0 || cs.num_on_workshops > cs.num_workshops)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Ошибка. Задайте осмысленное кол-во цехов:" << endl;
    }
    cout << "Задайте характеристику КС:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,cs.station_class);
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
    bool flag = 1;
    while (flag != 0)
    {
        cout << "Выберите, что вы хотите отредактировать?" << endl;
        cout << "1 - Изменить работающие цеха.\n" << "0 - Закончить редактирование." << endl;
        int check;
        
        while (!(cin >> check) || check < 0 || check > 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка.\n" << "Выберите, что вы хотите отредактировать?\n" << "1 - изменить работающие цеха\n" << "0 - закончить редактирование" << endl;
        }
        switch (check)
        {
        case 1:
            
            cout << "Сколько цехов в работе?" << endl;
            while(!(cin>>cs.num_on_workshops) || cs.num_on_workshops < 0 || cs.num_on_workshops > cs.num_workshops)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Ошибка. Введите число от 0 до "  << cs.num_workshops << endl;
            }
            break;
        case 0:
            flag = 0;
            break;
        
        default:
            break;
        }
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
    cout << "Задайте имя трубы:" << endl;
    while(pipe.name.empty()) getline(cin,pipe.name);

    cout << "Задайте длину трубы:" << endl;
    while( !(cin >> pipe.pipe_length) || pipe.pipe_length <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка.\n" << "Задайте осмысленную длину трубы:" << endl;
    }

    cout << "Задайте диаметр трубы:" << endl;
    while(!(cin >> pipe.pipe_diam) || pipe.pipe_diam <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка.\n" << "Задайте осмысленный диаметр трубы:" << endl;
    }

    cout << "В работе ли труба?" << endl;
    cout << "Выберете 0 - если труба в ремонте, 1 - если труба работоспособна" << endl;
    int isBreak;
    while( !(cin >> isBreak) || isBreak < 0 || isBreak > 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка.\n" << "В работе ли труба?\n" << "Выберете 0 - если труба в ремонте, 1 - если труба работоспособна." << endl;
    }
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
    bool flag = 1;
    while (flag != 0)
    {
    cout << "Выберите, что вы хотите отредактировать\n" << "1 - в ремонте ли труба\n" <<"0 - закончить редактирование" << endl;
        int check;
        while(!(cin >> check) || check < 0 || check > 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка.\n" << "Выберите, что вы хотите отредактировать\n" << "1 - в ремонте ли труба\n" <<"0 - закончить редактирование" << endl;
        }
        switch (check)
        {
        case 1:
            cout << "Выберете 0 - если труба в ремонте, 1 - если труба работоспособна" << endl;
            int isBreak;
            while(!(cin >> isBreak) || isBreak < 0 || isBreak > 1)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка.\n" << "В работе ли труба?\n" << "Выберете 0 - если труба в ремонте, 1 - если труба работоспособна." << endl;   
            }
            p.pipe_tech = (isBreak == 1);
            break;
        case 0:
            flag = 0;
            break;
        default: 
            break;
        }
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
    if (pipe.pipe_tech == 1)
    {
        cout << "Труба в работе" << endl;    
    }
    else
    {
        cout << "Труба не работает" << endl;
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

    //флаги
    file << cs.is_created << " " << pipe.is_created << endl;

    //блок CS
    if (cs.is_created)
    {
        file << cs.name << endl;
        file << cs.num_workshops << endl;
        file << cs.station_class << endl;
        file << cs.num_on_workshops << endl;
    }

    //блок PIPE
    if (pipe.is_created)
    {
        file << pipe.name << endl;
        file << pipe.pipe_diam << endl;
        file << pipe.pipe_length << endl;
        file << pipe.pipe_tech << endl;
    }
    if(!file)
    {
        file.close();
        cout << "Сохранение не выполнено." << endl;
        return;
    }
    file.close();
    cout << "Сохранение выполнено." << endl;
}   
void load_all(CS& cs, PIPE& pipe)
{
    ifstream file("save.txt");
    if (!file.is_open())
    {
        cout << "Файл save.txt не найден." << endl;
        return;
    }

    int cs_created = 0, pipe_created = 0;
    file >> cs_created >> pipe_created;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!file)
    {
        cout << "Файл повреждён (не читаются флаги)." << endl;
        return;
    }

    // блок CS 
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

    // блок PIPE 
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
    bool flag = 1;
    PIPE pipe;
    CS cs;
    while (flag != 0)
    {
        cout << "Выберите опцию\n" << "1 - Создать трубу\n"  << "2 - Редактировать трубу\n" << "3 - Создать КС\n" << "4 - Редактировать КС\n" << "5 - Посмотреть все элементы\n" << "6 - Сохранить элементы\n"  << "7 - Загрузить элементы\n" << "0 - Выйти из программы" << endl;
        int option;
        while( !(cin >> option) || option < 0 || option > 7)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка.\n" << "Выберите опцию\n" << "1 - Создать трубу\n"  << "2 - Редактировать трубу\n" << "3 - Создать КС\n" << "4 - Редактировать КС\n" << "5 - Посмотреть все элементы\n" << "6 - Сохранить элементы\n"  << "7 - Загрузить элементы\n" << "0 - Выйти из программы" << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (option)
        {
        case 1:
            settings_pipe(pipe);
            break;
        case 2:
            edit_pipe(pipe);
            break;
        case 3:
            settings_cs(cs);
            break;
        case 4:
            edit_cs(cs);
            break;
        case 5:
            show_pipe(pipe);
            show_cs(cs);
            break;
        case 6:
            save_all(cs,pipe);
            break;
        case 7:
            load_all(cs, pipe);
            break;
        case 0:
            flag = 0;
            break;

        default:
            break;
        }
        
    }
    return 0;
}