#include <stdio.h>  // 包含标准输入输出头文件

// 定义一个计算两数之和的函数
int add_numbers(int a, int b) {
    return a + b;
}

// 主函数，程序入口
int main() {
    // 变量声明和初始化
    int num1 = 10;
    int num2 = 20;
    int sum = 0;
    
    // 调用函数
    sum = add_numbers(num1, num2);
    
    // 打印结果
    printf("数字 %d 和 %d 的和是: %d\n", num1, num2, sum);
    
    // 用户输入示例
    int user_input;
    printf("请输入一个整数: ");
    scanf("%d", &user_input);
    printf("你输入的是: %d\n", user_input);
    
    // 条件判断
    if (user_input > 100) {
        printf("这个数大于100\n");
    } else {
        printf("这个数小于等于100\n");
    }
    
    // 循环示例
    printf("从1数到5:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;  // 程序正常结束
}