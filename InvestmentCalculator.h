#ifndef AIRGEAD_INVESTMENT_CALCULATOR_H
#define AIRGEAD_INVESTMENT_CALCULATOR_H

#include <string>

class InvestmentCalculator {
public:
    InvestmentCalculator();
    void Run();
private:
    double initialInvestment_;
    double monthlyDeposit_;
    double annualInterestRate_;
    int    numberOfYears_;
    void PrintTitle() const;
    void GetUserInput();
    void DisplayInputSummary() const;
    void WaitForEnter(const std::string& prompt = "Press Enter to continue...") const;
    void DisplayReport_NoMonthlyDeposits() const;
    void DisplayReport_WithMonthlyDeposits() const;
    static void PrintReportHeader();
    static void PrintYearRow(int year, double yearEndBalance, double yearEndInterest);
    static double ReadNonNegativeDouble(const std::string& prompt, double max = 1.0e12);
    static int    ReadPositiveInt(const std::string& prompt, int min = 1, int max = 10000);
};

#endif // AIRGEAD_INVESTMENT_CALCULATOR_H
