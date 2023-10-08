#pragma once
#include "common.hpp"

namespace subtasks_6
{

using Word = wchar_t[40];

auto matches = [](wchar_t* word){
    auto checkSubrange = [](wchar_t* start) {
        return start[0] < start[1] && start[1] < start[2];
    };
    auto len = wcslen(word);
    for (size_t i = 0; i < len - 3; ++i){
        if (checkSubrange(word + i)) {
            return true;
        }
    }
    return false;
};

void a()
{
    constexpr auto MAX = 2000;
    char in_filename[50];
    char out_filename[50];
    get_input(in_filename, L"Имя входного файла");
    get_input(out_filename, L"Имя выходного файла");
    std::wifstream in(in_filename);
    Word storage[MAX];
    wchar_t* words[MAX];
    for (size_t i = 0; i < MAX; ++i) {
        words[i] = storage[i];
    }
    auto* end = words;
    { //populate data
        while (!in.eof())
        {
            Word current;
            in >> current;
            if (!matches(current))
                continue;
            auto found = std::find_if(words, end, [&](wchar_t *word){
                return wcscmp(word, current) == 0;
            });
            if (found != end) {
                continue; //such word already present
            }
            if (end == words + MAX) {
                auto newLen = wcslen(current);
                for (auto* iter = words; iter != words + MAX; ++iter) {
                    if (wcslen(*iter) > newLen) {
                        memcpy(*iter, current, newLen);
                    }
                }
            } else {
                // keep data always sorted. then search for bigger length can be binary
                wcsncpy(*end++, current, sizeof(Word));
            }
        }
    }
    { // sort, write
        std::sort(words, end, [](wchar_t* lhs, wchar_t* rhs){
            return wcslen(lhs) < wcslen(rhs);
        });
        std::wofstream out(out_filename);
        for(auto* iter = words; iter != end; ++iter) {
            out << iter << '\n';
        }
    }
}

void b()
{

}

void c()
{

}
}

void DZ_6()
{
    Desctiption{"Подзадание A"} << subtasks_6::a;
    Desctiption{"Подзадание B"} << subtasks_6::b;
    Desctiption{"Подзадание C"} << subtasks_6::c;
}
