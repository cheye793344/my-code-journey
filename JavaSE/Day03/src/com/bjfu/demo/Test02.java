package com.bjfu.demo;

import java.util.Random;
import java.util.Scanner;

public class Test02 {
    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);

        int i = 1;

        while(i <= 10){
            System.out.println("100以内数字，第" + i + "轮！看看你几次能猜对");
        Random random = new Random();
         int num = random.nextInt(100);
         int guess = 0;
          while (num !=  guess){
              guess = sc.nextInt();
              if(guess > num){
                  System.out.println("猜大了,再来一次");
                  continue;
              }
              if(guess < num){
                  System.out.println("猜小了，再来一次");
                  continue;
              }
              if(guess == num) {
                  if(i < 10) {
                      System.out.println("恭喜你猜对了！再玩下一轮吧");
                      i++;
                      break;
                  }
                  if(i == 10){
                      System.out.println("恭喜你猜对了最后一轮！游戏结束");
                      break;
                  }
              }
         }
        }
    }
}
