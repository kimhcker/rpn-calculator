#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <map>
#include <functional>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class RPNCalculator {
private:
    std::stack<double> stack;
    std::vector<std::string> history;
    
    void binaryOp(std::function<double(double, double)> op) {
        if (stack.size() < 2) {
            throw std::runtime_error("栈中元素不足");
        }
        double b = pop();
        double a = pop();
        push(op(a, b));
    }

    void unaryOp(std::function<double(double)> op) {
        if (stack.empty()) {
            throw std::runtime_error("栈为空");
        }
        double a = pop();
        push(op(a));
    }

    void fibonacci() {
        if (stack.empty()) {
            throw std::runtime_error("栈为空");
        }
        double n = pop();
        if (n < 0 || n != int(n)) {
            throw std::runtime_error("斐波那契数列需要非负整数");
        }
        
        int num = static_cast<int>(n);
        if (num == 0) {
            push(0);
        } else if (num == 1) {
            push(1);
        } else {
            double a = 0, b = 1;
            for (int i = 2; i <= num; i++) {
                double temp = a + b;
                a = b;
                b = temp;
            }
            push(b);
        }
    }

    void clearStack() {
        while (!stack.empty()) {
            stack.pop();
        }
        std::cout << "栈已清空" << std::endl;
    }

    void showStack() {
        if (stack.empty()) {
            std::cout << "栈为空" << std::endl;
            return;
        }
        
        std::stack<double> temp = stack;
        std::vector<double> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        
        std::cout << "当前栈 (从顶到底): ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

public:
    void push(double value) {
        stack.push(value);
    }

    double pop() {
        if (stack.empty()) {
            throw std::runtime_error("栈为空");
        }
        double value = stack.top();
        stack.pop();
        return value;
    }

    double calculate(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        std::vector<std::string> tokens;
        
        // 分割输入
        while (iss >> token) {
            tokens.push_back(token);
        }

        // 保存历史
        history.push_back(expression);

        for (const auto& token : tokens) {
            if (token == "+") {
                binaryOp([](double a, double b) { return a + b; });
            } else if (token == "-") {
                binaryOp([](double a, double b) { return a - b; });
            } else if (token == "*") {
                binaryOp([](double a, double b) { return a * b; });
            } else if (token == "/") {
                binaryOp([](double a, double b) { 
                    if (b == 0) throw std::runtime_error("除零错误");
                    return a / b; 
                });
            } else if (token == "^") {
                binaryOp([](double a, double b) { return pow(a, b); });
            } else if (token == "sqrt") {
                unaryOp([](double a) { 
                    if (a < 0) throw std::runtime_error("负数不能开平方根");
                    return sqrt(a); 
                });
            } else if (token == "sin") {
                unaryOp([](double a) { return sin(a * M_PI / 180.0); });
            } else if (token == "cos") {
                unaryOp([](double a) { return cos(a * M_PI / 180.0); });
            } else if (token == "tan") {
                unaryOp([](double a) { return tan(a * M_PI / 180.0); });
            } else if (token == "fib") {
                fibonacci();
            } else if (token == "clear") {
                clearStack();
            } else if (token == "show") {
                showStack();
            } else {
                // 尝试解析为数字
                try {
                    double value = std::stod(token);
                    push(value);
                } catch (const std::exception&) {
                    throw std::runtime_error("无效的输入: " + token);
                }
            }
        }

        if (stack.empty()) {
            throw std::runtime_error("计算后栈为空");
        }

        return stack.top();
    }

    void printHistory() const {
        std::cout << "计算历史:" << std::endl;
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << i + 1 << ": " << history[i] << std::endl;
        }
    }

    size_t getStackSize() const {
        return stack.size();
    }

    void processBatch(const std::vector<std::string>& expressions) {
        std::cout << "批量计算开始..." << std::endl;
        for (size_t i = 0; i < expressions.size(); ++i) {
            try {
                std::cout << "表达式 " << (i + 1) << ": " << expressions[i] << std::endl;
                double result = calculate(expressions[i]);
                std::cout << "结果: " << result << std::endl;
                std::cout << "------------------------" << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
                std::cout << "------------------------" << std::endl;
            }
        }
        std::cout << "批量计算完成" << std::endl;
    }
};

void printHelp() {
    std::cout << "\n=== RPN计算器使用说明 ===" << std::endl;
    std::cout << "基础操作:" << std::endl;
    std::cout << "  +, -, *, /  - 四则运算" << std::endl;
    std::cout << "  ^           - 幂运算 (a^b)" << std::endl;
    std::cout << "  sqrt        - 平方根" << std::endl;
    std::cout << "  sin, cos, tan - 三角函数 (角度制)" << std::endl;
    std::cout << "  fib         - 斐波那契数列 (fib n 计算第n项)" << std::endl;
    std::cout << "栈操作:" << std::endl;
    std::cout << "  clear       - 清空栈" << std::endl;
    std::cout << "  show        - 显示当前栈" << std::endl;
    std::cout << "系统命令:" << std::endl;
    std::cout << "  history     - 显示计算历史" << std::endl;
    std::cout << "  batch       - 进入批量计算模式" << std::endl;
    std::cout << "  help        - 显示此帮助" << std::endl;
    std::cout << "  q           - 退出程序" << std::endl;
    std::cout << "示例:" << std::endl;
    std::cout << "  5 5 +        -> 10" << std::endl;
    std::cout << "  2 3 ^        -> 8" << std::endl;
    std::cout << "  9 sqrt       -> 3" << std::endl;
    std::cout << "  5 fib        -> 5" << std::endl;
    std::cout << "=======================\n" << std::endl;
}

int main() {
    RPNCalculator calc;
    std::cout << "=== C++ RPN 计算器 ===" << std::endl;
    std::cout << "输入 'help' 查看使用说明" << std::endl;
    
    printHelp();

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "q" || input == "quit") {
            break;
        } else if (input == "help") {
            printHelp();
        } else if (input == "history") {
            calc.printHistory();
        } else if (input == "batch") {
            std::cout << "进入批量计算模式，输入多行表达式，空行结束:" << std::endl;
            std::vector<std::string> batchExpressions;
            std::string line;
            while (true) {
                std::cout << "batch> ";
                std::getline(std::cin, line);
                if (line.empty()) {
                    break;
                }
                batchExpressions.push_back(line);
            }
            calc.processBatch(batchExpressions);
        } else if (!input.empty()) {
            try {
                double result = calc.calculate(input);
                std::cout << "结果: " << std::fixed << std::setprecision(6) << result << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
            }
        }
    }

    std::cout << "感谢使用RPN计算器！" << std::endl;
    return 0;
}
