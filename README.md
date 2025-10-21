# RPN 计算器项目

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://en.cppreference.com/)

一个功能完整的逆波兰表示法（RPN）计算器，支持基本运算、高级数学函数以及特殊的斐波那契和杨辉三角计算。

## 📋 项目结构

```
rpn_calc/
├── rpn_calc.cpp          # C++源代码
├── rpn_calc              # 编译后的可执行文件
├── rpn_manual.nim        # Nimib文档源码
├── rpn_manual.html       # 生成的HTML文档
└── README.md             # 本文件
```

## ✨ 功能特性

### 基础功能

- ✅ 四则运算 (+, -, *, /)
- ✅ 浮点数和整数支持
- ✅ 栈操作（清空、显示）
- ✅ 完善的错误处理

### 高级功能

- ✅ 数学函数：sqrt, pow, sin, cos, tan
- ✅ 斐波那契数列计算 (`fib`)
- ✅ 杨辉三角计算 (`pascal`)
- ✅ 计算历史记录
- ✅ 交互式命令行界面

## 🚀 快速开始

### 编译程序

```bash
# 克隆项目
git clone [your-repo-url]
cd rpn_calc

# 编译
g++ rpn_calc.cpp -o rpn_calc -std=c++11

# 运行
./rpn_calc
```

### 基本使用示例

```bash
> 5 5 +
结果: 10.000000

> 1 2 + 3 + 7 7 * +
结果: 55.000000

> 10 fib
结果: 55.000000

> 5 2 pascal
结果: 10.000000
```

## 📖 文档

### 生成HTML文档

```bash
# 安装Nim和Nimib
# 参考: https://codeberg.org/janAkali/grabnim

# 生成文档
nim r rpn_manual.nim

# 文档将生成为 rpn_manual.html
```

### 在线文档

访问 GitHub Pages: [你的GitHub Pages链接]

## 🎯 支持的操作

|类型  |操作符                   |说明      |示例                  |
|----|----------------------|--------|--------------------|
|基本运算|`+`, `-`, `*`, `/`    |四则运算    |`5 3 +`             |
|数学函数|`sqrt`, `pow`         |平方根、幂运算 |`16 sqrt`, `2 8 pow`|
|三角函数|`sin`, `cos`, `tan`   |三角函数（弧度）|`1.5708 sin`        |
|特殊运算|`fib`                 |斐波那契数列  |`10 fib`            |
|特殊运算|`pascal`              |杨辉三角    |`5 2 pascal`        |
|栈操作 |`clear`, `display`    |清空、显示栈  |`display`           |
|其他  |`history`, `help`, `q`|历史、帮助、退出|`history`           |


## 🔧 技术实现细节

### 核心算法

**斐波那契数列**（迭代实现，O(n)复杂度）：

```cpp
double fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    double a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        double temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
```

**杨辉三角**（优化的组合数算法）：

```cpp
double pascal(int n, int k) {
    if (k > n - k) k = n - k;  // 优化
    double result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}
```

### 错误处理机制

使用C++异常处理确保程序健壮性：

- `std::runtime_error` 用于所有运行时错误
- `try-catch` 块捕获并显示友好的错误信息
- 输入验证防止非法操作

## 📊 测试用例

### 基本运算测试

```bash
5 5 +          # 期望: 10
10 3 -         # 期望: 7
4 5 *          # 期望: 20
20 4 /         # 期望: 5
```

### 高级功能测试

```bash
16 sqrt        # 期望: 4
2 10 pow       # 期望:
```
