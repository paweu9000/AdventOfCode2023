// The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

struct Game {
    int id;
    int red = 0;
    int green = 0;
    int blue = 0;

    int is_valid() {
        // std::cout << "\nId:" << id << ", red: " << red << ", green: " << green << ", blue: " << blue << "\n"; 
        if (red <= 12 && green <= 13 && blue <= 14) {return id;}
        else return 0;
    }
};

std::vector<std::string> split_game(std::string& line) {
    std::string game = "";
    std::vector<std::string> rounds;
    for (auto c : line) {
        if (c == ':' || c == ';') {rounds.emplace_back(game); game = "";}
        else game += c;
    }
    rounds.emplace_back(game);
    return rounds;
}

int parse_id(std::string& line) {
    std::string res = "";
    for (auto c: line) {
        if (std::isdigit(c)) res += c;
    }
    return std::stoi(res);
}

void parse_scores(std::string& lines, Game* game) {
    std::vector<std::string> colors;
    std::string g = "";
    for (auto c: lines) {
        if (c == ',') {colors.emplace_back(g); g = "";}
        else g += c;
    }
    colors.emplace_back(g);
    g = "";
    for (auto color : colors) {
        for (int i = 1; i < color.size(); i++) {
            if (isdigit(color[i])) g += color[i];
            else if (color[i] == ' ' && g.size() > 0) {
                switch (color[i+1]) {
                    case 'r':
                        game->red = std::max(game->red, std::stoi(g));
                        break;
                    case 'g':
                        game->green = std::max(game->green, std::stoi(g));
                        break;
                    case 'b':
                        game->blue = std::max(game->blue, std::stoi(g));
                }
                break;
            }
        }
        g = "";
    }
}

int main() {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    int score = 0;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> split_g = split_game(line);
            Game game = Game{0,0,0,0};
            game.id = parse_id(split_g[0]);
            for (int i = 1; i < split_g.size(); i++) {
                parse_scores(split_g[i], &game);
            }
            score += game.is_valid();
        }
        file.close();
    }
    std::cout << score << std::endl;
    return 0;
}