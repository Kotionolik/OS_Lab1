# Обработчик записей сотрудников

## Обзор
Проект представляет собой Windows-приложение на C++ для управления записями сотрудников. Система состоит из трех основных компонентов:
1. **Creator** - создает бинарный файл с записями сотрудников
2. **Reporter** - генерирует отчеты о зарплатах из бинарных файлов
3. **Main** - основная программа, управляющая процессом

Проект включает модульные тесты для проверки функциональности и настроен для сборки через CMake.

## Системные требования
- ОС Windows
- Компилятор C++17 (MSVC, MinGW)
- CMake 3.10+
- Google Test (автоматически загружается через CMake)

## Сборка проекта

### Генерация проекта CMake
```bash
mkdir build
cd build
cmake ..
```

### Компиляция
```
cmake --build
```

### Сборка тестов
Тесты автоматически собираются вместе с основными компонентами. Исполняемый файл тестов будет создан как `tests.exe` (или `tests` в MinGW).

## Запуск программы
Основная программа:
```
Main.exe
```

После запуска:
1. Введите имя бинарного файла (например: `employees.bin`)
2. Введите количество записей сотрудников
3. Введите данные сотрудников (ID, имя, часы работы)
4. Введите имя файла отчета (например: `report.txt`)
5. Введите ставку оплаты (например: `20.0`)

## Компоненты системы

### Creator
- Создает бинарный файл с записями сотрудников
- Формат данных: `employee` структура (ID, имя[10], часы)
- Использование: `Creator.exe <файл> <количество записей>`

### Reporter
- Генерирует отчет о зарплатах
- Расчет: зарплата = часы × ставка
- Использование: `Reporter.exe <входной файл> <отчет> <ставка>`

### Main
- Основной процесс, запускающий Creator и Reporter
- Отображает содержимое созданных файлов

## Пример работы
```
Enter binary file name:
employees.bin
Enter record count:
2

Enter employee ID, name (no more than 10 symbols) and work hours:
101 John 160
Enter employee ID, name (no more than 10 symbols) and work hours:
102 Alice 120

File employees.bin created.

Contents of binary file employees.bin:
ID: 101, Name: John, Working hours: 160
ID: 102, Name: Alice, Working hours: 120

Enter report file name:
salaries.txt
Enter pay rate: 20

Report file salaries.txt created.

Contents of report file salaries.txt:
Report using file "employees.bin"
ID: 101, Worker's name: John, Hours of work: 160, Salary: 3200
ID: 102, Worker's name: Alice, Hours of work: 120, Salary: 2400
```

## Особенности реализации
- Все исполняемые файлы должны находиться в одной директории
- Имена сотрудников ограничены 10 символами
- Используется бинарный формат Windows
- Тесты автоматически загружают Google Test через CMake

## Тестирование
Проект включает три тестовых случая:
1. `CreatorTest` - проверка создания бинарных файлов
2. `ReporterTest` - проверка расчета зарплат
3. `MainTest` - интеграционное тестирование всего потока
