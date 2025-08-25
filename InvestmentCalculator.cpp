#include "InvestmentCalculator.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <stdexcept>
#include <string>

InvestmentCalculator::InvestmentCalculator()
    : initialInvestment_(0.0),
      monthlyDeposit_(0.0),
      annualInterestRate_(0.0),
      numberOfYears_(1) {}

void InvestmentCalculator::Run() {
    bool keepRunning = true;
    while (keepRunning) {
        PrintTitle();
        GetUserInput();
        DisplayInputSummary();
        WaitForEnter();
        std::cout << "\n\n================== Yearly Report (No Monthly Deposits) ==================\n";
        DisplayReport_NoMonthlyDeposits();
        std::cout << "\n\n================== Yearly Report (With Monthly Deposits) =================\n";
        DisplayReport_WithMonthlyDeposits();
        std::cout << "\n\nWould you like to run another scenario? (Y/N): ";
        std::string response;
        std::getline(std::cin, response);
        keepRunning = !response.empty() && (response[0] == 'Y' || response[0] == 'y');
    }
    std::cout << "\nThank you for using Airgead Banking Investment Calculator. Goodbye!\n";
}

void InvestmentCalculator::PrintTitle() const {
    std::cout << "\n=== Airgead Banking Investment Calculator ===\n"
              << "This program demonstrates compound interest growth with and without monthly deposits.\n";
}

void InvestmentCalculator::GetUserInput() {
    initialInvestment_   = ReadNonNegativeDouble("Enter Initial Investment Amount (e.g., 1000.00): $");
    monthlyDeposit_      = ReadNonNegativeDouble("Enter Monthly Deposit Amount (e.g., 50.00): $");
    annualInterestRate_  = ReadNonNegativeDouble("Enter Annual Interest Rate (percent, e.g., 5): ", 10000.0);
    numberOfYears_       = ReadPositiveInt("Enter Number of Years (whole number, e.g., 5): ", 1, 10000);
}

void InvestmentCalculator::DisplayInputSummary() const {
    std::cout << "\n-------------------- Input Summary --------------------\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << " Initial Investment : $" << initialInvestment_  << "\n";
    std::cout << " Monthly Deposit    : $" << monthlyDeposit_     << "\n";
    std::cout << " Annual Interest    :  " << annualInterestRate_ << "%\n";
    std::cout << " Number of Years    :  " << numberOfYears_      << "\n";
    std::cout << "-------------------------------------------------------\n";
}

void InvestmentCalculator::WaitForEnter(const std::string& prompt) const {
    std::cout << prompt;
    std::string dummy;
    std::getline(std::cin, dummy);
}

void InvestmentCalculator::DisplayReport_NoMonthlyDeposits() const {
    const double monthlyRate = (annualInterestRate_ / 100.0) / 12.0;
    double currentBalance = initialInvestment_;
    PrintReportHeader();
    for (int year = 1; year <= numberOfYears_; ++year) {
        double yearlyInterest = 0.0;
        for (int m = 0; m < 12; ++m) {
            const double monthlyInterest = currentBalance * monthlyRate;
            yearlyInterest += monthlyInterest;
            currentBalance += monthlyInterest;
        }
        PrintYearRow(year, currentBalance, yearlyInterest);
    }
}

void InvestmentCalculator::DisplayReport_WithMonthlyDeposits() const {
    const double monthlyRate = (annualInterestRate_ / 100.0) / 12.0;
    double currentBalance = initialInvestment_;
    PrintReportHeader();
    for (int year = 1; year <= numberOfYears_; ++year) {
        double yearlyInterest = 0.0;
        for (int m = 0; m < 12; ++m) {
            currentBalance += monthlyDeposit_;
            const double monthlyInterest = currentBalance * monthlyRate;
            yearlyInterest += monthlyInterest;
            currentBalance += monthlyInterest;
        }
        PrintYearRow(year, currentBalance, yearlyInterest);
    }
}

void InvestmentCalculator::PrintReportHeader() {
    using std::cout;
    using std::left;
    using std::right;
    using std::setw;
    cout << left  << setw(6)  << "Year"
         << right << setw(22) << "Year End Balance"
         << right << setw(28) << "Year End Earned Interest" << "\n";
    cout << std::string(6 + 22 + 28, '-') << "\n";
}

void InvestmentCalculator::PrintYearRow(int year, double yearEndBalance, double yearEndInterest) {
    using std::cout;
    using std::left;
    using std::right;
    using std::setw;
    cout << std::fixed << std::setprecision(2);
    cout << left  << setw(6)  << year
         << right << setw(22) << yearEndBalance
         << right << setw(28) << yearEndInterest
         << "\n";
}

double InvestmentCalculator::ReadNonNegativeDouble(const std::string& prompt, double max) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cin.clear();
            continue;
        }
        try {
            size_t idx = 0;
            double value = std::stod(line, &idx);
            while (idx < line.size() && std::isspace(static_cast<unsigned char>(line[idx]))) ++idx;
            if (idx != line.size()) throw std::invalid_argument("Trailing characters");
            if (value < 0.0) {
                std::cout << "Please enter a non-negative number.\n";
                continue;
            }
            if (value > max) {
                std::cout << "Value too large. Please enter a number <= " << max << ".\n";
                continue;
            }
            return value;
        } catch (...) {
            std::cout << "Invalid input. Please enter a numeric value.\n";
        }
    }
}

int InvestmentCalculator::ReadPositiveInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cin.clear();
            continue;
        }
        try {
            size_t idx = 0;
            long long temp = std::stoll(line, &idx);
            while (idx < line.size() && std::isspace(static_cast<unsigned char>(line[idx]))) ++idx;
            if (idx != line.size()) throw std::invalid_argument("Trailing characters");
            if (temp < min || temp > max) {
                std::cout << "Please enter a whole number between " << min << " and " << max << ".\n";
                continue;
            }
            return static_cast<int>(temp);
        } catch (...) {
            std::cout << "Invalid input. Please enter a whole number.\n";
        }
    }
}
