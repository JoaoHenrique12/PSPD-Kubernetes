#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string.h>

int main(int argc, char** argv) {
    // Inicializa o MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cada processo abre o arquivo "test.txt"
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        if(rank == 0)
            std::cerr << "Erro ao abrir o arquivo test.txt" << std::endl;
        MPI_Finalize();
        return 1;
    }

    // Cada processo lê as palavras e seleciona aquelas com índice atribuído ao seu rank.
    std::vector<std::string> localWords;
    std::string word;
    int index = 0;
    while (file >> word) {
        if (index % size == rank) {
            localWords.push_back(word);
        }
        index++;
    }
    file.close();

    // Contagem das palavras usando OpenMP:
    // Cada thread mantém um mapa local e, ao final, os resultados são mesclados.
    std::unordered_map<std::string, int> localCount;
    int n = localWords.size();
    int numThreads = omp_get_max_threads();
    std::vector<std::unordered_map<std::string, int>> threadMaps(numThreads);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int tid = omp_get_thread_num();
        threadMaps[tid][localWords[i]]++;
    }
    // Mescla os mapas locais das threads no mapa do processo
    for (int t = 0; t < numThreads; t++) {
        for (auto &pair : threadMaps[t]) {
            localCount[pair.first] += pair.second;
        }
    }

    // Comunicação via MPI: O processo 0 coleta os resultados dos demais.
    if (rank == 0) {
        // Recebe os resultados de cada processo e agrega
        for (int p = 1; p < size; p++) {
            int msgLength;
            MPI_Recv(&msgLength, 1, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            char *buffer = new char[msgLength + 1];
            MPI_Recv(buffer, msgLength, MPI_CHAR, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            buffer[msgLength] = '\0';
            std::istringstream iss(buffer);
            std::string line;
            while (std::getline(iss, line)) {
                if(line.empty()) continue;
                std::istringstream ls(line);
                std::string key;
                int count;
                ls >> key >> count;
                localCount[key] += count;
            }
            delete[] buffer;
        }
        // Imprime a contagem final das palavras
        std::cout << "Contagem de palavras:" << std::endl;
        for (auto &pair : localCount) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    } else {
        // Processos não-0: serializam o mapa e enviam para o processo 0.
        std::ostringstream oss;
        for (auto &pair : localCount) {
            oss << pair.first << " " << pair.second << "\n";
        }
        std::string sendStr = oss.str();
        int msgLength = sendStr.size();
        MPI_Send(&msgLength, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(sendStr.c_str(), msgLength, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
