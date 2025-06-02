package com.bjfu.demo;


public class GoldCard extends Card {

    public GoldCard(String cardId, String licensePlate, String owner, double balance, String phone) {
        super(cardId, licensePlate, owner, balance, phone);
    }
    @Override
            public void consume(double amount) {
        if (getBalance() >= amount)
        {
            setBalance(getBalance() - amount * 0.8);
             System.out.println("本次消费" + amount + "元");
              System.out.println("您是尊贵的金卡会员！");
             System.out.println("优惠金额" + amount * 0.2 + "元");
            System.out.println("实际消费" + amount * 0.8 + "元");

            if(amount >= 200){
                printTicket();
            }
        } else {
            System.out.println("余额不足");
        }
    }

    private void printTicket() {
         System.out.println("您本次原始消费满200元，请领取您的免费洗车票！");
    }
}
