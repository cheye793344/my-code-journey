package com.bjfu.demo;

import java.util.Scanner;

public class Test01 {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入第一个数字：");
        double num1 = sc.nextDouble();
        System.out.println("请输入第二个数字：");
        double num2 = sc.nextDouble();
        System.out.println("请输入运算符：");
        char op = sc.next().charAt(0);
        switch (op){
            case '+':
                System.out.println(num1 + num2);
                break;
            case '-':
                System.out.println(num1 - num2);
                break;
            case '*':
                System.out.println(num1 * num2);
                break;
            case '/':
                System.out.println(num1 / num2);
                break;
            default:
                System.out.println("输入有误");
        }
    }
}
