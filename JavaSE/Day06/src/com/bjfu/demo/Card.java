package com.bjfu.demo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor

public class Card {
     private String cardId;
      private String licensePlate;
       private String owner;
        private double balance;
         private String phone;

         //预存金额
     public void recharge(double amount){
          balance += amount;
     }

     //消费
     public void consume(double amount){
          balance -= amount;

             if (amount <= getBalance()) {
                 setBalance(getBalance() - amount);
                 System.out.println("本次消费" + amount + "元");
                 System.out.println("优惠金额" + amount * 0.0 + "元");
                 System.out.println("实际消费" + amount * 1.0 + "元");
             } else {
                 System.out.println("余额不足");
             }
     }


    }


