package com.bjfu.demo;

import java.util.Objects;
import java.util.Random;
import java.util.Scanner;

public class SmartHome {
    public static void main(String[] args) {

        Appliance[] appliances = new Appliance[4];
        appliances[0] = new Chandelier("吊灯", false, Chandelier.brightnessLevels.HIGH);
        appliances[1] = new FloortoceilingWindow("落地窗", false, FloortoceilingWindow.Level.FULLY);
        appliances[2] = new AirCondition("主卧空调", false, 25);
        appliances[3] = new AirCondition("客厅空调", false, 25);

        //创建一个智能家居控制系统对象
        SmartHomeControlSystem smartHomeControlSystem = SmartHomeControlSystem.getInstance();
        smartHomeControlSystem.control(appliances[0]);

        //打印全部设备状态
        for (Appliance appliance : appliances) {
            System.out.println(appliance.getModelNumber() + "\t当前状态：" + ((appliance.isStatus()) ? "开启" : "关闭"));
        }
        //用户选择要控制的设备
        System.out.println("请输入要控制的设备序号：");
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();

       // 控制器追踪到该设备
Appliance appliance = null;

        if (appliances == null) {
            System.out.println("未添加设备");
            return;
        }

for (Appliance app : appliances) {
    if (Objects.equals(app.getModelNumber(), input)) {
        appliance = app;
        break;
    }
}

if (appliance != null) {
    smartHomeControlSystem.control(appliance);
    String modelNumber = appliance.getModelNumber();
    boolean status = appliance.isStatus();
    System.out.println(modelNumber + "\t当前状态：" + (status ? "开启" : "关闭"));
} else {
    System.out.println("未找到匹配的设备");
}

        }
    }

