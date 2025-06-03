
package com.bjfu.demo;

public class SmartHomeControlSystem {

    // 私有静态实例（单例）
    private static final SmartHomeControlSystem INSTANCE = new SmartHomeControlSystem();

    // 私有构造函数
    private SmartHomeControlSystem() {}

    // 公共静态方法返回唯一实例
    public static SmartHomeControlSystem getInstance() {
        return INSTANCE;
    }

    // 控制设备的方法
    public void control(Appliance appliance) {
        System.out.println(appliance.getModelNumber() + "\t当前状态：" + (appliance.isStatus() ? "开启" : "关闭"));
        appliance.Click();
        System.out.println(appliance.getModelNumber() + "\t当前状态：" + (appliance.isStatus() ? "开启" : "关闭"));
    }
}
