// ...existing code...
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <unordered_set>
#include <string>

using namespace std;
#define MAX 10

 string products[MAX] = {
    "Cafe Expresso",
    "Cafe Duplo",
    "Cappuccino",
    "Chocolate Quente",
    "Cha",      
    "Agua 33cl"
};
const float prices[MAX] = {
    0.50f,
    0.60f,
    0.80f,
    1.00f,
    1.20f,
    0.30f
};

void menu() {
    system("cls");
    cout << "\n=========== MAQUINA DE CAFE ===========\n\n";
    for (int i = 0; i < MAX; ++i) {
        cout << (i + 1) << " - " << std::left << setw(25)
                  << products[i] << " (" << fixed << setprecision(2)
                  << prices[i] << " euros)\n";
    }
    cout << "======================================== \n";
}

int escolha() {
    int op;
    while (true) {
        std::cout << "Selecione uma opcao: ";
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (op >= 1 && op <= MAX) break;
    }
    return op;
}

int saberpreco_cents(int op) {
    if (op < 1 || op > MAX) return 0;
    return static_cast<int>(std::lround(prices[op - 1] * 100.0f));
}

int escolheracucar() {
    int want;
    while (true) {
        std::cout << "Quer acucar? (1-Sim / 0-Nao): ";
        if (!(std::cin >> want)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (want == 1 || want == 0) break;
    }

    if (want == 1) {
        int pacotes;
        std::cout << "Quantos pacotes de acucar quer? (1 ou 2): ";
        if (!(std::cin >> pacotes) || pacotes < 1 || pacotes > 2) {
            std::cout << "Quantidade invalida. Sera usado 1 pacote.\n";
            return 1;
        }
        return pacotes;
    } else {
        std::cout << "Sem acucar.\n";
        return 0;
    }
}

int pagamento_cents(int preco_cents) {
    const std::unordered_set<int> aceitaveis = {10,20,50,100,200,500,1000,2000};
    int total = 0;
    while (total < preco_cents) {
        double moeda;
        std::cout << "Total inserido: " << std::fixed << std::setprecision(2) << (total/100.0)
                  << " euros | Insira valor: ";
        if (!(std::cin >> moeda)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valor invalido!\n";
            continue;
        }
        int cents = static_cast<int>(std::lround(moeda * 100.0));
        if (cents <= 0 || aceitaveis.find(cents) == aceitaveis.end()) {
            std::cout << "Valor invalido!\n";
            continue;
        }
        total += cents;
    }
    return total;
}

int main() {
    int opcao, repetir = 0, acucar;
    do {
        menu();
        opcao = escolha();
        int preco_cents = saberpreco_cents(opcao);
        std::cout << "\nEscolheu \"" << products[opcao - 1] << "\" que custa " << std::fixed << std::setprecision(2)
                  << prices[opcao - 1] << " euros.\n";

        acucar = escolheracucar();

        std::cout << "\n--- PAGAMENTO ---\n";
        std::cout << "Aceita moedas: 0.10, 0.20, 0.50, 1.00, 2.00\n";
        std::cout << "Aceita notas: 5.00, 10.00, 20.00\n";

        int total_cents = pagamento_cents(preco_cents);

        if (total_cents > preco_cents) {
            std::cout << "Troco: " << std::fixed << std::setprecision(2)
                      << ((total_cents - preco_cents)/100.0) << " euros\n";
        }

        std::cout << "\nA preparar a sua bebida";
        for (int i = 0; i < 6; ++i) std::cout << ".";
        std::cout << "\nBebida pronta!\n";
        std::cout << "Acucar: " << acucar << " pacote(s)\n";

        std::cout << "\nDeseja pedir outra bebida? (1-Sim / 0-Nao): ";
        while (!(std::cin >> repetir)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (repetir == 1);

    std::cout << "\nObrigado e volte sempre!\n";
    return 0;
}
// ...existing code...