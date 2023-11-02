#pragma once
#include "common.hpp"
#include "predicates.hpp"
#include <istream>
#include <sstream>

namespace subtasks_6
{

using Word = char[40];

auto matches = [](char* word){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    auto wide = cvt.from_bytes(word);
    std::transform(wide.begin(), wide.end(), wide.begin(), ::tolower);
    auto checkSubrange = [](wchar_t* start) {
        return start[0] <= start[1] && start[1] <= start[2];
    };
    auto len = wide.size();
    for (size_t i = 0; i < len - 2; ++i){
        if (checkSubrange(wide.data() + i)) {
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
    auto in = open<std::ifstream>(in_filename);
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
                // TODO: keep data always sorted. then search for bigger length can be binary
                strncpy(*end++, current, sizeof(Word));
            }
        }
    }
    { // sort, write
        std::sort(words, end, [](char* lhs, char* rhs){
            return strlen(lhs) < strlen(rhs);
        });
        auto out = open<std::ofstream>(out_filename);
        print("Найдено слов: ", end - words);
        for(auto* iter = words; iter != end; ++iter) {
            out << *iter << '\n';
        }
    }
}

void b()
{
    using namespace std;
    char line[200];
    cout << "Введите ['Строка с русским тесктом']: ";
    cin.getline(line, sizeof(line));
    auto wide = ToWide(line);
    wide.c_str();
    wchar_t* words[30] = {};
    size_t wordsCount = 0;
    wchar_t** end;
    { //count and populate
        for (auto i = 0u; i < wide.size(); ++i) {
            if (wide[i] == L' ') {
                wide[i] = '\0';
                words[wordsCount++] = wide.data() + i;
            }
        }
        end = words + wordsCount;
    }
    bool hasDuplicates = false;
    for (auto i = words; i != end && !hasDuplicates; ++i) {
        if (i == end - 1) break;
        for (auto j = i + 1; i != end && !hasDuplicates; ++j) {
            if (wcscmp(*i, *j) == 0) {
                hasDuplicates = true;
            }
        }
    }
    if (hasDuplicates) {
        print("Есть дупликаты");
        for (auto w = words; w != end; ++w) {
            auto wordLen = wcslen(*w);
            auto wordEnd = remove_all_if(*w, *w + wordLen, isVowel);
            *wordEnd = '\0';
        }
        print("Слова с удаленными гласными");
        print_array(words, end - words);
    } else {
        print("Нет дупликатов");
        for (auto w = words; w != end; ++w) {
            auto wordLen = wcslen(*w);
            auto vowelsCount = std::count_if(*w, *w + wordLen, isVowel);
            bool shouldDuplicate = vowelsCount <= 3;
            if (shouldDuplicate) {
                auto word = *w;
                wchar_t ch;
                while ((ch = *word++)) {
                    wcout << ch;
                    if (!isVowel(ch)) {
                        wcout << ch;
                    }
                }
                wcout << endl;
            } else {
                wcout << *w << endl;
            }
        }
    }
}

bool wordHasOrdered(size_t count, wchar_t* word)
{

}

void c()
{
    std::wifstream in("input.txt");
    std::wofstream out("output.txt");
    wchar_t ch = 0;
    wchar_t currentWord[40];
    size_t wordInd = 0;
    bool lastSpace = true;
    while((ch = in.rdbuf()->snextc())) {
        out << ch;
        switch(ch) {
        case L'\t':
        case L'\n':
        case L' ' : {
            if (!lastSpace) {

            }
        }
        default: {
            lastSpace = false;
            currentWord[wordInd++] = ch;
        }
        }
    }
}
}

void DZ_6(int sub)
{
    if (sub == AllSubtasks || sub == 0) {
        Desctiption{"Подзадание A"}.Confirm(sub == AllSubtasks) << subtasks_6::a;
    }
    if (sub == AllSubtasks || sub == 1) {
        Desctiption{"Подзадание B"}.Confirm(sub == AllSubtasks) << subtasks_6::b;
    }
    if (sub == AllSubtasks || sub == 2) {
        Desctiption{"Подзадание C"}.Confirm(sub == AllSubtasks) << subtasks_6::c;
    }
}
