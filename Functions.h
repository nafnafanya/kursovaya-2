#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>     // Для работы со стандартными потоками ввода-вывода
#include <fstream>      // Для работы с файлами
#include <iomanip>      // Для использования функций setw() и OemToAnsi()
#include <windows.h>    // Для использования функции MessageBox()
#include <cstring>      // Для работы с массивами
#include <string>       // Для работы со строковыми переменными

using namespace std;
bool IsDebugMode = 1;

char* ReadLine(char* S, int len) { // функция для корректного ввода с клавиатуры русских букв
    cin.clear();                   // Возвращаем cin в 'обычный' режим работы
    cin.ignore(100, '\n');       // и удаляем значения предыдущего ввода из входного буфера
    cin.getline(S, len);
    OemToAnsi(S, S);
    return S;
}

int ReadNumber() {
    int a;
    cin >> a;

    if (cin.fail())                 // Если предыдущее извлечение оказалось неудачным,
    {
        cin.clear();                // То возвращаем cin в 'обычный' режим работы
        cin.ignore(100, '\n');    // И удаляем значения предыдущего ввода из входного буфера
        return -1;
    }
    else                            // Если всё хорошо, то возвращаем a
        return a;
}


struct FlightItem { // Структура для элемента списка 
    int Id;         // Уникальный номер 
    char Name[20];  // Рейс
    char Time[20];
    char City[20];
    char Airline[20];
    char Status[20];
    FlightItem* Adr;   // Адресное поле
};

FlightItem* Flights;

void WriteConItem(FlightItem* Item, int Number) { // Вывод данных рейса на экран
    if (IsDebugMode)
    {
        cout << setw(1) << Item->Id << '.'; // Идентификатор элемента в базе данных
        cout << setw(7) << " Время отправления: " << Item->Time; // Адрес элемента списка
        cout << setw(7) << " Город: " << Item->City;
        cout << setw(7) << " Авиалиния: " << Item->Airline;
        cout << setw(7) << " Статус: " << Item->Status;
    }
    cout << setw(12) << "Рейс: " << Item->Name << endl;
}

void WriteConItem(FlightItem Item, int Number) {
    if (IsDebugMode)
    {
        cout << setw(1) << Item.Id << '.'; // Идентификатор элемента в базе данных
        cout << setw(7) << " Время отправления: " << Item.Time; // Адрес элемента списка
        cout << setw(7) << " Город: " << Item.City;
        cout << setw(7) << " Авиалиния: " << Item.Airline;
        cout << setw(7) << " Статус: " << Item.Status;
    }
    cout << setw(12) << "Рейс: " << Item.Name << endl;
}

void PrintFlightsList(FlightItem* Item) { //Вывод списка предметов в консоль
    // Сохраним в переменную Curr адрес первого элемента списка
    FlightItem* Curr = Item;
    int num = 1;// Переменная для сквозной нумерации элементов списка
    cout << "Записанные рейсы: ";
    if (Curr != 0) {
        // Выполняем цикл пока адрес очередного элемента списка не равен 0
        cout << endl;
        while (Curr)
        {
            WriteConItem(Curr, num);
            Curr = Curr->Adr;
            num++;
        }
    }
    else {
        cout << "отсутствуют." << endl;
    }
}

unsigned LengthList(FlightItem* Beg) {
    unsigned Length = 0;
    while (Beg) {
        Length++;
        Beg = Beg->Adr;
    }
    return Length;
}

void ChangeFlightsItem(FlightItem* Beg) { //Изменение предмета из списка 
    // Сохраним адрес начала списка
    FlightItem* Curr = Beg;
    if (Curr != 0) {
        int ItemIndex;
        int Length = LengthList(Flights);
        cout << "Изменить рейс номер: ";
        ItemIndex = ReadNumber();
        if (ItemIndex > 0 && ItemIndex < Length + 1) {
            int num = 1;
            // Выполняем цикл пока адрес очередного элемента списка не равен 0
            while (Curr)//Заполним список
            {
                if (ItemIndex == num) {
                    // Выводим подсказку о текущем заполенении поля структуры
                    cout << "Номер рейса [" << num << "]: " << Curr->Name << ", Измененный номер рейса: ";
                    ReadLine(Curr->Name, sizeof(Curr->Name));
                    cout << "Время [" << num << "]: " << Curr->Time << ", Измененное время: ";
                    ReadLine(Curr->Time, sizeof(Curr->Time));
                    cout << "Город [" << num << "]: " << Curr->City << ", Измененный город: ";
                    ReadLine(Curr->City, sizeof(Curr->City));
                    cout << "Авиалиния [" << num << "]: " << Curr->Airline << ", Измененная авиалиния: ";
                    ReadLine(Curr->Airline, sizeof(Curr->Airline));
                    cout << "Статус [" << num << "]: " << Curr->Status << ", Измененный статус: ";
                    ReadLine(Curr->Status, sizeof(Curr->Status));
                }
                // Сохраняем в переменную Curr адрес следующего элемента списка
                // Цикл while закончится, когда адрес элемента станет равен 0
                Curr = Curr->Adr;
                // Изменяем переменную для уникального номера Id элемента списка
                num++;
            }
        }
        else
        {
            cout << "Рейс с данным номером отсутствует в списке. Проверьте список рейсов.\n";
        }
    }
    else {
        cout << "Список рейсов отсутствует. Перед изменением сначала создайте новый список.\n";
    }
}

