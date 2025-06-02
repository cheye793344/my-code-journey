package com.bjfu.demo;
import java.util.Scanner;

public class MiniPay {
     public static void main(String[] args)
    {
         System.out.println("欢迎使用MiniPay");

         GoldCard goldcard = new GoldCard("G001", "京A88888", "张三", 1000, "13888888888");
          SilverCard silvercard = new SilverCard("S001", "京A88888", "张三", 1000, "13888888888");
          Card standardcard = new Card("M001", "京A88888", "张三", 1000, "13888888888");
goldcard.recharge(1000);
 silvercard.recharge(1000);
 standardcard.recharge(1000);
    pay(goldcard);
    pay(silvercard);
    pay(standardcard);
    }

    public static void pay(Card card)
    {
         System.out.println("请输入消费金额：");
          Scanner Scanner = new Scanner(System.in);
          double amount = Scanner.nextDouble();
        card.consume(amount);
    }

}
