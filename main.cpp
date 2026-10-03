#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace {

constexpr int REQUIRED_WEEKLY_HOURS = 20;
constexpr int EXPECTED_WORK_DAYS = 5;
constexpr double EXPECTED_RATE = 0.5;
constexpr int EXPECTED_DAILY_HOURS = 4;
constexpr int MAX_DAILY_HOURS = 24;
constexpr int LAPTOP_COUNT = 30; // число ноутбуков в кабинете ИКТ
constexpr int LAST_MENU_ITEM = 7;
constexpr int PROTOCOL_STEP_DELAY_MS = 700;

[[noreturn]] void stopOnEndOfInput()
{
    std::cerr << "\nВвод завершен до окончания ознакомления. "
                 "Программа остановлена.\n";
    std::exit(EXIT_FAILURE);
}

std::string readLine(const std::string& prompt)
{
    std::cout << prompt;

    std::string line;
    if (!std::getline(std::cin, line))
    {
        stopOnEndOfInput();
    }
    return line;
}

int readInt(const std::string& prompt)
{
    while (true)
    {
        std::istringstream parser(readLine(prompt));
        int value = 0;
        char trailing = 0;

        if (parser >> value && !(parser >> trailing))
        {
            return value;
        }

        std::cout << "Ошибка! Введите целое число.\n";
    }
}

int readLaptopNumber(const std::string& prompt)
{
    int laptopNumber = 0;
    do
    {
        laptopNumber = readInt(prompt);

        if (laptopNumber < 1 || laptopNumber > LAPTOP_COUNT)
        {
            std::cout << "Ошибка! В кабинете ноутбуки с номерами от 1 до "
                      << LAPTOP_COUNT << ".\n";
        }
    } while (laptopNumber < 1 || laptopNumber > LAPTOP_COUNT);
    return laptopNumber;
}

double readRate(const std::string& prompt)
{
    while (true)
    {
        std::istringstream parser(readLine(prompt));
        double value = 0.0;
        char trailing = 0;

        if (parser >> value && !(parser >> trailing))
        {
            return value;
        }

        std::cout << "Ошибка! Введите число, например 0.5.\n";
    }
}

void showWorkingHours()
{
    std::cout << "\nРегламент рабочего времени:\n";
    std::cout << "На 0,5 ставки обязательный объем работы составляет "
              << REQUIRED_WEEKLY_HOURS << " часов в неделю.\n";
}

void showSoftwareDuty()
{
    std::cout << "\nПроверка программного обеспечения:\n";
    std::cout << "Лаборант обязан ежедневно, до начала занятий, проверять\n";
    std::cout << "работоспособность ПО на всех ноутбуках кабинета.\n";
}

void showMaterialLiability()
{
    std::cout << "\nМатериальная ответственность:\n";
    std::cout << "Лаборант отвечает за сохранность имущества компьютерного\n";
    std::cout << "класса: ноутбуков, блоков питания и периферии.\n";
}

void runWorkingTimeModule()
{
    std::cout << "\n=== УЧЕТ РАБОЧЕГО ВРЕМЕНИ ===\n";

    int workDays = 0;
    do
    {
        workDays = readInt("Введите количество рабочих дней в неделю (5): ");

        if (workDays != EXPECTED_WORK_DAYS)
        {
            std::cout << "Ошибка! Для данного сценария необходимо указать "
                      << EXPECTED_WORK_DAYS << " рабочих дней.\n";
        }
    } while (workDays != EXPECTED_WORK_DAYS);

    double rate = 0.0;
    do
    {
        rate = readRate("Введите ставку (0.5): ");

        if (rate != EXPECTED_RATE)
        {
            std::cout << "Ошибка! Необходимо указать ставку "
                      << EXPECTED_RATE << ".\n";
        }
    } while (rate != EXPECTED_RATE);

    int hoursPerDay = 0;
    do
    {
        hoursPerDay = readInt("Введите количество рабочих часов в день "
                              "(норма - 4): ");

        if (hoursPerDay < 1 || hoursPerDay > MAX_DAILY_HOURS)
        {
            std::cout << "Ошибка! Количество часов в день должно быть "
                         "от 1 до " << MAX_DAILY_HOURS << ".\n";
            continue;
        }

        const int weeklyHours = workDays * hoursPerDay;
        std::cout << "Расчет: " << workDays << " дн. x " << hoursPerDay
                  << " ч = " << weeklyHours << " ч в неделю.\n";

        if (hoursPerDay == 2)
        {
            std::cout << "\nОшибка! При 5-дневной рабочей неделе 2 часа в день "
                         "составляют 10 часов в неделю.\n";
            std::cout << "Дефицит рабочего времени: 10 часов "
                         "(50% от нормы 0.5 ставки).\n";
            std::cout << "Налицо факт предоставления заведомо ложных сведений "
                         "работодателю.\n";
        }

        if (hoursPerDay != EXPECTED_DAILY_HOURS)
        {
            std::cout << "Норма не подтверждена. Для продолжения необходимо "
                         "подтвердить "
                      << EXPECTED_DAILY_HOURS << " часа работы в день.\n\n";
        }
    } while (hoursPerDay != EXPECTED_DAILY_HOURS);

    std::cout << "\nНорма подтверждена: " << workDays << " дн. x "
              << EXPECTED_DAILY_HOURS << " ч = " << REQUIRED_WEEKLY_HOURS
              << " ч в неделю при ставке " << rate << ".\n";
}

