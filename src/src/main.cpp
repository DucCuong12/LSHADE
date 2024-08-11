#include <iostream>
#include "DE.h"
#include <dirent.h>

using namespace std;

void solve(const string &input_path, const int &index) {
    cout << "Start " << input_path << '\n';
    clock_t start_time = clock();
    string output_path = input_path;
    if (index >= 0)
        output_path += to_string(index);
    replace_all(output_path, "data", "result");
    replace_all(output_path, "test", "result");
    replace_all(output_path, ".inp", ".out");
    Problem *problem = Problem::read_problem(input_path);
    DE solver(problem);
    Individual *solution = solver.run(split(output_path, "/").back());
    clock_t end_time = clock();
    ofstream output_file(output_path);
    output_file << "Activation vector: " << solution->state << '\n';
    output_file << "Sensor angle: " << setprecision(12) << fixed << solution->direction << '\n';
    output_file << "Metrics:\n";
    output_file << "\tCQ = " << setprecision(12) << fixed << problem->CQ(solution) << '\n';
    output_file << "\tQBI = " << setprecision(12) << fixed << problem->QBI(solution) << '\n';
    output_file << "\tNumber of active sensors = " << Problem::count_active_sensor(solution) << '\n';
    output_file << "\tDI = " << setprecision(12) << fixed << problem->DI(solution) << '\n';
    output_file << "\tPower Consuming = " << setprecision(12) << fixed << problem->PC(solution) << '\n';
    output_file << "Running time: " << (end_time - start_time) / CLOCKS_PER_SEC << "s\n";
    output_file << "Number of generations: " << solver.history.size() << '\n';
    output_file << "History: " << setprecision(12) << fixed << solver.history << '\n';

    output_file.close();
    cout << "Done " << output_path << '\n';
} 

int main() {
    string root = ".././data/";
    vector<string> input_paths;

    if (auto dir = opendir(root.c_str())) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.')
                continue; // Skip everything that starts with a dot
            input_paths.emplace_back(root + f->d_name);
        }
        closedir(dir);
    }
//    input_paths.clear();
//    input_paths.emplace_back(root + "test_gr3_60sensing.inp");
    sort(input_paths.begin(), input_paths.end(), [](const string& a, const string& b){
        if (a.size() == b.size())
            return a < b;
        return a.size() < b.size();
    });
    cout << clock() << '\n';
    for (int i = 0; i <= 4; i++) {
        cout << "Try " << i << ": " << clock() << '\n';
        for (const auto &input_path: input_paths)
            solve(input_path, i);
        cout << "Try " << i << ": " << clock() << '\n';
    }
    cout << clock() << '\n';
}
