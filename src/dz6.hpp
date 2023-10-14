#pragma once
#include "common.hpp"

namespace subtasks_6
{

using Word = char[40];

auto matches = [](char* word){
    auto checkSubrange = [](char* start) {
        return start[0] < start[1]
               && start[1] < start[2];
    };
    auto len = strlen(word);
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
    get_input(in_filename, "Имя входного файла");
    get_input(out_filename, "Имя выходного файла");
    std::ifstream in(in_filename);
    Word storage[MAX];
    char* words[MAX];
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
            auto found = std::find_if(words, end, [&](char *word){
                return strcmp(word, current) == 0;
            });
            if (found != end) {
                continue; //such word already present
            }
            if (end == words + MAX) {
                auto newLen = strlen(current);
                for (auto* iter = words; iter != words + MAX; ++iter) {
                    if (strlen(*iter) > newLen) {
                        memcpy(*iter, current, newLen);
                    }
                }
            } else {
                // keep data always sorted. then search for bigger length can be binary
                strncpy(*end++, current, sizeof(Word));
            }
        }
    }
    { // sort, write
        std::sort(words, end, [](char* lhs, char* rhs){
            return strlen(lhs) < strlen(rhs);
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
