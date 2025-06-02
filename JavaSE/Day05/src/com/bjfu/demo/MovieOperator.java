package com.bjfu.demo;
import java.util.Scanner;

public class MovieOperator {
private final Movie[] movie;
public MovieOperator(Movie[] movies){
    this.movie = movies;
}


    public void printMoviesById() {
Scanner sc = new Scanner(System.in);
    System.out.println("请输入要查询的序号：");
     int id = sc.nextInt();
     boolean  found = false;
     for (Movie movie : movie){
         if (movie.getId() == id){
             found = true;
             System.out.println(movie.getId() + "\t "+ movie.getName() +"\t"+ movie.getScore() +"\t"+ movie.getActor());
         }
     }
     if (!found){
         System.out.println("没有找到该电影");
     }
    }


    public void printMoviesByScore() {
     Scanner sc = new Scanner(System.in);
     int option =  sc.nextInt();
     System.out.println("1.降序\t2.升序");
     switch (option){
         case 1:
             for (int i = 0; i < movie.length; i++) {
                 for (int j = i + 1; j < movie.length; j++) {
                     if (movie[i].getScore() < movie[j].getScore()) {
                         Movie temp = movie[i];
                         movie[i] = movie[j];
                         movie[j] = temp;
                     }
                 }
             }
             break;
         case 2:
              for (int i = 0; i < movie.length; i++) {
                 for (int j = i + 1; j < movie.length; j++) {
                     if (movie[i].getScore() > movie[j].getScore()) {
                         Movie temp = movie[i];
                         movie[i] = movie[j];
                         movie[j] = temp;
                     }
                 }
             }
     }
    }

    public void printMoviesByActor() {
    Scanner sc = new Scanner(System.in);
     String actor = sc.next();
      boolean  found = false;
     for (Movie movie : movie){
         if (movie.getActor().equals(actor)){
             System.out.println(movie.getId() + "\t "+ movie.getName() +"\t"+ movie.getScore() +"\t"+ movie.getActor());
         }
     }
     if (!found){
         System.out.println("没有找到该演员");
     }
    }

    public void printMoviesByName() {
     Scanner sc = new Scanner(System.in);
      String name = sc.next();
       boolean  found = false;
        for (Movie movie : movie){
           if (movie.getName().contains(name)){
               System.out.println(movie.getId() + "\t "+ movie.getName() +"\t"+ movie.getScore() +"\t"+ movie.getActor());
           }
       }
        if (!found){
            System.out.println("没有找到该电影");
        }
    }

    public void printMovies() {
    System.out.println("序号\t电影名\t评分\t主演");

    for (Movie movie : movie){
        System.out.println(movie.getId() + "\t "+ movie.getName() +"\t"+ movie.getScore() +"\t"+ movie.getActor());
    }
    }
}
