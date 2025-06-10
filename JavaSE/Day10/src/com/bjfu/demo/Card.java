package com.bjfu.demo;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.*;

@Data
@NoArgsConstructor

public class Card {
    private String suit;
    private String point;

    private static final Map<String, String> POINT_RANK_MAP = new HashMap<>();
    static
    {
        POINT_RANK_MAP.put("3", "3");
        POINT_RANK_MAP.put("4", "4");
        POINT_RANK_MAP.put("5", "5");
        POINT_RANK_MAP.put("6", "6");
        POINT_RANK_MAP.put("7", "7");
        POINT_RANK_MAP.put("8", "8");
        POINT_RANK_MAP.put("9", "9");
        POINT_RANK_MAP.put("10", "10");
        POINT_RANK_MAP.put("J", "11");
        POINT_RANK_MAP.put("Q", "12");
        POINT_RANK_MAP.put("K", "13");
        POINT_RANK_MAP.put("Ace", "14");
        POINT_RANK_MAP.put("2", "15");
        POINT_RANK_MAP.put("Joker", "16");
    }
    //"♠", "♥","♦", "♣"
    static final Map<String, String> SUIT_RANK_MAP = new HashMap<>();
    static
    {
        SUIT_RANK_MAP.put("♠", "4");
        SUIT_RANK_MAP.put("♥", "3");
        SUIT_RANK_MAP.put("♦", "2");
        SUIT_RANK_MAP.put("♣", "1");
        SUIT_RANK_MAP.put("Big", "6");
        SUIT_RANK_MAP.put("Small", "5");
    }

    static public void sortHands(List<Card> hands){
        Collections.sort(hands, new Comparator<Card>() {
            @Override
            public int compare(Card o1, Card o2) {
                int rank1 = Integer.parseInt(POINT_RANK_MAP.get(o1.getPoint()));
                int rank2 = Integer.parseInt(POINT_RANK_MAP.get(o2.getPoint()));
                if(rank1 != rank2){
                    return rank2 - rank1;
                }
                else {
                    rank1 = Integer.parseInt(SUIT_RANK_MAP.get(o1.getSuit()));
                    rank2 = Integer.parseInt(SUIT_RANK_MAP.get(o2.getSuit()));
                    return rank2 - rank1;
                }
            }
        });
    }

    public Card(String suit, String number)
    {
        this.suit = suit;
        this.point = number;
    }
    @Override
    public String toString()
    {
        return suit + point;
    }
}
