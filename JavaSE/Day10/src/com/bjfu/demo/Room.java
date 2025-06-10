package com.bjfu.demo;

import java.util.*;

import lombok.*;
public class Room {
private List<Card> cards = new ArrayList<>();
    {
        String[] suits = {"♠", "♥", "♣", "♦"};
        String[] point = {"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "Ace", "2"};
        for (String n : point) {
            for (String s : suits) {
                cards.add(new Card(s,n));
            }
        }
        //cards.add(new Card("Big","Joker"));
        //cards.add(new Card("Little","Joker"));
        Collections.addAll(cards, new Card("Big","Joker"), new Card("Little","Joker"));
    }

    public void start() {
        //洗牌
        Collections.shuffle(cards);
        System.out.println(cards);

        //发牌
        Map<Player, List<Card>> players = new HashMap<>();
        List<Card> p1Cards = new ArrayList<>();
        List<Card> p2Cards = new ArrayList<>();
        List<Card> p3Cards = new ArrayList<>();
        Player p1 = new Player("p1",  p1Cards);
        Player p2 = new Player("p2",  p2Cards);
        Player p3 = new Player("p3",  p3Cards);
        players.put(p1, p1Cards);
        players.put(p2, p2Cards);
        players.put(p3, p3Cards);

        for (int i = 0; i < 51; i++) {
            if (i % 3 == 0) {
                p1Cards.add(cards.get(i));
            } else if (i % 3 == 1) {
                p2Cards.add(cards.get(i));
            } else {
                p3Cards.add(cards.get(i));
            }
        }
        //叫地主（简化版，随机指定一名玩家为地主）
        Player landlord = p1;
        System.out.println(landlord.getName() + "是地主");
        //地主发牌
        landlord.getHands().addAll(cards.subList(51, 54));
        //展示地主牌
        System.out.println("地主牌：" + cards.subList(51, 54));
        //展示牌组
        System.out.println("牌组：");
        for (Map.Entry<Player, List<Card>> entry : players.entrySet()) {
            System.out.println(entry.getKey().getName() + "的牌：" + entry.getValue());
        }
        //对牌
        Card.sortHands(p1Cards);
        Card.sortHands(p2Cards);
        Card.sortHands(p3Cards);
        System.out.println("对牌后：");
        for (Map.Entry<Player, List<Card>> entry : players.entrySet()) {
            System.out.println(entry.getKey().getName() + "的牌：" + entry.getValue());
        }
    }
}