void runDisciplinaryModule()
{
    std::cout << "\n=== ДИСЦИПЛИНАРНЫЕ ВЗЫСКАНИЯ ===\n";

    const int laptopNumber = readLaptopNumber("Введите номер ноутбука, "
                                              "вынесенного из кабинета: ");

    std::cout << "\nИнцидент: самовольный вынос учебного настроенного "
                 "ноутбука №" << laptopNumber << "\n"
                 "за пределы учебного кабинета и срыв учебного процесса.\n";

    std::cout << "\nКвалификация по уставу ВУЗа:\n";
    std::cout << "  1. Грубое нарушение трудовой дисциплины - вынос "
                 "имущества кабинета без разрешения.\n";
    std::cout << "  2. Саботаж учебного процесса - занятие сорвано из-за "
                 "отсутствия настроенного оборудования.\n";
    std::cout << "  3. Несоответствие сотрудника занимаемой должности - "
                 "невыполнение обязанностей лаборанта.\n";

    std::cout << "\nМатериалы по инциденту передаются ответственному "
                 "руководителю.\n";
}

void pauseBetweenSteps()
{
    std::cout << std::flush; // показать шаг до паузы, даже если вывод перенаправлен
    std::this_thread::sleep_for(
        std::chrono::milliseconds(PROTOCOL_STEP_DELAY_MS));
}

void runSabotageProtocol()
{
    std::cout << "\n=== ПРОТОКОЛ РЕАГИРОВАНИЯ НА САБОТАЖ ===\n";

    const int laptopNumber = readLaptopNumber("Введите номер ноутбука: ");

    std::cout << "\nШаг 1. Фиксация нарушения\n";
    std::cout << "Обнаружен факт неисполнения обязанностей: "
                 "несанкционированный вынос оборудования (ноутбук №"
              << laptopNumber << "),\n"
                 "утеря материальных ценностей (блок питания), отказ от "
                 "подготовки и тестирования ПО кабинета ИКТ\n"
                 "и несоблюдение учебной дисциплины.\n";
    pauseBetweenSteps();

    std::cout << "\nШаг 2. Уведомление руководства\n";
    std::cout << "Действие преподавателя: официальное письменное или устное "
                 "уведомление ответственного лица,\n"
                 "закрепленного за кабинетом ИКТ.\n";
    pauseBetweenSteps();

    std::cout << "\nШаг 3. Проверка доказательной базы\n";
    std::cout << "Действие: запрос на аудит записей камер видеонаблюдения "
                 "и сопоставление с логами посещения кабинета.\n";
    pauseBetweenSteps();

    std::cout << "\nШаг 4. Подача служебной записки\n";
    std::cout << "Действие преподавателя: направление служебной записки на "
                 "имя заведующего кафедрой\n"
                 "(руководителя отдела) и декана факультета с описанием "
                 "инцидента и срыва учебного процесса на СРС.\n";
    pauseBetweenSteps();

    std::cout << "\nШаг 5. Административные последствия\n";
    std::cout << "Итог протокола: создание дисциплинарной комиссии, "
                 "вынесение выговора, расторжение трудового договора\n"
                 "(0.5 ставки) и передача дела в органы материального учета "
                 "ВУЗа.\n";

    std::cout << "\nПротокол завершен.\n";
}

void showMenu()
{
    std::cout << "\nМЕНЮ\n";
    std::cout << "1. Регламент рабочего времени\n";
    std::cout << "2. Проверка программного обеспечения\n";
    std::cout << "3. Материальная ответственность\n";
    std::cout << "4. Вся информация\n";
    std::cout << "5. Учет рабочего времени\n";
    std::cout << "6. Дисциплинарные взыскания\n";
    std::cout << "7. Протокол реагирования на саботаж\n";
    std::cout << "0. Завершить ознакомление\n";
}

} // namespace

int main()
{
    int choice = -1;

    do
    {
        showMenu();
        choice = readInt("Выберите пункт: ");

        switch (choice)
        {
        case 1:
            showWorkingHours();
            break;
        case 2:
            showSoftwareDuty();
            break;
        case 3:
            showMaterialLiability();
            break;
        case 4:
            showWorkingHours();
            showSoftwareDuty();
            showMaterialLiability();
            break;
        case 5:
            runWorkingTimeModule();
            break;
        case 6:
            runDisciplinaryModule();
            break;
        case 7:
            runSabotageProtocol();
            break;
        case 0:
            std::cout << "\nПереходим к контрольному вопросу.\n";
            break;
        default:
            std::cout << "\nОшибка! Выберите пункт от 0 до " << LAST_MENU_ITEM
                      << ".\n";
        }
    } while (choice != 0);

    int answer = 0;

    do
    {
        answer = readInt("\nСколько часов в неделю обязан отрабатывать "
                         "лаборант на 0,5 ставки? ");

        if (answer != REQUIRED_WEEKLY_HOURS)
        {
            std::cout << "Неверно! Повторите ввод.\n";
        }
    } while (answer != REQUIRED_WEEKLY_HOURS);

    std::cout << "\nПравильно! Ознакомление завершено.\n";
    return 0;
}
