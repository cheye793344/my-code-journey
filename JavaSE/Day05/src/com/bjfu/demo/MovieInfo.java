package com.bjfu.demo;

import java.util.Scanner;

public class MovieInfo {

    public static void main(String[] args)
    {
        Movie[] movies = new Movie[6];
        movies[0] =  new Movie(1, "唐顿庄园", 9.5, "罗宾·法拉利");
         movies[1] =  new Movie(2, "唐顿庄园2", 9.5, "罗宾·法拉利");
          movies[2] =  new Movie(3, "唐顿庄园3", 9.5, "罗宾·法拉利");
           movies[3] =  new Movie(4, "唐顿庄园4", 9.5, "罗宾·法拉利");
            movies[4] =  new Movie(5, "唐顿庄园5", 9.5, "罗宾·法拉利");
             movies[5] =  new Movie(6, "唐顿庄园6", 9.5, "罗宾·法拉利");

             MovieOperator mo = new MovieOperator(movies);

             Scanner sc = new Scanner(System.in);
             System.out.println("欢迎使用电影小助手！\n" +
                     "0.退出小助手\n" +
                     "1.查看所有电影信息\n" +
                     "2.按评分排序\n" +
                     "3.按序号查找\n" +
                     "4.按主演查找\n" +
                     "5.按电影名查找\n");
             int option = sc.nextInt();
             switch (option) {
                 case 0:
                     System.out.println("欢迎下次再来");
                     break;
                 case 1:
                     mo.printMovies();
                     break;
                 case 2:
                     mo.printMoviesByScore();
                     break;
                 case 3:
                     mo.printMoviesById();
                     break;
                 case 4:
                     mo.printMoviesByActor();
                     break;
                 case 5:
                      mo.printMoviesByName();
                       break;

                       default:
                           System.out.println("输入错误！");
                           break;
              }

    }
}
