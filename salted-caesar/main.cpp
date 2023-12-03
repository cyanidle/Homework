#include <codecvt>
#include <string>
#include <random>
#include <limits>
#include <iostream>
#include <locale>
#include <fstream>
#include <sstream>
#include "argparse/argparse.hpp"

using std::string_view;
using std::string;

template<typename...Args>
void fatal(Args&&...args)
{
    (std::cerr << ... << args);
    std::cerr << std::endl;
    std::exit(EXIT_FAILURE);
}

string readFile(string_view path)
{
    std::ifstream in(path.data());
    if (!in.is_open()) {
        fatal("Невозможно открыть файл: ", path);
    }
    return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}

void writeFile(string_view conts, string_view path)
{
    std::ofstream out(path.data());
    if (!out.is_open()) {
        fatal("Невозможно открыть файл: ", path);
    }
    out << conts;
}

enum Mode {
    mode_encode = 0,
    mode_decode = 1,
};

string process(string_view input, int key, Mode mode)
{
    std::mt19937 engine{uint32_t(key)};
    std::uniform_int_distribution<char> randomChar{' '};
    std::uniform_int_distribution<uint32_t> shouldScramble(0, 1);
    string result;
    if (mode == mode_encode) {
        for (auto ch: input) {
            while (shouldScramble(engine)) {
                result += randomChar(engine);
            }
            result += ch + key;
        }
    } else {
        for (auto ch: input) {
            if (shouldScramble(engine)) {
                randomChar(engine);
                continue;
            }
            result += ch - key;
        }
    }
    return result;
}

int main(int argc, char**argv)
{
    std::setlocale(LC_ALL, "Russian");
    std::cerr << "Шифр Цезаря с солью!" << std::endl;
    argparse::ArgumentParser prog(argv[0]);
    prog.add_argument("input")
        .help("input file to process")
        .required();
    prog.add_argument("--key", "-k")
        .help("caesar key")
        .scan<'i', int>()
        .required();
    prog.add_argument("--encode")
        .help("encode mode")
        .implicit_value(true)
        .default_value(false);
    prog.add_argument("--decode")
        .help("decode mode")
        .implicit_value(true)
        .default_value(false);
    prog.add_argument("--output", "-o")
        .help("output file")
        .default_value("caesar_out.txt");
    try {
        prog.parse_args(argc, argv);
        auto encode = prog.get<bool>("encode");
        auto decode = prog.get<bool>("decode");
        if (encode == decode) {
            throw std::runtime_error("Необходимо выбрать один режим: --encode/--decode");
        }
        auto conts = readFile(prog.get("input"));
        auto key = prog.get<int>("key");
        auto mode = encode ? mode_encode : mode_decode;
        auto result = process(conts, key, Mode(mode));
        writeFile(result, prog.get("output"));
        return EXIT_SUCCESS;
    } catch (std::exception& exc) {
        std::cerr << "Ошибка: " << exc.what() << std::endl;
        std::cerr << prog << std::endl;
        return EXIT_FAILURE;
    }
}
