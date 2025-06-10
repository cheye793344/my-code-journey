package com.bjfu.demo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.List;
@Data
@NoArgsConstructor
@AllArgsConstructor

public class Player {
    private String name;
    private List<Card> hands = new ArrayList<>();
}
