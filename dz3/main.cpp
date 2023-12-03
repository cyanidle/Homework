
#include "common.hpp"


int main()
{
    Desctiption{"Подзадание A"} << []{
        auto A = get_input<int>("A");
        auto B = get_input<int>("B");
        auto C = get_input<int>("C");
        int answer;
        if (A < B && B > C) {
            answer = B + A - C;
        } else if (B % C == 0) {
            answer = B / C - B;
        } else {
            answer = A * B - C;
        }
        print("Результат", answer);
    };
    Desctiption{"Подзадание B"} << []{
        auto N = get_input<int>("Номер месяца");
        switch (N)
        {
        case 0: print("Январь"); break;
        case 1: print("Февраль"); break;
        case 2: print("Март"); break;
        case 3: print("Апрель"); break;
        case 4: print("Май"); break;
        case 5: print("Июнь"); break;
        case 6: print("Июль"); break;
        case 7: print("Август"); break;
        case 8: print("Сентябрь"); break;
        case 9: print("Октябрь"); break;
        case 10: print("Ноябрь"); break;
        case 11: print("Декабрь"); break;
        default:
            throw std::runtime_error("Введено неправильное число-месяц (Должно быть 0 <= N <= 11)");
        }
    };
    Desctiption{"Подзадание C"} << []{
        auto x = get_input<int>("Number [1/-1]");
        if (x == 1) {
            print("Positive number");
        } else if (x == -1) {
            print("Negative number");
        } else {
            print("Error");
        }
    };
}