FlightItem* AddNewFlightItemFromFile(FlightItem*& Beg, FlightItem FlightFromFile) {
    int Length = LengthList(Beg);
    int ItemIndex = Length;
    FlightItem* Item = new FlightItem;
    strcpy_s(Item->Name, FlightFromFile.Name);
    strcpy_s(Item->Time, FlightFromFile.Time);
    strcpy_s(Item->City, FlightFromFile.City);
    strcpy_s(Item->Airline, FlightFromFile.Airline);
    strcpy_s(Item->Status, FlightFromFile.Status);
    Item->Id = FlightFromFile.Id;
    if (!ItemIndex || !Beg)
    {
        Item->Adr = Beg;
        Beg = Item;
        return Item;
    }
    FlightItem* PredItem = Beg;
    --ItemIndex;
    while (PredItem->Adr && (ItemIndex--))
        PredItem = PredItem->Adr;
    Item->Adr = PredItem->Adr;
    PredItem->Adr = Item;
    return Item;
}

FlightItem* AddFlightItem(FlightItem*& Beg, int ItemIndex) {
    int Length = LengthList(Beg);
    if ((ItemIndex >= 0 && ItemIndex <= Length) || !Beg) {
        FlightItem* Item = new FlightItem;
        // Выводим подсказку о текущем заполенении поля структуры
        cout << "Новый рейс: ";
        // Вводим данные в информационную часть очередного элемента с клавиатуры
        ReadLine(Item->Name, sizeof(Item->Name));
        cout << "Время: ";
        ReadLine(Item->Time, sizeof(Item->Time));
        cout << "Город: ";
        ReadLine(Item->City, sizeof(Item->City));
        cout << "Авиалиния: ";
        ReadLine(Item->Airline, sizeof(Item->Airline));
        cout << "Статус: ";
        ReadLine(Item->Status, sizeof(Item->Status));
        Item->Id = Length + 1;
        if (!ItemIndex || !Beg)
        {
            Item->Adr = Beg;
            Beg = Item;
            return Item;
        }
        FlightItem* PredItem = Beg;
        --ItemIndex;
        while (PredItem->Adr && (ItemIndex--)) //???
            PredItem = PredItem->Adr;
        Item->Adr = PredItem->Adr;
        PredItem->Adr = Item;
        return Item;
    }
    else {
        cout << "Введен неверный номер списка. Добавление рейса невозможно.";
        return Beg;
    }
}

FlightItem* AddFlightItemToBegin(FlightItem*& Beg) {       //???
    return AddFlightItem(Beg, 0);
}

FlightItem* AddFlightItemToEnd(FlightItem*& Beg) {
    return AddFlightItem(Beg, LengthList(Beg));
}

void DeleteFlightsList(FlightItem*& Beg) { 
    FlightItem* Next; // Указатель на следующий элемент списка
    // Начинаем с начала списка
    if (Beg != 0) {
        while (Beg)
        {
            // Запоминаем адрес следующего элемента списка. Если этого не сделать,
            // то после удаления элемента по адресу Beg негде будет взять адрес
            // следующего элемента списка
            Next = Beg->Adr;
            // Удаляем первый элемент списка
            delete Beg;
            // Делаем адрес первого элемента списка равным адресу
            // следующего после удаленного
            Beg = Next;
        }
        // После окончания работы эта функция возвращает через свой параметр - ссылку Beg
        // адрес 0 – список отсутствует(он перестал существовать).
        cout << "Список рейсов успешно очищен.\n";
    }
    else {
        cout << "Ошибка удаления списка рейсов. Список рейсов ещё не создан!\n";
    }
}
bool SaveListOfFlightsToTextFile(string FileName, FlightItem* Data) {
    if (Data != 0) {
        FlightItem SingleFlight; // Для одиночного элемента списка
        ofstream File(FileName, ios::out | ios::binary); // Создали поток для записи в файл в двоичном режиме
        if (!File)
        {
            cout << "Открыть файл не удалось! \n";
            return 0;
        }
        FlightItem* Curr = Data;
        while (Curr)
        {
            SingleFlight.Id = Curr->Id;
            strcpy_s(SingleFlight.Name, Curr->Name);
            strcpy_s(SingleFlight.Time, Curr->Time);
            strcpy_s(SingleFlight.City, Curr->City);
            strcpy_s(SingleFlight.Airline, Curr->Airline);
            strcpy_s(SingleFlight.Status, Curr->Status);
            File.write((char*)&SingleFlight, sizeof(SingleFlight)); // Записываем данные из переменной Curr в файл
            cout << "Сохранен рейс";
            if (IsDebugMode)
            {
                cout << " [" << SingleFlight.Id << "]";
            }
            cout << ": " << SingleFlight.Name << endl;
            Curr = Curr->Adr;
        }
        File.close();
        return 1;
    }
    else {
        cout << "Список рейсов пуст и не может быть сохранен в файл.\n";
    }
    return 0;
}
FlightItem* ReadListOfFlightsFromTextFile(string FileName) {
    FlightItem* result = 0;
    ifstream File(FileName, ios::in | ios::binary);   // Создали поток чтения файла в двоичном режиме
    if (!File)  //  Проверили удалось ли открыть файл
    {
        cout << "Открыть файл не удалось!\n";
        return 0;   // Файл не открыт
    }
    //  int num = 1;


    while (!File.eof()) {
        FlightItem Curr;
        File.read((char*)&Curr, sizeof(Curr)); // Читаем из файла в переменную Curr данные об очередном предмете
        if (File.eof()) break;
        //      WriteConItem(Curr, num);
        //      num++;
        AddNewFlightItemFromFile(result, Curr); // Запишем очередной элемент в список result
    }
    File.close();  // Закрываем файл
    return result;
}

bool  SaveDataToTextFile(string FileName) {
    ofstream File;
    File.open(FileName);
    if (!File.is_open())
    {
        cout << "Открыть файл не удалось! \n";
        return 0;
    }
    for (int I = 1; I <= 10; ++I)
        File << "Строка " << I << endl;
    File.close();
    return 1;
}

#endif
