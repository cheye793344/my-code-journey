package com.bjfu.demo;

public class Movie {
    private int id;
    private String name;
    private double score;
    private String actor;

    //定义一个无参构造器
    public Movie() {}

    public Movie(int id, String name, double price, String actor) {
        this.id = id;
        this.name = name;
        this.score = price;
        this.actor = actor;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
    }

    public String getActor() {
        return actor;
    }

    public void setActor(String actor) {
        this.actor = actor;
    }
}
