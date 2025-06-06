package com.bjfu.demo;

import java.util.*;

public class MovieManage {

    private static List<Movie> movies = new  LinkedList<>();
    public void run() {
        //打印操作界面
        System.out.println("========电影管理系统========");
        System.out.println("1. 上架电影");
        System.out.println("2. 下架电影");
        System.out.println("3. 查询电影");
        System.out.println("4. 多选电影");
        System.out.println("5. 退出系统");

        //获取用户输入
        Scanner scanner = new Scanner(System.in);
        int choice = scanner.nextInt();
        switch (choice) {
            case 1:
                System.out.println("请输入电影名称：");
                String name = scanner.next();
                System.out.println("请输入导演：");
                String director = scanner.next();
                System.out.println("请输入主演：");
                String actor = scanner.next();
                movies.add(new Movie(name, director, actor));
                break;

                case 2:
                    System.out.println("请输入电影名称：");
                    String name3 = scanner.next();
                    for (Movie movie : movies) {
                        if (movie.getName().equals(name3)) {
                            movies.remove(movie);
                            break;
                        }
                    }
                    break;

                case 3:
                    System.out.println("请输入电影名、导演或主演：");
                    String keyword = scanner.next();
                    for (Movie movie : movies) {
                        if (movie.getName().contains(keyword) || movie.getDirector().contains(keyword) || movie.getActor().contains(keyword)) {
                            System.out.println(movie.getName() + "\t" + movie.getDirector() + "\t" + movie.getActor());
                        }
                    }
                    break;

                case 4:
                    //创建一个临时数组存放待删除电影
                    List<Movie> tempMovies = new ArrayList<>();
                    System.out.println("选择以何种方式选中：");
                    System.out.println("1. 按电影名");
                    System.out.println("2. 按导演");
                    System.out.println("3. 按主演");
                    int choice2 = scanner.nextInt();
                    switch (choice2) {
                        case 1 ://按电影名，选中所有相同电影名的电影
                        System.out.println("请输入电影名：");
                        String name2 = scanner.next();
                        for (Movie movie : movies) {
                            //若找到符合的电影，则从原数组移动到临时数组中
                            if (movie.getName().equals(name2)) {
                                tempMovies.add(movie);
                            }
                        }
                        if(tempMovies.isEmpty()){
                            System.out.println("没有找到相关电影");
                        }
                        for (Movie movie : tempMovies) {
                            movies.remove(movie);
                        }
                        break;

                        case 2:
                            // 处理按导演选中电影的逻辑
                            System.out.println("请输入导演：");
                            String Director = scanner.next();
                            for (Movie movie : movies) {
                                if (movie.getDirector().equals(Director)) {
                                    tempMovies.add(movie);
                                }
                            }
                            if(tempMovies.isEmpty()){
                                System.out.println("没有找到相关电影");
                            }
                            for (Movie movie : tempMovies) {
                                movies.remove(movie);
                            }
                            break;

                            case 3:{
                                System.out.println("请输入主演：");
                                String Actor = scanner.next();
                                for (Movie movie : movies) {
                                    if (movie.getActor().equals(Actor)) {
                                        tempMovies.add(movie);
                                    }
                                }
                                if(tempMovies.isEmpty()){
                                    System.out.println("没有找到相关电影");
                                }
                                for (Movie movie : tempMovies) {
                                    movies.remove(movie);
                                }
                                break;
                            }
                        default:
                            System.out.println("无效的选择");
                            break;
                    }

            case 5:
                System.out.println("感谢使用电影管理系统！");
                System.exit(0);
                break;
            default:
                System.out.println("无效的选择");
                break;
        }
    }
}
