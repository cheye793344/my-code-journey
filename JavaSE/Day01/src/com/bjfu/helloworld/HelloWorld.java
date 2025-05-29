package com.bjfu.helloworld;

public class HelloWorld {
    /**
     * 程序的主入口点
     * @param args 命令行参数，未在此程序中使用
     */

    public static void main(String[] args) {
        // 打印Hello World到控制台
        System.out.println("Hello World");
            System.out.println(getRandomCode());
        }
        //定义一个方法帮我生成一个验证码返回
    public static String getRandomCode(){
        String str="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        StringBuilder sb=new StringBuilder();
        for(int i=0;i<4;i++){
            int index=(int)(Math.random()*str.length());
            char ch=str.charAt(index);
            sb.append(ch);
        }
        return sb.toString();
    }
}





