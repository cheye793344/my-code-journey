package com.bjfu.demo;


public class SilverCard extends Card{
    public SilverCard(String cardId, String licensePlate, String owner, int balance, String phone) {
         super(cardId, licensePlate, owner, balance, phone);
    }

    @Override
    public void consume(double amount){
        if (amount <= getBalance()) {
            setBalance(getBalance() - amount * 0.9);
            System.out.println("本次消费" + amount + "元");
             System.out.println("您是尊贵的银卡会员！");
            System.out.println("优惠金额" + amount * 0.1 + "元");
             System.out.println("实际消费" + amount * 0.9 + "元");
        } else {
            System.out.println("余额不足");
        }
    }
}
